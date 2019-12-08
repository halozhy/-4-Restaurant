#include "Restaurant.h"
#include "globel.h"

typedef struct tempmenu//�����˵�ʱ����߰�menu�ļ�����Ķ�����������tempmenu���͵Ľṹ���������棬����������������ṹ������
{
    int tid;//�ڵ��֮ǰ���϶��Ѿ��õ������ţ��浽����
    int id;//��Ʒ���
    char name[22];//����
    float money;//����
    int times;//�ڱ�������Ĵ���
} TMENU;


void changetablestate_infile(int seeid)//��������״̬�ĺ������������������ӵ�id
{
    //���ļ�
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
    int state=1;
    while(ftell(fp)<end)
    {
        fread(&id,sizeof(int),1,fp);//�������ӵ�id
        if(id==seeid)//������ӵ�id����Ҫ�ҵ�
        {
            fseek(fp,4,SEEK_CUR);//����capacity
            fwrite(&state,sizeof(int),1,fp);//��״̬1д��ȥ
            break;
        }
        else//����������Ҫ�ҵ�����
        {
            fseek(fp,8,SEEK_CUR);//����capacity��state����
        }
    }
    fclose(fp);//�����ļ��͹ر�


}

void addorder_and_printdishes(TMENU *tmenu,int menunumber)
//������д���ļ��ﲢ��ӡ������Ϣ������ĵ�һ��������tempmenu���͵�����ĵ�ַ���ڶ����ǲ˵�����
{
    //��order�ļ�
    FILE *fp;
    fp = fopen("order", "ab");//��д�ͺ�
    if(fp == NULL)
    {
        puts("���ļ�ʧ�ܣ�");
        system("pause");
        return;
    }
    //��menu�ļ�
    FILE *fpmenu;
    fpmenu=fopen("menu","rb+");//�򿪷�ʽΪ�ɶ���д
    if(fp == NULL)
    {
        puts("���ļ�ʧ�ܣ�");
        system("pause");
        return;
    }

    puts("\n��Ķ������£�");
    puts("--------------------------------");
    puts("��� ����                 ����");

    double totalmoney=0;//�������õ�
    int i,j;
    int mid,otimes;//���������Ƕ�menuʱ�����ʱ������mid������˵�id��otimes(originaltimes)�����������ԭ���ı������
    for(i=0; i<menunumber; i++)//��tmenu�����������Բ���
    {
        if(tmenu[i].times!=0)//˵������˿��˵���
        {
            //�Ѹ�����Ϣд���ļ�
            fwrite(&tmenu[i].tid, sizeof(int), 1, fp);
            fwrite(&tmenu[i].id, sizeof(int), 1, fp);
            fwrite(tmenu[i].name, sizeof(tmenu[i].name), 1, fp);
            fwrite(&tmenu[i].money, sizeof(float), 1, fp);
            fwrite(&tmenu[i].times, sizeof(int), 1, fp);
            printf("%-4d %-20s %.2f ��%d\n",tmenu[i].id, tmenu[i].name, tmenu[i].money,tmenu[i].times);//��ӡ��������˵���Ϣ
            totalmoney=totalmoney+tmenu[i].money*tmenu[i].times;//�ܼ�=ԭ�ܼ�+����˵ĵ��ۡ�������ڱ�������Ĵ���
            //����������Ʒ��times++
            fseek(fpmenu,0,SEEK_SET);//�ȰѶ�д�ļ��ġ���ͷ������ԭλ
            for(j=0; j<menunumber; j++)//�ڲ˵��ļ��������Բ���
            {
                fread(&mid,sizeof(int),1,fpmenu);//��������˵�id
                if(mid==tmenu[i].id)//���������˵�id��ͬ���Ǿ�������Ҫ�ҵ�
                {
                    fseek(fpmenu,22,SEEK_CUR);//����22�ֽڣ�����name����
                    fread(&otimes,sizeof(int),1,fpmenu);//�ȶ�һ��ԭ����ֵ
                    fseek(fpmenu,-4,SEEK_CUR);//ǰ��4�ֽڣ�׼��д��
                    otimes=otimes+tmenu[i].times;
                    fwrite(&otimes,sizeof(int),1,fpmenu);//д���µ�ֵ
                    break;
                }
                else
                {
                    fseek(fpmenu,30,SEEK_CUR);//һ�������ļ��еĳ�����34���Ѿ�����4λ�ˣ��������30λ�͵�����һ��
                }
            }
        }
    }
    fclose(fp);
    fclose(fpmenu);
    puts("--------------------------------");
    printf("�����ɣ�����%.2lfԪ\n", totalmoney);
    //delalldish(&dishhead);
}


int checkmenu()//���table�ļ��Ƿ�Ϊ�գ������ʧ�ܣ�����-1�����Ϊ�գ�����0
{
    FILE *fp;
    fp = fopen("menu", "rb");
    if(fp == NULL)
    {
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(end == 0)
    {
        fclose(fp);
        return 0;
    }
    else
    {
        fclose(fp);
        return 1;
    }
}

int inputselect2()//������������������룬�Ƿ����뷵��-1�����򷵻������
{
    char in[11];
    scanf("%9s", in);//int���Ϊ2147483647����ʮλ�������Ծͽ�����������Ƕ೤���ַ����ض�Ϊ����Ϊ9�ģ�������������10��9���ͳ���int�����ֵ��
    fflush(stdin);
    int i;
    for(i = 0; i < strlen(in); i++)//���ַ�������һ�����ң���������в������ֵ��ַ�������-1
    {
        if(in[i] < 48 || in[i] > 57)
        {
            return -1;
        }
    }

    return atoi(in);//��������ļ�飬Ӧ�þ��Ǹ����ˣ���atoi���ַ���ת������
}

int inputselect4()//inputselect2�ķ��棬ֻ��������������0
{
    char in[11];
    scanf("%9s", in);
    fflush(stdin);
    int i;
    for(i = 0; i < strlen(in); i++)
    {
        if(in[i] < 49 || in[i] > 57)
        {
            return -1;
        }
    }

    return atoi(in);
}


int checktable()//���table�ļ��Ƿ�Ϊ�գ������ʧ�ܣ�����-1�����Ϊ�գ�����0
{
    FILE *fp;
    fp = fopen("table", "rb");
    if(fp == NULL)
    {
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if(end == 0)
    {
        fclose(fp);
        return 0;
    }
    else
    {
        fclose(fp);
        return 1;
    }
}


void order()//��Ƭ��ʼ
{

    system("cls");

    int tableid = 0;//֮��������õ�
    //������ӺͲ˵��ļ�
    int tablestate = checktable();
    int menustate = checkmenu();

    if(tablestate == -1 || menustate == -1)
    {
        puts("���ļ�ʧ�ܣ�");
        system("pause");
        return;
    }
    else if(tablestate == 0 && menustate == 1)
    {
        puts("�������滹û������");
        system("pause");
        return;
    }
    else if(tablestate == 1 && menustate == 0)
    {
        puts("�˵����ǿյ�");
        system("pause");
        return;
    }
    else if(tablestate == 0 && menustate == 0)
    {
        puts("��������û�������Ҳ˵�Ϊ��");
        system("pause");
        return;
    }
    else
    {
        printf("%s", "����������������");
        int peoplenum = inputselect4();//������������
        if(peoplenum==-1)
        {
            puts("�������");
            system("pause");
            return;
        }
        puts("");
        int i;
        int find = 0;//findһ��ʼΪ0���ҵ�����֮����1
        //��ȡ���ӣ������������ʵ����Ӿ�break��һ����ͳɹ���֮��Ҫ�����ӵ�״̬�����޸�
        //���ļ������ļ����ڴ�
        FILE *fp;
        fp = fopen("table", "rb");
        if(fp == NULL)
        {
            puts("�ļ���ʧ�ܣ�");
            system("pause");
            return;
        }
        fseek(fp,0,SEEK_END);
        long end=ftell(fp);
        fseek(fp,0,SEEK_SET);
        int temp[3];//��Ϊ�����ļ����涼��int�͵ģ������������鵱����ʱ������
        while (ftell(fp)<end)
        {
            fread(&temp[0],sizeof(int),1,fp);
            fread(&temp[1],sizeof(int),1,fp);
            fread(&temp[2],sizeof(int),1,fp);
            if(temp[2]==0&&temp[1]>=peoplenum&&find==0)
            {
                find=1;
                tableid=temp[0];//��tableid��ֵ
                printf("�뵽%d��������\n", tableid);
                break;
            }
        }
        fclose(fp);

        if(find == 0)
        {
            puts("���ڿ����ˡ����´������ɣ�");
            system("pause");
            return;
        }

        puts("\n------------����˵�------------\n");
        puts("��� ����                 ����");

        //��menu�ļ������ļ����ڴ�
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
        end = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        int menunumber=end/34;//ÿ����ռ��34���ֽڣ��������ļ��ܳ���34���ܵõ��˵ĸ�����
        TMENU tmenu[menunumber];//�����齨����

        i=0;
        while (ftell(fp) < end)//�ⲿ�֣����ļ���д������
        {
            fread(&tempid, sizeof(tempid), 1, fp);
            fread(tempchar, sizeof(tempchar), 1, fp);
            fread(&temptimes, sizeof(temptimes), 1, fp);
            fread(&money, sizeof(money), 1, fp);

            tmenu[i].tid=tableid;
            tmenu[i].id=tempid;
            strcpy(tmenu[i].name,tempchar);
            tmenu[i].money=money;
            tmenu[i].times=0;
            printf("%-4d %-20s %.2lf\n", tempid, tempchar, money);//��д�����飬�ߴ�ӡ������������˲˵��Ĵ�ӡ���ִ������ڴ�
            i++;
        }
        fclose(fp);


        puts("\n--------------------------------\n");
        int orderornot = 0;//orderornot���û��Ƿ��˵�״̬
        while(1)
        {
            printf("%s", "�������Ʒ�ı�ţ�����0�Խ�����");
            int input;
            input = inputselect2();//inputselect2�������

            if(input == 0 && orderornot == 1)//��˽���
            {
                addorder_and_printdishes(tmenu,menunumber);//��order�ļ�д�벢��ӡ����������Ϣ
                changetablestate_infile(tableid);//�����ӵ�״̬

                system("pause");
                return;
            }
            else if(input == 0 && orderornot == 0) //û��ˡ���
            {
                puts("δ��ͣ�����������һ���˵�");
                Sleep(1000);
                return;
            }
            else if(input == -1)
            {
                puts("�������");
            }
            else
            {
                find = 0;
                for(i=0; i<menunumber; i++)//�ڲ˵���������û�������
                {
                    if(input == tmenu[i].id)
                    {
                        tmenu[i].times++;//�ҵ��ˣ��͸������ı������+1
                        find = 1;
                        if(orderornot == 0)
                        {
                            orderornot = 1;//��ʾȷʵ�������
                        }
                        break;
                    }
                }
                if(find == 0)
                {
                    puts("�ƺ�û��������أ�");
                }
            }
        }
    }
}
