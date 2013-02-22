//
//  CTextureManager.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CTextureManager.h"

CTextureManager::CTextureManager()
{
    m_textureList.clear();
}

CTextureManager::~CTextureManager()
{
    
}

void CTextureManager::LoadTexture(int num, const char *filename)
{
    std::map<int, wzTexture *>::iterator i = m_textureList.find(num);
    if (m_textureList.end() != i) {
        delete i->second;
        i->second = NULL;
    }
    
    wzTexture *texture = new wzTexture;
    wzCreateTextureFromPNG(texture, wzDCP(filename));
    m_textureList[num] = texture;
}

wzTexture *CTextureManager::GetTexture(int num)
{
    std::map<int, wzTexture *>::iterator i = m_textureList.find(num);
    if (m_textureList.end() == i) {
        return 0;
    }
    return i->second;
}

void CTextureManager::ReleaseAllTextures()
{
    std::map<int, wzTexture *>::iterator i;
    for (i = m_textureList.begin(); m_textureList.end() != i; i++) {
        delete i->second;
        i->second = 0;
    }
    m_textureList.clear();
}
