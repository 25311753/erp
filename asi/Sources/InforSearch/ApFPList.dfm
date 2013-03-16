object ApFPListForm: TApFPListForm
  Left = 238
  Top = 190
  Width = 1001
  Height = 571
  Caption = #35531#36092#27284#27284#21015#34920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 323
    Top = 16
    Width = 366
    Height = 33
    Caption = #35531#36092#21934#27512#27284#21015#34920#26597#35426
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lstView: TListView
    Left = 8
    Top = 56
    Width = 977
    Height = 361
    Columns = <
      item
        Caption = #20844#21496
        Width = 80
      end
      item
        Caption = #27284#34399
        Width = 75
      end
      item
        Caption = #35531#36092#26696#34399
        Width = 70
      end
      item
        Caption = #25509#20214#26085
        Width = 80
      end
      item
        Caption = #21697#21517
        Width = 150
      end
      item
        Caption = #32147#36774
        Width = 65
      end
      item
        Caption = #24471#27161#24288#21830
        Width = 80
      end
      item
        Caption = #24471#27161#37329#38989
        Width = 70
      end
      item
        Caption = #21576#26680#26085
        Width = 80
      end
      item
        Caption = #35330#36092#26085
        Width = 80
      end
      item
        Caption = #35036'/'#36864'/'#21462#28040
        Width = 70
      end
      item
        Caption = #38913#34399
      end>
    Font.Charset = CHINESEBIG5_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #26032#32048#26126#39636
    Font.Style = []
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    ParentFont = False
    TabOrder = 0
    ViewStyle = vsReport
  end
  object Panel1: TPanel
    Left = 8
    Top = 416
    Width = 977
    Height = 65
    TabOrder = 1
    object Label2: TLabel
      Left = 32
      Top = 17
      Width = 58
      Height = 13
      Caption = #36215#40670#27284#34399': '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #26032#32048#26126#39636
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 234
      Top = 17
      Width = 58
      Height = 13
      Caption = #32066#40670#27284#34399': '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #26032#32048#26126#39636
      Font.Style = []
      ParentFont = False
    end
    object btnPrint: TButton
      Left = 672
      Top = 37
      Width = 75
      Height = 25
      Caption = #21015'     '#21360
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #26032#32048#26126#39636
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnPrintClick
    end
    object btnQuery: TButton
      Left = 746
      Top = 37
      Width = 75
      Height = 25
      Caption = #26597'     '#35426
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #26032#32048#26126#39636
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = btnQueryClick
    end
    object btnToExcel: TButton
      Left = 820
      Top = 37
      Width = 75
      Height = 25
      Caption = #36681'Excel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #26032#32048#26126#39636
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = btnToExcelClick
    end
    object btnExit: TButton
      Left = 894
      Top = 37
      Width = 75
      Height = 25
      Caption = #36864'     '#20986
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #26032#32048#26126#39636
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnExitClick
    end
    object edtFile0: TEdit
      Left = 90
      Top = 14
      Width = 121
      Height = 21
      MaxLength = 8
      TabOrder = 4
    end
    object edtFile1: TEdit
      Left = 293
      Top = 14
      Width = 121
      Height = 21
      MaxLength = 8
      TabOrder = 5
    end
  end
end
