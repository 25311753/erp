#ifndef  _common_const_
#define  _common_const_

enum E_OPERATOR_TYPE{
        E_OPERATOR_TYPE_ADMIN           = 1,
        E_OPERATOR_TYPE_DIRECTOR        = 2,   //总监
        E_OPERATOR_TYPE_MANAGER              = 3,
        E_OPERATOR_TYPE_FINANCE              = 4,
        E_OPERATOR_TYPE_SALER               = 5,
        E_OPERATOR_TYPE_OPERATOR             = 6
};

#define D_SETTLEMENT_CYCLE_SEE          "见单付款"
#define D_SETTLEMENT_CYCLE_RELEASE      "发货后付款"
#define D_SETTLEMENT_CYCLE_MONTH        "月结"

#endif
