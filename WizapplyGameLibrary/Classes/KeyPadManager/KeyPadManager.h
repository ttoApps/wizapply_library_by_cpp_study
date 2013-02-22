//
//  KeyPadManager.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_KeyPadManager_h
#define WizapplyGameSDK_KeyPadManager_h

#include "CSingleton.h"
#include "CKeyPad.h"

class KeyPadManager : public CSingleton<KeyPadManager>
{
private:
    CKeyPad m_KeyPad;
public:
    CKeyPad *GetMainKeyPad();
};

#define sKeyPadManager (KeyPadManager::GetInstance())
#endif
