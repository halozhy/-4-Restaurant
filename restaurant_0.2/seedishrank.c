#include "Restaurant.h"
#include "globel.h"


typedef struct dish2
{
    int id;
    char name[22];
    int times;
    float money;

} DISH;
//֮��Ҫ����ʲô�ģ���ðѲ�Ʒ�����������档���Զ�����һ����ʱ�Ľṹ������dish2������ṹ������û��������Ŷ

int cmp(const void *p1, const void *p2)
//��stdlib.h�����qsort��������Ҫ������������Ƚϵĺ���
//�������ֵС�� 0��< 0������ô p1 ��ָ��Ԫ�ػᱻ����p2��ָ��Ԫ�ص�ǰ��
//�������ֵ���� 0��= 0������ô p1 ��ָ��Ԫ���� p2 ��ָ��Ԫ�ص�˳��ȷ��
//�������ֵ���� 0��> 0������ô p1 ��ָ��Ԫ�ػᱻ���� p2 ��ָ��Ԫ�صĺ���
{
    DISH *a = (DISH*)p1;
    DISH *b = (DISH*)p2;
    if(a->times > b->times)
        return -1;
    else if(a->times < b->times)//����Ϊ�˽������򣬵�p1<p2ʱ���ͷ���1��p2��������p1ǰ����
        return 1;
    else
        return 0;
}

void seedishrank()//��Ƭ��ʼ
{
    system("cls");
    puts("�˵��ܻ�ӭ�̶����£���\"*\"��������1�Σ�\"#\"��������50�Σ�");
    puts("--------------------------------");
    int menunumber = 0;

    //���ļ������ļ����ڴ�
    FILE *fp;
    fp = fopen("menu", "rb");
    if(fp == NULL)
    {
        puts("�ļ���ʧ��");
        system("pause");
        return;
    }
    int tempid = 0;
    char tempchar[22];
    memset(tempchar, 0, sizeof(tempchar));
    int temptimes = 0;
    float money = 0;

    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(end == 0)
    {
        puts("\n�˵����ǿյ�\n");
        system("pause");
        return;
    }

    int lenofonrdish = 34;
    menunumber = end / lenofonrdish; //��TM���Ǵ����������������ļ��ĺô�������ֱ�Ӿ�֪��menu�ļ�������˶��ٵ�����
    printf("����%d����\n\n", menunumber);

    DISH dish[menunumber];//����������

    int i = 0;
    int j = 0;
    while (ftell(fp) < end)
    {
        fread(&tempid, sizeof(tempid), 1, fp);
        fread(tempchar, sizeof(tempchar), 1, fp);
        fread(&temptimes, sizeof(temptimes), 1, fp);
        fread(&money, sizeof(money), 1, fp);

        //������Ķ���д������
        dish[i].id = tempid;
        strcpy(dish[i].name, tempchar);
        dish[i].times = temptimes;
        dish[i].money = money;

        //˳��ʹ�ӡ����
        printf("%d.%-20s %4d  ", dish[i].id, dish[i].name, dish[i].times);
        if(dish[i].times > 50)
        {
            printf("%s", "  ");
            int t = dish[i].times / 50;//tΪ#����
            int remain = dish[i].times - t * 50;//remainΪ*����
            for(j = 0; j < t; j++)
            {
                printf("%s", "#");

            }
            for(j = 0; j < remain; j++)
            {
                printf("%s", "*");

            }
            puts("");
            i++;
        }
        else
        {
            printf("%s", "  ");
            for(j = 0; j < dish[i].times; j++)
            {
                printf("%s", "*");
            }
            puts("");
            i++;
        }

    }
    fclose(fp);

    qsort(dish, menunumber, sizeof(DISH), cmp);//����

    puts("--------------------------------");

    if(menunumber <= 4)//����˵���ĿС�ڵ���4���Ͳ��ܴ�ӡ��ǰ4���ˡ��ˣ������ֵ�
    {
        printf("\n�Ƚ��ܻ�ӭ��%d�������£�\n", menunumber);
        puts("--------------------------------");
        for(i = 0; i < menunumber; i++)
        {
            printf("%d.%-20s \n", dish[i].id, dish[i].name);
        }
        puts("--------------------------------");
    }
    else
    {
        puts("\n�Ƚ��ܻ�ӭ��ǰ4�������£�");
        puts("--------------------------------");
        int i;
        for(i = 0; i < 4; i++)
        {
            printf("%d.%-20s \n", dish[i].id, dish[i].name);
        }
        puts("--------------------------------");
    }

    puts("");

    system("pause");
}
