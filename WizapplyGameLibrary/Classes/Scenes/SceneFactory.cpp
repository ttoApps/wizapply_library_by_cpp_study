//
//  SceneFactory.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/29.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "SceneFactory.h"
#include "TitleScene.h"
#include "GameScene.h"

CScene *SceneFactory::CreateScene(int sceneId)
{
    CScene *pScene = 0;
    
    switch (sceneId) {
        case SceneID_Title:
            pScene = new TitleScene();
            break;
            
        case SceneID_Game:
            pScene = new GameScene();
            break;
            
        default:
            break;
    }
    
    return pScene;
}
