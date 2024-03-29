/* Generated by Edge Impulse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
// Generated on: 16.10.2023 11:58:22

#include <stdio.h>
#include <stdlib.h>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#if EI_CLASSIFIER_PRINT_STATE
#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C" {
    extern void ei_printf(const char *format, ...);
}
#else
extern void ei_printf(const char *format, ...);
#endif
#endif

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#elif defined __ICCARM__
#define ALIGN(x) __attribute__((aligned(x)))
#endif

#ifndef EI_MAX_SCRATCH_BUFFER_COUNT
#ifndef CONFIG_IDF_TARGET_ESP32S3
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#else
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#endif // CONFIG_IDF_TARGET_ESP32S3
#endif // EI_MAX_SCRATCH_BUFFER_COUNT

#ifndef EI_MAX_OVERFLOW_BUFFER_COUNT
#define EI_MAX_OVERFLOW_BUFFER_COUNT 10
#endif // EI_MAX_OVERFLOW_BUFFER_COUNT

using namespace tflite;
using namespace tflite::ops;
using namespace tflite::ops::micro;

namespace {

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX) || defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
constexpr int kTensorArenaSize = 1440;
#else
constexpr int kTensorArenaSize = 416;
#endif

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) __attribute__((section(".tensor_arena")));
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  TfLiteType type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
  TfLiteQuantization quantization;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

typedef struct {
  TfLiteTensor tensor;
  int16_t index;
} TfLiteTensorWithIndex;

typedef struct {
  TfLiteEvalTensor tensor;
  int16_t index;
} TfLiteEvalTensorWithIndex;

TfLiteContext ctx{};
static const int MAX_TFL_TENSOR_COUNT = 4;
static TfLiteTensorWithIndex tflTensors[MAX_TFL_TENSOR_COUNT];
static const int MAX_TFL_EVAL_COUNT = 4;
static TfLiteEvalTensorWithIndex tflEvalTensors[MAX_TFL_EVAL_COUNT];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[4];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,13 } };
const TfArray<1, float> quant0_scale = { 1, { 0.18874919414520264, } };
const TfArray<1, int> quant0_zero = { 1, { -109 } };
const TfLiteAffineQuantization quant0 = { (TfLiteFloatArray*)&quant0_scale, (TfLiteIntArray*)&quant0_zero, 0 };
const ALIGN(8) int32_t tensor_data1[3] = { 1007, 347, -953, };
const TfArray<1, int> tensor_dimension1 = { 1, { 3 } };
const TfArray<1, float> quant1_scale = { 1, { 0.00043341249693185091, } };
const TfArray<1, int> quant1_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant1 = { (TfLiteFloatArray*)&quant1_scale, (TfLiteIntArray*)&quant1_zero, 0 };
const ALIGN(16) int8_t tensor_data2[3*50] = { 
  40, 2, 30, -21, -6, 13, 35, -22, -58, 32, 22, -16, -13, -100, 52, -41, -127, -65, 3, -51, -108, 45, 76, 6, -25, -26, -14, -79, -49, -24, 11, -53, 10, 2, -30, -42, 12, -54, -30, 43, -17, -39, 35, 38, 31, -15, 22, 39, 39, -1, 
  42, 15, -63, -22, -47, 15, 19, -68, 12, -25, -59, 42, 29, 20, -33, 14, 14, 16, -15, 24, 21, -45, -1, -13, 44, -2, 39, 26, 2, -41, 30, -22, 62, 13, -59, -29, 40, -68, -21, -29, 3, -17, -37, -57, -39, -16, 22, -64, -16, 40, 
  -64, -2, 70, -3, -13, -36, -42, 25, 24, 17, 68, -50, -39, 20, 5, 15, 15, 12, 0, 24, 22, 43, -12, -25, -70, 31, 4, 27, 12, 27, -7, 19, -70, -2, 59, 33, -6, 59, 20, 32, 2, -17, -4, 36, 27, 4, -32, -40, 5, -65, 
};
const TfArray<2, int> tensor_dimension2 = { 2, { 3,50 } };
const TfArray<1, float> quant2_scale = { 1, { 0.010610734112560749, } };
const TfArray<1, int> quant2_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant2 = { (TfLiteFloatArray*)&quant2_scale, (TfLiteIntArray*)&quant2_zero, 0 };
const ALIGN(16) int32_t tensor_data3[50] = { 365, -34, -52, -80, 171, 182, 283, -323, -225, -105, -271, 210, -18, -419, 70, -266, -386, -116, -43, -386, -247, -27, 341, -4, 108, 0, 477, -374, -289, -172, 431, -288, 52, -31, -73, 184, 149, -337, 0, 99, -71, -128, 66, 92, 130, -143, 421, 176, 325, 1, };
const TfArray<1, int> tensor_dimension3 = { 1, { 50 } };
const TfArray<1, float> quant3_scale = { 1, { 0.00065970001742243767, } };
const TfArray<1, int> quant3_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant3 = { (TfLiteFloatArray*)&quant3_scale, (TfLiteIntArray*)&quant3_zero, 0 };
const ALIGN(16) int8_t tensor_data4[50*40] = { 
  -20, 15, 3, -14, 17, 6, 17, -23, 12, -17, -12, -22, -7, 1, -5, -51, -31, 12, -7, 5, -27, -22, 14, 6, -14, 9, 22, -1, -8, 15, -15, 8, 11, 9, 11, -7, -5, 7, -3, -8, 
  -11, -11, -10, 16, -5, 7, 17, -3, 4, 0, -19, 3, -2, 0, -19, -10, 15, -6, 3, 10, -19, -19, 0, 14, -4, -19, -11, -17, 17, 0, 3, -22, 19, 9, -5, -7, 17, -13, -9, 0, 
  28, 28, 4, -12, -16, -7, -38, 14, 15, 10, -32, -11, -9, 1, -6, 5, -8, -15, 19, -56, -8, 17, -1, 12, -4, 0, -13, -20, -17, -3, -10, -2, 7, 17, 17, 8, 15, 7, 44, -10, 
  7, 6, 14, -8, 16, -15, 12, -2, -16, 10, 9, 12, -12, -13, -16, -8, 13, 15, -10, -5, -22, 11, -18, -8, -21, -9, -8, -5, -17, -7, -7, -21, 9, 8, -1, -1, 20, -8, 14, -19, 
  -18, 18, 7, -16, -20, -14, 0, 16, -10, -17, -10, 13, 0, -19, 25, 34, -16, -18, 17, -46, -3, 23, -5, 17, -12, -26, 31, 33, -20, 12, -5, 20, -20, -1, 13, 16, -5, 16, 91, 11, 
  -13, -31, 14, -12, -26, 7, -24, 5, 12, 14, 8, -18, 22, 9, -2, 19, -16, -4, 3, -1, -23, -21, -9, -14, -16, -22, -4, -16, -11, 13, -7, 2, -3, -9, 0, 9, 15, -18, -8, 16, 
  16, 32, 6, -2, 3, 6, -24, -5, -10, -2, 8, -14, -8, 11, 24, 18, 12, 18, -20, 11, 2, 10, -15, -21, -22, 5, 28, -10, -14, -5, 4, -3, 18, -24, -16, -4, 11, -6, -22, 18, 
  22, 30, -11, 9, -2, 17, -39, -5, 17, -13, -33, -33, 4, 5, 6, -1, -3, -11, 4, -71, -4, 44, -9, 9, -1, -16, -32, -47, 4, -9, 10, -20, -10, 38, 14, 11, 0, 17, 30, -31, 
  27, 16, 15, 16, 3, -15, -11, -15, -20, 5, -1, 11, 17, -21, 18, 15, 4, -43, -9, -37, -8, -5, -7, 11, -7, 17, -26, -9, 6, 8, -18, -18, -7, 38, -20, 9, 15, -5, 23, -11, 
  -2, 12, -18, -2, 8, -13, -6, 21, 11, 13, 7, 23, 15, 8, -23, 68, 4, -23, 4, -1, -11, 34, 12, 13, -22, -5, 39, 29, 10, 13, -14, -4, 9, 15, -17, -17, -2, -15, 81, 3, 
  19, 35, 3, 0, -21, 10, -4, 1, 6, 5, -25, -4, -17, -8, 12, 19, -12, -20, -10, -59, 20, 18, -10, 0, 5, 8, -23, -13, 1, 6, -3, -6, 18, 14, -11, 10, 3, 2, 38, -36, 
  -20, -59, -6, -10, -10, -12, 6, -10, 17, 14, 15, -4, -15, 9, -10, -27, 10, 20, 4, 40, 10, -31, 3, 1, 0, -12, -24, 42, -14, -1, 13, 2, -19, -14, -6, 5, 17, 4, 0, 10, 
  -13, -27, 11, 15, 13, -7, 2, -1, -16, -19, -8, -29, -40, 19, 9, -13, -8, 27, 9, -13, 21, -11, -14, 2, -16, -8, -14, 9, 17, -2, -16, 0, -14, -38, -18, -17, -17, 15, -19, -8, 
  51, -22, 16, -5, 17, 3, 29, -7, 3, 2, -10, -32, 14, 15, 4, -10, -5, -14, -10, -17, 5, -2, 14, 13, 17, 24, -20, -13, 5, -17, 14, -10, 6, 14, 15, -1, 8, -12, -50, -1, 
  -4, -1, 8, -8, -18, -4, -4, -10, -13, -4, -3, -12, 8, -13, 1, 127, 2, 2, 18, 17, 18, 26, -5, 13, -8, 7, -30, 4, -19, 5, 17, -36, -20, 12, 14, 16, 8, -15, 37, -11, 
  43, -18, 18, -7, 16, -1, 20, -18, -7, -17, -20, -29, -1, 18, -18, -2, -12, -5, -7, 13, 12, -34, -2, 10, -9, 15, -11, -19, 10, -13, 15, 11, 1, 0, 0, 11, 16, -13, -50, 13, 
  42, -10, 18, 10, -3, -10, 21, 1, 21, 6, -18, -54, -19, 30, 10, 6, -5, -8, 0, 18, 20, -26, -18, -5, 0, 13, -7, -53, 7, 0, 2, 14, 13, 8, 17, -6, -19, -10, -82, -9, 
  17, -7, 20, 14, 11, -6, 0, -2, 12, -14, -18, 9, -8, -10, 6, -16, -22, 22, 5, 28, 15, -30, 0, -14, -14, 6, -13, -5, -7, 7, 18, -15, -1, 16, -5, 3, -6, -19, -37, -4, 
  5, -21, 1, -15, -17, 11, 20, 0, -10, 12, 20, 0, 14, 3, -2, -18, 3, 0, -2, 12, -11, 10, 9, -11, -19, 5, -19, 14, -20, -2, 5, -17, 1, -3, 17, -8, -10, -21, -17, 4, 
  35, -13, 18, -4, -19, -9, -6, 1, 11, -3, -18, -48, -13, -4, 14, 8, -3, -8, -10, -15, 4, -19, -1, 11, 22, 4, -21, -21, -6, -8, 17, 16, 7, 18, 18, 23, -5, -19, -18, 0, 
  23, -15, 19, -5, 19, 16, 1, 0, 8, 7, -16, -34, -5, 22, 16, 3, -3, -21, -11, -6, 0, -14, 19, -8, 25, 6, -32, -10, 12, 3, -12, -5, 16, 18, -11, 10, -8, -13, -57, 7, 
  21, 16, 3, 7, -17, -12, -21, 10, -1, -9, -6, 9, 10, -13, 21, 49, -5, -32, -5, -50, 4, 26, -16, 16, 22, 2, 14, 22, -11, 7, 7, 10, -3, -4, -15, -4, 0, 1, 56, -5, 
  -13, 10, -12, -17, 1, 10, -14, 5, 20, -20, 20, 7, 26, 12, 5, 21, -10, 16, 11, -1, -13, 8, 33, -14, 6, -19, 25, 10, -15, 12, -14, -3, 13, -10, -8, -11, -3, -26, 49, 18, 
  16, -8, -13, -9, -12, 3, 9, 13, 0, 16, -9, -18, 3, -7, -8, 5, 5, -11, 0, 14, -4, 5, 7, 11, 10, 0, -17, 7, -19, 3, -9, 16, 10, 2, -9, -10, -2, 6, -15, 10, 
  -29, -42, -3, 16, 16, 9, -12, -16, 22, 9, 13, -15, -46, 21, -5, -19, -16, 67, -11, 29, 5, -28, -19, -15, -9, -17, -42, 16, -2, 17, 2, 18, -6, 23, 1, -12, 11, 14, -50, -7, 
  -12, 14, -9, 11, 11, 1, 1, 6, -14, -15, -7, -3, -17, 18, 9, -11, -4, -14, 5, 3, -16, -17, -14, -3, -13, -18, 10, 0, -1, -19, -19, -10, 10, 2, 0, 17, -12, -14, 18, -17, 
  -22, -44, -12, -3, -2, 13, -8, -7, 2, 11, 12, -40, -15, 1, -3, -13, 9, 30, -13, 16, 12, -51, -2, -14, 16, 4, -9, 39, -6, -5, -4, -2, 4, -19, -20, 20, 9, -4, -18, 5, 
  26, -37, 15, 0, -6, 20, 29, 17, 13, -11, -14, -32, 7, 4, -12, -3, 13, -22, 1, 1, -3, -2, 12, -1, 24, 6, -15, -9, -9, -20, -20, 10, -10, 13, 18, 23, 6, -19, -47, 8, 
  22, -22, 0, 11, 3, -19, -5, 20, -4, 18, -9, 14, 9, 15, 9, -3, -19, -21, -1, -5, 1, 32, 12, 4, -8, -23, -7, -22, -10, 7, 10, 14, -18, 28, -13, 5, -1, -10, -2, 6, 
  -2, -9, -14, 15, -17, 1, -5, -7, -5, 18, 17, -13, 14, -2, 22, -8, 15, 16, 0, -16, 3, -11, -10, -16, -13, -2, 3, -5, 11, -15, -27, 0, -7, 18, -14, -24, -12, -15, 27, -28, 
  -16, -10, 16, -12, 0, -10, -17, 4, -1, -1, 17, -37, 10, -15, -6, -28, -12, 52, 19, 26, 7, -19, 14, 5, 7, 6, -31, 14, -18, 9, 1, 16, 4, 9, -2, -21, 16, 12, -4, -4, 
  36, -6, 1, -8, 7, -12, -17, 12, 1, 18, -9, 18, 15, 10, -2, -6, -25, -30, -8, -33, -9, 24, 10, 10, 13, -14, -16, -16, 13, -5, 4, -5, -10, 41, 8, -9, 15, 9, 45, 9, 
  6, -58, -14, -18, -19, -1, 25, -22, 17, 18, 23, -20, -11, -20, -18, -27, -3, -7, -12, 40, 3, -24, -4, 12, -20, -17, -37, -19, 12, -11, 20, 10, 11, -15, 6, 10, 0, 1, -93, -10, 
  0, -7, -18, 18, -7, -2, 14, 8, -7, -15, 3, -11, -11, -7, -3, -10, 19, -9, -14, 0, 2, 15, -6, -5, -14, 15, 17, 13, -20, 6, 13, 8, 16, -7, 17, -21, -8, -2, -6, -8, 
  -1, -16, 7, 12, -14, 11, 2, 3, -1, 18, -11, -3, 4, 19, 9, 1, -19, -34, -11, -45, -51, 2, -4, -15, 10, -20, 4, 22, 0, -25, 14, -9, 10, 53, 10, 17, 18, 15, 79, 17, 
  11, -21, 10, -12, -2, 3, -24, -1, 3, -9, 4, 2, -11, 9, 8, -24, 2, -26, 4, -20, -27, 13, -13, 10, -10, -19, 4, -21, 11, 2, 27, -13, 0, 28, 0, -16, 13, 13, 61, 15, 
  -31, -53, -10, -3, -15, -20, -5, 14, 8, -13, 15, -26, -28, -13, 0, -17, -13, 14, 18, 45, 8, -31, 3, -4, 16, -13, -9, 25, 10, 8, -19, 3, -18, -1, -2, 17, 5, 11, -44, -19, 
  27, 11, -7, 2, -8, -16, -58, 15, 1, 12, -35, -22, 6, 10, -7, 18, -33, 0, 4, -35, -10, 14, -23, 13, 37, 8, -32, -43, -15, -9, 22, -12, 7, 0, 8, 16, -20, 9, 38, -13, 
  7, -5, -18, -8, 11, 4, 2, -16, -7, 13, -18, 6, 4, 9, -4, -8, -16, -5, 17, 0, 1, 0, -14, 10, -16, -14, -8, 14, 10, -10, -15, -13, -5, -18, 8, -7, -13, -9, -2, -15, 
  -8, 22, -14, 2, -1, 6, -15, -3, -21, -3, 2, -6, 19, -21, 16, 39, -3, -19, 7, -48, 27, 20, 11, -3, 13, -13, 23, 44, 1, -16, -1, 12, -3, -33, 0, 19, 4, 20, 59, 12, 
  15, -11, 6, 3, -22, 10, 17, -14, -3, 14, -2, 9, -6, 1, 12, -12, 9, 0, 3, -18, 3, -22, 17, -16, 1, 4, 12, -21, -15, -21, -13, 10, 7, -4, 9, 10, 14, -16, -1, 9, 
  2, -24, 10, -5, 19, -8, -1, 0, -13, 8, 2, -15, 7, 7, -1, -23, -1, 6, 6, -15, -1, 9, -11, -7, 0, -11, 2, 16, 18, 18, -3, -1, 4, -2, 20, 1, 12, -5, -33, -6, 
  -17, 16, -9, -13, 11, 13, -15, 3, 13, 3, 8, 4, 1, 1, 8, -17, 9, -16, -5, -27, -9, 30, -7, -2, 21, -22, 25, 38, 12, -4, -27, -21, 10, -7, 19, 15, 1, -29, 63, -32, 
  -19, 17, -7, 15, 7, 10, 7, -5, -13, 2, -10, 9, -3, 14, -14, 48, 9, -30, 17, -50, -10, 4, 9, 23, 19, -15, 37, 7, 13, -26, 19, -6, -10, 25, -7, 2, -15, 18, 64, 7, 
  -28, 5, 0, 11, -10, -13, 3, -6, -11, 2, -1, -7, 11, -16, 16, 37, 3, -10, -8, 33, 3, 10, -11, -14, 10, 7, 28, 65, 14, 10, 5, -18, -4, 2, -17, -25, 9, 11, 124, 12, 
  -9, -9, -10, 0, -12, -12, 2, 12, -24, -3, 10, 8, 5, -5, 3, -14, -20, 9, -3, -9, -1, -9, -7, 4, 1, 10, -9, 4, -20, -4, 7, 13, 11, 4, 3, 13, -8, -20, -3, 14, 
  0, 24, -2, -5, 9, 14, -24, -20, -6, -20, -2, 18, 18, -10, -13, 9, 0, 29, 20, -2, 4, 19, -16, -9, -8, -17, 8, 6, 10, -15, 4, 6, 8, -19, 5, -6, -19, -1, 42, 19, 
  -17, 2, -17, 15, 12, -8, -56, -4, -13, -8, -28, 7, -9, 20, 2, 54, 9, -17, -7, 5, 4, 23, 17, -13, 14, 5, -14, 4, 13, 8, -14, -7, -9, -17, 14, 8, 4, 16, 19, -3, 
  -20, 14, -14, -5, 17, -8, -33, 20, 14, 15, 1, 19, -13, -5, -6, 21, 17, 0, 5, -14, 15, 6, -2, -14, 11, 19, 49, 3, -5, 3, -31, -12, 19, -5, 1, -3, -4, -18, 17, -1, 
  9, -21, 9, 13, 8, -16, -29, 12, -25, -3, 5, 14, -23, -2, 9, -9, 17, -5, 10, -32, 10, -39, 11, 2, -21, -15, -5, 19, -11, 6, -21, 9, 16, -21, 3, 3, 18, 20, -38, 23, 
};
const TfArray<2, int> tensor_dimension4 = { 2, { 50,40 } };
const TfArray<1, float> quant4_scale = { 1, { 0.012714101932942867, } };
const TfArray<1, int> quant4_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant4 = { (TfLiteFloatArray*)&quant4_scale, (TfLiteIntArray*)&quant4_zero, 0 };
const ALIGN(16) int32_t tensor_data5[40] = { -152, 166, -159, -8, 114, 0, -46, -88, -56, 0, 52, 93, -15, -16, -63, 180, 77, 99, 0, 177, 12, 12, -22, -141, -52, -89, 142, 16, -61, 40, -70, 30, 0, -57, -6, -205, 0, 91, 3, 45, };
const TfArray<1, int> tensor_dimension5 = { 1, { 40 } };
const TfArray<1, float> quant5_scale = { 1, { 0.0018175997538492084, } };
const TfArray<1, int> quant5_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant5 = { (TfLiteFloatArray*)&quant5_scale, (TfLiteIntArray*)&quant5_zero, 0 };
const ALIGN(16) int8_t tensor_data6[40*13] = { 
  5, 13, 11, 2, 5, 13, -40, -2, 4, -34, 30, 34, -36, 
  -39, 53, -7, 40, 12, 20, 23, 33, 18, 41, 5, 19, 33, 
  20, -34, 19, 19, 24, -25, -29, -11, 27, -3, 25, 22, -4, 
  -30, -17, -1, -5, 16, 26, 15, 13, -28, 10, -24, -24, 19, 
  25, -9, -24, 36, -31, -24, -7, -22, 32, 9, -12, -1, 1, 
  -10, 6, -12, 3, -13, -32, -34, 6, -31, -11, -27, -3, 25, 
  22, -63, -39, -17, -22, -25, -9, 9, -25, 36, -29, -8, -17, 
  22, 14, 23, 13, -7, 13, -18, -16, -8, -35, 30, -29, -14, 
  17, 1, -32, -23, -7, -9, 12, 3, 1, 29, 29, 48, 29, 
  -29, -29, -20, -32, -19, -30, -35, -22, -4, 24, -7, 7, 35, 
  22, 93, -29, 16, -6, -47, 16, 6, -6, 13, -37, -27, 39, 
  -12, 115, -39, 27, 15, 36, 28, -34, -21, 36, 5, 9, 6, 
  -17, 7, 21, -40, -54, 7, 9, 3, 10, 27, 37, -13, 33, 
  6, -20, 34, -12, 3, 11, 36, -4, -19, -19, -29, 8, -14, 
  24, -30, 2, -21, 10, 33, -33, -34, -23, 14, 25, -38, -47, 
  -4, -127, -118, 18, 23, 17, 0, 13, 27, 19, -33, -33, 2, 
  6, -7, 36, -23, 14, -36, 7, -7, -14, 17, -38, 1, 15, 
  4, 23, 36, -21, -7, -23, -7, -15, -18, 41, 9, -40, -43, 
  -29, 18, 17, -23, -1, -32, -30, -26, 2, -19, -17, -19, -15, 
  -9, -9, -20, 26, 44, -36, 26, 2, 2, -16, -14, 42, 41, 
  -3, 28, 21, -27, 0, -6, -24, 35, 34, -14, -15, -3, 27, 
  -5, 3, -1, 29, 55, 33, 27, -27, 26, -15, 3, -28, -16, 
  -8, -22, -15, 25, -7, 2, 13, 20, 16, 11, -36, -31, -13, 
  13, 34, 9, 38, -23, 38, 4, -17, -37, 1, 13, -15, 12, 
  2, -34, -36, -11, 12, 14, -14, 24, 37, -6, 34, -19, -15, 
  27, -6, -15, 25, -2, -20, 11, 20, 24, -4, -36, -9, -5, 
  -9, 50, -56, 23, -9, -3, 45, -18, -17, 35, 23, 5, 4, 
  -38, 29, 22, 24, 49, 20, 27, -34, -15, 32, -18, -6, 39, 
  26, -21, 14, -8, 3, 8, -15, -26, -28, -7, 3, 8, 22, 
  6, -12, 8, -11, -36, -43, -20, 13, 8, -29, 12, 32, 28, 
  6, -29, -10, 25, 16, 31, -30, -22, -10, 4, 18, 39, -9, 
  12, -19, -25, -27, 1, 8, 29, 4, -13, 5, -13, 8, 29, 
  -33, -11, -30, -34, 17, -32, 18, 26, -12, -9, 19, 22, -11, 
  -40, -50, 40, 25, 43, -3, 7, -37, -13, -19, -23, -16, -41, 
  -31, 5, -20, 11, 10, -36, 32, -15, 3, -29, 32, 24, -22, 
  24, -6, 2, -12, 7, 22, 2, 28, 11, 6, 30, 5, -14, 
  -22, -3, -8, -25, -31, -11, 17, 13, -17, -11, -20, -15, -11, 
  12, 68, -15, 48, 1, 42, 28, -27, -5, -16, -14, 22, -33, 
  -1, -16, 7, -7, -15, -6, -40, -27, -55, -6, 51, 51, 12, 
  18, -64, -6, -18, 30, 32, 7, -21, -21, 11, -42, -43, -8, 
};
const TfArray<2, int> tensor_dimension6 = { 2, { 40,13 } };
const TfArray<1, float> quant6_scale = { 1, { 0.0096297087147831917, } };
const TfArray<1, int> quant6_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant6 = { (TfLiteFloatArray*)&quant6_scale, (TfLiteIntArray*)&quant6_zero, 0 };
const TfArray<2, int> tensor_dimension7 = { 2, { 1,40 } };
const TfArray<1, float> quant7_scale = { 1, { 0.051887266337871552, } };
const TfArray<1, int> quant7_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant7 = { (TfLiteFloatArray*)&quant7_scale, (TfLiteIntArray*)&quant7_zero, 0 };
const TfArray<2, int> tensor_dimension8 = { 2, { 1,50 } };
const TfArray<1, float> quant8_scale = { 1, { 0.040846608579158783, } };
const TfArray<1, int> quant8_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant8 = { (TfLiteFloatArray*)&quant8_scale, (TfLiteIntArray*)&quant8_zero, 0 };
const TfArray<2, int> tensor_dimension9 = { 2, { 1,3 } };
const TfArray<1, float> quant9_scale = { 1, { 0.26410973072052002, } };
const TfArray<1, int> quant9_zero = { 1, { 75 } };
const TfLiteAffineQuantization quant9 = { (TfLiteFloatArray*)&quant9_scale, (TfLiteIntArray*)&quant9_zero, 0 };
const TfArray<2, int> tensor_dimension10 = { 2, { 1,3 } };
const TfArray<1, float> quant10_scale = { 1, { 0.00390625, } };
const TfArray<1, int> quant10_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant10 = { (TfLiteFloatArray*)&quant10_scale, (TfLiteIntArray*)&quant10_zero, 0 };
const TfLiteFullyConnectedParams opdata0 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs0 = { 3, { 0,6,5 } };
const TfArray<1, int> outputs0 = { 1, { 7 } };
const TfLiteFullyConnectedParams opdata1 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs1 = { 3, { 7,4,3 } };
const TfArray<1, int> outputs1 = { 1, { 8 } };
const TfLiteFullyConnectedParams opdata2 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs2 = { 3, { 8,2,1 } };
const TfArray<1, int> outputs2 = { 1, { 9 } };
const TfLiteSoftmaxParams opdata3 = { 1 };
const TfArray<1, int> inputs3 = { 1, { 9 } };
const TfArray<1, int> outputs3 = { 1, { 10 } };
const TensorInfo_t tensorData[] = {
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension0, 13, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant0))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data1, (TfLiteIntArray*)&tensor_dimension1, 12, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant1))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 150, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant2))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 200, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant3))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data4, (TfLiteIntArray*)&tensor_dimension4, 2000, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant4))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 160, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant5))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 520, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant6))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 64, (TfLiteIntArray*)&tensor_dimension7, 40, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant7))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension8, 50, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant8))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 64, (TfLiteIntArray*)&tensor_dimension9, 3, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant9))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension10, 3, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant10))}, },
};const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs3, (TfLiteIntArray*)&outputs3, const_cast<void*>(static_cast<const void*>(&opdata3)), OP_SOFTMAX, },
};

static void init_tflite_tensor(size_t i, TfLiteTensor *tensor) {
  tensor->type = tensorData[i].type;
  tensor->is_variable = 0;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  tensor->allocation_type = tensorData[i].allocation_type;
#else
  tensor->allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
  tensor->bytes = tensorData[i].bytes;
  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  if(tensor->allocation_type == kTfLiteArenaRw){
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
      tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
  tensor->quantization = tensorData[i].quantization;
  if (tensor->quantization.type == kTfLiteAffineQuantization) {
    TfLiteAffineQuantization const* quant = ((TfLiteAffineQuantization const*)(tensorData[i].quantization.params));
    tensor->params.scale = quant->scale->data[0];
    tensor->params.zero_point = quant->zero_point->data[0];
  }

}

static void init_tflite_eval_tensor(int i, TfLiteEvalTensor *tensor) {

  tensor->type = tensorData[i].type;

  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  auto allocation_type = tensorData[i].allocation_type;
  if(allocation_type == kTfLiteArenaRw) {
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
    tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
}

static void* overflow_buffers[EI_MAX_OVERFLOW_BUFFER_COUNT];
static size_t overflow_buffers_ix = 0;
static void * AllocatePersistentBufferImpl(struct TfLiteContext* ctx,
                                       size_t bytes) {
  void *ptr;
  uint32_t align_bytes = (bytes % 16) ? 16 - (bytes % 16) : 0;

  if (current_location - (bytes + align_bytes) < tensor_boundary) {
    if (overflow_buffers_ix > EI_MAX_OVERFLOW_BUFFER_COUNT - 1) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d, does not fit in tensor arena and reached EI_MAX_OVERFLOW_BUFFER_COUNT\n",
        (int)bytes);
      return NULL;
    }

    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    ptr = ei_calloc(bytes, 1);
    if (ptr == NULL) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return NULL;
    }
    overflow_buffers[overflow_buffers_ix++] = ptr;
    return ptr;
  }

  current_location -= bytes;

  // align to the left aligned boundary of 16 bytes
  current_location -= 15; // for alignment
  current_location += 16 - ((uintptr_t)(current_location) & 15);

  ptr = current_location;
  memset(ptr, 0, bytes);

  return ptr;
}
typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;
static scratch_buffer_t scratch_buffers[EI_MAX_SCRATCH_BUFFER_COUNT];
static size_t scratch_buffers_ix = 0;

static TfLiteStatus RequestScratchBufferInArenaImpl(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  if (scratch_buffers_ix > EI_MAX_SCRATCH_BUFFER_COUNT - 1) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d, reached EI_MAX_SCRATCH_BUFFER_COUNT\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffer_t b;
  b.bytes = bytes;

  b.ptr = AllocatePersistentBufferImpl(ctx, b.bytes);
  if (!b.ptr) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffers[scratch_buffers_ix] = b;
  *buffer_idx = scratch_buffers_ix;

  scratch_buffers_ix++;

  return kTfLiteOk;
}

static void* GetScratchBufferImpl(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > (int)scratch_buffers_ix) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}

static const uint16_t TENSOR_IX_UNUSED = 0x7FFF;

static void ResetTensors() {
  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    tflTensors[ix].index = TENSOR_IX_UNUSED;
  }
  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    tflEvalTensors[ix].index = TENSOR_IX_UNUSED;
  }
}

static TfLiteTensor* GetTensorImpl(const struct TfLiteContext* context,
                               int tensor_idx) {

  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    // already used? OK!
    if (tflTensors[ix].index == tensor_idx) {
      return &tflTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_tensor(tensor_idx, &tflTensors[ix].tensor);
      tflTensors[ix].index = tensor_idx;
      return &tflTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_TENSOR_COUNT (%d)\n", MAX_TFL_TENSOR_COUNT);
  return nullptr;
}

static TfLiteEvalTensor* GetEvalTensorImpl(const struct TfLiteContext* context,
                                       int tensor_idx) {

  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    // already used? OK!
    if (tflEvalTensors[ix].index == tensor_idx) {
      return &tflEvalTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflEvalTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_eval_tensor(tensor_idx, &tflEvalTensors[ix].tensor);
      tflEvalTensors[ix].index = tensor_idx;
      return &tflEvalTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_EVAL_COUNT (%d)\n", (int)MAX_TFL_EVAL_COUNT);
  return nullptr;
}

class EonMicroContext : public MicroContext {
 public:
  EonMicroContext(): MicroContext(nullptr, nullptr, nullptr) { }

  void* AllocatePersistentBuffer(size_t bytes) {
    return AllocatePersistentBufferImpl(nullptr, bytes);
  };
  TfLiteStatus RequestScratchBufferInArena(size_t bytes,
                                           int* buffer_index) {
  return RequestScratchBufferInArenaImpl(nullptr, bytes, buffer_index);
  }
  void* GetScratchBuffer(int buffer_index) {
    return GetScratchBufferImpl(nullptr, buffer_index);
  }

  TfLiteTensor* AllocateTempTfLiteTensor(int tensor_index) {
    return GetTensorImpl(nullptr, tensor_index);
  }
  void DeallocateTempTfLiteTensor(TfLiteTensor* tensor) {
    return;
  }
  bool IsAllTempTfLiteTensorDeallocated() {
    return true;
  }

  TfLiteEvalTensor* GetEvalTensor(int tensor_index) {
    return GetEvalTensorImpl(nullptr, tensor_index);
  }
};

} // namespace

TfLiteStatus tflite_learn_73_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    ei_printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#else
  memset(tensor_arena, 0, kTensorArenaSize);
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;

  EonMicroContext micro_context_;
  ctx.impl_ = static_cast<void*>(&micro_context_);
  ctx.AllocatePersistentBuffer = &AllocatePersistentBufferImpl;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArenaImpl;
  ctx.GetScratchBuffer = &GetScratchBufferImpl;
  ctx.GetTensor = &GetTensorImpl;
  ctx.GetEvalTensor = &GetEvalTensorImpl;
  ctx.tensors_size = 11;
  for (size_t i = 0; i < 11; ++i) {
    TfLiteTensor tensor;
    init_tflite_tensor(i, &tensor);
    if (tensor.allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tensor.data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }
  if (tensor_boundary > current_location /* end of arena size */) {
    ei_printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }
  registrations[OP_FULLY_CONNECTED] = Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = Register_SOFTMAX();

  for (size_t i = 0; i < 4; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
tflNodes[i].custom_initial_data = nullptr;
      tflNodes[i].custom_initial_data_size = 0;
if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for (size_t i = 0; i < 4; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      ResetTensors();

      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  0, 
};
TfLiteStatus tflite_learn_73_input(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(inTensorIndices[index], tensor);
  return kTfLiteOk;
}

static const int outTensorIndices[] = {
  10, 
};
TfLiteStatus tflite_learn_73_output(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(outTensorIndices[index], tensor);
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_73_invoke() {
  for (size_t i = 0; i < 4; ++i) {
    ResetTensors();

    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);

#if EI_CLASSIFIER_PRINT_STATE
    ei_printf("layer %lu\n", i);
    ei_printf("    inputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].inputs->size; ix++) {
      auto d = tensorData[tflNodes[i].inputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");

    ei_printf("    outputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].outputs->size; ix++) {
      auto d = tensorData[tflNodes[i].outputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");
#endif // EI_CLASSIFIER_PRINT_STATE

    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_73_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif

  // scratch buffers are allocated within the arena, so just reset the counter so memory can be reused
  scratch_buffers_ix = 0;

  // overflow buffers are on the heap, so free them first
  for (size_t ix = 0; ix < overflow_buffers_ix; ix++) {
    ei_free(overflow_buffers[ix]);
  }
  overflow_buffers_ix = 0;
  return kTfLiteOk;
}
