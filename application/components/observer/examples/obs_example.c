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

#include "obs_example.h"
#include "ISubject.h"
#include <stdint.h>

void OBS_CreateObserverDemo(ObsExampleObj_t* pObj) {
    pObj->State     = ON;
    pObj->counter   = 0;
    OBS_CreateSubject(&pObj->Subject);
}

uint8_t OBS_HandleOberverDemo(ObsExampleObj_t* pObj) {
    pObj->counter++;

    if(pObj->counter >= 1000000) {
        pObj->counter = 0;

        if(pObj->State == ON) {
            pObj->State = OFF;
        } else {
            pObj->State = ON;
        }
        OBS_Notify(&pObj->Subject);
    }

    return 0;
}

ObsDemoState_t OBS_GetDemoState(ObsExampleObj_t* pObj) {
    return pObj->State;
}

void OBS_AttachObserver(ObsExampleObj_t* pObj, Observer_t* pObserver) {
    OBS_Attach(&pObj->Subject, pObserver);
}

void OBS_DetachObserver(ObsExampleObj_t* pObj, Observer_t* pObserver) {
    OBS_Detach(&pObj->Subject, pObserver);
}