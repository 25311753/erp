object SumHiggleNotEndForm: TSumHiggleNotEndForm
  Left = 471
  Top = 118
  Width = 858
  Height = 606
  Caption = #35696#20729#36926#26399#26410#23436#25104#26696#20214#32113#35336#34920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 224
    Top = 8
    Width = 396
    Height = 33
    Caption = #35696#20729#36926#26399#26410#23436#25104#26696#20214#32113#35336#34920
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
    Height = 417
    Columns = <
      item
        Caption = #37319#36092#32147#36774
        Width = 68
      end
      item
        Caption = #20844#21496#21029
        Width = 60
      end
      item
        Caption = #35531#36092#26696#34399
        Width = 70
      end
      item
        Caption = #25509#21934#26085
        Width = 65
      end
      item
        Caption = #39006#22411
        Width = 40
      end
      item
        Caption = #21697#21517
        Width = 150
      end
      item
        Caption = #24288#21830
        Width = 100
      end
      item
        Alignment = taRightJustify
        Caption = #25976#37327
      end
      item
        Caption = #35531#36092#32147#36774
        Width = 70
      end
      item
        Caption = #21576#26680#26085
      end
      item
        Alignment = taRightJustify
        Caption = #21576#26680#37329#38989
      end
      item
        Caption = #20633#27880
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object Panel1: TPanel
    Left = 8
    Top = 472
    Width = 777
    Height = 57
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 8
      Width = 65
      Height = 13
      Caption = #37319#36092#32147#36774#65306
    end
    object Label3: TLabel
      Left = 120
      Top = 8
      Width = 39
      Height = 13
      Caption = #20844#21496#65306
    end
    object Label4: TLabel
      Left = 192
      Top = 8
      Width = 39
      Height = 13
      Caption = #24288#21830#65306
    end
    object Label5: TLabel
      Left = 296
      Top = 8
      Width = 65
      Height = 13
      Caption = #23532#25918#22825#25976#65306
    end
    object Label6: TLabel
      Left = 376
      Top = 8
      Width = 65
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object lstHandle: TComboBox
      Left = 16
      Top = 24
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
    end
    object lstCorp: TComboBox
      Left = 112
      Top = 24
      Width = 65
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
    end
    object lstFactory: TComboBox
      Left = 184
      Top = 24
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      OnExit = lstFactoryExit
    end
    object btnQuery: TButton
      Left = 488
      Top = 16
      Width = 67
      Height = 25
      Caption = #26597#12288#35426
      TabOrder = 3
      OnClick = btnQueryClick
    end
    object btnPrint: TButton
      Left = 560
      Top = 16
      Width = 67
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 4
      OnClick = btnPrintClick
    end
    object btnToExcel: TButton
      Left = 632
      Top = 16
      Width = 67
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 5
      OnClick = btnToExcelClick
    end
    object btnExit: TButton
      Left = 704
      Top = 16
      Width = 67
      Height = 25
      Caption = #36864#12288#20986
      TabOrder = 6
      OnClick = btnExitClick
    end
    object edtDays: TEdit
      Left = 296
      Top = 24
      Width = 57
      Height = 21
      TabOrder = 7
      Text = 'edtDays'
    end
    object lstStockDepart: TComboBox
      Left = 360
      Top = 24
      Width = 121
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 8
    end
  end
end
