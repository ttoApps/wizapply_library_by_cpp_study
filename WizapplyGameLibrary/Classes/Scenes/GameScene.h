//
//  GameScene.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_GameScene_h
#define WizapplyGameSDK_GameScene_h

#include "CScene.h"
#include "Stage_001.h"
#include "ITransition.h"

class GameScene : public CScene, public ITransitionDelegate
{
private:
    Stage_001 *m_pStage;
public:
    GameScene();
    ~GameScene();
    void Update();
    
    // ITransitionDelegate
    void FinishTransition(int id);
};

#endif
