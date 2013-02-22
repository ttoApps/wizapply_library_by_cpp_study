//
//  CInputManager.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CInputManager.h"

void CInputManager::Update()
{
    sTouch->Update();
    
    std::vector<CButton *>::iterator iterator;
    for (iterator = m_buttons.begin(); iterator != m_buttons.end(); ++iterator) {
        (*iterator)->Update();
    }
}

void CInputManager::AddButton(CButton *pButton)
{
    m_buttons.push_back(pButton);
}

void CInputManager::RemoveButton(CButton *pButton)
{
    std::vector<CButton *>::iterator iterator = m_buttons.begin();
    while (m_buttons.end() != iterator) {
        if (pButton == (*iterator)) {
            iterator = m_buttons.erase(iterator);
            continue;
        }
        ++iterator;
    }
}
