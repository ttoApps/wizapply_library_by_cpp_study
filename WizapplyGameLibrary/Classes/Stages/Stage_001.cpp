//
//  Stage_001.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Stage_001.h"
#include "CTransitionFadeIn.h"
#include "CTransitionFadeOut.h"
#include "KeyPadManager.h"
#include "CCollision.h"
#include "CBlockSprite.h"
#include "CCriboSprite.h"

typedef enum {
    Stage_001TransitionID_Entry,
    Stage_001TransitionID_Exit,
    Stage_001TransitionID_NewPlayerEntry,
    Stage_001TransitionID_NewPlayerExit
} Stage_001TransitionID;

#define WIDTH   40
#define HEIGHT  15

#define PLAYER_SIZE CSize(64.0f, 64.0f)

int map[HEIGHT][WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Stage_001::Stage_001()
{
    m_pView->SetAlpha(1.0f);
    m_pView->SetSize(APPSCREEN_SIZE);
    
    m_drawSize = APPSCREEN_SIZE;
    
    m_pWorld = new CWorld(CVector(0.0f, 1.0f, 0.0f));
    
    InitializeWorld();
    
    CreatePlayer(CPoint(300.0f, 100.0f));
    
    for (int i = 0; i < MAX_MULTI_PLAYER; i++) {
        m_pOtherPlayers[i] = 0;
    }
    
    m_pConnection = new Connection(this);
    
    m_frame = 0;
}

Stage_001::~Stage_001()
{
    delete m_pConnection;
    m_pConnection = 0;
    
    delete m_pWorld;
    m_pWorld = 0;
    
    for (int i = 0; i < MAX_MULTI_PLAYER; i++) {
        if (0 != m_pOtherPlayers[i]) {
            if (m_pPlayer != m_pOtherPlayers[i]) {
                delete m_pOtherPlayers[i];
            }
            m_pOtherPlayers[i] = 0;
        }
    }
    
    delete m_pPlayer;
    m_pPlayer = 0;
}

void Stage_001::Update()
{
    m_frame++;
    
    m_pConnection->Update();
    
    for (int i = 0; i < MAX_MULTI_PLAYER; i++) {
        if (m_clientPositionQueues[i].empty() || 0 == m_pOtherPlayers[i]) {
            continue;
        }
        
        m_pOtherPlayers[i]->position = m_clientPositionQueues[i].front();
        m_clientPositionQueues[i].pop();
    }
    
    bool isMove = false;
    CVector moveVector = m_pPlayer->GetMoveVector();
    
    if (sKeyPadManager->GetMainKeyPad()->IsOn(KeyPadLeft)) {
        isMove = true;
        moveVector.x -= 4.0f;
    }
    /*
    if (sKeyPadManager->GetMainKeyPad()->IsOn(KeyPadTop)) {
        isMove = true;
        moveVector.y -= 4.0f;
    }*/
    
    if (sKeyPadManager->GetMainKeyPad()->IsOn(KeyPadRight)) {
        isMove = true;
        moveVector.x += 4.0f;
    }
    /*
    if (sKeyPadManager->GetMainKeyPad()->IsOn(KeyPadBottom)) {
        isMove = true;
        moveVector.y += 4.0f;
    }*/
    
    if (0.0f == moveVector.y && sKeyPadManager->GetMainKeyPad()->IsPress(KeyPadA)) {
        isMove = true;
        moveVector.y -= 16.0f;
        if (sKeyPadManager->GetMainKeyPad()->IsOn(KeyPadB)) {
            moveVector.y -= 4.0f;
        }
    }
    
    if (isMove) {
        m_pPlayer->SetMoveVector(moveVector);
        
        if (sKeyPadManager->GetMainKeyPad()->IsOn(KeyPadB)) {
            m_pPlayer->AddMoveVector(CVector(moveVector.x, 0.0f, 0.0f));
        }
    }
    
    if (sKeyPadManager->GetMainKeyPad()->IsPress(KeyPadStart)) {
        if (0 == CSocket::GetIP()) {
            m_pView->SetTransition(new CTransitionFadeIn(0.2f, this, Stage_001TransitionID_Entry));
            m_pView->RunTransition();
        }
        else {
            m_pConnection->Search();
        }
    }
    
    CRect drawRect = GetDrawRect();
    CRect stepRect = CRect(drawRect.left - m_drawSize.width, drawRect.top - m_drawSize.height, drawRect.right + m_drawSize.width, drawRect.bottom + m_drawSize.height);
    m_pWorld->Step(stepRect);
    
    std::list<CBody *> bodies = m_pWorld->GetBodyList();
    std::list<CBody *>::iterator i = bodies.begin();
    while (i != bodies.end()) {
        CRect bodyRect = (*i)->GetRect();
        if (CCollision::RectOnRect(bodyRect, drawRect)) {
            CPoint position = (*i)->position;
            position.x -= m_drawOffset.x;
            CView *surface = (*i)->GetSurface();
            surface->SetPosition(position);
        }
        
        ++i;
    }
    
    CVector vector = m_pPlayer->GetMoveVector();
    vector.x = 0.0f;
    m_pPlayer->SetMoveVector(vector);
    
    // プレイヤーの位置に合わせてステージの表示領域を移動
    CPoint center = CPoint(m_drawOffset.x + m_drawSize.width / 2.0f, m_drawOffset.y + m_drawSize.height / 2.0f);
    m_drawOffset.x += m_pPlayer->GetRect().right - center.x;
    if (0.0f > m_drawOffset.x || (0.0f >= (GetStageSize().width - m_drawSize.width))) {
        m_drawOffset.x = 0.0f;
    }
    else if ((GetStageSize().width - m_drawSize.width) < m_drawOffset.x) {
        m_drawOffset.x = GetStageSize().width - m_drawSize.width;
    }
    
    CPoint realPosition = m_pPlayer->GetSurface()->GetPosition() + m_drawOffset;
    m_pConnection->Move(realPosition);
}

void Stage_001::Draw()
{
    m_pView->Draw();
}

CSize Stage_001::GetStageSize()
{
    return CSize(WIDTH * SPRITE_SIZE, HEIGHT * SPRITE_SIZE);
}

void Stage_001::InitializeWorld()
{
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            int mapChip = map[j][i];
            switch (mapChip) {
                case 1:
                    CreateBlock(CPoint((float)i * SPRITE_SIZE, (float)j * SPRITE_SIZE));
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void Stage_001::CreatePlayer(CPoint position)
{
    if (0 == m_pWorld) {
        return;
    }
    
    CCriboSprite *pSprite = new CCriboSprite();
    pSprite->SetColor(CColor::WhiteColor());
    pSprite->SetSize(CSize(SPRITE_SIZE, SPRITE_SIZE));
    pSprite->SetPosition(position);
    
    ContactFilter filter;
    filter.categoryBit = 0x0001;
    filter.maskBit     = 0x1111;
    
    BodyType bodyType;
    bodyType.group    = 0;
    bodyType.isStatic = false;
    bodyType.size     = CSize(SPRITE_SIZE, SPRITE_SIZE);
    bodyType.filter   = filter;
    m_pPlayer = m_pWorld->CreateBody(bodyType);
    m_pPlayer->SetSurface(pSprite);
    m_pPlayer->position = position;
    
    m_pView->AddSubView(pSprite);
}

void Stage_001::CreateBlock(CPoint position)
{
    if (0 == m_pWorld) {
        return;
    }
    
    CBlockSprite *pSprite = new CBlockSprite();
    pSprite->SetSize(CSize(SPRITE_SIZE, SPRITE_SIZE));
    pSprite->SetPosition(position);
    
    ContactFilter filter;
    filter.categoryBit = 0x0001;
    filter.maskBit     = 0x1111;
    
    BodyType bodyType;
    bodyType.group    = 0;
    bodyType.isStatic = true;
    bodyType.size     = CSize(SPRITE_SIZE, SPRITE_SIZE);
    bodyType.filter   = filter;
    CBody *body = m_pWorld->CreateBody(bodyType);
    body->SetSurface(pSprite);
    body->position = position;
    
    m_pView->AddSubView(pSprite);
}

void Stage_001::CreateCribo(CPoint position)
{
    if (0 == m_pWorld) {
        return;
    }
    
    CCriboSprite *pSprite = new CCriboSprite();
    pSprite->SetSize(CSize(SPRITE_SIZE, SPRITE_SIZE));
    pSprite->SetPosition(position);
    
    ContactFilter filter;
    filter.categoryBit = 0x0001;
    filter.maskBit     = 0x1111;
    
    BodyType bodyType;
    bodyType.group    = 0;
    bodyType.isStatic = false;
    bodyType.size     = CSize(SPRITE_SIZE, SPRITE_SIZE);
    bodyType.filter   = filter;
    CBody *body = m_pWorld->CreateBody(bodyType);
    body->SetSurface(pSprite);
    body->position = position;
    
    m_pView->AddSubView(pSprite);
}

CBody *Stage_001::CreateNewPlayer(CPoint position)
{
    CCriboSprite *pSprite = new CCriboSprite();
    pSprite->SetSize(CSize(SPRITE_SIZE, SPRITE_SIZE));
    pSprite->SetPosition(position);
    
    ContactFilter filter;
    filter.categoryBit = 0x0001;
    filter.maskBit     = 0x1111;
    
    BodyType bodyType;
    bodyType.group    = 0;
    bodyType.isStatic = true;
    bodyType.size     = CSize(SPRITE_SIZE, SPRITE_SIZE);
    bodyType.filter   = filter;
    CBody *body = m_pWorld->CreateBody(bodyType);
    body->SetSurface(pSprite);
    body->position = position;
    
    m_pView->AddSubView(pSprite);
    
    return body;
}


#pragma mark - ITransitionDelegate Methods

void Stage_001::FinishTransition(int id)
{
    switch (id) {
        case Stage_001TransitionID_Entry:
            break;
            
        case Stage_001TransitionID_Exit:
            break;
            
        default:
            break;
    }
}


#pragma mark - ConnectionDelegate Methods

void Stage_001::DidDetectServer()
{
    m_pConnection->Entry(m_pPlayer->position);
}

void Stage_001::DidStartServer(int clientNo)
{
    if (0 > clientNo || MAX_MULTI_PLAYER < clientNo || 0 != m_pOtherPlayers[clientNo]) {
        return;
    }
    
    m_pView->SetColor(CColor::PurpleColor());
    
    m_pOtherPlayers[clientNo] = m_pPlayer;
}

void Stage_001::DidStartClient(int clientNo)
{
    m_pView->SetColor(CColor::YellowColor());
    
    m_pOtherPlayers[clientNo] = m_pPlayer;
}

bool Stage_001::GetClientPosition(int clientNo, CPoint *pPosition)
{
    if (0 > clientNo || MAX_MULTI_PLAYER < clientNo || 0 == m_pOtherPlayers[clientNo]) {
        return false;
    }
    
    CBody *pPlayer = m_pOtherPlayers[clientNo];
    pPosition->x = pPlayer->position.x;
    pPosition->y = pPlayer->position.y;
    
    return true;
}

void Stage_001::NewPlayerEntry(int clientNo, CPoint position)
{
    if (0 > clientNo || MAX_MULTI_PLAYER < clientNo || 0 != m_pOtherPlayers[clientNo]) {
        return;
    }
    
    CBody *pPlayer = CreateNewPlayer(position);
    
    CView *pPlayerView = pPlayer->GetSurface();
    if (0 == clientNo) {
        pPlayerView->SetColor(CColor::GreenColor().SetAlpha(0.8f));
    }
    else {
        pPlayerView->SetColor(CColor::BlueColor().SetAlpha(0.8f));
    }
    
    pPlayerView->SetTransition(new CTransitionFadeIn(0.4f, this, Stage_001TransitionID_NewPlayerEntry));
    pPlayerView->RunTransition();
    
    m_pOtherPlayers[clientNo] = pPlayer;
}

void Stage_001::UpdatePlayerPosition(int clientNo, CPoint position)
{
    if (0 > clientNo || MAX_MULTI_PLAYER < clientNo || 0 == m_pOtherPlayers[clientNo]) {
        return;
    }
    
    m_clientPositionQueues[clientNo].push(position);
}

void Stage_001::ExitPlayer(int clientNo)
{
    if (0 > clientNo || MAX_MULTI_PLAYER < clientNo || 0 == m_pOtherPlayers[clientNo]) {
        return;
    }
    
    delete m_pOtherPlayers[clientNo];
    m_pOtherPlayers[clientNo] = 0;
    
    while (!m_clientPositionQueues[clientNo].empty()) {
        m_clientPositionQueues[clientNo].pop();
    }
}
