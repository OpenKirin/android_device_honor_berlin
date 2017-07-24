/*
 * Copyright (C) 2017 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "HI3650 PowerHAL"

#define STATE_ON "state=1"

#define KERNEL_HMP_PATH "/sys/kernel/hmp/"

#define CPUFREQ_PATH0 "/sys/devices/system/cpu/cpu0/cpufreq/"
#define CPUFREQ_PATH1 "/sys/devices/system/cpu/cpu4/cpufreq/"

#define INTERACTIVE_PATH "/sys/devices/system/cpu/cpu0/cpufreq/interactive/"

#define ONDEMAND_PATH "/sys/devices/system/cpu/cpu4/cpufreq/ondemand/"

#define TAP_TO_WAKE_NODE "/sys/touchscreen/easy_wakeup_gesture"
#define TAP_TO_WAKE_UP "/sys/touchscreen/wakeup_gesture_enable"

#define VID_ENC_TIMER_RATE 30000
#define VID_ENC_IO_IS_BUSY 0

enum {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE,
    PROFILE_MAX
};

typedef struct governor_settings {
    char *above_hispeed_delay;
    int boost;
    int boostpulse_duration;
    int boostpulse_min_interval;
    int go_hispeed_load;
    int go_hispeed_load_off;
    int hispeed_freq;
    int hispeed_freq_off;
    int io_is_busy;
    int min_sample_time;
    char *target_loads;
    char *target_loads_off;
    int timer_rate;
    int timer_rate_off;
    int timer_slack;
    // freq.
    unsigned long scaling_max_freq;
    unsigned long scaling_min_freq;
    // hmp
    int down_threshold;
    int up_threshold;
    int task_fork_on_bigcluster;
    // ondemand
    int sampling_down_factor;
    int ondemand_up_threshold;
} power_profile;

static power_profile profiles0[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .above_hispeed_delay = "20000",
        .boost = 0,
        .boostpulse_duration = 80000,
        .boostpulse_min_interval = 500000,
        .go_hispeed_load = 99,
        .go_hispeed_load_off = 110,
        .hispeed_freq = 1306000,
        .hispeed_freq_off = 1306000,
        .io_is_busy = 0,
        .min_sample_time = 80000,
        .target_loads = "90",
        .target_loads_off = "95 1306000:99",
        .timer_rate = 20000,
        .timer_rate_off = 50000,
        .timer_slack = 80000,
        .scaling_max_freq = 1709000,
        .scaling_min_freq = 480000,
	.down_threshold = 512,
	.up_threshold = 1024,
	.task_fork_on_bigcluster = 0,
    },
    [PROFILE_BALANCED] = {
        .above_hispeed_delay = "20000",
        .boost = 0,
        .boostpulse_duration = 100000,
        .boostpulse_min_interval = 500000,
        .go_hispeed_load = 95,
        .go_hispeed_load_off = 110,
        .hispeed_freq = 1306000,
        .hispeed_freq_off = 1306000,
        .io_is_busy = 1,
        .min_sample_time = 80000,
        .target_loads = "75 807000:90 1306000:95",
        .target_loads_off = "95 1306000:99",
        .timer_rate = 20000,
        .timer_rate_off = 50000,
        .timer_slack = 80000,
        .scaling_max_freq = 1709000,
        .scaling_min_freq = 480000,
	.down_threshold = 384,
	.up_threshold = 700,
	.task_fork_on_bigcluster = 1,
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .above_hispeed_delay = "20000",
        .boost = 1,
        .boostpulse_duration = 100000,
        .boostpulse_min_interval = 500000,
        .go_hispeed_load = 90,
        .go_hispeed_load_off = 110,
        .hispeed_freq = 1306000,
        .hispeed_freq_off = 1306000,
        .io_is_busy = 1,
        .min_sample_time = 80000,
        .target_loads = "75 1306000:90 1709000:95",
        .target_loads_off = "95 1709000:99",
        .timer_rate = 20000,
        .timer_rate_off = 50000,
        .timer_slack = 80000,
        .scaling_max_freq = 1709000,
        .scaling_min_freq = 480000,
	.down_threshold = 256,
	.up_threshold = 665,
	.task_fork_on_bigcluster = 1,
    },
};

static power_profile profiles1[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .scaling_max_freq = 2112000,
        .scaling_min_freq = 1402000,
	.down_threshold = 512,
	.up_threshold = 1024,
	.task_fork_on_bigcluster = 0,
	.sampling_down_factor = 1,
	.ondemand_up_threshold = 99,
    },
    [PROFILE_BALANCED] = {
        .scaling_max_freq = 2112000,
        .scaling_min_freq = 1402000,
	.down_threshold = 384,
	.up_threshold = 700,
	.task_fork_on_bigcluster = 1,
	.sampling_down_factor = 7,
	.ondemand_up_threshold = 80,
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .scaling_max_freq = 2112000,
        .scaling_min_freq = 1402000,
	.down_threshold = 256,
	.up_threshold = 665,
	.task_fork_on_bigcluster = 1,
	.sampling_down_factor = 7,
	.ondemand_up_threshold = 80,
    },
};
