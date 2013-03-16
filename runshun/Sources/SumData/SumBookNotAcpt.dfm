object SumBookNotAcptForm: TSumBookNotAcptForm
  Left = 441
  Top = 119
  Width = 824
  Height = 588
  Caption = #36926#26399#26410#20132#36008#26696#20214#32113#35336#34920
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
    Left = 199
    Top = 8
    Width = 396
    Height = 33
    Caption = #36926#26399#26410#20132#36008#26696#20214#21608#22577#32113#35336#34920
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
    Width = 806
    Height = 417
    Columns = <
      item
        Caption = #37319#36092#32147#36774
        Width = 68
      end
      item
        Caption = #20844#21496
      end
      item
        Caption = #35531#36092#26696#34399
        Width = 70
      end
      item
        Caption = #25509#21934#26085
        Width = 70
      end
      item
        Caption = #21697#21517
        Width = 150
      end
      item
        Alignment = taRightJustify
        Caption = #25976#37327
      end
      item
        Caption = #24288#21830
        Width = 100
      end
      item
        Alignment = taRightJustify
        Caption = #37329#38989
        Width = 70
      end
      item
        Caption = #35330#36092#26085
        Width = 70
      end
      item
        Caption = #38928#23450#20132#36008#26085
      end
      item
        Caption = #35531#36092#32147#36774
        Width = 70
      end
      item
        Caption = #37319#36092#37096#38272
        Width = 70
      end
      item
        Caption = #34389#29702#32080#26524
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
    Width = 807
    Height = 85
    TabOrder = 1
    object Label2: TLabel
      Left = 3
      Top = 8
      Width = 70
      Height = 13
      Caption = #37319#36092#32147#36774#65306
    end
    object Label3: TLabel
      Left = 96
      Top = 8
      Width = 42
      Height = 13
      Caption = #20844#21496#65306
    end
    object Label4: TLabel
      Left = 159
      Top = 8
      Width = 42
      Height = 13
      Caption = #24288#21830#65306
    end
    object Label6: TLabel
      Left = 266
      Top = 8
      Width = 70
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object Label7: TLabel
      Left = 9
      Top = 56
      Width = 70
      Height = 13
      Caption = #32113#35336#36215#40670#65306
    end
    object Label8: TLabel
      Left = 249
      Top = 56
      Width = 70
      Height = 13
      Caption = #32113#35336#32066#40670#65306
    end
    object Label5: TLabel
      Left = 387
      Top = 8
      Width = 427
      Height = 13
      Caption = #35498#26126#65306#23578#26410#25910#26009#30340#26696#20214#33509#20854#38928#35330#20132#36008#26085#22312#32113#35336#26085#26399#33539#22285#20839#23601#35222#28858#36926#26399')'
    end
    object Label9: TLabel
      Left = 430
      Top = 24
      Width = 154
      Height = 13
      Caption = #38928#23450#20132#36008#26085'='#35330#36092#26085'+'#20132#26399
    end
    object lstHandle: TComboBox
      Left = 3
      Top = 24
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
    end
    object lstCorp: TComboBox
      Left = 94
      Top = 24
      Width = 65
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
    end
    object lstFactory: TComboBox
      Left = 159
      Top = 24
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      OnExit = lstFactoryExit
    end
    object btnQuery: TButton
      Left = 491
      Top = 56
      Width = 67
      Height = 25
      Caption = #26597#12288#35426
      TabOrder = 3
      OnClick = btnQueryClick
    end
    object btnPrint: TButton
      Left = 563
      Top = 56
      Width = 67
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 4
      OnClick = btnPrintClick
    end
    object btnToExcel: TButton
      Left = 635
      Top = 56
      Width = 67
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 5
      OnClick = btnToExcelClick
    end
    object btnExit: TButton
      Left = 707
      Top = 56
      Width = 67
      Height = 25
      Caption = #36864#12288#20986
      TabOrder = 6
      OnClick = btnExitClick
    end
    object lstStockDepart: TComboBox
      Left = 266
      Top = 24
      Width = 121
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
    end
    object DateTimePicker1: TDateTimePicker
      Left = 81
      Top = 56
      Width = 153
      Height = 21
      CalAlignment = dtaLeft
      Date = 38560.4461534259
      Time = 38560.4461534259
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 8
    end
    object DateTimePicker2: TDateTimePicker
      Left = 321
      Top = 56
      Width = 153
      Height = 21
      CalAlignment = dtaLeft
      Date = 38560.4461640972
      Time = 38560.4461640972
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 9
    end
  end
end
