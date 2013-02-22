//
//  CCollision.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CCollision_h
#define WizapplyGameSDK_CCollision_h

class CCollision : public CObject
{
public:
    static bool PointOnRect(CPoint point, CRect rect);
    static bool RectOnRect(CRect rect1, CRect rect2);
};

#endif
