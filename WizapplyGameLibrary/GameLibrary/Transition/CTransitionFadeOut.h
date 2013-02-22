//
//  CTransitionFadeOut.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/31.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CTransitionFadeOut_h
#define WizapplyGameSDK_CTransitionFadeOut_h

#include "ITransition.h"
#include "CView.h"

class CTransitionFadeOut : public ITransition
{
private:
    float m_alpha;
    float m_variationAlpha;
    void SetView(CView *pView);
    void Initialize();
public:
    CTransitionFadeOut(float duration);
    CTransitionFadeOut(float duration, ITransitionDelegate *pDelegate, int id);
    ~CTransitionFadeOut();
    void Run();
    void Update();
};

#endif
