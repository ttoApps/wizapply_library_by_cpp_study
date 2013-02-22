//
//  CStage.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CStage_h
#define WizapplyGameSDK_CStage_h

#include "CObject.h"
#include "CView.h"

class CStage : public CObject
{
protected:
    CView *m_pView;
    CPoint m_drawOffset;
    CSize m_drawSize;
public:
    CStage();
    virtual ~CStage();
    
    CView *GetView();
    CRect GetDrawRect();
    virtual void Update();
    virtual void Draw();
};

#endif
