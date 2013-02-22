//
//  CSprite.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CSprite_h
#define WizapplyGameSDK_CSprite_h

#include "CView.h"

typedef struct {
    float u;
    float v;
    float uw;
    float vh;
} TextureCoord;

class CSprite : public CView
{
protected:
    wzTexture    *m_pTexture;
    TextureCoord m_coord;
public:
    CSprite();
    virtual ~CSprite();
    
    virtual void Draw();
};

#endif
