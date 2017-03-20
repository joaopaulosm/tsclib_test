/*
 * tsclib_test.h
 *
 *  Created on: 16 mars 2017
 *      Author: joaopaulomartins
 */

#ifndef TSCLIB_TEST_H_
#define TSCLIB_TEST_H_

#define XUSERADDR	0x1000

#define TSC_ERR(msg, val) fprintf(stderr,"[TSC ERR] Function %s returned error number %d \n", msg, val)
#define TSC_WR(reg, val) printf("[TSC WR]  Register 0x%02x = 0x%08x \n", reg, val)
#define TSC_RD(reg, val) printf("[TSC RD]  Register 0x%02x = 0x%08x \n", reg, val)
#define TSC_LOG(msg) printf("[TSC LOG] %s\n", msg)
#define TSC_SETCLR(reg, set, clr) printf("[TSC SETCLR] Register 0x%02x set mask = 0x%08x clear mask = 0x%08x\n" ,reg, set, clr);

typedef enum {
    tosca_success = 0,    
    tosca_error  = -1,   
} tosca_status;

/* For now only works with FMC 1 */
static inline int32_t ifc14_get_fmc_tcsr_offset(void) 
{
    return 0x80;
}

/* For now only use FMC 1 in SMEM mode !!!! */
static inline int32_t ifc14_get_scope_tcsr_offset(void) {
	return 0x78;
}

int tsc_tcsr_read(int offset, int register_idx, int32_t *i32_reg_val);
int tsc_tcsr_write(int offset, int register_idx, int32_t value);
int tsc_tcsr_setclr(int offset, int register_idx, int32_t setmask, int32_t clrmask)

int ifc14_xuser_tcsr_read(int register_idx, int32_t *i32_reg_val);
int ifc14_xuser_tcsr_write(int register_idx, int32_t value);
int ifc14_xuser_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask);

int ifc14_scope_tcsr_read(int register_idx, int32_t *i32_reg_val);
int ifc14_scope_tcsr_write(int register_idx, int32_t value);
int ifc14_scope_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask);

int ifc14_scope_acq_tcsr_read(int register_idx, int32_t *i32_reg_val);
int ifc14_scope_acq_tcsr_write(int register_idx, int32_t value);
int ifc14_scope_acq_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask);

int ifc14_fmc_tcsr_read(int register_idx, int32_t *reg_val);
int ifc14_fmc_tcsr_write(int register_idx, int32_t value);
int ifc14_fmc_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask);


#endif /* TSCLIB_TEST_H_ */
