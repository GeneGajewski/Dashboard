object FormMain: TFormMain
  Left = 0
  Top = 55
  HelpKeyword = 'Application'
  HelpContext = 10
  Caption = 'DASHBOARD'
  ClientHeight = 689
  ClientWidth = 1201
  Color = clBtnFace
  Constraints.MinHeight = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  Position = poDesigned
  WindowMenu = Preferences1
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 15
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 1201
    Height = 193
    Align = alTop
    BevelOuter = bvNone
    Constraints.MinHeight = 193
    Constraints.MinWidth = 902
    ParentShowHint = False
    ShowCaption = False
    ShowHint = True
    TabOrder = 0
    object PanelLeft: TPanel
      Left = 0
      Top = 0
      Width = 553
      Height = 193
      Align = alLeft
      BevelOuter = bvNone
      Caption = 'PanelLeft'
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
        Hint = 'radio frequency'
        TabStop = False
        ReadOnly = True
        TabOrder = 0
      end
      object edBand: TEdit
        Left = 112
        Top = 96
        Width = 81
        Height = 23
        Hint = 'radio band'
        TabStop = False
        ReadOnly = True
        TabOrder = 1
      end
      object edMode: TEdit
        Left = 208
        Top = 96
        Width = 81
        Height = 23
        Hint = 'modulation mode'
        TabStop = False
        ReadOnly = True
        TabOrder = 2
      end
      object edNetControl: TEdit
        Left = 352
        Top = 96
        Width = 185
        Height = 23
        Hint = 'Network Controller callsign'
        HelpKeyword = 'Application'
        TabStop = False
        ReadOnly = True
        TabOrder = 3
      end
      object edLogger: TEdit
        Left = 352
        Top = 144
        Width = 185
        Height = 23
        Hint = 'net logger and software version'
        HelpType = htKeyword
        HelpKeyword = 'LICENSE'
        TabStop = False
        TabOrder = 4
      end
      object edSubscribe: TEdit
        Left = 16
        Top = 144
        Width = 81
        Height = 23
        Hint = 'Number of Netlogger clients'
        TabStop = False
        ReadOnly = True
        TabOrder = 5
      end
      object btnNets: TButton
        Left = 462
        Top = 39
        Width = 75
        Height = 25
        Hint = 'Choose a net to view'
        Caption = 'Live &Nets'
        TabOrder = 6
        OnClick = btnNetsClick
      end
      object edNET: TEdit
        Left = 16
        Top = 40
        Width = 416
        Height = 23
        Hint = 'Selected '#39'net'#39
        TabStop = False
        ReadOnly = True
        TabOrder = 7
      end
    end
    object PanelRight: TPanel
      Left = 852
      Top = 0
      Width = 349
      Height = 193
      Align = alRight
      BevelOuter = bvNone
      Caption = 'RightPanel'
      Constraints.MinWidth = 349
      ShowCaption = False
      TabOrder = 1
      object PanelDate: TPanel
        Left = -2
        Top = 19
        Width = 352
        Height = 30
        BevelOuter = bvNone
        Caption = 'PanelDate'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object PanelZone: TPanel
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
        object PanelClock: TPanel
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
    Width = 1181
    Height = 471
    Hint = 'double-click for Qrz.com info'
    HelpKeyword = 'Application'
    HelpContext = 10
    Margins.Left = 10
    Margins.Right = 10
    Align = alClient
    DataSource = DataSource1
    DrawingStyle = gdsClassic
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgTitleClick, dgTitleHotTrack, dgThumbTracking]
    ParentFont = False
    ParentShowHint = False
    ReadOnly = True
    ShowHint = True
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
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Callsign'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'State'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Remarks'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'QSLInfo'
        Title.Caption = 'Info'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CityCountry'
        Title.Caption = 'City'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'FirstName'
        Title.Caption = 'Name'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Status'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'County'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Grid'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Street'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Zip'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MemberID'
        Title.Caption = 'Member ID'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Country'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DXCC'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PreferredName'
        Title.Caption = 'Preferred Name'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -13
        Title.Font.Name = 'Segoe UI'
        Title.Font.Style = []
        Visible = True
      end>
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 670
    Width = 1201
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object ClockTimer: TTimer
    Enabled = False
    OnTimer = MasterTick
    Left = 983
    Top = 572
  end
  object DataSource1: TDataSource
    DataSet = FDTable1
    Left = 151
    Top = 295
  end
  object MainMenu1: TMainMenu
    Left = 502
    Top = 295
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
    Filter = 'comma delimited (*.csv)|*.csv'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 48
    Top = 585
  end
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=C:\Users\gajew\OneDrive\Desktop\Dashboard.sdb'
      'OpenMode=CreateUTF16'
      'DriverID=SQLite')
    LoginPrompt = False
    Left = 56
    Top = 296
  end
  object RefreshTimer: TTimer
    Enabled = False
    Interval = 20000
    OnTimer = RefreshTimerTimer
    Left = 1088
    Top = 576
  end
  object FDTable1: TFDTable
    Connection = FDConnection1
    TableName = 'NETLOGGER'
    Left = 232
    Top = 296
  end
  object RESTClient1: TRESTClient
    Params = <>
    SynchronizedEvents = False
    OnHTTPProtocolError = RESTClient1HTTPProtocolError
    OnNeedClientCertificate = RESTClient1NeedClientCertificate
    OnAuthEvent = RESTClient1AuthEvent
    OnSendData = RESTClient1SendData
    OnReceiveData = RESTClient1ReceiveData
    Left = 1112
    Top = 256
  end
  object RESTRequest1: TRESTRequest
    Client = RESTClient1
    Params = <>
    Response = RESTResponse1
    SynchronizedEvents = False
    Left = 1024
    Top = 256
  end
  object RESTResponse1: TRESTResponse
    Left = 928
    Top = 256
  end
end
