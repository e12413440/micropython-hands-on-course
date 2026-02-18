/*
* DEEPCRAFT Studio 5.9.4563.0+34bdb7f4372a1120ca38a0cb02e62db5b4b78270
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 02/18/2026 18:14:32 UTC. Any changes will be lost.
* 
* Model ID  8802f277-fe11-4a23-b81d-bfd450837b68
* 
* Memory    Size                      Efficiency
* Buffers   19200 bytes (RAM)         100 %
* State     5008 bytes (RAM)          100 %
* Readonly  33536 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-0
* 
* Class Index | Symbol Label
* 0           | (unlabeled)
* 1           | Jab_R
* 2           | Sidehook_R
* 3           | Uppercut_R
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [200,6]         float      dequeue
*    window_shape = [200,6]
*    stride = 342
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [200,6]         float      dequeue
*    contextual_length_sec = 0.5
*    prediction_freq = 7
* Input Layer                    [200,6]         float      dequeue
*    shape = [200,6]
* Convolution 1D                 [100,12]        float      dequeue
*    filters = 12
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,6,12]
* Batch Normalization            [100,12]        float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[12]
*    beta = float[12]
*    mean = float[12]
*    variance = float[12]
* Activation                     [100,12]        float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [100,24]        float      dequeue
*    filters = 24
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,12,24]
* Convolution 1D                 [100,24]        float      dequeue
*    filters = 24
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,24,24]
* Batch Normalization            [100,24]        float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[24]
*    beta = float[24]
*    mean = float[24]
*    variance = float[24]
* Activation                     [100,24]        float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [50,24]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Convolution 1D                 [50,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,24,32]
* Convolution 1D                 [50,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [50,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [50,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [25,32]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Global average pooling 1D      [32]            float      dequeue
*    trainable = True
* Dense                          [4]             float      dequeue
*    units = 4
*    use_bias = True
*    activation = linear
*    trainable = True
*    weight = float[32,4]
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
* (ACC) Accuracy 95.536 %
* (F1S) F1 Score 95.481 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                2293              348              328              177
* (FN) False Negative or Incorrect Negative Prediction               56               33               14               44
* (FP) False Positive or Incorrect Positive Prediction               91               20               26               10
* (TN) True Negative or Correct Negative Prediction                 853             2892             2925             3062
* (TPR) True Positive Rate or Sensitivity, Recall               97.62 %          91.34 %          95.91 %          80.09 %
* (TNR) True Negative Rate or Specificity, Selectivity          90.36 %          99.31 %          99.12 %          99.67 %
* (PPV) Positive Predictive Value or Precision                  96.18 %          94.57 %          92.66 %          94.65 %
* (NPV) Negative Predictive Value                               93.84 %          98.87 %          99.52 %          98.58 %
* (FNR) False Negative Rate or Miss Rate                         2.38 %           8.66 %           4.09 %          19.91 %
* (FPR) False Positive Rate or Fall-Out                          9.64 %           0.69 %           0.88 %           0.33 %
* (FDR) False Discovery Rate                                     3.82 %           5.43 %           7.34 %           5.35 %
* (FOR) False Omission Rate                                      6.16 %           1.13 %           0.48 %           1.42 %
* (F1S) F1 Score                                                96.89 %          92.92 %          94.25 %          86.76 %
*/


#define IMAI_TEST_AVG_ACC 0.9553598542362587 // Accuracy
#define IMAI_TEST_AVG_F1S 0.954806682411962 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "unlabeled", TP: 2293, FN: 56, FP: 91, TN: 853, TPR: 0.9761600681140, TNR: 0.9036016949152, PPV: 0.9618288590604, NPV: 0.9383938393839, FNR: 0.0238399318859, FPR: 0.0963983050847, FDR: 0.0381711409395, FOR: 0.0616061606160, F1S: 0.9689414747517, }, \
 {name: "Jab_R", TP: 348, FN: 33, FP: 20, TN: 2892, TPR: 0.9133858267716, TNR: 0.9931318681318, PPV: 0.9456521739130, NPV: 0.9887179487179, FNR: 0.0866141732283, FPR: 0.0068681318681, FDR: 0.0543478260869, FOR: 0.0112820512820, F1S: 0.9292389853137, }, \
 {name: "Sidehook_R", TP: 328, FN: 14, FP: 26, TN: 2925, TPR: 0.9590643274853, TNR: 0.9911894273127, PPV: 0.9265536723163, NPV: 0.9952364749914, FNR: 0.0409356725146, FPR: 0.0088105726872, FDR: 0.0734463276836, FOR: 0.0047635250085, F1S: 0.9425287356321, }, \
 {name: "Uppercut_R", TP: 177, FN: 44, FP: 10, TN: 3062, TPR: 0.8009049773755, TNR: 0.9967447916666, PPV: 0.9465240641711, NPV: 0.9858338699291, FNR: 0.1990950226244, FPR: 0.0032552083333, FDR: 0.0534759358288, FOR: 0.0141661300708, F1S: 0.8676470588235, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 96.132 %
* (F1S) F1 Score 96.100 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                7895             1110             1211              571
* (FN) False Negative or Incorrect Negative Prediction              134              128              101               71
* (FP) False Positive or Incorrect Positive Prediction              298               71               35               30
* (TN) True Negative or Correct Negative Prediction                2894             9912             9874            10549
* (TPR) True Positive Rate or Sensitivity, Recall               98.33 %          89.66 %          92.30 %          88.94 %
* (TNR) True Negative Rate or Specificity, Selectivity          90.66 %          99.29 %          99.65 %          99.72 %
* (PPV) Positive Predictive Value or Precision                  96.36 %          93.99 %          97.19 %          95.01 %
* (NPV) Negative Predictive Value                               95.57 %          98.73 %          98.99 %          99.33 %
* (FNR) False Negative Rate or Miss Rate                         1.67 %          10.34 %           7.70 %          11.06 %
* (FPR) False Positive Rate or Fall-Out                          9.34 %           0.71 %           0.35 %           0.28 %
* (FDR) False Discovery Rate                                     3.64 %           6.01 %           2.81 %           4.99 %
* (FOR) False Omission Rate                                      4.43 %           1.27 %           1.01 %           0.67 %
* (F1S) F1 Score                                                97.34 %          91.77 %          94.68 %          91.87 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9613225202744854 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9610033787987011 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "unlabeled", TP: 7895, FN: 134, FP: 298, TN: 2894, TPR: 0.9833104994395, TNR: 0.9066416040100, PPV: 0.9636274868790, NPV: 0.9557463672391, FNR: 0.0166895005604, FPR: 0.0933583959899, FDR: 0.0363725131209, FOR: 0.0442536327608, F1S: 0.9733694982123, }, \
 {name: "Jab_R", TP: 1110, FN: 128, FP: 71, TN: 9912, TPR: 0.8966074313408, TNR: 0.9928879094460, PPV: 0.9398814563928, NPV: 0.9872509960159, FNR: 0.1033925686591, FPR: 0.0071120905539, FDR: 0.0601185436071, FOR: 0.0127490039840, F1S: 0.9177346010748, }, \
 {name: "Sidehook_R", TP: 1211, FN: 101, FP: 35, TN: 9874, TPR: 0.9230182926829, TNR: 0.9964678575032, PPV: 0.9719101123595, NPV: 0.9898746867167, FNR: 0.0769817073170, FPR: 0.0035321424967, FDR: 0.0280898876404, FOR: 0.0101253132832, F1S: 0.9468334636434, }, \
 {name: "Uppercut_R", TP: 571, FN: 71, FP: 30, TN: 10549, TPR: 0.8894080996884, TNR: 0.9971641932129, PPV: 0.9500831946755, NPV: 0.9933145009416, FNR: 0.1105919003115, FPR: 0.0028358067870, FDR: 0.0499168053244, FOR: 0.0066854990583, F1S: 0.9187449718423, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 96.154 %
* (F1S) F1 Score 96.144 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                2387              391              454              218
* (FN) False Negative or Incorrect Negative Prediction               58               37               32               11
* (FP) False Positive or Incorrect Positive Prediction               80               28               15               15
* (TN) True Negative or Correct Negative Prediction                1063             3132             3087             3344
* (TPR) True Positive Rate or Sensitivity, Recall               97.63 %          91.36 %          93.42 %          95.20 %
* (TNR) True Negative Rate or Specificity, Selectivity          93.00 %          99.11 %          99.52 %          99.55 %
* (PPV) Positive Predictive Value or Precision                  96.76 %          93.32 %          96.80 %          93.56 %
* (NPV) Negative Predictive Value                               94.83 %          98.83 %          98.97 %          99.67 %
* (FNR) False Negative Rate or Miss Rate                         2.37 %           8.64 %           6.58 %           4.80 %
* (FPR) False Positive Rate or Fall-Out                          7.00 %           0.89 %           0.48 %           0.45 %
* (FDR) False Discovery Rate                                     3.24 %           6.68 %           3.20 %           6.44 %
* (FOR) False Omission Rate                                      5.17 %           1.17 %           1.03 %           0.33 %
* (F1S) F1 Score                                                97.19 %          92.33 %          95.08 %          94.37 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.9615384615384616 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.9614431248917147 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "unlabeled", TP: 2387, FN: 58, FP: 80, TN: 1063, TPR: 0.9762781186094, TNR: 0.9300087489063, PPV: 0.9675719497365, NPV: 0.9482604817127, FNR: 0.0237218813905, FPR: 0.0699912510936, FDR: 0.0324280502634, FOR: 0.0517395182872, F1S: 0.9719055374592, }, \
 {name: "Jab_R", TP: 391, FN: 37, FP: 28, TN: 3132, TPR: 0.9135514018691, TNR: 0.9911392405063, PPV: 0.9331742243436, NPV: 0.9883243925528, FNR: 0.0864485981308, FPR: 0.0088607594936, FDR: 0.0668257756563, FOR: 0.0116756074471, F1S: 0.9232585596221, }, \
 {name: "Sidehook_R", TP: 454, FN: 32, FP: 15, TN: 3087, TPR: 0.9341563786008, TNR: 0.9951644100580, PPV: 0.9680170575692, NPV: 0.9897403013786, FNR: 0.0658436213991, FPR: 0.0048355899419, FDR: 0.0319829424307, FOR: 0.0102596986213, F1S: 0.9507853403141, }, \
 {name: "Uppercut_R", TP: 218, FN: 11, FP: 15, TN: 3344, TPR: 0.9519650655021, TNR: 0.9955343852337, PPV: 0.9356223175965, NPV: 0.9967213114754, FNR: 0.0480349344978, FPR: 0.0044656147662, FDR: 0.0643776824034, FOR: 0.0032786885245, F1S: 0.9437229437229, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"(unlabeled)", "Jab_R", "Sidehook_R", "Uppercut_R"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0x77, 0xf2, 0x02, 0x88, 0x11, 0xfe, 0x23, 0x4a, 0xb8, 0x1d, 0xbf, 0xd4, 0x50, 0x83, 0x7b, 0x68}

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
