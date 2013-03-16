//说明：本文件定义的函数都在函数内部动态创建窗体，函数结束後自动删除
//      本文件内所有的函数都没有应用全局变量的窗体
#ifndef LDY_INTERFACE_H__
#define LDY_INTERFACE_H__
#include "LfcString.h"
#include "LfcTempl.h"

//权限参数定义
#define AUTH_AUTO			-1
#define AUTH_NONE					0		//没有权限
#define	AUTH_READ					1		//只读权限
#define	AUTH_FULL					2		//读写权限

#define NULL_RIGHT  2  //权限没定义时缺省值



#define ITEMSIZE(p) (sizeof(p)/sizeof(p[0]))

#define CALL_FORM(FORM) {FORM *pForm; \
	try {	pForm=new FORM(Application); } \
	catch (Exception &exception) \
  { \
  	Application->ShowException(&exception); \
    return; \
	} \
  pForm->ShowModal(); \
  delete pForm; }

//等级权限设置接口，文件ClassRight.*
void ClassRight(int nAuth=AUTH_FULL);
//取得操作等级的权限
int GetClassRight(int nClass,LPCSTR lpszMenu);
//取得操作员的权限
int GetOperatorRight(LPCSTR	lpszOper,LPCSTR lpszMenu);

//------------------------------------------------------------------
//采购部门档输入接口，文件StockDepart.*
void StockDepart(int nAuth=AUTH_FULL);

//部门别输入接口，文件DicDepart.*
void DicDepart(int nAuth=AUTH_FULL);

//单位档输入接口，文件DicUnits.*
void DicUnits(int nAuth=AUTH_FULL);

//交货地点输入接口，文件GoodsAddr.*
void GoodsAddr(int nAuth=AUTH_FULL);

//状态档输入接口，文件DicStatus.*
void DicStatus(int nAuth=AUTH_FULL);

//厂商资料档接口，文件：Factory.*
void FactoryInput(LPCSTR lpszID,int nAuth=AUTH_FULL);
void FactoryInput(int nAuth=AUTH_FULL);

//厂商资料查询接口，文件：FactorySearch.*
void FactorySearch(int nAuth=AUTH_FULL);

//经办人员档接口，文件HandleMan.*
void HandleMan(int nAuth=AUTH_FULL);

//部门公司档输入接口，文件DepartCorp.*
void DepartCorp(int nAuth=AUTH_FULL);

//请购单输入接口，文件：AskPurchase.*
void AskPurchase(int nAuth=AUTH_FULL);
void AskPurchase(LPCSTR lpszID,int nAuth=AUTH_FULL);
//统购单输入接口，文件：AskPurchase.*
void UnionPurchase(LPCSTR lpszID,int nAuth=AUTH_FULL);

//材料编号查询接口
void QueryMaterialCode(int nAuth=AUTH_FULL);

//请购单确认接口，文件AskPurchaseAfm.*
void AskPurchaseAfm(int nAuth=AUTH_FULL);

//请购单指派采购经办接口，文件AskPurchaseSetSH.*
void AskPurchaseSetSH(int nAuth=AUTH_FULL);

//采购经办档接口，文件StockHandleman.*
void StockHandleman(int nAuth=AUTH_FULL);

//付款方式档输入接口，文件DicPayment.*
void DicPayment(int nAuth=AUTH_FULL);

//请购单列表查询接口，文件：AskPurchaseList.*
void AskPurchaseList(int nAuth=AUTH_FULL);

//请购过程接口，文件：PurchaseRoad.*
void PurchaseRoad(int nAuth=AUTH_FULL);

//订购单输入接口，文件：BookFactory.*
void BookFactory(int nAuth=AUTH_FULL);
void BookFactory(LPCSTR lpszID,int nAuth=AUTH_FULL);

//开立发票抬头档输入接口，文件InvoiceTitle.*
void InvoiceTitle(int nAuth=AUTH_FULL);

//收货经办档接口，文件RcptHandleman.*
void RcptHandleman(int nAuth=AUTH_FULL);

//请购单结案接口，文件AskPurchaseEnd.*
void AskPurchaseEnd(int nAuth=AUTH_FULL);
void AskPurchaseEnd(LPCSTR lpszID,int nAuth=AUTH_FULL);

//订购单列表查询接口，文件：BookFactoryList.*
void BookFactoryList(int nAuth=AUTH_FULL);

//采购记录表接口，文件：MaterBookList.*
void MaterBookList(int nAuth=AUTH_FULL);

//合约采购档接口，文件：TreatStock.*
void TreatStock(int nAuth=AUTH_FULL);
void TreatStock(LPCSTR lpszID,int nAuth=AUTH_FULL);

//合约采购列表接口，文件：TreatStockList.*
void TreatStockList(int nAuth=AUTH_FULL);

//合约采购记录表接口，文件：TreatStockRecord.*
void TreatStockRecord(int nAuth=AUTH_FULL);

//已接案逾期未订明细接口，文件：APAffirmAndNotBook.*
void APAffirmAndNotBook(int nAuth=AUTH_FULL);

//新接案件统计报表接口，文件：AskPurchaseAfmList.*
void AskPurchaseAfmList(int nAuth=AUTH_FULL);

//订购单列印接口，文件：BookMultiPrn.*
void BookMultiPrn(int nAuth=AUTH_FULL);

//询价单列印接口，文件：SpeerMultiPrn.*
void SpeerMultiPrn(int nAuth=AUTH_FULL);

//订购超过4次汇总表接口，文件：Book4Times.*
void Book4Times(int nAuth=AUTH_FULL);

//已订购未受料明细接口，文件：BookNotAcceptList.*
void BookNotAcceptList(int nAuth=AUTH_FULL);

//已收料未请款明细接口，文件：AcceptNotPayList.*
void AcceptNotPayList(int nAuth=AUTH_FULL);

//议价逾期未完成案件统计表接口，文件：SumHiggleNotEnd.*
void SumHiggleNotEnd(int nAuth=AUTH_FULL);

//呈核逾期未完成案件统计表接口，文件：SumDecideNotEnd.*
void SumDecideNotEnd(int nAuth=AUTH_FULL);

//订购逾期未完成案件统计表接口，文件：SumBookNotEnd.*
void SumBookNotEnd(int nAuth=AUTH_FULL);

//逾期未交货案件统计表接口，文件：SumBookNotAcpt.*
void SumBookNotAcpt(int nAuth=AUTH_FULL);

//合约采购确认接口，文件TreatStockAfm.*
//参数：nType=0 确认，nType=1 会计确认
void TreatStockAfm(int nType,int nAuth=AUTH_FULL);

//统购材料清单接口，文件：PrnUnitTreatList
void PrnUnitTreatList(int nAuth=AUTH_FULL);

//统购材料列表接口，文件：UnitTreatList.*
void UnitTreatList(int nAuth=AUTH_FULL);

//宏信技术代号与材料编号对照表接口，文件：MaterHXCompare.*
void MaterHXCompare(int nAuth=AUTH_FULL);

//原料采购记录表接口，文件：StuffBookList.*
void StuffBookList(int nAuth=AUTH_FULL);
void StuffBookList(LPCSTR lpszID,int nAuth=AUTH_FULL);

//交货方式档输入接口，文件DicDelivery.*
void DicDelivery(int nAuth=AUTH_FULL);

//发票税率档输入接口，文件DicInvoice.*
void DicInvoice(int nAuth=AUTH_FULL);

//原料请购单列表查询接口，文件：RawPurchaseList.*
void RawPurchaseList(int nAuth=AUTH_FULL);

//原料订购单列表查询接口，文件：RawBookFactoryList.*
void RawBookFactoryList(int nAuth=AUTH_FULL);

//请购单档号页号建档,文件：ApFilePage.*
void ApFilePage(int nAuth=AUTH_FULL);

//请购单归档列表,文件：ApFPList.*
void ApFPList(int nAuth=AUTH_FULL);

//材料与厂商订购统计,文件：SumMaterialnoFactory.*
void SumMnFact(int nAuth=AUTH_FULL);

//材料外观展示,文件：MaterialPicEdit.*
void MaterialPicture(int nAuth=AUTH_FULL);

//材料编号原则 文件　F_MaterialRem
void MaterialRem(int nAuth=AUTH_FULL);

//采购记录模糊搜索接口，文件：MaterBookList2.*
void MaterBookList2(int nAuth=AUTH_FULL);
//asi
void DicClient(int nAuth=AUTH_FULL);
void DicSupplier(int nAuth=AUTH_FULL);
void Operation(int nAuth=AUTH_FULL);
void FinanceOp(int nAuth=AUTH_FULL);
void Commition(int nAuth=AUTH_FULL);
void NewClientPrize(int nAuth=AUTH_FULL);
void QrySale(int nAuth=AUTH_FULL);
void AlarmSale(int nAuth=AUTH_FULL);
void YjQry(int nAuth=AUTH_FULL);
void Tc(int nAuth=AUTH_FULL);
void XkQry(int nAuth=AUTH_FULL);
void OpQry(int nAuth=AUTH_FULL);
void XkCSSZ(int nAuth=AUTH_FULL);
void TcCSSZ(int nAuth=AUTH_FULL);
void YjCSSZ(int nAuth=AUTH_FULL);


#endif
