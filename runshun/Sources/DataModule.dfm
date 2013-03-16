object dm1: Tdm1
  OldCreateOrder = False
  Left = 410
  Top = 126
  Height = 375
  Width = 544
  object db1: TDatabase
    AliasName = 'runshun'
    DatabaseName = 'runshun'
    LoginPrompt = False
    Params.Strings = (
      'user name=runshunuser'
      'password=runshunuser')
    SessionName = 'Default'
    Left = 24
    Top = 14
  end
  object DS1: TDataSource
    Left = 73
    Top = 14
  end
  object Query1: TQuery
    DatabaseName = 'runshun'
    Left = 131
    Top = 14
  end
  object Query2: TQuery
    DatabaseName = 'runshun'
    Left = 176
    Top = 14
  end
  object Query3: TQuery
    DatabaseName = 'runshun'
    Left = 229
    Top = 14
  end
  object DSRights: TDataSource
    DataSet = ClassRights
    Left = 299
    Top = 68
  end
  object SPcomn: TStoredProc
    DatabaseName = 'runshun'
    StoredProcName = 'backtosemidel;1'
    Left = 23
    Top = 68
  end
  object DSOper: TDataSource
    DataSet = OperTab
    Left = 89
    Top = 68
  end
  object OperTab: TTable
    DatabaseName = 'runshun'
    TableName = 'dbo.operator'
    Left = 168
    Top = 68
  end
  object ClassRights: TTable
    DatabaseName = 'runshun'
    TableName = 'dbo.classrights'
    Left = 239
    Top = 68
  end
  object Table1: TTable
    DatabaseName = 'runshun'
    Left = 288
    Top = 14
  end
  object sqlPrint: TQuery
    DatabaseName = 'runshun'
    SQL.Strings = (
      
        'select pd_code,df_mfplan,df_plandate,cf_mfcode,mf_shortname,cf_q' +
        'uotenum,cf_card,cf_quoteprice,cf_quotermb,'
      
        '  cf_higgleprice,pm_name,dd_name,cf_quotenum*cf_higgleprice,cf_i' +
        'nvoice,cf_deliverday,df_planrem'
      
        'from PurchaseDetail,DecideFactory,CompareFactory,Manufactur,DicP' +
        'ayment,DicDelivery'
      'where pd_code=df_apcode'
      'and pd_code=cf_apcode'
      'and cf_mfcode=mf_code'
      'and cf_pmcode=pm_code'
      'and cf_ddcode=dd_code'
      'and pd_code like '#39'P4B0375_'#39)
    Left = 24
    Top = 152
  end
  object db2: TDatabase
    DatabaseName = 'hxerpdb'
    DriverName = 'SQL Server'
    KeepConnection = False
    LoginPrompt = False
    Params.Strings = (
      'DATABASE NAME=hxerpdb'
      'USER NAME=hxuser'
      'ODBC DSN=hxerpdb'
      'OPEN MODE=READ/WRITE'
      'BATCH COUNT=200'
      'LANGDRIVER='
      'MAX ROWS=-1'
      'SCHEMA CACHE DIR='
      'SCHEMA CACHE SIZE=8'
      'SCHEMA CACHE TIME=-1'
      'SQLPASSTHRU MODE=SHARED AUTOCOMMIT'
      'SQLQRYMODE='
      'ENABLE SCHEMA CACHE=FALSE'
      'ENABLE BCD=FALSE'
      'ROWSET SIZE=20'
      'BLOBS TO CACHE=64'
      'BLOB SIZE=32'
      'PASSWORD=hanrigid')
    SessionName = 'Default'
    Left = 87
    Top = 150
  end
  object sqlElse: TQuery
    DatabaseName = 'hxerpdb'
    SQL.Strings = (
      'select * from MeterTech')
    Left = 136
    Top = 152
  end
  object Query4: TQuery
    DatabaseName = 'runshun'
    Left = 344
    Top = 16
  end
  object sqlPrint2: TQuery
    DatabaseName = 'runshun'
    SQL.Strings = (
      
        'select pd_code,df_mfplan,df_plandate,cf_mfcode,mf_shortname,cf_q' +
        'uotenum,cf_card,cf_quoteprice,cf_quotermb,'
      
        '  cf_higgleprice,pm_name,dd_name,cf_quotenum*cf_higgleprice,cf_i' +
        'nvoice,cf_deliverday,df_planrem'
      
        'from PurchaseDetail,DecideFactory,CompareFactory,Manufactur,DicP' +
        'ayment,DicDelivery'
      'where pd_code=df_apcode'
      'and pd_code=cf_apcode'
      'and cf_mfcode=mf_code'
      'and cf_pmcode=pm_code'
      'and cf_ddcode=dd_code'
      'and pd_code like '#39'P4B0375_'#39)
    Left = 64
    Top = 200
  end
  object sqlPrintDeclare: TQuery
    DatabaseName = 'runshun'
    SQL.Strings = (
      
        'select pd_code,df_mfplan,df_plandate,cf_mfcode,mf_shortname,cf_q' +
        'uotenum,cf_card,cf_quoteprice,cf_quotermb,'
      
        '  cf_higgleprice,pm_name,dd_name,cf_quotenum*cf_higgleprice,cf_i' +
        'nvoice,cf_deliverday,df_planrem'
      
        'from PurchaseDetail,DecideFactory,CompareFactory,Manufactur,DicP' +
        'ayment,DicDelivery'
      'where pd_code=df_apcode'
      'and pd_code=cf_apcode'
      'and cf_mfcode=mf_code'
      'and cf_pmcode=pm_code'
      'and cf_ddcode=dd_code'
      'and pd_code like '#39'P4B0375_'#39)
    Left = 184
    Top = 248
  end
end
