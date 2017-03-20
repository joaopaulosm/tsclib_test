/*
 * tsclib_rw.c
 *
 *  Created on: 16 mars 2017
 *      Author: joaopaulomartins
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/* Include TSCLIB headers */
#include "tsculib.h"
#include "tscioctl.h"

#include "tsclib_test.h"

int tsc_tcsr_read(int offset, int register_idx, int32_t *i32_reg_val)
{
    int ret;
    ret = tsc_csr_read((BASEADDRESS + offset + (register_idx * 4)), i32_reg_val);   
    if (ret < 0)
    {
        TSC_ERR("tsc_csr_read()", ret);
    }
    
    return ret;
}

int tsc_tcsr_write(int offset, int register_idx, int32_t value)
{
    int32_t i32_reg_val;
    int ret;

    ret = tsc_tcsr_read(offset, register_idx, &i32_reg_val);

    if (ret >= 0)
    {
        ret = tsc_csr_write(BASEADDRESS + offset + (register_idx * 4), &value);
        
        if (ret >= 0)
        {
            tsc_tcsr_read(offset, register_idx, &i32_reg_val);
            TSC_WR(register_idx, i32_reg_val);
        }
    }
    return ret;
}

