// #include "HT66F004.h"
// #include "build-in.h"
// #include "ht66f004_common_define.h"
//*=============================================================
//本程序专门测试遥控器电路板的led
//7.27下午，开始写,
//完成show_c的调试，可以单独显示,show_C(show_c_data);与宏pin口
//7.29凌晨完成两个595的互斥显示 show_AB_A,show_AB_B;
//完成，595的两个参数的兼容同时显示show_AB_ALL(show_a_data,show_b_data)
//完成删除其他多余代码，用于腾出20*3char空间
//删除多余重复数组
//===========================================================================================*//
//----------------------------------------------------------
//I/O 口定义
//----------------------------------------------------------
////----------------------ghh_define_variable----------------------------
unsigned char A[9+1] ;//__attribute__ ((at(0x70)));;
unsigned char B[8+1] ;//__attribute__ ((at(0x85)));;//static volatile unsigned char arr[10] __attribute__ ((at(0x140))); 
unsigned char C[5+1] ;//static //unsigned char C[21] ;//是在ram中，static是在rom,volatile 是在ram
////-------------ghh_define_variable----还能减少变量空间吗，人家都是用8bit进行操作hc595的，位域是不行的----

//----------------------ghh_led_waterLight_define-----------------------------
#define A_L1	(~(unsigned char )1)
#define A_L2	(~(unsigned char )2)
#define A_L3	(~(unsigned char )4)
#define A_L12	(~(unsigned char )8)
#define A_L13	(~(unsigned char )16)
#define A_L14	(~(unsigned char )32)
#define A_L16	(~(unsigned char )64)
#define A_L17	(~(unsigned char )128)

#define B_L01   (~(unsigned char )1)
#define B_L02	(~(unsigned char )2)
#define B_L03	(~(unsigned char )4)
#define B_L04	(~(unsigned char )8)
#define B_L05	(~(unsigned char )16)
#define B_L18	(~(unsigned char )32)
#define B_L19	(~(unsigned char )64)

#define C_L15  (~(unsigned char )1)
#define C_L6	(~(unsigned char )2)
#define C_L5	(~(unsigned char )4)
#define C_L4	(~(unsigned char )8)
#define C_L9	(~(unsigned char )16)

#define C_D1	(~(unsigned char )32)
#define C_D2	(~(unsigned char )64)
#define C_D3	(~(unsigned char )128)

#define ABC_ORIG	(~(unsigned char )0)
//----------------------ghh_led_waterLight_define-----------------------------
///////////////////////////system——fun-in-mainfuntion//////////////////////////////////
//extern void init_port(void)
//extern void init_reg(void)
//extern void int_close()
//extern void int_open()
///////////////////////////system-fun-in-mainfuntion//////////////////////////////////
////
/////////////////////////ghh_MYfuntion///////////////
///////extern-funtion-in-mainfuntion/////
///extern void HC595send_data1(unsigned char sendval)
//extern void HC595show_data1(void)
//extern void HC595send_data(unsigned char sendval)
//extern void HC595show_data(void)
////////////
void show_abc_wait(void)
{
	unsigned int t = 50000;
	while(--t){GCC_NOP();}

}
unsigned char A_L_opera(unsigned char hc595_show_count)
{	
	unsigned char return_num;
	switch(hc595_show_count)
	{
		case 18:	return_num=	(unsigned char)A_L1	;break;
		case 19:	return_num=(unsigned char)	A_L2	;break;
		case 20:	return_num=	(unsigned char)A_L3	;break;
		case 4:return_num=	(unsigned char)A_L12	;break;
		case 5:return_num=	(unsigned char)A_L13	;break;
		case 6:return_num=(unsigned char)	A_L14	;break;
		case 2:return_num=(unsigned char)	A_L16	;break;
		case 3:return_num=	(unsigned char)A_L17	;break;
		default: return_num= (unsigned char)ABC_ORIG	 ;break;
	}
		return return_num;
}	

unsigned char B_L_opera(unsigned char hc595_show_count)
{
	unsigned char return_num;
	switch(hc595_show_count)
	{
	case 7:	return_num=	B_L01	;break;
	case 8:	return_num=	B_L02	;break;
	case 9:	return_num=	B_L03	;break;
	case 10:return_num=	B_L04	;break;
	case 11:return_num=	B_L05	;break;
	case 12:return_num=	B_L18	;break;
	case 14:return_num=	B_L19	;break;
	default: return_num= ABC_ORIG	 ;break;
	}	
	return return_num;
}	

unsigned char C_L_opera(unsigned char hc595_show_count)
{
	unsigned char return_num;
	switch(hc595_show_count)
	{
	case 1:	return_num=	C_L15	;break;
	case 15:return_num=	C_L4	;break;
	case 16:return_num=	C_L5	;break;
	case 17:return_num=	C_L6	;break;
	case 13:return_num=	C_L9	;break;
	default: return_num= ABC_ORIG	 ;break;
	}	
	return return_num;
}	
unsigned char C_D_opera_num(unsigned char one_to_three)
{	
	unsigned char return_num;
	switch(one_to_three)
	{
		case 1:return_num=	(unsigned char)C_D1	;break;
		case 2:return_num=	(unsigned char)C_D2	;break;
		case 3:return_num=	(unsigned char)C_D3	;break;
		//////////////
		////
	    // case 4:	return_num =(unsigned char)(C_D1 & C_D2); break;
	    // case 5: return_num =(unsigned char)((C_D1) & (C_D3)) ; break;
		// case 6:	return_num =(unsigned char)((C_D2) & (C_D3)) ; break;
		// case 7:	return_num =(unsigned char)((C_D1) & (C_D2) &(C_D3)) ; break;
	/////////////////////////
		default: return_num= ABC_ORIG	 ;break;
	}
	return return_num;
			  
}
//////////////

void show_AB_ALL(unsigned char show_a_data,unsigned char show_b_data)
{
	HC595send_data(show_b_data);HC595send_data(show_a_data); HC595show_data();
}

void show_C(unsigned char show_c_data)
{
HC595send_data1(show_c_data);HC595show_data1();
}
void hc595_show_alloff(void)
{
	HC595send_data(0xff); HC595send_data(0xff);HC595show_data();
	HC595send_data1(0xff);HC595show_data1();show_abc_wait();	
		  
}

void show_tricolour_C_EndOffAll(void)
{	
	unsigned char OneToSevSelect;
	for(OneToSevSelect=1;OneToSevSelect<=3; OneToSevSelect++)
	{
		show_C(  C_D_opera_num(OneToSevSelect) );//////(OneToSevSelect)
		show_abc_wait();show_abc_wait();
	}
	show_C(ABC_ORIG);
	show_abc_wait();
}		


/////////////////
unsigned char a_array_select(unsigned char OneToTwenty)
{	
	unsigned char return_num;
	switch(OneToTwenty)
	{
		case 1: return_num = 1; break;
		case 2:	return_num = 2;	break;
		case 3:	return_num = 3;	break;
		case 4: return_num = 4;	break;
		case 5: return_num = 5;	break;
		case 6: return_num = 6;
		case 7:	
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17: return_num = 6;break;
		case 18: return_num = 7;break;
		case 19: return_num = 8;break;
		case 20: return_num = 9;break;
		
		default: return_num = 0;break;
	}
	return return_num;
}
unsigned char b_array_select(unsigned char OneToTwenty)
{	
	unsigned char return_num;
	switch(OneToTwenty)
	{
		case 1: return_num = 1; 
		case 2:	
		case 3:	
		case 4: 
		case 5: 	
		case 6: return_num = 1;break;
		case 7:	return_num = 2;break;
		case 8:	return_num = 3;break;
		case 9:	return_num = 4;break;
		case 10:return_num = 5;break;
		case 11:return_num = 6;break;
		case 12:return_num = 7;
		case 13:return_num = 7;break;
		case 14:return_num = 8;
		case 15:
		case 16:
		case 17: 
		case 18: 
		case 19: 
		case 20:return_num = 8;break;
		default: return_num = 0;break;
	}
	return return_num;
}
unsigned char c_array_select(unsigned char OneToTwenty)
{
	unsigned char return_num;
	switch(OneToTwenty)
	{
		case 1: return_num = 1; 
		case 2:	
		case 3:	
		case 4: 
		case 5: 	
		case 6: 
		case 7:	
		case 8:	
		case 9:	
		case 10:
		case 11:
		case 12:return_num = 1;break;
		case 13:return_num = 2;
		case 14:return_num = 2;break;
		case 15:return_num = 3;break;
		case 16:return_num = 4;break;
		case 17: return_num = 5;
		case 18: 
		case 19: 
		case 20:return_num = 5;break;
		default: return_num = 0;break;
	}
	return return_num;
}
////////////////
void init_array_abc(void)
{	
	unsigned char hc595_show_count,old_dat_a,old_dat_b,old_dat_c;
	for(hc595_show_count=1,old_dat_a=old_dat_b=old_dat_c=ABC_ORIG;hc595_show_count<=20;hc595_show_count++)
	{
			 //	A[1] = old_dat_a = ABC_ORIG;	//B[1] = old_dat_b =ABC_ORIG;	 C[1] = old_dat_c= ABC_ORIG & C_L15 ;
			// A[2] = old_dat_a =old_dat_a & A_L16;	//	B[2] = old_dat_b ;	 C[2] = old_dat_c ;  break;
			// case 3: A[3] = old_dat_a =old_dat_a & A_L17;		B[3] = old_dat_b ;	 C[3] = old_dat_c ;  break;
			// case 4: A[4] = old_dat_a =old_dat_a & A_L12;		B[4] = old_dat_b ;	 C[4] = old_dat_c ;  break;
			// case 5: A[5] = old_dat_a =old_dat_a & A_L13;		B[5] = old_dat_b ;	 C[5] = old_dat_c ;  break;
			// case 6: A[6] = old_dat_a =old_dat_a & A_L14;		B[6] = old_dat_b ;	 C[6] = old_dat_c ;  break;
		A[a_array_select(hc595_show_count)] = old_dat_a = old_dat_a & A_L_opera(hc595_show_count) ;	
		B[b_array_select(hc595_show_count)] = old_dat_b = old_dat_b & B_L_opera(hc595_show_count) ;	
		C[c_array_select(hc595_show_count)] = old_dat_c = old_dat_c & C_L_opera(hc595_show_count) ;  
	}
	 
}

void show_lightwater_track(void)//
{	
	unsigned char hc595_show_count;
	for(hc595_show_count=1;hc595_show_count<=20;hc595_show_count++)
	{								
													//show_AB_B(B_L19);//show_AB_A(A_L17&A_L16);
	show_AB_ALL(A[a_array_select(hc595_show_count)],B[b_array_select(hc595_show_count)] );	//A[hc595_show_count-1],B[hc595_show_count-1] 
	show_C( C[c_array_select(hc595_show_count)]);//	show_C( C_L9);
	
	///*/////以上2个函数必须同时执行，同时点亮led才有跑马灯轨迹效果;show_AB_A/B,是互斥的，不用此函数///*////////////
	show_abc_wait();
	
		
	}
	
}
void init_test_LED(void)//////最终调用2之1////////////
{
	init_array_abc();
    hc595_show_alloff();
}
void power_on_test_LED_once(void)////最终调用2之2///////////////
{
	 //全灭 	  
	hc595_show_alloff();show_abc_wait();show_abc_wait();show_abc_wait();show_abc_wait();//all-off-led 
	//show_tricolour三色灯
	 show_tricolour_C_EndOffAll();
	 //流水灯
	 show_lightwater_track();
	//led-all-off
	hc595_show_alloff();
}
/////////////////////////GhhMYfuntion//全部函数定义完成，可以直接复制到main之前/////////////




