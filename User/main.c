/*
 *                        .::::.
 *                      .::::::::.
 *                     :::::::::::
 *                  ..:::::::::::'
 *               '::::::::::::'
 *                 .::::::::::
 *            '::::::::::::::..
 *                 ..::::::::::::.
 *               ``::::::::::::::::
 *                ::::``:::::::::'        .:::.
 *               ::::'   ':::::'       .::::::::.
 *             .::::'      ::::     .:::::::'::::.
 *            .:::'       :::::  .:::::::::' ':::::.
 *           .::'        :::::.:::::::::'      ':::::.
 *          .::'         ::::::::::::::'         ``::::.
 *      ...:::           ::::::::::::'              ``::.
 *     ````':.          ':::::::::'                  ::::..
 *                        '.:::::'                    ':'````..
 */

/*
 * @Author: JJ HE hjj20010422@163.com
 * @Date: 2022-09-24 12:12:04
 * @LastEditors: JJ HE hjj20010422@163.com
 * @LastEditTime: 2022-10-14 16:27:16
 * @FilePath: \stm32_ADC\User\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"						//加入TIM3定时10ms;给编码器记速
#include "led.h"
#include "NTC.h"

int main(void)
{
	
	OLED_Init();
	led_Init();
	Ntc_Init();
	
	


	while (1)
	{
		OLED_ShowNum(2,1,AD_GetVal(),10);
		Delay_ms(200);
		led_blink(5,200);
		OLED_ShowString(1,1,"Helloworld");
		OLED_ShowString(1,1,"Helloworld");
		
	}
	
}




