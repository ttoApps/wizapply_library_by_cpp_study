//
//  CTouch.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CTouch.h"
#include <algorithm>

CTouch::CTouch()
{
    m_pElements.clear();
}

CTouch::~CTouch()
{
    std::vector<CElement *>::iterator iterator = m_pElements.begin();
    while (m_pElements.end() != iterator) {
        m_pElements.pop_back();
    }
}

void CTouch::AddElement(CElement *pView)
{
    m_pElements.push_back(pView);
}

void CTouch::RemoveElement(CElement *pElement)
{
    std::vector<CElement *>::iterator iterator = m_pElements.begin();
    while (m_pElements.end() != iterator) {
        if (pElement == (*iterator)) {
            iterator = m_pElements.erase(iterator);
            continue;
        }
        iterator++;
    }
}

void CTouch::Update()
{
    m_isTouch    = false;
    m_touchCount = 0;
    
    std::vector<CElement *>::iterator iterator = m_pElements.begin();
    while (m_pElements.end() != iterator) {
        (*iterator)->Touching(false);
        iterator++;
    }
    
    // sort depth
    std::sort(m_pElements.begin(), m_pElements.end(), &CElement::CompareDepth_Desc);
    
    for (int i = 0; i < TOUCH_COUNT; i++) {
        Touch touch;
        touch.isTouch = wzGetCursorSrPos(i, &touch.x, &touch.y);
        m_touch[i] = touch;
        
        if (touch.isTouch) {
            m_touchCount++;
            m_isTouch = true;
            
            std::vector<CElement *>::iterator iterator = m_pElements.begin();
            while (m_pElements.end() != iterator) {
                if ((*iterator)->IsTouchEnabled() && (*iterator)->PointOnRect(CPoint(touch.x, touch.y))) {
                    (*iterator)->Touching(true);
                    if (!(*iterator)->IsTouchThrow()) {
                        break;
                    }
                }
                iterator++;
            }
        }
    }
}

bool CTouch::IsTouch()
{
    return m_isTouch;
}

int CTouch::GetTouchesCount()
{
    return m_touchCount;
}

CPoint CTouch::GetTouchPoint(int index)
{
    Touch touches[m_touchCount];
    
    int n = 0;
    for (int i = 0; i < TOUCH_COUNT; i++) {
        if (m_touch[i].isTouch) {
            touches[n] = m_touch[i];
            n++;
        }
    }
    
    return CPoint(touches[index].x, touches[index].y);
}
