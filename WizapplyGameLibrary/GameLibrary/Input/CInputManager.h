//
//  CInputManager.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CInputManager_h
#define WizapplyGameSDK_CInputManager_h

#include "CSingleton.h"
#include "CTouch.h"
#include "CButton.h"
#include <vector>

class CInputManager : public CSingleton<CInputManager>
{
private:
    std::vector<CButton *> m_buttons;
public:
    void AddButton(CButton *pButton);
    void RemoveButton(CButton *pButton);
    void Update();
};

#define sInputManager (CInputManager::GetInstance())
#endif
