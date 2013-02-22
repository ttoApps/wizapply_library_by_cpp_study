//
//  ISurface.h
//  WizapplyGameSDK
//
//  Created by  on 12/12/30.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#ifndef WizapplyGameSDK_ISurface_h
#define WizapplyGameSDK_ISurface_h

class ISurface
{
public:
    ISurface();
    virtual ~ISurface();
    
    virtual void SetPosition(CPoint position) = 0;
    virtual void SetAngle(float angle) = 0;
    virtual void Draw() = 0;
};

#endif
