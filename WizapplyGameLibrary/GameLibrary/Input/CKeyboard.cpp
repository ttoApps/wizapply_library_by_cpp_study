//
//  CKeyboard.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/25.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CKeyboard.h"

bool CKeyboard::IsOnKey(unsigned char keyCode)
{
    return (0 < wzGetKeyState(keyCode));
}

void CKeyboard::DebugKeyCode()
{
    for (int i = 0; i < 256; i++) {
        if (0 < wzGetKeyState((unsigned char)i)) {
            CLog("%d", i);
        }
    }
}
