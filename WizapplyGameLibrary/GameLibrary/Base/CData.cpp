//
//  CData.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/02.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CData.h"
#include <string.h>

CData::CData(unsigned int length, const void *pBytes)
{
    m_length  = length;
    m_pData   = new char[length];
    m_pString = new char[length + 1];
    
    for (int i = 0; i < length; i++) {
        m_pData[i]   = 0;
        m_pString[i] = 0;
    }
    m_pString[length + 1] = '\0';
    
    if (0 != pBytes) {
        CopyData(pBytes);
    }
}

CData::~CData()
{
    delete[] m_pString;
    m_pString = 0;
    
    delete[] m_pData;
    m_pData = 0;
}

void CData::CopyData(const void *pBytes)
{
    memcpy(m_pData, pBytes, m_length);
}

const char *CData::GetData()
{
    return m_pData;
}

unsigned int CData::GetLength()
{
    return m_length;
}

const char *CData::ToString()
{
    for (int i = 0; i < m_length; i++) {
        m_pString[i] = m_pData[i];
    }
    
    return m_pString;
}
