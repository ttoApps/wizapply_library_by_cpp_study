//
//  CBlockSprite.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CBlockSprite.h"
#include "CTextureManager.h"

CBlockSprite::CBlockSprite()
{
    m_pTexture    = sTextureManager->GetTexture(0);
    m_coord.u     = 0.0f;
    m_coord.v     = 0.0f;
    m_coord.uw    = 0.5f;
    m_coord.vh    = 0.5f;
    m_size.width  = SPRITE_SIZE;
    m_size.height = SPRITE_SIZE;
    m_position.x  = 0.0f;
    m_position.y  = 0.0f;
    m_depth       = 0;
    
    SetTouchEnabled(false);
}
