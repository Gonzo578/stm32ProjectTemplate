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

#include <cstdint>
#include "BSP_setup.h"
#include "led.h"
#include "IObserver.h"
#include "obs_example.h"
#include "fpmath.h"

mcal::DioPin		LifeLEDPin{mcal::GPIOA, mcal::IDioPin::Pin5};
Led					LifeLED{LifeLEDPin, Led::State::OFF};
ObsExampleObj_t  	OBS_DemoObj;

static void NotifyStateChange_CB(void) {
	ObsDemoState_t _state;
	TPolNum polNum = {0, 0};
	TCartNum cartNum = {FP(0.5), FP(0.5)};
	TAngle angle = 0;

	_state = OBS_GetDemoState(&OBS_DemoObj);

	if(_state == ON) {
		LifeLED.turnOn();
		FPM_vCart2Pol(&cartNum, &polNum);
		LifeLED.turnOff();
		angle = polNum.siAngle;
		if(angle < 10) {
			angle ++;
		}
	} else {
		//LifeLED.switchOff();
	}
}

int main(void)
{
	Observer_t DemoObsObj;
	
	BSP_HWSetup();

	OBS_CreateObserver(&DemoObsObj, NotifyStateChange_CB);
	OBS_CreateObserverDemo(&OBS_DemoObj);
	OBS_AttachObserver(&OBS_DemoObj, &DemoObsObj);

	for(;;) {
		(void)OBS_HandleOberverDemo(&OBS_DemoObj);		
	}

	return 0;
}
