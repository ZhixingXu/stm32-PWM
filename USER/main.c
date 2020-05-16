#include <stm32f10x.h>
#include "tim.h"
const int MAX=500;
const int MIN=5;
const int STEP=4;
// void delayus(int t){
//     SysTick->LOAD=9*t;
//     SysTick->VAL=0;
//     SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
//     while(SysTick)
// }
void delayus(unsigned int t){
    unsigned int temp;
    SysTick->LOAD=t*9;//我是这样想的,(1us/1s)*9Mhz
     SysTick->VAL=0;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
    do {
        //这里这么写是因为systick的控制及状态寄存器是16位,
        //当数到0,他的最高位变为1
        temp=SysTick->CTRL;
    } while ((temp&0x01)&&(!(temp&(1<<16))));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL=0;
}
int main(){
    int high=500,sign=1;
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    TIM3_GPIO_Config();
    TIM3_Mode_Config();
    while (1)
    {
		//PA6实现了光的渐变
        //这个函数就实现了我写的下面的程序TIM_SetCompare1()
        delayus(50000-high*high/10);
        TIM3->CCR1=high;
        if(high>MAX)
            sign=0;
        if(high<MIN)
            sign=1;
        if(sign)
            high=high+STEP;
        else
            high=high-STEP;
    }
    
}
