object SumBookNotEndForm: TSumBookNotEndForm
  Left = 304
  Top = 125
  Width = 853
  Height = 616
  Caption = #35330#36092#36926#26399#26410#23436#25104#26696#20214#32113#35336#34920
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
    Left = 272
    Top = 8
    Width = 297
    Height = 33
    Caption = #35330#36092#36926#26399#26696#20214#32113#35336#34920
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lstView: TListView
    Left = 0
    Top = 48
    Width = 841
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
        Caption = #25509#20214#26085
        Width = 70
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
        Width = 70
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
        Width = 65
      end
      item
        Alignment = taRightJustify
        Caption = #21576#26680#37329#38989
        Width = 70
      end
      item
        Caption = #20633#27880
        Width = 100
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object Panel1: TPanel
    Left = 0
    Top = 472
    Width = 845
    Height = 105
    TabOrder = 1
    object Label2: TLabel
      Left = 3
      Top = 8
      Width = 70
      Height = 13
      Caption = #37319#36092#32147#36774#65306
    end
    object Label3: TLabel
      Left = 93
      Top = 8
      Width = 42
      Height = 13
      Caption = #20844#21496#65306
    end
    object Label4: TLabel
      Left = 158
      Top = 8
      Width = 42
      Height = 13
      Caption = #24288#21830#65306
    end
    object Label6: TLabel
      Left = 264
      Top = 8
      Width = 70
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object Label7: TLabel
      Left = 4
      Top = 81
      Width = 63
      Height = 13
      Caption = #32113#35336#36215#40670':'
    end
    object Label8: TLabel
      Left = 268
      Top = 81
      Width = 63
      Height = 13
      Caption = #32113#35336#32066#40670':'
    end
    object Label5: TLabel
      Left = 409
      Top = 8
      Width = 434
      Height = 13
      Caption = '('#21608#22577#65306#26410#35330#36092#30340#26696#20214#33509#20854#35330#36092#26368#24460#38480#26399#22312#32113#35336#33539#22285#20043#20839#23601#34987#35222#28858#36926#26399')'
    end
    object Label9: TLabel
      Left = 409
      Top = 32
      Width = 427
      Height = 13
      Caption = '('#26376#22577#65306#35330#36092#26368#24460#38480#26399#22312#32113#35336#33539#22285#20043#20839#20006#19988#35330#36092#26368#24460#38480#26399'<'#23526#38555#35330#36092#26085')'
    end
    object Label10: TLabel
      Left = 363
      Top = 56
      Width = 462
      Height = 13
      Caption = #26399#38480#35373#23450#65306#19968#33324#20214':'#35330#36092#26368#24460#38480#26399'='#21576#26680#26085'+6  '#24613#20214':'#35330#36092#26368#24460#38480#26399'='#21576#26680#26085'+2'
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
      Left = 93
      Top = 24
      Width = 65
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
    end
    object lstFactory: TComboBox
      Left = 158
      Top = 24
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      OnExit = lstFactoryExit
    end
    object btnQuery: TButton
      Left = 570
      Top = 78
      Width = 67
      Height = 25
      Caption = #26597#12288#35426
      TabOrder = 3
      OnClick = btnQueryClick
    end
    object btnPrint: TButton
      Left = 637
      Top = 78
      Width = 67
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 4
      OnClick = btnPrintClick
    end
    object btnToExcel: TButton
      Left = 705
      Top = 78
      Width = 67
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 5
      OnClick = btnToExcelClick
    end
    object btnExit: TButton
      Left = 772
      Top = 78
      Width = 67
      Height = 25
      Caption = #36864#12288#20986
      TabOrder = 6
      OnClick = btnExitClick
    end
    object lstStockDepart: TComboBox
      Left = 264
      Top = 24
      Width = 96
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
    end
    object DateTimePicker1: TDateTimePicker
      Left = 68
      Top = 81
      Width = 186
      Height = 21
      CalAlignment = dtaLeft
      Date = 38562.478273287
      Time = 38562.478273287
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 8
    end
    object DateTimePicker2: TDateTimePicker
      Left = 332
      Top = 81
      Width = 186
      Height = 21
      CalAlignment = dtaLeft
      Date = 38562.4782841435
      Time = 38562.4782841435
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 9
    end
    object RadioButton1: TRadioButton
      Left = 363
      Top = 8
      Width = 44
      Height = 17
      Caption = #21608#22577
      Checked = True
      TabOrder = 10
      TabStop = True
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 363
      Top = 32
      Width = 47
      Height = 17
      Caption = #26376#22577
      TabOrder = 11
      OnClick = RadioButton2Click
    end
  end
end
