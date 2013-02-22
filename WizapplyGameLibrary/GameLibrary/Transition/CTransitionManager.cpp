//
//  CTransitionManager.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/31.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CTransitionManager.h"

CTransitionManager::CTransitionManager()
{
    m_pTransitions.clear();
}

CTransitionManager::~CTransitionManager()
{
    std::vector<ITransition *>::iterator iterator = m_pTransitions.begin();
    while (m_pTransitions.end() != iterator) {
        iterator = m_pTransitions.erase(iterator);
    }
}

void CTransitionManager::AddTransition(ITransition *pTransition)
{
    m_pTransitions.push_back(pTransition);
}

void CTransitionManager::CreanUpTransition()
{
    std::vector<ITransition *>::iterator iterator = m_pTransitions.begin();
    while (m_pTransitions.end() != iterator) {
        if ((*iterator)->IsDeleted()) {
            ITransition *transition = (*iterator);
            iterator = m_pTransitions.erase(iterator);
            delete transition;
            transition = 0;
            continue;
        }
        iterator++;
    }
}

void CTransitionManager::Update()
{
    std::vector<ITransition *>::iterator iterator;
    for (iterator = m_pTransitions.begin(); iterator != m_pTransitions.end(); ++iterator) {
        (*iterator)->Update();
    }
    
    CreanUpTransition();
}
