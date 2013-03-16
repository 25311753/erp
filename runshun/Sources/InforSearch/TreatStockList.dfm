object TreatStockListForm: TTreatStockListForm
  Left = 367
  Top = 107
  Width = 800
  Height = 555
  Caption = #21512#32004#37319#36092#21015#34920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 296
    Top = 8
    Width = 192
    Height = 32
    Caption = #21512#32004#37319#36092#21015#34920
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = []
    ParentFont = False
  end
  object ctlPage: TPageControl
    Left = 8
    Top = 48
    Width = 777
    Height = 401
    ActivePage = ctlCurrent
    TabIndex = 0
    TabOrder = 0
    object ctlCurrent: TTabSheet
      Caption = #26368#26032#21512#32004
      OnShow = ctlCurrentShow
      object lstView: TListView
        Left = 0
        Top = 0
        Width = 761
        Height = 346
        Columns = <
          item
            Caption = #21512#32004#32232#34399
            Width = 70
          end
          item
            Caption = #26448#26009#32232#34399
            Width = 100
          end
          item
            Caption = #21697#21517#35215#26684
            Width = 150
          end
          item
            Caption = #24288#21830#31777#31281
            Width = 100
          end
          item
            Caption = #24288#29260
            Width = 100
          end
          item
            Caption = #29983#25928#26085#26399
            Width = 70
          end
          item
            Caption = #21934#20301
            Width = 40
          end
          item
            Caption = #21934#20729
          end
          item
            Caption = #32147#36774#20154
          end
          item
            Caption = #37319#36092#37096#38272
          end
          item
            Caption = #20132#26399' '
          end
          item
            Caption = #24314#27284#26085#26399
            Width = 70
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lstViewClick
        OnDblClick = lstViewDblClick
        OnSelectItem = lstViewSelectItem
      end
      object Button1: TButton
        Left = 51
        Top = 348
        Width = 97
        Height = 25
        Caption = #32066#27490#25152#36984#21512#32004
        TabOrder = 1
        OnClick = Button1Click
      end
    end
    object ctlModify: TTabSheet
      Caption = #26356#27491#27284
      ImageIndex = 1
      OnShow = ctlModifyShow
      object lstModify: TListView
        Left = 0
        Top = 4
        Width = 761
        Height = 365
        Columns = <
          item
            Caption = #21512#32004#32232#34399
            Width = 70
          end
          item
            Caption = #26448#26009#32232#34399
            Width = 100
          end
          item
            Caption = #21697#21517#35215#26684
            Width = 150
          end
          item
            Caption = #24288#21830#31777#31281
            Width = 100
          end
          item
            Caption = #24288#29260
            Width = 100
          end
          item
            Caption = #29983#25928#26085#26399
            Width = 70
          end
          item
            Caption = #21934#20301
            Width = 40
          end
          item
            Caption = #21934#20729
          end
          item
            Caption = #32147#36774#20154
          end
          item
            Caption = #37319#36092#37096#38272
          end
          item
            Caption = #20132#26399' '
          end
          item
            Caption = #26356#27491#20154
            Width = 60
          end
          item
            Caption = #26356#27491#26178#38291
            Width = 70
          end
          item
            Caption = #26356#27491#39006#22411
          end
          item
            Caption = #24314#27284#26085#26399
            Width = 70
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lstViewClick
        OnDblClick = lstViewDblClick
        OnSelectItem = lstViewSelectItem
      end
    end
    object ctlHistory: TTabSheet
      Caption = #27511#21490#27284
      ImageIndex = 2
      OnShow = ctlHistoryShow
      object lstHistory: TListView
        Left = -8
        Top = 4
        Width = 761
        Height = 365
        Columns = <
          item
            Caption = #21512#32004#32232#34399
            Width = 70
          end
          item
            Caption = #26448#26009#32232#34399
            Width = 100
          end
          item
            Caption = #21697#21517#35215#26684
            Width = 150
          end
          item
            Caption = #24288#21830#31777#31281
            Width = 100
          end
          item
            Caption = #24288#29260
            Width = 100
          end
          item
            Caption = #29983#25928#26085#26399
            Width = 70
          end
          item
            Caption = #21934#20301
            Width = 40
          end
          item
            Caption = #21934#20729
          end
          item
            Caption = #32147#36774#20154
          end
          item
            Caption = #37319#36092#37096#38272
          end
          item
            Caption = #20132#26399' '
          end
          item
            Caption = #24314#27284#26085#26399
            Width = 70
          end
          item
            Caption = #32066#27490#26085#26399
            Width = 70
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lstViewClick
        OnDblClick = lstViewDblClick
        OnSelectItem = lstViewSelectItem
      end
    end
  end
  object ctlPane: TPanel
    Left = 8
    Top = 448
    Width = 777
    Height = 73
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 16
      Width = 65
      Height = 13
      Caption = #21512#32004#32232#34399#65306
    end
    object Label3: TLabel
      Left = 160
      Top = 16
      Width = 65
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object Label4: TLabel
      Left = 416
      Top = 16
      Width = 39
      Height = 13
      Caption = #24288#21830#65306
    end
    object Label5: TLabel
      Left = 624
      Top = 16
      Width = 39
      Height = 13
      Caption = #32147#36774#65306
    end
    object Label6: TLabel
      Left = 8
      Top = 48
      Width = 65
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object Label7: TLabel
      Left = 160
      Top = 48
      Width = 65
      Height = 13
      Caption = #24314#27284#26085#26399#65306
    end
    object edtID: TEdit
      Left = 72
      Top = 8
      Width = 81
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 0
      Text = 'EDTID'
    end
    object edtMater: TEdit
      Left = 224
      Top = 8
      Width = 145
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 21
      TabOrder = 1
      Text = 'EDTMATER'
    end
    object btnPickup: TButton
      Left = 368
      Top = 9
      Width = 34
      Height = 20
      Caption = #26597#25214
      TabOrder = 2
      OnClick = btnPickupClick
    end
    object lstFact: TComboBox
      Left = 451
      Top = 8
      Width = 134
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = 'lstFact'
      OnExit = lstFactExit
    end
    object lstHandle: TComboBox
      Left = 664
      Top = 8
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 4
      Text = 'lstHandle'
      OnExit = lstHandleExit
    end
    object btnToExcel: TButton
      Left = 592
      Top = 40
      Width = 75
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 5
      OnClick = btnToExcelClick
    end
    object btnDetail: TButton
      Left = 496
      Top = 40
      Width = 75
      Height = 25
      Caption = #35443#32048#24773#27841
      TabOrder = 6
      OnClick = btnDetailClick
    end
    object btnQuery: TButton
      Left = 400
      Top = 40
      Width = 75
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 7
      OnClick = btnQueryClick
    end
    object btnExit: TButton
      Left = 688
      Top = 40
      Width = 75
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 8
      OnClick = btnExitClick
    end
    object lstDepart: TComboBox
      Left = 72
      Top = 40
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 9
    end
    object btnFactPickup: TButton
      Left = 583
      Top = 8
      Width = 33
      Height = 20
      Caption = #26597#25214
      TabOrder = 10
      OnClick = btnFactPickupClick
    end
    object lstDateType: TComboBox
      Left = 224
      Top = 40
      Width = 41
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 11
      Items.Strings = (
        '>'
        '='
        '<')
    end
    object edtDate: TEdit
      Left = 264
      Top = 40
      Width = 105
      Height = 21
      MaxLength = 8
      TabOrder = 12
      Text = 'edtDate'
    end
  end
end
