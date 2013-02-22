//
//  CGameSDK.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/24.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_CGameSDK_h
#define WizapplyGameSDK_CGameSDK_h

typedef struct CPoint {
    float x;
    float y;
    CPoint(float x_ = 0.0f, float y_ = 0.0f) {
        x = x_;
        y = y_;
    }
    CPoint operator+(const CPoint &point_) {
        CPoint point;
        point.x += x + point_.x;
        point.y += y + point_.y;
        return point;
    }
    CPoint &operator+=(const CPoint &point_) {
        x += point_.x;
        y += point_.y;
        return *this;
    }
};

typedef struct CRect {
    float left;
    float top;
    float right;
    float bottom;
    CRect(float left_ = 0.0f, float top_ = 0.0f, float right_ = 0.0f, float bottom_ = 0.0f) {
        left   = left_;
        top    = top_;
        right  = right_;
        bottom = bottom_;
    }
};

typedef struct CVector {
    float x;
    float y;
    float z;
    CVector(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) {
        x = x_;
        y = y_;
        z = z_;
    }
};

typedef struct CSize {
    float width;
    float height;
    CSize(float width_ = 0.0f, float height_ = 0.0f) {
        width  = width_;
        height = height_;
    }
};

typedef struct CColor {
    float r;
    float g;
    float b;
    float a;
    CColor(float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f, float a_ = 0.0f) {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
    static CColor RedColor() {
        return CColor(1.0f, 0.0f, 0.0f, 1.0f);
    }
    static CColor GreenColor() {
        return CColor(0.0f, 1.0f, 0.0f, 1.0f);
    }
    static CColor BlueColor() {
        return CColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
    static CColor YellowColor() {
        return CColor(1.0f, 1.0f, 0.0f, 1.0f);
    }
    static CColor PurpleColor() {
        return CColor(1.0f, 0.0f, 1.0f, 1.0f);
    }
    static CColor CyanColor() {
        return CColor(0.0f, 1.0f, 1.0f, 1.0f);
    }
    static CColor WhiteColor() {
        return CColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    static CColor BlackColor() {
        return CColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    CColor SetAlpha(float alpha) {
        a = alpha;
        return *this;
    }
};

#endif
