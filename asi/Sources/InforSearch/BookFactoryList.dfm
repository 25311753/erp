object BookFactoryListForm: TBookFactoryListForm
  Left = 324
  Top = 147
  Width = 800
  Height = 560
  Caption = #35330#36092#21934#21015#34920#26597#35426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 288
    Top = 8
    Width = 231
    Height = 33
    Caption = #35330#36092#21934#21015#34920#26597#35426
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 777
    Height = 369
    Columns = <
      item
        Caption = #35330#36092#21934#34399
        Width = 70
      end
      item
        Caption = #35330#36092#26085#26399
        Width = 70
      end
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #25910#36008#32147#36774
        Width = 80
      end
      item
        Caption = #35330#36092#24288#21830
        Width = 120
      end
      item
        Caption = #24288#29260
        Width = 70
      end
      item
        Caption = #26448#26009#32232#34399
        Width = 120
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 200
      end
      item
        Alignment = taRightJustify
        Caption = #35330#36092#25976#37327
        Width = 70
      end
      item
        Alignment = taRightJustify
        Caption = #21934#20729
      end
      item
        Caption = #24163#21029
      end
      item
        Alignment = taRightJustify
        Caption = #37329#38989
        Width = 70
      end
      item
        Caption = #25910#26009#25976#37327
      end
      item
        Caption = #21512#26684#25976#37327
      end
      item
        Caption = #19981#21512#26684#25976#37327
      end
      item
        Caption = #25910#27454#37329#38989
        Width = 70
      end
      item
        Caption = #37319#36092#37096#38272#12288
      end
      item
        Caption = #20844#21496#21029
      end
      item
        Caption = #35330#36092#21934#20633#27880
        Width = 100
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
  object Panel1: TPanel
    Left = 8
    Top = 432
    Width = 777
    Height = 91
    TabOrder = 1
    object Label2: TLabel
      Left = 5
      Top = 16
      Width = 65
      Height = 13
      Caption = #35330#36092#21934#34399#65306
    end
    object Label3: TLabel
      Left = 157
      Top = 16
      Width = 78
      Height = 13
      Caption = #35330#36092#36215#22987#26085#65306
    end
    object Label4: TLabel
      Left = 309
      Top = 16
      Width = 78
      Height = 13
      Caption = #35330#36092#25130#27490#26085#65306
    end
    object Label5: TLabel
      Left = 453
      Top = 16
      Width = 65
      Height = 13
      Caption = #35531#36092#21934#34399#65306
    end
    object Label6: TLabel
      Left = 605
      Top = 16
      Width = 65
      Height = 13
      Caption = #25910#36008#32147#36774#65306
    end
    object Label7: TLabel
      Left = 4
      Top = 40
      Width = 65
      Height = 13
      Caption = #37319#36092#39006#21029#65306
    end
    object Label8: TLabel
      Left = 142
      Top = 40
      Width = 39
      Height = 13
      Caption = #25910#26009#65306
    end
    object Label9: TLabel
      Left = 260
      Top = 40
      Width = 65
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object Label10: TLabel
      Left = 415
      Top = 40
      Width = 52
      Height = 13
      Caption = #20844#21496#21029#65306
    end
    object Label11: TLabel
      Left = 569
      Top = 40
      Width = 39
      Height = 13
      Caption = #24288#21830#65306
    end
    object btnExit: TButton
      Left = 536
      Top = 61
      Width = 67
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 0
      OnClick = btnExitClick
    end
    object btnQuery: TButton
      Left = 160
      Top = 61
      Width = 67
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 1
      OnClick = btnQueryClick
    end
    object btnToExcel: TButton
      Left = 442
      Top = 61
      Width = 67
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 2
      OnClick = btnToExcelClick
    end
    object edtBookID: TEdit
      Left = 69
      Top = 8
      Width = 73
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 3
      Text = 'BTNBOOKID'
    end
    object edtDate0: TEdit
      Left = 230
      Top = 8
      Width = 65
      Height = 21
      MaxLength = 8
      TabOrder = 4
      Text = 'edtDate0'
    end
    object edtDate1: TEdit
      Left = 382
      Top = 8
      Width = 56
      Height = 21
      MaxLength = 8
      TabOrder = 5
      Text = 'edtDate1'
    end
    object edtAskID: TEdit
      Left = 517
      Top = 8
      Width = 73
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 6
      Text = 'EDTASKID'
    end
    object lstRcpt: TComboBox
      Left = 669
      Top = 8
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
    end
    object lstStockType: TComboBox
      Left = 68
      Top = 32
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      MaxLength = 5
      TabOrder = 8
      Items.Strings = (
        #19968#33324#37319#36092
        #21512#32004#37319#36092)
    end
    object btnDetail: TButton
      Left = 348
      Top = 61
      Width = 67
      Height = 25
      Caption = #35443#32048#24773#27841
      TabOrder = 9
      OnClick = btnDetailClick
    end
    object lstAccept: TComboBox
      Left = 177
      Top = 32
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 10
      Items.Strings = (
        #20840#37096
        #26410#25910#26009
        #39511#25910#26410#23436
        #39511#25910#24050#23436)
    end
    object lstDepart: TComboBox
      Left = 324
      Top = 32
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 11
    end
    object lstCorp: TComboBox
      Left = 479
      Top = 32
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 12
    end
    object lstFactory: TComboBox
      Left = 609
      Top = 32
      Width = 128
      Height = 21
      ItemHeight = 13
      TabOrder = 13
      Text = 'lstFactory'
      OnExit = lstFactoryExit
    end
    object btnPickFact: TButton
      Left = 736
      Top = 33
      Width = 37
      Height = 20
      Caption = #25552#21462
      TabOrder = 14
      OnClick = btnPickFactClick
    end
    object btnToAsk: TButton
      Left = 254
      Top = 61
      Width = 75
      Height = 25
      Caption = #26597#30475#35531#36092#21934
      TabOrder = 15
      OnClick = btnToAskClick
    end
  end
end
