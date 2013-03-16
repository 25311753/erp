object DicDepartForm: TDicDepartForm
  Left = 478
  Top = 97
  Width = 705
  Height = 545
  Caption = #37096#38272#21029#36664#20837
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
    Left = 256
    Top = 16
    Width = 165
    Height = 32
    Caption = #37096#38272#21029#36664#20837
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
    Width = 649
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
      Top = 32
      Width = 369
      Height = 361
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
          Caption = #37096#38272#20844#21496
          Width = 80
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
    Left = 432
    Top = 96
    Width = 193
    Height = 193
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 12
      Width = 60
      Height = 13
      Caption = #37096#38272#32232#34399#65306
    end
    object Label3: TLabel
      Left = 16
      Top = 60
      Width = 60
      Height = 13
      Caption = #37096#38272#21517#31281#65306
    end
    object Label1: TLabel
      Left = 16
      Top = 104
      Width = 48
      Height = 13
      Caption = #37096#38272#20844#21496
    end
    object edtID: TEdit
      Left = 16
      Top = 28
      Width = 161
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 6
      TabOrder = 0
      Text = 'EDTID'
      OnExit = edtIDExit
    end
    object edtName: TEdit
      Left = 16
      Top = 76
      Width = 161
      Height = 21
      MaxLength = 12
      TabOrder = 1
      Text = 'edtName'
    end
    object btnOK0: TButton
      Left = 32
      Top = 160
      Width = 57
      Height = 25
      Caption = #30906#23450
      TabOrder = 2
      OnClick = btnOK0Click
    end
    object btnCancel0: TButton
      Left = 104
      Top = 160
      Width = 57
      Height = 25
      Cancel = True
      Caption = #21462#28040
      TabOrder = 3
      OnClick = btnCancel0Click
    end
    object edtDepartCorp: TEdit
      Left = 16
      Top = 120
      Width = 161
      Height = 21
      TabOrder = 4
      Text = 'edtDepartCorp'
    end
  end
  object btnAddNew: TButton
    Left = 448
    Top = 304
    Width = 161
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 2
    OnClick = btnAddNewClick
  end
  object btnEdit: TButton
    Left = 448
    Top = 336
    Width = 161
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 3
    OnClick = btnEditClick
  end
  object btnRefresh: TButton
    Left = 448
    Top = 400
    Width = 161
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 4
    OnClick = btnRefreshClick
  end
  object btnExit: TButton
    Left = 448
    Top = 464
    Width = 161
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDelete: TButton
    Left = 448
    Top = 368
    Width = 161
    Height = 25
    Caption = #21034'    '#38500
    TabOrder = 6
    OnClick = btnDeleteClick
  end
  object btnPrint: TButton
    Left = 448
    Top = 432
    Width = 161
    Height = 25
    Caption = #21015'    '#21360
    TabOrder = 7
    OnClick = btnPrintClick
  end
end
