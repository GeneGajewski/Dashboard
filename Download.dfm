object DL: TDL
  Left = 0
  Top = 0
  Caption = 'DL'
  ClientHeight = 166
  ClientWidth = 501
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  TextHeight = 15
  object Label1: TLabel
    Left = 16
    Top = 32
    Width = 56
    Height = 15
    Caption = 'LblPercent'
  end
  object ProgressBar1: TProgressBar
    Left = 16
    Top = 64
    Width = 465
    Height = 21
    TabOrder = 0
  end
  object BtnAbort: TButton
    Left = 216
    Top = 104
    Width = 75
    Height = 25
    Caption = '&Abort'
    TabOrder = 1
    TabStop = False
    OnClick = BtnAbortClick
  end
end
