//
//  ISceneFactory.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/29.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_ISceneFactory_h
#define WizapplyGameSDK_ISceneFactory_h

#include "CScene.h"

class ISceneFactory
{
public:
    virtual CScene *CreateScene(int sceneId) = 0;
};

#endif
