inherited InputCorpForm: TInputCorpForm
  Left = 234
  Top = 184
  Caption = #20844#21496#21029#36664#20837
  OldCreateOrder = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel1: TPanel
    Caption = #20844#21496#21029#36664#20837
    Font.Charset = DEFAULT_CHARSET
  end
  inherited Panel2: TPanel
    inherited Label1: TLabel
      Width = 77
      Caption = #20844#21496#21029#20195#30908':'
    end
    inherited Label2: TLabel
      Left = 41
      Width = 63
      Caption = #20844#21496#21517#31281':'
    end
    inherited edtcode: TEdit
      Left = 106
      CharCase = ecUpperCase
      MaxLength = 1
    end
    inherited edtname: TEdit
      Left = 106
      Width = 253
      MaxLength = 20
      OnKeyDown = edtnameKeyDown
    end
    inherited ListView1: TListView
      Columns = <
        item
          Width = 0
        end
        item
          Caption = #20195#30908
          Width = 40
        end
        item
          Caption = '          '#20844#21496#21517#31281
          Width = 200
        end>
      OnClick = ListView1Click
    end
  end
  inherited Panel3: TPanel
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
    Font.Charset = DEFAULT_CHARSET
  end
end
