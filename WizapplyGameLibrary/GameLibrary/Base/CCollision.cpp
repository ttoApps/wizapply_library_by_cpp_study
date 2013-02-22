//
//  CCollision.cpp
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "CCollision.h"

bool CCollision::PointOnRect(CPoint point, CRect rect)
{
    if (point.x <= rect.left) {
        return false;
    }
    
    if (point.x >= rect.right) {
        return false;
    }
    
    if (point.y <= rect.top) {
        return false;
    }
    
    if (point.y >= rect.bottom) {
        return false;
    }
    
    return true;
}

bool CCollision::RectOnRect(CRect rect1, CRect rect2)
{
    if (rect1.top >= rect2.bottom) {
        return false;
    }
    
    if (rect1.right <= rect2.left) {
        return false;
    }
    
    if (rect1.bottom <= rect2.top) {
        return false;
    }
    
    if (rect1.left >= rect2.right) {
        return false;
    }
    
    return true;
}
