//
//  CBody.h
//  WizapplyGameSDK
//
//  Created by  on 12/12/29.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#ifndef WizapplyGameSDK_CBody_h
#define WizapplyGameSDK_CBody_h

#include "CObject.h"
#include "CView.h"

typedef struct {
    short categoryBit;
    short maskBit;
} ContactFilter;

typedef struct {
    int group;
    bool isStatic;
    CSize size;
    ContactFilter filter;
} BodyType;

class CBody : public CObject
{
private:
    CView *m_pSurface;
    CVector m_moveVector;
    BodyType m_bodyType;
public:
    CBody(BodyType bodyType);
    ~CBody();
    void SetSurface(CView *pView);
    CView *GetSurface();
    CVector GetMoveVector();
    void Update();
    void SetMoveVector(CVector moveVector);
    void AddMoveVector(CVector addVector);
    void Move();
    void MoveX();
    void MoveY();
    bool IsStaticBody();
    int GetBodyGroup();
    CSize GetSize();
    CRect GetRect();
    
    CPoint position;
    float  angle;
};

#endif
