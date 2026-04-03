object UpdInfo: TUpdInfo
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'New Update!'
  ClientHeight = 313
  ClientWidth = 324
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesktopCenter
  TextHeight = 15
  object Label1: TLabel
    Left = 19
    Top = 22
    Width = 36
    Height = 15
    Caption = 'Label1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 19
    Top = 82
    Width = 74
    Height = 15
    Caption = 'CHANGE LOG'
  end
  object Button1: TButton
    Left = 50
    Top = 264
    Width = 75
    Height = 25
    Caption = '&Ok'
    ModalResult = 1
    TabOrder = 0
  end
  object Button2: TButton
    Left = 186
    Top = 264
    Width = 75
    Height = 25
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object RichEdit1: TRichEdit
    Left = 17
    Top = 103
    Width = 290
    Height = 138
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      'RichEdit1')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 2
  end
end
