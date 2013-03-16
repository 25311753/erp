object RawPurchaseListForm: TRawPurchaseListForm
  Left = 231
  Top = 172
  Width = 800
  Height = 560
  Caption = #21407#26009#35531#36092#21934#21015#34920#26597#35426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 288
    Top = 8
    Width = 297
    Height = 33
    Caption = #21407#26009#35531#36092#21934#21015#34920#26597#35426
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
    Height = 377
    Columns = <
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #37319#36092#21029
        Width = 55
      end
      item
        Caption = #37319#36092#37096#38272
        Width = 80
      end
      item
        Caption = #20844#21496#21029
      end
      item
        Caption = #35531#36092#37096#38272
        Width = 70
      end
      item
        Caption = #39006#21029
      end
      item
        Caption = #35531#36092#26085
        Width = 65
      end
      item
        Caption = #38656#35201#26085
        Width = 65
      end
      item
        Caption = #26448#26009#32232#34399
        Width = 150
      end
      item
        Caption = #35215#26684#21517#31281
        Width = 150
      end
      item
        Caption = #25509#26696#26085#26399
      end
      item
        Caption = #37319#36092#32147#36774
      end
      item
        Caption = #32080#26696
      end
      item
        Alignment = taRightJustify
        Caption = #35531#36092#25976#37327
      end
      item
        Caption = #22577#20729#25130#27490#26085
      end
      item
        Caption = #35426#20729#21015#21360#26085
      end
      item
        Caption = #22577#20729#36664#20837#26085
      end
      item
        Caption = #35696#20729#36664#20837#26085
      end
      item
        Caption = #21576#26680#26085
      end
      item
        Caption = #27770#27161#26085
      end
      item
        Caption = #35330#36092#21934#34399
      end
      item
        Caption = #35330#36092#26085#26399
      end
      item
        Caption = #20132#26399
      end
      item
        Caption = #35330#36092#24288#21830#21517#31281
      end
      item
        Alignment = taRightJustify
        Caption = #35330#36092#25976#37327
      end
      item
        Alignment = taRightJustify
        Caption = #25910#26009#25976#37327
      end
      item
        Alignment = taRightJustify
        Caption = #39511#25910#25976#37327
      end
      item
        Caption = #35531#27454#25976#37327
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnDblClick = lstViewDblClick
    OnSelectItem = lstViewSelectItem
  end
  object ctlPane: TPanel
    Left = 8
    Top = 432
    Width = 777
    Height = 89
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 16
      Width = 65
      Height = 13
      Caption = #35531#36092#21934#34399#65306
    end
    object Label3: TLabel
      Left = 152
      Top = 16
      Width = 39
      Height = 13
      Caption = #39006#21029#65306
    end
    object Label6: TLabel
      Left = 432
      Top = 16
      Width = 52
      Height = 13
      Caption = #38656#35201#26085#65306
    end
    object Label8: TLabel
      Left = 8
      Top = 40
      Width = 65
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object Label9: TLabel
      Left = 184
      Top = 40
      Width = 65
      Height = 13
      Caption = #35531#36092#37096#38272#65306
    end
    object Label10: TLabel
      Left = 512
      Top = 40
      Width = 39
      Height = 13
      Caption = #25509#26696#65306
    end
    object Label11: TLabel
      Left = 8
      Top = 64
      Width = 65
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object Label4: TLabel
      Left = 256
      Top = 16
      Width = 52
      Height = 13
      Caption = #35531#36092#26085#65306
    end
    object Label5: TLabel
      Left = 360
      Top = 40
      Width = 65
      Height = 13
      Caption = #35531#36092#20844#21496#65306
    end
    object Label12: TLabel
      Left = 640
      Top = 40
      Width = 39
      Height = 13
      Caption = #32080#26696#65306
    end
    object Label13: TLabel
      Left = 616
      Top = 16
      Width = 65
      Height = 13
      Caption = #37319#36092#32147#36774#65306
    end
    object Label7: TLabel
      Left = 264
      Top = 64
      Width = 65
      Height = 13
      Caption = #37319#36092#39006#21029#65306
    end
    object edtID: TEdit
      Left = 72
      Top = 8
      Width = 73
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 0
      Text = 'EDTID'
    end
    object lstType: TComboBox
      Left = 184
      Top = 8
      Width = 65
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      Items.Strings = (
        #20840#37096
        #26222#36890
        #32202#24613)
    end
    object edtReqDate0: TEdit
      Left = 352
      Top = 8
      Width = 73
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 2
      Text = 'EDTREQDATE0'
    end
    object edtNeedDate: TEdit
      Left = 528
      Top = 8
      Width = 81
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 3
      Text = 'EDTNEEDDATE'
    end
    object lstNeedType: TComboBox
      Left = 479
      Top = 8
      Width = 49
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 4
      Items.Strings = (
        '='
        '>'
        '<')
    end
    object lstStockDep: TComboBox
      Left = 72
      Top = 32
      Width = 105
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 5
    end
    object lstAskDep: TComboBox
      Left = 248
      Top = 32
      Width = 105
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 6
    end
    object lstAfm: TComboBox
      Left = 552
      Top = 32
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
      Items.Strings = (
        #20840#37096
        #26410#25509#26696
        #24050#25509#26696)
    end
    object edtMncode: TEdit
      Left = 72
      Top = 56
      Width = 137
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 21
      TabOrder = 8
      Text = 'EDTMNCODE'
    end
    object btnQuery: TButton
      Left = 488
      Top = 56
      Width = 67
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 9
      OnClick = btnQueryClick
    end
    object btnToExcel: TButton
      Left = 632
      Top = 56
      Width = 67
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 10
      OnClick = btnToExcelClick
    end
    object btnExit: TButton
      Left = 704
      Top = 56
      Width = 67
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 11
      OnClick = btnExitClick
    end
    object btnDetail: TButton
      Left = 560
      Top = 56
      Width = 67
      Height = 25
      Caption = #35443#32048#24773#27841
      TabOrder = 12
      OnClick = btnDetailClick
    end
    object lstReqType: TComboBox
      Left = 304
      Top = 8
      Width = 49
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 13
      Items.Strings = (
        '='
        '>'
        '<')
    end
    object lstReqCorp: TComboBox
      Left = 424
      Top = 32
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 14
      OnClick = lstReqCorpClick
    end
    object lstEndFlag: TComboBox
      Left = 680
      Top = 32
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 15
      Items.Strings = (
        #26410#32080#26696
        #24050#32080#26696
        #20840#37096)
    end
    object lstStockman: TComboBox
      Left = 680
      Top = 8
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 16
    end
    object btnToEnd: TButton
      Left = 416
      Top = 56
      Width = 67
      Height = 25
      Caption = #21435#32080#26696
      TabOrder = 17
      OnClick = btnToEndClick
    end
    object lstStockType: TComboBox
      Left = 328
      Top = 56
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 18
      Items.Strings = (
        #19968#33324#37319#36092
        #21512#32004#37319#36092)
    end
    object btnMaterPickup: TButton
      Left = 208
      Top = 57
      Width = 32
      Height = 20
      Caption = #25552#21462
      TabOrder = 19
      OnClick = btnMaterPickupClick
    end
  end
end
