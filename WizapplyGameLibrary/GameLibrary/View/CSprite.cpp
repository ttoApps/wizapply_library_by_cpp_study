//
//  CSprite.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CSprite.h"

CSprite::CSprite()
{
    m_pTexture     = 0;
    m_coord.u      = 0.0f;
    m_coord.v      = 0.0f;
    m_coord.uw     = 0.0f;
    m_coord.vh     = 0.0f;
    m_size.width   = 0.0f;
    m_size.height  = 0.0f;
    m_position.x   = 0.0f;
    m_position.y   = 0.0f;
    m_depth        = 0;
    m_color        = CColor::WhiteColor();
}

CSprite::~CSprite()
{
    
}

void CSprite::Draw()
{
    if (0 == m_pTexture) {
        return;
    }
    
    CPoint position = GetRealPosition();
    float alpha = m_color.a * GetRealAlpha();
    
    wzSetSpriteColor(m_color.r, m_color.g, m_color.b, alpha);
	wzSetSpriteTexCoord(m_coord.u, m_coord.v, m_coord.uw - m_coord.u, m_coord.vh - m_coord.v);
	wzSetSpritePosition(position.x, position.y, 0.0f);
	wzSetSpriteSizeLeftUp(m_size.width, m_size.height);
	wzSetSpriteTexture(m_pTexture);
	wzSpriteDraw();
}