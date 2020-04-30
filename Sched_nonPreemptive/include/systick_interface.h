#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

typedef void(* STK_callBack_t)(void);

#define STK_CLKSRC_DIV_1        0x00000004
#define STK_CLKSRC_DIV_8        0x00000000
#define STK_INTERRUPT_ENABLE    0x00000002
#define STK_INTERRUPT_DISABLE   0x00000000
#define STK_STATE_ENABLE        0x00000001
#define STK_STATE_DISABLE       0x00000000

void STK_Init(void);
void STK_configLoadVal(u32 val);
void STK_controlState(u32 state);
void STK_setCallBack(STK_callBack_t ptr);
void STK_controlInterrupt(u32 state);
u32 STK_getVal(void);
u8 STK_getZeroFlag(void);
void STK_setTimeUS(u32 time, u32 AHB_CLK);
void STK_setClkSrc(u32 src);

#endif
