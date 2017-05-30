#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"des.h"
/******************************²¿·ÖÈ«¾Ö±äÁ¿**********************/
unsigned int input_l = 0x0, input_r = 0x0;
char buffer[20],input[20];           				//buffer receive the input,after exchange ,result saved in input 
unsigned int IP_loput=0,IP_roput=0;      //IP  exchange's output
char IP_soput[100];									//IP exchange's string format output
unsigned char E_str[50];
unsigned int F_oput=0;
char key[20]="aed123bc34213fc2";
unsigned int VIP_loput=0,VIP_roput=0;
unsigned int rVIP_loput=0,rVIP_roput=0;

char *value_buffer="k_value:\n";               //用于界面上text中输出结果
char *output_value_buffer="output:\n";
/****************************const table using in des process************************/
const int IPtable[64]={ 58 ,50 ,42, 34, 26, 18, 10, 2,
						60, 52, 44, 36, 28, 20, 12, 4,
						62, 54, 46, 38, 30, 22, 14, 6,
						64 ,56 ,48 ,40 ,32 ,24 ,16, 8,
						57 ,49 ,41 ,33 ,25 ,17 ,9 , 1,
						59, 51, 43, 35, 27, 19, 11, 3,
						61, 53 ,45, 37, 29, 21, 13, 5,
						63, 55, 47, 39, 31, 23, 15, 7 };
										
const int VIPtable[64]={
						40, 8, 48, 16, 56, 24, 64, 32,
						39 ,7 ,47 ,15 ,55 ,23 ,63 ,31,
						38 ,6 ,46 ,14 ,54 ,22 ,62 ,30,
						37 ,5 ,45 ,13 ,53 ,21 ,61 ,29,
						36 ,4, 44, 12 ,52 ,20 ,60, 28,
						35 ,3 ,43 ,11 ,51 ,19 ,59 ,27,
						34 ,2, 42, 10, 50, 18 ,58, 26,
						33 ,1 ,41 ,9 ,49 ,17 ,57 ,25};

const int Etable[48]={  32, 1, 2 ,3, 4, 5,
						4 ,5, 6, 7, 8, 9,
						8 ,9, 10, 11, 12 ,13,
						12 ,13 ,14 ,15 ,16 ,17,
						16 ,17, 18, 19, 20, 21,
						20 ,21 ,22 ,23 ,24 ,25,
						24 ,25 ,26 ,27 ,28 ,29,
						28 ,29 ,30 ,31, 32 ,1};
									
const int Ptable[32]={   16 ,7, 20, 21,
						29 ,12 ,28 ,17,
						1 ,15, 23 ,26,
						5 ,18 ,31 ,10,
						2 ,8, 24, 14,
						32 ,27 ,3 ,9,
						19 ,13, 30, 6,
						22 ,11 ,4 ,25};
									
const int Stable[8][4][16] = {
/*		1	 2	 3	4	5	 6	 7	8	9	10	11	12	13	14 15  16*/
	//S1
		14,  4, 13, 1 , 2 , 15, 11, 8 , 3 , 10,  6, 12,  5,  9, 0 , 7 ,
		0, 15,  7, 4 , 14,  2, 13, 1 , 10,  6, 12, 11,  9,  5, 3 , 8 ,
		4,  1, 14, 8 , 13,  6,  2, 11, 15, 12,  9 , 7 , 3, 10, 5 , 0 ,
		15, 12,  8, 2 ,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0, 6 , 13,
	//S2
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2 ,8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
	//S3
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
	//S4
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
	//S5
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
	//S6
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
	//S7
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
	//S8
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};

const int PC1table[56]={
						57 ,49 ,41 ,33 ,25 ,17, 9,
						1 ,58 ,50 ,42 ,34 ,26, 18,
						10 ,2 ,59, 51 ,43 ,35 ,27,
						19 ,11 ,3, 60, 52 ,44 ,36,
						63, 55, 47, 39 ,31 ,23 ,15,
						7 ,62,54 ,46 ,38, 30, 22,
						14 ,6 ,61 ,53 ,45, 37 ,29,
						21 ,13 ,5 ,28 ,20 ,12 ,4};
												
const int PC2table[48]={
						14, 17 ,11, 24, 1,5,
						3 ,28, 15, 6 ,21 ,10,
						23, 19, 12, 4, 26, 8,
						16, 7, 27, 20, 13, 2,
						41, 52, 31, 37, 47, 55,
						30 ,40 ,51 ,45, 33 ,48,
						44 ,49, 39, 56, 34, 53,
						46 ,42 ,50 ,36 ,29 ,32};
												
const int LStable[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int des()
{
	int ret =0,i=0;
	unsigned int  l_value1=0,r_value1=0,l_value2=0,r_value2=0;   
	char k_buffer[50]={'0'};
	/***format print the k value*******************/
	char k_label[5]={'0'};
	k_label[2]=':';
	k_label[3]='\t';
	value_buffer=(char *)malloc(1500*sizeof(char));
	memset(value_buffer,'\0',1500*sizeof(char));
	/****format print thr output(L,R) value********/
	//output_value_buffer=(char *)malloc(200*sizeof(char));
	//memset(output_value_buffer,'\0',200*sizeof(char));
	char out_tmp[20]={'0'};
	char out_label[6]={'0'};
	out_label[4]=':';
	out_label[1]='_';
	/****init the global_variable***/
	memset(input,'\0',sizeof(input));
	memset(IP_soput,'\0',sizeof(IP_soput));
	memset(E_str,'\0',sizeof(E_str));
	
	ret=str_format(buffer,input);
	if(ret<0)
	{
		printf("format erro.\n");
		return -1;
	}
	printf("input is:%s\n",input);
	ip_process(input);
	//printf("IP_output is %x\t%x\n",IP_loput,IP_roput);
	
	l_value1=IP_loput;
	r_value1=IP_roput;	
	
	for(i=0;i<16;i++)
	{
		strcat(value_buffer,"\tk_");
		//sprintf(k_label[0],"%d",i);
		k_label[1]=((i+1)%10)+48;
		k_label[0]=((i+1)/10)+48;
	//	printf("key_label:%c\n",k_label[0]);
		strcat(value_buffer,k_label);
		
		K_generate(i,key,k_buffer);
		
		strcat(value_buffer,k_buffer);
		strcat(value_buffer,";\n");
		
		l_value2=r_value1;
		F_func(r_value1,k_buffer,&F_oput);
		r_value2=l_value1^F_oput;                 
		
		l_value1=l_value2;                               //如今l_value1,r_value1位为当前值。
		r_value1=r_value2;
		
		
		/*******构建字符输出，到界面的text1***********/
		out_label[0]='L';
		out_label[3]=((i+1)%10)+48;
		out_label[2]=((i+1)/10)+48;
	//printf("here\n");
		strcat(value_buffer,out_label);
		
		if(i!=15)
			sprintf(out_tmp,"%x",l_value1);
		else
			sprintf(out_tmp,"%x",r_value1);
		
		strcat(value_buffer,out_tmp);
		strcat(value_buffer,";\t\t");
			
		out_label[0]='R';
		strcat(value_buffer,out_label);
		
		if(i!=15)
			sprintf(out_tmp,"%x",r_value1);
		else
			sprintf(out_tmp,"%x",l_value1);
		
		strcat(value_buffer,out_tmp);
		strcat(value_buffer,";\n\n");
	/****************************************************/
		//printf("the output is %x\t%x\n",l_value1,r_value1);
	//printf("the K%d is %s\n",i+1,k_buffer);
		//printf("l_value1:%x\tr_value1:%x\n\tF_out:%x\n",l_value1,r_value1,F_oput);
	}
	l_value2=r_value1;
	r_value2=l_value1;
	reverse_ip_process(VIPtable,l_value2,r_value2,&VIP_loput,&VIP_roput);
	printf("the final output is %x\t%x\n",VIP_loput,VIP_roput);
	return 0;
}

void reverse_des()
{
	int ret = 0,i=0;
	unsigned int  l_value1=0,r_value1=0, l_value2=0,r_value2=0; 
	char k_buffer[60]={'0'};
	//memset(input,'0',sizeof(input));
	//str2hex(input,&VIP_loput,&VIP_roput);
	printf("input.,left:%x\tright:%x\n",VIP_loput,VIP_roput);
	reverse_ip_process(IPtable,VIP_loput,VIP_roput,&l_value1,&r_value1);
	//printf("in reverse,IP_output is %x\t%x\n",l_value1,r_value1);
	
	for(i=0;i<16;i++)
	{
		K_generate(15-i,key,k_buffer);
	//	printf("the K%d is %s\n",16-i,k_buffer);
		l_value2=r_value1;
		F_func(r_value1,k_buffer,&F_oput);
		r_value2=l_value1^F_oput;                 
		
		l_value1=l_value2;                               //如今l_value1,r_value1位为当前值。
		r_value1=r_value2;
		//printf("the output is %x\t%x\n",l_value1,r_value1);
	}
	l_value2=r_value1;
	r_value2=l_value1;

	reverse_ip_process(VIPtable,l_value2,r_value2,&rVIP_loput,&rVIP_roput);
	printf("the reverse_output is %x\t%x\n\n",rVIP_loput,rVIP_roput);
}
//将输入字符串规范化
int str_format(char *str, char *input) //str是源输入，input是规范化输入,默认没有0x前缀
{
	int len = 0, cnt = 0;
	char tmp = '0';

	while (str[cnt] != '\0')
	{
		tmp = str[cnt];
		if ((tmp >= 48 && tmp <= 57)  || (tmp >= 65&& tmp <= 70)) //数字，大写字母
			cnt++;
			
		else if (tmp >= 97 && tmp <= 102)
		{	
			tmp -= 32;                      //小写转大写
			str[cnt]=tmp;
			cnt++;
		}
		else
			return -1;
	}
	cnt = 0;
	len = strlen(str);
	if (len < 16)
	{
		for (cnt = 0;cnt < (16 - len);cnt++)
			input[cnt] = '0';
		strcat(input,str);
	}
	else
		strcpy(input, str);
		return 0;
}

//IP表变换，判断输入合适是否正确，并且处理之
int ip_process(const char * input)
{
	IP_loput=0,IP_roput=0; 
	int cnt = 0,i=0,j=0;
	unsigned int tmp=0,mr=0;
	//printf("input :%s\n",input);
	str2hex(input, &input_l, &input_r);
	//printf("left:%x \tright:%x \n",input_l,input_r);
	for(i=0;i<16;i++)
	{
		mr=0;
		for(j=0;j<4;j++)
		{
		if(IPtable[i*4+j]<=32)
			tmp=(input_l&(1<<(32-IPtable[i*4+j])))>>(32-IPtable[i*4+j]);
		else 
			tmp=(input_r&(1<<(32-(IPtable[i*4+j]-32))))>>(32-(IPtable[i*4+j]-32));
		//printf("tmp%d:%x\n",IPtable[i*4+j],tmp);
			mr|=tmp<<(3-j);
		}
		//printf("%x\t",mr);
		if(i<8)
		{
			IP_loput|=(mr<<((7-i)*4));
		}
		else
		{
			IP_roput|=(mr<<((7-i)*4));
		}
	}
	//printf(" IP_output is %x\t%x\n",IP_loput,IP_roput);
	return 0;
}

//将大小为64字节的字符串转换为两部分，再分别转换为16进制
int str2hex(const char *input, unsigned int *lp, unsigned int *rp)
{
	int cnt = 0,i=0;
	char inputc_l[9] = {' '};
	char inputc_r[9] = {' '};
	*lp=0;*rp=0;
	strncpy(inputc_l, input, 8);
	strncpy(inputc_r, input + 8, 8);
	//printf("inputc_l:%s  inputc_r:%s\n",inputc_l,inputc_r);
	for (cnt = 0;cnt<8;cnt++)
	{
		if((inputc_l[cnt]>=48) && (inputc_l[cnt]<=57))
			inputc_l[cnt]-=48;
		else
			inputc_l[cnt] -= 55;
	//	printf("inputc_l:%x\n",inputc_l[cnt]);
	//	*lp=(*lp)*16+inputc_l;
		*lp|=(inputc_l[cnt]<<(7-cnt)*4);
	//	printf("lp_value:%x\n",*lp);
	}
	for (cnt = 0;cnt<8;cnt++)
	{
		if((inputc_r[cnt]>=48) && (inputc_r[cnt]<=57))
			inputc_r[cnt]-=48;
		else
			inputc_r[cnt] -= 55;
	//	printf("inputc_r:%x\n",inputc_r[cnt]);
		*rp|=(inputc_r[cnt]<<(7-cnt)*4);
	//	printf("rp_value:%x\n",*rp);
		}
	return 0;
}

//E表变换,32位变为48位
void E_exchange(const unsigned int up,char * E_output)
{
	int i=0;
	for(i=0;i<48;i++)
	{
			if((1<<(32-Etable[i]))&up)
			{
				E_output[i]='1';
			}
			else
				E_output[i]='0';
	}
}

void P_exchange(const unsigned int up,unsigned int *out)
{
	int i=0,ptmp=0;
	for(i=0;i<32;i++)
	{
		ptmp=((1<<(32-Ptable[i]))&up)>>(32-Ptable[i]);
		*out|=ptmp<<(31-i);
	}
}

void F_func(const unsigned int fi,const char *k,unsigned int *F_oput)
{
	*F_oput=0;
	char tmp[49]={'0'};
	int i=0;
	unsigned int tmp_value=0;
	unsigned int tmp_oput=0;
	E_exchange(fi,tmp);
//	printf("the output is E:%s\n",tmp);
//	printf("the output is K:%s\n",k);
//	printf("the xorput is X:");
	for(i=0;i<48;i++)
	{
		if(tmp[i]==k[i])
			tmp[i]='0';
		else  			
			tmp[i]='1';
//	printf("%c",tmp[i]);
	}
	//printf("\n");
	for(i=0;i<8;i++)
	{
		tmp_value=Stable[i][((tmp[i*6]-48)<<1) | (tmp[i*6+5]-48)][((tmp[i*6+1]-48)<<3) | ((tmp[i*6+2]-48)<<2)|((tmp[i*6+3]-48)<<1)|(tmp[i*6+4]-48)];
	//printf("tmp_value Stable[%d][%d][%d]is %x\n",i,((tmp[i*6]-48)<<1) | (tmp[i*6+5]-48),((tmp[i*6+1]-48)<<3) | ((tmp[i*6+2]-48)<<2)|((tmp[i*6+3]-48)<<1)|(tmp[i*6+4]-48),tmp_value);
		tmp_oput|=(tmp_value<<(7-i)*4);
	}
	//printf("the tmp output is %x\n",tmp_oput);
		P_exchange(tmp_oput,F_oput);
		//printf("the F output is %x\n",*F_oput);
}

//KEY的输入形式为16进制的字符串形式，共64位。
void K_generate(const int n,const char * k_str,char *k_out)
{
	int i=0,j=0,tmp=0;
	unsigned int lp=0,rp=0;
	char k_cbuffer[29]={'0'},k_dbuffer[29]={'0'};
	char k_cout[29]={'0'},k_dout[29]={'0'};
	str2hex(k_str,&lp,&rp);
	//printf("in k_generate......lp is %x\t rp is %x\n",lp,rp);
	for(i=0;i<56;i++)
	{
			tmp=PC1table[i];
			//printf("tmp is  %d\n",tmp);
			if(i<28)
			{
				if(tmp>32)
				{
					if((1<<(32-(tmp-32)))&rp)
						k_cout[i]='1'; 
					else 
						k_cout[i]='0';
					//printf("%x,%d, ",((1<<(tmp-33))&lp)>>(tmp-33),tmp);
				}
				if(tmp<=32)
				{
					if((1<<(32-tmp))&lp)
						k_cout[i]='1';
					else 
						k_cout[i]='0';
					//printf("%x, %d,",((1<<(tmp-1))&rp)>>(tmp-1),tmp);
				}
			}
			if(i>=28)
			{
				if(tmp>32)
				{
					if((1<<(32-(tmp-32)))&rp)
						k_dout[i-28]='1';
					else 
						k_dout[i-28]='0';
				}
				 if(tmp<=32)
				{
					if((1<<(32-tmp))&lp)
						k_dout[i-28]='1';
					else 
						k_dout[i-28]='0';
				}
			}
	}
	//printf("the cout is %s,dout is %s\n",k_cout,k_dout);
	/*
}
*/
	for(i=0;i<=n;i++)
	{
		left_shift(LStable[i],k_cout,k_cbuffer);
		stpcpy(k_cout,k_cbuffer);
	//	printf("the c shift%d  %dshift is: %s\n",i,LStable[i],k_cbuffer);
		left_shift(LStable[i],k_dout,k_dbuffer);
		stpcpy(k_dout,k_dbuffer);
		//printf("the d shift%d  %dshift is: %s\n",i,LStable[i],k_dbuffer);
	}

/*
static void PC2_process(const char *k_cbuffer,const char *k_dbuffer,char *k_out)
{
	*/
	j=0;
	tmp=0;
		for(j=0;j<48;j++)
		{
			tmp=PC2table[j];
			if(j<24)                // '='?
				k_out[j]=k_cbuffer[tmp-1];
			else
				k_out[j]=k_dbuffer[tmp-29];
		}
//	return k_out;
}

void left_shift(const int n,char *str,char *shift_buffer)
{
	int i=0;
	char tmp1='0',tmp2='0';
	if(n==1)
	{
		shift_buffer[27]=str[0];
		for(i=0;i<27;i++)           //here should be 27
			shift_buffer[i]=str[i+1];
	}
	else if(n==2)
	{
		shift_buffer[26]=str[0];
		shift_buffer[27]=str[1];
		for(i=0;i<26;i++)
			shift_buffer[i]=str[i+2];
	}
	//printf("after shift output:%s\n",shift_buffer);
}

void reverse_ip_process(const unsigned int *VIP_ptr,const unsigned int input_l,const unsigned int input_r,unsigned int *VIP_loput,unsigned int *VIP_roput)
{
	int cnt = 0,i=0,j=0;
	unsigned int tmp=0,mr=0;
//	printf("left:%x \tright:%x \n",input_l,input_r);
	*VIP_loput=0;
	*VIP_roput=0;
	for(i=0;i<16;i++)
	{
		mr=0;
		for(j=0;j<4;j++)
		{
		if(VIP_ptr[i*4+j]<=32)
			tmp=(input_l&(1<<(32-VIP_ptr[i*4+j])))>>(32-VIP_ptr[i*4+j]);
		else 
			tmp=(input_r&(1<<(32-(VIP_ptr[i*4+j]-32))))>>(32-(VIP_ptr[i*4+j]-32));
		//printf("tmp%d:%x\n",VIPtable[i*4+j],tmp);
			mr|=tmp<<(3-j);
		}
		//printf("%x\t",mr);
		if(i<8)
		{
			*VIP_loput|=(mr<<((7-i)*4));
		}
		else
		{
			*VIP_roput|=(mr<<((7-i)*4));
		}
	}
	//printf("VIP_output is %x\t%x\n",VIP_loput,VIP_roput);
}












