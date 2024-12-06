object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'DASHBOARD'
  ClientHeight = 624
  ClientWidth = 976
  Color = clBtnFace
  Constraints.MinHeight = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 15
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 976
    Height = 193
    Align = alTop
    BevelOuter = bvNone
    Constraints.MinHeight = 193
    Constraints.MinWidth = 976
    ShowCaption = False
    TabOrder = 0
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 553
      Height = 193
      Align = alLeft
      BevelOuter = bvNone
      Caption = 'Panel1'
      Constraints.MinHeight = 193
      Constraints.MinWidth = 553
      ShowCaption = False
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 19
        Width = 19
        Height = 15
        Caption = 'Net'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label2: TLabel
        Left = 16
        Top = 75
        Width = 23
        Height = 15
        Caption = 'Freq'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label3: TLabel
        Left = 112
        Top = 75
        Width = 27
        Height = 15
        Caption = 'Band'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label4: TLabel
        Left = 208
        Top = 75
        Width = 31
        Height = 15
        Caption = 'Mode'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label5: TLabel
        Left = 352
        Top = 75
        Width = 61
        Height = 15
        Caption = 'Net Control'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label6: TLabel
        Left = 352
        Top = 125
        Width = 37
        Height = 15
        Caption = 'Logger'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label7: TLabel
        Left = 16
        Top = 125
        Width = 56
        Height = 15
        Caption = 'Subcribers'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object edFreq: TEdit
        Left = 16
        Top = 96
        Width = 81
        Height = 23
        TabStop = False
        ReadOnly = True
        TabOrder = 0
      end
      object edBand: TEdit
        Left = 112
        Top = 96
        Width = 81
        Height = 23
        TabStop = False
        ReadOnly = True
        TabOrder = 1
      end
      object edMode: TEdit
        Left = 208
        Top = 96
        Width = 81
        Height = 23
        TabStop = False
        ReadOnly = True
        TabOrder = 2
      end
      object edNetControl: TEdit
        Left = 352
        Top = 96
        Width = 185
        Height = 23
        TabStop = False
        ReadOnly = True
        TabOrder = 3
      end
      object edLogger: TEdit
        Left = 352
        Top = 144
        Width = 185
        Height = 23
        TabStop = False
        ReadOnly = True
        TabOrder = 4
      end
      object edSubscribe: TEdit
        Left = 16
        Top = 144
        Width = 81
        Height = 23
        TabStop = False
        ReadOnly = True
        TabOrder = 5
      end
      object btnNets: TButton
        Left = 462
        Top = 39
        Width = 75
        Height = 25
        Caption = '&Nets'
        TabOrder = 6
        OnClick = btnNetsClick
      end
      object edNET: TEdit
        Left = 16
        Top = 40
        Width = 416
        Height = 23
        TabStop = False
        ReadOnly = True
        TabOrder = 7
      end
    end
    object Panel4: TPanel
      Left = 627
      Top = 0
      Width = 349
      Height = 193
      Align = alRight
      BevelOuter = bvNone
      Caption = 'Panel4'
      Constraints.MinWidth = 349
      ShowCaption = False
      TabOrder = 1
      object panDate: TPanel
        Left = -2
        Top = 23
        Width = 352
        Height = 20
        BevelOuter = bvNone
        Caption = 'panDate'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object panZone: TPanel
        Left = -2
        Top = 121
        Width = 353
        Height = 24
        BevelOuter = bvNone
        BorderWidth = 1
        Caption = 'Panel3'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        VerticalAlignment = taAlignTop
      end
      object panClockBorder: TPanel
        Left = 48
        Top = 72
        Width = 252
        Height = 47
        BevelOuter = bvLowered
        BevelWidth = 4
        Caption = 'panClockBorder'
        TabOrder = 2
        object panClock: TPanel
          Left = 4
          Top = 4
          Width = 244
          Height = 39
          Align = alClient
          BevelOuter = bvNone
          Caption = '23:59:00 PM'
          Color = clBlack
          DoubleBuffered = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clOrangered
          Font.Height = -37
          Font.Name = 'alarm clock'
          Font.Style = []
          ParentBackground = False
          ParentDoubleBuffered = False
          ParentFont = False
          TabOrder = 0
          StyleName = 'Windows'
        end
      end
    end
  end
  object DBGrid1: TDBGrid
    AlignWithMargins = True
    Left = 10
    Top = 196
    Width = 956
    Height = 405
    Margins.Left = 10
    Margins.Right = 10
    Align = alClient
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgTitleClick, dgTitleHotTrack, dgThumbTracking]
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'SerialNo'
        Title.Caption = 'Serial No'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Callsign'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'State'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Remarks'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'QSLInfo'
        Title.Caption = 'Info'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CityCountry'
        Title.Caption = 'City'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'FirstName'
        Title.Caption = 'Name'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Status'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'County'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Grid'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Street'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Zip'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MemberID'
        Title.Caption = 'Member ID'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Country'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DXCC'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PreferredName'
        Title.Caption = 'Preferred Name'
        Visible = True
      end>
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 604
    Width = 976
    Height = 20
    Panels = <
      item
        Alignment = taRightJustify
        Bevel = pbNone
        Style = psOwnerDraw
        Text = 'LED'
        Width = 24
      end
      item
        Bevel = pbNone
        Text = 'Ready'
        Width = 10
      end>
    OnDrawPanel = StatusBar1DrawPanel
  end
  object ClockTimer: TTimer
    Enabled = False
    OnTimer = MasterTick
    Left = 663
    Top = 140
  end
  object ImageList1: TImageList
    Left = 558
    Top = 35
    Bitmap = {
      494C010102000800040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BABABA68676767E8585858FF585858FE8F8F8FAAF7F7F70C0000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000A2A9E568313FC7E81D2EC4FF1D2DC3FE6873D5AAF4F5FC0C0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      C657595959FF606060FF636363FF656565FF646464FF626262FF5C5C5CFF6B6B
      6BE100000000000000000000000000000000000000000000000000000000B1B7
      E9571D2EC7FF1F32D5FF2033DEFF2134E1FF2033E0FF2033D9FF1F2FCDFF3745
      C8E1000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000A5A5A5885C5C
      5CFF656565FF6B6B6BFF6F6F6FFF707070FF707070FF6D6D6DFF686868FF6161
      61FF585858FE0000000000000000000000000000000000000000868FDD881F2F
      CEFF2134E1FF2337EEFF2439F6FF253AF9FF2439F8FF2338F2FF2235E8FF2032
      D7FF1D2DC3FE0000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000ECECEC1D5B5B5BFF6666
      66FF6E6E6EFF757575FF797979FF7B7B7BFF7A7A7AFF777777FF717171FF6A6A
      6AFF616161FF6B6B6BE1000000000000000000000000E5E7F71D1E2FCCFF2134
      E3FF2439F6FF293EFEFF3044FFFF3347FFFF3246FFFF2D42FFFF253AFBFF2236
      ECFF2032D7FF3745C8E100000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005A5A5AFB636363FF6D6D
      6DFF777777FF7E7E7EFF808080FF818181FF818181FF7F7F7FFF7B7B7BFF7171
      71FF686868FF5C5C5CFFF7F7F70C00000000000000002030C3FB2033DDFF2438
      F3FF2C41FEFF364BFFFF3B4EFFFF3C4FFFFF3C4FFFFF394DFFFF3246FFFF253A
      FBFF2235E8FF1F2FCDFFF4F5FC0C000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005C5C5CFF686868FF7272
      72FF7D7D7DFF818181FF838383FF838383FF838383FF828282FF7F7F7FFF7777
      77FF6D6D6DFF626262FF8F8F8FAA00000000000000001E2FCCFF2235E8FF263B
      FDFF3549FFFF3C4FFFFF3F52FFFF4052FFFF3F52FFFF3E51FFFF394DFFFF2D42
      FFFF2338F2FF2033D9FF6873D5AA000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E4E4E4295F5F5FFF6B6B6BFF7676
      76FF7F7F7FFF828282FF838383FF838383FF838383FF838383FF818181FF7A7A
      7AFF707070FF646464FF585858FE00000000DADDF5291F31D3FF2337EEFF2B3F
      FEFF384CFFFF3F51FFFF4052FFFF4052FFFF4052FFFF3F52FFFF3C4FFFFF3246
      FFFF2439F8FF2033E0FF1D2DC3FE000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D7D7D73C606060FF6C6C6CFF7676
      76FF7F7F7FFF838383FF838383FF838383FF838383FF838383FF818181FF7B7B
      7BFF707070FF656565FF585858FF00000000C9CDF03C1F32D4FF2337F0FF2B40
      FFFF394DFFFF3F52FFFF4052FFFF4052FFFF4052FFFF4052FFFF3C4FFFFF3347
      FFFF253AF9FF2134E1FF1D2EC4FF000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7F7F70B696969FF6A6A6AFF7474
      74FF7E7E7EFF828282FF838383FF838383FF838383FF838383FF808080FF7979
      79FF6F6F6FFF646464FF676767E800000000F5F5FC0B2E3ED4FF2236ECFF293E
      FEFF374BFFFF3E51FFFF4052FFFF4052FFFF4052FFFF3F52FFFF3B4EFFFF3044
      FFFF2439F6FF2034DEFF313FC7E8000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000737373FF939393FF9A9A
      9AFF949494FF8C8C8CFF868686FF838383FF838383FF878787FF8D8D8DFF9494
      94FF979797FF8F8F8FFFBABABA680000000000000000404ED0FF6370ECFF6574
      FBFF5A6AFFFF4D5FFFFF4456FFFF3F52FFFF4053FFFF4557FFFF4E60FFFF5969
      FEFF6472F3FF626FE1FFA2A9E568000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008A8A8AB2A5A5A5FFAAAA
      AAFFAFAFAFFFB4B4B4FFB6B6B6FFB6B6B6FFB6B6B6FFB5B5B5FFB1B1B1FFADAD
      ADFFA7A7A7FF7C7C7CFF000000000000000000000000616DD3B2808AE7FF818D
      F5FF8490FEFF8A96FFFF8D99FFFF8E99FFFF8E99FFFF8C98FFFF8793FEFF828E
      F9FF808BEEFF4D5AD2FF00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000747474FFBBBB
      BBFFBFBFBFFFC1C1C1FFC3C3C3FFC4C4C4FFC4C4C4FFC2C2C2FFC0C0C0FFBDBD
      BDFFB5B5B5FFC6C6C657000000000000000000000000000000004351CDFF9FA7
      EFFFA0A8F7FFA1AAFDFFA2ACFEFFA4ADFFFFA3ACFFFFA1AAFEFFA0A9FAFF9FA7
      F3FF9AA1E8FFB2B8E95700000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FBFBFB057B7B
      7BFFCFCFCFFFD1D1D1FFD2D2D2FFD3D3D3FFD3D3D3FFD2D2D2FFD0D0D0FFC0C0
      C0FFA7A7A7880000000000000000000000000000000000000000FAFAFD054C59
      D0FFBCC2F3FFBCC2F7FFBDC3F9FFBDC3FAFFBDC3FAFFBDC2F8FFBCC2F4FFA8AE
      EBFF8890DD880000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008A8A8AB2A0A0A0FFE2E2E2FFE3E3E3FFE2E2E2FFC8C8C8FF676767FBECEC
      EC1D000000000000000000000000000000000000000000000000000000000000
      0000616DD3B27E87DEFFD7DAF6FFD7DAF7FFD7DAF7FFB3B9EDFF3241C7FBE5E7
      F71D000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F7F7F70BD7D7D73CE4E4E42900000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F5F5FC0BCACEF03CDADDF52900000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000F81FF81F00000000
      E00FE00F00000000C007C0070000000080038003000000008001800100000000
      8001800100000000000100010000000000010001000000000001000100000000
      80018001000000008003800300000000C003C00300000000C007C00700000000
      F00FF00F00000000FC7FFC7F0000000000000000000000000000000000000000
      000000000000}
  end
  object DataSource1: TDataSource
    DataSet = FDTable1
    Left = 103
    Top = 351
  end
  object MainMenu1: TMainMenu
    Left = 574
    Top = 119
    object File1: TMenuItem
      Caption = '&File'
      object Preferences1: TMenuItem
        Caption = '&Preferences'
        OnClick = Preferences1Click
      end
      object Export1: TMenuItem
        Caption = '&Export'
        OnClick = Export1Click
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object Help2: TMenuItem
        Caption = '&Help'
        OnClick = Help1Click
      end
      object About1: TMenuItem
        Caption = '&About'
        OnClick = About1Click
      end
      object Update1: TMenuItem
        Caption = '&Update'
        OnClick = nmUpdatesClick
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'csv'
    Filter = 'Comma delmited|*.csv'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 840
    Top = 137
  end
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=C:\Users\gajew\OneDrive\Desktop\Dashboard.sdb'
      'OpenMode=CreateUTF16'
      'DriverID=SQLite')
    LoginPrompt = False
    Left = 480
    Top = 360
  end
  object FDCommand1: TFDCommand
    Connection = FDConnection1
    CommandKind = skCreate
    CommandText.Strings = (
      'CREATE TABLE NETLOGGER'
      '('
      'SerialNo VARCHAR(255),'
      'Callsign VARCHAR(255),'
      'State VARCHAR(255),'
      'Remarks VARCHAR(255),'
      'QSLInfo VARCHAR(255),'
      'CityCountry VARCHAR(255),'
      'FirstName VARCHAR(255),'
      'Status VARCHAR(255),'
      'County VARCHAR(255),'
      'Grid VARCHAR(255),'
      'Street VARCHAR(255),'
      'Zip VARCHAR(255),'
      'MemberID VARCHAR(255),'
      'Country VARCHAR(255),'
      'DXCC VARCHAR(255),'
      'PreferredName VARCHAR(255)'
      ')'
      ''
      '')
    Left = 600
    Top = 368
  end
  object RefreshTimer: TTimer
    Enabled = False
    Interval = 20000
    OnTimer = RefreshTimerTimer
    Left = 120
    Top = 144
  end
  object FDTable1: TFDTable
    Connection = FDConnection1
    TableName = 'NETLOGGER'
    Left = 760
    Top = 304
  end
end
