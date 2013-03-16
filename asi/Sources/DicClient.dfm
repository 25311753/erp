object DicClientForm: TDicClientForm
  Left = 240
  Top = 151
  Width = 983
  Height = 576
  BorderIcons = [biSystemMenu]
  Caption = #23458#25143#36164#26009
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
    Left = 0
    Top = 210
    Width = 945
    Height = 316
    Columns = <
      item
        Caption = #23458#25143#32534#21495
        Width = 100
      end
      item
        Caption = #30331#35760#26102#38388
        Width = 100
      end
      item
        Caption = #23458#25143#21517#31216
        Width = 120
      end
      item
        Caption = #33521#25991#21517#31216
        Width = 120
      end
      item
        Caption = #20844#21496#31616#31216
        Width = 100
      end
      item
        Caption = #23458#25143#31867#22411
        Width = 100
      end
      item
        Caption = #32463#33829#26041#24335
      end
      item
        Caption = #22320#22336
      end
      item
        Caption = #20844#21496#30005#35805
      end
      item
        Caption = #20844#21496#20256#30495
      end
      item
        Caption = #32852#31995#20154
      end
      item
        Caption = #32852#31995#20154#30005#35805
      end
      item
        Caption = 'QQ'
      end
      item
        Caption = 'MSN'
      end
      item
        Caption = 'E-MAIL'
      end
      item
        Caption = #25152#23646#19994#21153#21592
      end
      item
        Caption = #32467#31639#26041#24335
      end
      item
        Caption = #20449#35465#31243#24230
      end
      item
        Caption = #32467#31639#21608#26399
      end
      item
        Caption = #39318#31080#20132#25509#21333#21495
      end
      item
        Caption = #22791#27880
      end
      item
        Caption = #19994#21153
      end
      item
        Caption = #25805#20316
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = ListView1Click
    OnCustomDrawItem = ListView1CustomDrawItem
    OnDrawItem = ListView1DrawItem
  end
  object btnAddNew: TButton
    Left = 408
    Top = 1
    Width = 66
    Height = 25
    Caption = #26032'  '#22686
    TabOrder = 1
    OnClick = btnAddNewClick
  end
  object btnDelete: TButton
    Left = 539
    Top = 1
    Width = 66
    Height = 25
    Caption = #21024#38500
    TabOrder = 2
    OnClick = btnDeleteClick
  end
  object btnEdit: TButton
    Left = 473
    Top = 1
    Width = 66
    Height = 25
    Caption = #20462#25913
    TabOrder = 3
    OnClick = btnEditClick
  end
  object btnExit: TButton
    Left = 803
    Top = 1
    Width = 73
    Height = 25
    Caption = #36864#20986
    TabOrder = 4
    OnClick = btnExitClick
  end
  object btnRefresh: TButton
    Left = 605
    Top = 1
    Width = 66
    Height = 25
    Caption = #21047#26032
    TabOrder = 5
    OnClick = btnRefreshClick
  end
  object btnOK0: TButton
    Left = 688
    Top = 1
    Width = 54
    Height = 25
    Caption = #30830#23450
    TabOrder = 6
    OnClick = btnOK0Click
  end
  object btnCancel0: TButton
    Left = 742
    Top = 1
    Width = 55
    Height = 25
    Cancel = True
    Caption = #21462#28040
    TabOrder = 7
    OnClick = btnCancel0Click
  end
  object edtDebug: TEdit
    Left = 216
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 8
    Text = 'edtDebug'
    Visible = False
  end
  object btnQry: TButton
    Left = 342
    Top = 1
    Width = 66
    Height = 25
    Caption = #26597'   '#35810
    TabOrder = 9
    OnClick = btnQryClick
  end
  object plInput: TPanel
    Left = 0
    Top = 32
    Width = 953
    Height = 173
    TabOrder = 10
    object Label2: TLabel
      Left = 5
      Top = 12
      Width = 56
      Height = 14
      Caption = #23458#25143#32534#21495' '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label3: TLabel
      Left = 205
      Top = 12
      Width = 52
      Height = 14
      Caption = #23458#25143#21517#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label5: TLabel
      Left = 386
      Top = 12
      Width = 52
      Height = 14
      Caption = #33521#25991#21517#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label6: TLabel
      Left = 594
      Top = 12
      Width = 52
      Height = 14
      Caption = #20844#21496#31616#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label7: TLabel
      Left = 775
      Top = 12
      Width = 52
      Height = 14
      Caption = #23458#25143#31867#22411
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label8: TLabel
      Left = 7
      Top = 124
      Width = 52
      Height = 14
      Caption = #32463#33829#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label11: TLabel
      Left = 35
      Top = 39
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
    object Label12: TLabel
      Left = 594
      Top = 39
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
      Left = 775
      Top = 39
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
      Left = 22
      Top = 68
      Width = 39
      Height = 14
      Caption = #32852#31995#20154
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label15: TLabel
      Left = 192
      Top = 68
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
    object Label16: TLabel
      Left = 420
      Top = 68
      Width = 18
      Height = 14
      Caption = 'QQ'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label17: TLabel
      Left = 619
      Top = 68
      Width = 27
      Height = 14
      Caption = 'MSN'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label18: TLabel
      Left = 783
      Top = 68
      Width = 44
      Height = 14
      Caption = 'E-MAIL'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label19: TLabel
      Left = 772
      Top = 95
      Width = 65
      Height = 14
      Caption = #25152#23646#19994#21153#21592
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label20: TLabel
      Left = 9
      Top = 97
      Width = 52
      Height = 14
      Caption = #32467#31639#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label21: TLabel
      Left = 386
      Top = 97
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
      Left = 205
      Top = 97
      Width = 52
      Height = 14
      Caption = #32467#31639#21608#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label23: TLabel
      Left = 568
      Top = 97
      Width = 78
      Height = 14
      Caption = #39318#31080#20132#25509#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
      Visible = False
    end
    object Label24: TLabel
      Left = 204
      Top = 124
      Width = 52
      Height = 14
      Caption = #30331#35760#26102#38388
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label25: TLabel
      Left = 31
      Top = 148
      Width = 26
      Height = 14
      Caption = #22791#27880
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Label1: TLabel
      Left = 772
      Top = 119
      Width = 65
      Height = 14
      Caption = #24405#20837#25805#20316#21592
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object edtCid: TEdit
      Left = 65
      Top = 5
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MaxLength = 10
      TabOrder = 0
      Text = 'edtCid'
    end
    object edtNameShort: TEdit
      Left = 649
      Top = 5
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = 'edtNameShort'
    end
    object edtNameCh: TEdit
      Left = 261
      Top = 5
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = 'edtNameCh'
    end
    object edtNameEn: TEdit
      Left = 441
      Top = 5
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = 'edtNameEn'
    end
    object cbbClientType: TComboBox
      Left = 831
      Top = 5
      Width = 122
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 4
      Items.Strings = (
        ''
        #30452#23458
        #21516#34892)
    end
    object cbbOpType: TComboBox
      Left = 63
      Top = 117
      Width = 120
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 16
      Items.Strings = (
        ''
        #20010#20307
        #38598#20307
        #32929#20221#20844#21496
        #22269#20225
        #22806#20225)
    end
    object edtAddress: TEdit
      Left = 65
      Top = 32
      Width = 497
      Height = 21
      TabOrder = 5
      Text = 'edtAddress'
    end
    object edtTel: TEdit
      Left = 649
      Top = 32
      Width = 121
      Height = 21
      TabOrder = 6
      Text = 'edtTel'
    end
    object edtFax: TEdit
      Left = 831
      Top = 32
      Width = 121
      Height = 21
      TabOrder = 7
      Text = 'edtFax'
    end
    object edtLinkMan: TEdit
      Left = 65
      Top = 61
      Width = 121
      Height = 21
      TabOrder = 8
      Text = 'edtLinkMan'
    end
    object edtTelLinkMan: TEdit
      Left = 261
      Top = 61
      Width = 121
      Height = 21
      TabOrder = 9
      Text = 'edtTelLinkMan'
    end
    object edtQQ: TEdit
      Left = 441
      Top = 61
      Width = 121
      Height = 21
      TabOrder = 10
      Text = 'edtQQ'
    end
    object edtMsn: TEdit
      Left = 649
      Top = 61
      Width = 121
      Height = 21
      TabOrder = 11
      Text = 'edtMsn'
    end
    object edtEmail: TEdit
      Left = 831
      Top = 61
      Width = 121
      Height = 21
      TabOrder = 12
      Text = 'edtEmail'
    end
    object cbbSettlementType: TComboBox
      Left = 65
      Top = 90
      Width = 121
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 13
      Items.Strings = (
        ''
        #29616#37329
        #27719#27454
        #25903#31080
        #20854#23427)
    end
    object cbbReputation: TComboBox
      Left = 441
      Top = 90
      Width = 123
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 15
      Items.Strings = (
        ''
        #20248#31168
        #33391#22909
        #19968#33324
        #24046)
    end
    object cbbSettlementCycle: TComboBox
      Left = 261
      Top = 90
      Width = 122
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 14
      Items.Strings = (
        ''
        #35265#21333#20184#27454
        #21457#36135#21518#20184#27454
        #26376#32467)
    end
    object edtFirstOpId: TEdit
      Left = 649
      Top = 90
      Width = 121
      Height = 21
      TabOrder = 19
      Text = 'edtFirstOpId'
      Visible = False
    end
    object dtpDate: TDateTimePicker
      Left = 261
      Top = 117
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 17
    end
    object edtRemarks: TEdit
      Left = 63
      Top = 141
      Width = 511
      Height = 21
      TabOrder = 18
      Text = 'edtRemarks'
    end
    object cbbOpCodeSl: TComboBox
      Left = 839
      Top = 89
      Width = 114
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 20
    end
    object cbbOpCodeOp: TComboBox
      Left = 839
      Top = 113
      Width = 114
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 21
    end
  end
  object Button1: TButton
    Left = 892
    Top = 0
    Width = 75
    Height = 25
    Caption = #26368#23567#21270
    TabOrder = 11
    OnClick = Button1Click
  end
  object TrayIcon1: TTrayIcon
    Hint = 'ASI'
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 160
  end
end
