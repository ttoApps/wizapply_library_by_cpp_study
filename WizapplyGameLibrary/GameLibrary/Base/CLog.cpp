//
//  CLog.cpp
//  Prototype
//
//  Created by  on 12/12/26.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#include "CLog.h"
#include <stdio.h>
#include <stdarg.h>

void CLog::Debug(const char *file, const int line, const char *function, const char *format, ...)
{
    va_list argp;
    fprintf(stderr, "[DEBUG] %s(%d): %s() ", file, line, function);
    va_start(argp, format);
    vfprintf(stderr, format, argp);
    va_end(argp);
    fprintf(stderr, "\n");
}
