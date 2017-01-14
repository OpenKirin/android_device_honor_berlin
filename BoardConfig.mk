#
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := device/honor/berlin

# Architecture
TARGET_ARCH := arm64
TARGET_ARCH_VARIANT := armv8-a
TARGET_CPU_ABI := arm64-v8a
TARGET_CPU_ABI2 :=
TARGET_CPU_VARIANT := generic

TARGET_2ND_ARCH := arm
TARGET_2ND_ARCH_VARIANT := armv7-a-neon
TARGET_2ND_CPU_ABI := armeabi-v7a
TARGET_2ND_CPU_ABI2 := armeabi
TARGET_2ND_CPU_VARIANT := cortex-a15

TARGET_CPU_SMP := true
ARCH_ARM_HAVE_TLS_REGISTER := true
ARCH_ARM_HAVE_NEON := true
ARCH_ARM_HIGH_OPTIMIZATION := true
TARGET_USES_64_BIT_BINDER := true

TARGET_BOARD_PLATFORM := hi6250
BOARD_VENDOR_PLATFORM := hi6250

ENABLE_CPUSETS := true

# Assert
TARGET_OTA_ASSERT_DEVICE := hi6250,Berlin,berlin,HWBLN-H,BLN-L21,BLN-L22,BLN-L24

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := hi6250
TARGET_NO_BOOTLOADER := true
TARGET_NO_RADIOIMAGE := true

# Init
TARGET_UNIFIED_DEVICE := true
TARGET_INIT_VENDOR_LIB := libinit_hi6250
TARGET_LIBINIT_DEFINES_FILE := $(LOCAL_PATH)/init/init_berlin.cpp

# Kernel
BOARD_KERNEL_BASE := 0x00478000
BOARD_KERNEL_PAGESIZE := 2048
BOARD_KERNEL_CMDLINE := loglevel=4 coherent_pool=512K mmcparts=mmcblk0:p1(vrl),p2(vrl_backup),p6(modemnvm_factory),p10(modemnvm_backup),p11(modemnvm_img),p12(modemnvm_system),p18(modem_om),p21(modemnvm_update),p31(modem_fw) no_console_suspend page_tracker=on ate_enable=true androidboot.selinux=permissive
BOARD_MKBOOTIMG_ARGS := --kernel_offset 0x00008000 --ramdisk_offset 0x07b88000 --tags_offset 0x07588000
TARGET_PREBUILT_KERNEL := $(LOCAL_PATH)/kernel

# Partitions
BOARD_HAS_LARGE_FILESYSTEM := true
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true
BOARD_BOOTIMAGE_PARTITION_SIZE := 33554432
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 67108864
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 3758096384
BOARD_USERDATAIMAGE_PARTITION_SIZE := 25983713280
BOARD_CACHEIMAGE_PARTITION_SIZE := 268435456
BOARD_FLASH_BLOCK_SIZE := 131072

# Recovery
TARGET_RECOVERY_DEVICE_MODULES := libinit_hi6250
TARGET_RECOVERY_FSTAB := $(LOCAL_PATH)/recovery/root/fstab.hi6250

# TWRP
RECOVERY_VARIANT := twrp
TW_THEME := portrait_hdpi

RECOVERY_SDCARD_ON_DATA := true
BOARD_SUPPRESS_SECURE_ERASE := true
BOARD_SUPPRESS_EMMC_WIPE := true

TW_EXCLUDE_SUPERSU := true

TW_INPUT_BLACKLIST := "accelerometer"

TARGET_RECOVERY_PIXEL_FORMAT := BGRA_8888
RECOVERY_GRAPHICS_FORCE_USE_LINELENGTH := true
BACKLIGHT_PATH := /sys/class/leds/lcd_backlight0/brightness
TW_BRIGHTNESS_PATH := $(BACKLIGHT_PATH)
TW_CUSTOM_BATTERY_PATH := /sys/class/power_supply/Battery
