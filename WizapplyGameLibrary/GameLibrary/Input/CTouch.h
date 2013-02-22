//
//  CTouch.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CTouch_h
#define WizapplyGameSDK_CTouch_h

#include "CSingleton.h"
#include "CElement.h"
#include <vector>

#define TOUCH_COUNT 5

typedef struct Touch {
    bool isTouch;
    float x;
    float y;
    Touch(bool isTouch_ = false, float x_ = 0.0f, float y_ = 0.0f) {
        isTouch = isTouch_;
        x = x_;
        y = y_;
    }
};

class CTouch : public CSingleton<CTouch>
{
private:
    bool m_isTouch;
    int  m_touchCount;
    Touch m_touch[TOUCH_COUNT];
    std::vector<CElement *> m_pElements;
    
    friend class CElement;
    void AddElement(CElement *pViews);
    void RemoveElement(CElement *pViews);
public:
    CTouch();
    ~CTouch();
    void Update();
    bool IsTouch();
    int  GetTouchesCount();
    CPoint GetTouchPoint(int index);
};

#define sTouch (CTouch::GetInstance())
#endif
