//
//  Macro.h
//  WizapplyGameSDK
//
//  Created by  on 12/12/26.
//  Copyright (c) 2012 ttoApps. All rights reserved.
//

#ifndef WizapplyGameSDK_Macro_h
#define WizapplyGameSDK_Macro_h

// アプリのスクリーン表示サイズ
#ifdef MACOSX
#define APPSCREEN_WIDTH		(960)
#define APPSCREEN_HEIGHT	(640)
#else
#define APPSCREEN_WIDTH		(960)
#define APPSCREEN_HEIGHT	(640)
#endif

// スプライトのサイズ
#define SPRITE_SIZE 32.0f

// 一度に表示される敵の最大数
#define MAX_ENEMY_COUNT 20

// 最大マルチプレイヤー数
#define MAX_MULTI_PLAYER    12

// デバッグモード
#define DEBUG_MODE  true

#define APPSCREEN_SIZE CSize(APPSCREEN_WIDTH, APPSCREEN_HEIGHT)

#endif
