/*******************************************************************************
* Filename:     lib_ringbuffer.h
*
* Author:       Saheblal Bagwan
* email:        bagwan@buildstorm.com
*
* Description:
*               Contains wrapper functions to implement ring-buffer.
*******************************************************************************/

#ifndef _LIB_RING_BUFFER_H_
#define _LIB_RING_BUFFER_H_

#include "stdutils.h"

typedef struct
{
    uint16_t head_u16;
    uint16_t tail_u16;
    uint16_t maxRbElements_u16;
    uint16_t elemetSize_u16;
    uint16_t writeCount_u16;
    uint16_t readCount_u16;
    uint8_t *pBuffer_u8;
} rb_st;

bool RB_init(rb_st *ps_rb, uint16_t sizeOfElement_u16, uint16_t noOfElements_u16);
void RB_free(rb_st *ps_rb);
void RB_clear(rb_st *ps_rb);
uint16_t RB_available(rb_st *ps_rb);
uint16_t RB_hasSpace(rb_st *ps_rb);
bool RB_write(rb_st *ps_rb, void *pBuffer);
bool RB_read(rb_st *ps_rb, void *pBuffer);

#endif
