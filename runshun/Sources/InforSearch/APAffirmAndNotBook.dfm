object APAffirmAndNotBookForm: TAPAffirmAndNotBookForm
  Left = 322
  Top = 189
  Width = 852
  Height = 602
  Caption = #24050#25509#26696#36926#26399#26410#35330#26126#32048
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 256
    Top = 8
    Width = 288
    Height = 33
    Caption = #24050#25509#26696#36926#26399#26410#35330#26126#32048
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = []
    ParentFont = False
  end
  object lstView: TListView
    Left = 2
    Top = 42
    Width = 788
    Height = 401
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
        Caption = #35215#26684#21517#31281
        Width = 150
      end
      item
        Caption = #25509#26696#26085#26399
        Width = 70
      end
      item
        Caption = #37319#36092#32147#36774
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
  object ctlPane: TPanel
    Left = 2
    Top = 443
    Width = 775
    Height = 78
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 20
      Width = 65
      Height = 13
      Caption = #35531#36092#21934#34399#65306
    end
    object Label3: TLabel
      Left = 150
      Top = 20
      Width = 39
      Height = 13
      Caption = #39006#21029#65306
    end
    object Label8: TLabel
      Left = 407
      Top = 20
      Width = 65
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object Label9: TLabel
      Left = 152
      Top = 57
      Width = 65
      Height = 13
      Caption = #35531#36092#37096#38272#65306
    end
    object Label11: TLabel
      Left = 564
      Top = 19
      Width = 65
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object Label5: TLabel
      Left = 8
      Top = 58
      Width = 65
      Height = 13
      Caption = #35531#36092#20844#21496#65306
    end
    object Label13: TLabel
      Left = 256
      Top = 20
      Width = 65
      Height = 13
      Caption = #37319#36092#32147#36774#65306
    end
    object Label4: TLabel
      Left = 325
      Top = 57
      Width = 65
      Height = 13
      Caption = #25509#26696#26085#26399#65306
    end
    object Label6: TLabel
      Left = 421
      Top = 54
      Width = 26
      Height = 13
      Caption = #22825#21069
    end
    object edtID: TEdit
      Left = 72
      Top = 12
      Width = 73
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 0
      Text = 'EDTID'
    end
    object lstType: TComboBox
      Left = 184
      Top = 12
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
    object lstStockDep: TComboBox
      Left = 471
      Top = 12
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
    end
    object lstAskDep: TComboBox
      Left = 216
      Top = 49
      Width = 105
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
    end
    object edtMncode: TEdit
      Left = 628
      Top = 11
      Width = 113
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 21
      TabOrder = 4
      Text = 'EDTMNCODE'
    end
    object btnQuery: TButton
      Left = 449
      Top = 47
      Width = 60
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 5
      OnClick = btnQueryClick
    end
    object btnExit: TButton
      Left = 713
      Top = 47
      Width = 60
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 6
      OnClick = btnExitClick
    end
    object btnDetail: TButton
      Left = 515
      Top = 47
      Width = 60
      Height = 25
      Caption = #35443#32048#24773#27841
      TabOrder = 7
      OnClick = btnDetailClick
    end
    object lstReqCorp: TComboBox
      Left = 72
      Top = 50
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 8
    end
    object lstStockman: TComboBox
      Left = 320
      Top = 12
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 9
    end
    object edtAfmDay: TEdit
      Left = 389
      Top = 49
      Width = 33
      Height = 21
      TabOrder = 10
      Text = 'edtAfmDay'
    end
    object btnPrint: TButton
      Left = 647
      Top = 47
      Width = 60
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 11
      OnClick = btnPrintClick
    end
    object btnMaterPickup: TButton
      Left = 740
      Top = 12
      Width = 33
      Height = 20
      Caption = #25552#21462
      TabOrder = 12
      OnClick = btnMaterPickupClick
    end
    object btnToExcel: TButton
      Left = 581
      Top = 47
      Width = 60
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 13
      OnClick = btnToExcelClick
    end
  end
end
