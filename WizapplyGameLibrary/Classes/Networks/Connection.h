//
//  Connection.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/03.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_Connection_h
#define WizapplyGameSDK_Connection_h

#include "CObject.h"
#include "CSocket.h"
#include <vector>

typedef enum {
    CommunicationType_Search,
    CommunicationType_SearchResponse,
    CommunicationType_Entry,
    CommunicationType_EntryResponse,
    CommunicationType_Move,
    CommunicationType_Exit,
} CommunicationType;

typedef struct RetryConnection {
    unsigned int counter;
    unsigned int numberOfRetry;
    CommunicationType type;
    
    RetryConnection(unsigned int counter_, unsigned int numberOfRetry_, CommunicationType type_) {
        counter       = counter_;
        numberOfRetry = numberOfRetry_;
        type          = type_;
    }
};

typedef struct ConnectionClient {
    const char *pIP;
    unsigned short port;
    
    ConnectionClient(const char *pIP_ = 0, unsigned short port_ = 20000) {
        pIP = pIP_;
        port = port_;
    }
};

class ConnectionDelegate
{
public:
    virtual void DidDetectServer() = 0;
    virtual void DidStartServer(int clientNo) = 0;
    virtual void DidStartClient(int clientNo) = 0;
    virtual bool GetClientPosition(int clientNo, CPoint *pPosition) = 0;
    virtual void NewPlayerEntry(int clientNo, CPoint position) = 0;
    virtual void UpdatePlayerPosition(int clientNo, CPoint position) = 0;
    virtual void ExitPlayer(int clientNo) = 0;
};

class Connection : public CObject
{
private:
    CSocketUDP *m_pSocketUDP;
    ConnectionDelegate *m_pDelegate;
    unsigned short m_port;
    
    std::vector<RetryConnection *> m_retryConnections;
    
    bool m_isReady;
    int  m_clientNo;
    char *m_pServerIP;
    unsigned short m_serverPort;
    ConnectionClient *m_pClients[MAX_MULTI_PLAYER];
    
    void CommunicationInterpretation(const char *pData);
    
    void SearchResponse(const char *pIP, unsigned short port);
    void EntryResponse(bool isValid, int clientNo);
    void RemoveRetryConnection(CommunicationType type);
public:
    Connection(ConnectionDelegate *pDelegate, unsigned short port = 20000);
    ~Connection();
    
    void Update();
    bool IsServer();
    bool IsClient();
    bool IsUnknown();
    
    void Search(RetryConnection *pRetryConnection = 0);
    void Entry(CPoint point);
    void Move(CPoint point);
    void Exit();
};

#endif
