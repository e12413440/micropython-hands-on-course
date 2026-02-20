/*
* DEEPCRAFT Studio 5.9.4563.0+34bdb7f4372a1120ca38a0cb02e62db5b4b78270
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 02/20/2026 12:33:16 UTC. Any changes will be lost.
* 
* Model ID  3ad5eb51-fca3-4835-932f-05068a5af5db
* 
* Memory    Size                      Efficiency
* Buffers   13760 bytes (RAM)         80 %
* State     2248 bytes (RAM)          100 %
* Readonly  94800 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-3_1
* 
* Class Index | Symbol Label
* 0           | (unlabeled)
* 1           | Jab_R
* 2           | Sidehook_R
* 3           | Uppercut_R
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [85,6]          float      dequeue
*    window_shape = [85,6]
*    stride = 72
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [85,6]          float      dequeue
*    contextual_length_sec = 0.85
*    prediction_freq = 8
* Input Layer                    [85,6]          float      dequeue
*    shape = [85,6]
* Convolution 1D                 [43,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,6,16]
* Batch Normalization            [43,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [43,16]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [43,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,32]
* Convolution 1D                 [43,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [43,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [43,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [21,32]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Dropout                        [21,32]         float      dequeue
*    rate = 0.1
*    trainable = True
* Convolution 1D                 [21,64]         float      dequeue
*    filters = 64
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,64]
* Convolution 1D                 [21,64]         float      dequeue
*    filters = 64
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,64,64]
* Batch Normalization            [21,64]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[64]
*    beta = float[64]
*    mean = float[64]
*    variance = float[64]
* Activation                     [21,64]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [10,64]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Dropout                        [10,64]         float      dequeue
*    rate = 0.1
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
*    Parameter data_in is Input of size float[2,3].
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
* (ACC) Accuracy 95.222 %
* (F1S) F1 Score 95.268 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                3215              193              233               66
* (FN) False Negative or Incorrect Negative Prediction              123                7               16               40
* (FP) False Positive or Incorrect Positive Prediction               63               65               37               21
* (TN) True Negative or Correct Negative Prediction                 492             3628             3607             3766
* (TPR) True Positive Rate or Sensitivity, Recall               96.32 %          96.50 %          93.57 %          62.26 %
* (TNR) True Negative Rate or Specificity, Selectivity          88.65 %          98.24 %          98.98 %          99.45 %
* (PPV) Positive Predictive Value or Precision                  98.08 %          74.81 %          86.30 %          75.86 %
* (NPV) Negative Predictive Value                               80.00 %          99.81 %          99.56 %          98.95 %
* (FNR) False Negative Rate or Miss Rate                         3.68 %           3.50 %           6.43 %          37.74 %
* (FPR) False Positive Rate or Fall-Out                         11.35 %           1.76 %           1.02 %           0.55 %
* (FDR) False Discovery Rate                                     1.92 %          25.19 %          13.70 %          24.14 %
* (FOR) False Omission Rate                                     20.00 %           0.19 %           0.44 %           1.05 %
* (F1S) F1 Score                                                97.19 %          84.28 %          89.79 %          68.39 %
*/


#define IMAI_TEST_AVG_ACC 0.9522219368096584 // Accuracy
#define IMAI_TEST_AVG_F1S 0.9526805049348557 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "unlabeled", TP: 3215, FN: 123, FP: 63, TN: 492, TPR: 0.9631515877771, TNR: 0.8864864864864, PPV: 0.9807809640024, NPV: 0.8, FNR: 0.0368484122228, FPR: 0.1135135135135, FDR: 0.0192190359975, FOR: 0.2, F1S: 0.9718863361547, }, \
 {name: "Jab_R", TP: 193, FN: 7, FP: 65, TN: 3628, TPR: 0.965, TNR: 0.9823991334958, PPV: 0.7480620155038, NPV: 0.9980742778541, FNR: 0.035, FPR: 0.0176008665041, FDR: 0.2519379844961, FOR: 0.0019257221458, F1S: 0.8427947598253, }, \
 {name: "Sidehook_R", TP: 233, FN: 16, FP: 37, TN: 3607, TPR: 0.9357429718875, TNR: 0.9898463227222, PPV: 0.8629629629629, NPV: 0.9955837703560, FNR: 0.0642570281124, FPR: 0.0101536772777, FDR: 0.1370370370370, FOR: 0.0044162296439, F1S: 0.8978805394990, }, \
 {name: "Uppercut_R", TP: 66, FN: 40, FP: 21, TN: 3766, TPR: 0.6226415094339, TNR: 0.9944547134935, PPV: 0.7586206896551, NPV: 0.9894902785076, FNR: 0.3773584905660, FPR: 0.0055452865064, FDR: 0.2413793103448, FOR: 0.0105097214923, F1S: 0.6839378238341, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 96.247 %
* (F1S) F1 Score 96.354 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction               10977              685              919              217
* (FN) False Negative or Incorrect Negative Prediction              352               45               70               32
* (FP) False Positive or Incorrect Positive Prediction              147              199               75               78
* (TN) True Negative or Correct Negative Prediction                1821            12368            12233            12970
* (TPR) True Positive Rate or Sensitivity, Recall               96.89 %          93.84 %          92.92 %          87.15 %
* (TNR) True Negative Rate or Specificity, Selectivity          92.53 %          98.42 %          99.39 %          99.40 %
* (PPV) Positive Predictive Value or Precision                  98.68 %          77.49 %          92.45 %          73.56 %
* (NPV) Negative Predictive Value                               83.80 %          99.64 %          99.43 %          99.75 %
* (FNR) False Negative Rate or Miss Rate                         3.11 %           6.16 %           7.08 %          12.85 %
* (FPR) False Positive Rate or Fall-Out                          7.47 %           1.58 %           0.61 %           0.60 %
* (FDR) False Discovery Rate                                     1.32 %          22.51 %           7.55 %          26.44 %
* (FOR) False Omission Rate                                     16.20 %           0.36 %           0.57 %           0.25 %
* (F1S) F1 Score                                                97.78 %          84.88 %          92.69 %          79.78 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9624727382116267 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9635403626996911 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "unlabeled", TP: 10977, FN: 352, FP: 147, TN: 1821, TPR: 0.9689292964957, TNR: 0.9253048780487, PPV: 0.9867853290183, NPV: 0.8380119650253, FNR: 0.0310707035042, FPR: 0.0746951219512, FDR: 0.0132146709816, FOR: 0.1619880349746, F1S: 0.9777757983342, }, \
 {name: "Jab_R", TP: 685, FN: 45, FP: 199, TN: 12368, TPR: 0.9383561643835, TNR: 0.9841648762632, PPV: 0.7748868778280, NPV: 0.9963747683879, FNR: 0.0616438356164, FPR: 0.0158351237367, FDR: 0.2251131221719, FOR: 0.0036252316120, F1S: 0.8488228004956, }, \
 {name: "Sidehook_R", TP: 919, FN: 70, FP: 75, TN: 12233, TPR: 0.9292214357937, TNR: 0.9939064023399, PPV: 0.9245472837022, NPV: 0.9943103308136, FNR: 0.0707785642062, FPR: 0.0060935976600, FDR: 0.0754527162977, FOR: 0.0056896691863, F1S: 0.9268784669692, }, \
 {name: "Uppercut_R", TP: 217, FN: 32, FP: 78, TN: 12970, TPR: 0.8714859437751, TNR: 0.9940220723482, PPV: 0.7355932203389, NPV: 0.9975388401784, FNR: 0.1285140562248, FPR: 0.0059779276517, FDR: 0.2644067796610, FOR: 0.0024611598215, F1S: 0.7977941176470, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 94.979 %
* (F1S) F1 Score 95.145 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                3418              197              336               78
* (FN) False Negative or Incorrect Negative Prediction              143               25               34               11
* (FP) False Positive or Incorrect Positive Prediction               70               83               29               31
* (TN) True Negative or Correct Negative Prediction                 611             3937             3843             4122
* (TPR) True Positive Rate or Sensitivity, Recall               95.98 %          88.74 %          90.81 %          87.64 %
* (TNR) True Negative Rate or Specificity, Selectivity          89.72 %          97.94 %          99.25 %          99.25 %
* (PPV) Positive Predictive Value or Precision                  97.99 %          70.36 %          92.05 %          71.56 %
* (NPV) Negative Predictive Value                               81.03 %          99.37 %          99.12 %          99.73 %
* (FNR) False Negative Rate or Miss Rate                         4.02 %          11.26 %           9.19 %          12.36 %
* (FPR) False Positive Rate or Fall-Out                         10.28 %           2.06 %           0.75 %           0.75 %
* (FDR) False Discovery Rate                                     2.01 %          29.64 %           7.95 %          28.44 %
* (FOR) False Omission Rate                                     18.97 %           0.63 %           0.88 %           0.27 %
* (F1S) F1 Score                                                96.98 %          78.49 %          91.43 %          78.79 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.9497878359264498 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.9514481489465552 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "unlabeled", TP: 3418, FN: 143, FP: 70, TN: 611, TPR: 0.9598427408031, TNR: 0.8972099853157, PPV: 0.9799311926605, NPV: 0.8103448275862, FNR: 0.0401572591968, FPR: 0.1027900146842, FDR: 0.0200688073394, FOR: 0.1896551724137, F1S: 0.9697829479358, }, \
 {name: "Jab_R", TP: 197, FN: 25, FP: 83, TN: 3937, TPR: 0.8873873873873, TNR: 0.9793532338308, PPV: 0.7035714285714, NPV: 0.9936900555275, FNR: 0.1126126126126, FPR: 0.0206467661691, FDR: 0.2964285714285, FOR: 0.0063099444724, F1S: 0.7848605577689, }, \
 {name: "Sidehook_R", TP: 336, FN: 34, FP: 29, TN: 3843, TPR: 0.9081081081081, TNR: 0.9925103305785, PPV: 0.9205479452054, NPV: 0.9912303327314, FNR: 0.0918918918918, FPR: 0.0074896694214, FDR: 0.0794520547945, FOR: 0.0087696672685, F1S: 0.9142857142857, }, \
 {name: "Uppercut_R", TP: 78, FN: 11, FP: 31, TN: 4122, TPR: 0.8764044943820, TNR: 0.9925355164941, PPV: 0.7155963302752, NPV: 0.9973384950399, FNR: 0.1235955056179, FPR: 0.0074644835058, FDR: 0.2844036697247, FOR: 0.0026615049600, F1S: 0.7878787878787, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"(unlabeled)", "Jab_R", "Sidehook_R", "Uppercut_R"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0x51, 0xeb, 0xd5, 0x3a, 0xa3, 0xfc, 0x35, 0x48, 0x93, 0x2f, 0x05, 0x06, 0x8a, 0x5a, 0xf5, 0xdb}

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
