object FormPrefs: TFormPrefs
  Left = 0
  Top = 0
  Caption = 'Preferences'
  ClientHeight = 315
  ClientWidth = 479
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnShow = FormShow
  TextHeight = 15
  object label: TLabel
    Left = 280
    Top = 23
    Width = 25
    Height = 15
    Caption = '&Style'
  end
  object Label1: TLabel
    Left = 280
    Top = 224
    Width = 39
    Height = 15
    Caption = '&Refresh'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 225
    Height = 249
    Caption = 'Fields'
    TabOrder = 0
    object ckbSerialNo: TCheckBox
      Left = 24
      Top = 32
      Width = 97
      Height = 17
      Caption = 'Serial No'
      TabOrder = 0
    end
    object ckbCall: TCheckBox
      Tag = 1
      Left = 24
      Top = 55
      Width = 97
      Height = 17
      Caption = 'Call'
      TabOrder = 1
    end
    object ckbState: TCheckBox
      Tag = 2
      Left = 24
      Top = 80
      Width = 97
      Height = 17
      Caption = 'State'
      TabOrder = 2
    end
    object ckbRemarks: TCheckBox
      Tag = 3
      Left = 24
      Top = 103
      Width = 97
      Height = 17
      Caption = 'Remarks'
      TabOrder = 3
    end
    object ckbInfo: TCheckBox
      Tag = 4
      Left = 24
      Top = 128
      Width = 97
      Height = 17
      Caption = 'Info'
      TabOrder = 4
    end
    object ckbCity: TCheckBox
      Tag = 5
      Left = 24
      Top = 151
      Width = 97
      Height = 17
      Caption = 'City'
      TabOrder = 5
    end
    object ckbName: TCheckBox
      Tag = 6
      Left = 24
      Top = 176
      Width = 97
      Height = 17
      Caption = 'Name'
      TabOrder = 6
    end
    object ckbStatus: TCheckBox
      Tag = 7
      Left = 24
      Top = 199
      Width = 97
      Height = 17
      Caption = 'Status'
      TabOrder = 7
    end
    object ckbPreferred: TCheckBox
      Tag = 15
      Left = 127
      Top = 199
      Width = 97
      Height = 17
      Caption = 'Preferred'
      TabOrder = 8
    end
    object ckbDXCC: TCheckBox
      Tag = 14
      Left = 127
      Top = 176
      Width = 97
      Height = 17
      Caption = 'DXCC'
      TabOrder = 9
    end
    object ckbCountry: TCheckBox
      Tag = 13
      Left = 127
      Top = 150
      Width = 97
      Height = 17
      Caption = 'Country'
      TabOrder = 10
    end
    object ckbMemberID: TCheckBox
      Tag = 12
      Left = 127
      Top = 127
      Width = 90
      Height = 17
      Caption = 'Member ID'
      TabOrder = 11
    end
    object ckbZip: TCheckBox
      Tag = 11
      Left = 127
      Top = 102
      Width = 97
      Height = 17
      Caption = 'Zip'
      TabOrder = 12
    end
    object ckbStreet: TCheckBox
      Tag = 10
      Left = 127
      Top = 79
      Width = 97
      Height = 17
      Caption = 'Street'
      TabOrder = 13
    end
    object ckbGrid: TCheckBox
      Tag = 9
      Left = 127
      Top = 55
      Width = 97
      Height = 17
      Caption = 'Grid'
      TabOrder = 14
    end
    object ckbCounty: TCheckBox
      Tag = 8
      Left = 127
      Top = 31
      Width = 97
      Height = 17
      Caption = 'County'
      TabOrder = 15
    end
  end
  object cbStyles: TComboBox
    Left = 280
    Top = 44
    Width = 169
    Height = 23
    AutoCloseUp = True
    Style = csDropDownList
    Sorted = True
    TabOrder = 1
    TabStop = False
    OnChange = cbStylesChange
  end
  object GroupBox2: TGroupBox
    Left = 280
    Top = 86
    Width = 136
    Height = 115
    Caption = 'Time'
    TabOrder = 2
    object rb12: TRadioButton
      Left = 24
      Top = 32
      Width = 113
      Height = 17
      Caption = '12 Hour'
      TabOrder = 0
      OnClick = rb12Click
    end
    object rb24: TRadioButton
      Left = 24
      Top = 55
      Width = 113
      Height = 17
      Caption = '24 Hour'
      TabOrder = 1
      OnClick = rb24Click
    end
    object ckbUTC: TCheckBox
      Left = 24
      Top = 78
      Width = 97
      Height = 17
      Caption = 'UTC'
      TabOrder = 2
      OnClick = ckbUTCClick
    end
  end
  object btnOk: TButton
    Left = 122
    Top = 279
    Width = 75
    Height = 25
    Caption = '&Ok'
    TabOrder = 3
    OnClick = btnOkClick
  end
  object btnCancel: TButton
    Left = 282
    Top = 279
    Width = 75
    Height = 25
    Caption = 'C&ancel'
    TabOrder = 4
    OnClick = btnCancelClick
  end
  object CSpinEdit1: TCSpinEdit
    Left = 280
    Top = 241
    Width = 169
    Height = 24
    MaxValue = 180
    MinValue = 20
    TabOrder = 5
    Value = 20
  end
end
