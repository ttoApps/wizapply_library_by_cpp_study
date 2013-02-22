//
//  CLabel.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/02.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CLabel_h
#define WizapplyGameSDK_CLabel_h

#include "CView.h"

class CLabel : public CView
{
protected:
    char *m_pText;
    int m_fontSize;
public:
    CLabel();
    ~CLabel();
    
    void SetText(const char *pText);
    const char *GetText();
    void SetFontSize(unsigned size);
    void Draw();
};

#endif
