// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Num_lineup16_Unit1.h"
#include "TilesVersionUnit2.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::NextTabAction1Update(TObject *Sender) {
	// ジェスチャーで右から左。タイル画面呼び出し
	if (btnGotoTile->Enabled == True && TabControlSetting->TabIndex == 0) {
		TabControlSetting->SetActiveTabWithTransition(Tile,
			TTabTransition::Slide, TTabTransitionDirection::Normal);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::PreviousTabAction1Update(TObject *Sender) {
	// ジェスチャーで左から右。設定画面呼び出し
	if (btnGotoSetting->Enabled == True && TabControlSetting->TabIndex == 1) {
		TabControlSetting->SetActiveTabWithTransition(Setting,
			TTabTransition::Slide, TTabTransitionDirection::Reversed);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FlButtonAnimationFinish(TObject *Sender) {
	// ボタン移動のアニメーション完了後の処理
	// 移動後のボタン有効化と、インビシブルタイルの移動
	if (!FComp) {
		btnMoving->Enabled = True;
		// 移動が正しくできたかチェック（インビジの位置まで動いたか)
		if (btnMoving->Position->X == btnInvisibleTile->Position->X &&
			btnMoving->Position->Y == btnInvisibleTile->Position->Y) {
			// インビジタイルの移動
			int iTmpTag = btnMoving->Tag;
			btnInvisibleTile->Position->X = slpx;
			btnInvisibleTile->Position->Y = slpy;
			btnMoving->Tag = btnInvisibleTile->Tag;
			btnInvisibleTile->Tag = iTmpTag;
		}

	}
	// コンプリートチェック
	if (CheckFin() && !FComp) {
		CompleteSet();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::MultiView1Hidden(TObject *Sender) {
	// マルチビューが隠れるとき、設定リストをもとの設定タブの返す
	Setting->AddObject(lbSetting);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::MultiView1StartShowing(TObject *Sender) {
	// Multi Viewが現れるとき、設定リストをマルチビューに乗せ換える
	Layout1->AddObject(lbSetting);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	// フォームクリエイト時の初期設定
	TabControlSetting->ActiveTab = Setting;
	Tile->Enabled = False;
	btnGotoTile->Enabled = False;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender) {
	// トラックバーのスライドの合わせてマルチビューの幅を変える
	MultiView1->Width = 220 + TrackBar1->Value * 2;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ListBoxGroupFooter1Click(TObject *Sender) {
	// エンバカデロロゴ表示
	Form3->Height = Form1->Height;
	Form3->Width = Form1->Width;
	Form3->Top = Form1->Top + 50;
	Form3->Left = Form1->Left + 50;
	Form3->Show();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnNewGameClick(TObject *Sender) {
	///  ニューゲームボタンが押された時の処理
	SetNewGame(); // ゲーム開始処理一式の呼び出し
	SetTileRect();
	// ゲーム画面にスライド
	TabControlSetting->SetActiveTabWithTransition(Tile, TTabTransition::Slide,
		TTabTransitionDirection::Normal);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::cbTileRectChange(TObject *Sender) {
	// タイルの表示方法コンボが変更されたときのイベント
	SetTileRect();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Switch1Switch(TObject *Sender) {
	// スイッチのオンオフでスタイル の適用を切り替える
	if (Switch1->IsChecked == True) {
		Form1->StyleBook = StyleBook1;
	}
	else {
		Form1->StyleBook = NULL;
	}

}

void __fastcall TForm1::btnGotoSettingClick(TObject *Sender) {
	// 設定画面へのボタンが押されたらスライド
	TabControlSetting->SetActiveTabWithTransition(Setting,
		TTabTransition::Slide, TTabTransitionDirection::Reversed);
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
void __fastcall TForm1::btnGotoTileClick(TObject *Sender) {
	// タイル画面へのボタンが押されたらスライド
	TabControlSetting->SetActiveTabWithTransition(Tile, TTabTransition::Slide,
		TTabTransitionDirection::Normal);
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) {
	// タイルが押されたイベントきたら、ボタン情報とともにボタン押されたらの統一処理へ送る
	btnPushed(dynamic_cast<TButton*>(Sender));
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::btnPushed(TButton *pbtn)
	// ボタンがクリックされたときに呼ばれる処理
{
	// 他ボタンのアニメーション実行中かたしかめてから処理開始
	if (not FlButtonAnimation->Running && !FComp) {
		NextPosChk(pbtn);
	}
}
// ---------------------------------------------------------------------------

TmyPosition __fastcall TForm1::GetTilePosition(int tag)
	// オブジェクトのタグ情報からタイル位置を割り出す
{
	TmyPosition myPos;

	myPos.X = -1;
	myPos.Y = -1;
	// 範囲外なら -1   返しとく
	if (tag <= 0 || tag > iNumOfBtn) {
		return (myPos);
	}
	// 一列の数を割り出す
	int iCount = 1;
	int iLine = round(sqrt(iNumOfBtn));

	for (int Y = 0; Y <= (iLine - 1); Y++) {
		for (int X = 0; X <= (iLine - 1); X++) {
			if (iCount == tag) {

				myPos.X = X;
				myPos.Y = Y;
				return myPos;
			}
			iCount = iCount + 1;
		}
	}
	return myPos;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ButtonAni(TButton *pbtn, String PName, Single StpValue)
{
	// ボタンの移動のアニメーション設定
	slpx = pbtn->Position->X;
	slpy = pbtn->Position->Y; // ボタンの一時記憶
	btnMoving = pbtn;
	pbtn->AddObject(dynamic_cast<TFmxObject*>(FlButtonAnimation));
	// アニメーションをアタッチ
	FlButtonAnimation->PropertyName = PName;
	FlButtonAnimation->StopValue = StpValue;
	if (SpinBox1->Value != 0) {
		FlButtonAnimation->Duration = SpinBox1->Value / 10;
	}
	else {
		FlButtonAnimation->Duration = 0.01;
	}
	pbtn->Enabled = False;
	FlButtonAnimation->Start();
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::ChangeBtnPlace(TButton *btnFirst, TButton *btnSecond)
	// 初期ボタン配列のためのボタンシャッフル用
{
	TmyPosition posTemp;

	// Firstの場所を一時記憶
	posTemp.X = btnFirst->Position->X;
	posTemp.Y = btnFirst->Position->Y;
	int iTag = btnFirst->Tag;

	// firstをSecondの場所に移動
	btnFirst->Position->X = btnSecond->Position->X;
	btnFirst->Position->Y = btnSecond->Position->Y;
	btnFirst->Tag = btnSecond->Tag;

	// Secound を 元Firstばしょへ
	btnSecond->Position->X = posTemp.X;
	btnSecond->Position->Y = posTemp.Y;
	btnSecond->Tag = iTag;
}
// ---------------------------------------------------------------------------

bool __fastcall TForm1::CheckFin()
	// ボタンのアニメ終了後に呼ばれる予定の、ゲーム完成チェック
{
	// tag の数値とボタンの数値が全部そろってれば完成！
	for (int I = 0; I <= ScaledLayout1->Children->Count - 1; I++) {
		if (NULL != dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])) {
			if (IntToStr(dynamic_cast<TButton*>
				(ScaledLayout1->Children->Items[I])->Tag)
				!= dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Text) {
				return false;
			}
		}
	}
	return true;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::CompleteSet() {
	// ゲーム達成処理
	btnInvisibleTile->Opacity = 0; // 見えなくしておく
	btnInvisibleTile->Visible = True;
	btnInvisibleTile->SetFocus();
	btnInvisibleTile->AddObject((TFmxObject*)FlButtonAnimation); // アニメーションをアタッチ
	FlButtonAnimation->PropertyName = L"Opacity";
	FlButtonAnimation->StopValue = 0.9;
	FlButtonAnimation->Duration = 1; // 最後のタイル出現所要時間
	FlButtonAnimation->Start();
	FComp = true;

	// NewGameボタンピカピカさせる
	GlowEffectNewGame->Enabled = True;
	FloatAnimationNewGame->Start();

	// 設定行きボタンピカピカさせる
	GlowEffectGotoSetting->Enabled = True;
	FloatAnimationGotoSetting->Start();

	// タイルピカ-させる
	FloatAnimationTileGrow->StartValue = 0;
	GlowEffectTile->Enabled = True;
	FloatAnimationTileGrow->Start();
}

// ---------------------------------------------------------------------------

TButton* __fastcall TForm1::FindTagBtn(int tag)
	// ボタンの持ってるタグ情報から自分の位置を割り出す
{
	// 引数がボタンの範囲外だったらnil
	if (tag <= 0 || tag > iNumOfBtn) {
		return (NULL);
	}
	// スケールレイアウト内の子供の数だけ回す
	for (int I = 0; I <= ScaledLayout1->Children->Count - 1; I++) {
		if (NULL != dynamic_cast<TButton*>
			(ScaledLayout1->Children->Items[I])) // ボタンなら
		{
			if (dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Tag == tag) {
				return (dynamic_cast<TButton*>
					(ScaledLayout1->Children->Items[I]));
			}
		}
	}
	// ここまできて見つからなかったら失敗
	return (NULL);
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::NextPosChk(TButton *pbtn)
	// ボタンがクリックされたとき、インビジタイルが横にいるかチェックして動かす
{
	TmyPosition posTemp, myPos, InvPos;

	// 空きタイルとの差を求める
	myPos = GetTilePosition(pbtn->Tag);
	InvPos = GetTilePosition(btnInvisibleTile->Tag);

	posTemp.X = myPos.X - InvPos.X;
	posTemp.Y = myPos.Y - InvPos.Y;
	// X列の同一性チェック& ｙ列が隣か
	if (posTemp.X == 0 && posTemp.Y >= -1 && posTemp.Y <= 1) {
		// 隣ならボタン移動アニメ
		ButtonAni(pbtn, "Position.Y", btnInvisibleTile->Position->Y);
	}
	// y列の同一性チェック& ｙ列が隣か
	if (posTemp.Y == 0 && posTemp.X >= -1 && posTemp.X <= 1) {
		// 隣ならボタン移動アニメ
		ButtonAni(pbtn, "Position.X", btnInvisibleTile->Position->X);
	}
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::SetInitTilePos() {
	// ボタンの位置の初期設定とボタン位置を割り出しやすくするためのタグ設定


	// 消えたボタン情報クリア
	// タイルをきれいにならべなおす
	iNumOfBtn = 0;

	// ボタンの数を取得
	for (int I = 0; I <= ScaledLayout1->Children->Count - 1; I++) {
		if (NULL != dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])) {
			iNumOfBtn = iNumOfBtn + 1;
		}
	}

	// 一列の数を割り出す
	int iTile = round(sqrt(iNumOfBtn));

	// ボタンの位置を確認するための比較Position
	TmyPosition Pos;

	// 子供をよびだすと基本、順序良く呼び出す
	int iNum = 1;
	for (int I = 0; I <= ScaledLayout1->Children->Count - 1; I++) {
		// ボタンなら
		if (NULL != dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])) {
			// 位置設定
			dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Position->X = Pos.X;
			dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Position->Y = Pos.Y;
			//
			dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Enabled = True;
			dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Visible = True;
			// 可視化
			dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Opacity = 0.7;
			// 位置情報としてのタグデータを設定
			dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])->Text =
				IntToStr(iNum);
			dynamic_cast<TButton*>(ScaledLayout1->Children->Items[I])
				->Tag = iNum;

			iNum = iNum + 1;
		}

		if (Pos.X < (iTile * 100 - 100)) { // 一列のサイズ確認
			Pos.X = Pos.X + 100; // 列内ならX列増やす
		}
		else { // 一列うめたら先頭に戻り、２列目
			Pos.X = 0;
			Pos.Y = Pos.Y + 100;
		}
	}
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::SetInvisibleTile()
	// 全タイルからランダムで、隠し（インビジ）タイルを決めて、消す（隠す）
{
	// どのタイルを消すか抽選
	Randomize();
	int luckey = Random(iNumOfBtn) + 1;

	// ボタン隠し
	btnInvisibleTile = FindTagBtn(luckey);
	if (NULL != dynamic_cast<TButton*>(btnInvisibleTile)) {
		btnInvisibleTile->Visible = False;
		btnInvisibleTile->Enabled = False;
	}
	else {
		ShowMessage("エラー空きタイルを設定できません。アプリを再起動してください");
	}
}

// ---------------------------------------------------------------------------

void __fastcall TForm1::SetNewGame() {
	// 新しいゲームの処理一式
	SetInitTilePos(); // タイルならべ
	SetInvisibleTile(); // 空きタイル設定
	ShuffleTiles(); // タイルシャッフル
	FComp = False; // 終了フラグ初期化
	GlowEffectNewGame->Enabled = False;
	// タイル行き矢印の有効
	Tile->Enabled = True;
	btnGotoTile->Enabled = True;
	// タイルのピカピカとめる
	if (FloatAnimationTileGrow->Running) {
		FloatAnimationTileGrow->Stop();
	}
	GlowEffectTile->Enabled = False;
	// 設定行き矢印ピカピカ止める
	if (FloatAnimationGotoSetting->Running) {
		FloatAnimationGotoSetting->Stop();
	}
	GlowEffectGotoSetting->Enabled = False;

}

// ---------------------------------------------------------------------------

void __fastcall TForm1::SetTileRect() {
	// タイルの表示方法Fit（正方形）かClient か設定
	if (cbTileRect->ItemIndex == 1) {
		ScaledLayout1->Align = TAlignLayout::Fit;
		ScaledLayout1->Margins->Top = 53;
		ScaledLayout1->Height = ScaledLayout1->Width;
	}
	else {
		ScaledLayout1->Align = TAlignLayout::Client;
		ScaledLayout1->Margins->Top = 5;
	}
}

void __fastcall TForm1::ShuffleTiles()
	// 初期タイル位置の並べ替え{
{
	TmyPosition myPos;
	TButton* tmpbtnMove;
	bool Flg;

	// インビジブルタイルをランダムに動かしてタイルをシャッフルする]
	int iloopHigh = 2000; // インビジブルタイルを動かす回数
	int iLoop = 0;
	// 一列の数
	int iLine = round(sqrt(iNumOfBtn));
	Randomize();
	while (iLoop < iloopHigh) {
		Flg = False;
		// ランダムに方向決めて
		int iWay = Random(4);
		// 同じ方向に何回動かすか決める
		int iRep = Random(iLine - 1) + 1;
		for (int I = 0; I <= iRep; I++) {
			// 自分の位置をチェック
			myPos = GetTilePosition(btnInvisibleTile->Tag);

			switch (iWay) {
			case 0: // 上に
				{
					if (myPos.Y > 0) // 最上段でなければ
					{
						// 自分の上のボタンを探す
						tmpbtnMove = FindTagBtn(btnInvisibleTile->Tag - iLine);
						ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
						Flg = True;
					}
				} break;
			case 1: // 下に
				{
					if (myPos.Y < (iLine - 1)) // 最下段でなければ
					{
						// 自分の下のボタンを探す
						tmpbtnMove = FindTagBtn(btnInvisibleTile->Tag + iLine);
						ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
						Flg = True;
					}
				} break;
			case 2: // 左に
				{
					if (myPos.X > 0) // 最左列でなければ
					{
						// 自分の左のボタンを探す
						tmpbtnMove = FindTagBtn(btnInvisibleTile->Tag - 1);
						ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
						Flg = True;
					}
				} break;
			case 3: // 右に
				{
					if (myPos.X < (iLine - 1)) // 最右列でなければ
					{
						// 自分の右のボタンを探す
						tmpbtnMove = FindTagBtn(btnInvisibleTile->Tag + 1);
						ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
						Flg = True;
					}
				} break;
			}
		}
		if (Flg) {
			iLoop = iLoop + 1;
		}
	}
}
