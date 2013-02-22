//
//  CLog.h
//  Prototype
//
//  Created by  on 12/12/26.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#ifndef Prototype_CLog_h
#define Prototype_CLog_h

#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#include "CObject.h"

class CLog : public CObject
{
public:
    void static Debug(const char *file, const int line, const char *function, const char *format, ...);
};

#endif
