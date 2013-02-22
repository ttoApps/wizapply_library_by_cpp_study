//
//  CTime.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/31.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CTime.h"

CTime::CTime()
{
    m_counterStartTime = 0;
    m_counterTime      = 0;
}

CTime::~CTime()
{
}

unsigned int CTime::GetCurrentTime()
{
    return wzGetTime();
}

void CTime::Sleep(unsigned long time)
{
    wzSleep(time);
}

void CTime::StartCounter()
{
    m_counterStartTime = GetCurrentTime();
}

void CTime::StopCounter()
{
    m_counterTime += GetCurrentTime() - m_counterStartTime;
}

void CTime::ResetCounter()
{
    m_counterTime = 0;
}

unsigned int CTime::GetCounterTime()
{
    return m_counterTime + (GetCurrentTime() - m_counterStartTime);
}

float CTime::GetCounterRatio(float targetCounter)
{
    if (0.0f == targetCounter) {
        return 0.0f;
    }
    
    float counterTime = ((float)GetCounterTime()) / 1000.0f;
    return counterTime / targetCounter;
}