//
//  Connection.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/03.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Connection.h"

#define UNKNOWN_CLIENT_NO   -1
#define SERVER_NO           0

#define COMMUNICATION_HEADER_LENGTH 4

Connection::Connection(ConnectionDelegate *pDelegate, unsigned short port)
{
    m_pSocketUDP = new CSocketUDP(port);
    m_pSocketUDP->CreateBroadcast(port);
    
    m_pDelegate = pDelegate;
    m_port      = port;
    
    m_isReady    = false;
    m_clientNo   = UNKNOWN_CLIENT_NO;
    m_pServerIP  = 0;
    m_serverPort = 0;
    
    for (int i = 0; i < MAX_MULTI_PLAYER; i++) {
        m_pClients[i] = 0;
    }
    
    m_retryConnections.clear();
}

Connection::~Connection()
{
    if (m_isReady) {
        Exit();
    }
    
    for (int i = 0; i < MAX_MULTI_PLAYER; i++) {
        if (0 == m_pClients[i]) {
            continue;
        }
        
        delete m_pClients[i];
        m_pClients[i] = 0;
    }
    
    delete m_pSocketUDP;
    m_pSocketUDP = 0;
}

void Connection::CommunicationInterpretation(const char *pData)
{
    //CLog("type %d", pData[1]);
    switch (pData[1]) {
        case CommunicationType_Search:
            {
                int dataLength = pData[2] + pData[3] * 0x0100;
                int ipLength   = dataLength - 2;
                
                unsigned short port = pData[4] + pData[5] * 0x0100;
                
                char ip[ipLength];
                for (int i = 0; i < ipLength; i++) {
                    ip[i] = pData[6 + i];
                }
                
                bool isMyIp   = (0 == strcmp(CSocket::GetIP(), (const char *)&ip));
                bool isMyPort = m_port == port;
                if (!isMyIp || !isMyPort) {
                    SearchResponse(ip, port);
                }
            }
            break;
            
        case CommunicationType_SearchResponse:
            {
                RemoveRetryConnection(CommunicationType_Search);
                
                int dataLength = pData[2] + pData[3] * 0x0100;
                if (1 == dataLength) {
                    // とりあえず無視。
                }
                else {
                    m_clientNo   = pData[4] + pData[5] * 0x0100;
                    m_serverPort = pData[6] + pData[7] * 0x0100;
                    
                    int ipLength = dataLength - 4;
                    m_pServerIP  = new char[ipLength];
                    
                    for (int i = 0; i < ipLength; i++) {
                        m_pServerIP[i] = pData[8 + i];
                    }
                    
                    const char *pSelfIP = CSocket::GetIP();
                    char *pIP = new char[strlen(pSelfIP)];
                    memcpy(pIP, pSelfIP, strlen(pSelfIP));
                    
                    m_pClients[SERVER_NO]  = new ConnectionClient(m_pServerIP, m_serverPort);
                    m_pClients[m_clientNo] = new ConnectionClient(pIP, m_port);
                    
                    m_pDelegate->DidDetectServer();
                }
            }
            break;
            
        case CommunicationType_Entry:
            {
                int dataLength = pData[2] + pData[3] * 0x0100;
                int clientNo   = pData[4] + pData[5] * 0x0100;
                
                if (m_clientNo != clientNo) {
                    bool isInvalidClientNo = (0 > clientNo || MAX_MULTI_PLAYER < clientNo || (IsServer() && 0 == m_pClients[clientNo]) || IsClient() && 0 != m_pClients[clientNo]);
                    if (!isInvalidClientNo) {
                        int floatSize  = (dataLength - 2) / 2;
                        
                        CPoint point = CPoint(BytesToFloat(&pData[6]), BytesToFloat(&pData[6 + floatSize]));
                        
                        ToLittleEndian((char *)&point.x, floatSize);
                        ToLittleEndian((char *)&point.y, floatSize);
                        
                        if (IsClient()) {
                            m_pClients[clientNo] = new ConnectionClient();
                        }
                        
                        m_pDelegate->NewPlayerEntry(clientNo, point);
                    }
                    
                    if (IsServer()) {
                        EntryResponse(!isInvalidClientNo, clientNo);
                    }
                }
            }
            break;
            
        case CommunicationType_EntryResponse:
            {
                m_isReady = true;
                
                int dataLength = pData[2] + pData[3] * 0x0100;
                //int isEntry    = pData[4];
                int floatSize  = pData[5];
                
                if (2 < dataLength) {
                    int temporaryLength = 0;
                    
                    while (dataLength > (temporaryLength + 2)) {
                        int clientNo = pData[6 + temporaryLength] + pData[7 + temporaryLength] * 0x0100;
                        if (m_clientNo == clientNo) {
                            continue;
                        }
                        
                        CPoint point;
                        memcpy(&point.x, &pData[8 + temporaryLength], floatSize);
                        memcpy(&point.y, &pData[8 + temporaryLength + floatSize], floatSize);
                        
                        m_pDelegate->NewPlayerEntry(clientNo, point);
                        
                        if (IsClient()) {
                            m_pClients[clientNo] = new ConnectionClient();
                        }
                        
                        temporaryLength += 2 + (floatSize * 2);
                    }
                }
                
                m_pDelegate->DidStartClient(m_clientNo);
            }
            break;
            
        case CommunicationType_Move:
            {
                int dataLength = pData[2] + pData[3] * 0x0100;
                int clientNo   = pData[4] + pData[5] * 0x0100;
                
                if (m_clientNo != clientNo) {
                    bool isInvalidClientNo = (0 > clientNo || MAX_MULTI_PLAYER < clientNo || 0 == m_pClients[clientNo]);
                    if (!isInvalidClientNo) {
                        int floatSize  = (dataLength - 2) / 2;
                        
                        CPoint point = CPoint(BytesToFloat(&pData[6]), BytesToFloat(&pData[6 + floatSize]));
                        
                        ToLittleEndian((char *)&point.x, floatSize);
                        ToLittleEndian((char *)&point.y, floatSize);
                        
                        m_pDelegate->UpdatePlayerPosition(clientNo, point);
                    }
                }
            }
            break;
            
        case CommunicationType_Exit:
            {
                int clientNo = pData[4] + pData[5] * 0x0100;
                
                if (m_clientNo != clientNo) {
                    bool isInvalidClientNo = (0 > clientNo || MAX_MULTI_PLAYER < clientNo || 0 == m_pClients[clientNo]);
                    if (!isInvalidClientNo) {
                        m_pDelegate->ExitPlayer(clientNo);
                        delete m_pClients[clientNo];
                        m_pClients[clientNo] = 0;
                    }
                }
            }
            break;
        default:
            break;
    }
}


void Connection::SearchResponse(const char *pIP, unsigned short port)
{
    if (IsUnknown()) {
        return;
    }
    
    int length = COMMUNICATION_HEADER_LENGTH;
    
    if (IsClient()) {
        length += 1;
        
        char data[length];
        
        data[0] = 0x00;
        data[1] = CommunicationType_SearchResponse;
        data[2] = 0x01;
        data[3] = 0x00;
        data[4] = 0x01;
        
        m_pSocketUDP->CreateSender(pIP, port);
        m_pSocketUDP->SendData(data, length);
        return;
    }
    
    // クライアント配列に登録してクライアント番号を決めておく
    unsigned short clientNo = UNKNOWN_CLIENT_NO;
    for (int i = 0; i < MAX_MULTI_PLAYER; i++) {
        if (0 == m_pClients[i]) {
            char *pClientIp = new char[strlen(pIP)];
            memcpy(pClientIp, pIP, strlen(pIP));
            m_pClients[i] = new ConnectionClient(pClientIp, port);
            clientNo = i;
            break;
        }
    }
    
    const char *pSelfIP = CSocket::GetIP();
    unsigned short selfPort = m_port;
    
    int clientNoLength = 2;
    int portLength     = 2;
    int ipLength       = (int)(strlen(pSelfIP) + 1);
    int dataLength     = clientNoLength + portLength + ipLength;
    length            += dataLength;
    
    ToLittleEndian((char *)&dataLength, sizeof(int));
    ToLittleEndian((char *)&clientNo, sizeof(unsigned short));
    ToLittleEndian((char *)&selfPort, sizeof(unsigned short));
    
    char data[length];
    
    data[0] = 0x00;
    data[1] = CommunicationType_SearchResponse;
    data[2] = ((char *)&dataLength)[0];
    data[3] = ((char *)&dataLength)[1];
    data[4] = ((char *)&clientNo)[0];
    data[5] = ((char *)&clientNo)[1];
    data[6] = ((char *)&selfPort)[0];
    data[7] = ((char *)&selfPort)[1];
    
    for (int i = 0; i < ipLength; i++) {
        data[8 + i] = pSelfIP[i];
    }
    
    m_pSocketUDP->CreateSender(pIP, port);
    m_pSocketUDP->SendData(data, length);
}

void Connection::EntryResponse(bool isValid, int clientNo)
{
    int dataLength = 2;
    int floatSize  = sizeof(float);
    
    char temporaryBuffer[1024] = {0};
    int  temporaryLength       = 0;
    
    // 全クライアント番号とクライアントの座標を送信する
    for (int i = 0; i < MAX_MULTI_PLAYER; i++) {
        if (0 == m_pClients[i] || clientNo == i) {
            continue;
        }
        
        CPoint position;
        if (!m_pDelegate->GetClientPosition(i, &position)) {
            continue;
        }
        
        unsigned short no = i;
        
        ToLittleEndian((char *)&no, sizeof(unsigned short));
        ToLittleEndian((char *)&position.x, floatSize);
        ToLittleEndian((char *)&position.y, floatSize);
        
        temporaryBuffer[temporaryLength + 0] = ((char *)&no)[0];
        temporaryBuffer[temporaryLength + 1] = ((char *)&no)[1];
        
        for (int j = 0; j < (floatSize * 2); j++) {
            if (j < floatSize) {
                temporaryBuffer[temporaryLength + 2 + j] = ((char *)&position.x)[j];
            }
            else {
                temporaryBuffer[temporaryLength + 2 + j] = ((char *)&position.y)[j - floatSize];
            }
        }
        
        temporaryLength += 2 + (floatSize * 2);
    }
    
    dataLength += temporaryLength;
    
    int length = COMMUNICATION_HEADER_LENGTH + dataLength;
    
    ToLittleEndian((char *)&dataLength, sizeof(int));
    ToLittleEndian((char *)&floatSize, sizeof(int));
    
    char data[length];
    data[0] = 0x00;
    data[1] = CommunicationType_EntryResponse;
    data[2] = ((char *)&dataLength)[0];
    data[3] = ((char *)&dataLength)[1];
    data[4] = (isValid) ? 0x01 : 0x00;
    data[5] = ((char *)&floatSize)[0];
    
    memcpy(&data[6], &temporaryBuffer[0], temporaryLength);
    
    m_pSocketUDP->CreateSender(m_pClients[clientNo]->pIP, m_pClients[clientNo]->port);
    m_pSocketUDP->SendData(data, length);
}

void Connection::RemoveRetryConnection(CommunicationType type)
{
    std::vector<RetryConnection *>::iterator iterator = m_retryConnections.begin();
    while (m_retryConnections.end() != iterator) {
        RetryConnection *pRetryConnection = (*iterator);
        if (type == pRetryConnection->type) {
            iterator = m_retryConnections.erase(iterator);
            delete pRetryConnection;
            pRetryConnection = 0;
            continue;
        }
    }
}

void Connection::Update()
{
    std::vector<RetryConnection *>::iterator iterator = m_retryConnections.begin();
    while (m_retryConnections.end() != iterator) {
        RetryConnection *pRetryConnection = (*iterator);
        if (0 < pRetryConnection->counter) {
            pRetryConnection->counter--;
            if (0 == pRetryConnection->counter) {
                switch (pRetryConnection->type) {
                    case CommunicationType_Search:
                        if (0 < pRetryConnection->numberOfRetry) {
                            Search(pRetryConnection);
                        }
                        else {
                            m_clientNo = SERVER_NO;
                            m_isReady  = true;
                            
                            m_serverPort = 0;
                            if (0 != m_pServerIP) {
                                delete m_pServerIP;
                                m_pServerIP = 0;
                            }
                            
                            const char *pSelfIP = CSocket::GetIP();
                            char *pIP = new char[strlen(pSelfIP)];
                            memcpy(pIP, pSelfIP, strlen(pSelfIP));
                            
                            m_pClients[m_clientNo] = new ConnectionClient(pIP, m_port);
                            
                            m_pDelegate->DidStartServer(m_clientNo);
                        }
                        break;
                        
                    default:
                        break;
                }
                
                if (0 == pRetryConnection->numberOfRetry) {
                    iterator = m_retryConnections.erase(iterator);
                    delete pRetryConnection;
                    pRetryConnection = 0;
                    continue;
                }
                
                pRetryConnection->numberOfRetry--;
            }
        }
        iterator++;
    }
    
    while (true) {
        char receiveData[1024] = {0};
        
        int length = m_pSocketUDP->GetReceiveData(receiveData);
        if (length <= 0) {
            break;
        }
        
        /*
        for (int i = 0; i < length; i++) {
            if (CommunicationType_Move == receiveData[1]) {
                CLog("%d", receiveData[i]);
            }
        }*/
        
        CommunicationInterpretation(receiveData);
    }
}

bool Connection::IsServer()
{
    return (SERVER_NO == m_clientNo);
}

bool Connection::IsClient()
{
    return (0 < m_clientNo);
}

bool Connection::IsUnknown()
{
    return (UNKNOWN_CLIENT_NO == m_clientNo);
}

void Connection::Search(RetryConnection *pRetryConnection)
{
    if (!IsUnknown() || 0 == CSocket::GetIP()) {
        return;
    }
    
    if (0 == pRetryConnection) {
        pRetryConnection = new RetryConnection(10, 3, CommunicationType_Search);
        m_retryConnections.push_back(pRetryConnection);
    }
    else {
        pRetryConnection->counter = 10;
    }
    
    const char *pIP = CSocket::GetIP();
    unsigned short port = m_port;
    
    int portLength = 2;
    int ipLength   = (int)(strlen(pIP) + 1);
    int dataLength = portLength + ipLength;
    int length     = COMMUNICATION_HEADER_LENGTH + dataLength;
    
    ToLittleEndian((char *)&dataLength, sizeof(int));
    ToLittleEndian((char *)&port, sizeof(unsigned short));
    
    char data[length];
    
    data[0] = 0x00;
    data[1] = CommunicationType_Search;
    data[2] = ((char *)&dataLength)[0];
    data[3] = ((char *)&dataLength)[1];
    data[4] = ((char *)&port)[0];
    data[5] = ((char *)&port)[1];
    
    for (int i = 0; i < ipLength; i++) {
        data[6 + i] = pIP[i];
    }
    
    m_pSocketUDP->SendData(data, length);
}

void Connection::Entry(CPoint point)
{
    int floatSize      = sizeof(float);
    int clientNoLength = 2;
    int positionLength = floatSize * 2;
    int dataLength     = clientNoLength + positionLength;
    int length         = COMMUNICATION_HEADER_LENGTH + dataLength;
    
    int clientNo = m_clientNo;
    
    ToLittleEndian((char *)&dataLength, sizeof(int));
    ToLittleEndian((char *)&clientNo, sizeof(int));
    ToLittleEndian((char *)&point.x, floatSize);
    ToLittleEndian((char *)&point.y, floatSize);
    
    char data[length];
    
    data[0] = 0x00;
    data[1] = CommunicationType_Entry;
    data[2] = ((char *)&dataLength)[0];
    data[3] = ((char *)&dataLength)[1];
    data[4] = ((char *)&clientNo)[0];
    data[5] = ((char *)&clientNo)[1];
    
    for (int i = 0; i < floatSize; i++) {
        data[6 + i] = ((char *)&point.x)[i];
    }
    
    for (int j = 0; j < floatSize; j++) {
        data[6 + floatSize + j] = ((char *)&point.y)[j];
    }
    
    m_pSocketUDP->CreateBroadcast(m_port);
    m_pSocketUDP->SendData(data, length);
}

void Connection::Move(CPoint point)
{
    if (!m_isReady) {
        return;
    }
    
    int floatSize      = sizeof(float);
    int clientNoLength = 2;
    int positionLength = floatSize * 2;
    int dataLength     = clientNoLength + positionLength;
    int length         = COMMUNICATION_HEADER_LENGTH + dataLength;
    
    int clientNo = m_clientNo;
    
    ToLittleEndian((char *)&dataLength, sizeof(int));
    ToLittleEndian((char *)&clientNo, sizeof(int));
    ToLittleEndian((char *)&point.x, floatSize);
    ToLittleEndian((char *)&point.y, floatSize);
    
    char data[length];
    
    data[0] = 0x00;
    data[1] = CommunicationType_Move;
    data[2] = ((char *)&dataLength)[0];
    data[3] = ((char *)&dataLength)[1];
    data[4] = ((char *)&clientNo)[0];
    data[5] = ((char *)&clientNo)[1];
    
    for (int i = 0; i < floatSize; i++) {
        data[6 + i] = ((char *)&point.x)[i];
    }
    
    for (int j = 0; j < floatSize; j++) {
        data[6 + floatSize + j] = ((char *)&point.y)[j];
    }
    
    m_pSocketUDP->CreateBroadcast(m_port);
    m_pSocketUDP->SendData(data, length);
}

void Connection::Exit()
{
    int dataLength = 2;
    int clientNo   = m_clientNo;
    ToLittleEndian((char *)&dataLength, sizeof(int));
    ToLittleEndian((char *)&clientNo, sizeof(int));
    
    char data[6] = {0};
    
    data[0] = 0x00;
    data[1] = CommunicationType_Exit;
    data[2] = ((char *)&dataLength)[0];
    data[3] = ((char *)&dataLength)[1];
    data[4] = ((char *)&clientNo)[0];
    data[5] = ((char *)&clientNo)[1];
    
    m_pSocketUDP->CreateBroadcast(m_port);
    m_pSocketUDP->SendData(data, 6);
}
