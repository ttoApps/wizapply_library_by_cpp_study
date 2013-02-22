//
//  CSceneManager.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CSceneManager_h
#define WizapplyGameSDK_CSceneManager_h

#include "CSingleton.h"
#include <stack>
#include "CScene.h"
#include "ISceneFactory.h"

class CSceneManager : public CSingleton<CSceneManager>
{
private:
    ISceneFactory *m_pSceneFactory;
    std::stack<CScene *> m_scenes;
public:
    CSceneManager();
    ~CSceneManager();
    
    void SetSceneFactory(ISceneFactory *pSceneFactory);
    void ReplaceScene(int sceneId);
    void PushScene(int sceneId);
    void PopScene();
    void Update();
    void Draw();
};


#define sSceneManager (CSceneManager::GetInstance())
#endif
