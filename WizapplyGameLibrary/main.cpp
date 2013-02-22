/*
 * Wizapply ウィザードプロジェクトファイル
 * Mac OS Xプロジェクト
 */

/* -- インクルードファイル -------------------------------------------- */

// エントリポイント
#include <EntryPoint.h>		//!<クロスプラットフォーム用共通エントリーポイント

/* -- マクロ定義 ------------------------------------------------------- */

//アプリのスクリーン表示サイズ
#define APPSCREEN_WIDTH		(640)
#define APPSCREEN_HEIGHT	(480)

/* -- グローバル変数定義 ----------------------------------------------- */


/* -- プロトタイプ宣言 ------------------------------------------------- */

void UpdateFunc(void);	//!<関数

/* -- 関数 ------------------------------------------------------------- */

/*
 * アプリ初期化関数
 * ※returnに「0」以外を返すとエラー扱いになりプログラムが終了します。
 */
int Initialize()
{
	// Wizapplyライブラリを初期化
	wzInitCreateWizapply("Wizapply for Mac",APPSCREEN_WIDTH,APPSCREEN_HEIGHT,0);

	/*------------------------------------------------------------------*/

	// 情報をセット
	wzSetClearColor(0.1f,0.1f,0.1f,1);		// クリア情報
	wzSetSpriteScSize(APPSCREEN_WIDTH, APPSCREEN_HEIGHT);	// スプライト設定
	wzSetCursorScSize(APPSCREEN_WIDTH, APPSCREEN_HEIGHT);	// 画面カーソル設定

	/*--------------------------------------

		****ゲームデータを初期化する****
	
	----------------------------------------*/

	/*------------------------------------------------------------------*/

	// 関数をセット
	wzSetUpdateThread(60,UpdateFunc);	// 更新 -> UpdateFunc

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

	/*------------------------------------------------------------------*/

	// デバッグ情報（通常不要）
	wzSetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	wzSetSpriteRotate(0.0f);
	wzFontSize(18);

	wzPrintf(20, 40, "Wizapply");
	wzPrintf(20, 70, "Update:%.2f", wzGetUpdateFPS());
	wzPrintf(20, 90, "Draw  :%.2f", wzGetDrawFPS());

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
}

//EOF