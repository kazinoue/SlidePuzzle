unit Num_lineup16_Unit1;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes,
  System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs,
  FMX.Controls.Presentation, FMX.StdCtrls, FMX.Layouts, FMX.Ani, FMX.TabControl,
  FMX.Edit, FMX.EditBox, FMX.SpinBox, FMX.Effects, FMX.ListBox, FMX.ScrollBox,
  FMX.Memo, System.Actions, FMX.ActnList, FMX.Gestures, FMX.Objects,
  FMX.MultiView;

type
  TmyPosition = record
    X: Single;
    Y: Single;
  end;

type
  TForm1 = class(TForm)
    ScaledLayout1: TScaledLayout;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    FlButtonAnimation: TFloatAnimation;
    Button10: TButton;
    Button11: TButton;
    Button12: TButton;
    Button13: TButton;
    Button14: TButton;
    Button15: TButton;
    Button16: TButton;
    TabControlSetting: TTabControl;
    Tile: TTabItem;
    Setting: TTabItem;
    GlowEffectTile: TGlowEffect;
    FloatAnimationTileGrow: TFloatAnimation;
    tbSetting: TToolBar;
    tbTile: TToolBar;
    Label1: TLabel;
    Label2: TLabel;
    btnNewGame: TButton;
    GlowEffectNewGame: TGlowEffect;
    FloatAnimationNewGame: TFloatAnimation;
    SpinBox1: TSpinBox;
    cbTileRect: TComboBox;
    lbSetting: TListBox;
    ListBoxItem1: TListBoxItem;
    ListBoxItem2: TListBoxItem;
    ListBoxItem3: TListBoxItem;
    btnGotoSetting: TButton;
    btnGotoTile: TButton;
    GlowEffectGotoSetting: TGlowEffect;
    FloatAnimationGotoSetting: TFloatAnimation;
    GestureManager1: TGestureManager;
    ActionList1: TActionList;
    NextTabAction1: TNextTabAction;
    PreviousTabAction1: TPreviousTabAction;
    ListBoxGroupHeader1: TListBoxGroupHeader;
    ListBoxGroupHeader2: TListBoxGroupHeader;
    ListBoxItem4: TListBoxItem;
    Switch1: TSwitch;
    StyleBook1: TStyleBook;
    ListBoxGroupFooter1: TListBoxGroupFooter;
    MultiView1: TMultiView;
    btnMaster: TButton;
    ToolBar1: TToolBar;
    Label3: TLabel;
    TrackBar1: TTrackBar;
    Layout1: TLayout;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure FlButtonAnimationFinish(Sender: TObject);
    procedure btnNewGameClick(Sender: TObject);
    procedure cbTileRectChange(Sender: TObject);
    procedure btnGotoSettingClick(Sender: TObject);
    procedure btnGotoTileClick(Sender: TObject);
    procedure NextTabAction1Update(Sender: TObject);
    procedure PreviousTabAction1Update(Sender: TObject);
    procedure Switch1Switch(Sender: TObject);
    procedure ListBoxGroupFooter1Click(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
    procedure MultiView1StartShowing(Sender: TObject);
    procedure MultiView1Hidden(Sender: TObject);
  private
    { private 宣言 }
    procedure SetNewGame; //新規ゲーム開始手続呼び出しのための、ほか手続きまとめて呼び出し
    procedure SetInitTilePos; //タイル位置の初期整列
    procedure SetInvisibleTile;  //隠しタイル決定
    procedure ShuffleTiles;       //タイル位置シャッフル
    procedure ChangeBtnPlace(btnFirst: TButton; btnSecond: TButton); //シャッフル時にボタンの位置入れ替えのための手続き

    procedure btnPushed(btn: TButton);     //タイルがクリックされたたらポジションチェックを呼び出すための手続き
    procedure NextPosChk(btn: TButton);     //横が見えないタイルかチェック
    procedure ButtonAni(btn: TButton; PName: string; StpValue: Single);   //タイル移動アニメの手続き
    function CheckFin: Boolean;     //タイルならべが完成しているかチェック
    procedure CompleteSet;           //完成した場合の処理

    procedure SetTileRect;    //タイル表示方法の切り替え（正方形かフィットか）
    function FindTagBtn(tag: Integer): TButton;     //ボタンの持っているタグ情報から対象のボタンオブジェクト見つける
    function GetTilePosition(tag: Integer): TmyPosition;     //タグ情報からボタンの座標情報を見つける

  public
    { public 宣言 }
  end;

var
  Form1: TForm1;

implementation

{$R *.fmx}

uses TilesVersionUnit2;　//エンバカデロ　ロゴフォーム呼び出すためのUses

var     //グローバル変数
  btnMoving, btnInvisibleTile: TButton;   //動いているボタン、消しているボタンを覚えとく
  iNumOfBtn: Integer;      //タイル数を覚えておく
  FComp: Boolean;          //完成しているかフラグ
  slpx, slpy: Single;

procedure TForm1.btnGotoSettingClick(Sender: TObject);
begin
//設定画面へのボタンが押されたらスライド
  TabControlSetting.SetActiveTabWithTransition(Setting, TTabTransition.Slide,
    TTabTransitionDirection.Reversed);
end;

procedure TForm1.btnGotoTileClick(Sender: TObject);
begin
//タイル画面へのボタンが押されたらスライド
  TabControlSetting.SetActiveTabWithTransition(Tile, TTabTransition.Slide,
    TTabTransitionDirection.Normal);
end;

procedure TForm1.Button1Click(Sender: TObject);
//タイルが押されたイベントきたら、ボタン情報とともにボタン押されたらの統一処理へ送る
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button2Click(Sender: TObject);
//以下同文
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
  btnPushed(TButton(Sender));
end;

procedure TForm1.cbTileRectChange(Sender: TObject);
begin
//タイルの表示方法コンボが変更されたときのイベント
  SetTileRect;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
//フォームクリエイト時の初期設定
  TabControlSetting.ActiveTab := Setting;
  Tile.Enabled := False;
  btnGotoTile.Enabled := False;
end;

function TForm1.GetTilePosition(tag: Integer): TmyPosition;
//オブジェクトのタグ情報からタイル位置を割り出す
var
  iLine: Integer;
  myPos: TmyPosition;
  Y, X, iCount: Integer;
begin
  myPos.X := -1;
  myPos.Y := -1;
  // 範囲外なら -1   返しとく
  if (tag <= 0) or (tag > iNumOfBtn) then
    Exit(myPos);

  // 一列の数を割り出す
  iCount := 1;
  iLine := round(sqrt(iNumOfBtn));

  for Y := 0 to (iLine - 1) do
  begin
    for X := 0 to (iLine - 1) do
    begin
      if iCount = tag then
      begin
        myPos.X := X;
        myPos.Y := Y;
        Exit(myPos);
      end;
      iCount := iCount + 1;
    end;
  end;
  Result := myPos;
end;

procedure TForm1.ListBoxGroupFooter1Click(Sender: TObject);
begin
//エンバカデロロゴ表示
  Form2.Height := Form1.Height;
  Form2.Width := Form1.Width;
  Form2.Top := Form1.Top + 50;
  Form2.Left := Form1.Left +50;
  Form2.Show;
end;

procedure TForm1.MultiView1Hidden(Sender: TObject);
begin
//マルチビューが隠れるとき、設定リストをもとの設定タブの返す
  setting.AddObject(lbSetting);
end;

procedure TForm1.MultiView1StartShowing(Sender: TObject);
begin
// Multi Viewが現れるとき、設定リストをマルチビューに乗せ換える
 if lbSetting = nil then
 begin
   lbSetting.Create(self);
 end;

 Layout1.AddObject(lbSetting);
end;

procedure TForm1.ButtonAni(btn: TButton; PName: string; StpValue: Single);
begin
  // ボタンの移動のアニメーション設定
  slpx := btn.Position.X;
  slpy := btn.Position.Y; // ボタンの一時記憶
  btnMoving := btn;
  btn.AddObject(TFmxObject(FlButtonAnimation)); // アニメーションをアタッチ
  FlButtonAnimation.PropertyName := PName;
  FlButtonAnimation.StopValue := StpValue;
  if SpinBox1.Value <> 0 then
    FlButtonAnimation.Duration := SpinBox1.Value / 10
  else
    FlButtonAnimation.Duration := 0.01;
  btn.Enabled := False;
  FlButtonAnimation.Start;
end;



procedure TForm1.ChangeBtnPlace(btnFirst, btnSecond: TButton);
//初期ボタン配列のためのボタンシャッフル用
var
  posTemp: TmyPosition;
  iTag: Integer;
begin
  // Firstの場所を一時記憶
  posTemp.X := btnFirst.Position.X;
  posTemp.Y := btnFirst.Position.Y;
  iTag := btnFirst.tag;

  // firstをSecondの場所に移動
  btnFirst.Position.X := btnSecond.Position.X;
  btnFirst.Position.Y := btnSecond.Position.Y;
  btnFirst.tag := btnSecond.tag;

  // Secound を 元Firstばしょへ
  btnSecond.Position.X := posTemp.X;
  btnSecond.Position.Y := posTemp.Y;
  btnSecond.tag := iTag;
end;

function TForm1.CheckFin: Boolean;
//ボタンのアニメ終了後に呼ばれる予定の、ゲーム完成チェック
var
  I: Integer;
begin
  // tag の数値とボタンの数値が全部そろってれば完成！
  for I := 0 to ScaledLayout1.Children.Count - 1 do
  begin
    if (ScaledLayout1.Children.Items[I] is TButton) then
    begin
      if TButton(ScaledLayout1.Children.Items[I]).tag.ToString <>
        TButton(ScaledLayout1.Children.Items[I]).Text then
        Exit(False);
    end;
  end;
  Result := True;

end;

procedure TForm1.CompleteSet;
begin
  // ゲーム達成処理
  btnInvisibleTile.Opacity := 0; // 見えなくしておく
  btnInvisibleTile.Visible := True;
  btnInvisibleTile.SetFocus;
  btnInvisibleTile.AddObject(TFmxObject(FlButtonAnimation)); // アニメーションをアタッチ
  FlButtonAnimation.PropertyName := 'Opacity';
  FlButtonAnimation.StopValue := 0.9;
  FlButtonAnimation.Duration := 1; // 最後のタイル出現所要時間
  FlButtonAnimation.Start;
  FComp := True;

  // NewGameボタンピカピカさせる
  GlowEffectNewGame.Enabled := True;
  FloatAnimationNewGame.Start;

  // 設定行きボタンピカピカさせる
  GlowEffectGotoSetting.Enabled := True;
  FloatAnimationGotoSetting.Start;

  // タイルピカ-させる
  FloatAnimationTileGrow.StartValue := 0;
  GlowEffectTile.Enabled := True;
  FloatAnimationTileGrow.Start;
end;

function TForm1.FindTagBtn(tag: Integer): TButton;
//ボタンの持ってるタグ情報から自分の位置を割り出す
var
  I: Integer;
begin
  // 引数がボタンの範囲外だったらnil
  if (tag <= 0) or (tag > iNumOfBtn) then
    Exit(nil);
  // スケールレイアウト内の子供の数だけ回す
  for I := 0 to ScaledLayout1.Children.Count - 1 do
  begin
    if (ScaledLayout1.Children.Items[I] is TButton) then // ボタンなら
    begin
      if TButton(ScaledLayout1.Children.Items[I]).tag = tag then
        Exit(TButton(ScaledLayout1.Children.Items[I]));
    end;
  end;
  // ここまできて見つからなかったら失敗
  Result := nil;
end;

procedure TForm1.FlButtonAnimationFinish(Sender: TObject);
//ボタン移動のアニメーション完了後の処理
var
  iTmpTag: Integer;
begin
  // 移動後のボタン有効化と、インビシブルタイルの移動
  if (not FComp) then
  begin
    btnMoving.Enabled := True;
    // 移動が正しくできたかチェック（インビジの位置まで動いたか)
    if (btnMoving.Position.X = btnInvisibleTile.Position.X) and
      (btnMoving.Position.Y = btnInvisibleTile.Position.Y) then
    begin
      // インビジタイルの移動
      iTmpTag := btnMoving.tag;
      btnInvisibleTile.Position.X := slpx;
      btnInvisibleTile.Position.Y := slpy;
      btnMoving.tag := btnInvisibleTile.tag;
      btnInvisibleTile.tag := iTmpTag;
    end;

  end;
  // コンプリートチェック
  if CheckFin and (not FComp) then
    CompleteSet;
end;

procedure TForm1.NextPosChk(btn: TButton);
//ボタンがクリックされたとき、インビジタイルが横にいるかチェックして動かす
var
  posTemp, myPos, InvPos: TmyPosition;
begin
  // 空きタイルとの差を求める
  myPos := GetTilePosition(btn.tag);
  InvPos := GetTilePosition(btnInvisibleTile.tag);

  posTemp.X := myPos.X - InvPos.X;
  posTemp.Y := myPos.Y - InvPos.Y;
  // X列の同一性チェック& ｙ列が隣か
  if (posTemp.X = 0) and (posTemp.Y >= -1) and (posTemp.Y <= 1) then
  begin
    // 隣ならボタン移動アニメ
    ButtonAni(btn, 'Position.Y', btnInvisibleTile.Position.Y);
  end;
  // y列の同一性チェック& ｙ列が隣か
  if (posTemp.Y = 0) and (posTemp.X >= -1) and (posTemp.X <= 1) then
  begin
    // 隣ならボタン移動アニメ
    ButtonAni(btn, 'Position.X', btnInvisibleTile.Position.X);
  end;
end;

procedure TForm1.NextTabAction1Update(Sender: TObject);
//ジェスチャーで呼び出されるアクション
begin
  // ジェスチャーで右から左。タイル画面呼び出し
  if (btnGotoTile.Enabled = True) and (TabControlSetting.TabIndex = 0) then
    TabControlSetting.SetActiveTabWithTransition(Tile, TTabTransition.Slide,
      TTabTransitionDirection.Normal);
end;

procedure TForm1.PreviousTabAction1Update(Sender: TObject);
//ジェスチャーで呼び出されるアクション
begin
  // ジェスチャーで左から右。設定画面呼び出し
  if (btnGotoSetting.Enabled = True) and (TabControlSetting.TabIndex = 1) then
    TabControlSetting.SetActiveTabWithTransition(Setting, TTabTransition.Slide,
      TTabTransitionDirection.Reversed);
end;

procedure TForm1.SetInitTilePos;
//ボタンの位置の初期設定とボタン位置を割り出しやすくするためのタグ設定
var
  I: Integer;
  iTile: Integer;
  Pos: TmyPosition;
  iNum: Integer;
begin
  // 消えたボタン情報クリア
  // タイルをきれいにならべなおす
  iNumOfBtn := 0;

  // ボタンの数を取得
  for I := 0 to ScaledLayout1.Children.Count - 1 do
  begin
    if ScaledLayout1.Children.Items[I] is TButton then
      iNumOfBtn := iNumOfBtn + 1;
  end;

  // 一列の数を割り出す
  iTile := round(sqrt(iNumOfBtn));

  // ボタンの位置を確認するための比較Position
  Pos.X := 0;
  Pos.Y := 0;

  // 子供をよびだすと基本、順序良く呼び出す
  iNum := 1;
  for I := 0 to ScaledLayout1.Children.Count - 1 do
  begin
    // ボタンなら
    if (ScaledLayout1.Children.Items[I] is TButton) then
    begin
      // 位置設定
      TButton(ScaledLayout1.Children.Items[I]).Position.X := Pos.X;
      TButton(ScaledLayout1.Children.Items[I]).Position.Y := Pos.Y;
      //
      TButton(ScaledLayout1.Children.Items[I]).Enabled := True;
      TButton(ScaledLayout1.Children.Items[I]).Visible := True;
      // 可視化
      TButton(ScaledLayout1.Children.Items[I]).Opacity := 0.7;
      // 位置情報としてのタグデータを設定
      TButton(ScaledLayout1.Children.Items[I]).Text := iNum.ToString;
      TButton(ScaledLayout1.Children.Items[I]).tag := iNum;

      iNum := iNum + 1;
    end;
    if Pos.X < (iTile * 100 - 100) then // 一列のサイズ確認
    begin
      Pos.X := Pos.X + 100; // 列内ならX列増やす
    end
    else
    begin // 一列うめたら先頭に戻り、２列目
      Pos.X := 0;
      Pos.Y := Pos.Y + 100;
    end;
  end;
end;

procedure TForm1.SetInvisibleTile;
//全タイルからランダムで、隠し（インビジ）タイルを決めて、消す（隠す）
var
  luckey: Integer;
begin

  // どのタイルを消すか抽選
  Randomize;
  luckey := Random(iNumOfBtn) + 1;

  // ボタン隠し
  btnInvisibleTile := FindTagBtn(luckey);
  if btnInvisibleTile is TButton then
  begin
    btnInvisibleTile.Visible := False;
    btnInvisibleTile.Enabled := False;
  end
  else
  begin
    ShowMessage('エラー空きタイルを設定できません。アプリを再起動してください');
  end;
end;

procedure TForm1.SetNewGame;
begin
  // 新しいゲームの処理一式
  SetInitTilePos; // タイルならべ
  SetInvisibleTile; // 空きタイル設定
  ShuffleTiles; // タイルシャッフル
  FComp := False; // 終了フラグ初期化
  GlowEffectNewGame.Enabled := False;
  // タイル行き矢印の有効
  Tile.Enabled := True;
  btnGotoTile.Enabled := True;
  // タイルのピカピカとめる
  if FloatAnimationTileGrow.Running then
    FloatAnimationTileGrow.Stop;
  GlowEffectTile.Enabled := False;
  // 設定行き矢印ピカピカ止める
  if FloatAnimationGotoSetting.Running then
    FloatAnimationGotoSetting.Stop;
  GlowEffectGotoSetting.Enabled := False;

end;

procedure TForm1.SetTileRect;
begin
  // タイルの表示方法Fit（正方形）かClient か設定
  if cbTileRect.ItemIndex = 1 then
  begin
    ScaledLayout1.Align := TAlignLayout.Fit;
    ScaledLayout1.Margins.Top := 53;
    ScaledLayout1.Height := ScaledLayout1.Width;
  end
  else
  begin
    ScaledLayout1.Align := TAlignLayout.Client;
    ScaledLayout1.Margins.Top := 5;
  end;
end;

procedure TForm1.ShuffleTiles;
//初期タイル位置の並べ替え
var
  iLoop: Integer;
  iloopHigh: Integer;
  iWay, iRep: Integer;
  iLine: Integer;
  myPos: TmyPosition;
  tmpbtnMove: TButton;
  I: Integer;
  Flg: Boolean;
begin
  // インビジブルタイルをランダムに動かしてタイルをシャッフルする]
  iloopHigh := 2000; // インビジブルタイルを動かす回数
  iLoop := 0;
  // 一列の数
  iLine := round(sqrt(iNumOfBtn));
  Randomize;
  while iLoop < iloopHigh do
  begin
    Flg := False;
    // ランダムに方向決めて
    iWay := Random(4);
    // 同じ方向に何回動かすか決める
    iRep := Random(iLine - 1) + 1;
    for I := 0 to iRep do
    begin
      // 自分の位置をチェック
      myPos := GetTilePosition(btnInvisibleTile.tag);

      case iWay of
        0: // 上に
          begin
            if myPos.Y > 0 then // 最上段でなければ
            begin
              // 自分の上のボタンを探す
              tmpbtnMove := FindTagBtn(btnInvisibleTile.tag - iLine);
              ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
              Flg := True;
            end
          end;
        1: // 下に
          begin
            if myPos.Y < (iLine - 1) then // 最下段でなければ
            begin
              // 自分の下のボタンを探す
              tmpbtnMove := FindTagBtn(btnInvisibleTile.tag + iLine);
              ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
              Flg := True;
            end;
          end;

        2: // 左に
          begin
            if myPos.X > 0 then // 最左列でなければ
            begin
              // 自分の左のボタンを探す
              tmpbtnMove := FindTagBtn(btnInvisibleTile.tag - 1);
              ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
              Flg := True;
            end;
          end;

        3: // 右に
          begin
            if myPos.X < (iLine - 1) then // 最右列でなければ
            begin
              // 自分の右のボタンを探す
              tmpbtnMove := FindTagBtn(btnInvisibleTile.tag + 1);
              ChangeBtnPlace(tmpbtnMove, btnInvisibleTile);
              Flg := True;
            end;
          end;
      end;
    end;
    if Flg then
      iLoop := iLoop + 1;
  end;
end;

procedure TForm1.Switch1Switch(Sender: TObject);
//スイッチのオンオフでスタイル の適用を切り替える
begin
  if Switch1.IsChecked then
  begin
    Form1.StyleBook := StyleBook1;
  end
  else
  begin
    Form1.StyleBook := nil;
  end;
end;

procedure TForm1.TrackBar1Change(Sender: TObject);
//トラックバーのスライドの合わせてマルチビューの幅を変える
begin
 MultiView1.Width := 220 + TrackBar1.Value *2;
end;

procedure TForm1.btnNewGameClick(Sender: TObject);
begin
  ///  ニューゲームボタンが押された時の処理
  SetNewGame; // ゲーム開始処理一式の呼び出し
  SetTileRect;
  //ゲーム画面にスライド
  TabControlSetting.SetActiveTabWithTransition(Tile, TTabTransition.Slide,
    TTabTransitionDirection.Normal);
end;

procedure TForm1.btnPushed(btn: TButton);
//ボタンがクリックされたときに呼ばれる処理
begin
  // 他ボタンのアニメーション実行中かたしかめてから処理開始
  if (not FlButtonAnimation.Running) and (not FComp) then
    NextPosChk(btn);
end;

end.
