#include "LED.h"
#include "Handler.h"
#include  "datafigures.h"
void Init_LED(void)
{
    scu_pinmux(LED1_PORT ,LED1_PIN , MD_PDN, FUNC4);
    GPIO_SetDir(LED1_GPIO_PORT,(1<<LED1_GPIO_PIN), 1);
    scu_pinmux(LED2_PORT ,LED2_PIN , MD_PDN, FUNC0);
    GPIO_SetDir(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN), 1);
    SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000); 
    GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));	
    GPIO_SetValue(LED1_GPIO_PORT,(1<<LED1_GPIO_PIN));
}

int c_entry_led (void) 
{ 
    GPIO_ClearValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN));
    GPIO_SetValue(LED1_GPIO_PORT,(1<<LED1_GPIO_PIN));
    OSTimeDly(200);
    GPIO_SetValue(LED2_GPIO_PORT,(1<<LED2_GPIO_PIN)); 
    GPIO_ClearValue(LED1_GPIO_PORT,(1<<LED1_GPIO_PIN));
    OSTimeDly(200);
    return 0;
}

void Init_States(void)
{
    scu_pinmux(Open_PORT ,Open_PIN , MD_PDN, Open_PORT_FUNC);
    GPIO_SetDir(Open_GPIO_PORT,(1<<Open_GPIO_PIN), 1);
    scu_pinmux(Local_PORT ,Local_PIN , MD_PDN, Local_PORT_FUNC);
    GPIO_SetDir(Local_GPIO_PORT,(1<<Local_GPIO_PIN), 1);
    scu_pinmux(PC_PORT ,PC_PIN , MD_PDN, PC_PORT_FUNC);
    GPIO_SetDir(PC_GPIO_PORT,(1<<PC_GPIO_PIN), 1);
    scu_pinmux(Close_PORT ,Close_PIN , MD_PDN, Close_PORT_FUNC);
    GPIO_SetDir(Close_GPIO_PORT,(1<<Close_GPIO_PIN), 1);
    SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000); 
	GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_SetValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_SetValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
}

void c_entry_OPEN(void)
{
	GPIO_ClearValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
}
void c_entry_LOCAL(void)
{
	GPIO_ClearValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_SetValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
}

void c_entry_LOCAL1(void)
{
	GPIO_ClearValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
}
void c_entry_LOCAL2(void)
{
	GPIO_SetValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
}
void c_entry_PC(void)
{
	GPIO_ClearValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));
	GPIO_SetValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));	
}
void c_entry_CLOSE(void)
{
	GPIO_ClearValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
	GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
}
void c_entry_allclose(void)
{
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
	GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_SetValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_SetValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
}

void c_enty_allclose_close_open()
{
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
	GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
}

void c_enty_allclose_pc_local()
{	
	GPIO_SetValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_SetValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
}

void c_entry_states (void) 
{ 
    GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_ClearValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_ClearValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
	GPIO_ClearValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
    OSTimeDly(200);
    GPIO_ClearValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_SetValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_ClearValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
	GPIO_ClearValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
    OSTimeDly(200);
	GPIO_ClearValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_ClearValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_SetValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
	GPIO_ClearValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
    OSTimeDly(200);
	GPIO_ClearValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_ClearValue(Local_GPIO_PORT,(1<<Local_GPIO_PIN));
	GPIO_ClearValue(PC_GPIO_PORT,(1<<PC_GPIO_PIN));	
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
    OSTimeDly(200);
}

void RUN_CLOSE (void) 
{ 
	GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_ClearValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
	led.flag_close=1;
	OSTimeDly(200);
	GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
	led.flag_close=0;
	OSTimeDly(200);
	
}

void RUN_OPEN (void) 
{ 
	GPIO_ClearValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
	OSTimeDly(200);
	GPIO_SetValue(Open_GPIO_PORT,(1<<Open_GPIO_PIN));	
	GPIO_SetValue(Close_GPIO_PORT,(1<<Close_GPIO_PIN));
	OSTimeDly(200);
}
