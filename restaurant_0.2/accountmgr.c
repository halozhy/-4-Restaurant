#include "Restaurant.h"

void addaccount(double money)//��account�ļ���׷д��ʷ��¼���������˵�ֵ
{
    //�ⲿ���ǻ�ȡʱ�䣬����ʱ��ת���ַ���
    time_t rawtime;
    struct tm *timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    char *timec = asctime(timeinfo);

    //���ļ�
    FILE *fp;
    fp = fopen("account", "a");//׷д�Ϳ�
    if(fp == NULL)
    {
        puts("�ļ���ʧ��");
        system("pause");
        return;
    }
    else
    {
        fprintf(fp, "%lf ", money);//����д���ļ�
        fprintf(fp, "%s\n", timec);//ʱ��д���ļ�
    }
    fclose(fp);
    puts("\n��д����Ŀ��ʷ");
}

void readfromfileaccount()//��account�ļ������ȡ��ʷ��¼����ӡ
{
    FILE *fp;
    fp = fopen("account", "r");
    if(fp == NULL)
    {
        puts("�ļ���ʧ��");
        system("pause");
        return;
    }
    else
    {
        double money = 0;
        char timec[30];
        memset(timec, 0, sizeof(timec));
        while(fscanf(fp, "%lf", &money) != EOF)//�߶��ߴ�ӡ
        {
            fscanf(fp, "%[^\n]", timec);
            printf("%.2lf ", money);
            printf("%s\n\n", timec);
        }
        if(money == 0)
        {
            puts("��Ŀ���ǿյġ���");
        }

    }
    fclose(fp);
}

void accountmgr()
{
    puts("");
    puts("��Ŀ���£�");
    puts("-------------------");
    readfromfileaccount();
    puts("-------------------");
    puts("");
    system("pause");
}



