object DicSupplierForm: TDicSupplierForm
  Left = 225
  Top = 135
  Width = 1071
  Height = 610
  BorderIcons = [biSystemMenu]
  Caption = #21512#20316#20379#24212#21830
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object msgState: TLabel
    Left = 32
    Top = 332
    Width = 377
    Height = 13
    AutoSize = False
    Caption = #29366#24577#65306
    Visible = False
  end
  object ListView1: TListView
    Left = 7
    Top = 142
    Width = 1043
    Height = 419
    Columns = <
      item
        Caption = #20379#24212#21830#21495
      end
      item
        Caption = #21517#31216
      end
      item
        Caption = #22320#22336
        Width = 100
      end
      item
        Caption = #20844#21496#30005#35805
        Width = 80
      end
      item
        Caption = #20844#21496#20256#30495
        Width = 80
      end
      item
        Caption = #36127#36131#20154
      end
      item
        Caption = #32852#31995#20154#30005#35805
        Width = 80
      end
      item
        Caption = #22791#27880#33829#19994#25191#29031
      end
      item
        Caption = #20449#35465#31243#24230
      end
      item
        Caption = #25910#27454#26465#20214
        Width = 80
      end
      item
        Caption = #25910#27454#38134#34892
        Width = 80
      end
      item
        Caption = #25910#27454#38134#34892#36134#21495
        Width = 100
      end
      item
        Caption = #25143#21517
        Width = 100
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = ListView1Click
  end
  object btnAddNew: TButton
    Left = 528
    Top = 1
    Width = 66
    Height = 25
    Caption = #26032'  '#22686
    TabOrder = 1
    OnClick = btnAddNewClick
  end
  object btnDelete: TButton
    Left = 659
    Top = 1
    Width = 66
    Height = 25
    Caption = #21024#38500
    TabOrder = 2
    OnClick = btnDeleteClick
  end
  object btnEdit: TButton
    Left = 593
    Top = 1
    Width = 66
    Height = 25
    Caption = #20462#25913
    TabOrder = 3
    OnClick = btnEditClick
  end
  object btnExit: TButton
    Left = 903
    Top = 1
    Width = 73
    Height = 25
    Caption = #36864#20986
    TabOrder = 4
    OnClick = btnExitClick
  end
  object btnRefresh: TButton
    Left = 725
    Top = 1
    Width = 66
    Height = 25
    Caption = #21047#26032
    TabOrder = 5
    OnClick = btnRefreshClick
  end
  object btnOK0: TButton
    Left = 793
    Top = 1
    Width = 55
    Height = 25
    Caption = #30830#23450
    TabOrder = 6
    OnClick = btnOK0Click
  end
  object btnCancel0: TButton
    Left = 848
    Top = 1
    Width = 55
    Height = 25
    Cancel = True
    Caption = #21462#28040
    TabOrder = 7
    OnClick = btnCancel0Click
  end
  object plQry: TPanel
    Left = 0
    Top = 0
    Width = 297
    Height = 30
    BevelInner = bvLowered
    BevelOuter = bvLowered
    TabOrder = 8
    object Label9: TLabel
      Left = 133
      Top = 14
      Width = 52
      Height = 14
      Caption = #21830#21697#21517#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnHighlight
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label10: TLabel
      Left = 5
      Top = 12
      Width = 65
      Height = 14
      Caption = #20379#24212#21830#21517#31216
      Color = clBlack
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object edtQryNameCh: TEdit
      Left = 76
      Top = 7
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
    end
    object btnQry: TButton
      Left = 214
      Top = 3
      Width = 75
      Height = 25
      Caption = #26597#35810
      TabOrder = 1
    end
  end
  object plInput: TPanel
    Left = 0
    Top = 32
    Width = 1052
    Height = 107
    TabOrder = 9
    object Label2: TLabel
      Left = 5
      Top = 13
      Width = 52
      Height = 14
      Caption = #20379#24212#21830#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label3: TLabel
      Left = 209
      Top = 13
      Width = 26
      Height = 14
      Caption = #21517#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label12: TLabel
      Left = 5
      Top = 40
      Width = 52
      Height = 14
      Caption = #20844#21496#30005#35805
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label13: TLabel
      Left = 183
      Top = 40
      Width = 52
      Height = 14
      Caption = #20844#21496#20256#30495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label14: TLabel
      Left = 368
      Top = 40
      Width = 39
      Height = 14
      Caption = #36127#36131#20154
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label15: TLabel
      Left = 536
      Top = 40
      Width = 65
      Height = 14
      Caption = #32852#31995#20154#30005#35805
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label20: TLabel
      Left = 5
      Top = 68
      Width = 52
      Height = 14
      Caption = #25910#27454#26465#20214
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label21: TLabel
      Left = 898
      Top = 40
      Width = 52
      Height = 14
      Caption = #20449#35465#31243#24230
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label22: TLabel
      Left = 733
      Top = 40
      Width = 78
      Height = 14
      Caption = #22791#27880#33829#19994#25191#29031
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label23: TLabel
      Left = 361
      Top = 68
      Width = 78
      Height = 14
      Caption = #25910#27454#38134#34892#36134#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label1: TLabel
      Left = 381
      Top = 13
      Width = 26
      Height = 14
      Caption = #22320#22336
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label4: TLabel
      Left = 183
      Top = 68
      Width = 52
      Height = 14
      Caption = #25910#27454#38134#34892
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label5: TLabel
      Left = 745
      Top = 68
      Width = 30
      Height = 14
      Caption = #25143#21517' '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object edtSpId: TEdit
      Left = 58
      Top = 6
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MaxLength = 10
      TabOrder = 0
      Text = 'edtSpId'
    end
    object edtName: TEdit
      Left = 237
      Top = 6
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = 'edtName'
    end
    object edtTel: TEdit
      Left = 58
      Top = 33
      Width = 121
      Height = 21
      TabOrder = 3
      Text = 'edtTel'
    end
    object edtFax: TEdit
      Left = 237
      Top = 33
      Width = 121
      Height = 21
      TabOrder = 4
      Text = 'edtFax'
    end
    object edtChargeMan: TEdit
      Left = 409
      Top = 33
      Width = 121
      Height = 21
      TabOrder = 5
      Text = 'edtChargeMan'
    end
    object edtTelLinkMan: TEdit
      Left = 605
      Top = 33
      Width = 121
      Height = 21
      TabOrder = 6
      Text = 'edtTelLinkMan'
    end
    object cbbSettlementType: TComboBox
      Left = 58
      Top = 61
      Width = 121
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 9
      Items.Strings = (
        #29616#37329
        #27719#27454
        #25903#31080
        #20854#23427)
    end
    object cbbReputation: TComboBox
      Left = 953
      Top = 33
      Width = 96
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 8
      Items.Strings = (
        #20248#31168
        #33391#22909
        #19968#33324
        #24046)
    end
    object cbbLicense: TComboBox
      Left = 813
      Top = 33
      Width = 84
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
      Items.Strings = (
        #26159
        #21542)
    end
    object edtBankAccount: TEdit
      Left = 441
      Top = 61
      Width = 296
      Height = 21
      TabOrder = 11
      Text = 'edtBankAccount'
    end
    object edtAddress: TEdit
      Left = 409
      Top = 6
      Width = 537
      Height = 21
      TabOrder = 2
      Text = 'edtAddress'
    end
    object edtBank: TEdit
      Left = 237
      Top = 61
      Width = 121
      Height = 21
      TabOrder = 10
      Text = 'edtBank'
    end
    object edtHuMing: TEdit
      Left = 773
      Top = 60
      Width = 121
      Height = 21
      TabOrder = 12
    end
  end
  object Button1: TButton
    Left = 980
    Top = 0
    Width = 75
    Height = 25
    Caption = #26368#23567#21270
    TabOrder = 10
    OnClick = Button1Click
  end
  object TrayIcon1: TTrayIcon
    Hint = 'ASI'
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 352
  end
end
