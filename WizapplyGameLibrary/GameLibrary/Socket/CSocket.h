//
//  CSocket.h
//  WizapplyGameSDK
//
//  Created by  on 13/02/02.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CSocket_h
#define WizapplyGameSDK_CSocket_h

#include "CObject.h"
#include "CSocketTCPServer.h"
#include "CSocketTCPClient.h"
#include "CSocketUDP.h"

class CSocket : public CObject
{
public:
    static const char *GetIP();
};

#endif
