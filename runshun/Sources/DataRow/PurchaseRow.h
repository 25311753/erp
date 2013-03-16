#ifndef  __SUNTEK_TELECOM_LAODY_GRACESTOCK_PURCHASEROW__
#define  __SUNTEK_TELECOM_LAODY_GRACESTOCK_PURCHASEROW__

#include "RamRow.h"

class CAskPurchaseRow : public CRamRow
{
public:
	CAskPurchaseRow();
	bool ReadFromDB(TQuery *pQuery);
	CAskPurchaseRow& operator=(CAskPurchaseRow &row);

	char				ap_code        [80];
	TDateTime		ap_needdate    ;
	char				ap_type        [80];
	TDateTime		ap_reqdate     ;
	char				ap_buytype     [80];
	char				ap_reqdepart   [80];
	char				ap_sdcode      [80];
	char				ap_chargedep   [80];
	char				ap_prjcode     [80];
	char				ap_usage       [80];
	char				ap_gacode      [80];
	char				ap_chkflag     [80];
	char				ap_chkspec     [80];
	char				ap_hmcode      [80];
	char				ap_shcode			 [80];
	char				ap_treatflag	 [10];
	TDateTime		ap_affirmdate  ;
	TDateTime		ap_modifydate  ;
	TDateTime		ap_inputdate   ;
	TDateTime		ap_printdate   ;
	TDateTime		ap_opertime    ;
};

class CPurchaseDetailRow : public CRamRow
{
public:
	CPurchaseDetailRow();
	bool ReadFromDB(TQuery *pQuery);
	CPurchaseDetailRow& operator=(CPurchaseDetailRow &row);
	CString GetItem();

	char			pd_code        [80];
	char			pd_mncode      [80];
	char			pd_ducode      [80];
	double		pd_count       ;
	char			pd_cooper      [80];
	char			pd_tscode      [80];
	char			pd_endflag     [80];
	TDateTime pd_opertime    ;
};

#endif  //__SUNTEK_TELECOM_LAODY_GRACESTOCK_PURCHASEROW__