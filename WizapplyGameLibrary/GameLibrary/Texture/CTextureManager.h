//
//  CTextureManager.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CTextureManager_h
#define WizapplyGameSDK_CTextureManager_h

#include "CSingleton.h"
#include <map>

class CTextureManager : public CSingleton<CTextureManager>
{
private:
    std::map<int, wzTexture *> m_textureList;
public:
    CTextureManager();
    ~CTextureManager();
    
    void LoadTexture(int num, const char *filename);
    wzTexture *GetTexture(int num);
    void ReleaseAllTextures();
};

#define sTextureManager (CTextureManager::GetInstance())
#endif
