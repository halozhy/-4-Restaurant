#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globel.h"

void inserttable(tableptr *sPtr, int id, int capacity, int state)//�����½ڵ�
{
    tableptr newPtr = malloc(sizeof(Table));//����ռ�

    if (newPtr != NULL)
    {
        newPtr->capacity = capacity;//��ֵ
        newPtr->id = id;//��ֵ
        newPtr->state = state;//��ֵ
        newPtr->next = NULL;//�Ȱ�next��ֵΪNULL

        tableptr previousPtr = NULL;
        tableptr currentPtr = *sPtr;

        while (currentPtr != NULL && capacity > currentPtr->capacity)//�ҵ�һ�����ʵ�λ�ã�����capacity��������Ļ���������orderʱ����λ
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }

        if (previousPtr == NULL)//�����ʵ�λ���������ͷʱ��previousPtrȷʵ����ڿգ������൱���������ͷ��
        {
            newPtr->next = *sPtr;
            *sPtr = newPtr;
        }
        else//�ҵ�����λ�õ����������ͷ
        {
            previousPtr->next = newPtr;
            newPtr->next = currentPtr;
        }
    }
    else
    {
        puts("�ڴ�����ʧ�ܣ�");
        system("pause");
    }
}

int deletetable (tableptr *sPtr, int value)//ɾ���ڵ㣬���ɹ�������0���������Ա�ռ�ã�����-1����û�ҵ�������-2
{
    if (value == (*sPtr)->id&&(*sPtr)->state==0)//�����һ���ڵ����Ҫ�ҵģ������ӿ���
    {
        tableptr tempPtr = *sPtr;
        *sPtr = (*sPtr)->next;
        free(tempPtr);
        return 0;
    }

    else if (value == (*sPtr)->id&&(*sPtr)->state!=0)//�����һ���ڵ����Ҫ�ҵģ�����������
    {
        return -1;
    }
    else
    {
        tableptr previousPtr = *sPtr;
        tableptr currentPtr = (*sPtr)->next;

        while (currentPtr != NULL && currentPtr->id != value)//����ң�ֱ���ҵ�Ϊֹ
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }

        if (currentPtr != NULL&&currentPtr->state==0)//�ҵ����ҿ���
        {
            tableptr tempPtr = currentPtr;
            previousPtr->next = currentPtr->next;
            free(tempPtr);
            return 0;
        }
        else if(currentPtr != NULL&&currentPtr->state!=0)//�ҵ�����������
        {
            return -1;
        }
    }

    return -2;
}

void writetable(tableptr head)
{
    //��������ǿյ�
    if (NULL==head)
    {
        //����w�򿪷�ʽ�����ʰ��ļ�д��
        FILE *fp;
        fp = fopen("table", "wb");
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
        FILE *fp;
        fp = fopen("table", "wb");
        if (fp == NULL)
        {
            puts("�ļ���ʧ��");
            system("pause");
            return;
        }
        else
        {
            while (head != NULL)//��������д���ļ�
            {
                fwrite(&head->id,sizeof(head->id),1,fp);
                fwrite(&head->capacity,sizeof(head->capacity),1,fp);
                fwrite(&head->state,sizeof(head->state),1,fp);
                head = head->next;
            }
            fclose(fp);
        }
    }
}


void delalltable(tableptr *head)          //��������ٲ���
{
    tableptr q;
    while(*head)//��ûɾ��Ļ�
    {
        q = (*head)->next;//�Ȱѵ�ǰͷ�ڵ����һ��������ʱ��q
        free(*head);//ɾ����ǰ��ͷ�ڵ�
        *head = q;//��q����*head
    }
}


