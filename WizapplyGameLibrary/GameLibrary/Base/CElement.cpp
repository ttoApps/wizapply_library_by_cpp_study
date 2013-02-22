//
//  CElement.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/30.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CElement.h"
#include "CCollision.h"
#include "CTouch.h"

CElement::CElement()
{
    m_depth = 0;
    
    m_isTouch        = false;
    m_isTouchEnabled = true;
    m_isTouchThrow   = false;
    
    m_position = CPoint();
    m_size     = CSize();
    
    sTouch->AddElement(this);
}

CElement::~CElement()
{
    sTouch->RemoveElement(this);
}

void CElement::Touching(bool isTouching)
{
    m_isTouch = isTouching;
}

bool CElement::IsTouching()
{
    return m_isTouch;
}

void CElement::SetTouchThrow(bool isTouchThrow)
{
    m_isTouchThrow = isTouchThrow;
}

void CElement::SetPosition(CPoint position)
{
    m_position = position;
}

CPoint CElement::GetPosition()
{
    return m_position;
}

void CElement::SetSize(CSize size)
{
    m_size = size;
}

CSize CElement::GetSize()
{
    return m_size;
}

int CElement::GetDepth()
{
    return m_depth;
}

CRect CElement::GetRect()
{
    return CRect(m_position.x, m_position.y, m_position.x + m_size.width, m_position.y + m_size.height);
}

void CElement::SetTouchEnabled(bool isEnable)
{
    m_isTouchEnabled = isEnable;
}

bool CElement::IsTouchEnabled()
{
    return m_isTouchEnabled;
}

bool CElement::IsTouchThrow()
{
    return m_isTouchThrow;
}

bool CElement::PointOnRect(CPoint point)
{
    return CCollision::PointOnRect(point, GetRect());
}
