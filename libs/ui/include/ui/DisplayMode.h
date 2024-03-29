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

#pragma once

#include <cstdint>
#include <type_traits>

#include <ui/GraphicTypes.h>
#include <ui/Size.h>
#include <utils/Flattenable.h>
#include <utils/Timers.h>

namespace android::ui {

// This value is going to be serialized over binder so we prefer a fixed width type.
using DisplayModeId = int32_t;

// Mode supported by physical display.
struct DisplayMode {
    DisplayModeId id;
    ui::Size resolution;
    float xDpi = 0;
    float yDpi = 0;
    std::vector<ui::Hdr> supportedHdrTypes;

    // Some modes have peak refresh rate lower than the panel vsync rate.
    float peakRefreshRate = 0.f;
    float vsyncRate = 0.f;
    nsecs_t appVsyncOffset = 0;
    nsecs_t sfVsyncOffset = 0;
    nsecs_t presentationDeadline = 0;
    int32_t group = -1;
};

} // namespace android::ui
