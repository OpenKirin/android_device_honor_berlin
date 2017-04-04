#
# Copyright (C) 2017 OpenKirin, OldDroid
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
#

## Specify phone tech before including full_phone
$(call inherit-product, vendor/omni/config/gsm.mk)

# Inherit from the common Open Source product configuration
$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base_telephony.mk)

# Inherit some common Omni stuff.
$(call inherit-product, vendor/omni/config/common.mk)

PRODUCT_COPY_FILES += \
    bionic/libc/zoneinfo/tzdata:root/system/usr/share/zoneinfo/tzdata

PRODUCT_PACKAGES += \
    charger_res_images \
    charger

ADDITIONAL_DEFAULT_PROPERTIES += \
    ro.secure=0 \
    ro.adb.secure=0 \
    security.perf_harden=0 \
    ro.allow.mock.location=1

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    sys.usb.configfs=1 \
    sys.usb.config=mtp,adb \
    persist.sys.usb.config=manufacture,adb \
    sys.usb.controller=hisi-usb-otg

PRODUCT_NAME := omni_berlin
PRODUCT_DEVICE := berlin
PRODUCT_BRAND := Honor
PRODUCT_MODEL := HONOR-6X
PRODUCT_MANUFACTURER := HUAWEI
