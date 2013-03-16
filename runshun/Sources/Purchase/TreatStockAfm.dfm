object TreatStockAfmForm: TTreatStockAfmForm
  Left = 214
  Top = 111
  Width = 696
  Height = 480
  Caption = #21512#32004#37319#36092#30906#35469
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object txtTitle: TLabel
    Left = 224
    Top = 8
    Width = 198
    Height = 33
    Caption = #21512#32004#37319#36092#30906#35469
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 576
    Top = 48
    Width = 65
    Height = 13
    Caption = #21512#32004#32232#34399#65306
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 553
    Height = 393
    Columns = <
      item
        Caption = #21512#32004#32232#34399
        Width = 70
      end
      item
        Caption = #36664#20837#26085#26399
        Width = 70
      end
      item
        Caption = #20462#25913#26085#26399
        Width = 70
      end
      item
        Caption = #30906#35469#26085#26399
        Width = 70
      end
      item
        Caption = #26371#35336#30906#35469
        Width = 70
      end
      item
        Alignment = taRightJustify
        Caption = #21934#20729
        Width = 60
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 120
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lstViewClick
    OnSelectItem = lstViewSelectItem
  end
  object edtID: TEdit
    Left = 576
    Top = 64
    Width = 105
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 8
    TabOrder = 1
    Text = 'EDTID'
    OnKeyDown = edtIDKeyDown
  end
  object btnRefresh: TButton
    Left = 576
    Top = 104
    Width = 105
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 2
    OnClick = btnRefreshClick
  end
  object btnAfm: TButton
    Left = 576
    Top = 200
    Width = 105
    Height = 25
    Caption = #30906#12288#35469
    TabOrder = 3
    OnClick = btnAfmClick
  end
  object btnDeafm: TButton
    Left = 576
    Top = 248
    Width = 105
    Height = 25
    Caption = #35299#38500#30906#35469
    TabOrder = 4
    OnClick = btnDeafmClick
  end
  object btnExit: TButton
    Left = 576
    Top = 392
    Width = 105
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDetail: TButton
    Left = 576
    Top = 152
    Width = 105
    Height = 25
    Caption = #35443#32048#36039#26009
    TabOrder = 6
    OnClick = btnDetailClick
  end
  object btnAfm2: TButton
    Left = 576
    Top = 296
    Width = 105
    Height = 25
    Caption = #26371#35336#30906#35469
    TabOrder = 7
    OnClick = btnAfm2Click
  end
  object btnDeafm2: TButton
    Left = 576
    Top = 344
    Width = 105
    Height = 25
    Caption = #35299#38500#26371#35336#30906#35469
    TabOrder = 8
    OnClick = btnDeafm2Click
  end
end
