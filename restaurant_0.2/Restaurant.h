#ifndef	RESTAURANT_H
#define  RESTAURANT_H
//���Ｘ��include��������ѧ�ĳ��õı�׼��ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
//����include�˱������е��Զ���ͷ�ļ�
#include "pwd.h"
#include "tablelist.h"
#include "menulist.h"
#include "orderlist.h"


void mainmenu();
void otherfunc();
int inputselect1();
int inputselect2();

void tablemgr();
void menumgr();
void accountmgr();
void addaccount(double money);

void order();
void calculate();
void seedishrank();
#endif

