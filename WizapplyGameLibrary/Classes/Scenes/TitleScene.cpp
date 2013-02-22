//
//  TitleScene.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "TitleScene.h"
#include "CSceneManager.h"
#include "KeyPadManager.h"
#include "SceneFactory.h"
#include "CTransitionFadeIn.h"
#include "CTransitionFadeOut.h"
#include "CLabel.h"

typedef enum {
    TitleSceneTransitionID_SceneEntry,
    TitleSceneTransitionID_SceneExit,
    TitleSceneTransitionID_StartButtonShow,
    TitleSceneTransitionID_StartButtonHide
} TitleSceneTransitionID;

TitleScene::TitleScene()
{
    m_pView->SetPosition(CPoint(0.0f, 0.0f));
    m_pView->SetColor(CColor::CyanColor());
    m_pView->SetSize(APPSCREEN_SIZE);
    
    m_pStartButton = new CButton();
    m_pStartButton->SetPosition(CPoint(0.0f, 200.0f));
    m_pStartButton->SetSize(CSize(100.0f, 100.0f));
    m_pStartButton->SetColor(CColor::BlueColor());
    m_pView->AddSubView(m_pStartButton);
    
    m_pView->SetTransition(new CTransitionFadeIn(0.4f, this, TitleSceneTransitionID_SceneEntry));
    m_pView->RunTransition();
}

TitleScene::~TitleScene()
{
    if (0 != m_pStartButton) {
        delete m_pStartButton;
        m_pStartButton = 0;
    }
}

void TitleScene::Update()
{
    if ((0 != m_pStartButton && m_pStartButton->IsOn()) || sKeyPadManager->GetMainKeyPad()->IsPress(KeyPadA)) {
        m_pView->SetTransition(new CTransitionFadeOut(0.4f, this, TitleSceneTransitionID_SceneExit));
        m_pView->RunTransition();
        return;
    }
    
    if (sKeyPadManager->GetMainKeyPad()->IsPress(KeyPadB)) {
        if (m_pStartButton->IsHidden()) {
            m_pStartButton->SetHidden(false);
            m_pStartButton->SetAlpha(1.0f);
            m_pStartButton->SetTransition(new CTransitionFadeIn(0.4f, this, TitleSceneTransitionID_StartButtonShow));
            m_pStartButton->RunTransition();
        }
        else {
            m_pStartButton->SetTransition(new CTransitionFadeOut(0.4f, this, TitleSceneTransitionID_StartButtonHide));
            m_pStartButton->RunTransition();
        }
    }
}

void TitleScene::FinishTransition(int id)
{
    switch (id) {
        case TitleSceneTransitionID_SceneEntry:
            break;
            
        case TitleSceneTransitionID_SceneExit:
            sSceneManager->ReplaceScene(SceneID_Game);
            break;
            
        case TitleSceneTransitionID_StartButtonShow:
            m_pStartButton->SetHidden(false);
            break;
            
        case TitleSceneTransitionID_StartButtonHide:
            m_pStartButton->SetHidden(true);
            break;
            
        default:
            break;
    }
}
