//
//  Stage_001.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/06.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_Stage_001_h
#define WizapplyGameSDK_Stage_001_h

#include "CStage.h"
#include "CWorld.h"
#include "ITransition.h"
#include "Connection.h"
#include <queue>

class Stage_001 : public CStage, public ITransitionDelegate, public ConnectionDelegate
{
private:
    int m_frame;
    CWorld *m_pWorld;
    CBody *m_pPlayer;
    CBody *m_pOtherPlayers[MAX_MULTI_PLAYER];
    std::queue<CPoint> m_clientPositionQueues[MAX_MULTI_PLAYER];
    Connection *m_pConnection;
    
    void CreatePlayer(CPoint position);
    void CreateBlock(CPoint position);
    void CreateCribo(CPoint position);
    CBody *CreateNewPlayer(CPoint position);
    void InitializeWorld();
public:
    Stage_001();
    ~Stage_001();
    
    void Update();
    void Draw();
    
    CSize GetStageSize();
    
    // ITransitionDelegate
    void FinishTransition(int id);
    
    // ConnectionDelegate
    void DidDetectServer();
    void DidStartServer(int clientNo);
    void DidStartClient(int clientNo);
    bool GetClientPosition(int clientNo, CPoint *pPosition);
    void NewPlayerEntry(int clientNo, CPoint position);
    void UpdatePlayerPosition(int clientNo, CPoint moveVector);
    void ExitPlayer(int clientNo);
};

#endif
