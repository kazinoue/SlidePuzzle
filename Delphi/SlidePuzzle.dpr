program SlidePuzzle;

uses
  System.StartUpCopy,
  FMX.Forms,
  Num_lineup16_Unit1 in 'Num_lineup16_Unit1.pas' {Form1},
  TilesVersionUnit2 in 'TilesVersionUnit2.pas' {Form2};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.Run;
end.
