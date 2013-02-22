//
//  CSingleton.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CSingleton_h
#define WizapplyGameSDK_CSingleton_h

template <typename T>
class CSingleton
{
protected:
    CSingleton(){};
public:
    static T *GetInstance()
    {
        static T instance;
        return &instance;
    }
};

#endif
