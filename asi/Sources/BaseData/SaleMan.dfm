object SalesManForm: TSalesManForm
  Left = 218
  Top = 103
  Width = 803
  Height = 592
  Caption = #26989#21209#20154#21729#21029#36664#20837
  Color = clBtnFace
  Font.Charset = CHINESEBIG5_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  WindowState = wsMaximized
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 256
    Top = 16
    Width = 231
    Height = 32
    Caption = #37319#36092#37096#38272#21029#36664#20837
    Font.Charset = CHINESEBIG5_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 64
    Width = 689
    Height = 489
    TabOrder = 0
    object msgState: TLabel
      Left = 24
      Top = 468
      Width = 377
      Height = 13
      AutoSize = False
      Caption = #24037#20316#29376#24907#65306
    end
    object ListView1: TListView
      Left = 24
      Top = 32
      Width = 393
      Height = 425
      Columns = <
        item
          Caption = #32232#34399
          Width = 60
        end
        item
          Caption = #22995#21517
          Width = 80
        end
        item
          Caption = #32068#21029#21517#31281
          Width = 150
        end
        item
          Caption = #32068#38263#27880#35352
          Width = 70
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
    Left = 480
    Top = 96
    Width = 193
    Height = 233
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 12
      Width = 98
      Height = 13
      Caption = #26989#21209#20154#21729#32232#34399#65306
    end
    object Label3: TLabel
      Left = 16
      Top = 60
      Width = 98
      Height = 13
      Caption = #26989#21209#20154#21729#21517#31281#65306
    end
    object Label1: TLabel
      Left = 16
      Top = 108
      Width = 70
      Height = 13
      Caption = #29151#26989#32068#21029#65306
    end
    object Label5: TLabel
      Left = 16
      Top = 156
      Width = 70
      Height = 13
      Caption = #32068#38263#27880#35352#65306
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
    end
    object edtName: TEdit
      Left = 16
      Top = 76
      Width = 161
      Height = 21
      MaxLength = 10
      TabOrder = 1
      Text = 'edtName'
    end
    object btnOK0: TButton
      Left = 32
      Top = 200
      Width = 57
      Height = 25
      Caption = #30906#23450
      TabOrder = 4
      OnClick = btnOK0Click
    end
    object btnCancel0: TButton
      Left = 104
      Top = 200
      Width = 57
      Height = 25
      Cancel = True
      Caption = #21462#28040
      TabOrder = 5
      OnClick = btnCancel0Click
    end
    object edtMonitor: TEdit
      Left = 16
      Top = 172
      Width = 161
      Height = 21
      MaxLength = 1
      TabOrder = 3
      Text = 'edtName'
    end
    object lstGroup: TComboBox
      Left = 16
      Top = 128
      Width = 161
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = 'lstGroup'
    end
  end
  object btnAddNew: TButton
    Left = 488
    Top = 336
    Width = 161
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 2
    OnClick = btnAddNewClick
  end
  object btnEdit: TButton
    Left = 488
    Top = 368
    Width = 161
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 3
    OnClick = btnEditClick
  end
  object btnRefresh: TButton
    Left = 488
    Top = 432
    Width = 161
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 4
    OnClick = btnRefreshClick
  end
  object btnExit: TButton
    Left = 488
    Top = 496
    Width = 161
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDelete: TButton
    Left = 488
    Top = 400
    Width = 161
    Height = 25
    Caption = #21034'    '#38500
    TabOrder = 6
    OnClick = btnDeleteClick
  end
  object btnPrint: TButton
    Left = 488
    Top = 464
    Width = 161
    Height = 25
    Caption = #21015'    '#21360
    TabOrder = 7
    OnClick = btnPrintClick
  end
end
