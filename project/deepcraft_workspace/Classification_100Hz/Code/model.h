/*
* DEEPCRAFT Studio 5.9.4563.0+34bdb7f4372a1120ca38a0cb02e62db5b4b78270
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 02/20/2026 14:59:59 UTC. Any changes will be lost.
* 
* Model ID  f5f23cb0-b739-482b-ac95-2d1f6e6c06f3
* 
* Memory    Size                      Efficiency
* Buffers   4400 bytes (RAM)          73 %
* State     1408 bytes (RAM)          100 %
* Readonly  26512 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-1
* 
* Class Index | Symbol Label
* 0           | (unlabeled)
* 1           | Jab_R
* 2           | Sidehook_R
* 3           | Uppercut_R
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [50,6]          float      dequeue
*    window_shape = [50,6]
*    stride = 300
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [50,6]          float      dequeue
*    contextual_length_sec = 0.5
*    prediction_freq = 2
* Input Layer                    [50,6]          float      dequeue
*    shape = [50,6]
* Convolution 1D                 [25,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,6,16]
* Batch Normalization            [25,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [25,16]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [25,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,16]
* Convolution 1D                 [25,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,16]
* Batch Normalization            [25,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [25,16]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [12,16]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Dropout                        [12,16]         float      dequeue
*    rate = 0.05
*    trainable = True
* Convolution 1D                 [12,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,32]
* Convolution 1D                 [12,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [12,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [12,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [6,32]          float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Dropout                        [6,32]          float      dequeue
*    rate = 0.05
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
* (ACC) Accuracy 94.255 %
* (F1S) F1 Score 94.247 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                 515              156              120               95
* (FN) False Negative or Incorrect Negative Prediction               18               11               13               12
* (FP) False Positive or Incorrect Positive Prediction               30                7               15                2
* (TN) True Negative or Correct Negative Prediction                 377              766              792              831
* (TPR) True Positive Rate or Sensitivity, Recall               96.62 %          93.41 %          90.23 %          88.79 %
* (TNR) True Negative Rate or Specificity, Selectivity          92.63 %          99.09 %          98.14 %          99.76 %
* (PPV) Positive Predictive Value or Precision                  94.50 %          95.71 %          88.89 %          97.94 %
* (NPV) Negative Predictive Value                               95.44 %          98.58 %          98.39 %          98.58 %
* (FNR) False Negative Rate or Miss Rate                         3.38 %           6.59 %           9.77 %          11.21 %
* (FPR) False Positive Rate or Fall-Out                          7.37 %           0.91 %           1.86 %           0.24 %
* (FDR) False Discovery Rate                                     5.50 %           4.29 %          11.11 %           2.06 %
* (FOR) False Omission Rate                                      4.56 %           1.42 %           1.61 %           1.42 %
* (F1S) F1 Score                                                95.55 %          94.55 %          89.55 %          93.14 %
*/


#define IMAI_TEST_AVG_ACC 0.9425531914893617 // Accuracy
#define IMAI_TEST_AVG_F1S 0.9424674583595382 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "unlabeled", TP: 515, FN: 18, FP: 30, TN: 377, TPR: 0.9662288930581, TNR: 0.9262899262899, PPV: 0.9449541284403, NPV: 0.9544303797468, FNR: 0.0337711069418, FPR: 0.0737100737100, FDR: 0.0550458715596, FOR: 0.0455696202531, F1S: 0.9554730983302, }, \
 {name: "Jab_R", TP: 156, FN: 11, FP: 7, TN: 766, TPR: 0.9341317365269, TNR: 0.9909443725743, PPV: 0.9570552147239, NPV: 0.9858429858429, FNR: 0.0658682634730, FPR: 0.0090556274256, FDR: 0.0429447852760, FOR: 0.0141570141570, F1S: 0.9454545454545, }, \
 {name: "Sidehook_R", TP: 120, FN: 13, FP: 15, TN: 792, TPR: 0.9022556390977, TNR: 0.9814126394052, PPV: 0.8888888888888, NPV: 0.9838509316770, FNR: 0.0977443609022, FPR: 0.0185873605947, FDR: 0.1111111111111, FOR: 0.0161490683229, F1S: 0.8955223880597, }, \
 {name: "Uppercut_R", TP: 95, FN: 12, FP: 2, TN: 831, TPR: 0.8878504672897, TNR: 0.9975990396158, PPV: 0.9793814432989, NPV: 0.9857651245551, FNR: 0.1121495327102, FPR: 0.0024009603841, FDR: 0.0206185567010, FOR: 0.0142348754448, F1S: 0.9313725490196, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 96.440 %
* (F1S) F1 Score 96.428 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                1805              487              494              302
* (FN) False Negative or Incorrect Negative Prediction               42               43               18               11
* (FP) False Positive or Incorrect Positive Prediction               69               15               17               13
* (TN) True Negative or Correct Negative Prediction                1286             2657             2673             2876
* (TPR) True Positive Rate or Sensitivity, Recall               97.73 %          91.89 %          96.48 %          96.49 %
* (TNR) True Negative Rate or Specificity, Selectivity          94.91 %          99.44 %          99.37 %          99.55 %
* (PPV) Positive Predictive Value or Precision                  96.32 %          97.01 %          96.67 %          95.87 %
* (NPV) Negative Predictive Value                               96.84 %          98.41 %          99.33 %          99.62 %
* (FNR) False Negative Rate or Miss Rate                         2.27 %           8.11 %           3.52 %           3.51 %
* (FPR) False Positive Rate or Fall-Out                          5.09 %           0.56 %           0.63 %           0.45 %
* (FDR) False Discovery Rate                                     3.68 %           2.99 %           3.33 %           4.13 %
* (FOR) False Omission Rate                                      3.16 %           1.59 %           0.67 %           0.38 %
* (F1S) F1 Score                                                97.02 %          94.38 %          96.58 %          96.18 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9643972517176764 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9642838858931371 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "unlabeled", TP: 1805, FN: 42, FP: 69, TN: 1286, TPR: 0.9772604223064, TNR: 0.9490774907749, PPV: 0.9631803628601, NPV: 0.9683734939759, FNR: 0.0227395776935, FPR: 0.0509225092250, FDR: 0.0368196371398, FOR: 0.0316265060240, F1S: 0.9701693093254, }, \
 {name: "Jab_R", TP: 487, FN: 43, FP: 15, TN: 2657, TPR: 0.9188679245283, TNR: 0.9943862275449, PPV: 0.9701195219123, NPV: 0.9840740740740, FNR: 0.0811320754716, FPR: 0.0056137724550, FDR: 0.0298804780876, FOR: 0.0159259259259, F1S: 0.9437984496124, }, \
 {name: "Sidehook_R", TP: 494, FN: 18, FP: 17, TN: 2673, TPR: 0.96484375, TNR: 0.9936802973977, PPV: 0.9667318982387, NPV: 0.9933110367892, FNR: 0.03515625, FPR: 0.0063197026022, FDR: 0.0332681017612, FOR: 0.0066889632107, F1S: 0.9657869012707, }, \
 {name: "Uppercut_R", TP: 302, FN: 11, FP: 13, TN: 2876, TPR: 0.9648562300319, TNR: 0.9955001730702, PPV: 0.9587301587301, NPV: 0.9961898164184, FNR: 0.0351437699680, FPR: 0.0044998269297, FDR: 0.0412698412698, FOR: 0.0038101835815, F1S: 0.9617834394904, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 94.439 %
* (F1S) F1 Score 94.426 %
* 
* Name of class                                               unlabeled            Jab_R       Sidehook_R       Uppercut_R
* (TP) True Positive or Correct Positive Prediction                 516              171              171              110
* (FN) False Negative or Incorrect Negative Prediction               22               20                8                7
* (FP) False Positive or Incorrect Positive Prediction               31                6               12                8
* (TN) True Negative or Correct Negative Prediction                 456              828              834              900
* (TPR) True Positive Rate or Sensitivity, Recall               95.91 %          89.53 %          95.53 %          94.02 %
* (TNR) True Negative Rate or Specificity, Selectivity          93.63 %          99.28 %          98.58 %          99.12 %
* (PPV) Positive Predictive Value or Precision                  94.33 %          96.61 %          93.44 %          93.22 %
* (NPV) Negative Predictive Value                               95.40 %          97.64 %          99.05 %          99.23 %
* (FNR) False Negative Rate or Miss Rate                         4.09 %          10.47 %           4.47 %           5.98 %
* (FPR) False Positive Rate or Fall-Out                          6.37 %           0.72 %           1.42 %           0.88 %
* (FDR) False Discovery Rate                                     5.67 %           3.39 %           6.56 %           6.78 %
* (FOR) False Omission Rate                                      4.60 %           2.36 %           0.95 %           0.77 %
* (F1S) F1 Score                                                95.12 %          92.93 %          94.48 %          93.62 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.944390243902439 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.944261134226339 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "unlabeled", TP: 516, FN: 22, FP: 31, TN: 456, TPR: 0.9591078066914, TNR: 0.9363449691991, PPV: 0.9433272394881, NPV: 0.9539748953974, FNR: 0.0408921933085, FPR: 0.0636550308008, FDR: 0.0566727605118, FOR: 0.0460251046025, F1S: 0.9511520737327, }, \
 {name: "Jab_R", TP: 171, FN: 20, FP: 6, TN: 828, TPR: 0.8952879581151, TNR: 0.9928057553956, PPV: 0.9661016949152, NPV: 0.9764150943396, FNR: 0.1047120418848, FPR: 0.0071942446043, FDR: 0.0338983050847, FOR: 0.0235849056603, F1S: 0.9293478260869, }, \
 {name: "Sidehook_R", TP: 171, FN: 8, FP: 12, TN: 834, TPR: 0.9553072625698, TNR: 0.9858156028368, PPV: 0.9344262295081, NPV: 0.9904988123515, FNR: 0.0446927374301, FPR: 0.0141843971631, FDR: 0.0655737704918, FOR: 0.0095011876484, F1S: 0.9447513812154, }, \
 {name: "Uppercut_R", TP: 110, FN: 7, FP: 8, TN: 900, TPR: 0.9401709401709, TNR: 0.9911894273127, PPV: 0.9322033898305, NPV: 0.9922822491730, FNR: 0.0598290598290, FPR: 0.0088105726872, FDR: 0.0677966101694, FOR: 0.0077177508269, F1S: 0.9361702127659, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"(unlabeled)", "Jab_R", "Sidehook_R", "Uppercut_R"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0xb0, 0x3c, 0xf2, 0xf5, 0x39, 0xb7, 0x2b, 0x48, 0xac, 0x95, 0x2d, 0x1f, 0x6e, 0x6c, 0x06, 0xf3}

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
