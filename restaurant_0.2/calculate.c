#include "Restaurant.h"
#include "globel.h"

void calculate()//��Ƭ��ʼ
{
    system("cls");
    printf("%s", "���������ţ�");

    int seetableid = inputselect2();//������
    if(seetableid == -1||seetableid==0)
    {
        puts("�������");
        system("pause");
        return;
    }

    int find = 0;//�����ʾorder�ļ������Ƿ��ҵ���tableidΪseetableid�Ĳˣ����ҵ����ᱻ��Ϊ1
    int printheadornot = 0;//������ͷֻ��Ҫ��ӡһ�ξ͹��ˣ������״̬��������headֻ��ӡһ��
    int dishnum = 0;
    double totalmoney = 0;//�������õ�

    orderptr orderhead = NULL;//����������ͷָ��

    {
        //���ļ�����order�ļ����ڴ�
        FILE *fp;
        fp = fopen("order", "rb");
        if(fp == NULL)
        {
            puts("���ļ�ʧ��");
            system("pause");
            return;
        }
        fseek(fp, 0, SEEK_END);
        long end = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        int temptid;
        int tempid;
        char tempname[22];
        float tempmoney;
        int temptimes;

        while (ftell(fp) < end)//������Ҫȫ�����룡������Ȼ�Ǳ߶���ߴ�ӡ
        {

            fread(&temptid, sizeof(int), 1, fp);//��һ��tableid
            if(seetableid == temptid)//�������Ҫ�ҵ�
            {
                dishnum++;//�˵�����+1
                find = 1;//��ʾȷʵ�ҵ���
            }
            if(printheadornot == 0 && find == 1)//�ҵ��ˣ����һ�û��ӡhead���Ǿʹ�ӡ
            {
                puts("");
                printf("%d�������˵����£�\n", temptid);
                puts("--------------------------------");
                puts("��� ����                 ����");
                puts("");
                printheadornot = 1;//��ӡ���ˣ�״̬������Ϊ1
            }
            fread(&tempid, sizeof(int), 1, fp);
            fread(tempname, sizeof(tempname), 1, fp);
            fread(&tempmoney, sizeof(float), 1, fp);
            fread(&temptimes, sizeof(int), 1, fp);

            if(seetableid == temptid) //�����Ҫ�ҵ�
            {
                printf("%-4d %-20s %.2f ��%d\n", tempid, tempname, tempmoney, temptimes);//�ʹ�ӡ������ϸ��Ϣ
                totalmoney = totalmoney + tempmoney * temptimes;//����=ԭ����+���ۡ�����
            }

            insertorder(&orderhead, temptid, tempid, tempname, tempmoney, temptimes);//���뵽��������
        }
        fclose(fp);
    }

    if(find == 0)//while�����ˣ���findΪ0���Ǿ���û���ҵ�
    {
        puts("������û��������ӵ���ϢŶ");
        system("pause");
        return;
    }
    else
    {
        printf("\n�������� %.2lf Ԫ\n", totalmoney);//�������
        puts("--------------------------------");
    }


    printf("%s", "\n���������ĸ��ֻ֧������Ŷ����");
    //���Ե�ʱ��double�͵���ֵһ����󣬾ͻ��о���������֣����һ��ǮҲ������ȡ������Ծ͸ɴ಻ŪС��������
    int pay = inputselect2();//�û����븶����
    if(pay == -1)
    {
        puts("�������");
        system("pause");
        return;
    }

    if((double)pay - totalmoney > 0)//���ﻹ��Ҫǿ��ת��һ�µ�
    {
        printf("����%.2lfԪ", (double)pay - totalmoney);
    }
    else if(totalmoney > (double)pay)//û����Ǯ���ǲ��е�Ŷ
    {
        puts("���������С�ڶ����ܼ�");
        system("pause");
        return;
    }

    puts("\nлл�ݹˣ���ӭ�´ι��٣�");
    addaccount(totalmoney);//д����ʷ��¼

    int i;
    for(i = 0; i < dishnum; i++)//ɾ������
    {
        deleteorder(&orderhead, seetableid);
    }


    {
        //�����ӵ�״̬
        FILE *fp;
        fp = fopen("table", "rb+");
        if(fp == NULL)
        {
            puts("�ļ���ʧ�ܣ�");
            system("pause");
            return;
        }
        fseek(fp, 0, SEEK_END);
        long end = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        int id;
        int state = 0;
        while(ftell(fp) < end)
        {
            fread(&id, sizeof(int), 1, fp);
            if(id == seetableid)
            {
                fseek(fp, 4, SEEK_CUR);
                fwrite(&state, sizeof(int), 1, fp);
                break;
            }
            else
            {
                fseek(fp, 8, SEEK_CUR);
            }
        }
        fclose(fp);
    }

    writeorder(orderhead);//���µ�����д���ļ�
    delallorder(&orderhead);//�ݻ������ͷſռ�

    system("pause");
}
