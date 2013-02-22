//
//  CPadButton.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/25.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CPadButton.h"
#include "CKeyboard.h"

CPadButton::CPadButton()
{
    m_keyCode = NULL;
    
    SetTouchThrow(true);
}

void CPadButton::CheckState()
{
    CButton::CheckState();
    
    if (sKeyboard->IsOnKey(m_keyCode)) {
        SetState(ButtonStateHighlight);
    }
}

void CPadButton::SetKeyCode(unsigned char keyCode)
{
    m_keyCode = keyCode;
}

const char *CPadButton::GetClassName()
{
    return "CPadButton";
}
