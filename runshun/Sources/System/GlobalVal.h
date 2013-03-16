#ifndef  __SUNTEK_TELECOM_LAODY_GRACESTOCK_GLOBALVAL__
#define  __SUNTEK_TELECOM_LAODY_GRACESTOCK_GLOBALVAL__

#define INI_FILE_NAME ".\\GraceStock.ini"

typedef struct _operator_data
{
	char op_code[80];
	char op_name[80];
	int  op_class;
	char op_dept[80];
	char op_cpcode[80];
} OPERATOR_DATA;

extern OPERATOR_DATA g_theOperator;

#endif //__SUNTEK_TELECOM_LAODY_GRACESTOCK_GLOBALVAL__