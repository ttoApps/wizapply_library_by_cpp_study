//
//  CBody.cpp
//  WizapplyGameSDK
//
//  Created by  on 12/12/29.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#include "CBody.h"

CBody::CBody(BodyType bodyType)
{
    m_pSurface = 0;
    m_moveVector = CVector(0.0f, 0.0f, 0.0f);
    m_bodyType = bodyType;
    
    position = CPoint(0.0f, 0.0f);
    angle    = 0.0f;
}

CBody::~CBody()
{
}

void CBody::SetSurface(CView *pView)
{
    m_pSurface = pView;
}

CView *CBody::GetSurface()
{
    return m_pSurface;
}

CVector CBody::GetMoveVector()
{
    return m_moveVector;
}

void CBody::Update()
{
    
}

void CBody::SetMoveVector(CVector moveVector)
{
    m_moveVector = moveVector;
}

void CBody::AddMoveVector(CVector addVector)
{
    m_moveVector.x += addVector.x;
    m_moveVector.y += addVector.y;
}

void CBody::Move()
{
    position.x += m_moveVector.x;
    position.y += m_moveVector.y;
}

void CBody::MoveX()
{
    position.x += m_moveVector.x;
}

void CBody::MoveY()
{
    position.y += m_moveVector.y;
}

bool CBody::IsStaticBody()
{
    return m_bodyType.isStatic;
}

int CBody::GetBodyGroup()
{
    return m_bodyType.group;
}

CSize CBody::GetSize()
{
    return m_bodyType.size;
}

CRect CBody::GetRect()
{
    CRect rect;
    rect.left   = position.x;
    rect.top    = position.y;
    rect.right  = position.x + m_bodyType.size.width;
    rect.bottom = position.y + m_bodyType.size.height;
    
    return rect;
}
