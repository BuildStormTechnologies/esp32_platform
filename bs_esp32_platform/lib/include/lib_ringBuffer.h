/**
 * \copyright Copyright (c) 2021, Buildstorm Pvt Ltd
 *
 * \file lib_ringBuffer.h
 * \brief Rig buffer library header file.
 */

#ifndef _LIB_RING_BUFFER_H_
#define _LIB_RING_BUFFER_H_

#include "lib_utils.h"

/**
 * @brief Ring buffer structure
 */
typedef struct
{
    uint16_t head_u16;          /*!< Head pointer of ring buffer */
    uint16_t tail_u16;          /*!< Tail pointer of ring buffer */
    uint16_t maxRbElements_u16; /*!< Maximum elements in a ring buffer */
    uint16_t elemetSize_u16;    /*!< Sizef of each element */
    uint16_t writeCount_u16;    /*!< Number of elements written to ring buffer */
    uint16_t readCount_u16;     /*!< Number of elements read */
    uint8_t *pBuffer_u8;        /*!< Buffer */
} rb_st;

/**
 * @brief Intialize the ring buffer.
 * @param [in] ps_rb Instance of ring buffer
 * @param [in] sizeOfElement_u16 size of each element in ring buffer
 * @param [in] noOfElements_u16 Total number of elements in a ring buffer
 * @returns status of initialization
 * @retval true on success
 * @retval false on errors
 */
bool RB_init(rb_st *ps_rb, uint16_t sizeOfElement_u16, uint16_t noOfElements_u16);

/**
 * @brief Free the memory associated with ring buffer
 * @param [in] ps_rb Instance of ring buffer
 * @returns none
 */
void RB_free(rb_st *ps_rb);

/**
 * @brief Clear the ring buffer
 * @param [in] ps_rb Instance of ring buffer
 * @returns none
 */
void RB_clear(rb_st *ps_rb);

/**
 * @brief Number of bytes available in a ring buffer
 * @param [in] ps_rb Instance of ring buffer
 * @returns Number of bytes written in a ring buffer
 */
uint16_t RB_available(rb_st *ps_rb);

/**
 * @brief Check if ring buffer is not full
 * @param [in] ps_rb Instance of ring buffer
 * @returns Number of bytes that are remaining in ring buffer
 */
uint16_t RB_hasSpace(rb_st *ps_rb);

/**
 * @brief Write data to ring buffer
 * @param [in] ps_rb Instance of ring buffer
 * @param [in] pBuffer data to be written
 * @returns Status of write operation
 * @retval true on successful write
 * @retval false on errors
 */
bool RB_write(rb_st *ps_rb, void *pBuffer);
uint16_t RB_writeChunk(rb_st *ps_rb, void *pBuffer, uint16_t buffLen_u16);

/**
 * @brief Read data from ring buffer
 * @param [in] ps_rb Instance of ring buffer
 * @param [out] pBuffer data read from ring buffer
 * @returns status of read operation
 * @retval true on successful read
 * @retval false on errors
 */
bool RB_read(rb_st *ps_rb, void *pBuffer);
uint16_t RB_readChunk(rb_st *ps_rb, void *pBuffer, uint16_t buffLen_u16);

#endif
