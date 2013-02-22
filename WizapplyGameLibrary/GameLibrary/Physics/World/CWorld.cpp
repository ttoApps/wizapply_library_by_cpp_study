//
//  CWorld.cpp
//  WizapplyGameSDK
//
//  Created by  on 12/12/29.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#include "CWorld.h"
#include "CCollision.h"

CWorld::CWorld(CVector gravity)
{
    m_gravity = gravity;
    m_bodies.clear();
    m_contactBodies.clear();
}

CBody *CWorld::CreateBody(BodyType bodyType)
{
    CBody *body = new CBody(bodyType);
    m_bodies.push_back(body);
    return body;
}

void CWorld::DestroyBody(CBody *body)
{
}

std::list<CBody *> CWorld::GetBodyList()
{
    return m_bodies;
}

std::list<CContact *> CWorld::GetContactBodyList()
{
    return m_contactBodies;
}

void CWorld::Step(CRect rect)
{
    if (m_bodies.empty()) {
        return;
    }
    
    m_contactBodies.clear();
    
    // step計算するオブジェクトを可視領域で限定する ※ステージが広くてもupdate回数が減らない様に。
    m_showingBodies.clear();
    std::list<CBody *>::iterator j = m_bodies.begin();
    while (j != m_bodies.end()) {
        if (CCollision::RectOnRect((*j)->GetRect(), rect)) {
            m_showingBodies.push_back((*j));
        }
        ++j;
    }
    
    if (m_showingBodies.empty()) {
        return;
    }
    
    // T.B.D. とりあえず重力加算とキャラの移動力だけ ※ここで全てのオブジェクトを管理して衝突チェックを行う事になる。
    std::list<CBody *>::iterator i = m_showingBodies.begin();
    while (i != m_showingBodies.end()) {
        CBody *body = *i;
        
        // 静的な物体はスキップ
        if (body->IsStaticBody()) {
            ++i;
            continue;
        }
        
        // 重力加算
        body->AddMoveVector(m_gravity);
        
        // まず横のみ移動して衝突するかチェック
        body->MoveX();
        
        // 接触しているオブジェクトを追加
        CheckContactBodies(body, DirectionHorizon);
        
        // 縦移動
        body->MoveY();
        
        // 接触しているオブジェクトを追加
        CheckContactBodies(body, DirectionVertical);
        
        ++i;
    }
}

void CWorld::CheckContactBodies(CBody *body, Direction direction)
{
    if (m_showingBodies.empty()) {
        return;
    }
    
    std::list<CBody *>::iterator i = m_showingBodies.begin();
    while (i != m_showingBodies.end()) {
        if (body == *i) {
            ++i;
            continue;
        }
        
        if (CCollision::RectOnRect(body->GetRect(),(*i)->GetRect())) {
            // 衝突
            // 反発力と衝突相手との移動力の相殺を計算と、移動位置の補正(めり込みの訂正)
            // とりあえず横方向のみ
            if (DirectionHorizon == direction) {
                if (body->GetMoveVector().x > 0.0f) {
                    // 右移動
                    // まず位置の補正
                    body->position.x += (*i)->GetRect().left - body->GetRect().right;
                    
                    // 反発力, 移動力の相殺 (とりあえず0にする)
                    CVector moveVector = CVector(0.0f, body->GetMoveVector().y, body->GetMoveVector().z);
                    body->SetMoveVector(moveVector);
                }
                else if (body->GetMoveVector().x < 0.0f) {
                    // 左移動
                    // まず位置の補正
                    body->position.x += (*i)->GetRect().right - body->GetRect().left;
                    
                    // 反発力, 移動力の相殺 (とりあえず0にする)
                    CVector moveVector = CVector(0.0f, body->GetMoveVector().y, body->GetMoveVector().z);
                    body->SetMoveVector(moveVector);
                }
            }
            else if (DirectionVertical == direction) {
                if (body->GetMoveVector().y > 0.0f) {
                    // 下移動
                    // まず位置の補正
                    body->position.y += (*i)->GetRect().top - body->GetRect().bottom;
                    
                    // 反発力, 移動力の相殺 (とりあえず0にする)
                    CVector moveVector = CVector(body->GetMoveVector().x, 0.0f, body->GetMoveVector().z);
                    body->SetMoveVector(moveVector);
                }
                else if (body->GetMoveVector().y < 0.0f) {
                    // 上移動
                    // まず位置の補正
                    body->position.y += (*i)->GetRect().bottom - body->GetRect().top;
                    
                    // 反発力, 移動力の相殺 (とりあえず反転する)
                    CVector moveVector = CVector(body->GetMoveVector().x, body->GetMoveVector().y * -0.5f, body->GetMoveVector().z);
                    body->SetMoveVector(moveVector);
                }
            }
            
            m_contactBodies.push_back(new CContact(body, (*i)));
        }
        ++i;
    }
}
