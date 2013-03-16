object TreatStockRecordForm: TTreatStockRecordForm
  Left = 192
  Top = 114
  Width = 800
  Height = 554
  Caption = #21512#32004#37319#36092#35352#37636#34920
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
    Left = 288
    Top = -3
    Width = 231
    Height = 33
    Caption = #21512#32004#37319#36092#35352#37636#34920
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 16
    Top = 18
    Width = 65
    Height = 13
    Caption = #26368#26032#21512#32004#65306
  end
  object Label4: TLabel
    Left = 13
    Top = 248
    Width = 65
    Height = 13
    Caption = #27511#21490#21512#32004#65306
  end
  object lstView: TListView
    Left = 8
    Top = 34
    Width = 777
    Height = 193
    Columns = <
      item
        Caption = #26448#26009#32232#34399
        Width = 150
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
      end
      item
        Caption = #24288#21830
        Width = 120
      end
      item
        Caption = #26377#25928#26085#26399
        Width = 70
      end
      item
        Caption = #21934#20301
      end
      item
        Alignment = taRightJustify
        Caption = #21934#20729
        Width = 70
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
    Top = 480
    Width = 777
    Height = 41
    BorderStyle = bsSingle
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 11
      Width = 65
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object btnExit: TButton
      Left = 682
      Top = 5
      Width = 75
      Height = 27
      Caption = #36864'    '#20986
      TabOrder = 0
      OnClick = btnExitClick
    end
    object edtID: TEdit
      Left = 72
      Top = 7
      Width = 153
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 21
      TabOrder = 1
      Text = 'EDTID'
    end
  end
  object ListView1: TListView
    Left = 8
    Top = 262
    Width = 777
    Height = 189
    Columns = <
      item
        Caption = #26448#26009#32232#34399
        Width = 150
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
      end
      item
        Caption = #24288#21830
        Width = 120
      end
      item
        Caption = #26377#25928#26085#26399
        Width = 70
      end
      item
        Caption = #21934#20301
      end
      item
        Alignment = taRightJustify
        Caption = #21934#20729
        Width = 70
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
  end
  object Button1: TButton
    Left = 475
    Top = 228
    Width = 95
    Height = 25
    Caption = #25353#26448#26009#32232#34399#26597#35426
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 595
    Top = 228
    Width = 60
    Height = 25
    Caption = #36681'Excel'
    TabOrder = 4
    OnClick = Button2Click
  end
  object btnRefresh: TButton
    Left = 475
    Top = 452
    Width = 95
    Height = 25
    Caption = #25353#26448#26009#32232#34399#26597#35426
    TabOrder = 5
    OnClick = btnRefreshClick
  end
  object btnToExcel: TButton
    Left = 595
    Top = 452
    Width = 60
    Height = 25
    Caption = #36681'Excel'
    TabOrder = 6
    OnClick = btnToExcelClick
  end
end
