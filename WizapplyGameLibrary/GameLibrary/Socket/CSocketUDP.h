//
//  CSocketUDP.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/03.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CSocketUDP_h
#define WizapplyGameSDK_CSocketUDP_h

#include "CObject.h"

class CSocketUDP : public CObject
{
private:
    wzSocket m_socket;
    wzSender m_sender;
    int m_bufferLength;
    char *m_pBuffer;
public:
    CSocketUDP(unsigned short port, int bufferLength = 1024, int blocking = 0);
    ~CSocketUDP();
    
    bool CreateSender(const char *pIP, unsigned short port);
    bool CreateBroadcast(unsigned short port);
    int SendData(const char *pData, unsigned int length);
    int GetReceiveData(char *pReceiveData);
};

#endif
