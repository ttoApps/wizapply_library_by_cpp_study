//
//  CWorld.h
//  WizapplyGameSDK
//
//  Created by  on 12/12/29.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

// Box2dのb2worldに相当するように作る。box2dと置き換えられる様になれば理想的。

#ifndef WizapplyGameSDK_CWorld_h
#define WizapplyGameSDK_CWorld_h

#include "CObject.h"
#include "CBody.h"
#include "CContact.h"
#include <list>

typedef enum {
    DirectionVertical = 0,
    DirectionHorizon
} Direction;

class CWorld : public CObject
{
private:
    std::list<CBody *> m_showingBodies;
    void CheckContactBodies(CBody *body, Direction direction);
protected:
    CVector m_gravity;
    std::list<CBody *> m_bodies;
    std::list<CContact *> m_contactBodies;
public:
    CWorld(CVector gravity);
    CBody *CreateBody(BodyType bodyType);
    void DestroyBody(CBody *body);
    std::list<CBody *> GetBodyList();
    std::list<CContact *> GetContactBodyList();
    void Step(CRect rect);
};

#endif
