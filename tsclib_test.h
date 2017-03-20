/*
 * tsclib_test.h
 *
 *  Created on: 16 mars 2017
 *      Author: joaopaulomartins
 */

#ifndef TSCLIB_TEST_H_
#define TSCLIB_TEST_H_

#define BASEADDRESS 0x00000000 //TOSCA USER LIB DOES NOT NEED TO GET BASE ADDRESS FROM CLIENT
#define XUSERADDR	0x1000

#define TSC_ERR(msg, val) fprintf(stderr,"[TSC ERR] Function %s returned error number %d \n", msg, val)
#define TSC_WR(reg, val) printf("[TSC WR] Register 0x%02x = 0x%08x \n" )
#define TSC_RD(reg, val) printf("[TSC RD] Register 0x%02x = 0x%08x \n" )
#define TSC_LOG(msg) printf("[TSC LOG] %s\n", msg)

typedef enum {
    tosca_success           = 0,    
    tosca_error			    = -1,   
} tosca_status;

int tsc_tcsr_read(int offset, int register_idx, int32_t *i32_reg_val);
int tsc_tcsr_write(int offset, int register_idx, int32_t value);


#endif /* TSCLIB_TEST_H_ */
