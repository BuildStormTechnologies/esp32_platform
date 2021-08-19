/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File:   lib_ringbuffer.h
 * Version: 1.0
 * Author: Saheblal Bagwan
 * Description: Library module for ringbuffer implementation.
                - Supports byte, integers, structutres by taking the size as argument
                - Safe to call from interrupts.
                - RB_available() has to be called before reading any data.
                - RB_hasSpace() has to be called before writing data to ringbuffer, else it will overwrite the old data.
                

Copyright © 2021 BuildStorm Private Limited <admin@buildstorm.com>

The software is liscensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/

#ifndef _LIB_RING_BUFFER_H_
#define _LIB_RING_BUFFER_H_

#include <stdint.h>
#include <stdlib.h> //Malloc functions
#include <string.h>

typedef struct
{
	uint16_t head_u16;
	uint16_t tail_u16;
	uint16_t maxRbElements_u16;
	uint16_t elemetSize_u16;
	uint8_t *buff;
}ringBuffer_st;

uint8_t RB_init(ringBuffer_st *rb_ptr, uint16_t sizeOfElement_u16, uint16_t noOfElements_u16);
void RB_clear(ringBuffer_st *rb_ptr);
uint16_t RB_available(ringBuffer_st *rb_ptr);
uint16_t RB_hasSpace(ringBuffer_st *rb_ptr);
uint8_t RB_write(ringBuffer_st *rb_ptr, void *inPtr);
uint8_t RB_read(ringBuffer_st *rb_ptr, void *outPtr);


#endif
