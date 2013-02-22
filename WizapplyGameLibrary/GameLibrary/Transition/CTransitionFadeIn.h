//
//  CTransitionFadeIn.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/31.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CTransitionFadeIn_h
#define WizapplyGameSDK_CTransitionFadeIn_h

#include "ITransition.h"
#include "CView.h"

class CTransitionFadeIn : public ITransition
{
private:
    float m_alpha;
    float m_variationAlpha;
    void SetView(CView *pView);
    void Initialize();
public:
    CTransitionFadeIn(float duration);
    CTransitionFadeIn(float duration, ITransitionDelegate *pDelegate, int id);
    ~CTransitionFadeIn();
    void Run();
    void Update();
};

#endif
