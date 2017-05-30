#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "aes.h"
#include	"des.h"

unsigned int word[44] = { 0 };
//using for the aes_file_process
char aes_pathname[90]="/mnt/hgfs/winshare/Information_Secure/test_file";
char aes_outfile[90]="";
// format the input test data to state
char aes_ibuffer[33]="";
char aes_obuffer[33]="";
char k_buffer[33]="";
//using for counting the end index
unsigned int count=0;         //count the number of 16byte 
int end_index=0;
int tmp_index=0;
int end_flag=0;

byte state[4][4] = {
		0x32, 0x88, 0x31, 0xe0,
		0x43, 0x5a, 0x31, 0x37,
		0xf6, 0x30, 0x98, 0x07,
		0xa8, 0x8d, 0xa2, 0x34
	};
byte aes_key[16] = {
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c
	};
const unsigned char S_box[] = 
{
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
const unsigned char Inverse_S_box[] =
{
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};
const unsigned char a[4][4]=
{
	{0x02, 0x03, 0x01, 0x01},
	{0x01, 0x02, 0x03, 0x01},
	{0x01, 0x01, 0x02, 0x03},
	{0x03, 0x01, 0x01, 0x02}
};
const unsigned char Inverse_a[4][4] =
{
	{0x0e, 0x0b, 0x0d, 0x09},
	{0x09, 0x0e, 0x0b, 0x0d},
	{0x0d, 0x09, 0x0e, 0x0b},
	{0x0b, 0x0d, 0x09, 0x0e}
};
const unsigned int Rcon[] =
{
	0x00000000 , 0x01000000, 0x02000000, 0x04000000, 0x08000000, 
	0x10000000, 0x20000000 , 0x40000000, 0x80000000, 0x1b000000, 0x36000000
};
//byte aes_buffer[4][4];
/*
int main(void)
{
	//printState("before MixColumn", state);
	//MixColumn(state);
	//Inverse_MixColumn(state);
	//printState("after MixColumn", state);
	encrypt_frame();
	//printf("count is %d\n\n",count);
	decrypt_frame();
	return 0;
}
*/
int encrypt_file(void)
{
	int i=0,j=0;
	end_flag=0,count=0,end_index=0;
	FILE *fp1=NULL;
	FILE *fp2=NULL;
	fp1=fopen(aes_pathname,"r");
	if(fp1==NULL)
	{
		printf("open file error.\n");
		return -1;
	}
	char drive[5];
	char dir[60];
	char filename[20];
	char ext[5];
	_splitpath(aes_pathname,drive,dir,filename,ext);
	strcat(filename,"_aes");
	_makepath(aes_pathname,drive,dir,filename,ext);
	//strcpy(encrypt_aes_outfile,aes_pathname);
	
	printf("the aes encrypt outfile is %s\n",aes_pathname);
	fp2=fopen(aes_pathname,"w+");
	KeyExpansion(aes_key);
	while(!end_flag)
	{
		get_one_buffer(fp1);
		/*
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				printf("input:%x\n",state[i][j]);
			printf("\n");
	printf("the tmp_index is %d\n",tmp_index);
	*/
	//KeyExpansion(aes_key);
	encrypt(state);
	//printState("after encrypt", state);
	fwrite(state,sizeof(state),1,fp2);
	count++;
	}
	end_index=tmp_index%16;
	//printf("tmp_index=%d,\n",tmp_index);
	fclose(fp1);
	fclose(fp2);
//	printf("after aes_encrypt ,count=%d,end_flag=%d,end_index=%d\n",count,end_flag,end_index);
	return 0;
}

int decrypt_file(void)
{
	int i=0,j=0;
	end_flag=0;
	FILE *fp1=NULL,*fp2=NULL;
	fp1=fopen(aes_pathname,"r");         //open the decrypt_input_file
	char drive[5];
	char dir[60];
	char filename[20];
	char ext[5];
	_splitpath(aes_pathname,drive,dir,filename,ext);
	strcat(filename,"_new");
	_makepath(aes_pathname,drive,dir,filename,ext);
	
	fp2=fopen(aes_pathname,"w+");
	KeyExpansion(aes_key);
	if(fp1==NULL)
	{
		printf("open file error.\n");
		perror("open");
		return -1;
	}
	//while(!end_flag&&count)
	while(count)
	{
		get_one_buffer(fp1);
		count--;
		//KeyExpansion(aes_key);
		decrypt(state);
		if(count>=0)
		{
		if(count==0)
		{
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
				{
					if((i*4+j+1)<=end_index)
					{
						fputc(state[i][j],fp2);
						printf("i=%d,j=%d\n",i,j);
					}
					else 
					{
						fclose(fp1);
						fclose(fp2);
						printf("hello.\n");
						printf("in aes_decrypt ,count=%d,end_flag=%d,end_index=%d\n",count,end_flag,end_index);
						return 0;
					}
				}	
		}
		else
			fwrite(state,sizeof(state),1,fp2);
			printf("i have written once.\n");
		}
	}
		fclose(fp1);
		fclose(fp2);
		//printf("in aes_decrypt ,count=%d,end_flag=%d,end_index=%d\n",count,end_flag,end_index);
	return 0;
}

void get_one_buffer(FILE *fp)
{
	int i=0,j=0;
	char tmp;
	memset(state,'\0',sizeof(state));
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				tmp=fgetc(fp);
				if(tmp!=EOF)
				{
					state[i][j]=tmp;
					tmp_index++;
				}
				else
				{
					end_flag=1;
					return ;
				}
			}
		}
}
void encrypt_data()
{
	char tmp_str[3]="0";
	int i=0,j=0,flag=0;
	format_process(aes_ibuffer,0);
	format_process(k_buffer,1);
	KeyExpansion(aes_key);
	encrypt(state);
	decrypt(state);

	//decrypt(state);
	/*
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				printf("decrypt out:%x\n",state[i][j]);
			
			printf("\n");
	*/
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			
			if(state[i][j]!=0x00)
				flag=1;
			if(flag)
			{
			sprintf(tmp_str,"%x",state[i][j]);
			//printf("len:%d.\n",strlen(tmp_str));
			
			if(strlen(tmp_str)<2)
			{
				tmp_str[1]=tmp_str[0];
				tmp_str[0]='0';
			}
			strcat(aes_obuffer,tmp_str);
			}
		}
	
}

void decrypt_data(void)
{
	char tmp_str[3]="0";
	int i=0,j=0,flag=0;
	format_process(aes_ibuffer,0);
	format_process(k_buffer,1);
	KeyExpansion(aes_key);
	decrypt(state);

	//decrypt(state);
	/*
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				printf("decrypt out:%x\n",state[i][j]);
			
			printf("\n");
	*/
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(state[i][j]!=0x00)
				flag=1;
			if(flag)
			{
			sprintf(tmp_str,"%x",state[i][j]);
			strcat(aes_obuffer,tmp_str);
			}
		}
	
}
void format_process(char *str,int flag)
{
	char tmp[33],tmpc='0';
	int len=0,i=0,j=0;
	memset(tmp,0,sizeof(tmp));
	//printf("ibuffer;%s\tkbuffer:%s.\n",aes_ibuffer,k_buffer);
	len=strlen(str);
	for(i=0;i<32;i++)
    printf("in aes,str=%u.\n",str[i]);
	printf("\n");
	
	for(i=0;i<(32-len);i++)
	{
		tmp[i]='0';
	}
	
	for(i=32-len;i<32;i++)
	{
		tmpc=str[i+len-32];
		//printf("tmpc is %u.\n",tmpc);
		if((tmpc<=57)&& (tmpc>=48))
			tmp[i]=tmpc-48;
		if((tmpc >= 65) && (tmpc <= 70))
			tmp[i]=tmpc-55;
		if(tmpc >= 97 && tmpc <= 102)
			tmp[i]=tmpc-87;
	}
	/*
	for(i=0;i<32;i++)
    printf("in aes,tmp=%u.\n",tmp[i]);
	printf("\n");
	*/
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{/*
			if(tmp[(i*4+j)*2]<97)
			array[i][j]=((tmp[(i*4+j)*2]-87)<<16) | tmp[(i*4+j)*2+1];
		*/
		if(flag==0)
		{
			state[i][j]=((tmp[(i*4+j)*2])<<4) | tmp[(i*4+j)*2+1];
			//printf("state[%d][%d]:%x\n",i,j,state[i][j]);
		}
		if(flag==1)
		{
			aes_key[i*4+j]=((tmp[(i*4+j)*2])<<4) | tmp[(i*4+j)*2+1];
			//printf("aes_key[%d][%d]:%x\n",i,j,aes_key[i][j]);
		}
		}
	
}

void Subbytes(unsigned char state[][4])
{
	int i=0,j=0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			int tmp = state[i][j];
			state[i][j] = S_box[tmp];
		}
}
void Inverse_Subbytes(unsigned char state[][4])
{
	int i=0,j=0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			int tmp = state[i][j];
			state[i][j] = Inverse_S_box[tmp];
		}
}
void ShiftRow(unsigned char state[][4])
{
	int i=0,j=0;
	for (i = 1; i < 4; i++)
	{
		unsigned char tmp[4];
		for (j = 0; j < 4; j++)
			tmp[j] = state[i][j];
		for (j = 0; j < 4; j++)
			state[i][j] = tmp[(i + j) & 3];
	}
}
void Inverse_ShiftRow(unsigned char state[][4])
{
	int i=0,j=0;
	for (i = 1; i < 4; i++)
	{
		unsigned char tmp[4];
		for (j = 0; j < 4; j++)
			tmp[j] = state[i][j];
		for (j = 0; j < 4; j++)
			state[i][j] = tmp[(4 + j - i) % 4];
	}
}
void MixColumn(unsigned char state[][4])
{
	int i=0,j=0,k=0;
	for (j = 0; j < 4; j++)
	{
		unsigned char tmp[4];
		for (i = 0; i < 4; i++)
			tmp[i] = state[i][j];
		for (i = 0; i < 4; i++)
		{
			state[i][j] = MulCompute(a[i][0] , tmp[0]);		//将第一个值赋给state[i][j],使后面的异或结果不受影响
			for (k = 1; k < 4; k++)
				state[i][j] ^= MulCompute(a[i][k] , tmp[k]);
		}
	}
}
void Inverse_MixColumn(unsigned char state[][4])
{
	int i=0,j=0,k=0;
	for (j = 0; j < 4; j++)
	{
		unsigned char tmp[4];
		for (i = 0; i < 4; i++)
			tmp[i] = state[i][j];
		for (i = 0; i < 4; i++)
		{
			state[i][j] = MulCompute(Inverse_a[i][0], tmp[0]);		//将第一个值赋给state[i][j],使后面的异或结果不受影响
			for (k = 1; k < 4; k++)
				state[i][j] ^= MulCompute(Inverse_a[i][k], tmp[k]);
		}
	}
}
unsigned char MulCompute(unsigned char a , unsigned char s)
{
	//unsigned char res = 0;
	//for (int i = 0; i < 8; i++)
	//{
	//	if (((a >> i) & 1) == 0)
	//		continue;
	//	if (s < (1 << (6 - i)))
	//		res ^= s << i;
	//	else res ^= ((s << i) ^ MODULE);
	//}
	//return res;
	switch (a)
	{
	case 1:return s;break;
	case 2:if (s < 0x80)
		return s << 1;
		   else return (s << 1) ^ MODULE;
			   break;
	case 3:return s ^ MulCompute(2, s);break;
	case 4:if (s < 0x80)
		return MulCompute(2, s << 1);
		   else return MulCompute(2 , (s << 1) ^ MODULE);
	case 8:if (s < 0x80)
		return MulCompute(4, s << 1);
		   else return MulCompute(4, (s << 1) ^ MODULE);
	case 9:return MulCompute(8, s) ^ s;
	case 0x0b:return MulCompute(8, s) ^ MulCompute(2, s) ^ s;
	case 0x0d:return MulCompute(8, s) ^ MulCompute(4, s) ^ s;
	case 0x0e:return MulCompute(8, s) ^ MulCompute(4, s) ^ MulCompute(2 ,s);
	default:return 0;break;
	}
}
void KeyExpansion(unsigned char *key)
{
	int i=0,j=0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			word[i] = (word[i] << 8) + key[(i << 2) + j];
	for (; i < 44; i++)
	{
		unsigned int tmp = word[i - 1];
		if ((i % 4) == 0)
			tmp = SubWord(RotWord(tmp)) ^ Rcon[i >> 2];
		word[i] = word[i - 4] ^ tmp;
	}
}
unsigned int SubWord(unsigned int w)
{
	int res = 0;
	int i=0,j=0;
	for (i = 0; i < 4; i++)
	{
		int index = (w >> ((3 - i) << 3)) & 0xff;
		res = (res << 8) + S_box[index];
	}
	return res;
}
unsigned int RotWord(unsigned int w)
{
	w = (w << 8) + ((w >> 24) & 0xff);
	return w;
}
void AddAroundKey(int round, unsigned char state[][4])
{
	int i=0,j=0;
	int base = round << 2;
	for (j = 0; j < 4; j++)
	{
		unsigned int w = word[base + j];
		for (i = 0; i < 4; i++)
			state[i][j] ^= ((w >> ((3 - i) << 3)) & 0xff);
	}
}
void encrypt(unsigned char state[][4])
{
	int round = 0;
	AddAroundKey(round , state);
	for (round = 1; round < 10; round++)
	{
		Subbytes(state);
		ShiftRow(state);
		MixColumn(state);
		AddAroundKey(round , state);
	}
	Subbytes(state);
	ShiftRow(state);
	AddAroundKey(round, state);
}
void decrypt(unsigned char state[][4])
{
	int round = 10;
	AddAroundKey(round, state);
	for (round = 9; round > 0; round--)
	{
		Inverse_ShiftRow(state);
		Inverse_Subbytes(state);
		AddAroundKey(round, state);
		Inverse_MixColumn(state);
	}
	Inverse_ShiftRow(state);
	Inverse_Subbytes(state);
	AddAroundKey(round, state);
}
void printState(const char *comment,unsigned char state[][4])
{
	int i=0,j=0;
	printf("%s\n",comment);
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			printf("%2x ", state[i][j]);
		printf("\n");
	}
	printf("\n");
}
void printKey()
{
	int i=0,j=0,k=0;
	for (i = 0; i < 11; i++)
	{
		printf("round %d:\n", i);
		for (k = 0; k < 4; k++)
		{
			for (j = 0; j < 4; j++)
				printf("%2x", (unsigned char)(word[i * 4 + j] >> ((3 - k) << 3)));
			printf("\n");
		}
		printf("\n");
	}
}

static void _split_whole_name(const char *whole_name, char *fname, char *ext)
{
	char *p_ext;

	p_ext = rindex(whole_name, '.');
	if (NULL != p_ext)
	{
		strcpy(ext, p_ext);
		snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
	}
	else
	{
		ext[0] = '\0';
		strcpy(fname, whole_name);
	}
}
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
{
	char *p_whole_name;

	drive[0] = '\0';
	if (NULL == path)
	{
		dir[0] = '\0';
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	if ('/' == path[strlen(path)])
	{
		strcpy(dir, path);
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	p_whole_name = rindex(path, '/');
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		_split_whole_name(p_whole_name, fname, ext);

		snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		_split_whole_name(path, fname, ext);
		dir[0] = '\0';
	}
}

void _makepath(char *path, char *drive, char *dir, char *fname, char *ext)
{
	char tmp[2];
	tmp[0]='/';
	tmp[1]='\0';
	strcpy(path,drive);
	strcat(path,dir);
	strcat(path,tmp);
	strcat(path,fname);
	strcat(path,ext);
}
