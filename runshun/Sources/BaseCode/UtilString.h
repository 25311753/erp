#ifndef  __UTIL_STRING__ 
#define  __UTIL_STRING__ 


AnsiString randStr(int strlen)
{
int len=1;
AnsiString str;
//if(strlen)
//len=rand()%strlen;

for(int i=0;i<strlen;i++)
{
//[a,b)
int a=65;
int b=91;
int r = (rand()%(b-a)) + a ;
str+=AnsiString(char(r));

}
return str;
}

AnsiString randNum(int strlen)
{
int len=1;
AnsiString str;
//if(strlen)
//len=rand()%strlen;

for(int i=0;i<strlen;i++)
{
//[a,b)
int a=48;
int b=58;
int r = (rand()%(b-a)) + a ;
str+=AnsiString(char(r));
}
return str;
}

#endif  //__cjmon__
