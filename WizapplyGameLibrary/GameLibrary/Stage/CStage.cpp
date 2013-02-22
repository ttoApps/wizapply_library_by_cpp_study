//
//  CStage.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CStage.h"

CStage::CStage()
{
    m_pView = new CView();
    
    m_drawOffset = CPoint();
    m_drawSize   = CSize(40.0f, 15.0f);
}

CStage::~CStage()
{
    if (0 != m_pView) {
        delete m_pView;
        m_pView = 0;
    }
}

CView *CStage::GetView()
{
    return m_pView;
}

CRect CStage::GetDrawRect()
{
    return CRect(m_drawOffset.x, m_drawOffset.y, m_drawOffset.x + m_drawSize.width, m_drawOffset.y + m_drawSize.height);
}

void CStage::Update()
{
}

void CStage::Draw()
{
    if (0 == m_pView) {
        return;
    }
    
    m_pView->Draw();
}
