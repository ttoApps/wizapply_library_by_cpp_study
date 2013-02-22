//
//  CContact.h
//  WizapplyGameSDK
//
//  Created by  on 12/12/31.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#ifndef WizapplyGameSDK_CContact_h
#define WizapplyGameSDK_CContact_h

#include "CObject.h"
#include "CBody.h"

class CContact : public CObject
{
private:
    CBody *m_pBodyA;
    CBody *m_pBodyB;
    bool m_isHitHorizon;
    bool m_isHitVertical;
public:
    CContact(CBody *pBodyA, CBody *pBodyB);
    ~CContact();
    CBody *GetBodyA();
    CBody *GetBodyB();
    bool IsHorizonHit();
    bool IsVerticalHit();
};

#endif
