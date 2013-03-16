inherited MiddleTypeForm: TMiddleTypeForm
  Left = 223
  Top = 159
  Height = 426
  Caption = #20013#39006#24314#27284
  FormStyle = fsStayOnTop
  OldCreateOrder = True
  OnActivate = FormActivate
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel1: TPanel
    Caption = #20013#39006#24314#27284
    Font.Charset = DEFAULT_CHARSET
  end
  inherited Panel2: TPanel
    Height = 316
    inherited Label1: TLabel
      Left = 14
      Top = 41
      Width = 63
      Alignment = taRightJustify
      Caption = #20013#39006#20195#30908':'
    end
    inherited Label2: TLabel
      Left = 14
      Top = 68
      Width = 63
      Alignment = taRightJustify
      Caption = #20013#39006#21517#31281':'
    end
    object Label3: TLabel [2]
      Left = 42
      Top = 12
      Width = 35
      Height = 13
      Alignment = taRightJustify
      Caption = #22823#39006':'
    end
    object Label4: TLabel [3]
      Left = 204
      Top = 41
      Width = 42
      Height = 13
      Alignment = taRightJustify
      Caption = '('#20841#20301')'
    end
    inherited edtcode: TEdit
      Left = 81
      Top = 37
      MaxLength = 2
      OnExit = edtcodeExit
    end
    inherited edtname: TEdit
      Left = 81
      Top = 64
      MaxLength = 40
      OnKeyDown = edtnameKeyDown
    end
    inherited ListView1: TListView
      Top = 92
      Height = 226
      Columns = <
        item
          Width = 0
        end
        item
          Alignment = taCenter
          Caption = #20195#30908
          Width = 40
        end
        item
          Caption = '                  '#21517#31281
          Width = 300
        end>
      OnClick = ListView1Click
    end
    object cbltype: TComboBox
      Left = 81
      Top = 8
      Width = 290
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnChange = cbltypeChange
    end
  end
  inherited Panel3: TPanel
    Height = 316
    inherited btnok: TBitBtn
      OnClick = btnokClick
    end
    inherited btnprint: TBitBtn
      OnClick = btnprintClick
    end
    inherited btnref: TBitBtn
      OnClick = btnrefClick
    end
  end
  inherited PanelHint: TPanel
    Top = 365
    Font.Charset = DEFAULT_CHARSET
  end
end
