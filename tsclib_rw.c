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
    ret = tsc_csr_rd((BASEADDRESS + offset + (register_idx * 4)), i32_reg_val);
    
    if (ret < 0)
    {
        printf("Error trying to read reg 0x%02x : tsc_csr_rd() returned %d\n", register_idx, ret);
    }
    // else
    // {
    //     printf("Wrote 0x%08x to register %02x \n", *i32_reg_val, register_idx);
    // }
    return ret;
}

int tsc_tcsr_write(int offset, int register_idx, int32_t value)
{
    int32_t i32_reg_val;
    int ret;

    ret = tsc_tcsr_read(offset, register_idx, &i32_reg_val);

    if (ret >= 0)
    {
        ret = tsc_csr_wr(BASEADDRESS + offset + (register_idx * 4), value);
        
        if (ret >= 0)
        {
            tsc_tcsr_read(offset, register_idx, &i32_reg_val);
            printf("Wrote 0x%08x to register %02x \n", i32_reg_val, register_idx);
        }
    }
    return ret;
}

