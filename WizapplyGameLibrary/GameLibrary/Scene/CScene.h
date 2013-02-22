//
//  CScene.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CScene_h
#define WizapplyGameSDK_CScene_h

#include "CObject.h"
#include "CView.h"

class CScene : public CObject
{
protected:
    CView *m_pView;
public:
    CScene();
    virtual ~CScene();
    virtual void Update();
    virtual void Draw();
};

#endif
