/*
 * tsclib_test.h
 *
 *  Created on: 16 mars 2017
 *      Author: joaopaulomartins
 */

#ifndef TSCLIB_TEST_H_
#define TSCLIB_TEST_H_

#define BASEADDRESS 0x68000000
#define XUSERADDR	0x1000

#define TOSCA_ERR(msg, val) fprintf(stderr,"TOSCA function %s returned error number %d \n", msg, val)

typedef enum {
    tosca_success           = 0,    
    tosca_error			    = -1,   
} tosca_status;

int tsc_tcsr_read(int offset, int register_idx, int32_t *i32_reg_val);
tosca_status tsc_tcsr_write(int offset, int register_idx, int32_t value);


#endif /* TSCLIB_TEST_H_ */
