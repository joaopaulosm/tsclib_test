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
    ret = tsc_csr_read((offset + (register_idx * 4)), i32_reg_val);   
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
        ret = tsc_csr_write(offset + (register_idx * 4), &value);
        
        if (ret >= 0)
        {
            tsc_tcsr_read(offset, register_idx, &i32_reg_val);
            TSC_WR(register_idx, i32_reg_val);
        }
    }
    return ret;
}


int tsc_tcsr_setclr(int offset, int register_idx, int32_t setmask, int32_t clrmask)
{
    int32_t i32_reg_val;
    int ret;
    
    ret = tsc_csr_read((offset + (register_idx * 4)), &i32_reg_val);
    if (ret < 0) goto read_err;
    
    TSC_SETCLR(register_idx, setmask, clrmask);

    i32_reg_val &= ~clrmask;
    i32_reg_val |= setmask;

    ret = tsc_csr_write(offset + (register_idx * 4), &i32_reg_val);
    if (ret < 0) goto write_err;

    if (tsc_tcsr_read(offset, register_idx, &i32_reg_val) == 0)
    {
        TSC_RD(register_idx, i32_reg_val);
        return 0;
    }
    else
        return -1;

write_err:
    TSC_ERR("tsc_csr_write()", ret);

read_err:
    TSC_ERR("tsc_csr_read()", ret);
    
    return ret;
}

/* Functions for accessing any XUSER TCSR *********************************************************/

int ifc14_xuser_tcsr_read(int register_idx, int32_t *i32_reg_val)
{
    return tsc_tcsr_read(XUSERADDR, register_idx, i32_reg_val);
}

int ifc14_xuser_tcsr_write(int register_idx, int32_t value)
{
    return tsc_tcsr_write(XUSERADDR, register_idx, value);
}

int ifc14_xuser_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask)
{
    return tsc_tcsr_setclr(XUSERADDR, register_idx, setmask, clrmask);
}

/* **********************************************************************************************/


/* Functions for accessing 0x60 to 0x6F (SCOPE MAIN TCSR) *******************************************/

int ifc14_scope_tcsr_read(int register_idx, int32_t *i32_reg_val)
{
    return tsc_tcsr_read(XUSERADDR, 0x60 + register_idx, i32_reg_val);
}

int ifc14_scope_tcsr_write(int register_idx, int32_t value)
{
    return tsc_tcsr_write(XUSERADDR, 0x60 + register_idx, value);
}

int ifc14_scope_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask)
{
    return tsc_tcsr_setclr(XUSERADDR, 0x60 + register_idx, setmask, clrmask);
}

/**********************************************************************************************************/

/* Functions for accessing 0x70-0x73, 0x74-0x77, 0x78-0x7B, 0x7C-0x7F 
(SCOPE FMC1/FMC2 and SRAM/SMEM specific) registers ********************************************************/

int ifc14_scope_acq_tcsr_read(int register_idx, int32_t *i32_reg_val)
{
    return tsc_tcsr_read(XUSERADDR, ifc14_get_scope_tcsr_offset() + register_idx, i32_reg_val);
}

int ifc14_scope_acq_tcsr_write(int register_idx, int32_t value)
{
    return tsc_tcsr_write(XUSERADDR, ifc14_get_scope_tcsr_offset() + register_idx, value);
}

int ifc14_scope_acq_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask)
{
    return tsc_tcsr_setclr(XUSERADDR, ifc14_get_scope_tcsr_offset() + register_idx, setmask, clrmask);
}

/***********************************************************************************************************/

/* Functions for accessing 0x80-0xBF or 0xC0-0xFF based on FMC1/FMC2. */

int ifc14_fmc_tcsr_read(int register_idx, int32_t *reg_val)
{
    return tsc_tcsr_read(XUSERADDR, ifc14_get_fmc_tcsr_offset() + register_idx, reg_val);
}

int ifc14_fmc_tcsr_write(int register_idx, int32_t value)
{
    return tsc_tcsr_write(XUSERADDR, ifc14_get_fmc_tcsr_offset() + register_idx, value);
}

int ifc14_fmc_tcsr_setclr(int register_idx, int32_t setmask, int32_t clrmask)
{
    return tsc_tcsr_setclr(XUSERADDR, ifc14_get_fmc_tcsr_offset() + register_idx, setmask, clrmask);
}



int ifc14_dma_allocate(ifc14device *ifcdevice)
{
    //ifcdevice->sram_dma_buf = calloc(1, sizeof(struct pev_ioctl_buf));
    ifcdevice->sram_dma_buf = calloc(1, sizeof(struct tsc_ioctl_kbuf_req));
    if (!ifcdevice->sram_dma_buf) {
        goto err_sram_ctl;
    }

    ifcdevice->sram_dma_buf->size = 16*1024;

    LOG((5, "Trying to allocate %dkiB in kernel\n", 16*1024 / 1024));

    if (tsc_kbuf_alloc(ifcdevice->sram_dma_buf) == NULL) {
        goto err_sram_buf;
    }

    //ifcdevice->smem_dma_buf = calloc(1, sizeof(struct pev_ioctl_buf));
    ifcdevice->smem_dma_buf = calloc(1, sizeof(struct tsc_ioctl_kbuf_req));
    if (!ifcdevice->smem_dma_buf) {
        goto err_smem_ctl;
    }

    // Try to allocate as large dma memory as possible
    ifcdevice->smem_dma_buf->size = 128*1024*1024;
    do {
        LOG((5, "Trying to allocate %dMiB in kernel\n", ifcdevice->smem_dma_buf->size / 1024 / 1024));

        p = tsc_kbuf_alloc(ifcdevice->smem_dma_buf);


    } while (p == NULL && (ifcdevice->smem_dma_buf->size >>= 1) > 0);

    if(!p) {
        goto err_smem_buf;
    }

    LOG((5, "Trying to allocate %dMiB in userspace\n", 128*1024*1024 / 1024 / 1024));
    ifcdevice->all_ch_buf = calloc(128*1024*1024, 1);
    if(!ifcdevice->all_ch_buf){
        goto err_smem_user_buf;
    }

    return 0;

err_smem_user_buf:
    //pevx_buf_free(ifcdevice->card, ifcdevice->smem_dma_buf);
    tsc_kbuf_free(ifcdevice->smem_dma_buf);
 

err_smem_buf:
    free(ifcdevice->smem_dma_buf);

err_smem_ctl:
    //pevx_buf_free(ifcdevice->card, ifcdevice->smem_dma_buf);
    tsc_kbuf_free(ifcdevice->sram_dma_buf);

err_sram_buf:
    free(ifcdevice->sram_dma_buf);

err_sram_ctl:
    return -1;
}