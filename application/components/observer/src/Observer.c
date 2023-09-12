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
#include <stddef.h>

void OBS_CreateSubject(Subject_t* pSubject) {
    pSubject->pHead     = NULL;
    pSubject->cnt       = 0;
}

void OBS_CreateObserver(Observer_t* pObserver, Observer_cb_t cb) {
    pObserver->p_next   = NULL;
    pObserver->p_prev   = NULL;
    pObserver->p_cb     = cb;
}

void OBS_Attach(Subject_t* pSubject, Observer_t* pObserver) {
    /**
     *  We always attach new observers at head of the list
     */
    pObserver->p_next       = pSubject->pHead;
    pObserver->p_prev       = NULL;             // this should be already the case but we do it for sake of consistency
    if(pSubject->pHead != NULL) {
        // list is not empty ==> change backwards pointer
        pSubject->pHead->p_prev = pObserver;
    }
        pSubject->pHead         = pObserver;
}

void OBS_Detach(Subject_t* pSubject, Observer_t* pObserver) {
    /**
     *  Detaching can take place anywhere in the list
     */
    if((pObserver->p_prev == NULL) && (pObserver->p_next == NULL)) {
        // passed observer object is not part of the list at all
        return;
    } else if (pObserver->p_prev == NULL) {
        // first element is to be detached
        pSubject->pHead = pObserver->p_next;
    } else {
        // any other element is to be detached
        pObserver->p_prev->p_next = pObserver->p_next;
    }
    pObserver->p_next = NULL;
    pObserver->p_prev = NULL;
}

void OBS_Notify(Subject_t* pSubject) {
    Observer_t* pTmp = pSubject->pHead;

    //iterate over observer list and call all the update functions
    while(pTmp != NULL) {
        if(pTmp->p_cb != NULL) {
            pTmp->p_cb();
        }
        pTmp = pTmp->p_next;
    }
}
