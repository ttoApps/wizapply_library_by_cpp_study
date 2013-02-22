//
//  CTransitionManager.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/31.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CTransitionManager_h
#define WizapplyGameSDK_CTransitionManager_h

#include "CSingleton.h"
#include "ITransition.h"
#include <vector>

class CTransitionManager : public CSingleton<CTransitionManager>
{
private:
    std::vector<ITransition *> m_pTransitions;
public:
    CTransitionManager();
    ~CTransitionManager();
    void AddTransition(ITransition *pTransition);
    void CreanUpTransition();
    void Update();
};

#define sTransitionManager (CTransitionManager::GetInstance())
#endif
