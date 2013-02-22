//
//  SceneFactory.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/29.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_SceneFactory_h
#define WizapplyGameSDK_SceneFactory_h

#include "CSingleton.h"
#include "ISceneFactory.h"
#include "CScene.h"

typedef enum {
    SceneID_Title,
    SceneID_Game
} SceneID;

class SceneFactory : public ISceneFactory
{
    CScene *CreateScene(int sceneId);
};

#endif
