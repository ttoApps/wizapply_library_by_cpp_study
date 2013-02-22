//
//  CElement.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/30.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CElement_h
#define WizapplyGameSDK_CElement_h

#include "CObject.h"

class CElement : public CObject
{
private:
    bool m_isTouch;
    bool m_isTouchEnabled;
    bool m_isTouchThrow;
    
    friend class CTouch;
    void Touching(bool isTouching);
protected:
    int m_depth;
    CPoint m_position;
    CSize  m_size;
    
    bool IsTouching();
    void SetTouchThrow(bool isTouchThrow);
public:
    CElement();
    virtual ~CElement();
    
    void SetPosition(CPoint point);
    CPoint GetPosition();
    void SetSize(CSize size);
    CSize GetSize();
    int GetDepth();
    
    virtual CRect GetRect();
    
    void SetTouchEnabled(bool isEnable);
    bool IsTouchEnabled();
    bool IsTouchThrow();
    virtual bool PointOnRect(CPoint point);
    
    static bool CompareDepth_Asc(CElement *pElementA, CElement *pElementB)
    {
        return (pElementA->GetDepth() < pElementB->GetDepth());
    }
    
    static bool CompareDepth_Desc(CElement *pElementA, CElement *pElementB)
    {
        return (pElementA->GetDepth() > pElementB->GetDepth());
    }
};

#endif
