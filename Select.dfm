object FormSelect: TFormSelect
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Active Nets'
  ClientHeight = 275
  ClientWidth = 247
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnDestroy = FormDestroy
  OnShow = FormShow
  TextHeight = 15
  object ListBox1: TListBox
    Left = 6
    Top = 8
    Width = 233
    Height = 225
    ItemHeight = 15
    Sorted = True
    TabOrder = 0
    OnDblClick = ListBox1DblClick
  end
  object btnOk: TButton
    Left = 86
    Top = 242
    Width = 75
    Height = 25
    Caption = '&Ok'
    ModalResult = 1
    TabOrder = 1
  end
end
