//
//  GameScene.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/26.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "GameScene.h"
#include "SceneFactory.h"
#include "CSceneManager.h"
#include "KeyPadManager.h"
#include "CTransitionFadeIn.h"
#include "CTransitionFadeOut.h"

typedef enum {
    GameSceneTransitionID_Entry,
    GameSceneTransitionID_Exit,
    GameSceneTransitionID_NewPlayerEntry,
    GameSceneTransitionID_NewPlayerExit
} GameSceneTransitionID;

#define PLAYER_SIZE CSize(64.0f, 64.0f)

GameScene::GameScene()
{
    m_pView->SetPosition(CPoint(0.0f, 0.0f));
    m_pView->SetColor(CColor::GreenColor());
    m_pView->SetSize(APPSCREEN_SIZE);
    
    m_pStage = new Stage_001();
    m_pView->AddSubView(m_pStage->GetView());
    
    m_pView->SetTransition(new CTransitionFadeIn(0.4f, this, GameSceneTransitionID_Entry));
    m_pView->RunTransition();
}

GameScene::~GameScene()
{
    delete m_pStage;
    m_pStage = 0;
}

void GameScene::Update()
{
    m_pStage->Update();
    
    if (sKeyPadManager->GetMainKeyPad()->IsPress(KeyPadExit)) {
        m_pView->SetTransition(new CTransitionFadeOut(0.4f, this, GameSceneTransitionID_Exit));
        m_pView->RunTransition();
    }
}

#pragma mark - ITransitionDelegate Methods

void GameScene::FinishTransition(int id)
{
    switch (id) {
        case GameSceneTransitionID_Entry:
            break;
            
        case GameSceneTransitionID_Exit:
            sSceneManager->ReplaceScene(SceneID_Title);
            break;
            
        default:
            break;
    }
}
