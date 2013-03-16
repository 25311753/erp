//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PurchaseRow.h"

//----------------------------------------------------------------------------
CAskPurchaseRow::CAskPurchaseRow()
{
	InitMemberField(ap_code        );
	InitMemberField(ap_needdate    );
	InitMemberField(ap_type        );
	InitMemberField(ap_reqdate     );
	InitMemberField(ap_buytype     );
	InitMemberField(ap_reqdepart   );
	InitMemberField(ap_sdcode      );
	InitMemberField(ap_chargedep   );
	InitMemberField(ap_prjcode     );
	InitMemberField(ap_usage       );
	InitMemberField(ap_gacode      );
	InitMemberField(ap_chkflag     );
	InitMemberField(ap_chkspec     );
	InitMemberField(ap_hmcode      );
	InitMemberField(ap_shcode      );
	InitMemberField(ap_treatflag   );
	InitMemberField(ap_affirmdate  );
	InitMemberField(ap_modifydate  );
	InitMemberField(ap_inputdate   );
	InitMemberField(ap_printdate   );
	InitMemberField(ap_opertime    );
}

CAskPurchaseRow& CAskPurchaseRow::operator=(CAskPurchaseRow &row)
{
	memcpy(m_aNull,row.m_aNull,sizeof(m_aNull));

	strcpy(ap_code      ,row.ap_code      );
	strcpy(ap_type      ,row.ap_type      );
	strcpy(ap_buytype   ,row.ap_buytype   );
	strcpy(ap_reqdepart ,row.ap_reqdepart );
	strcpy(ap_sdcode    ,row.ap_sdcode    );
	strcpy(ap_chargedep ,row.ap_chargedep );
	strcpy(ap_prjcode   ,row.ap_prjcode   );
	strcpy(ap_usage     ,row.ap_usage     );
	strcpy(ap_gacode    ,row.ap_gacode    );
	strcpy(ap_chkflag   ,row.ap_chkflag   );
	strcpy(ap_chkspec   ,row.ap_chkspec   );
	strcpy(ap_hmcode    ,row.ap_hmcode    );
	strcpy(ap_shcode    ,row.ap_shcode    );
	strcpy(ap_treatflag ,row.ap_treatflag );

	ap_needdate  =row.ap_needdate;
	ap_reqdate   =row.ap_reqdate;
	ap_affirmdate=row.ap_affirmdate;
	ap_modifydate=row.ap_modifydate;
	ap_inputdate =row.ap_inputdate;
	ap_printdate =row.ap_printdate;
	ap_opertime  =row.ap_opertime;	
	
	return *this;
}


bool CAskPurchaseRow::ReadFromDB(TQuery *pQuery)
{
	ReadMember(ap_code      ,pQuery->FieldByName("ap_code"      ));
	ReadMember(ap_needdate  ,pQuery->FieldByName("ap_needdate"  ));
	ReadMember(ap_type      ,pQuery->FieldByName("ap_type"      ));
	ReadMember(ap_reqdate   ,pQuery->FieldByName("ap_reqdate"   ));
	ReadMember(ap_buytype   ,pQuery->FieldByName("ap_buytype"   ));
	ReadMember(ap_reqdepart ,pQuery->FieldByName("ap_reqdepart" ));
	ReadMember(ap_sdcode    ,pQuery->FieldByName("ap_sdcode"    ));
	ReadMember(ap_chargedep ,pQuery->FieldByName("ap_chargedep" ));
	ReadMember(ap_prjcode   ,pQuery->FieldByName("ap_prjcode"   ));
	ReadMember(ap_usage     ,pQuery->FieldByName("ap_usage"     ));
	ReadMember(ap_gacode    ,pQuery->FieldByName("ap_gacode"    ));
	ReadMember(ap_chkflag   ,pQuery->FieldByName("ap_chkflag"   ));
	ReadMember(ap_chkspec   ,pQuery->FieldByName("ap_chkspec"   ));
	ReadMember(ap_hmcode    ,pQuery->FieldByName("ap_hmcode"    ));
	ReadMember(ap_shcode    ,pQuery->FieldByName("ap_shcode"    ));
	ReadMember(ap_treatflag ,pQuery->FieldByName("ap_treatflag" ));
	ReadMember(ap_affirmdate,pQuery->FieldByName("ap_affirmdate"));
	ReadMember(ap_modifydate,pQuery->FieldByName("ap_modifydate"));
	ReadMember(ap_inputdate ,pQuery->FieldByName("ap_inputdate" ));
	ReadMember(ap_printdate ,pQuery->FieldByName("ap_printdate" ));
	ReadMember(ap_opertime  ,pQuery->FieldByName("ap_opertime"  ));

	return true;
}

//-------------------------------------------------------------------------------
CPurchaseDetailRow::CPurchaseDetailRow()
{
	InitMemberField(pd_code    );
	InitMemberField(pd_mncode  );
	InitMemberField(pd_ducode  );
	InitMemberField(pd_count   );
	InitMemberField(pd_cooper  );
	InitMemberField(pd_tscode	 );
	InitMemberField(pd_endflag );
	InitMemberField(pd_opertime);
}

CPurchaseDetailRow& CPurchaseDetailRow::operator=(CPurchaseDetailRow &row)
{
	memcpy(m_aNull,row.m_aNull,sizeof(m_aNull));

	strcpy(pd_code    ,row.pd_code    );
	strcpy(pd_mncode  ,row.pd_mncode  );
	strcpy(pd_ducode  ,row.pd_ducode  );
	strcpy(pd_cooper  ,row.pd_cooper  );
	strcpy(pd_tscode  ,row.pd_tscode  );
	strcpy(pd_endflag ,row.pd_endflag );

	pd_count   =row.pd_count;
	pd_opertime=row.pd_opertime;

	return *this;
}

bool CPurchaseDetailRow::ReadFromDB(TQuery *pQuery)
{
	ReadMember(pd_code    ,pQuery->FieldByName("pd_code"    ));
	ReadMember(pd_mncode  ,pQuery->FieldByName("pd_mncode"  ));
	ReadMember(pd_ducode  ,pQuery->FieldByName("pd_ducode"  ));
	ReadMember(pd_count   ,pQuery->FieldByName("pd_count"   ));
	ReadMember(pd_cooper  ,pQuery->FieldByName("pd_cooper"  ));
	ReadMember(pd_tscode  ,pQuery->FieldByName("pd_tscode"  ));
	ReadMember(pd_endflag ,pQuery->FieldByName("pd_endflag" ));
	ReadMember(pd_opertime,pQuery->FieldByName("pd_opertime"));

	return true;
}

CString CPurchaseDetailRow::GetItem()
{
	if(pd_code[0]=='\0')	return "";
	return CString(pd_code+strlen(pd_code)-1);
}


