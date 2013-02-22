//
//  CScene.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CScene.h"

CScene::CScene()
{
    m_pView = new CView();
}

CScene::~CScene()
{
    if (0 != m_pView) {
        delete m_pView;
        m_pView = 0;
    }
}

void CScene::Update()
{
}

void CScene::Draw()
{
    if (0 == m_pView) {
        return;
    }
    
    m_pView->Draw();
}
