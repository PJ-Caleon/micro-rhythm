#ifndef STM32F401_H
#define STM32F401_H
#include <stdint.h>

#define BIT(n) (1u << (n))
#define SYSCLK_HZ 84000000u

/* ======================= Base Addresses ======================= */
/* APB1 */
#define TIM2_BASE     0x40000000u
#define I2C1_BASE     0x40005400u
/* APB2 */
#define TIM1_BASE     0x40010000u
#define ADC1_BASE     0x40012000u
#define ADC_COMMON_BASE 0x40012300u
#define SYSCFG_BASE   0x40013800u
#define EXTI_BASE     0x40013C00u
/* AHB1 */
#define GPIOA_BASE    0x40020000u
#define GPIOB_BASE    0x40020400u
#define CRC_BASE      0x40023000u
#define RCC_BASE      0x40023800u
#define FLASH_BASE_R  0x40023C00u
#define DMA1_BASE     0x40026000u
#define DMA2_BASE     0x40026400u

#define SYSTICK_BASE  0xE000E010u

/* ======================= Register Structs ======================= */
typedef struct {
  volatile uint32_t MODER;    /* 0x00: 00=in, 01=out, 10=af, 11=analog */
  volatile uint32_t OTYPER;   /* 0x04: 0=pp, 1=od */
  volatile uint32_t OSPEEDR;  /* 0x08: 00=low, 01=med, 10=fast, 11=high */
  volatile uint32_t PUPDR;    /* 0x0C: 00=none, 01=pu, 10=pd */
  volatile uint32_t IDR;      /* 0x10 */
  volatile uint32_t ODR;      /* 0x14 */
  volatile uint32_t BSRR;     /* 0x18: [15:0] set, [31:16] reset */
  volatile uint32_t LCKR;     /* 0x1C */
  volatile uint32_t AFRL;     /* 0x20: pins 0-7 */
  volatile uint32_t AFRH;     /* 0x24: pins 8-15 */
} GPIO_TypeDef;

typedef struct {
  volatile uint32_t CTRL; 
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile uint32_t CALIB;
} Systick_TypeDef;

typedef struct {
  volatile uint32_t CR;          /* 0x00 */
  volatile uint32_t PLLCFGR;     /* 0x04 */
  volatile uint32_t CFGR;        /* 0x08 */
  volatile uint32_t CIR;         /* 0x0C */
  volatile uint32_t AHB1RSTR;    /* 0x10 */
  volatile uint32_t AHB2RSTR;    /* 0x14 */
  volatile uint32_t RES0[2];     /* 0x18..0x1C */
  volatile uint32_t APB1RSTR;    /* 0x20 */
  volatile uint32_t APB2RSTR;    /* 0x24 */
  volatile uint32_t RES1[2];     /* 0x28..0x2C */
  volatile uint32_t AHB1ENR;     /* 0x30 */
  volatile uint32_t AHB2ENR;     /* 0x34 */
  volatile uint32_t RES2[2];     /* 0x38..0x3C */
  volatile uint32_t APB1ENR;     /* 0x40 */
  volatile uint32_t APB2ENR;     /* 0x44 */
  volatile uint32_t RES3[2];     /* 0x48..0x4C */
  volatile uint32_t AHB1LPENR;   /* 0x50 */
  volatile uint32_t AHB2LPENR;   /* 0x54 */
  volatile uint32_t RES4[2];     /* 0x58..0x5C */
  volatile uint32_t APB1LPENR;   /* 0x60 */
  volatile uint32_t APB2LPENR;   /* 0x64 */
  volatile uint32_t RES5[2];     /* 0x68..0x6C */
  volatile uint32_t BDCR;        /* 0x70 */
  volatile uint32_t CSR;         /* 0x74 */
  volatile uint32_t RES6[2];     /* 0x78..0x7C */
  volatile uint32_t SSCGR;       /* 0x80 */
  volatile uint32_t PLLI2SCFGR;  /* 0x84 */
  volatile uint32_t RES7;        /* 0x88 */
  volatile uint32_t DCKCFGR;     /* 0x8C */
} RCC_TypeDef;

typedef struct {
  volatile uint32_t SR, CR1, CR2, SMPR1, SMPR2;          /* 0x00..0x10 */
  volatile uint32_t JOFR[4];                             /* 0x14..0x20 */
  volatile uint32_t HTR, LTR, SQR1, SQR2, SQR3, JSQR;    /* 0x24..0x38 */
  volatile uint32_t JDR[4];                              /* 0x3C..0x48 */
  volatile uint32_t DR;                                  /* 0x4C */
} ADC_TypeDef;

/* TIM1 (advanced) and TIM2 (general) share this layout up to DMAR.
   RCR/BDTR exist on TIM1 only (reserved on TIM2). */
typedef struct {
  volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCMR2, CCER;  /* 0x00..0x20 */
  volatile uint32_t CNT, PSC, ARR, RCR, CCR1, CCR2, CCR3, CCR4;         /* 0x24..0x40 */
  volatile uint32_t BDTR, DCR, DMAR;                                    /* 0x44..0x4C */
} TIM_TypeDef;

/* One DMA stream (F4 has streams 0-7, each with a CHSEL channel 0-7) */
typedef struct {
  volatile uint32_t CR, NDTR, PAR, M0AR, M1AR, FCR;    /* 0x18 bytes */
} DMA_Stream_TypeDef;

typedef struct {
  volatile uint32_t LISR, HISR, LIFCR, HIFCR;          /* 0x00..0x0C: streams 0-3 low, 4-7 high */
  DMA_Stream_TypeDef S[8];                             /* stream 0 starts at 0x10 */
} DMA_TypeDef;

typedef struct {
  volatile uint32_t CR1, CR2, OAR1, OAR2, DR, SR1, SR2, CCR, TRISE, FLTR;  /* 0x00..0x24 */
} I2C_TypeDef;

typedef struct {
  volatile uint32_t ACR, KEYR, OPTKEYR, SR, CR, OPTCR;   /* 0x00..0x14 */
} FLASH_TypeDef;

typedef struct {
  volatile uint32_t IMR, EMR, RTSR, FTSR, SWIER, PR;     /* 0x00..0x14 */
} EXTI_TypeDef;

typedef struct {
  volatile uint32_t MEMRMP, PMC;                         /* 0x00, 0x04 */
  volatile uint32_t EXTICR[4];                           /* 0x08..0x14 */
  volatile uint32_t RES[2];                              /* 0x18..0x1C */
  volatile uint32_t CMPCR;                               /* 0x20 */
} SYSCFG_TypeDef;

typedef struct {
  volatile uint32_t DR, IDR, CR;                         /* 0x00, 0x04, 0x08 */
} CRC_TypeDef;

/* ======================= Peripheral Pointers ======================= */
#define GPIOA   ((GPIO_TypeDef *)GPIOA_BASE)
#ifdef UNIT_TEST 
extern GPIO_TypeDef fake_gpiob;
extern DMA_TypeDef fake_dma2;
#define GPIOB (&fake_gpiob)
#define DMA2 (&fake_dma2)
#else
#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)
#define DMA2    ((DMA_TypeDef *)DMA2_BASE)
#endif
#define RCC     ((RCC_TypeDef *)RCC_BASE)
#define ADC1    ((ADC_TypeDef *)ADC1_BASE)
#define ADC_CCR (*(volatile uint32_t *)(ADC_COMMON_BASE + 0x04u))
#define TIM1    ((TIM_TypeDef *)TIM1_BASE)    /* free-running counter (RNG seed) */
#define TIM2    ((TIM_TypeDef *)TIM2_BASE)    /* 1 kHz ADC trigger (TRGO) */
#define DMA1    ((DMA_TypeDef *)DMA1_BASE)    /* I2C1_TX: S6, CH1 */
#define I2C1    ((I2C_TypeDef *)I2C1_BASE)
#define FLASH   ((FLASH_TypeDef *)FLASH_BASE_R)
#define EXTI    ((EXTI_TypeDef *)EXTI_BASE)
#define SYSCFG  ((SYSCFG_TypeDef *)SYSCFG_BASE)
#define CRC     ((CRC_TypeDef *)CRC_BASE)
#define SYSTICK ((Systick_TypeDef *)SYSTICK_BASE)

/* ======================= IRQ numbers (for NVIC) ======================= */
#define DMA1_Stream6_IRQn  17
#define I2C1_EV_IRQn       31
#define I2C1_ER_IRQn       32
#define EXTI15_10_IRQn     40
#define DMA2_Stream0_IRQn  56

/* ======================= Bit names ======================= */

/* RCC CR */
#define RCC_CR_HSEON     BIT(16)
#define RCC_CR_HSERDY    BIT(17)
#define RCC_CR_PLLON     BIT(24)
#define RCC_CR_PLLRDY    BIT(25)
/* RCC PLLCFGR (25 MHz HSE: M=25, N=336, P=1(/4), Q>=2 -> 84 MHz) */
#define RCC_PLLCFGR_PLLM_Pos   0u   /* 6 bits: 2..63 */
#define RCC_PLLCFGR_PLLN_Pos   6u   /* 9 bits: 50..432 */
#define RCC_PLLCFGR_PLLP_Pos   16u  /* 2 bits: 0=/2, 1=/4, 2=/6, 3=/8 */
#define RCC_PLLCFGR_PLLSRC_HSE BIT(22)
#define RCC_PLLCFGR_PLLQ_Pos   24u  /* 4 bits: 2..15 (must not be 0/1 if you write the whole reg) */
/* RCC CFGR */
#define RCC_CFGR_SW_Pos        0u   /* 2 bits: 2 = PLL */
#define RCC_CFGR_SWS_Pos       2u   /* 2 bits: 2 = PLL */
#define RCC_CFGR_HPRE_Pos      4u   /* 4 bits: 0 = /1 */
#define RCC_CFGR_PPRE1_Pos     10u  /* 3 bits: 4 = /2 (max 42MHz) */
#define RCC_CFGR_PPRE2_Pos     13u  /* 3 bits: 0 = /1 (max 84MHz) */
#define RCC_CFGR_SWS_PLL     BIT(3)
/* RCC enable bits */
#define RCC_AHB1ENR_GPIOAEN  BIT(0)
#define RCC_AHB1ENR_GPIOBEN  BIT(1)
#define RCC_AHB1ENR_CRCEN    BIT(12)
#define RCC_AHB1ENR_DMA1EN   BIT(21)
#define RCC_AHB1ENR_DMA2EN   BIT(22)
#define RCC_APB1ENR_TIM2EN   BIT(0)
#define RCC_APB1ENR_I2C1EN   BIT(21)
#define RCC_APB2ENR_TIM1EN   BIT(0)
#define RCC_APB2ENR_ADC1EN   BIT(8)
#define RCC_APB2ENR_SYSCFGEN BIT(14)

/* Systick enable bits */
#define SYSTICK_ENABLE BIT(0)
#define SYSTICK_TICKINT BIT(1)
#define SYSTICK_CLKSRC BIT(2)
/* FLASH ACR */
#define FLASH_ACR_LATENCY_Pos 0u  /* 4 bits: 2 = two wait states at 84MHz */
#define FLASH_ACR_PRFTEN      BIT(8)
#define FLASH_ACR_ICEN        BIT(9)
#define FLASH_ACR_DCEN        BIT(10)
/* FLASH programming (score storage) */
#define FLASH_KEY1            0x45670123u
#define FLASH_KEY2            0xCDEF89ABu
#define FLASH_SR_EOP          BIT(0)
#define FLASH_SR_ERR_MASK     (BIT(4) | BIT(5) | BIT(6) | BIT(7))  /* WRPERR, PGAERR, PGPERR, PGSERR */
#define FLASH_SR_BSY          BIT(16)
#define FLASH_CR_PG           BIT(0)
#define FLASH_CR_SER          BIT(1)
#define FLASH_CR_SNB_Pos      3u   /* 4 bits: sector number (storage = 5) */
#define FLASH_CR_PSIZE_Pos    8u   /* 2 bits: 2 = x32 (needs VDD 2.7-3.6V) */
#define FLASH_CR_STRT         BIT(16)
#define FLASH_CR_LOCK         BIT(31)

/* CRC */
#define CRC_CR_RESET          BIT(0)   /* hardware CRC is CRC-32/MPEG-2, not zlib */

/* EXTI: line n = BIT(n). PB12/PB13 -> lines 12/13.
   SYSCFG->EXTICR[3]: line 12 in bits [3:0], line 13 in bits [7:4]; port B = 1. */
#define SYSCFG_EXTICR_PORTB   1u

/* ADC */
#define ADC_SR_EOC         BIT(1)
#define ADC_CR2_ADON       BIT(0)
#define ADC_CR2_DMA        BIT(8)
#define ADC_CR2_DDS        BIT(9)   /* needed so circular DMA keeps getting requests */
#define ADC_CR2_EXTSEL_Pos 24u      /* 4 bits: 0=TIM1_CC1, 1=TIM1_CC2, 2=TIM1_CC3, 6=TIM2_TRGO, 8=TIM3_TRGO */
#define ADC_CR2_EXTEN_Pos  28u      /* 2 bits: 0=off, 1=rising, 2=falling, 3=both */
#define ADC_CR2_SWSTART    BIT(30)
#define ADC_CCR_ADCPRE_Pos 16u      /* 2 bits: 0=/2, 1=/4 (use this: ADCCLK max 36MHz), 2=/6, 3=/8 */

/* TIM */
#define TIM_CR1_CEN        BIT(0)
#define TIM_CR1_ARPE       BIT(7)
#define TIM_CR2_MMS_Pos    4u       /* 3 bits: 2 = update event -> TRGO */
#define TIM_EGR_UG         BIT(0)

/* DMA SxCR (shared by all streams) */
#define DMA_SxCR_EN        BIT(0)
#define DMA_SxCR_TCIE      BIT(4)
#define DMA_SxCR_DIR_Pos   6u       /* 2 bits: 0=periph->mem, 1=mem->periph */
#define DMA_SxCR_CIRC      BIT(8)
#define DMA_SxCR_PINC      BIT(9)
#define DMA_SxCR_MINC      BIT(10)
#define DMA_SxCR_PSIZE_Pos 11u      /* 2 bits: 0=8-bit, 1=16-bit, 2=32-bit */
#define DMA_SxCR_MSIZE_Pos 13u      /* 2 bits: 0=8-bit, 1=16-bit, 2=32-bit */
#define DMA_SxCR_CHSEL_Pos 25u      /* 3 bits: channel 0-7 */
/* DMA flags for the streams we use */
#define DMA_LISR_TEIF0     BIT(3)   /* DMA2 S0 (ADC): LISR / clear via LIFCR, same bits */
#define DMA_LISR_TCIF0     BIT(5)
#define DMA_HISR_TEIF6     BIT(19)  /* DMA1 S6 (I2C TX): HISR / clear via HIFCR, same bits */
#define DMA_HISR_TCIF6     BIT(21)

/* I2C */
#define I2C_CR1_PE      BIT(0)
#define I2C_CR1_START   BIT(8)
#define I2C_CR1_STOP    BIT(9)
#define I2C_CR1_ACK     BIT(10)
#define I2C_CR1_SWRST   BIT(15)
#define I2C_CR2_FREQ_Pos 0u         /* 6 bits: PCLK1 in MHz (42) */
#define I2C_CR2_ITERREN BIT(8)
#define I2C_CR2_ITEVTEN BIT(9)
#define I2C_CR2_DMAEN   BIT(11)
#define I2C_SR1_SB      BIT(0)
#define I2C_SR1_ADDR    BIT(1)
#define I2C_SR1_BTF     BIT(2)
#define I2C_SR1_TXE     BIT(7)
#define I2C_SR1_BERR    BIT(8)
#define I2C_SR1_ARLO    BIT(9)
#define I2C_SR1_AF      BIT(10)
#define I2C_SR1_TIMEOUT BIT(14)
#define I2C_SR2_BUSY    BIT(1)
#define I2C_CCR_DUTY    BIT(14)
#define I2C_CCR_FS      BIT(15)     /* 400kHz @42MHz, DUTY=0: CCR=35, TRISE=13 */

#endif
