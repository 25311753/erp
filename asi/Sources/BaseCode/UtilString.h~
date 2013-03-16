#ifndef  __OLE_EXCEL_COMMON__
#define  __OLE_EXCEL_COMMON__

#define EXCEL_COL_LIMIT 100
//insert into excel, varg as char*, end by NULL
void Insert2Excel(Variant sheet, int row, ...) {
	va_list ap;
	va_start(ap, row);
	for(int i=0; i<EXCEL_COL_LIMIT; ++i) {
		char * val = va_arg(ap, char*);
	if (val == NULL) {
		va_end(ap);
		return;
	}
 }
 va_end(ap);
}

// Convert A, B, .... AAA, AAB to number 1, 2, ...
int StringToNumber(CString s)
{
    int r = 0 ;
    for (unsigned i = 0; i < s.GetLength(); i++)
    {
        r = r * 26 + s[i] - 'A' + 1;
    }
    return r ;
}

// Convert number 1, 2, ... to string A, B, ...
CString NumbertoString(int n)
{
        //ShowMessage(AnsiString(n));
    CString s = "" ;     // result
    int r = 0 ;         // remainder
 
    while(n)
    {
        r = n % 26 ;
//ShowMessage(AnsiString(r));
        char ch = ' ' ;
        if(r == 0)
            ch = 'Z' ;
        else
            ch = r - 1 + 'A' ;
//        s.insert(0, 1, ch) ;
//ShowMessage(ch);
//        s.SetAt(0,ch);
        s = s + ch;
 
        if(s[0] == 'Z')
            n = n / 26 - 1 ;
        else
            n /= 26 ;
    }
 
    return s ;
}



#endif  //__cjmon__
