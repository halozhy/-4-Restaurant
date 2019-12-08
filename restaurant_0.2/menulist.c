#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globel.h"

//����menulist��tablelist�ǳ����ƣ����ԾͲ���дע����
void insertmenu(menuptr *sPtr, int id, char name[], int times, float money)
{
    menuptr newPtr = malloc(sizeof(Menu));

    if (newPtr != NULL)
    {
        strcpy(newPtr->name, name);
        newPtr->id = id;
        newPtr->times = times;
        newPtr->money = money;
        newPtr->next = NULL;

        menuptr previousPtr = NULL;
        menuptr currentPtr = *sPtr;

        while (currentPtr != NULL && id > currentPtr->id)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }

        if (previousPtr == NULL)
        {
            newPtr->next = *sPtr;
            *sPtr = newPtr;
        }
        else
        {
            previousPtr->next = newPtr;
            newPtr->next = currentPtr;
        }
    }
    else
    {
        puts("�ڴ�����ʧ�ܣ�");
    }
}


int deletemenu (menuptr *sPtr, int value)//�����Ϊ�ˣ�ɾ���ɹ����ز�Ʒid��û�ҵ��򷵻�0
{
    if (value == (*sPtr)->id)
    {
        menuptr tempPtr = *sPtr;
        *sPtr = (*sPtr)->next;
        free(tempPtr);
        return value;
    }
    else
    {
        menuptr previousPtr = *sPtr;
        menuptr currentPtr = (*sPtr)->next;

        while (currentPtr != NULL && currentPtr->id != value)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        if (currentPtr != NULL)
        {
            menuptr tempPtr = currentPtr;
            previousPtr->next = currentPtr->next;
            free(tempPtr);
            return value;
        }
    }
    return 0;
}



void writemenu(menuptr head)
{
    if (NULL == head)
    {
        //����w�򿪷�ʽ�����ʰ��ļ�д��
        FILE *fp;
        fp = fopen("menu", "wb");
        if (fp == NULL)
        {
            puts("�ļ���ʧ��");
            system("pause");
            return;
        }
        else
        {
            fclose(fp);
        }
    }
    else
    {
        int num=0;
        FILE *fp;
        fp = fopen("menu", "wb");
        if (fp == NULL)
        {
            puts("�ļ���ʧ��");
            system("pause");
            return;
        }
        else
        {
            while (head != NULL)
            {
                fwrite(&head->id, sizeof(head->id), 1, fp);
                fwrite(head->name, sizeof(head->name), 1, fp);
                fwrite(&head->times, sizeof(head->times), 1, fp);
                fwrite(&head->money, sizeof(head->money), 1, fp);
                num++;
                head = head->next;
            }
            fclose(fp);
        }
    }
}


void delallmenu(menuptr *head)          //��������ٲ���
{
    menuptr q;
    while(*head)
    {
        q = (*head)->next;
        free(*head);
        *head = q;
    }

}



