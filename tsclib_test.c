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
		printf("Missing FMC number\n");
		return -1;
	} 
	else {
		if ((atoi(argv[1]) != 1) && (atoi(argv[1]) != 2)) {
			printf("Wrong FMC number [1 or 2]\n");
			return -1;
		}
	}

	printf("Initializing TSCLIB userspace driver...\n");
	ret = tsc_init();
	if (ret < 0)
	{
		TOSCA_ERR("tsc_init()",ret);
		goto clean_exit;
	}

	printf("Reading TOSCA signature ...\n");
	if (tsc_tcsr_read(XUSERADDR, 0x00, &scrap_register) != 0)
		goto error_tosca;
	printf("TOSCA SIGNATURE = 0x%08x\n", scrap_register);

	printf("Reading SCOPE signature ...\n");
	if (tsc_tcsr_read(XUSERADDR, 0x60, &scrap_register) != 0)
		goto error_tosca;
	printf("SCOPE SIGNATURE = 0x%08x\n", scrap_register);

	printf("R/W Test Register\n");
	
	if (tsc_tcsr_write(XUSERADDR, 0x01, TESTBITS) != 0)
		goto error_tosca;
	
	if (tsc_tcsr_read(XUSERADDR, 0x01, &scrap_register) != 0)
		goto error_tosca;
	
	printf("Wrote 0x%08x and read 0x%08x from TEST register\n", TESTBITS, scrap_register);
	

error_tosca:
	printf("Exiting ... \n");
	ret = tsc_exit();
	if (ret < 0)
		TOSCA_ERR("tsc_exit()",ret);

clean_exit:
	return 0;
}


