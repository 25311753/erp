object GoodsAddrForm: TGoodsAddrForm
  Left = 199
  Top = 99
  Width = 803
  Height = 540
  Caption = #20132#36008#22320#40670#36664#20837
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
    Left = 306
    Top = 16
    Width = 198
    Height = 33
    Caption = #20132#36008#22320#40670#36664#20837
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
    Width = 753
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
      Left = 24
      Top = 96
      Width = 513
      Height = 297
      Columns = <
        item
          Caption = #32232#34399
          Width = 80
        end
        item
          Caption = #20132#36008#20844#21496#25110#21312#22495
          Width = 100
        end
        item
          Caption = #20132#36008#22320#40670
          Width = 300
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
    Left = 48
    Top = 80
    Width = 689
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
      Left = 104
      Top = 12
      Width = 96
      Height = 13
      Caption = #20132#36008#20844#21496#36008#21312#22495#65306
    end
    object Label1: TLabel
      Left = 272
      Top = 12
      Width = 60
      Height = 13
      Caption = #20132#36008#22320#40670#65306
    end
    object edtID: TEdit
      Left = 16
      Top = 28
      Width = 81
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 0
      Text = 'EDTID'
    end
    object edtName: TEdit
      Left = 104
      Top = 28
      Width = 161
      Height = 21
      MaxLength = 8
      TabOrder = 1
      Text = 'edtName'
    end
    object btnOK0: TButton
      Left = 616
      Top = 8
      Width = 57
      Height = 25
      Caption = #30906#23450
      TabOrder = 3
      OnClick = btnOK0Click
    end
    object btnCancel0: TButton
      Left = 616
      Top = 40
      Width = 57
      Height = 25
      Cancel = True
      Caption = #21462#28040
      TabOrder = 4
      OnClick = btnCancel0Click
    end
    object edtType: TEdit
      Left = 272
      Top = 28
      Width = 329
      Height = 21
      MaxLength = 20
      TabOrder = 2
      Text = 'edtName'
    end
  end
  object btnAddNew: TButton
    Left = 576
    Top = 256
    Width = 161
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 2
    OnClick = btnAddNewClick
  end
  object btnEdit: TButton
    Left = 576
    Top = 288
    Width = 161
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 3
    OnClick = btnEditClick
  end
  object btnRefresh: TButton
    Left = 576
    Top = 352
    Width = 161
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 4
    OnClick = btnRefreshClick
  end
  object btnExit: TButton
    Left = 576
    Top = 416
    Width = 161
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDelete: TButton
    Left = 576
    Top = 320
    Width = 161
    Height = 25
    Caption = #21034'    '#38500
    TabOrder = 6
    OnClick = btnDeleteClick
  end
  object btnPrint: TButton
    Left = 576
    Top = 384
    Width = 161
    Height = 25
    Caption = #21015'    '#21360
    TabOrder = 7
    OnClick = btnPrintClick
  end
end
