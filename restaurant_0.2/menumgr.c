#include "Restaurant.h"
#include "globel.h"

float inputselect3()//���С�����룬֧��5Ϊ������2λС��
{
    char in[14];
    scanf("%13s", in);
    fflush(stdin);
    if(strlen(in) > 8)//12345.67Ϊ8λ�����Գ��ȴ���8��ֱ��pass
        return -1;
    int i;
    int isfloat = 0;//�ж��Ƿ�λС����״̬����
    int floatpos = -1;//�����С�������ַ������λ��
    for(i = 0; i < strlen(in); i++)
    {
        if(in[i] == '.' && floatpos == -1) //����ҵ�С���㣬���ǵ�һ���ҵ�
        {
            isfloat = 1;//�Ǹ�С��
            floatpos = i;//�ڵ�iλ��С����
            continue;
        }
        else if(in[i] == '.' && floatpos != -1) //����ҵ�С���㣬�����ǵ�һ���ҵ�
        {
            return -1;//����1.123.12����������Ӧ�ǲ��Ϸ���
        }
        else if(in[i] < 48 || in[i] > 57)//���ڲ�������Ҳ����С������ַ�
        {
            return -1;
        }
    }

    //����12.3456�����ĵ����룬�ܹ���������м�飬������ָ���ѵ���λС����֮���С��ȥ��
    if(strlen(in) - floatpos > 3 && isfloat == 1) //��С������С�����λ�ú��ַ�����β��λ�ó�����3��˵��С��λ������
    {
        for(i = strlen(in) - 1; strlen(in) - 1 - floatpos > 2; i--)//�ѳ��˵Ķ�����'\0'
        {
            in[i] = '\0';
        }
    }

    if(isfloat == 0)//�������һϵ���жϣ�������С��
    {
        return (float)atoi(in);//ǿתһ�²�return
    }
    else
    {
        float out;
        sscanf(in, "%f", &out);//sscanf���԰�ĳ���ַ��������������ٴν��и�ʽ������
        return out;
    }
}


int getnewmenuid(menuptr currentPtr, int menunumber)//��ͬgetnewtableid����ע�����Ʋ�tablemgr.c
{
    if (NULL == currentPtr)
    {
        return 1;
    }
    else
    {
        if(menunumber == 0)
            return 1;
        int n[menunumber];
        int i = 0;
        int ok;
        while (currentPtr != NULL)
        {
            n[i] = currentPtr->id;
            i++;
            if(i > menunumber)
                break;
            currentPtr = currentPtr->next;
        }
        int biggest = n[0];
        for(i = 0; i < menunumber; i++)
        {

            if(n[i] > biggest)
            {
                biggest = n[i];
            }
        }
        int find = 1;
        while(biggest != find)
        {
            ok = 0;
            for(i = 0; i < menunumber ; i++)
            {
                if(n[i] == find)
                {
                    ok = 1;
                }
            }
            if(ok == 0)
                return find;
            find++;
        }
        return biggest + 1;

    }
}

//ʣ�µĲ��ֺ�tablemgr�ǳ����ƣ����ԾͲ���дע����
void seemenu()
{
    int menunumber = 0;

    //���ļ������ļ����ڴ�
    FILE *fp;
    fp = fopen("menu", "rb");
    if(fp == NULL)
    {
        puts("���ļ�ʧ�ܣ�");
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
        puts("\nһ���˶�û����\n");
        fclose(fp);
        return;
    }
    puts("");
    while (ftell(fp) < end)
    {
        fread(&tempid, sizeof(tempid), 1, fp);
        fread(tempchar, sizeof(tempchar), 1, fp);
        fread(&temptimes, sizeof(temptimes), 1, fp);
        fread(&money, sizeof(money), 1, fp);

        printf("��ţ�%3d   ������%-22s  ���ۣ�%.2f  �������: %3d \n", tempid, tempchar, money, temptimes);
        menunumber++;
    }

    printf("\n����%d����\n", menunumber);
    fclose(fp);
}

int readmenutomem(menuptr *menuhead)
{
    int menunumber = 0;

    //���ļ������ļ����ڴ�
    FILE *fp;
    fp = fopen("menu", "rb");
    if(fp == NULL)
    {
        puts("�ļ���ʧ�ܣ�");
        system("pause");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(end == 0)
    {
        return 0;
    }

    int tempid = 0;
    char tempchar[22];
    memset(tempchar, 0, sizeof(tempchar));
    int temptimes = 0;
    float money = 0;

    while (ftell(fp) < end)
    {
        fread(&tempid, sizeof(tempid), 1, fp);
        fread(tempchar, sizeof(tempchar), 1, fp);
        fread(&temptimes, sizeof(temptimes), 1, fp);
        fread(&money, sizeof(money), 1, fp);

        insertmenu(&*menuhead, tempid, tempchar, temptimes, money);
        menunumber++;

    }

    fclose(fp);

    return menunumber;

}
void addmenu()
{
    menuptr menuhead = NULL;
    int menunumber = readmenutomem(&menuhead);
    printf("\n%s", "�������²�Ʒ�����֣����10�����֣���");
    char in[22];
    scanf("%20s", in);
    fflush(stdin);

    float money;
    printf("\n%s", "�������²�Ʒ�ļ۸�֧��5λ������2λС������");
    money = inputselect3();
    if(money == -1)
    {
        system("cls");
        puts("�������");
        return;
    }

    insertmenu(&menuhead, getnewmenuid(menuhead, menunumber), in, 0, money); // insert item in list

    writemenu(menuhead);//���ڴ�д���ļ�
    system("cls");
    delallmenu(&menuhead);
}
void delmenu()
{
    menuptr menuhead = NULL;
    readmenutomem(&menuhead);
    if (menuhead != NULL)
    {
        printf("\n%s", "������Ҫɾ���Ĳ�Ʒ�ı�ţ�");
        int delid = inputselect4();
        if(delid == -1)
        {
            puts("�������");
            system("pause");
            return;
        }
        if (deletemenu(&menuhead, delid))
        {

            system("cls");
            printf("%d�Ų�Ʒ�Ѿ�ɾ��\n", delid);
            writemenu(menuhead);
            delallmenu(&menuhead);
            return;
        }
        else
        {
            system("cls");
            puts("�ƺ�û�������Ŷ");
            delallmenu(&menuhead);
            return;
        }
    }
    else
    {
        system("cls");
        puts("һ���˶�û����");
        delallmenu(&menuhead);//�ݻ������ͷſռ�
        return;
    }

}
void menumgr()
{
    while (1)
    {
        puts("");
        puts("-------------------");
        puts("Ŀǰ�Ĳ˵����Ϊ��");
        seemenu();
        puts("-------------------");
        puts("������");
        puts("1.��Ӳ�Ʒ");
        puts("2.ɾ����Ʒ");
        puts("3.������һ��");
        puts("-------------------");
        printf("\n%s", "��ѡ�����谴�س�����");
        switch(inputselect1(3))
        {
        case 1:
            addmenu();
            break;
        case 2:
            delmenu();
            break;
        case 3:
            return;
        case -1:
            system("cls");
            puts("\n�����������������!");
            break;
        default:
            break;
        }
    }
}
