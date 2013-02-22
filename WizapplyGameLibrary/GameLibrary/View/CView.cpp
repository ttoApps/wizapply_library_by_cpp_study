//
//  CView.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CView.h"

static wzTexture texture = 0;

CView::CView()
{
    m_isHidden = false;
    
    m_pSuperView = 0;
    m_pSubViews.clear();
    
    m_color = CColor();
    m_alpha = 1.0f;
    
    m_pTransition = 0;
    
    if (0 == texture) {
        wzCreateTextureFromPNG(&texture, wzDCP("Button.png"));
    }
}

CView::~CView()
{
    std::vector<CView *>::iterator iterator = m_pSubViews.begin();
    while (iterator != m_pSubViews.end()) {
        iterator = m_pSubViews.erase(iterator);
    }
    m_pSubViews.clear();
    
    RemoveFromSuperView();
    
    if (0 != m_pTransition) {
        m_pTransition->SetDeleted(true);
    }
}

void CView::SetSuperView(CView *pView)
{
    m_pSuperView = pView;
    m_depth = pView->GetDepth() + pView->GetSubViewCount() + 1;
    
    std::vector<CView *>::iterator iterator = m_pSubViews.begin();
    while (iterator != m_pSubViews.end()) {
        (*iterator)->SetSuperView(this);
        iterator++;
    }
}


void CView::SetHidden(bool isHidden)
{
    m_isHidden = isHidden;
}

bool CView::IsHidden()
{
    return m_isHidden;
}

CView *CView::GetSuperView()
{
    return m_pSuperView;
}

int CView::GetSubViewCount()
{
    return (int)m_pSubViews.size();
}

void CView::AddSubView(CView *pView)
{
    // 自分自身に追加しようとした時は何もしない
    if (pView->GetSuperView() == pView) {
        return;
    }
    
    pView->RemoveFromSuperView();
    pView->SetSuperView(this);
    m_pSubViews.push_back(pView);
}

void CView::RemoveSubView(CView *pView)
{
    std::vector<CView *>::iterator iterator = m_pSubViews.begin();
    while (iterator != m_pSubViews.end()) {
        if (pView == (*iterator)) {
            iterator = m_pSubViews.erase(iterator);
            continue;
        }
        iterator++;
    }
}

void CView::RemoveFromSuperView()
{
    m_depth = 0;
    
    if (0 == m_pSuperView) {
        return;
    }
    
    m_pSuperView->RemoveSubView(this);
    m_pSuperView = 0;
}

void CView::SetColor(CColor color)
{
    m_color = color;
}

CColor CView::GetColor()
{
    return m_color;
}

void CView::SetAlpha(float alpha)
{
    m_alpha = alpha;
}

float CView::GetAlpha()
{
    return m_alpha;
}

CPoint CView::GetRealPosition()
{
    CPoint position = m_position;
    
    CView *pSuperView = m_pSuperView;
    while (0 != pSuperView) {
        position += pSuperView->GetPosition();
        pSuperView = pSuperView->GetSuperView();
    }
    
    return position;
}

float CView::GetRealAlpha()
{
    float alpha = m_alpha;
    
    CView *pSuperView = m_pSuperView;
    while (0 != pSuperView) {
        alpha *= pSuperView->GetAlpha();
        pSuperView = pSuperView->GetSuperView();
    }
    
    return alpha;
}

CRect CView::GetRect()
{
    CPoint position = GetRealPosition();
    return CRect(position.x, position.y, position.x + m_size.width, position.y + m_size.height);
}

void CView::Draw()
{
    if (m_isHidden) {
        return;
    }
    
    CPoint position = GetRealPosition();
    float alpha = m_color.a * GetRealAlpha();
    
    wzSetSpriteColor(m_color.r, m_color.g, m_color.b, alpha);
    wzSetSpriteTexCoord(0.0f, 0.0f, 1.0f, 1.0f);
    wzSetSpritePosition(position.x, position.y, 0.0f);
    wzSetSpriteSizeLeftUp(m_size.width, m_size.height);
    wzSetSpriteTexture(&texture);
    wzSpriteDraw();
    
    std::vector<CView *>::iterator iterator = m_pSubViews.begin();
    while (iterator != m_pSubViews.end()) {
        (*iterator)->Draw();
        iterator++;
    }
}

void CView::SetTransition(ITransition *pTransition)
{
    if (0 != m_pTransition) {
        m_pTransition->SetDeleted(true);
    }
    
    m_pTransition = pTransition;
    m_pTransition->SetView(this);
}

void CView::RunTransition()
{
    if (0 == m_pTransition) {
        return;
    }
    
    m_pTransition->Run();
}

bool CView::PointOnRect(CPoint point)
{
    return (m_isHidden) ? false : CElement::PointOnRect(point);
}

const char *CView::GetClassName()
{
    return "CView";
}
