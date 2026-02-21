/*
* DEEPCRAFT Studio 5.9.4563.0+34bdb7f4372a1120ca38a0cb02e62db5b4b78270
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 02/20/2026 16:54:10 UTC. Any changes will be lost.
* 
* Model ID  4e6d14e8-8b5b-4d2a-9c5d-61760c282217
* 
* Memory    Size                      Efficiency
* Buffers   6400 bytes (RAM)          80 %
* State     1168 bytes (RAM)          100 %
* Readonly  94800 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-3
* 
* Class Index | Symbol Label
* 0           | (unlabeled)
* 1           | Jab_R
* 2           | Sidehook_R
* 3           | Uppercut_R
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [40,6]          float      dequeue
*    window_shape = [40,6]
*    stride = 150
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [40,6]          float      dequeue
*    contextual_length_sec = 0.4
*    prediction_freq = 4
* Input Layer                    [40,6]          float      dequeue
*    shape = [40,6]
* Convolution 1D                 [20,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,6,16]
* Batch Normalization            [20,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [20,16]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [20,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,32]
* Convolution 1D                 [20,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [20,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [20,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [10,32]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Dropout                        [10,32]         float      dequeue
*    rate = 0.05
*    trainable = True
* Convolution 1D                 [10,64]         float      dequeue
*    filters = 64
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,64]
* Convolution 1D                 [10,64]         float      dequeue
*    filters = 64
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,64,64]
* Batch Normalization            [10,64]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[64]
*    beta = float[64]
*    mean = float[64]
*    variance = float[64]
* Activation                     [10,64]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [5,64]          float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Dropout                        [5,64]          float      dequeue
*    rate = 0.05
*    trainable = True
* Global average pooling 1D      [64]            float      dequeue
*    trainable = True
* Dense                          [4]             float      dequeue
*    units = 4
*    use_bias = True
*    activation = linear
*    trainable = True
*    weight = float[64,4]
*    bias = float[4]
* Activation                     [4]             float      dequeue
*    activation = softmax
*    trainable = True
* 
* Exported functions:
* 
* int IMAI_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[4].
* 
* int IMAI_enqueue(const float *restrict data_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[6].
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

#ifndef _IMAI_MODEL_H_
#define _IMAI_MODEL_H_
#ifdef _MSC_VER
#pragma once
#endif

#include <stdint.h>

typedef struct {    
    char *name;
    double TP; // True Positive or Correct Positive Prediction
    double FN; // False Negative or Incorrect Negative Prediction
    double FP; // False Positive or Incorrect Positive Prediction
    double TN; // True Negative or Correct Negative Prediction
    double TPR; // True Positive Rate or Sensitivity, Recall
    double TNR; // True Negative Rate or Specificity, Selectivity
    double PPV; // Positive Predictive Value or Precision
    double NPV; // Negative Predictive Value
    double FNR; // False Negative Rate or Miss Rate
    double FPR; // False Positive Rate or Fall-Out
    double FDR; // False Discovery Rate
    double FOR; // False Omission Rate
    double F1S; // F1 Score
} IMAI_stats;

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 94.840 %
* (F1S) F1 Score 94.820 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                1151              261              218              153
* (FN) False Negative or Incorrect Negative Prediction               37               20               20               20
* (FP) False Positive or Incorrect Positive Prediction               56               15               17                9
* (TN) True Negative or Correct Negative Prediction                 636             1584             1625             1698
* (TPR) True Positive Rate or Sensitivity, Recall               96.89 %          92.88 %          91.60 %          88.44 %
* (TNR) True Negative Rate or Specificity, Selectivity          91.91 %          99.06 %          98.96 %          99.47 %
* (PPV) Positive Predictive Value or Precision                  95.36 %          94.57 %          92.77 %          94.44 %
* (NPV) Negative Predictive Value                               94.50 %          98.75 %          98.78 %          98.84 %
* (FNR) False Negative Rate or Miss Rate                         3.11 %           7.12 %           8.40 %          11.56 %
* (FPR) False Positive Rate or Fall-Out                          8.09 %           0.94 %           1.04 %           0.53 %
* (FDR) False Discovery Rate                                     4.64 %           5.43 %           7.23 %           5.56 %
* (FOR) False Omission Rate                                      5.50 %           1.25 %           1.22 %           1.16 %
* (F1S) F1 Score                                                96.12 %          93.72 %          92.18 %          91.34 %
*/


#define IMAI_TEST_AVG_ACC 0.948404255319149 // Accuracy
#define IMAI_TEST_AVG_F1S 0.9482012480909787 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "unlabeled", TP: 1151, FN: 37, FP: 56, TN: 636, TPR: 0.9688552188552, TNR: 0.9190751445086, PPV: 0.9536039768019, NPV: 0.9450222882615, FNR: 0.0311447811447, FPR: 0.0809248554913, FDR: 0.0463960231980, FOR: 0.0549777117384, F1S: 0.9611691022964, }, \
 {name: "Jab_R", TP: 261, FN: 20, FP: 15, TN: 1584, TPR: 0.9288256227758, TNR: 0.9906191369606, PPV: 0.9456521739130, NPV: 0.9875311720698, FNR: 0.0711743772241, FPR: 0.0093808630393, FDR: 0.0543478260869, FOR: 0.0124688279301, F1S: 0.9371633752244, }, \
 {name: "Sidehook_R", TP: 218, FN: 20, FP: 17, TN: 1625, TPR: 0.9159663865546, TNR: 0.9896467722289, PPV: 0.9276595744680, NPV: 0.9878419452887, FNR: 0.0840336134453, FPR: 0.0103532277710, FDR: 0.0723404255319, FOR: 0.0121580547112, F1S: 0.9217758985200, }, \
 {name: "Uppercut_R", TP: 153, FN: 20, FP: 9, TN: 1698, TPR: 0.8843930635838, TNR: 0.9947275922671, PPV: 0.9444444444444, NPV: 0.9883585564610, FNR: 0.1156069364161, FPR: 0.0052724077328, FDR: 0.0555555555555, FOR: 0.0116414435389, F1S: 0.9134328358208, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 95.549 %
* (F1S) F1 Score 95.544 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                3937              835              853              493
* (FN) False Negative or Incorrect Negative Prediction              128               77               52               28
* (FP) False Positive or Incorrect Positive Prediction              149               36               64               36
* (TN) True Negative or Correct Negative Prediction                2189             5455             5434             5846
* (TPR) True Positive Rate or Sensitivity, Recall               96.85 %          91.56 %          94.25 %          94.63 %
* (TNR) True Negative Rate or Specificity, Selectivity          93.63 %          99.34 %          98.84 %          99.39 %
* (PPV) Positive Predictive Value or Precision                  96.35 %          95.87 %          93.02 %          93.19 %
* (NPV) Negative Predictive Value                               94.48 %          98.61 %          99.05 %          99.52 %
* (FNR) False Negative Rate or Miss Rate                         3.15 %           8.44 %           5.75 %           5.37 %
* (FPR) False Positive Rate or Fall-Out                          6.37 %           0.66 %           1.16 %           0.61 %
* (FDR) False Discovery Rate                                     3.65 %           4.13 %           6.98 %           6.81 %
* (FOR) False Omission Rate                                      5.52 %           1.39 %           0.95 %           0.48 %
* (F1S) F1 Score                                                96.60 %          93.66 %          93.63 %          93.90 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9554896142433235 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9554401717796434 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "unlabeled", TP: 3937, FN: 128, FP: 149, TN: 2189, TPR: 0.9685116851168, TNR: 0.9362703165098, PPV: 0.9635340186000, NPV: 0.9447561501942, FNR: 0.0314883148831, FPR: 0.0637296834901, FDR: 0.0364659813999, FOR: 0.0552438498057, F1S: 0.9660164397006, }, \
 {name: "Jab_R", TP: 835, FN: 77, FP: 36, TN: 5455, TPR: 0.9155701754385, TNR: 0.9934438171553, PPV: 0.9586681974741, NPV: 0.9860809833694, FNR: 0.0844298245614, FPR: 0.0065561828446, FDR: 0.0413318025258, FOR: 0.0139190166305, F1S: 0.9366236679753, }, \
 {name: "Sidehook_R", TP: 853, FN: 52, FP: 64, TN: 5434, TPR: 0.9425414364640, TNR: 0.9883594034194, PPV: 0.9302071973827, NPV: 0.9905213270142, FNR: 0.0574585635359, FPR: 0.0116405965805, FDR: 0.0697928026172, FOR: 0.0094786729857, F1S: 0.9363336992316, }, \
 {name: "Uppercut_R", TP: 493, FN: 28, FP: 36, TN: 5846, TPR: 0.9462571976967, TNR: 0.9938796327779, PPV: 0.9319470699432, NPV: 0.9952332311882, FNR: 0.0537428023032, FPR: 0.0061203672220, FDR: 0.0680529300567, FOR: 0.0047667688117, F1S: 0.9390476190476, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 94.775 %
* (F1S) F1 Score 94.789 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                1148              296              317              180
* (FN) False Negative or Incorrect Negative Prediction               52               26               20                9
* (FP) False Positive or Incorrect Positive Prediction               53               21                8               25
* (TN) True Negative or Correct Negative Prediction                 795             1705             1703             1834
* (TPR) True Positive Rate or Sensitivity, Recall               95.67 %          91.93 %          94.07 %          95.24 %
* (TNR) True Negative Rate or Specificity, Selectivity          93.75 %          98.78 %          99.53 %          98.66 %
* (PPV) Positive Predictive Value or Precision                  95.59 %          93.38 %          97.54 %          87.80 %
* (NPV) Negative Predictive Value                               93.86 %          98.50 %          98.84 %          99.51 %
* (FNR) False Negative Rate or Miss Rate                         4.33 %           8.07 %           5.93 %           4.76 %
* (FPR) False Positive Rate or Fall-Out                          6.25 %           1.22 %           0.47 %           1.34 %
* (FDR) False Discovery Rate                                     4.41 %           6.62 %           2.46 %          12.20 %
* (FOR) False Omission Rate                                      6.14 %           1.50 %           1.16 %           0.49 %
* (F1S) F1 Score                                                95.63 %          92.64 %          95.77 %          91.37 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.94775390625 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.9478879705663837 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "unlabeled", TP: 1148, FN: 52, FP: 53, TN: 795, TPR: 0.9566666666666, TNR: 0.9375, PPV: 0.9558701082431, NPV: 0.9386068476977, FNR: 0.0433333333333, FPR: 0.0625, FDR: 0.0441298917568, FOR: 0.0613931523022, F1S: 0.9562682215743, }, \
 {name: "Jab_R", TP: 296, FN: 26, FP: 21, TN: 1705, TPR: 0.9192546583850, TNR: 0.9878331402085, PPV: 0.9337539432176, NPV: 0.9849797804737, FNR: 0.0807453416149, FPR: 0.0121668597914, FDR: 0.0662460567823, FOR: 0.0150202195262, F1S: 0.9264475743348, }, \
 {name: "Sidehook_R", TP: 317, FN: 20, FP: 8, TN: 1703, TPR: 0.9406528189910, TNR: 0.9953243717124, PPV: 0.9753846153846, NPV: 0.9883923389437, FNR: 0.0593471810089, FPR: 0.0046756282875, FDR: 0.0246153846153, FOR: 0.0116076610562, F1S: 0.9577039274924, }, \
 {name: "Uppercut_R", TP: 180, FN: 9, FP: 25, TN: 1834, TPR: 0.9523809523809, TNR: 0.9865519096288, PPV: 0.8780487804878, NPV: 0.9951166576234, FNR: 0.0476190476190, FPR: 0.0134480903711, FDR: 0.1219512195121, FOR: 0.0048833423765, F1S: 0.9137055837563, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"(unlabeled)", "Jab_R", "Sidehook_R", "Uppercut_R"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0xe8, 0x14, 0x6d, 0x4e, 0x5b, 0x8b, 0x2a, 0x4d, 0x9c, 0x5d, 0x61, 0x76, 0x0c, 0x28, 0x22, 0x17}

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

// data_in [6] (24 bytes)
#define IMAI_DATA_IN_COUNT (6)
#define IMAI_DATA_IN_TYPE float
#define IMAI_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_IN_SCALE (1)
#define IMAI_DATA_IN_OFFSET (0)
#define IMAI_DATA_IN_IS_QUANTIZED (0)

// data_out [4] (16 bytes)
#define IMAI_DATA_OUT_COUNT (4)
#define IMAI_DATA_OUT_TYPE float
#define IMAI_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_OUT_SCALE (1)
#define IMAI_DATA_OUT_OFFSET (0)
#define IMAI_DATA_OUT_IS_QUANTIZED (0)

#define IMAI_KEY_MAX (39)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out);
int IMAI_enqueue(const float *restrict data_in);
void IMAI_init(void);

#endif /* _IMAI_MODEL_H_ */
