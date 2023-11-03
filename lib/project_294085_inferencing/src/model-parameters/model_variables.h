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

#ifndef _EI_CLASSIFIER_MODEL_VARIABLES_H_
#define _EI_CLASSIFIER_MODEL_VARIABLES_H_

#include <stdint.h>
#include "model_metadata.h"

#include "tflite-model/tflite_learn_82.h"
#include "edge-impulse-sdk/classifier/ei_model_types.h"
#include "edge-impulse-sdk/classifier/inferencing_engines/engines.h"

const char* ei_classifier_inferencing_categories[] = { "平伸", "招手" };

uint8_t ei_dsp_config_81_axes[] = { 0 };
const uint32_t ei_dsp_config_81_axes_size = 1;
ei_dsp_config_spectral_analysis_t ei_dsp_config_81 = {
    81, // uint32_t blockId
    4, // int implementationVersion
    1, // int length of axes
    1.0f, // float scale-axes
    1, // int input-decimation-ratio
    "none", // select filter-type
    3.0f, // float filter-cutoff
    6, // int filter-order
    "FFT", // select analysis-type
    64, // int fft-length
    3, // int spectral-peaks-count
    0.1f, // float spectral-peaks-threshold
    "0.1, 0.5, 1.0, 2.0, 5.0", // string spectral-power-edges
    true, // boolean do-log
    true, // boolean do-fft-overlap
    1, // int wavelet-level
    "db4", // select wavelet
    false // boolean extra-low-freq
};

const size_t ei_dsp_blocks_size = 1;
ei_model_dsp_t ei_dsp_blocks[ei_dsp_blocks_size] = {
    { // DSP block 81
        37,
        &extract_spectral_analysis_features,
        (void*)&ei_dsp_config_81,
        ei_dsp_config_81_axes,
        ei_dsp_config_81_axes_size
    }
};
const ei_config_tflite_graph_t ei_config_tflite_graph_82 = {
    .implementation_version = 1,
    .model = tflite_learn_82,
    .model_size = tflite_learn_82_len,
    .arena_size = tflite_learn_82_arena_size
};

const ei_learning_block_config_tflite_graph_t ei_learning_block_config_82 = {
    .implementation_version = 1,
    .block_id = 82,
    .object_detection = 0,
    .object_detection_last_layer = EI_CLASSIFIER_LAST_LAYER_UNKNOWN,
    .output_data_tensor = 0,
    .output_labels_tensor = 1,
    .output_score_tensor = 2,
    .quantized = 1,
    .compiled = 0,
    .graph_config = (void*)&ei_config_tflite_graph_82
};

const size_t ei_learning_blocks_size = 1;
const ei_learning_block_t ei_learning_blocks[ei_learning_blocks_size] = {
    {
        &run_nn_inference,
        (void*)&ei_learning_block_config_82,
        EI_CLASSIFIER_IMAGE_SCALING_NONE,
    },
};

const ei_model_performance_calibration_t ei_calibration = {
    1, /* integer version number */
    false, /* has configured performance calibration */
    (int32_t)(EI_CLASSIFIER_RAW_SAMPLE_COUNT / ((EI_CLASSIFIER_FREQUENCY > 0) ? EI_CLASSIFIER_FREQUENCY : 1)) * 1000, /* Model window */
    0.8f, /* Default threshold */
    (int32_t)(EI_CLASSIFIER_RAW_SAMPLE_COUNT / ((EI_CLASSIFIER_FREQUENCY > 0) ? EI_CLASSIFIER_FREQUENCY : 1)) * 500, /* Half of model window */
    0   /* Don't use flags */
};

const ei_impulse_t impulse_294085_11 = {
    .project_id = 294085,
    .project_owner = "devin",
    .project_name = "肌电",
    .deploy_version = 11,

    .nn_input_frame_size = 37,
    .raw_sample_count = 87,
    .raw_samples_per_frame = 1,
    .dsp_input_frame_size = 87 * 1,
    .input_width = 0,
    .input_height = 0,
    .input_frames = 0,
    .interval_ms = 40,
    .frequency = 25,
    .dsp_blocks_size = ei_dsp_blocks_size,
    .dsp_blocks = ei_dsp_blocks,
    
    .object_detection = 0,
    .object_detection_count = 0,
    .object_detection_threshold = 0,
    .object_detection_last_layer = EI_CLASSIFIER_LAST_LAYER_UNKNOWN,
    .fomo_output_size = 0,
    
    .tflite_output_features_count = 2,
    .learning_blocks_size = ei_learning_blocks_size,
    .learning_blocks = ei_learning_blocks,

    .inferencing_engine = EI_CLASSIFIER_TFLITE,

    .sensor = EI_CLASSIFIER_SENSOR_FUSION,
    .fusion_string = "Channel 1",
    .slice_size = (87/4),
    .slices_per_model_window = 4,

    .has_anomaly = 0,
    .label_count = 2,
    .calibration = ei_calibration,
    .categories = ei_classifier_inferencing_categories
};

const ei_impulse_t ei_default_impulse = impulse_294085_11;

#endif // _EI_CLASSIFIER_MODEL_METADATA_H_
