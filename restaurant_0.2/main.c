#include "Restaurant.h"
void mainmenu()
{
    while (1)
    {
        puts("*****************************");
        puts("    ��ӭ�����������ϵͳ");
        puts("*****************************");
        puts("");
        puts("-------------------");
        puts("1.���");
        puts("2.�ͻ�����");
        puts("3.�͹�ͳ��");
        puts("4.��������");
        puts("5.�˳�");
        puts("-------------------");
        printf("\n%s", "��ѡ�����谴�س�����");
        switch (inputselect1(5))//inputselect��������Ϸ��жϣ����ص��������ֵ�����Ƿ����룬�򷵻�-1�������һ��int���͵ı����ǲ˵������ѡ����
        {
        case 1:
            order();//��ˣ�������order.c��
            system("cls");//cls���cmd����ʵ������Ч��
            break;
        case 2:
            calculate();//���ˣ�������calculate.c��
            system("cls");
            break;
        case 3:
            seedishrank();//�鿴ͳ����Ϣ��������seedishrank.c��
            system("cls");
            break;
        case 4:
            otherfunc();//��������
            break;
        case 5://�˳�����
            puts("\nлл���Ļݹˣ���ӭ�´ι��٣�");
            system("pause");
            exit(0);
        case -1://�Ƿ�����������ʾ
            system("cls");
            puts("�����������������!");
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    }
}

void otherfunc()
{
    system("cls");
    char pwd[PWDMAX];//PWDMAX��pwd.h������
    int seed = getseed(pwd);//getseed��ȡ�����ļ���������ֱ�Ӵ浽pwd�У����ؽ��ܺ��seedֵ������-1��ʾ����
    if (seed == -1)
    {
        puts("�������ļ�ʧ�ܻ������ļ���������ϵ����Ա������⣡");
        system("pause");
        return;
    }
    else
    {
        decypto(pwd, seed);//����seedֵ�����Ľ������ģ��õ���������
        //puts(pwd);//��ʽ����ʱҪȥ���ɡ���
        printf("%s", "���������룬���س�ֹͣ���룺");
        if (inandcmppwd(pwd) == 1)//inandcmppwd�������������ͱȶԣ��ȶԳɹ��򷵻�1
        {
            system("cls");//��������ǰ���������Ĳ������
            while (1)
            {
                puts("");
                puts("-------------------");
                puts("1.��Ŀ����");
                puts("2.�˵�����");
                puts("3.��������");
                puts("4.�޸�����");
                puts("5.������һ��");
                puts("6.�˳�");
                puts("-------------------");
                printf("\n%s", "��ѡ�����谴�س�����");
                switch (inputselect1(6))
                {
                case 1:
                    system("cls");
                    accountmgr();//��Ŀ������������������accountmgr.c��
                    system("cls");//��������֮���������
                    break;
                case 2:
                    system("cls");
                    menumgr();//�˵�����������menumgr.c��
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    tablemgr();//��������������tablemgr.c��
                    system("cls");
                    break;
                case 4:
                    system("cls");
                    changepwd(pwd);//�޸����룬������ǵ�ǰ����������
                    break;
                case 5:
                    system("cls");
                    mainmenu();//�ص����˵�
                    break;
                case 6://ֱ���˳�
                    puts("\n��ӭ�´�ʹ�ã�");
                    system("pause");
                    exit(0);
                case -1:
                    system("cls");
                    puts("�����������������!");
                    system("pause");
                    system("cls");
                    break;
                default:
                    break;
                }
            }
        }
        else//������֤��ͨ��������£��ص����˵�
        {
            system("cls");
            puts("������������ѷ��������˵�\n");
            mainmenu();
        }
    }
}



int inputselect1(int maxn)
//inputselect��������Ϸ��жϣ����ص��������ֵ�����Ƿ����룬�򷵻�-1��
//�����int���͵ı����ǲ˵��е����ѡ����
{
    int select;
    char s;
    s = getch();//getchֻ����һ���ַ����Ҳ����Ե����ԣ��Ƚ��ʺϽ��е������ֵ����룬�����Ͳ��ð��س������������
    putchar(s);//�ֶ�����һ��
    fflush(stdin);//ϰ���Ե����������
    select = (int)(s - 48);//��������ַ�ת��int���͵ģ�1��ASCII����49�������������������֣��ַ���ASCII-48�͸պ����������
    if (select < 1 || select > maxn)//�������ı�1С���߱ȴ�������ֵ�󣬾��ǷǷ�������
    {
        return -1;
    }
    else
        return select;
}


int main()//���mainȷʵ�е㵥��
{
    mainmenu();
    return 0;
}
