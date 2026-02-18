/*
* DEEPCRAFT Studio 5.8.4292+50129d917517243fc033cba30ce355705c84a08c
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 02/17/2026 16:20:31 UTC. Any changes will be lost.
* 
* Memory    Size                      Efficiency
* State     6608 bytes (RAM)          100 %
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [200,6]         float      dequeue
*    window_shape = [200,6]
*    stride = 240
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [200,6]         float      dequeue
*    contextual_length_sec = 0.5
*    prediction_freq = 10
* 
* Exported functions:
* 
* int IMAI_dequeue(float *restrict data_out, float *restrict time_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[200,6].
*    Parameter time_out is Output of size float[2].
* 
* int IMAI_enqueue(const float *restrict data_in, const float *restrict time_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[2,3].
*    Parameter time_in is Input of size float[1].
* 
* void IMAI_init(void)
*    Description: Initializes buffers to initial state. This function also works as a reset function.
* 
* 
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#ifndef _IMAI_SAMPLER_H_
#define _IMAI_SAMPLER_H_
#ifdef _MSC_VER
#pragma once
#endif

#include <stdint.h>
#define IMAI_API_QUEUE_TIME

// First nibble is bit encoding, second nibble is number of bytes
#define IMAGINET_TYPES_NONE	(0x0)
#define IMAGINET_TYPES_FLOAT32	(0x14)
#define IMAGINET_TYPES_FLOAT64	(0x18)
#define IMAGINET_TYPES_INT8	(0x21)
#define IMAGINET_TYPES_INT16	(0x22)
#define IMAGINET_TYPES_INT32	(0x24)
#define IMAGINET_TYPES_INT64	(0x28)
#define IMAGINET_TYPES_QDYN8	(0x31)
#define IMAGINET_TYPES_QDYN16	(0x32)
#define IMAGINET_TYPES_QDYN32	(0x34)

// data_in [2,3] (24 bytes)
#define IMAI_DATA_IN_COUNT (6)
#define IMAI_DATA_IN_TYPE float
#define IMAI_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_IN_SCALE (1)
#define IMAI_DATA_IN_OFFSET (0)
#define IMAI_DATA_IN_IS_QUANTIZED (0)

// time_in [1] (4 bytes)
#define IMAI_TIME_IN_COUNT (1)
#define IMAI_TIME_IN_TYPE float
#define IMAI_TIME_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_TIME_IN_SCALE (1)
#define IMAI_TIME_IN_OFFSET (0)
#define IMAI_TIME_IN_IS_QUANTIZED (0)

// data_out [200,6] (4800 bytes)
#define IMAI_DATA_OUT_COUNT (1200)
#define IMAI_DATA_OUT_TYPE float
#define IMAI_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_OUT_SCALE (1)
#define IMAI_DATA_OUT_OFFSET (0)
#define IMAI_DATA_OUT_IS_QUANTIZED (0)

// time_out [2] (8 bytes)
#define IMAI_TIME_OUT_COUNT (2)
#define IMAI_TIME_OUT_TYPE float
#define IMAI_TIME_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_TIME_OUT_SCALE (1)
#define IMAI_TIME_OUT_OFFSET (0)
#define IMAI_TIME_OUT_IS_QUANTIZED (0)

#define IMAI_KEY_MAX (5)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out, float *restrict time_out);
int IMAI_enqueue(const float *restrict data_in, const float *restrict time_in);
void IMAI_init(void);

#endif /* _IMAI_SAMPLER_H_ */
