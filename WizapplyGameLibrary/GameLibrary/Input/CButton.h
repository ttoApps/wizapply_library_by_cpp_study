//
//  CButton.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CButton_h
#define WizapplyGameSDK_CButton_h

#include "CView.h"

typedef enum {
    ButtonStateNormal = 0,
    ButtonStateHighlight
} ButtonState;

class CButton : public CView
{
private:
    ButtonState m_state;
    ButtonState m_oldState;
    CColor m_normalColor;
    CColor m_highlightColor;
    bool IsOnPreviousFrame();
    bool IsOnNowFrame();
protected:
    int m_holdFrame;
    virtual void CheckState();
public:
    CButton();
    virtual ~CButton();
    bool IsOn();
    bool IsPress();
    bool IsRelease();
    bool IsHold();
    bool IsOff();
    int  GetHoldFrame();
    void SetState(ButtonState state);
    void SetColor(CColor color);
    void SetHighlightColor(CColor color);
    void Update();
    void Draw();
    
    virtual const char *GetClassName();
};

#endif
