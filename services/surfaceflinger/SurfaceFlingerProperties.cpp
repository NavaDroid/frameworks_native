/*
 * Copyright 2019 The Android Open Source Project
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

#include <android/hardware/configstore/1.0/ISurfaceFlingerConfigs.h>
#include <android/hardware/configstore/1.1/ISurfaceFlingerConfigs.h>
#include <android/hardware/configstore/1.1/types.h>
#include <configstore/Utils.h>
#include <utils/Log.h>

#include <log/log.h>
#include <cstdlib>
#include <tuple>

#include "SurfaceFlingerProperties.h"

namespace android {
namespace sysprop {
using namespace android::hardware::configstore;
using namespace android::hardware::configstore::V1_0;
using android::hardware::graphics::common::V1_2::Dataspace;
using android::hardware::graphics::common::V1_2::PixelFormat;
using android::ui::DisplayPrimaries;

// Keep logic in sync with WindowManagerService functions that query SurfaceFlinger properties.
// Consider exposing properties via ISurfaceComposer instead.
int64_t vsync_event_phase_offset_ns(int64_t defaultValue) {
    auto temp = SurfaceFlingerProperties::vsync_event_phase_offset_ns();
    if (temp.has_value()) {
        return *temp;
    }
    return getInt64<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::vsyncEventPhaseOffsetNs>(
            defaultValue);
}

int64_t vsync_sf_event_phase_offset_ns(int64_t defaultValue) {
    auto temp = SurfaceFlingerProperties::vsync_sf_event_phase_offset_ns();
    if (temp.has_value()) {
        return *temp;
    }
    return getInt64<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::vsyncSfEventPhaseOffsetNs>(
            defaultValue);
}

bool use_context_priority(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::use_context_priority();
    if (temp.has_value()) {
        return *temp;
    }
    return getBool<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::useContextPriority>(
            defaultValue);
}

int64_t max_frame_buffer_acquired_buffers(int64_t defaultValue) {
    auto temp = SurfaceFlingerProperties::max_frame_buffer_acquired_buffers();
    if (temp.has_value()) {
        return *temp;
    }
    return getInt64<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::maxFrameBufferAcquiredBuffers>(
            defaultValue);
}

int32_t max_graphics_width(int32_t defaultValue) {
    auto temp = SurfaceFlingerProperties::max_graphics_width();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

int32_t max_graphics_height(int32_t defaultValue) {
    auto temp = SurfaceFlingerProperties::max_graphics_height();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

bool has_wide_color_display(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::has_wide_color_display();
    if (temp.has_value()) {
        return *temp;
    }
    return getBool<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::hasWideColorDisplay>(
            defaultValue);
}

bool running_without_sync_framework(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::running_without_sync_framework();
    if (temp.has_value()) {
        return !(*temp);
    }
    return getBool<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::hasSyncFramework>(defaultValue);
}

bool has_HDR_display(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::has_HDR_display();
    if (temp.has_value()) {
        return *temp;
    }
    return getBool<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::hasHDRDisplay>(defaultValue);
}

int64_t present_time_offset_from_vsync_ns(int64_t defaultValue) {
    auto temp = SurfaceFlingerProperties::present_time_offset_from_vsync_ns();
    if (temp.has_value()) {
        return *temp;
    }
    return getInt64<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::presentTimeOffsetFromVSyncNs>(
            defaultValue);
}

bool force_hwc_copy_for_virtual_displays(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::force_hwc_copy_for_virtual_displays();
    if (temp.has_value()) {
        return *temp;
    }
    return getBool<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::useHwcForRGBtoYUV>(
            defaultValue);
}

int64_t max_virtual_display_dimension(int64_t defaultValue) {
    auto temp = SurfaceFlingerProperties::max_virtual_display_dimension();
    if (temp.has_value()) {
        return *temp;
    }
    return getUInt64<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::maxVirtualDisplaySize>(
            defaultValue);
}

bool use_vr_flinger(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::use_vr_flinger();
    if (temp.has_value()) {
        return *temp;
    }
    return getBool<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::useVrFlinger>(defaultValue);
}

bool start_graphics_allocator_service(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::start_graphics_allocator_service();
    if (temp.has_value()) {
        return *temp;
    }
    return getBool<ISurfaceFlingerConfigs, &ISurfaceFlingerConfigs::startGraphicsAllocatorService>(
            defaultValue);
}

SurfaceFlingerProperties::primary_display_orientation_values primary_display_orientation(
        SurfaceFlingerProperties::primary_display_orientation_values defaultValue) {
    auto temp = SurfaceFlingerProperties::primary_display_orientation();
    if (temp.has_value()) {
        return *temp;
    }
    auto configDefault = DisplayOrientation::ORIENTATION_0;
    switch (defaultValue) {
        case SurfaceFlingerProperties::primary_display_orientation_values::ORIENTATION_90:
            configDefault = DisplayOrientation::ORIENTATION_90;
            break;
        case SurfaceFlingerProperties::primary_display_orientation_values::ORIENTATION_180:
            configDefault = DisplayOrientation::ORIENTATION_180;
            break;
        case SurfaceFlingerProperties::primary_display_orientation_values::ORIENTATION_270:
            configDefault = DisplayOrientation::ORIENTATION_270;
            break;
        default:
            configDefault = DisplayOrientation::ORIENTATION_0;
            break;
    }
    DisplayOrientation result =
            getDisplayOrientation<V1_1::ISurfaceFlingerConfigs,
                                  &V1_1::ISurfaceFlingerConfigs::primaryDisplayOrientation>(
                    configDefault);
    switch (result) {
        case DisplayOrientation::ORIENTATION_90:
            return SurfaceFlingerProperties::primary_display_orientation_values::ORIENTATION_90;
        case DisplayOrientation::ORIENTATION_180:
            return SurfaceFlingerProperties::primary_display_orientation_values::ORIENTATION_180;
        case DisplayOrientation::ORIENTATION_270:
            return SurfaceFlingerProperties::primary_display_orientation_values::ORIENTATION_270;
        default:
            break;
    }
    return SurfaceFlingerProperties::primary_display_orientation_values::ORIENTATION_0;
}

int64_t default_composition_dataspace(Dataspace defaultValue) {
    auto temp = SurfaceFlingerProperties::default_composition_dataspace();
    if (temp.has_value()) {
        return *temp;
    }
    return static_cast<int64_t>(defaultValue);
}

int32_t default_composition_pixel_format(PixelFormat defaultValue) {
    auto temp = SurfaceFlingerProperties::default_composition_pixel_format();
    if (temp.has_value()) {
        return *temp;
    }
    return static_cast<int32_t>(defaultValue);
}

int64_t wcg_composition_dataspace(Dataspace defaultValue) {
    auto temp = SurfaceFlingerProperties::wcg_composition_dataspace();
    if (temp.has_value()) {
        return *temp;
    }
    return static_cast<int64_t>(defaultValue);
}

int32_t wcg_composition_pixel_format(PixelFormat defaultValue) {
    auto temp = SurfaceFlingerProperties::wcg_composition_pixel_format();
    if (temp.has_value()) {
        return *temp;
    }
    return static_cast<int32_t>(defaultValue);
}

bool refresh_rate_switching(bool defaultValue) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    auto temp = SurfaceFlingerProperties::refresh_rate_switching();
#pragma clang diagnostic pop
    if (temp.has_value()) {
        ALOGW("Using deprecated refresh_rate_switching sysprop. Value: %d", *temp);
        return *temp;
    }
    return defaultValue;
}

int32_t set_idle_timer_ms(int32_t defaultValue) {
    auto temp = SurfaceFlingerProperties::set_idle_timer_ms();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

int32_t set_touch_timer_ms(int32_t defaultValue) {
    auto temp = SurfaceFlingerProperties::set_touch_timer_ms();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

int32_t set_display_power_timer_ms(int32_t defaultValue) {
    auto temp = SurfaceFlingerProperties::set_display_power_timer_ms();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

bool use_content_detection_for_refresh_rate(bool defaultValue) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    auto smart_90_deprecated = SurfaceFlingerProperties::use_smart_90_for_video();
#pragma clang diagnostic pop
    if (smart_90_deprecated.has_value()) {
        ALOGW("Using deprecated use_smart_90_for_video sysprop. Value: %d", *smart_90_deprecated);
        return *smart_90_deprecated;
    }

    auto temp = SurfaceFlingerProperties::use_content_detection_for_refresh_rate();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

bool enable_protected_contents(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::enable_protected_contents();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

bool support_kernel_idle_timer(bool defaultValue) {
    auto temp = SurfaceFlingerProperties::support_kernel_idle_timer();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

bool enable_sdr_dimming(bool defaultValue) {
    return SurfaceFlingerProperties::enable_sdr_dimming().value_or(defaultValue);
}

int32_t display_update_imminent_timeout_ms(int32_t defaultValue) {
    auto temp = SurfaceFlingerProperties::display_update_imminent_timeout_ms();
    if (temp.has_value()) {
        return *temp;
    }
    return defaultValue;
}

#define DISPLAY_PRIMARY_SIZE 3

constexpr float kSrgbRedX = 0.4123f;
constexpr float kSrgbRedY = 0.2126f;
constexpr float kSrgbRedZ = 0.0193f;
constexpr float kSrgbGreenX = 0.3576f;
constexpr float kSrgbGreenY = 0.7152f;
constexpr float kSrgbGreenZ = 0.1192f;
constexpr float kSrgbBlueX = 0.1805f;
constexpr float kSrgbBlueY = 0.0722f;
constexpr float kSrgbBlueZ = 0.9506f;
constexpr float kSrgbWhiteX = 0.9505f;
constexpr float kSrgbWhiteY = 1.0000f;
constexpr float kSrgbWhiteZ = 1.0891f;

DisplayPrimaries getDisplayNativePrimaries() {
    auto mDisplay_primary_red = SurfaceFlingerProperties::display_primary_red();
    auto mDisplay_primary_green = SurfaceFlingerProperties::display_primary_green();
    auto mDisplay_primary_blue = SurfaceFlingerProperties::display_primary_blue();
    auto mDisplay_primary_white = SurfaceFlingerProperties::display_primary_white();
    // To avoid null point exception.
    mDisplay_primary_red.resize(DISPLAY_PRIMARY_SIZE);
    mDisplay_primary_green.resize(DISPLAY_PRIMARY_SIZE);
    mDisplay_primary_blue.resize(DISPLAY_PRIMARY_SIZE);
    mDisplay_primary_white.resize(DISPLAY_PRIMARY_SIZE);
    DisplayPrimaries primaries =
            {{static_cast<float>(mDisplay_primary_red[0].value_or(kSrgbRedX)),
              static_cast<float>(mDisplay_primary_red[1].value_or(kSrgbRedY)),
              static_cast<float>(mDisplay_primary_red[2].value_or(kSrgbRedZ))},
             {static_cast<float>(mDisplay_primary_green[0].value_or(kSrgbGreenX)),
              static_cast<float>(mDisplay_primary_green[1].value_or(kSrgbGreenY)),
              static_cast<float>(mDisplay_primary_green[2].value_or(kSrgbGreenZ))},
             {static_cast<float>(mDisplay_primary_blue[0].value_or(kSrgbBlueX)),
              static_cast<float>(mDisplay_primary_blue[1].value_or(kSrgbBlueY)),
              static_cast<float>(mDisplay_primary_blue[2].value_or(kSrgbBlueZ))},
             {static_cast<float>(mDisplay_primary_white[0].value_or(kSrgbWhiteX)),
              static_cast<float>(mDisplay_primary_white[1].value_or(kSrgbWhiteY)),
              static_cast<float>(mDisplay_primary_white[2].value_or(kSrgbWhiteZ))}};

    return primaries;
}

bool update_device_product_info_on_hotplug_reconnect(bool defaultValue) {
    return SurfaceFlingerProperties::update_device_product_info_on_hotplug_reconnect().value_or(
            defaultValue);
}

bool enable_frame_rate_override(bool defaultValue) {
    return SurfaceFlingerProperties::enable_frame_rate_override().value_or(defaultValue);
}

bool enable_layer_caching(bool defaultValue) {
    return SurfaceFlingerProperties::enable_layer_caching().value_or(defaultValue);
}

bool ignore_hdr_camera_layers(bool defaultValue) {
    return SurfaceFlingerProperties::ignore_hdr_camera_layers().value_or(defaultValue);
}

bool clear_slots_with_set_layer_buffer(bool defaultValue) {
    return SurfaceFlingerProperties::clear_slots_with_set_layer_buffer().value_or(defaultValue);
}

int32_t game_default_frame_rate_override(int32_t defaultValue) {
    return SurfaceFlingerProperties::game_default_frame_rate_override().value_or(defaultValue);
}

} // namespace sysprop
} // namespace android
