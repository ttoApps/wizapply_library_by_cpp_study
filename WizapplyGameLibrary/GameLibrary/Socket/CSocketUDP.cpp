//
//  CSocketUDP.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/03.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CSocketUDP.h"

CSocketUDP::CSocketUDP(unsigned short port, int bufferLength, int blocking)
{
    wzCreateSocketUDP(&m_socket, port, blocking);
    
    m_pBuffer      = new char[bufferLength];
    m_bufferLength = bufferLength;
    
    memset(m_pBuffer, 0, bufferLength);
}

CSocketUDP::~CSocketUDP()
{
    delete[] m_pBuffer;
    m_pBuffer = 0;
    
    wzDeleteSocket(&m_socket);
}

bool CSocketUDP::CreateSender(const char *pIP, unsigned short port)
{
    return (0 == wzCreateSenderUDP(&m_sender, pIP, port));
}

bool CSocketUDP::CreateBroadcast(unsigned short port)
{
    return (0 == wzCreateBroadcastUDP(&m_sender, port));
}

int CSocketUDP::SendData(const char *pData, unsigned int length)
{
    return wzSendData(&m_socket, pData, length, &m_sender);
}

int CSocketUDP::GetReceiveData(char *pReceiveData)
{
    int length = wzRecvData(&m_socket, m_pBuffer, m_bufferLength, &m_sender);
    if (0 < length) {
        memcpy(pReceiveData, m_pBuffer, length);
    }
    
    return length;
}
