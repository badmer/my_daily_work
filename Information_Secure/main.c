#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"des.h"
#include"aes.h"
// int str2hex(const char *input, unsigned int *lp, unsigned int *rp);
//extern void des();
//extern void reverse_des();
GdkPixbuf *create_pixbuf(const gchar *filename);
void on_button_clicked(GtkWidget *button,gpointer data);
void select_file(GtkWidget *gtkwidget,gpointer data);
/********select the test_encrypt type*************/
	//GtkWidget *select_box1;
	//GtkWidget *select_button1_1;
	//GtkWidget *select_button1_2;
	//GSList *group1=NULL;
/********select the file_encrypt type*************/
	//GtkWidget *select_box2;
	//GtkWidget *select_button2_1;
	//GtkWidget *select_button2_2;
	//GSList *group2=NULL;
/******box1**using for des encrpyt******/
	GtkWidget *box1;
	GtkWidget *label1;
	GtkWidget *entry1;
	GtkWidget *button1;
	/*****box1_2**using for key************/
	GtkWidget *box1_2;
	GtkWidget *label1_2;
	GtkWidget *entry1_2;
	GtkWidget *button1_2;
	/******box2**using for des decrypt******/
	GtkWidget *box2;
	GtkWidget *label2;
	GtkWidget *entry2;
	GtkWidget *button2;
	/*****box2_1**using for des decrypt output************/
	GtkWidget *box2_1;
	GtkWidget *label2_1;
	GtkWidget *entry2_1;
	/***half above in box**/
	GtkWidget *hbox1;
	GtkWidget *vbox1_1;
	GtkWidget *vbox1_2;
	/*****in  vbox1_2********/
	GtkWidget *text1_label;
	GtkWidget *text1;
	GtkWidget *text1_scrolled;
	GtkTextBuffer *text1_buffer;
	GtkTextIter *Iter;
	GtkWidget *sep;
	/******in below half******/
	GtkWidget *hbox2;
	GtkWidget *hbox3;
	GtkWidget *sentry;
	GtkWidget *sbutton;       //select button
	GtkWidget *ai_button;
	GtkWidget *ai_label;
	GtkWidget *aes_decrypt_button;
	//GtkWidget *fchooser;      //select dialog
	GtkWidget *k_label;
	GtkWidget *k_entry;
	GtkWidget *hidden_button;
int main(int argc , char *argv[])
{

	GtkWidget *box;
	GtkWidget *window;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//set the window
	gtk_window_set_title(GTK_WINDOW(window),"DES-PRACTICE,Using GTK2,Beta0.1");
	gtk_window_set_default_size(GTK_WINDOW(window),500,400); //advice 1000,800
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(window),create_pixbuf("icon.jpg"));
	
	box=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);

	hbox1=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),hbox1,FALSE,FALSE,5);
	
	vbox1_1=gtk_vbox_new(FALSE,0);
	vbox1_2=gtk_vbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),vbox1_1,FALSE,FALSE,20);
	gtk_box_pack_start(GTK_BOX(hbox1),vbox1_2,FALSE,FALSE,20);
	text1_label=gtk_label_new("Relative Information:");
	//text1_scrolled
	text1_scrolled=gtk_scrolled_window_new(NULL,NULL);
	//TEXT1
	text1=gtk_text_view_new();
	gtk_widget_set_size_request(text1,600,250);
	gtk_box_pack_start(GTK_BOX(vbox1_2),text1_label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1_2),text1_scrolled,FALSE,FALSE,5);
//	gtk_box_pack_start(GTK_BOX(vbox1_2),text1,FALSE,FALSE,0);

	gtk_container_add(GTK_CONTAINER(text1_scrolled),text1);
/********************this is the in hbox1**************************/
	//box1
	//create a row entry1.
	box1=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1_1),box1,FALSE,FALSE,20);

	/*******select test_box****************/
	//select_box1=gtk_vbox_new(FALSE,0);
	//gtk_box_pack_start(GTK_BOX(box1),select_box1,FALSE,FALSE,5);
//	type_label=gtk_label_new("encrypt/decrypt_type");
//	gtk_box_pack_start(GTK_BOX(box1),type_label,FALSE,FALSE,5);


	/*******SELECT BUTTON1***************/
	/*
	group1=gtk_radio_button_group(GTK_RADIO_BUTTON(select_button1_1));
	select_button1_1=gtk_radio_button_new_with_label(group1,"DES_input");
	gtk_box_pack_start(GTK_BOX(select_box1),select_button1_1,FALSE,FALSE,0);
	select_button1_2=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(select_button1_1),"AES_input");
	gtk_signal_connect(G_OBJECT(select_button1_2),"toggled",G_CALLBACK(on_button_clicked),(gpointer)6);
	gtk_signal_connect(G_OBJECT(select_button1_1),"toggled",G_CALLBACK(on_button_clicked),(gpointer)7);
	gtk_box_pack_start(GTK_BOX(select_box1),select_button1_2,FALSE,FALSE,0);
*/
	entry1=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry1),16);
	gtk_widget_set_size_request(entry1,280,30);
	gtk_entry_set_text(GTK_ENTRY(entry1),"abcdef1234567890");
	//label1
	label1=gtk_label_new("data_input");
	//button1
	button1=gtk_button_new_with_label("encrpyt");
	g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(on_button_clicked),(gpointer)1);
	gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(box1),entry1,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(box1),button1,FALSE,TRUE,5);
	
	//box1_2
	box1_2=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1_1),box1_2,FALSE,FALSE,20);
	//create a label1_2
	label1_2=gtk_label_new("KEY");
	//create a row entry1_2.
	entry1_2=gtk_entry_new();
	gtk_widget_set_size_request(entry1_2,280,30);
	gtk_entry_set_max_length(GTK_ENTRY(entry1_2),16);
	gtk_entry_set_text(GTK_ENTRY(entry1_2),"aed123bc34213fc2");
	//create button1_2.
	button1_2=gtk_check_button_new_with_label("invisable");
	g_signal_connect(G_OBJECT(button1_2),"clicked",G_CALLBACK(on_button_clicked),(gpointer)2);
	gtk_box_pack_start(GTK_BOX(box1_2),label1_2,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(box1_2),entry1_2,FALSE,FALSE,20);
	gtk_box_pack_start(GTK_BOX(box1_2),button1_2,FALSE,FALSE,5);

	//box2
	box2=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1_1),box2,FALSE,FALSE,20);
	//create a row entry2.
	entry2=gtk_entry_new();
	gtk_widget_set_size_request(entry2,280,30);
	gtk_entry_set_max_length(GTK_ENTRY(entry2),16);
	gtk_entry_set_text(GTK_ENTRY(entry2),"");
	//label2
	label2=gtk_label_new("data_encrypt_output");
	//button2
	button2=gtk_button_new_with_label("decrpyt");
	g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(on_button_clicked),(gpointer)3);
	gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(box2),entry2,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(box2),button2,FALSE,TRUE,5);

	//box2_1
	box2_1=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1_1),box2_1,FALSE,FALSE,20);
	label2_1=gtk_label_new("data_decrypt_output");
	gtk_box_pack_start(GTK_BOX(box2_1),label2_1,FALSE,FALSE,5);
	entry2_1=gtk_entry_new();
	gtk_widget_set_size_request(entry2_1,280,30);
	gtk_entry_set_max_length(GTK_ENTRY(entry2_1),16);
	gtk_entry_set_text(GTK_ENTRY(entry2_1),"");
	gtk_box_pack_start(GTK_BOX(box2_1),entry2_1,FALSE,TRUE,1);


	//separate line
	sep=gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,50);

	/***************half below**********************/

	//hbox2
	hbox2=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),hbox2,FALSE,FALSE,5);
	//ai_label
	ai_label=gtk_label_new("file_input");
		/*******select file_box****************/
	//select_box2=gtk_vbox_new(FALSE,0);
	//gtk_box_pack_start(GTK_BOX(hbox2),select_box2,FALSE,FALSE,5);
//	type_label=gtk_label_new("encrypt/decrypt_type");
//	gtk_box_pack_start(GTK_BOX(box1),type_label,FALSE,FALSE,5);
	/*******SELECT BUTTON2***************/
	/*
	group2=gtk_radio_button_group(GTK_RADIO_BUTTON(select_button2_1));
	select_button2_1=gtk_radio_button_new_with_label(group2,"DES_file_input");
	g_signal_connect(G_OBJECT(select_button2_1),"toggled",G_CALLBACK(on_button_clicked),(gpointer)9);
	gtk_box_pack_start(GTK_BOX(select_box2),select_button2_1,FALSE,FALSE,0);
	select_button2_2=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(select_button2_1),"AES_file_input");
	g_signal_connect(G_OBJECT(select_button2_2),"toggled",G_CALLBACK(on_button_clicked),(gpointer)10);
	gtk_box_pack_start(GTK_BOX(select_box2),select_button2_2,FALSE,FALSE,0);
	*/
	//sentry
	sentry=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(sentry),100);
	gtk_widget_set_size_request(sentry,400,30);
	gtk_entry_set_text(GTK_ENTRY(sentry),"/mnt/hgfs/winshare/Information_Secure/test.c");
	//select button
	sbutton=gtk_button_new_with_label("select");
	g_signal_connect(G_OBJECT(sbutton),"clicked",G_CALLBACK(select_file),NULL);
	gtk_box_pack_start(GTK_BOX(hbox2),ai_label,FALSE,FALSE,1);
	gtk_box_pack_start(GTK_BOX(hbox2),sentry,FALSE,TRUE,1);
	gtk_box_pack_start(GTK_BOX(hbox2),sbutton,FALSE,FALSE,5);
	//aes input :encrypt button,decrypt button
	ai_button=gtk_button_new_with_label("encrypt");
	g_signal_connect(G_OBJECT(ai_button),"clicked",G_CALLBACK(on_button_clicked),(gpointer)4);
	aes_decrypt_button=gtk_button_new_with_label("decrypt");
	g_signal_connect(G_OBJECT(aes_decrypt_button),"clicked",G_CALLBACK(on_button_clicked),(gpointer)5);
	
	gtk_box_pack_start(GTK_BOX(hbox2),ai_button,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox2),aes_decrypt_button,FALSE,FALSE,5);
	//in aes ,k_input
	hbox3=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),hbox3,FALSE,FALSE,5);
	k_label=gtk_label_new("k_input");
	k_entry=gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(k_entry),"aed123bc34213fc2");
	gtk_widget_set_size_request(k_entry,300,30);
	hidden_button=gtk_check_button_new_with_label("invisable");
	g_signal_connect(G_OBJECT(hidden_button),"clicked",G_CALLBACK(on_button_clicked),(gpointer)8);
	gtk_box_pack_start(GTK_BOX(hbox3),k_label,FALSE,FALSE,1);
	gtk_box_pack_start(GTK_BOX(hbox3),k_entry,FALSE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(hbox3),hidden_button,FALSE,FALSE,5);
	gtk_widget_show_all(window);
	//click 'X',then close.
	g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();
	return 0;

}

//create the program's icon at bottom
GdkPixbuf *create_pixbuf(const gchar *filename)
{
	GdkPixbuf *pixbuf;
	GError *error=NULL;
	pixbuf=gdk_pixbuf_new_from_file(filename,&error);
	if(!pixbuf)
	{
		fprintf(stderr,"%s\n",error->message);
		g_error_free(error);
	}
	return pixbuf;
}

void on_button_clicked(GtkWidget *button,gpointer data)
{
	//gchar *text_content;
	GtkTextIter start,end;
	GtkWidget *error_dialog;

	if((int)data==1)   //这里是encrypt button
	{
		const gchar	*gbuffer=gtk_entry_get_text(GTK_ENTRY(entry1));
		const gchar	*gkey=gtk_entry_get_text(GTK_ENTRY(entry1_2));

		//if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button1_1)))
	//	{
		sprintf(buffer,"%s",gbuffer);
		sprintf(key,"%s",gkey);
		g_printf("buffer:%s\nkey:%s\n",buffer,key);
		int ret=des();
		if(ret<0)
		{
		//	gtk_entry_set_text(GTK_ENTRY(entry2),"input error");
			error_dialog=gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"input format error,accepted only 0-9&a-f/A-F");
			gtk_dialog_run(GTK_DIALOG(error_dialog));
			gtk_widget_destroy(error_dialog);
		}
		else
		{
			char des_out[18]={'0'},des_rout[9]={'0'};
			sprintf(des_out,"%x",VIP_loput);
			sprintf(des_rout,"%x",VIP_roput);
			strcat(des_out,des_rout);
			gtk_entry_set_text(GTK_ENTRY(entry2),des_out);
		
		text1_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(text1));
		if(value_buffer!=NULL)
			gtk_text_buffer_set_text (text1_buffer,value_buffer, -1);
		//}
		}
		/*
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button1_2)))
		{	
			sprintf(aes_ibuffer,"%s",gbuffer);
			sprintf(k_buffer,"%s",gkey);
		printf("ibuffer;%s\tkbuffer:%s.\n",aes_ibuffer,k_buffer);
			encrypt_data();
			gtk_entry_set_text(GTK_ENTRY(entry2),aes_obuffer);
			
		}*/
	}
	if((int)data==2)
	{
		
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button1_2)))
			gtk_entry_set_visibility(GTK_ENTRY(entry1_2),FALSE); 
		else
			gtk_entry_set_visibility(GTK_ENTRY(entry1_2),TRUE); 
	}
	if((int )data==3)   //这里是decrypt button
	{
		//if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button1_1)))
	//	{
		const gchar* des_output=gtk_entry_get_text(GTK_ENTRY(entry2));
		const gchar *gkey=gtk_entry_get_text(GTK_ENTRY(entry1_2));
		printf("in main reverse des_output:%s,gkey:%s\n",des_output,gkey);
		char des_out[18]={'0'},des_rout[9]={'0'};

		sprintf(key,"%s",gkey);
		sprintf(input,"%s",des_output);
		reverse_des();
		sprintf(des_rout,"%x",rVIP_roput);
		if(rVIP_loput!=0)
		{
		sprintf(des_out,"%x",rVIP_loput);
		//printf("in main reverse VIP_L:%x\tVIP_R:%x\n",rVIP_loput,rVIP_roput);
		strcat(des_out,des_rout);
		}
		else
			strcpy(des_out,des_rout);
		gtk_entry_set_text(GTK_ENTRY(entry2_1),des_out);
	//	}
		/*	
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button1_2)))
		{	
			const gchar* gbuffer=gtk_entry_get_text(GTK_ENTRY(entry2));
			const gchar *gkey=gtk_entry_get_text(GTK_ENTRY(entry1_2));
			sprintf(aes_ibuffer,"%s",gbuffer);
			sprintf(k_buffer,"%s",gkey);
	//		printf("ibuffer;%s\tkbuffer:%s.\n",aes_ibuffer,k_buffer);
			decrypt_data();
			gtk_entry_set_text(GTK_ENTRY(entry2_1),aes_obuffer);
			
		}*/
	}
	if((int)data==4)    
	{
		//des encrypt
	//	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button2_1)))
	//	{
			const gchar *gbuffer=gtk_entry_get_text(GTK_ENTRY(sentry));
			const gchar *gkey=gtk_entry_get_text(GTK_ENTRY(k_entry));
			sprintf(des_pathname,"%s",gbuffer);
			sprintf(key,"%s",gkey);
			des_encrypt_file();
			
			text1_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(text1));
		if(value_buffer!=NULL)
			gtk_text_buffer_set_text (text1_buffer,value_buffer, -1);
	//	}
		//aes encrypt
		/*
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button2_2)))
		{
			const gchar *gbuffer=gtk_entry_get_text(GTK_ENTRY(sentry));
			sprintf(aes_pathname,"%s",gbuffer);
			encrypt_file();
		
		}*/
	}
	if((int)data==5)   
	{
		//des file decrypt
		//if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button2_1)))
	//	{
			const gchar *gbuffer=gtk_entry_get_text(GTK_ENTRY(sentry));
			
			sprintf(des_pathname,"%s",gbuffer);
			//printf("in des_decrypt original pathname is %s.\n",des_pathname);
			des_decrypt_file();
		//}
		//aes file  decrypt
		/*
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(select_button2_2)))
		{
			const gchar *buffer=gtk_entry_get_text(GTK_ENTRY(sentry));
			sprintf(aes_pathname,"%s",buffer);
			decrypt_file();
		}
*/
	}
	/*
	if((int)data==6)
	{
		gtk_entry_set_max_length(GTK_ENTRY(entry1),32);
		gtk_entry_set_max_length(GTK_ENTRY(entry1_2),32);
		gtk_entry_set_max_length(GTK_ENTRY(entry2),32);
		gtk_entry_set_max_length(GTK_ENTRY(entry2_1),32);
		
		gtk_widget_set_size_request(entry1,280,30);
		gtk_widget_set_size_request(entry1_2,280,30);
		gtk_widget_set_size_request(entry2,280,30);
		gtk_widget_set_size_request(entry2_1,280,30);
		
		gtk_entry_set_text(GTK_ENTRY(entry1),"328831e0435a3137f6309807a88da234");
		gtk_entry_set_text(GTK_ENTRY(entry1_2),"2b7e151628aed2a6abf7158809cf4f3c");
	}
	
	if((int)data==7)
	{
		gtk_entry_set_max_length(GTK_ENTRY(entry1),16);
		gtk_entry_set_max_length(GTK_ENTRY(entry1_2),16);
		gtk_entry_set_max_length(GTK_ENTRY(entry2),16);
		gtk_entry_set_max_length(GTK_ENTRY(entry2_1),16);
		
			gtk_widget_set_size_request(entry1,140,30);
		gtk_widget_set_size_request(entry1_2,140,30);
		gtk_widget_set_size_request(entry2,140,30);
		gtk_widget_set_size_request(entry2_1,140,30);
		
		gtk_entry_set_text(GTK_ENTRY(entry1),"123456789abcdef0");
		gtk_entry_set_text(GTK_ENTRY(entry1_2),"aed123bc34213fc2");
	}*/
	if((int)data==8)
	{
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(hidden_button)))
		  gtk_entry_set_visibility(GTK_ENTRY(k_entry),FALSE);
		else
		  gtk_entry_set_visibility(GTK_ENTRY(k_entry),TRUE);

	}/*
	if((int)data==9)
	{
		gtk_entry_set_max_length(GTK_ENTRY(k_entry),16);
	}
	if((int)data==10)
	{
		gtk_entry_set_max_length(GTK_ENTRY(k_entry),32);
	}
*/
}

void select_file(GtkWidget *widget,gpointer data)
{
	GtkWidget *file_chooser;
	int file_return;
	gchar *filename;

	file_chooser=gtk_file_chooser_dialog_new("Select File",NULL,GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,NULL);
	if(gtk_dialog_run(GTK_DIALOG(file_chooser))==GTK_RESPONSE_ACCEPT)
	{	
	//	print_filename(file_chooser);
		filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
		gtk_entry_set_text(GTK_ENTRY(sentry),filename);
		gtk_widget_destroy(file_chooser);
	}
	else
	  gtk_widget_destroy(file_chooser);

}





