//
//  CSocket.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/02/02.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CSocket.h"

const char *CSocket::GetIP()
{
    return wzGetSelfIP(0);
}
