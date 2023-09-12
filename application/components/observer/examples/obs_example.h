// MIT License

// Copyright (c) 2023 Ralf Hochhausen

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "ISubject.h"
#include "IObserver.h"

typedef enum _ObsDemoState_t {
    ON,
    OFF
}ObsDemoState_t;

typedef struct _ObsExampleObj_t {
    ObsDemoState_t  State;
    uint32_t        counter;
    Subject_t       Subject;
}ObsExampleObj_t;

void OBS_CreateObserverDemo(ObsExampleObj_t* pObj);

uint8_t OBS_HandleOberverDemo(ObsExampleObj_t* pObj);

ObsDemoState_t OBS_GetDemoState(ObsExampleObj_t* pObj);

void OBS_AttachObserver(ObsExampleObj_t* pObj, Observer_t* pObserver);

void OBS_DetachObserver(ObsExampleObj_t* pObj, Observer_t* pObserver);

#ifdef __cplusplus
}
#endif