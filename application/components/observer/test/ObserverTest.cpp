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

#include "ISubject.h"
#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include <cstdint>

using testing::Test;
using testing::Eq;
using testing::IsNull;
using testing::NotNull;
using testing::TypedEq;

namespace ObserverUnitTest {
    namespace testing {

        uint32_t Observer_1_CallCnt;
        uint32_t Observer_2_CallCnt;
        uint32_t Observer_3_CallCnt;
	    class ObserverTest : public Test {
	    protected:
		    ObserverTest(){}
		    ~ObserverTest(){}
            
            Subject_t subject;
            Observer_t observer_1;
            Observer_t observer_2;
            Observer_t observer_3;

		    virtual void SetUp(){
                /*  Init subject with dummy values in order to simulate that
                    the subject might not be initialized by default */
                subject.pHead   = (Observer_t*)1234;
                subject.cnt     = 1;

                observer_1.p_next   = (Observer_t*)1234;
                observer_1.p_prev   = (Observer_t*)1234;
                observer_1.p_cb     = (Observer_cb_t)0;
                Observer_1_CallCnt  = 0;
                Observer_2_CallCnt  = 0;
                Observer_3_CallCnt  = 0;
            }

		    virtual void TearDown(){}

            static void Observer1_CB(void) {
                Observer_1_CallCnt++;
            }

            static void Observer2_CB(void) {
                Observer_2_CallCnt++;
            }
            
            static void Observer3_CB(void) {
                Observer_3_CallCnt++;
            }
	    };

        TEST_F(ObserverTest, SubjectIsNotInitializedBeforeCreation) {
		    EXPECT_THAT(subject.pHead, NotNull());
            EXPECT_THAT(subject.cnt, Eq(1));
	    }

        TEST_F(ObserverTest, SubjectIsInitializedAfterCreation) {
            OBS_CreateSubject(&subject);
		    EXPECT_THAT(subject.pHead, IsNull());
            EXPECT_THAT(subject.cnt, Eq(0));
	    }

        TEST_F(ObserverTest, ObserverIsNotInitializedBeforeCreation) {
		    EXPECT_THAT(observer_1.p_next,  NotNull());
            EXPECT_THAT(observer_1.p_prev,  NotNull());
            EXPECT_THAT(observer_1.p_cb,    IsNull());
	    }

        TEST_F(ObserverTest, ObserverIsInitializedAfterCreation) {
            OBS_CreateObserver(&observer_1, (Observer_cb_t)4321);
		    EXPECT_THAT(observer_1.p_next,  IsNull());
            EXPECT_THAT(observer_1.p_prev,  IsNull());
            EXPECT_THAT(observer_1.p_cb,    NotNull());
	    }

        TEST_F(ObserverTest, AttachSingleObserver) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
		    OBS_Attach(&subject, &observer_1);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
	    }

        TEST_F(ObserverTest, AttachSingleObserverAndNotify) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
		    OBS_Attach(&subject, &observer_1);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(2));
	    }

        TEST_F(ObserverTest, AttachMultipleObservers) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
            OBS_CreateObserver(&observer_2, (Observer_cb_t)Observer2_CB);
            OBS_CreateObserver(&observer_3, (Observer_cb_t)Observer3_CB);
		    OBS_Attach(&subject, &observer_1);
            OBS_Attach(&subject, &observer_2);
            OBS_Attach(&subject, &observer_3);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(0));
	    }

        TEST_F(ObserverTest, AttachMultipleObserversAndNotify) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
            OBS_CreateObserver(&observer_2, (Observer_cb_t)Observer2_CB);
            OBS_CreateObserver(&observer_3, (Observer_cb_t)Observer3_CB);
		    OBS_Attach(&subject, &observer_1);
            OBS_Attach(&subject, &observer_2);
            OBS_Attach(&subject, &observer_3);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(0));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
	    }

        TEST_F(ObserverTest, DetachFirstObserverAndNotify) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
            OBS_CreateObserver(&observer_2, (Observer_cb_t)Observer2_CB);
            OBS_CreateObserver(&observer_3, (Observer_cb_t)Observer3_CB);
		    OBS_Attach(&subject, &observer_1);
            OBS_Attach(&subject, &observer_2);
            OBS_Attach(&subject, &observer_3);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(0));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
            OBS_Detach(&subject, &observer_3);
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(2));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(2));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
	    }

        TEST_F(ObserverTest, DetachMiddleObserverAndNotify) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
            OBS_CreateObserver(&observer_2, (Observer_cb_t)Observer2_CB);
            OBS_CreateObserver(&observer_3, (Observer_cb_t)Observer3_CB);
		    OBS_Attach(&subject, &observer_1);
            OBS_Attach(&subject, &observer_2);
            OBS_Attach(&subject, &observer_3);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(0));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
            OBS_Detach(&subject, &observer_2);
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(2));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(2));
	    }

        TEST_F(ObserverTest, DetachLastObserverAndNotify) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
            OBS_CreateObserver(&observer_2, (Observer_cb_t)Observer2_CB);
            OBS_CreateObserver(&observer_3, (Observer_cb_t)Observer3_CB);
		    OBS_Attach(&subject, &observer_1);
            OBS_Attach(&subject, &observer_2);
            OBS_Attach(&subject, &observer_3);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(0));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
            OBS_Detach(&subject, &observer_1);
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(2));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(2));
	    }

        TEST_F(ObserverTest, DetachMultipleObserversAndNotify) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
            OBS_CreateObserver(&observer_2, (Observer_cb_t)Observer2_CB);
            OBS_CreateObserver(&observer_3, (Observer_cb_t)Observer3_CB);
		    OBS_Attach(&subject, &observer_1);
            OBS_Attach(&subject, &observer_2);
            OBS_Attach(&subject, &observer_3);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(0));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
            OBS_Detach(&subject, &observer_1);
            OBS_Detach(&subject, &observer_3);
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(2));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
	    }

        TEST_F(ObserverTest, DetachAlreadyDetachedObserverAndNotify) {
            OBS_CreateSubject(&subject);
            OBS_CreateObserver(&observer_1, (Observer_cb_t)Observer1_CB);
            OBS_CreateObserver(&observer_2, (Observer_cb_t)Observer2_CB);
            OBS_CreateObserver(&observer_3, (Observer_cb_t)Observer3_CB);
		    OBS_Attach(&subject, &observer_1);
            OBS_Attach(&subject, &observer_2);
            OBS_Attach(&subject, &observer_3);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(0));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(0));
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(1));
            OBS_Detach(&subject, &observer_1);
            OBS_Detach(&subject, &observer_1);
            OBS_Notify(&subject);
            EXPECT_THAT(Observer_1_CallCnt,  Eq(1));
            EXPECT_THAT(Observer_2_CallCnt,  Eq(2));
            EXPECT_THAT(Observer_3_CallCnt,  Eq(2));
	    }

    }   // namespace testing
}   // namespace Observer
