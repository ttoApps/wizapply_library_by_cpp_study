//
//  CData.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/02.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CData_h
#define WizapplyGameSDK_CData_h

#include "CObject.h"

class CData : public CObject
{
private:
    char *m_pData;
    char *m_pString;
    unsigned int m_length;
public:
    CData(unsigned int length, const void *pBytes = 0);
    ~CData();
    
    void CopyData(const void *pBytes);
    const char *GetData();
    unsigned int GetLength();
    const char *ToString();
};

#endif
