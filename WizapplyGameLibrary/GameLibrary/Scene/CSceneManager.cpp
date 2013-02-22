//
//  CSceneManager.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CSceneManager.h"
#include "KeyPadManager.h"

CSceneManager::CSceneManager()
{
    m_pSceneFactory = 0;
}

CSceneManager::~CSceneManager()
{
    while (!m_scenes.empty()) {
        delete m_scenes.top();
        m_scenes.pop();
    }
    
    if (0 != m_pSceneFactory) {
        delete m_pSceneFactory;
    }
}

void CSceneManager::SetSceneFactory(ISceneFactory *pSceneFactory)
{
    m_pSceneFactory = pSceneFactory;
}

void CSceneManager::ReplaceScene(int sceneId)
{
    if (0 == m_pSceneFactory) {
        return;
    }
    
    CScene *scene = m_pSceneFactory->CreateScene(sceneId);
    if (0 == scene) {
        return;
    }
    
    if (m_scenes.empty()) {
        m_scenes.push(scene);
        return;
    }
    
    delete m_scenes.top();
    m_scenes.pop();
    
    m_scenes.push(scene);
}

void CSceneManager::PushScene(int sceneId)
{
    if (0 == m_pSceneFactory) {
        return;
    }
    
    CScene *scene = m_pSceneFactory->CreateScene(sceneId);
    if (0 == scene) {
        return;
    }
    
    m_scenes.push(scene);
}

void CSceneManager::PopScene()
{
    if (m_scenes.empty()) {
        return;
    }
    
    delete m_scenes.top();
    m_scenes.pop();
}

void CSceneManager::Update()
{
    if (m_scenes.empty()) {
        return;
    }
    
    m_scenes.top()->Update();
}

void CSceneManager::Draw()
{
    if (m_scenes.empty()) {
        return;
    }
    
    m_scenes.top()->Draw();
    sKeyPadManager->GetMainKeyPad()->GetView()->Draw();
}
