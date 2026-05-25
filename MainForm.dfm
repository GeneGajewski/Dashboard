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
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 15
  object PanelTop: TPanel
    Left = 0
    Top = 27
    Width = 1201
    Height = 207
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
      Width = 664
      Height = 207
      Align = alLeft
      BevelOuter = bvNone
      Caption = 'PanelLeft'
      Constraints.MinHeight = 193
      Constraints.MinWidth = 553
      ShowCaption = False
      TabOrder = 0
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
      object edNET: TLabeledEditEx
        Left = 16
        Top = 26
        Width = 397
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
        BoundCaption = 'Net'
        BoundLabel.Left = 16
        BoundLabel.Top = 10
        BoundLabel.Width = 19
        BoundLabel.Height = 15
        BoundLabel.Color = clBtnFace
        BoundLabel.ParentColor = False
      end
      object edFreq: TLabeledEditEx
        Left = 16
        Top = 72
        Width = 81
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        BoundCaption = 'Frequency'
        BoundLabel.Left = 16
        BoundLabel.Top = 56
        BoundLabel.Width = 55
        BoundLabel.Height = 15
      end
      object edBand: TLabeledEditEx
        Left = 111
        Top = 72
        Width = 81
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        BoundCaption = 'Band'
        BoundLabel.Left = 111
        BoundLabel.Top = 56
        BoundLabel.Width = 27
        BoundLabel.Height = 15
      end
      object edMode: TLabeledEditEx
        Left = 207
        Top = 72
        Width = 69
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        BoundCaption = 'Mode'
        BoundLabel.Left = 207
        BoundLabel.Top = 56
        BoundLabel.Width = 31
        BoundLabel.Height = 15
      end
      object edNetControl: TLabeledEditEx
        Left = 16
        Top = 118
        Width = 185
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        BoundCaption = 'Net Control'
        BoundLabel.Left = 16
        BoundLabel.Top = 102
        BoundLabel.Width = 62
        BoundLabel.Height = 15
      end
      object edLogger: TLabeledEditEx
        Left = 228
        Top = 118
        Width = 185
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        BoundCaption = 'Logger'
        BoundLabel.Left = 228
        BoundLabel.Top = 102
        BoundLabel.Width = 37
        BoundLabel.Height = 15
      end
      object edStart: TLabeledEditEx
        Left = 16
        Top = 164
        Width = 185
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        BoundCaption = 'Started'
        BoundLabel.Left = 16
        BoundLabel.Top = 148
        BoundLabel.Width = 37
        BoundLabel.Height = 15
      end
      object edClosed: TLabeledEditEx
        Left = 228
        Top = 164
        Width = 185
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
        Visible = False
        BoundCaption = 'Closed'
        BoundLabel.Left = 228
        BoundLabel.Top = 148
        BoundLabel.Width = 36
        BoundLabel.Height = 15
      end
      object edNetID: TLabeledEditEx
        Left = 439
        Top = 26
        Width = 114
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 8
        Visible = False
        BoundCaption = 'Net ID'
        BoundLabel.Left = 439
        BoundLabel.Top = 10
        BoundLabel.Width = 33
        BoundLabel.Height = 15
      end
      object edSourceIP: TLabeledEditEx
        Left = 291
        Top = 72
        Width = 122
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        TabOrder = 9
        BoundCaption = 'Source IP'
        BoundLabel.Left = 291
        BoundLabel.Top = 56
        BoundLabel.Width = 49
        BoundLabel.Height = 15
      end
      object edLastActivity: TLabeledEditEx
        Left = 439
        Top = 164
        Width = 185
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 10
        Visible = False
        BoundCaption = 'Last Activity'
        BoundLabel.Left = 439
        BoundLabel.Top = 148
        BoundLabel.Width = 64
        BoundLabel.Height = 15
      end
      object edInactivity: TLabeledEditEx
        Left = 439
        Top = 72
        Width = 114
        Height = 23
        TabStop = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Segoe UI Semibold'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 11
        Visible = False
        BoundCaption = 'Inactivity  Timer'
        BoundLabel.Left = 439
        BoundLabel.Top = 56
        BoundLabel.Width = 85
        BoundLabel.Height = 15
      end
      object cbAIM: TCheckBox
        Left = 559
        Top = 121
        Width = 97
        Height = 17
        TabStop = False
        Caption = 'AIM'
        TabOrder = 12
        Visible = False
      end
    end
    object PanelRight: TPanel
      Left = 852
      Top = 0
      Width = 349
      Height = 207
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
    object edAIMUpdate: TLabeledEditEx
      Left = 439
      Top = 118
      Width = 114
      Height = 23
      TabStop = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Segoe UI Semibold'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      Visible = False
      BoundCaption = 'AIM Update'
      BoundLabel.Left = 439
      BoundLabel.Top = 102
      BoundLabel.Width = 63
      BoundLabel.Height = 15
    end
    object dbcbAsassinated: TDBCheckBox
      Left = 559
      Top = 75
      Width = 117
      Height = 17
      Caption = 'Asassinated'
      TabOrder = 3
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 670
    Width = 1201
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object ActionMainMenuBar1: TActionMainMenuBar
    Left = 0
    Top = 0
    Width = 1201
    Height = 27
    HelpType = htKeyword
    ActionManager = ActionManager1
    Caption = 'ActionMainMenuBar1'
    Color = clMenuBar
    ColorMap.DisabledFontColor = 10461087
    ColorMap.HighlightColor = clWhite
    ColorMap.BtnSelectedFont = clBlack
    ColorMap.UnusedColor = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentShowHint = False
    ShowHint = True
    Spacing = 0
  end
  object DBGrid1: TLabeledDbGrid
    Left = 0
    Top = 234
    Width = 1201
    Height = 436
    Align = alClient
    DataSource = DataSource1
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI Semibold'
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgRowSelect, dgConfirmDelete, dgTitleClick, dgTitleHotTrack]
    ParentFont = False
    TabOrder = 3
    OnDrawColumnCell = DBGrid1DrawColumnCell
    OnDblClick = DBGrid1DblClick
    OnTitleClick = DBGrid1TitleClick
    BoundLabel.Left = 0
    BoundLabel.Top = 218
    BoundLabel.Width = 3
    BoundLabel.Height = 15
    OnSortedField = DBGrid1SortedField
    Columns = <
      item
        Expanded = False
        FieldName = 'SerialNo'
        Title.Caption = 'No.'
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
        Title.Caption = 'Preferred'
        Visible = True
      end>
  end
  object ClockTimer: TTimer
    Enabled = False
    OnTimer = MasterTick
    Left = 983
    Top = 572
  end
  object DataSource1: TDataSource
    DataSet = FDMemTable1
    Left = 151
    Top = 295
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'csv'
    Filter = 'comma delimited (*.csv)|*.csv'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 48
    Top = 585
  end
  object RefreshTimer: TTimer
    Enabled = False
    Interval = 20000
    OnTimer = RefreshTimerTimer
    Left = 1088
    Top = 576
  end
  object RESTClient1: TRESTClient
    Params = <>
    SynchronizedEvents = False
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
  object ActionManager1: TActionManager
    ActionBars = <
      item
        BackgroundLayout = blLeftBanner
        Items = <
          item
            Items = <
              item
                Action = actExportCSV
              end
              item
                Action = actExit
                ImageIndex = 43
              end>
            Caption = '&File'
          end
          item
            Action = actPreferences
          end
          item
            Action = actAutoFit
            Caption = '&AutoFit'
          end
          item
            Items = <
              item
                Action = actAbout
              end
              item
                Action = actContents
                ImageIndex = 40
              end
              item
                Action = actHelpOnHelp
              end
              item
                Action = actCheckUpdates
                Caption = 'Ch&eck Updates'
              end>
            Caption = '&Help'
          end
          item
            Items = <
              item
                Action = actLiveNet
                ShortCut = 16449
              end
              item
                Action = ActPastNets
                ShortCut = 16464
              end>
            Caption = '&Nets'
          end>
        ActionBar = ActionMainMenuBar1
      end>
    Left = 869
    Top = 421
    StyleName = 'XP Style'
    object actExportCSV: TAction
      Category = 'File'
      Caption = 'Export &CSV'
      Enabled = False
      Hint = 'Export data to file'
      OnExecute = ActionExport
    end
    object actAbout: TAction
      Category = 'Help'
      Caption = '&About'
      Hint = 'About this program'
      OnExecute = ActionAbout
    end
    object actPreferences: TAction
      Caption = '&Preferences'
      OnExecute = ActionPreferences
    end
    object actAutoFit: TAction
      Caption = 'Auto&Fit'
      OnExecute = ActionAutoFit
    end
    object actContents: THelpContents
      Category = 'Help'
      Caption = '&Contents'
      HelpKeyword = 'Introduction'
      Hint = 'Help Contents'
      ImageIndex = 40
    end
    object actExit: TFileExit
      Category = 'File'
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object actHelpOnHelp: THelpOnHelp
      Category = 'Help'
      Caption = '&Help on Help'
      Enabled = False
      Hint = 'Help on help'
    end
    object actCheckUpdates: TAction
      Category = 'Help'
      Caption = 'Check Updates'
      OnExecute = actCheckUpdatesExecute
    end
    object actLiveNet: TAction
      Category = 'Nets'
      Caption = '&Active Nets'
      ShortCut = 16449
      OnExecute = ActionLiveNet
    end
    object ActPastNets: TAction
      Category = 'Nets'
      Caption = '&Past Nets'
      ShortCut = 16464
      OnExecute = ActPastNetsExecute
    end
  end
  object FDMemTable1: TFDMemTable
    FieldDefs = <
      item
        Name = 'SerialNo'
        DataType = ftInteger
      end
      item
        Name = 'Callsign'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'State'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'Remarks'
        DataType = ftString
        Size = 128
      end
      item
        Name = 'QSLInfo'
        DataType = ftString
        Size = 128
      end
      item
        Name = 'CityCountry'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'FirstName'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'Status'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'County'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'Grid'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'Street'
        DataType = ftString
        Size = 128
      end
      item
        Name = 'Zip'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'MemberID'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'Country'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'DXCC'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'PreferredName'
        DataType = ftString
        Size = 64
      end>
    IndexDefs = <>
    FetchOptions.AssignedValues = [evMode]
    FetchOptions.Mode = fmAll
    ResourceOptions.AssignedValues = [rvSilentMode]
    ResourceOptions.SilentMode = True
    UpdateOptions.AssignedValues = [uvCheckRequired, uvAutoCommitUpdates]
    UpdateOptions.CheckRequired = False
    UpdateOptions.AutoCommitUpdates = True
    StoreDefs = True
    Left = 280
    Top = 295
  end
end
