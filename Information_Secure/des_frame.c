#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"aes.h"
#include"des.h"

char des_pathname[90]="/mnt/hgfs/winshare/Information_Secure/test.c";
static void get_des_buffer(FILE *fp,int *break_flag,int des_type);
int file_count=0;       //record the count of file,each count means 8 Byte.
int left_mark=0,right_mark=0;
int des_encrypt_file(void)
{
	char des_out[16]={0},des_rout[9]={0};
	int i=0,break_flag=0,tmp_cnt=0;
	FILE *fp1=NULL;
	FILE *fp2=NULL;
	fp1=fopen(des_pathname,"r");
	if(fp1==NULL)
	{
		printf("open file error.\n");
		return -1;
	}
	char drive[5];
	char dir[60];
	char filename[20];
	char ext[5];
	_splitpath(des_pathname,drive,dir,filename,ext);
	strcat(filename,"_des");
	_makepath(aes_pathname,drive,dir,filename,ext);
	printf("the des encrypt outfile is %s\n",aes_pathname);
	fp2=fopen(aes_pathname,"w+");
	while(!break_flag)
	{
		get_des_buffer(fp1,&break_flag,0);
		tmp_cnt++;
		des();
		sprintf(des_out,"%08x",VIP_loput);
		sprintf(des_rout,"%08x",VIP_roput);
		strcat(des_out,des_rout);
		/*
		if(break_flag==0)                    //check at the last count,if there is some needless zero at left in array.
		{
			if(VIP_loput<0x10000000)
				left_mark=1;
			if(VIP_roput<0x10000000)
				right_mark=1;
		}
		*/
		printf("the des_out is %s.\n\n",des_out);
		fwrite(des_out,sizeof(des_out),1,fp2);
	}
	file_count=tmp_cnt;
	printf("the file count is %d.\n",file_count);
	fclose(fp1);
	fclose(fp2);
	return 0;
	
}

int des_decrypt_file(void)
{
	char des_out[8]={0},tmp_out[8]={0};
	int i=0,j=0,k=0,break_flag=0;
	FILE *fp1=NULL;
	FILE *fp2=NULL;
	fp1=fopen(des_pathname,"r");
	//printf("in des_decrypt original pathname is %s.\n",des_pathname);
	if(fp1==NULL)
	{
		printf("open file error.\n");
		return -1;
	}
	char drive[5];
	char dir[60];
	char filename[20];
	char ext[5];
	_splitpath(des_pathname,drive,dir,filename,ext);
	strcat(filename,"_new");
	_makepath(des_pathname,drive,dir,filename,ext);
	printf("the des encrypt outfile is %s\n",des_pathname);
	fp2=fopen(des_pathname,"w+");
	while(!break_flag && file_count)
	{
		get_des_buffer(fp1,&break_flag,1);
		file_count--;

		printf("in des_decrypt_file buffer is %s.\n",buffer);
		str_format(buffer,input);
		str2hex(input,&VIP_loput,&VIP_roput);
		reverse_des();
		for(i=0;i<8;i++)
		{
			if(i<4)
				des_out[i]=rVIP_loput>>(32-(i+1)*8);
			else
				des_out[i]=rVIP_roput>>(32-(i+1)*8);
		}
		
		printf("the des_out is %s.\n\n",des_out);
		
		if(file_count==0)
		{
			//printf("the des_out is %s\n\n",des_out);
			for(j=0;j<8;j++)
			{
				printf("every char is %x\n",des_out[j]);
				
				if(des_out[j]!=0)
				{
					fputc(des_out[j],fp2);
				}
			}
				
			fclose(fp1);
			fclose(fp2);
			return 0;
		
		}
		
		fwrite(des_out,sizeof(des_out),1,fp2);
	}
	printf("the file count is %d.\n",file_count);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

static void get_des_buffer(FILE *fp,int *break_flag,int des_type)
{
	int i=0,j=0 ;
	char tmp_buffer[3],tmp;
	memset(tmp_buffer,'\0',sizeof(tmp_buffer));
	memset(buffer,'\0',sizeof(buffer));
	if(!des_type)                   //des_type==0,this is for the des_encrypt
	{
		for(i=0;i<8;i++)
		{
			tmp=fgetc(fp);
			if(tmp!=EOF)
			{
				sprintf(tmp_buffer,"%x",tmp);
				if(strlen(tmp_buffer)<2)
				{
					tmp_buffer[1]=tmp_buffer[0];
					tmp_buffer[0]='0';
				}
				strcat(buffer,tmp_buffer);
			}
			else
			{
				*break_flag=1;
				return ;
			}
		}
	}
	if(des_type==1)                   //des_type==0,this is for the des_encrypt
	{
		for(i=0;i<16;i++)
		{
			tmp=fgetc(fp);
			if(tmp!=EOF)
			{
				buffer[i]=tmp;
			}
			else
			{
				*break_flag=1;
				return ;
			}
		}
			
	}
}



















