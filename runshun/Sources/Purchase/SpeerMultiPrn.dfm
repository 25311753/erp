object SpeerMultiPrnForm: TSpeerMultiPrnForm
  Left = 258
  Top = 115
  Width = 800
  Height = 524
  Caption = #35426#20729#21934#21015#21360
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
    Left = 312
    Top = 8
    Width = 165
    Height = 33
    Caption = #35426#20729#21934#21015#21360
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 32
    Top = 76
    Width = 70
    Height = 13
    Caption = #37319#36092#32147#36774#65306
  end
  object Label4: TLabel
    Left = 224
    Top = 76
    Width = 70
    Height = 13
    Caption = #38283#22987#26085#26399#65306
  end
  object Label5: TLabel
    Left = 400
    Top = 76
    Width = 70
    Height = 13
    Caption = #25130#27490#26085#26399#65306
  end
  object Label6: TLabel
    Left = 16
    Top = 474
    Width = 56
    Height = 13
    Caption = #35426#27490#26085#65306
  end
  object lstHandle: TComboBox
    Left = 104
    Top = 68
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
  end
  object lstView: TListView
    Left = 16
    Top = 124
    Width = 761
    Height = 329
    Columns = <
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 300
      end
      item
        Caption = #21934#20301
        Width = 40
      end
      item
        Alignment = taRightJustify
        Caption = #25976#37327
        Width = 60
      end
      item
        Caption = #20132#36008#22320#22336
        Width = 150
      end
      item
        Caption = #35531#36092#20844#21496
        Width = 70
      end
      item
        Caption = #21015#21360
        Width = 40
      end>
    GridLines = True
    HideSelection = False
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object btnExit: TButton
    Left = 672
    Top = 465
    Width = 75
    Height = 25
    Caption = #36864#12288#20986
    TabOrder = 2
    OnClick = btnExitClick
  end
  object btnPrint: TButton
    Left = 568
    Top = 465
    Width = 75
    Height = 25
    Caption = #21015#12288#21360
    TabOrder = 3
    OnClick = btnPrintClick
  end
  object btnQuery: TButton
    Left = 637
    Top = 62
    Width = 89
    Height = 33
    Caption = #26597#12288#35426
    TabOrder = 4
    OnClick = btnQueryClick
  end
  object edtEndDate: TEdit
    Left = 72
    Top = 466
    Width = 97
    Height = 21
    MaxLength = 8
    TabOrder = 5
    Text = 'edtEndDate'
  end
  object ctlDate0: TDateTimePicker
    Left = 296
    Top = 68
    Width = 97
    Height = 21
    CalAlignment = dtaLeft
    Date = 37880.4871177546
    Time = 37880.4871177546
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 6
  end
  object ctlDate1: TDateTimePicker
    Left = 472
    Top = 68
    Width = 145
    Height = 21
    CalAlignment = dtaLeft
    Date = 37880.4879420833
    Time = 37880.4879420833
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 7
  end
  object chkShowQuoted: TCheckBox
    Left = 32
    Top = 100
    Width = 145
    Height = 17
    Caption = #19981#39023#31034#24050#22577#20729#25976#25818
    Checked = True
    State = cbChecked
    TabOrder = 8
  end
end
