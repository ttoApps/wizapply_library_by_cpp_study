//
//  CTransitionFadeIn.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/31.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CTransitionFadeIn.h"
#include "CTransitionManager.h"

void CTransitionFadeIn::Initialize()
{
    m_alpha          = 0.0f;
    m_variationAlpha = 0.0f;
    
    sTransitionManager->AddTransition(this);
}

CTransitionFadeIn::CTransitionFadeIn(float duration)
{
    Initialize();
    
    m_duration = duration;
}

CTransitionFadeIn::CTransitionFadeIn(float duration, ITransitionDelegate *pDelegate, int id)
{
    Initialize();
    
    m_duration = duration;
    SetDelegate(pDelegate);
    SetId(id);
}

CTransitionFadeIn::~CTransitionFadeIn()
{
    if (0 != m_pTime) {
        delete m_pTime;
        m_pTime = 0;
    }
}

void CTransitionFadeIn::SetView(CView *pView)
{
    m_pView = pView;
}

void CTransitionFadeIn::Run()
{
    if (0 == m_pView) {
        return;
    }
    
    m_pTime = new CTime();
    m_pTime->StartCounter();
    
    m_alpha          = m_pView->GetAlpha();
    m_variationAlpha = m_alpha / (m_duration * 1000);
    
    m_pView->SetAlpha(0.0f);
    m_isRun = true;
}

void CTransitionFadeIn::Update()
{
    if (!m_isRun) {
        return;
    }
    
    float alpha = m_variationAlpha * ((float)m_pTime->GetCounterTime());
    if (1.0f <= m_pTime->GetCounterRatio(m_duration)) {
        alpha = m_alpha;
        m_isRun = false;
        
        if (0 != m_pDelegate) {
            m_pDelegate->FinishTransition(GetId());
        }
    }
    
    m_pView->SetAlpha(alpha);
}
