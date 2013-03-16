object CalcForm: TCalcForm
  Left = 290
  Top = 456
  Width = 870
  Height = 269
  Caption = #25104#26412#26680#31639
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 16
    Width = 39
    Height = 13
    Caption = #24037#21333#21495' '
  end
  object Label2: TLabel
    Left = 208
    Top = 16
    Width = 72
    Height = 13
    Caption = #25253#20851#22522#26412#25104#26412
  end
  object edtCid: TEdit
    Left = 72
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'edtCid'
  end
  object edtBaseFree: TEdit
    Left = 280
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'edtBaseFree'
  end
  object btnMod: TButton
    Left = 424
    Top = 16
    Width = 75
    Height = 25
    Caption = #20462#25913
    TabOrder = 2
  end
  object btnQuery: TButton
    Left = 504
    Top = 16
    Width = 75
    Height = 25
    Caption = #26597#35810
    TabOrder = 3
  end
  object lstView: TListView
    Left = 32
    Top = 40
    Width = 785
    Height = 153
    Columns = <>
    RowSelect = True
    TabOrder = 4
    ViewStyle = vsReport
  end
end
