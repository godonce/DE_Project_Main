#include "Extern.h"
#include  "datafigures.h"
#include "DataInterface.h"
#include "states.h"
void ExternIN_Init(void)
{
	scu_pinmux(ExClose_PORT ,ExClose_PORT_PIN , MD_EZI, ExClose_PORT_FUNC);
  GPIO_SetDir(ExClose_GPIO,(1<<ExClose_GPIO_PIN), 0);
	scu_pinmux(ExOpen_PORT ,ExOpen_PORT_PIN , MD_EZI, ExOpen_PORT_FUNC);
  GPIO_SetDir(ExOpen_GPIO,(1<<ExOpen_GPIO_PIN), 0);
	scu_pinmux(ExStop_PORT ,ExStop_PORT_PIN , MD_EZI, ExStop_PORT_FUNC);
  GPIO_SetDir(ExStop_GPIO,(1<<ExStop_GPIO_PIN), 0);
	scu_pinmux(ExEme_PORT ,ExEme_PORT_PIN , MD_EZI, ExEme_PORT_FUNC);
  GPIO_SetDir(ExEme_GPIO,(1<<ExEme_GPIO_PIN), 0);
	scu_pinmux(ExMod_PORT ,ExMod_PORT_PIN , MD_EZI, ExMod_PORT_FUNC);
  GPIO_SetDir(ExMod_GPIO,(1<<ExMod_GPIO_PIN), 0);

  SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);
}

void ExternOUT_Init(void)
{
	scu_pinmux(ExOUT1_PORT ,ExOUT1_PORT_PIN , MD_PDN, ExOUT1_PORT_FUNC);
  GPIO_SetDir(ExOUT1_GPIO,(1<<ExOUT1_GPIO_PIN), 1);
	scu_pinmux(ExOUT2_PORT ,ExOUT2_PORT_PIN , MD_PDN, ExOUT2_PORT_FUNC);
  GPIO_SetDir(ExOUT2_GPIO,(1<<ExOUT2_GPIO_PIN), 1);
	scu_pinmux(ExOUT3_PORT ,ExOUT3_PORT_PIN , MD_PDN, ExOUT3_PORT_FUNC);
  GPIO_SetDir(ExOUT3_GPIO,(1<<ExOUT3_GPIO_PIN), 1);
	scu_pinmux(ExOUT4_PORT ,ExOUT4_PORT_PIN , MD_PDN, ExOUT4_PORT_FUNC);
  GPIO_SetDir(ExOUT4_GPIO,(1<<ExOUT4_GPIO_PIN), 1);
	scu_pinmux(ExOUT5_PORT ,ExOUT5_PORT_PIN , MD_PDN, ExOUT5_PORT_FUNC);
  GPIO_SetDir(ExOUT5_GPIO,(1<<ExOUT5_GPIO_PIN), 1);
	scu_pinmux(ExOUT6_PORT ,ExOUT6_PORT_PIN , MD_PDN, ExOUT6_PORT_FUNC);
  GPIO_SetDir(ExOUT6_GPIO,(1<<ExOUT6_GPIO_PIN), 1);
	scu_pinmux(ExOUT7_PORT ,ExOUT7_PORT_PIN , MD_PDN, ExOUT7_PORT_FUNC);
  GPIO_SetDir(ExOUT7_GPIO,(1<<ExOUT7_GPIO_PIN), 1);
	scu_pinmux(ExOUT8_PORT ,ExOUT8_PORT_PIN , MD_PDN, ExOUT8_PORT_FUNC);
  GPIO_SetDir(ExOUT8_GPIO,(1<<ExOUT8_GPIO_PIN), 1);
	scu_pinmux(ExEN_PORT ,ExEN_PORT_PIN , MD_PDN, ExEN_PORT_FUNC);
  GPIO_SetDir(ExEN_GPIO,(1<<ExEN_GPIO_PIN), 1);
  SysTick_Config(CGU_GetPCLKFrequency(CGU_PERIPHERAL_M4CORE)/1000);
}

void Extern_out(void)
{
	GPIO_ClearValue(ExEN_GPIO,(1<<ExEN_GPIO_PIN));
}
	
void Extern_in(void)
{
	if(GPIO_ReadValue(ExClose_GPIO)&(1<<ExClose_GPIO_PIN))
	{
		flag_figures.KEYClose=1;
	}else
	{
		flag_figures.KEYClose=0;
	}
	if(GPIO_ReadValue(ExOpen_GPIO)&(1<<ExOpen_GPIO_PIN))
	{
		flag_figures.KEYOpen=1;
	}else
	{
		flag_figures.KEYOpen=0;
	}
	if(GPIO_ReadValue(ExStop_GPIO)&(1<<ExStop_GPIO_PIN))
	{
		flag_figures.KEYStop=1;
	}else
	{
		flag_figures.KEYStop=0;
	}
	if(GPIO_ReadValue(ExEme_GPIO)&(1<<ExEme_GPIO_PIN))
	{
		flag_figures.KEYEme=1;
	}else
	{
		flag_figures.KEYEme=0;
	}
	if(GPIO_ReadValue(ExMod_GPIO)&(1<<ExMod_GPIO_PIN))
	{
		flag_figures.KEYMod=0;
	}else
	{
		flag_figures.KEYMod=0;
	}

}

int TEST2[8][19];
extern int out_test[19];
void Extern_set(void)
{
    Extern_out_test();	
    if(out_test[ext_IO.eep_TEST_of1]==1)
    {
        ext_IO.flag_test_extern0=1;
    }else
    {
        ext_IO.flag_test_extern0=0;
    }
    if(out_test[ext_IO.eep_TEST_of2]==1)
    {
        ext_IO.flag_test_extern1=1;
    }else
    {
        ext_IO.flag_test_extern1=0;
    }
    if(out_test[ext_IO.eep_TEST_of3]==1)
    {
        ext_IO.flag_test_extern2=1;
    }else
    {
        ext_IO.flag_test_extern2=0;
    }
    if(out_test[ext_IO.eep_TEST_of4]==1)
    {
        ext_IO.flag_test_extern3=1;
    }else
    {
        ext_IO.flag_test_extern3=0;
    }
    if(out_test[ext_IO.eep_TEST_of5]==1)
    {
        ext_IO.flag_test_extern4=1;
    }else
    {
        ext_IO.flag_test_extern4=0;
    }
    if(out_test[ext_IO.eep_TEST_of6]==1)
    {
        ext_IO.flag_test_extern5=1;
    }else
    {
        ext_IO.flag_test_extern5=0;
    }
    if(out_test[ext_IO.eep_TEST_of7]==1)
    {
        ext_IO.flag_test_extern6=1;
    }else
    {
        ext_IO.flag_test_extern6=0;
    }
    if(out_test[ext_IO.eep_TEST_of8]==1)
    {
        ext_IO.flag_test_extern7=1;
    }else
    {
        ext_IO.flag_test_extern7=0;
    }
}

#if 1
void Extern_set_IO(void)
{

		#if 1
	if(ext_IO.flag_test_extern0==1)
	{
		Extern_out0();
	}else
	{
		Extern_out0_ex();
	}
	if(ext_IO.flag_test_extern1==1)
	{
		Extern_out1();
	}else
	{
		Extern_out1_ex();
	}
		if(ext_IO.flag_test_extern2==1)
	{
		Extern_out2();
	}else
	{
		Extern_out2_ex();
	}
		if(ext_IO.flag_test_extern3==1)
	{
		Extern_out3();
	}else
	{
		Extern_out3_ex();
	}
	#endif
		if(ext_IO.flag_test_extern4==1)
	{
		Extern_out4();
	}else
	{
		Extern_out4_ex();
	}
		if(ext_IO.flag_test_extern5==1)
	{
		Extern_out5();
	}else
	{
		Extern_out5_ex();
	}
		if(ext_IO.flag_test_extern6==1)
	{
		Extern_out6();
	}else
	{
		Extern_out6_ex();
	}
		if(ext_IO.flag_test_extern7==1)
	{
		Extern_out7();
	}else
	{
		Extern_out7_ex();
	}
}



#endif
void Extern_out0(void)
{

	if(ext_IO.eep_TEST2_of1==1)
	{
		GPIO_SetValue(ExOUT1_GPIO,(1<<ExOUT1_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of1==0)
	{
		GPIO_ClearValue(ExOUT1_GPIO,(1<<ExOUT1_GPIO_PIN));
	}
}
void Extern_out0_ex(void)
{

	if(ext_IO.eep_TEST2_of1==1)
	{
		GPIO_ClearValue(ExOUT1_GPIO,(1<<ExOUT1_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of1==0)
	{
		GPIO_SetValue(ExOUT1_GPIO,(1<<ExOUT1_GPIO_PIN));
	}
}

void Extern_out1(void)
{
	if(ext_IO.eep_TEST2_of2==1)
	{
		GPIO_SetValue(ExOUT2_GPIO,(1<<ExOUT2_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of2==0)
	{
		GPIO_ClearValue(ExOUT2_GPIO,(1<<ExOUT2_GPIO_PIN));
	}
}
void Extern_out1_ex(void)
{
	if(ext_IO.eep_TEST2_of2==1)
	{
		GPIO_ClearValue(ExOUT2_GPIO,(1<<ExOUT2_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of2==0)
	{
		GPIO_SetValue(ExOUT2_GPIO,(1<<ExOUT2_GPIO_PIN));
	}
}

void Extern_out2(void)
{
	if(ext_IO.eep_TEST2_of3==1)
	{
		GPIO_SetValue(ExOUT3_GPIO,(1<<ExOUT3_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of3==0)
	{
		GPIO_ClearValue(ExOUT3_GPIO,(1<<ExOUT3_GPIO_PIN));
	}
}
void Extern_out2_ex(void)
{
	if(ext_IO.eep_TEST2_of3==1)
	{
		GPIO_ClearValue(ExOUT3_GPIO,(1<<ExOUT3_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of3==0)
	{
		GPIO_SetValue(ExOUT3_GPIO,(1<<ExOUT3_GPIO_PIN));
	}
}

void Extern_out3(void)
{
	if(ext_IO.eep_TEST2_of4==1)
	{
		GPIO_SetValue(ExOUT4_GPIO,(1<<ExOUT4_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of4==0)
	{
		GPIO_ClearValue(ExOUT4_GPIO,(1<<ExOUT4_GPIO_PIN));
	}
}
void Extern_out3_ex(void)
{
	if(ext_IO.eep_TEST2_of4==1)
	{
		GPIO_ClearValue(ExOUT4_GPIO,(1<<ExOUT4_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of4==0)
	{
		GPIO_SetValue(ExOUT4_GPIO,(1<<ExOUT4_GPIO_PIN));
	}
}

void Extern_out4(void)
{
	if(ext_IO.eep_TEST2_of5==1)
	{
		GPIO_SetValue(ExOUT5_GPIO,(1<<ExOUT5_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of5==0)
	{
		GPIO_ClearValue(ExOUT5_GPIO,(1<<ExOUT5_GPIO_PIN));
	}
}
void Extern_out4_ex(void)
{
	if(ext_IO.eep_TEST2_of5==1)
	{
		GPIO_ClearValue(ExOUT5_GPIO,(1<<ExOUT5_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of5==0)
	{
		GPIO_SetValue(ExOUT5_GPIO,(1<<ExOUT5_GPIO_PIN));
	}
}

void Extern_out5(void)
{
	if(ext_IO.eep_TEST2_of6==1)
	{
		GPIO_SetValue(ExOUT6_GPIO,(1<<ExOUT6_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of6==0)
	{
		GPIO_ClearValue(ExOUT6_GPIO,(1<<ExOUT6_GPIO_PIN));
	}
}

void Extern_out5_ex(void)
{
	if(ext_IO.eep_TEST2_of6==1)
	{
		GPIO_ClearValue(ExOUT6_GPIO,(1<<ExOUT6_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of6==0)
	{
		GPIO_SetValue(ExOUT6_GPIO,(1<<ExOUT6_GPIO_PIN));
	}
}

void Extern_out6(void)
{
	if(ext_IO.eep_TEST2_of7==1)
	{
		GPIO_SetValue(ExOUT7_GPIO,(1<<ExOUT7_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of7==0)
	{
		GPIO_ClearValue(ExOUT7_GPIO,(1<<ExOUT7_GPIO_PIN));
	}
}

void Extern_out6_ex(void)
{
	if(ext_IO.eep_TEST2_of7==1)
	{
		GPIO_ClearValue(ExOUT7_GPIO,(1<<ExOUT7_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of7==0)
	{
		GPIO_SetValue(ExOUT7_GPIO,(1<<ExOUT7_GPIO_PIN));
	}
}
void Extern_out7(void)
{
	if(ext_IO.eep_TEST2_of8==1)
	{
		GPIO_SetValue(ExOUT8_GPIO,(1<<ExOUT8_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of8==0)
	{
		GPIO_ClearValue(ExOUT8_GPIO,(1<<ExOUT8_GPIO_PIN));
	}
}

void Extern_out7_ex(void)
{
	if(ext_IO.eep_TEST2_of8==1)
	{
		GPIO_ClearValue(ExOUT8_GPIO,(1<<ExOUT8_GPIO_PIN));
	}else
	if(ext_IO.eep_TEST2_of8==0)
	{
		GPIO_SetValue(ExOUT8_GPIO,(1<<ExOUT8_GPIO_PIN));
	}
}
extern int out_test[19];


void SET_IO_Extern(void)
{
	#if 1
	if(ext_IO.flag_IO_extern0==1)
	{
		ext_IO.flag_extern0=1;
	}else
	{
		ext_IO.flag_extern0=0;
	}
	if(ext_IO.flag_IO_extern1==1)
	{
		ext_IO.flag_extern1=1;
	}else
	{
		ext_IO.flag_extern1=0;
	}
	if(ext_IO.flag_IO_extern2==1)
	{
		ext_IO.flag_extern2=1;
	}else
	{
		ext_IO.flag_extern2=0;
	}
	if(ext_IO.flag_IO_extern3==1)
	{
		ext_IO.flag_extern3=1;
	}else
	{
		ext_IO.flag_extern3=0;
	}
	if(ext_IO.flag_IO_extern4==1)
	{
		ext_IO.flag_extern4=1;
	}else
	{
		ext_IO.flag_extern4=0;
	}
	
	#endif
	if(ext_IO.flag_IO_extern5==1)
	{
		ext_IO.flag_extern5=1;
	}else
	{
		ext_IO.flag_extern5=0;
	}
	if(ext_IO.flag_IO_extern6==1)
	{
		ext_IO.flag_extern6=1;
	}else
	{
		ext_IO.flag_extern6=0;
	}
	if(ext_IO.flag_IO_extern7==1)
	{
		ext_IO.flag_extern7=1;
	}else
	{
		ext_IO.flag_extern7=0;
	}
	
}



