// ---------------------------------------------------------------------------

#ifndef Num_lineup16_Unit1H
#define Num_lineup16_Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ActnList.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.MultiView.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <System.Actions.hpp>

// ---------------------------------------------------------------------------
struct TmyPosition {
	Single X;
	Single Y;
public:
	TmyPosition() {
		X = 0;
		Y = 0;
	}
};

class TForm1 : public TForm {
__published: // IDE で管理されるコンポーネント
	TTabControl *TabControlSetting;
	TTabItem *Setting;
	TToolBar *tbSetting;
	TLabel *Label2;
	TButton *btnGotoTile;
	TButton *btnMaster;
	TListBox *lbSetting;
	TListBoxGroupHeader *ListBoxGroupHeader1;
	TListBoxItem *ListBoxItem1;
	TButton *btnNewGame;
	TGlowEffect *GlowEffectNewGame;
	TFloatAnimation *FloatAnimationNewGame;
	TListBoxGroupHeader *ListBoxGroupHeader2;
	TListBoxItem *ListBoxItem3;
	TComboBox *cbTileRect;
	TListBoxItem *ListBoxItem2;
	TSpinBox *SpinBox1;
	TListBoxItem *ListBoxItem4;
	TSwitch *Switch1;
	TListBoxGroupFooter *ListBoxGroupFooter1;
	TTabItem *Tile;
	TScaledLayout *ScaledLayout1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TGlowEffect *GlowEffectTile;
	TFloatAnimation *FloatAnimationTileGrow;
	TToolBar *tbTile;
	TLabel *Label1;
	TButton *btnGotoSetting;
	TGlowEffect *GlowEffectGotoSetting;
	TFloatAnimation *FloatAnimationGotoSetting;
	TMultiView *MultiView1;
	TToolBar *ToolBar1;
	TLabel *Label3;
	TTrackBar *TrackBar1;
	TLayout *Layout1;
	TStyleBook *StyleBook1;
	TActionList *ActionList1;
	TNextTabAction *NextTabAction1;
	TPreviousTabAction *PreviousTabAction1;
	TFloatAnimation *FlButtonAnimation;
	TGestureManager *GestureManager1;

	void __fastcall NextTabAction1Update(TObject *Sender);
	void __fastcall PreviousTabAction1Update(TObject *Sender);
	void __fastcall FlButtonAnimationFinish(TObject *Sender);
	void __fastcall MultiView1Hidden(TObject *Sender);
	void __fastcall MultiView1StartShowing(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall ListBoxGroupFooter1Click(TObject *Sender);
	void __fastcall btnNewGameClick(TObject *Sender);
	void __fastcall cbTileRectChange(TObject *Sender);
	void __fastcall Switch1Switch(TObject *Sender);
	void __fastcall btnGotoTileClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btnGotoSettingClick(TObject *Sender);

private: // ユーザー宣言

	TButton *btnMoving, *btnInvisibleTile; // 動いているボタン、消しているボタンを覚えとく
	int iNumOfBtn; // タイル数を覚えておく
	bool FComp; // 完成しているかフラグ
	Single slpx, slpy;

	void __fastcall SetNewGame(); // 新規ゲーム開始手続呼び出しのための、ほか手続きまとめて呼び出し
	void __fastcall SetInitTilePos(); // タイル位置の初期整列
	void __fastcall SetInvisibleTile(); // 隠しタイル決定
	void __fastcall ShuffleTiles(); // タイル位置シャッフル
	void __fastcall ChangeBtnPlace(TButton *btnFirst, TButton *btnSecond); // シャッフル時にボタンの位置入れ替えのための手続き
	void __fastcall btnPushed(TButton *pbtn); // タイルがクリックされたたらポジションチェックを呼び出すための手続き
	void __fastcall NextPosChk(TButton *pbtn); // 横が見えないタイルかチェック
	void __fastcall ButtonAni(TButton *pbtn, String PName, Single StpValue); // タイル移動アニメの手続き
	void __fastcall CompleteSet(); // 完成した場合の処理
	void __fastcall SetTileRect(); // タイル表示方法の切り替え（正方形かフィットか）
	bool __fastcall CheckFin(); // タイルならべが完成しているかチェック
	TButton* __fastcall FindTagBtn(int tag); // ボタンの持っているタグ情報から対象のボタンオブジェクト見つける
	TmyPosition __fastcall GetTilePosition(int tag); // タグ情報からボタンの座標情報を見つける

public: // ユーザー宣言
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
