/*
 * tsclib_test.c
 *
 *  Created on: 16 mars 2017
 *      Author: joaopaulomartins
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Include TSCLIB headers */
#include "tsculib.h"
#include "tscioctl.h"

/* Program headers */
#include "tsclib_test.h"

#define TESTBITS 0x1234ABCD


int main(int argc, char *argv[])
{
	int ret;
	int32_t scrap_register = 0;

	if (argc != 2) {
		TSC_LOG("Missing FMC number");
		return -1;
	} 
	else {
		if ((atoi(argv[1]) != 1) && (atoi(argv[1]) != 2)) {
			TSC_LOG("Wrong FMC number [1 or 2]");
			return -1;
		}
	}

	TSC_LOG("Initializing TSCLIB userspace driver");
	ret = tsc_init();
	if (ret < 0)
	{
		TOSCA_ERR("tsc_init()",ret);
		goto clean_exit;
	}

	TSC_LOG("Reading TOSCA signature");
	if (tsc_tcsr_read(XUSERADDR, 0x00, &scrap_register) != 0)
		goto error_tosca;
	TSC_RD(0x00, scrap_register);

	TSC_LOG("Reading SCOPE signature");
	if (tsc_tcsr_read(XUSERADDR, 0x60, &scrap_register) != 0)
		goto error_tosca;
	TSC_RD(0x00, scrap_register);

	TSC_LOG("R/W Test Register");
	if (tsc_tcsr_write(XUSERADDR, 0x01, TESTBITS) != 0)
		goto error_tosca;
	
	if (tsc_tcsr_read(XUSERADDR, 0x01, &scrap_register) != 0)
		goto error_tosca;
	TSC_RD(0x01, scrap_register);
	
error_tosca:
	TSC_LOG("Exiting ...");
	ret = tsc_exit();
	if (ret < 0)
		TOSCA_ERR("tsc_exit()",ret);

clean_exit:
	return 0;
}


