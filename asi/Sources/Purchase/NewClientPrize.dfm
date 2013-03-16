object NewClientPrizeForm: TNewClientPrizeForm
  Left = 1585
  Top = 302
  Width = 881
  Height = 537
  Caption = #26032#23458#22870#21169
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 464
    Width = 30
    Height = 13
    Caption = #21512#35745'  '
  end
  object Label2: TLabel
    Left = 48
    Top = 464
    Width = 45
    Height = 13
    Caption = #26032#23458#25968':  '
  end
  object lbTotalNewCliCnt: TLabel
    Left = 104
    Top = 464
    Width = 6
    Height = 13
    Caption = '0'
  end
  object btnQry: TButton
    Left = 0
    Top = 0
    Width = 63
    Height = 25
    Caption = #26597#35810
    TabOrder = 0
    OnClick = btnQryClick
  end
  object lvNewCliPrize: TListView
    Left = 1
    Top = 59
    Width = 845
    Height = 398
    Columns = <
      item
        Caption = #25805#20316#26085#26399
        Width = 100
      end
      item
        Caption = #25805#20316#21333#21495
        Width = 100
      end
      item
        Caption = #23458#25143#31616#31216
        Width = 70
      end
      item
        Caption = #26412#31080#21033#28070
        Width = 80
      end
      item
        Caption = #26032#23458#22870#21169
        Width = 80
      end
      item
        Caption = #26159#21542#21457#25918
        Width = 70
      end
      item
        Caption = #21457#25918#26085#26399
        Width = 80
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object plQuery: TPanel
    Left = 1
    Top = 24
    Width = 844
    Height = 33
    TabOrder = 2
    object Panel15: TPanel
      Left = 4
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23458#25143#31616#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
    object cbbClShortName: TComboBox
      Left = 66
      Top = 3
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object Panel20: TPanel
      Left = 192
      Top = 1
      Width = 74
      Height = 21
      Alignment = taLeftJustify
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26376#20221
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 2
      object cbIsQryByDate: TCheckBox
        Left = 58
        Top = 4
        Width = 16
        Height = 17
        Caption = 'cbIsQryByDate'
        TabOrder = 0
      end
    end
    object dtpQryDateBegin: TDateTimePicker
      Left = 267
      Top = 1
      Width = 66
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 3
    end
    object dtpQryDateEnd: TDateTimePicker
      Left = 350
      Top = 1
      Width = 66
      Height = 21
      CalAlignment = dtaLeft
      Date = 41260.3921510648
      Time = 41260.3921510648
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 4
    end
  end
  object Edit1: TEdit
    Left = 440
    Top = 0
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'Edit1'
    Visible = False
  end
  object Button1: TButton
    Left = 790
    Top = 0
    Width = 75
    Height = 25
    Caption = #26368#23567#21270
    TabOrder = 4
    OnClick = Button1Click
  end
  object TrayIcon1: TTrayIcon
    Hint = 'ASI'
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 1012
  end
end
