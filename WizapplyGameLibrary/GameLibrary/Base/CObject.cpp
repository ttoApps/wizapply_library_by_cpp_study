//
//  CObject.cpp
//  Prototype
//
//  Created by  on 12/12/26.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#include "CObject.h"


bool CObject::IsLittleEndian()
{
    int a = 1;
    return (*(char *)&a);
}

void CObject::ToLittleEndian(char *pData, unsigned int length)
{
    if (IsLittleEndian()) {
        return;
    }
    
    ReverseEndian(pData, length);
}

void CObject::ToBigEndian(char *pData, unsigned int length)
{
    if (!IsLittleEndian()) {
        return;
    }
    
    ReverseEndian(pData, length);
}

void CObject::ReverseEndian(char *pData, unsigned int length)
{
    char a = pData[0];
    for (int i = 0; i < length - 1; i++) {
        pData[i] = pData[i + 1];
    }
    pData[length - 1] = a;
}

float CObject::BytesToFloat(const char *pData)
{
    float value = 0.0f;
    
    memcpy(&value, &pData[0], sizeof(float));
    
    return value;
}

const char *CObject::GetClassName()
{
    return "CObject";
}
