//
//  CTime.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/31.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CTime_h
#define WizapplyGameSDK_CTime_h

#include "CObject.h"

class CTime : public CObject
{
private:
    unsigned int m_counterStartTime;
    unsigned int m_counterTime;
public:
    CTime();
    ~CTime();
    
    static unsigned int GetCurrentTime();
    static void Sleep(unsigned long time);
    void StartCounter();
    void StopCounter();
    void ResetCounter();
    unsigned int GetCounterTime();
    float GetCounterRatio(float targetCounter);
};

#endif
