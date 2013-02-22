//
//  CObject.h
//  Prototype
//
//  Created by  on 12/12/26.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#ifndef Prototype_CObject_h
#define Prototype_CObject_h

#include "CGameSDK.h"
#include "wizapply.h"

class CObject
{
public:
    bool IsLittleEndian();
    void ToLittleEndian(char *pData, unsigned int length);
    void ToBigEndian(char *pData, unsigned int length);
    void ReverseEndian(char *pData, unsigned int length);
    
    float BytesToFloat(const char *pData);
    
    virtual const char *GetClassName();
};

#endif
