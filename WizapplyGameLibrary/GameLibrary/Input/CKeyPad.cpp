//
//  CKeyPad.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/25.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CKeyPad.h"

#define PAD_BUTTON_SIZE     CSize(120.0f, 120.0f)
#define PAD_UP_DOWN_SIZE    CSize(280.0f, 120.0f)
#define PAD_LEFT_RIGHT_SIZE CSize(120.0f, 280.0f)

KeyPadButton keyPadButtonMap[KEY_PAD_BUTTON_COUNT] = {
    KeyPadButton(1,  CPoint(40.0f,  340.0f), PAD_LEFT_RIGHT_SIZE, CColor::WhiteColor().SetAlpha(0.4f)),
    KeyPadButton(14, CPoint(40.0f, 340.0f), PAD_UP_DOWN_SIZE, CColor::WhiteColor().SetAlpha(0.4f)),
    KeyPadButton(3,  CPoint(200.0f, 340.0f), PAD_LEFT_RIGHT_SIZE, CColor::WhiteColor().SetAlpha(0.4f)),
    KeyPadButton(2,  CPoint(40.0f, 500.0f), PAD_UP_DOWN_SIZE, CColor::WhiteColor().SetAlpha(0.4f)),
    KeyPadButton(40, CPoint(800.0f, 420.0f), PAD_BUTTON_SIZE, CColor::RedColor().SetAlpha(0.4f)),
    KeyPadButton(38, CPoint(640.0f, 420.0f), PAD_BUTTON_SIZE, CColor::YellowColor().SetAlpha(0.4f)),
    KeyPadButton(49, CPoint(350.0f, 500.0f), PAD_BUTTON_SIZE, CColor(0.2f, 0.2f, 0.2f, 0.4f)),
    KeyPadButton(36, CPoint(490.0f, 500.0f), PAD_BUTTON_SIZE, CColor(0.2f, 0.2f, 0.2f, 0.4f)),
    KeyPadButton(53, CPoint(20.0f,   20.0f), PAD_BUTTON_SIZE, CColor(0.2f, 0.2f, 0.2f, 0.4f))
};

CKeyPad::CKeyPad()
{
    m_pView = new CView();
    m_pView->SetTouchEnabled(false);
    
    for (int i = 0; i < KEY_PAD_BUTTON_COUNT; i++) {
        m_button[i].SetKeyCode(keyPadButtonMap[i].keyCode);
        m_button[i].SetPosition(keyPadButtonMap[i].position);
        m_button[i].SetSize(keyPadButtonMap[i].size);
        m_button[i].SetColor(keyPadButtonMap[i].color);
        
        m_pView->AddSubView(&m_button[i]);
    }
}

CKeyPad::~CKeyPad()
{
    if (0 != m_pView) {
        delete m_pView;
        m_pView = 0;
    }
}

CView *CKeyPad::GetView()
{
    return m_pView;
}

bool CKeyPad::IsOn(KeyPad keyPad)
{
    return m_button[keyPad].IsOn();
}

bool CKeyPad::IsPress(KeyPad keyPad)
{
    return m_button[keyPad].IsPress();
}

bool CKeyPad::IsRelease(KeyPad keyPad)
{
    return m_button[keyPad].IsRelease();
}

bool CKeyPad::IsHold(KeyPad keyPad)
{
    return m_button[keyPad].IsHold();
}

bool CKeyPad::IsOff(KeyPad keyPad)
{
    return m_button[keyPad].IsOff();
}

int CKeyPad::GetHoldFrame(KeyPad keyPad)
{
    return m_button[keyPad].GetHoldFrame();
}
