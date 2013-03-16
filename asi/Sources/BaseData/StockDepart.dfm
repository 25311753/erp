object StockDepartForm: TStockDepartForm
  Left = 217
  Top = 81
  Width = 836
  Height = 561
  Caption = #37319#36092#37096#38272#27284#36664#20837
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 263
    Top = 8
    Width = 231
    Height = 32
    Caption = #37319#36092#37096#38272#27284#36664#20837
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 64
    Width = 745
    Height = 441
    TabOrder = 0
    object msgState: TLabel
      Left = 24
      Top = 404
      Width = 377
      Height = 13
      AutoSize = False
      Caption = #24037#20316#29376#24907#65306
    end
    object ListView1: TListView
      Left = 8
      Top = 96
      Width = 633
      Height = 297
      Columns = <
        item
          Caption = #32232#34399
          Width = 80
        end
        item
          Caption = #21517#31281
          Width = 100
        end
        item
          Caption = #22320#22336
          Width = 200
        end
        item
          Caption = #38651#35441
          Width = 200
        end>
      GridLines = True
      HideSelection = False
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = ListView1Click
    end
  end
  object Panel1: TPanel
    Left = 32
    Top = 80
    Width = 729
    Height = 73
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 12
      Width = 36
      Height = 13
      Caption = #32232#34399#65306
    end
    object Label3: TLabel
      Left = 96
      Top = 12
      Width = 36
      Height = 13
      Caption = #21517#31281#65306
    end
    object Label1: TLabel
      Left = 184
      Top = 12
      Width = 24
      Height = 13
      Caption = #22320#22336
    end
    object Label5: TLabel
      Left = 400
      Top = 8
      Width = 24
      Height = 13
      Caption = #38651#35441
    end
    object edtID: TEdit
      Left = 16
      Top = 28
      Width = 65
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 0
      Text = 'EDTID'
    end
    object edtName: TEdit
      Left = 88
      Top = 28
      Width = 81
      Height = 21
      MaxLength = 10
      TabOrder = 1
      Text = 'edtName'
    end
    object btnOK0: TButton
      Left = 664
      Top = 8
      Width = 57
      Height = 25
      Caption = #30906#23450
      TabOrder = 4
      OnClick = btnOK0Click
    end
    object btnCancel0: TButton
      Left = 664
      Top = 40
      Width = 57
      Height = 25
      Cancel = True
      Caption = #21462#28040
      TabOrder = 5
      OnClick = btnCancel0Click
    end
    object edtAddress: TEdit
      Left = 176
      Top = 28
      Width = 193
      Height = 21
      MaxLength = 80
      TabOrder = 2
      Text = 'edtAddress'
    end
    object edtTel: TEdit
      Left = 376
      Top = 29
      Width = 273
      Height = 21
      MaxLength = 80
      TabOrder = 3
      Text = 'edtTel'
    end
  end
  object btnAddNew: TButton
    Left = 679
    Top = 219
    Width = 81
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 2
    OnClick = btnAddNewClick
  end
  object btnEdit: TButton
    Left = 679
    Top = 251
    Width = 81
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 3
    OnClick = btnEditClick
  end
  object btnRefresh: TButton
    Left = 679
    Top = 315
    Width = 81
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 4
    OnClick = btnRefreshClick
  end
  object btnExit: TButton
    Left = 679
    Top = 379
    Width = 81
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDelete: TButton
    Left = 679
    Top = 283
    Width = 81
    Height = 25
    Caption = #21034'    '#38500
    TabOrder = 6
    OnClick = btnDeleteClick
  end
  object btnPrint: TButton
    Left = 679
    Top = 347
    Width = 81
    Height = 25
    Caption = #21015'    '#21360
    TabOrder = 7
    OnClick = btnPrintClick
  end
end
