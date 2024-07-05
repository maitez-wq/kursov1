#include "stdafx.h" //Подключение библиотек
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
#define ENTER 13 //Обозначение кнопок
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79
struct z{
	char name[20]; //ФИО клиента
	char data[20]; //Дата прибытия на склад
	long ind; //Индекс товара
	char procces[20]; //Состояние доставки
	long sum; //Прибыль с доставки
	};
struct sp {
	char fio[20];
	long sum;
	struct sp* sled; //Указатель на следующий элемент в списке
	struct sp* pred; //Указатель на предыдущий элемент в списке
	} *spisok; //Шаблон, глобальное описание структуры алфавитного списка
int menu(int); //Функция для меню, указание шаблонов используемых функций
void perv(struct z*, int);
void alfalist(struct z*,int);
void kolvo(struct z*,int);
void diagram(struct z*,int);
void spiso(struct z*,int);
void odin(struct z*,int);
void ret(struct z*,int);
int main(array<System::String ^> ^args)
{
//На локальном уровне осуществляем открытие файла,
//Считываем данные из файла в выделенную память
int i,n;
FILE *in;
struct z *clients;
int NC;
char BlankLine[]="                                                                ";//Пустая линия для создания меню
	setlocale(LC_CTYPE,"Russian");//Поддержка русского языка
	Console::CursorVisible::set(false); //Отключаем видимость курсора
	Console::BufferHeight=Console::WindowHeight; //Установка размера буфера по высоте
	Console::BufferWidth=Console::WindowWidth; //Установка размера буфера по ширине
	if((in=fopen("idea.dat","r"))==NULL) //Попытка открытия файла
		{
		printf("\nФайл idea.dat не открыт !");
		_getch(); exit(1);} //При неудачном открытия файла выводится сообщение “Файл idea.dat не открыт !”
fscanf(in,"%d",&NC);
clients=(struct z*)malloc(NC*sizeof(struct z)); //Выделяем память
for(i=0;i<NC;i++)//Считываем данные из списка
	fscanf(in,"%s%s%ld%s%ld",clients[i].name,clients[i].data, &clients[i].ind,clients[i].procces,&clients[i].sum);
for(i=0;i<NC;i++)
	printf("\n%-20s %-12s %10ld %-5s %ld",clients[i].name,clients[i].data,clients[i].ind,clients[i].procces,clients[i].sum); //Выводим данные из списка на экран
_getch();
char dan[8][65]={
				" Какой клиент первый вызвал доставку со склада.                 ",
				" Алфавитный список всех клиентов.                               ", 
				" Сколько товаров на складе.                                     ",
				" Список клиентов с определенным статусом товара.                ",
				" Одинаковые статусы доставки, но разные дни прибытия на складе. ",
				" Диаграмма. Процентное отношение прибыли с доставок             ",
				" Обратно к списку                                               ",
				" Выход.                                                         ",
};//Задание списка вопросов, пунктов меню
while(1){ // В цикле создаем область для вопросов  и окрашиваем её в цвета
//Устанавливаем для букв цвет и подсветку для выбранного вопроса

	Console::ForegroundColor=ConsoleColor::DarkYellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::DarkYellow;
	Console::CursorLeft=11; //Первая точка, откуда будем закрашивать область меню
	Console::CursorTop=4;
	printf(BlankLine);
	for (i=0;i<8;i++){ //Размещение вопросов
		Console::CursorLeft=11;
		Console::CursorTop=i+5;
		printf("%s",dan[i]);}
	Console::CursorLeft=11; //Последняя точка, где будет заканчиваеться выделенная область под меню
	Console::CursorTop=13;
	printf(BlankLine);
	n = menu(8); //Выбор вопроса в меню
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
	}//конец while(1) 
  return 0;
}// конец main()
int menu(int n) //n=9
{
	char dan[8][65]={
				" Какой клиент первый вызвал доставку со склада.                 ",
				" Алфавитный список всех клиентов.                               ", 
				" Сколько товаров на складе.                                     ",
				" Список клиентов с определенным статусом товара.                ",
				" Одинаковые статусы доставки, но разные дни прибытия на складе. ",
				" Диаграмма. Процентное отношение прибыли с доставок             ",
				" Обратно к списку                                               ",
				" Выход.                                                         ",
};//Задание списка вопросов, пунктов меню
int y1=0,y2=n-1; //Устанавливаем выеделение для строчки
char c=1;
while(c!=ESC) //При нажатие кнопки ESC, меню закроется
	{
	switch(c) { //Программирование кнопок вверх, вниз, вверх, ввод, END,HOME
		case DOWN: y2=y1; y1++; break;
		case UP: y2=y1; y1--; break;
		case ENTER: return y1+1;
		case END: y2=y1;y1=n-1;break;
		case HOME: y2=y1;y1=0;break;
	}
	if(y1>n-1){y2=n-1;y1=0;} //Условие когда срабатывает кнопка вниз
	if(y1<0) {y2=0;y1=n-1;} //Условие когда срабатывает кнопка вверх
	Console::ForegroundColor=ConsoleColor::White; //При выборе вопроса буквы окрашиваются в белый цвет
	Console::BackgroundColor=ConsoleColor::Red; //При выборе вопроса план за буквами подсвечивается красным
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::DarkYellow;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	} //Конец while(c!=ESC)
exit(0);
}

void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={"января","февраля","марта","апреля","мая","июня","июля","августа","сентября","октября","ноября","декабря"};//Месяцы в порядке числового исчисления
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return; //Функция возращает строку с текстовой датой 
}
//Функция поиска первого клиента заказавший доставку со склада
void perv(struct z* clients,int NC){
int i;
char s[30];
struct z* own=clients;
for (i=0;i<NC;i++)
	if (strcmp(clients[i].data,own->data)<0) //Поиск меньшей даты
		own=&clients[i];
	text_data(s,own->data);		
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Индекс самого \"первого\" товара %d ",own->ind);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Имеет клиент %s",own->name);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("Открыт %s ",s);
getch();
}
void vstavka(struct z* clients,char* fio) //Вставка в список
{
int i;
int NC=15;
struct sp *nov,*nt,*z=0;
for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled); //ищем места вставки
if(nt && strcmp(nt->fio,fio)==0) return; //проверка на повтор в случае повтора выход
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
//Сортировка всех клиентов по алфавиту, и обратный алфавит
void alfalist(struct z* clients,int NC){ //Формирование списка
int i;
struct sp *nt,*z;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf("\n Алфавитный список клиентов");
printf("\t\tОбратный алфавитный список");
printf("\n ===========================            ============================\n");
if(!spisok) //Формирование алфавитного списка
	for(i=0;i<NC;i++)
		vstavka(clients,clients[i].name);
	for (nt=spisok; nt!=0; nt=nt->sled) 
		printf("\n %-20s %ld ", nt->fio, nt->sum); //вывод алфавитного списка
	for(nt=spisok,z=0; nt!=0; z=nt,nt=nt->sled); {//Формирование обратного алфавитного списка
		Console::CursorTop=4;
	for(nt=z;nt!=0;nt=nt->pred)
	{
		Console::CursorLeft=40;
		printf("%-20s  %ld", nt->fio,nt->sum); //Вывод обратного алфавитного списка
		Console::CursorTop+=1;}
	}
_getch();
}

 //Функция для поиска товаров на складе
void kolvo(struct z	*clients,int NC)
{
int i,k=0;
for(i=0;i<NC;i++)
if (strcmp(clients[i].procces,"на-складе")==0)
		k++;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Всего товаров на складе: %d",k);
getch();
}
//Диаграмма, показывающая соотношение прибыли с доставок
void diagram(struct z *clients,int NC) //Создаем диаграмму
{
struct sp *nt; //переменная для работы со списком
int len,i,NColor; //i-для работы со списком
long summa = 0 ; //число-100%
char str1[20];
char str2[20];//Задаёт константы, которые определяют основной цвет и цвет фона консоли
System::ConsoleColor Color; 
Console::ForegroundColor=ConsoleColor::DarkYellow; //Цвет символов
Console::BackgroundColor=ConsoleColor::Black; // Цвет заднего фона
Console::Clear();
for(i=0;i<NC;i++) 
	summa = summa+clients[i].sum;
if(!spisok)
	for(i=0;i<NC;i++)
		vstavka(clients,clients[i].name); //Вставляем из списка названия имен и красим символы в темно-фиолетовый цвет
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
	if(NColor==14) //Выделяем на диаграмму 14 цветов
		{ Color=ConsoleColor::Black; NColor=0; }
	}
_getch();
return ;
}
//Функция для поиска килентов с определенным статусом товара
void spiso(struct z* clients,int NC)
{
int i,k;
char temp[20];
struct z* nt;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf(" 1) на-складе \n 2) в-процессе \n 3) доставлен  \n 4) отклонен \n 5) потерян\n Введите стаутус:");
SetConsoleCP(1251); // Для считывания русских символов 
fgets(temp, sizeof(temp), stdin); //вписываем нужный текст 
SetConsoleCP(866); //кодировка консоли, чтобы моглои выводить русские символы
temp[strcspn(temp, "\n")] = '\0'; //Возращает длину участка, в котором не содержится \n, добавляем \0 в конец массива.
//Проверка того, что ввёл пользователь
if ((strcmp(temp,"на-складе")==0)||(strcmp(temp,"на складе")==0)||(strcmp(temp,"1")==0)) //Сравниваем, что ввёл пользователь 
	strcpy(temp, "на-складе"); //Копируем  в переменную temp
else if ((strcmp(temp,"в-процессе")==0)||(strcmp(temp,"в процессе")==0)||(strcmp(temp,"2")==0))
	strcpy(temp, "в-процессе"); 
else if ((strcmp(temp,"доставлен")==0)||(strcmp(temp,"Доставлен")==0)||(strcmp(temp,"3")==0))
    strcpy(temp, "доставлен"); 
else if ((strcmp(temp,"отклонен")==0)||(strcmp(temp,"Отклонен")==0)||(strcmp(temp,"4")==0))
    strcpy(temp, "отклонен");
else if ((strcmp(temp,"Потерян")==0)||(strcmp(temp,"потерян")==0)||(strcmp(temp,"5")==0))
    strcpy(temp, "потерян");
else 	
	{
	Console::Clear();
	Console::ForegroundColor=ConsoleColor::DarkYellow;
	Console::BackgroundColor=ConsoleColor::Black;
	printf("\n\n\nПопробуйте ещё раз");
	_getch();return;} //Если не прошли проверки, возрашает в меню
Console::Clear();
SetConsoleCP(1251);
SetConsoleCP(866);
printf("\n Список товаров : %s ",temp);
SetConsoleCP(866);
printf("\n =======================================================================");
for (i=0,nt=clients;i<NC;nt++,i++)
if (strcmp(nt->procces,temp)==0) //Сравнивание состояние товара с переменной temp
printf("\n | %s | %s - %s | %ld |", nt->name,clients[i].data,clients[i].procces,nt->ind); //Вывод списка клиентов
printf("\n =======================================================================\n"); 
_getch();
}
//Функция для поиска одинаковых статусов доставки,но разных дней прибытия на складе
void odin(struct z* clients,int NC){
int k;
char temp[20];
Console::CursorLeft=0;
Console::BackgroundColor=ConsoleColor::Black;
Console::ForegroundColor=ConsoleColor::DarkYellow;
Console::CursorTop=0;
Console::Clear();
printf("Введите кол-во нужных ответов:");
SetConsoleCP(1251);
fgets(temp, sizeof(temp), stdin);
SetConsoleCP(866);
temp[strcspn(temp, "\n")] = '\0';
k=atoi(temp); //перевод в целое число
Console::Clear();
if (k>5){
	Console::CursorLeft=0;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::ForegroundColor=ConsoleColor::DarkYellow;
	Console::CursorTop=0;
	Console::Clear();
	SetConsoleCP(1251);
	SetConsoleCP(866);
	printf("Слишком много");
	SetConsoleCP(866);
	_getch();return;
	}
int i,j;
for (i=0;i<NC, k!=0 ;i++){
	for (j=i+1;j<NC;j++){
		if (strcmp(clients[i].data,clients[j].data)!=0){
			if (strcmp(clients[i].procces,clients[j].procces)==0){
				printf("\nОтвет: %s и %s.\n%s | %s , %s | %s.",clients[i].name,clients[j].name,clients[i].data,clients[i].procces,clients[j].data,clients[j].procces);//Вывод ответа
				k=k-1;break;
			}
		}
		
	}
  }
_getch();
}
//Функция возврата к выводу списка 
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

