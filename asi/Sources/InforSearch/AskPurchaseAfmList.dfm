object AskPurchaseAfmListForm: TAskPurchaseAfmListForm
  Left = 229
  Top = 161
  Width = 800
  Height = 560
  Caption = #26032#25509#26696#20214#32113#35336#22577#34920
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
    Left = 272
    Top = 8
    Width = 264
    Height = 32
    Caption = #26032#25509#26696#20214#32113#35336#22577#34920
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
    Height = 401
    Columns = <
      item
        Caption = #20844#21496
        Width = 80
      end
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #39006#21029
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
      end
      item
        Caption = #25509#26696#26085
        Width = 120
      end
      item
        Caption = #38656#35201#26085
        Width = 65
      end
      item
        Caption = #26696#20214#39006#21029
        Width = 70
      end
      item
        Caption = #37319#36092#32147#36774
        Width = 65
      end
      item
        Caption = #21576#26680#26085
        Width = 65
      end
      item
        Caption = #21576#20934#26085
        Width = 70
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
    Top = 456
    Width = 777
    Height = 65
    TabOrder = 1
    object Label2: TLabel
      Left = 49
      Top = 15
      Width = 65
      Height = 13
      Caption = #36215#40670#26178#38291#65306
    end
    object Label3: TLabel
      Left = 319
      Top = 15
      Width = 65
      Height = 13
      Caption = #32066#40670#26178#38291#65306
    end
    object Label4: TLabel
      Left = 589
      Top = 15
      Width = 65
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object ctlTime0: TDateTimePicker
      Left = 200
      Top = 8
      Width = 105
      Height = 21
      CalAlignment = dtaLeft
      Date = 37851.426571875
      Time = 37851.426571875
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkTime
      ParseInput = False
      TabOrder = 0
    end
    object btnExit: TButton
      Left = 677
      Top = 38
      Width = 75
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 1
      OnClick = btnExitClick
    end
    object ctlDate0: TDateTimePicker
      Left = 111
      Top = 8
      Width = 89
      Height = 21
      CalAlignment = dtaLeft
      Date = 37851.4462603704
      Time = 37851.4462603704
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object ctlDate1: TDateTimePicker
      Left = 380
      Top = 7
      Width = 89
      Height = 21
      CalAlignment = dtaLeft
      Date = 37851.4462603704
      Time = 37851.4462603704
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 3
    end
    object ctlTime1: TDateTimePicker
      Left = 468
      Top = 7
      Width = 101
      Height = 21
      CalAlignment = dtaLeft
      Date = 37851.426571875
      Time = 37851.426571875
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkTime
      ParseInput = False
      TabOrder = 4
    end
    object lstDepart: TComboBox
      Left = 653
      Top = 7
      Width = 100
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 5
    end
    object btnToExcel: TButton
      Left = 601
      Top = 38
      Width = 75
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 6
      OnClick = btnToExcelClick
    end
    object btnQuery: TButton
      Left = 489
      Top = 38
      Width = 112
      Height = 25
      Caption = #26597'  '#35426'('#25152#26377')'
      TabOrder = 7
      OnClick = btnQueryClick
    end
    object btnPrint: TButton
      Left = 304
      Top = 38
      Width = 75
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 8
      OnClick = btnPrintClick
    end
    object btnQuery0: TButton
      Left = 379
      Top = 38
      Width = 110
      Height = 25
      Caption = #26597'  '#35426'('#26410#25351#27966#32147#36774')'
      TabOrder = 9
      OnClick = btnQuery0Click
    end
  end
end
