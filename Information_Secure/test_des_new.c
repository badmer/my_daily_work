#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"des.h"
//#include"aes.h"
// int str2hex(const char *input, unsigned int *lp, unsigned int *rp);
//extern void des();
//extern void reverse_des();
GdkPixbuf *create_pixbuf(const gchar *filename);
void on_button_clicked(GtkWidget *button,gpointer data);
void select_file(GtkWidget *gtkwidget,gpointer data);
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
	GtkWidget *ai_label;
	GtkWidget *sentry;
	GtkWidget *sbutton;       //select button
	GtkWidget *ai_button;
	GtkWidget *aes_decrypt_button;
	//GtkWidget *fchooser;      //select dialog

	hello world
