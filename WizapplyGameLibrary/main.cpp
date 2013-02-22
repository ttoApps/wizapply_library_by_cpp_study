/*
 * Wizapply ウィザードプロジェクトファイル
 * Mac OS Xプロジェクト
 */

/* -- インクルードファイル -------------------------------------------- */

// エントリポイント
#include <EntryPoint.h>		//!<クロスプラットフォーム用共通エントリーポイント
#include "KeyPadManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "SceneFactory.h"
#include "CTransitionManager.h"
#include "CTextureManager.h"

/* -- マクロ定義 ------------------------------------------------------- */
#include "Macro.h"

/* -- グローバル変数定義 ----------------------------------------------- */

/* -- プロトタイプ宣言 ------------------------------------------------- */

void UpdateFunc(void);	//!<関数
float GetRand();

/* -- 関数 ------------------------------------------------------------- */

/*
 * アプリ初期化関数
 * ※returnに「0」以外を返すとエラー扱いになりプログラムが終了します。
 */
int Initialize()
{
	// Wizapplyライブラリを初期化
	wzInitCreateWizapply("Wizapply for Mac", APPSCREEN_WIDTH, APPSCREEN_HEIGHT, 0);

	/*------------------------------------------------------------------*/

	// 情報をセット
	wzSetClearColor(0.0f, 0.0f, 0.0f, 1.0f);                // クリア情報
	wzSetSpriteScSize(APPSCREEN_WIDTH, APPSCREEN_HEIGHT);	// スプライト設定
	wzSetCursorScSize(APPSCREEN_WIDTH, APPSCREEN_HEIGHT);	// 画面カーソル設定

	/*--------------------------------------

		****ゲームデータを初期化する****
	
	----------------------------------------*/
    sSceneManager->SetSceneFactory(new SceneFactory());
    sSceneManager->PushScene(SceneID_Title);
    sTextureManager->LoadTexture(0, "textures32.png");
    
	/*------------------------------------------------------------------*/

	// 関数をセット
	wzSetUpdateThread(60, UpdateFunc);	// 更新 -> UpdateFunc

	return 0;
}

/*
 * アプリ終了関数
 * ※returnに「0」以外を返すとエラー扱いになりプログラムが終了します。
 */
int Terminate()
{

	/*----------------------------------------

		****ゲームデータを解放する****
	
	----------------------------------------*/
    
	/*------------------------------------------------------------------*/

	// Wizapplyライブラリの終了処理
	wzExitWizapply();

	return 0;
}

/*
 * 描画用スレッド関数
 * 最大のパフォーマンスの間隔で呼ばれます。
 */
void DrawLoop(void)
{
	// 画面クリア
	wzClear();

	/*----------------------------------------

		****ゲームを描画する****
		（GPUにアクセスする描画処理を書く）

		※繰り返し呼び出されます。
	
	----------------------------------------*/
    
    sSceneManager->Draw();

	/*------------------------------------------------------------------*/

	// デバッグ情報（通常不要）
    
	wzSetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	wzSetSpriteRotate(0.0f);
    wzFontSize(18);
    
	wzPrintf(20,  40, (char *)"Wizapply");
	wzPrintf(20,  70, (char *)"Update:%0.2f", wzGetUpdateFPS());
	wzPrintf(20,  90, (char *)"Draw  :%0.2f", wzGetDrawFPS());
	wzPrintf(20, 120, (char *)"isHold:%u", wzGetTime());
	wzPrintf(20, 140, (char *)"holdFrame:%d", sKeyPadManager->GetMainKeyPad()->GetHoldFrame(KeyPadA));
}

float GetRand()
{
    return (float)(rand() % 256) / 256;
}

/*
 * 更新用スレッド関数
 * 1秒間に60回の固定の間隔で呼ばれます。
 */
void UpdateFunc(void)
{
	/*----------------------------------------

		****ゲームを更新する****
		（GPUにアクセスする描画関連の処理は書かないこと[テクスチャ読み込み含む]）

		※繰り返し呼び出されます。
	
     ----------------------------------------*/
    sInputManager->Update();
    sSceneManager->Update();
    sTransitionManager->Update();
}

//EOF