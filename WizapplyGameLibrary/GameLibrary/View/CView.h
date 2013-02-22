//
//  CView.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CView_h
#define WizapplyGameSDK_CView_h

#include "CElement.h"
#include "ITransition.h"
#include <vector>

class CView : public CElement
{
private:
    bool m_isHidden;
    
    CView *m_pSuperView;
    std::vector<CView *> m_pSubViews;
    
    void SetSuperView(CView *pView);
    void RemoveSubView(CView *pView);
    
    ITransition *m_pTransition;
protected:
    CColor m_color;
    float m_alpha;
    
    CPoint GetRealPosition();
    float GetRealAlpha();
public:
    CView();
    virtual ~CView();
    
    void SetHidden(bool isHidden);
    bool IsHidden();
    CView *GetSuperView();
    void AddSubView(CView *pView);
    void RemoveFromSuperView();
    int GetSubViewCount();
    virtual void SetColor(CColor color);
    CColor GetColor();
    void SetAlpha(float alpha);
    float GetAlpha();
    CRect GetRect();
    virtual void Draw();
    
    void SetTransition(ITransition *pTransition);
    void RunTransition();
    
    bool PointOnRect(CPoint point);
    virtual const char *GetClassName();
};

#endif
