//
//  CPadButton.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CPadButton_h
#define WizapplyGameSDK_CPadButton_h

#include "CButton.h"

class CPadButton : public CButton
{
private:
    unsigned char m_keyCode;
protected:
    void CheckState();
public:
    CPadButton();
    void SetKeyCode(unsigned char keyCode);
    
    virtual const char *GetClassName();
};

#endif
