//
//  ITransition.h
//  WizapplyGameSDK
//
//  Created by  on 13/01/29.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WizapplyGameSDK_ITransition_h
#define WizapplyGameSDK_ITransition_h

#include "CTime.h"

class ITransitionDelegate
{
public:
    virtual void FinishTransition(int id) = 0;
};

class CView;

class ITransition
{
private:
    int m_id;
    bool m_isDeleted;
protected:
    CView *m_pView;
    CTime *m_pTime;
    ITransitionDelegate *m_pDelegate;
    
    float m_duration;
    bool m_isRun;
    
    friend class CView;
    virtual void SetView(CView *pView) = 0;
public:
    ITransition() {
        m_pView = 0;
        m_pTime = 0;
        m_pDelegate = 0;
        m_duration = 0.0f;
        m_isRun = false;
        m_isDeleted = false;
    }
    
    virtual ~ITransition() {};
    virtual void Run() = 0;
    virtual void Update() = 0;
    
    void SetDelegate(ITransitionDelegate *pDelegate) {
        m_pDelegate = pDelegate;
    }
    
    void SetId(int id) {
        m_id = id;
    }
    
    int GetId() {
        return m_id;
    }
    
    void SetDeleted(bool isDeleted) {
        m_isDeleted = isDeleted;
    }
    
    bool IsDeleted() {
        return m_isDeleted;
    }
};

#endif
