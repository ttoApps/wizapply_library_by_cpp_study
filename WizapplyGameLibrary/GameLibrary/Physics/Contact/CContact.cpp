//
//  CContact.cpp
//  WizapplyGameSDK
//
//  Created by  on 12/12/31.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#include "CContact.h"

CContact::CContact(CBody *pBodyA, CBody *pBodyB)
{
    m_pBodyA = pBodyA;
    m_pBodyB = pBodyB;
    
    m_isHitHorizon  = false;
    m_isHitVertical = false;
}

CContact::~CContact()
{
    if (NULL != m_pBodyA) {
        delete m_pBodyA;
        m_pBodyA = NULL;
    }
    
    if (NULL != m_pBodyB) {
        delete m_pBodyB;
        m_pBodyB = NULL;
    }
}

CBody *CContact::GetBodyA()
{
    return m_pBodyA;
}

CBody *CContact::GetBodyB()
{
    return m_pBodyB;
}

bool CContact::IsHorizonHit()
{
    return m_isHitHorizon;
}

bool CContact::IsVerticalHit()
{
    return m_isHitVertical;
}
