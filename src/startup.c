#include <stdint.h>

extern uint32_t _estack, _sidata, _sdata, _edata, _sbss, _ebss;
extern int main(void);

void Reset_Handler(void);
void Default_Handler(void);
void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

typedef void (*isr_t)(void);

__attribute__((section(".isr_vector"), used))
const isr_t vectors[16] = {
    (isr_t)&_estack,       /* 0  initial stack pointer */
    Reset_Handler,         /* 1  reset                 */
    NMI_Handler,           /* 2  NMI           */
    HardFault_Handler,     /* 3  HardFault     */
    MemManage_Handler,     /* 4  MemManage     */
    BusFault_Handler,      /* 5  BusFault      */
    UsageFault_Handler,    /* 6  UsageFault    */
    0, 0, 0, 0,            /* 7-10 reserved    */
    SVC_Handler,           /* 11 SVCall        */
    DebugMon_Handler,      /* 12 DebugMon      */
    0,                     /* 13 reserved      */
    PendSV_Handler,        /* 14 PendSV        */
    SysTick_Handler,       /* 15 SysTick       */
};

void Reset_Handler(void){
  
  // copying words from ROM to RAM
  uint32_t *src = (uint32_t *)&_sidata;
  uint32_t *start = (uint32_t *)&_sdata;
  uint32_t *end = (uint32_t *)&_edata;
  while(start < end){
    *start = *src;
    start ++;
    src ++;
  }

  // Setting zero for bss
  uint32_t *sbss = (uint32_t *)&_sbss;
  while (sbss < (uint32_t *)&_ebss){
    *sbss = 0u;
    sbss++;
  }

  main();
  for (;;){}
}

void Default_Handler(void){
  for (;;){}
}
