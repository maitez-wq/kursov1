#include "stdafx.h" //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>
#include <iostream>
using namespace std;
using namespace System;
using namespace System::IO;
#define ENTER 13 //����������� ������
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79
struct z{
	char name[20]; //��� �������
	char data[20]; //���� �������� �� �����
	long ind; //������ ������
	char procces[20]; //��������� ��������
	long sum; //������� � ��������
	};
struct sp {
	char fio[20];
	long sum;
	struct sp* sled; //��������� �� ��������� ������� � ������
	struct sp* pred; //��������� �� ���������� ������� � ������
	} *spisok; //������, ���������� �������� ��������� ����������� ������
int menu(int); //������� ��� ����, �������� �������� ������������ �������
void perv(struct z*, int);
void alfalist(struct z*,int);
void kolvo(struct z*,int);
void diagram(struct z*,int);
void spiso(struct z*,int);
void odin(struct z*,int);
void ret(struct z*,int);
int main(array<System::String ^> ^args)
{
//�� ��������� ������ ������������ �������� �����,
//��������� ������ �� ����� � ���������� ������
int i,n;
FILE *in;
struct z *clients;
int NC;
char BlankLine[]="                                                                ";//������ ����� ��� �������� ����
	setlocale(LC_CTYPE,"Russian");//��������� �������� �����
	Console::CursorVisible::set(false); //��������� ��������� �������
	Console::BufferHeight=Console::WindowHeight; //��������� ������� ������ �� ������
	Console::BufferWidth=Console::WindowWidth; //��������� ������� ������ �� ������
	if((in=fopen("idea.dat","r"))==NULL) //������� �������� �����
		{
		printf("\n���� idea.dat �� ������ !");
		_getch(); exit(1);} //��� ��������� �������� ����� ��������� ��������� ����� idea.dat �� ������ !�
fscanf(in,"%d",&NC);
clients=(struct z*)malloc(NC*sizeof(struct z)); //�������� ������
for(i=0;i<NC;i++)//��������� ������ �� ������
	fscanf(in,"%s%s%ld%s%ld",clients[i].name,clients[i].data, &clients[i].ind,clients[i].procces,&clients[i].sum);
for(i=0;i<NC;i++)
	printf("\n%-20s %-12s %10ld %-5s %ld",clients[i].name,clients[i].data,clients[i].ind,clients[i].procces,clients[i].sum); //������� ������ �� ������ �� �����
_getch();
char dan[8][65]={
				" ����� ������ ������ ������ �������� �� ������.                 ",
				" ���������� ������ ���� ��������.                               ", 
				" ������� ������� �� ������.                                     ",
				" ������ �������� � ������������ �������� ������.                ",
				" ���������� ������� ��������, �� ������ ��� �������� �� ������. ",
				" ���������. ���������� ��������� ������� � ��������             ",
				" ������� � ������                                               ",
				" �����.                                                         ",
};//������� ������ ��������, ������� ����
while(1){ // � ����� ������� ������� ��� ��������  � ���������� � � �����
//������������� ��� ���� ���� � ��������� ��� ���������� �������

	Console::ForegroundColor=ConsoleColor::DarkYellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::DarkYellow;
	Console::CursorLeft=11; //������ �����, ������ ����� ����������� ������� ����
	Console::CursorTop=4;
	printf(BlankLine);
	for (i=0;i<8;i++){ //���������� ��������
		Console::CursorLeft=11;
		Console::CursorTop=i+5;
		printf("%s",dan[i]);}
	Console::CursorLeft=11; //��������� �����, ��� ����� �������������� ���������� ������� ��� ����
	Console::CursorTop=13;
	printf(BlankLine);
	n = menu(8); //����� ������� � ����
	switch(n){
		case 1: perv(clients, NC);break;
		case 2: alfalist(clients, NC);break;
		case 3: kolvo(clients, NC);break;
		case 4: spiso(clients, NC);break;
		case 5: odin(clients, NC);break;
		case 6: diagram(clients, NC);break;
		case 7: ret(clients, NC);break;
		case 8: exit(0);
		}
	}//����� while(1) 
  return 0;
}// ����� main()
int menu(int n) //n=9
{
	char dan[8][65]={
				" ����� ������ ������ ������ �������� �� ������.                 ",
				" ���������� ������ ���� ��������.                               ", 
				" ������� ������� �� ������.                                     ",
				" ������ �������� � ������������ �������� ������.                ",
				" ���������� ������� ��������, �� ������ ��� �������� �� ������. ",
				" ���������. ���������� ��������� ������� � ��������             ",
				" ������� � ������                                               ",
				" �����.                                                         ",
};//������� ������ ��������, ������� ����
int y1=0,y2=n-1; //������������� ���������� ��� �������
char c=1;
while(c!=ESC) //��� ������� ������ ESC, ���� ���������
	{
	switch(c) { //���������������� ������ �����, ����, �����, ����, END,HOME
		case DOWN: y2=y1; y1++; break;
		case UP: y2=y1; y1--; break;
		case ENTER: return y1+1;
		case END: y2=y1;y1=n-1;break;
		case HOME: y2=y1;y1=0;break;
	}
	if(y1>n-1){y2=n-1;y1=0;} //������� ����� ����������� ������ ����
	if(y1<0) {y2=0;y1=n-1;} //������� ����� ����������� ������ �����
	Console::ForegroundColor=ConsoleColor::White; //��� ������ ������� ����� ������������ � ����� ����
	Console::BackgroundColor=ConsoleColor::Red; //��� ������ ������� ���� �� ������� �������������� �������
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::DarkYellow;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	} //����� while(c!=ESC)
exit(0);
}

void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={"������","�������","�����","������","���","����","����","�������","��������","�������","������","�������"};//������ � ������� ��������� ����������
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return; //������� ��������� ������ � ��������� ����� 
}
//������� ������ ������� ������� ���������� �������� �� ������
void perv(struct z* clients,int NC){
int i;
char s[30];
struct z* own=clients;
for (i=0;i<NC;i++)
	if (strcmp(clients[i].data,own->data)<0) //����� ������� ����
		own=&clients[i];
	text_data(s,own->data);		
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("������ ������ \"�������\" ������ %d ",own->ind);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("����� ������ %s",own->name);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("������ %s ",s);
getch();
}
void vstavka(struct z* clients,char* fio) //������� � ������
{
int i;
int NC=15;
struct sp *nov,*nt,*z=0;
for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled); //���� ����� �������
if(nt && strcmp(nt->fio,fio)==0) return; //�������� �� ������ � ������ ������� �����
nov=(struct sp*)malloc(sizeof(struct sp));
strcpy(nov->fio,fio);
nov->pred=z;
nov->sled=nt;
nov->sum=0;
for(i=0;i<NC;i++)
	if (strcmp(clients[i].name,fio)==0)
			nov->sum+=clients[i].sum;
if(!z) spisok=nov;
else z->sled=nov;
if(nt) nt->pred=nov;
return;
}
//���������� ���� �������� �� ��������, � �������� �������
void alfalist(struct z* clients,int NC){ //������������ ������
int i;
struct sp *nt,*z;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf("\n ���������� ������ ��������");
printf("\t\t�������� ���������� ������");
printf("\n ===========================            ============================\n");
if(!spisok) //������������ ����������� ������
	for(i=0;i<NC;i++)
		vstavka(clients,clients[i].name);
	for (nt=spisok; nt!=0; nt=nt->sled) 
		printf("\n %-20s %ld ", nt->fio, nt->sum); //����� ����������� ������
	for(nt=spisok,z=0; nt!=0; z=nt,nt=nt->sled); {//������������ ��������� ����������� ������
		Console::CursorTop=4;
	for(nt=z;nt!=0;nt=nt->pred)
	{
		Console::CursorLeft=40;
		printf("%-20s  %ld", nt->fio,nt->sum); //����� ��������� ����������� ������
		Console::CursorTop+=1;}
	}
_getch();
}

 //������� ��� ������ ������� �� ������
void kolvo(struct z	*clients,int NC)
{
int i,k=0;
for(i=0;i<NC;i++)
if (strcmp(clients[i].procces,"��-������")==0)
		k++;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("����� ������� �� ������: %d",k);
getch();
}
//���������, ������������ ����������� ������� � ��������
void diagram(struct z *clients,int NC) //������� ���������
{
struct sp *nt; //���������� ��� ������ �� �������
int len,i,NColor; //i-��� ������ �� �������
long summa = 0 ; //�����-100%
char str1[20];
char str2[20];//����� ���������, ������� ���������� �������� ���� � ���� ���� �������
System::ConsoleColor Color; 
Console::ForegroundColor=ConsoleColor::DarkYellow; //���� ��������
Console::BackgroundColor=ConsoleColor::Black; // ���� ������� ����
Console::Clear();
for(i=0;i<NC;i++) 
	summa = summa+clients[i].sum;
if(!spisok)
	for(i=0;i<NC;i++)
		vstavka(clients,clients[i].name); //��������� �� ������ �������� ���� � ������ ������� � �����-���������� ����
Color=ConsoleColor::Black; NColor=0;
for(nt=spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
	sprintf(str1,"%s",nt->fio);
	sprintf(str2,"%3.1f%%",(nt->sum*100./summa));
	Console::ForegroundColor=ConsoleColor::DarkYellow;
	Console::BackgroundColor= ConsoleColor::Black;
	Console::CursorLeft=0; Console::CursorTop=i+1;
	printf(str1);
	Console::CursorLeft=20;
	printf("%s",str2);
	Console::BackgroundColor=++Color; NColor++;
	Console::CursorLeft=30;
	for(len=0; len<nt->sum*100/summa; len++) 
		printf(" ");
	if(NColor==14) //�������� �� ��������� 14 ������
		{ Color=ConsoleColor::Black; NColor=0; }
	}
_getch();
return ;
}
//������� ��� ������ �������� � ������������ �������� ������
void spiso(struct z* clients,int NC)
{
int i,k;
char temp[20];
struct z* nt;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf(" 1) ��-������ \n 2) �-�������� \n 3) ���������  \n 4) �������� \n 5) �������\n ������� �������:");
SetConsoleCP(1251); // ��� ���������� ������� �������� 
fgets(temp, sizeof(temp), stdin); //��������� ������ ����� 
SetConsoleCP(866); //��������� �������, ����� ������ �������� ������� �������
temp[strcspn(temp, "\n")] = '\0'; //��������� ����� �������, � ������� �� ���������� \n, ��������� \0 � ����� �������.
//�������� ����, ��� ��� ������������
if ((strcmp(temp,"��-������")==0)||(strcmp(temp,"�� ������")==0)||(strcmp(temp,"1")==0)) //����������, ��� ��� ������������ 
	strcpy(temp, "��-������"); //��������  � ���������� temp
else if ((strcmp(temp,"�-��������")==0)||(strcmp(temp,"� ��������")==0)||(strcmp(temp,"2")==0))
	strcpy(temp, "�-��������"); 
else if ((strcmp(temp,"���������")==0)||(strcmp(temp,"���������")==0)||(strcmp(temp,"3")==0))
    strcpy(temp, "���������"); 
else if ((strcmp(temp,"��������")==0)||(strcmp(temp,"��������")==0)||(strcmp(temp,"4")==0))
    strcpy(temp, "��������");
else if ((strcmp(temp,"�������")==0)||(strcmp(temp,"�������")==0)||(strcmp(temp,"5")==0))
    strcpy(temp, "�������");
else 	
	{
	Console::Clear();
	Console::ForegroundColor=ConsoleColor::DarkYellow;
	Console::BackgroundColor=ConsoleColor::Black;
	printf("\n\n\n���������� ��� ���");
	_getch();return;} //���� �� ������ ��������, ��������� � ����
Console::Clear();
SetConsoleCP(1251);
SetConsoleCP(866);
printf("\n ������ ������� : %s ",temp);
SetConsoleCP(866);
printf("\n =======================================================================");
for (i=0,nt=clients;i<NC;nt++,i++)
if (strcmp(nt->procces,temp)==0) //����������� ��������� ������ � ���������� temp
printf("\n | %s | %s - %s | %ld |", nt->name,clients[i].data,clients[i].procces,nt->ind); //����� ������ ��������
printf("\n =======================================================================\n"); 
_getch();
}
//������� ��� ������ ���������� �������� ��������,�� ������ ���� �������� �� ������
void odin(struct z* clients,int NC){
int k;
char temp[20];
Console::CursorLeft=0;
Console::BackgroundColor=ConsoleColor::Black;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::CursorTop=0;
Console::Clear();
printf("������� ���-�� ������ �������:");
SetConsoleCP(1251);
fgets(temp, sizeof(temp), stdin);
SetConsoleCP(866);
temp[strcspn(temp, "\n")] = '\0';
k=atoi(temp); //������� � ����� �����
Console::Clear();
if (k>5){
	Console::CursorLeft=0;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::ForegroundColor=ConsoleColor::DarkYellow;
	Console::CursorTop=0;
	Console::Clear();
	SetConsoleCP(1251);
	SetConsoleCP(866);
	printf("������� �����");
	SetConsoleCP(866);
	_getch();return;
	}
int i,j;
for (i=0;i<NC, k!=0 ;i++){
	for (j=i+1;j<NC;j++){
		if (strcmp(clients[i].data,clients[j].data)!=0){
			if (strcmp(clients[i].procces,clients[j].procces)==0){
				printf("\n�����: %s � %s.\n%s | %s , %s | %s.",clients[i].name,clients[j].name,clients[i].data,clients[i].procces,clients[j].data,clients[j].procces);//����� ������
				k=k-1;break;
			}
		}
		
	}
  }
_getch();
}
//������� �������� � ������ ������ 
void ret(struct z* clients,int NC){
Console::CursorLeft=0;
Console::BackgroundColor=ConsoleColor::Black;
Console::ForegroundColor=ConsoleColor::White;
Console::CursorTop=0;
Console::Clear();
int i;
for(i=0;i<NC;i++)
	printf("\n%-20s %-12s %10ld %-5s %ld",clients[i].name,clients[i].data,clients[i].ind,clients[i].procces,clients[i].sum);
_getch();
}

