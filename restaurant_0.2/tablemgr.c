#include "Restaurant.h"
#include "globel.h"


int getnewtableid(tableptr currentPtr, int tablenumber) //�����ܡ����һ������id
//����˵���ڵ�����idΪ��1 2 3 5 6�����������᷵��4
{
    if (NULL == currentPtr)
    {
        return 1;//�����û�����ӵĻ�����Ȼ��1��
    }
    else
    {
        if(tablenumber == 0)//���Ƕ�����֤���û�����Ӱ�
            return 1;
        int n[tablenumber];//��������
        int i = 0;
        int ok;
        while (currentPtr != NULL)//��������������id�ȴ�����
        {
            n[i] = currentPtr->id;
            i++;
            currentPtr = currentPtr->next;
        }
        int biggest = n[0];//�����1����id���
        for(i = 0; i < tablenumber ; i++)
        {
            if(n[i] > biggest)//�������ֵ
            {
                biggest = n[i];
            }
        }
        int find = 1;
        while(biggest != find)
        {
            ok = 0;//״ֵ̬��0
            for(i = 0; i < tablenumber ; i++)//��id����������
            {
                if(n[i] == find)//������˺͵�ǰ��find��ȵģ�������
                {
                    ok = 1;//�ı�״ֵ̬
                }
            }
            if(ok == 0)//˵�����find��id�ﲻ����
                return find;//��������������Ӻ��ʵ�id��
            else
                find++;//������ڣ���++��Ȼ�������
        }
        return biggest + 1;

    }
}


void seetable()//ֱ�Ӵ��ļ�����벢��ӡ
{
    int tablenumber = 0;
    {
        //���ļ������ļ�����ӡ
        FILE *fp;
        fp = fopen("table", "rb");
        if(fp == NULL)
        {
            puts("�ļ���ʧ�ܣ�");
            system("pause");
            return;
        }
        int tempid, tempcap, tempstate;

        fseek(fp, 0, SEEK_END);
        long end = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        if(end == 0)
        {
            puts("\nһ�����Ӷ�û����\n");
            fclose(fp);
            return;
        }
        int num = end / 12;//ÿ�����ӵ��ֽ���Ϊ12���ǾͿ��������Ҫ�����ٴ�
        int i = 0;
        while (i < num)
        {
            fread(&tempid, sizeof(int), 1, fp);
            fread(&tempcap, sizeof(int), 1, fp);
            fread(&tempstate, sizeof(int), 1, fp);
            printf("��ţ�%5d ������%5d   ", tempid, tempcap);
            if(tempstate == 1)
                printf("%s", "״̬���п�\n");
            else
                printf("%s", "״̬���޿�\n");
            tablenumber++;
            i++;
        }
        fclose(fp);


    }
    printf("\n����%d������\n", tablenumber);
}


int readtabletomem(tableptr *tablehead)//���ļ���ȡ������Ϣ�������������������ӵĸ���
{
    int tablenumber = 0;
    {
        //���ļ������ļ����ڴ�
        FILE *fp;
        fp = fopen("table", "rb");
        if(fp == NULL)
        {
            puts("�ļ���ʧ�ܣ�");
            system("pause");
            return 0;
        }
        int temp[3];

        fseek(fp, 0, SEEK_END);
        long end = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        if(end == 0)
        {
            return 0;
        }
        while (ftell(fp) < end)
        {
            fread(&temp[0], sizeof(int), 1, fp);
            fread(&temp[1], sizeof(int), 1, fp);
            fread(&temp[2], sizeof(int), 1, fp);
            inserttable(&*tablehead, temp[0], temp[1], temp[2]);
            //printf("��ţ�%d ������%d   ״̬��%d\n", temp[0], temp[1], temp[2]);
            tablenumber++;
        }
        //puts("NULL");
        fclose(fp);
    }
    return tablenumber;
}


void addtable()//�������
{
    tableptr tablehead = NULL;
    int tablenumber = readtabletomem(&tablehead);//�����ڴ�
    printf("\n%s", "�����������ӵ�������");
    char in[11];
    scanf("%9s", in);
    int i;
    for(i = 0; i < strlen(in); i++)
    {
        if(in[0] < 49 || in[0] > 57)
        {
            system("cls");
            puts("��������");
            return;
        }
    }


    int cap = atoi(in);

    inserttable(&tablehead, getnewtableid(tablehead, tablenumber), cap, 0); //�������������������
    writetable(tablehead);//���ڴ�д���ļ�
    delalltable(&tablehead);//�ݻ������ͷſռ�
    system("cls");
}
void deltable()//ɾ������
{
    tableptr tablehead = NULL;
    readtabletomem(&tablehead);//���ļ������ڴ�
    if (tablehead != NULL)
    {
        printf("\n%s", "������Ҫɾ�������ӵı�ţ�");

        int delid = inputselect2();
        if(delid == -1)
        {
            puts("�������");
            system("pause");
            return;
        }
        int s = deletetable(&tablehead, delid);//ɾ���ڵ㣬���ɹ�������0���������Ա�ռ�ã�����-1����û�ҵ�������-2
        if (s == 0)
        {
            system("cls");
            printf("%d�������Ѿ�ɾ��\n", delid);


            writetable(tablehead);//���ڴ�д���ļ�
            delalltable(&tablehead);//�ݻ������ͷſռ�
            return;
        }
        else if(s == -1)
        {
            system("cls");
            puts("�����Ա�ռ�ã��޷�ɾ��");
            delalltable(&tablehead);//�ݻ������ͷſռ�
            return;
        }
        else if(s == -2)
        {
            system("cls");
            puts("�ƺ�û����������");
            delalltable(&tablehead);//�ݻ������ͷſռ�
            return;
        }


    }
    else
    {
        system("cls");
        puts("һ�����ӻ�û����");
        delalltable(&tablehead);//�ݻ������ͷſռ�
        return;
    }

}


void tablemgr()
{
    while (1)
    {
        puts("");
        puts("-------------------");
        puts("Ŀǰ�Ĳ������Ϊ��");
        seetable();
        puts("-------------------");
        puts("������");
        puts("1.��Ӳ���");
        puts("2.ɾ������");
        puts("3.������һ��");
        puts("-------------------");
        printf("\n%s", "��ѡ�����谴�س�����");
        switch(inputselect1(3))
        {
        case 1:
            addtable();
            break;
        case 2:
            deltable();
            break;
        case 3:
            return;
        case -1:
            system("cls");
            puts("�����������������!");
            break;
        default:
            break;
        }
    }
}
