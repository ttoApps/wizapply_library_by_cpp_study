//
//  TitleScene.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_TitleScene_h
#define WizapplyGameSDK_TitleScene_h

#include "CScene.h"
#include "CButton.h"
#include "ITransition.h"

class TitleScene : public CScene, public ITransitionDelegate
{
private:
    CButton *m_pStartButton;
    void CallBackTest();
public:
    TitleScene();
    ~TitleScene();
    void Update();
    
    void FinishTransition(int id);
};

#endif
