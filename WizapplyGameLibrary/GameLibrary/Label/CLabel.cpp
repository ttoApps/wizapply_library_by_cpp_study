//
//  CLabel.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/02.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CLabel.h"
#include <string.h>

CLabel::CLabel()
{
    m_pText    = new char[1024];
    m_fontSize = 12;
    
    SetTouchEnabled(false);
}

CLabel::~CLabel()
{
    delete[] m_pText;
    m_pText = 0;
}

void CLabel::SetText(const char *pText)
{
    strcpy(m_pText, pText);
}

const char *CLabel::GetText()
{
    return m_pText;
}

void CLabel::SetFontSize(unsigned size)
{
    m_fontSize = size;
}

void CLabel::Draw()
{
    if (IsHidden()) {
        return;
    }
    
    CPoint position = GetRealPosition();
    float alpha = m_color.a * GetRealAlpha();
    
    wzSetSpriteColor(m_color.r, m_color.g, m_color.b, alpha);
    wzSetSpriteRotate(0.0f);
    wzFontSize(m_fontSize);
    wzPrintf(position.x, position.y, m_pText);
}
