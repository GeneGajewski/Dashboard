object FormActiveNets: TFormActiveNets
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = 'Active Nets'
  ClientHeight = 264
  ClientWidth = 933
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 210
    Width = 933
    Height = 54
    Align = alBottom
    BevelEdges = []
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 922
    object BitBtnOk: TBitBtn
      Left = 16
      Top = 16
      Width = 75
      Height = 25
      Caption = 'OK'
      ModalResult = 1
      NumGlyphs = 2
      TabOrder = 0
      OnClick = BitBtnOkClick
    end
    object BitBtnCancel: TBitBtn
      Left = 110
      Top = 15
      Width = 75
      Height = 25
      Kind = bkCancel
      NumGlyphs = 2
      TabOrder = 1
    end
    object ActivityIndicator1: TActivityIndicator
      Left = 874
      Top = 6
      IndicatorType = aitRefresh
    end
  end
  object Panel2: TPanel
    Left = 917
    Top = 16
    Width = 16
    Height = 194
    Align = alRight
    BevelEdges = []
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 906
  end
  object Panel3: TPanel
    Left = 0
    Top = 16
    Width = 16
    Height = 194
    Align = alLeft
    BevelEdges = []
    BevelOuter = bvNone
    TabOrder = 2
  end
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 933
    Height = 16
    Align = alTop
    BevelEdges = []
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitWidth = 922
  end
  object NetGrid: TLabeledDbGrid
    Left = 16
    Top = 16
    Width = 901
    Height = 194
    Align = alClient
    BorderStyle = bsNone
    DataSource = DataSource4
    Enabled = False
    Options = [dgTitles, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgTitleClick, dgTitleHotTrack]
    TabOrder = 4
    OnTitleClick = NetGridTitleClick
    BoundLabel.Left = 16
    BoundLabel.Top = 0
    BoundLabel.Width = 3
    BoundLabel.Height = 15
    OnSortedField = NetGridSortedField
    Columns = <
      item
        Expanded = False
        FieldName = 'NetName'
        Title.Caption = 'Net'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'AltNetName'
        Title.Caption = 'Alt Name'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Frequency'
        Title.Caption = 'Freq'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Logger'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NetControl'
        Title.Caption = 'Net Control'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Date'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Mode'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Band'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Server'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'SubscriberCount'
        Title.Caption = 'Subs'
        Visible = True
      end>
  end
  object DataSource4: TDataSource
    DataSet = FDMemTab
    Left = 168
    Top = 40
  end
  object FDMemTab: TFDMemTable
    FieldDefs = <
      item
        Name = 'NetName'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'AltNetName'
        DataType = ftString
        Size = 64
      end
      item
        Name = 'Frequency'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'Logger'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'NetControl'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'Date'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'Mode'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'Band'
        DataType = ftString
        Size = 32
      end
      item
        Name = 'SubscriberCount'
        DataType = ftInteger
      end
      item
        Name = 'Server'
        DataType = ftString
        Size = 20
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
    Left = 88
    Top = 40
    object FDMemTabNetName: TStringField
      FieldName = 'NetName'
      Size = 64
    end
    object FDMemTabAltNetName: TStringField
      FieldName = 'AltNetName'
      Size = 64
    end
    object FDMemTabFrequency: TStringField
      FieldName = 'Frequency'
      Size = 32
    end
    object FDMemTabLogger: TStringField
      FieldName = 'Logger'
      Size = 32
    end
    object FDMemTabNetControl: TStringField
      FieldName = 'NetControl'
      Size = 32
    end
    object FDMemTabDate: TStringField
      FieldName = 'Date'
      Size = 32
    end
    object FDMemTabMode: TStringField
      FieldName = 'Mode'
      Size = 32
    end
    object FDMemTabBand: TStringField
      FieldName = 'Band'
      Size = 32
    end
    object FDMemTabSubscriberCount: TIntegerField
      FieldName = 'SubscriberCount'
    end
    object FDMemTabServer: TStringField
      FieldName = 'Server'
    end
  end
  object RESTClient: TRESTClient
    Params = <>
    SynchronizedEvents = False
    Left = 790
    Top = 51
  end
  object RESTRequest: TRESTRequest
    Client = RESTClient
    Params = <>
    Response = RESTResponse
    SynchronizedEvents = False
    Left = 844
    Top = 49
  end
  object RESTResponse: TRESTResponse
    Left = 741
    Top = 51
  end
end
