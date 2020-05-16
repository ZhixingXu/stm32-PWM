#include "tim.h"
//tim3

void TIM3_GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/*brief:配置TIM3输出的PWM信号的模式,如周期,极性,占空比*/
void TIM3_Mode_Config(){
    TIM_TimeBaseInitTypeDef TIM_TimBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;//what's the difference between two type
    uint16_t CCR1_VAL=500,CCR2_VAL=375,CCR3_VAL=250,CCR4_VAL=125;
    /*TIM3配置:生成4路不同占空比的PWM信号
    TIM3CLK=72MHZ,预分频系数0,计数时钟72MHZ
    重装载寄存器999,故4路占空比50%,37.5%,25%,12.5%
    */
   TIM_TimBaseStructure.TIM_Prescaler=0;//不预分频
   TIM_TimBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟分频系数,时钟不分频
   TIM_TimBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimBaseStructure.TIM_Period=999;//from 0-999 is 1000,,1000*T=1000*1/f
   //TIM_TimBaseStructure.TIM_RepetitionCounter=ENABLE;
   TIM_TimeBaseInit(TIM3,&TIM_TimBaseStructure);

   //mode config
   //TIM_OCInitStructure.TIM_OCIdleState=
   /********************1************************/
   TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//polarity:截然相反的
   TIM_OCInitStructure.TIM_Pulse=CCR1_VAL;
   TIM_OC1Init(TIM3,&TIM_OCInitStructure);
   TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
   /********************2************************/
   TIM_OCInitStructure.TIM_Pulse=CCR2_VAL;
   TIM_OC2Init(TIM3,&TIM_OCInitStructure);
   TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
   /********************3************************/
   TIM_OCInitStructure.TIM_Pulse=CCR3_VAL;
   TIM_OC3Init(TIM3,&TIM_OCInitStructure);
   TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
   /********************4************************/
   TIM_OCInitStructure.TIM_Pulse=CCR4_VAL;
   TIM_OC4Init(TIM3,&TIM_OCInitStructure);
   TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);

   TIM_ARRPreloadConfig(TIM3,ENABLE);
   TIM_Cmd(TIM3,ENABLE);
}

