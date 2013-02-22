//
//  CButton.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CButton.h"
#include "CInputManager.h"
#include "CCollision.h"

CButton::CButton()
{
    m_holdFrame = 0;
    m_state          = ButtonStateNormal;
    m_oldState       = ButtonStateNormal;
    m_normalColor    = m_color;
    m_highlightColor = m_color;
    
    sInputManager->AddButton(this);
}

CButton::~CButton()
{
    sInputManager->RemoveButton(this);
}

void CButton::Update()
{
    m_oldState = m_state;
    m_state = ButtonStateNormal;
    
    CheckState();
    
    m_holdFrame = (ButtonStateHighlight == m_state) ? m_holdFrame + 1 : 0;
}

void CButton::CheckState()
{
    m_state = IsTouching() ? ButtonStateHighlight : ButtonStateNormal;
}

bool CButton::IsOn()
{
    return IsOnNowFrame();
}

bool CButton::IsPress()
{
    return (IsOnNowFrame() && !IsOnPreviousFrame());
}

bool CButton::IsRelease()
{
    return (!IsOnNowFrame() && IsOnPreviousFrame());
}

bool CButton::IsHold()
{
    return (IsOnNowFrame() && IsOnPreviousFrame());
}

bool CButton::IsOff()
{
    return (!IsOnNowFrame() && !IsOnPreviousFrame());
}

int CButton::GetHoldFrame()
{
    return m_holdFrame;
}

void CButton::SetState(ButtonState state)
{
    m_state = state;
}

void CButton::SetColor(CColor color)
{
    CView::SetColor(color);
    m_normalColor    = color;
    m_highlightColor = color;
    m_highlightColor.a += (0.5f < color.a) ? -0.4f : 0.4f;
}

void CButton::SetHighlightColor(CColor color)
{
    m_highlightColor = color;
}

void CButton::Draw()
{
    switch (m_state) {
        case ButtonStateNormal:
            m_color = m_normalColor;
            break;
            
        case ButtonStateHighlight:
            m_color = m_highlightColor;
        default:
            break;
    }
    
    CView::Draw();
}


bool CButton::IsOnPreviousFrame()
{
    return (ButtonStateHighlight == m_oldState);
}

bool CButton::IsOnNowFrame()
{
    return (ButtonStateHighlight == m_state);
}

const char *CButton::GetClassName()
{
    return "CButton";
}
