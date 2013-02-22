//
//  CKeyboard.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CKeyboard_h
#define WizapplyGameSDK_CKeyboard_h

#include "CSingleton.h"

class CKeyboard : public CSingleton<CKeyboard>
{
public:
    bool IsOnKey(unsigned char keyCode);
    void DebugKeyCode();
};

#define sKeyboard (CKeyboard::GetInstance())
#endif
