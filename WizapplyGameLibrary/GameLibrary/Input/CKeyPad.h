//
//  CKeyPad.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/25.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CKeyPad_h
#define WizapplyGameSDK_CKeyPad_h

#include "CObject.h"
#include "CView.h"
#include "CPadButton.h"

#define KEY_PAD_BUTTON_COUNT    9

typedef enum {
    KeyPadLeft = 0,
    KeyPadTop,
    KeyPadRight,
    KeyPadBottom,
    KeyPadA,
    KeyPadB,
    KeyPadSelect,
    KeyPadStart,
    KeyPadExit
} KeyPad;

typedef struct KeyPadButton {
    unsigned char keyCode;
    CPoint position;
    CSize  size;
    CColor color;
    KeyPadButton(unsigned char keyCode_, CPoint point_, CSize size_, CColor color_) {
        keyCode  = keyCode_;
        position = point_;
        size     = size_;
        color    = color_;
    }
};

class CKeyPad : public CObject
{
private:
    CView *m_pView;
protected:
    CPadButton m_button[KEY_PAD_BUTTON_COUNT];
public:
    CKeyPad();
    ~CKeyPad();
    
    CView *GetView();
    
    bool IsOn(KeyPad keyPad);
    bool IsPress(KeyPad keyPad);
    bool IsRelease(KeyPad keyPad);
    bool IsHold(KeyPad keyPad);
    bool IsOff(KeyPad keyPad);
    int  GetHoldFrame(KeyPad keyPad);
};

#endif
