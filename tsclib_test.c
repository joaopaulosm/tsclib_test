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
		TSC_ERR("tsc_init()",ret);
		goto clean_exit;
	}

	TSC_LOG("Reading TOSCA signature");
	if (ifc14_xuser_tcsr_read(0x00, &scrap_register) != 0)
		goto error_tosca;
	TSC_RD(0x00, scrap_register);

	TSC_LOG("Reading SCOPE signature");
	if (ifc14_scope_tcsr_read(0x00, &scrap_register) != 0)
		goto error_tosca;
	TSC_RD(0x60, scrap_register);

	TSC_LOG("R/W Test Register");
	if (ifc14_xuser_tcsr_write(0x01, TESTBITS) != 0)
		goto error_tosca;
	
	if (ifc14_xuser_tcsr_read(0x01, &scrap_register) != 0)
		goto error_tosca;
	TSC_RD(0x01, scrap_register);


	/* DAQ Configuration -> FMC 1 SMEM MODE !!! */

	/* Downsampling */
	if (ifc14_scope_acq_tcsr_setclr(0x00, 1<<15, 0) != 0)
		goto error_tosca;

	/* Averaging factor = 4 */
	if (ifc14_scope_acq_tcsr_setclr(0x00, 0, 7 << 2) != 0)
		goto error_tosca;

	/* Configure BUFFER size register 7B - 16 MB !!! */
	if (ifc14_scope_acq_tcsr_setclr(0x03, 16, 0) != 0)
		goto error_tosca;

	/* Allocate buffers in kernel */
	


	
error_tosca:
	TSC_LOG("Exiting ...");
	ret = tsc_exit();
	if (ret < 0)
		TSC_ERR("tsc_exit()",ret);

clean_exit:
	return 0;
}


