#include "Restaurant.h"
#define PWDMAX 16//������󳤶ȵĺ궨��
char seedstable[11] = "aicxoqpdst";//seed�������

void tostring(int src, char *dest, int len)//��һ��int������תΪchar���ַ����ĺ���
{
    char c[len];
    int i = 0;
    for (i = 0; i < len; i++)
    {
        c[i] = (char)((src - (src / 10) * 10) + 48);
        src = src / 10;
    }
    int j = 0;
    for (i = len - 1; i >= 0; i--)
    {
        dest[j] = c[i];//��c[i]���Ŵ浽dest����
        j++;
    }
    dest[len]='\0';//�����˲�0
}
void encode(char* src)//����seed������src����
{
	int i;
	for (i = 0; i < 9; i++)
	{
		src[i] = seedstable[(int)(src[i] - 48)];
	}
}
void encypto(char* src, int seed)//�����ļ���
{
	unsigned int i;
	char pwdtable[96];
	memset(pwdtable, 0, 96);
	for (i = 0; i < 95; i++)
	{
		pwdtable[i] = (char)(32 + i);//��ʼ�����������������е��ܴӼ���������ַ�
	}
	srand(seed);//�ô����seed��Ϊsrand����Ĳ���

	for (i = 0; i < strlen(pwdtable); i++)//�������������srand�Ĳ����ǹ̶��ģ�������ҵĽ��Ҳ�ǹ̶���
	{
		int a = rand() % strlen(pwdtable);
		int b = rand() % strlen(pwdtable);
		char c = pwdtable[b];
		pwdtable[b] = pwdtable[a];
		pwdtable[a] = c;
	}

	unsigned int len = strlen(src);
	i = 0;
	while (i < len)
	{
		src[i] = pwdtable[(int)src[i] - 32];//���մ��ҵ�������õ�����
		i++;
	}
}

int randnum()//�������Ļ�ȡһ�������������Ϊ9λ��
{
	int num;
	int totalNum;
	srand((unsigned int)(time(NULL)));
	totalNum = 0;
	int j;
	for (j = 0; j < 9; j++)
	{
		num = rand() % 9 + 1;
		totalNum += num * (int)pow(10, j);
	}
	return totalNum;
}


void decypto(char* src, int seed)//�����Ľ���
{
	char pwdtable[96];
	memset(pwdtable, 0, 96);
	unsigned int i;
	for (i = 0;i < 95;i++) {
		pwdtable[i] = (char)(32 + i);//�������ȳ�ʼ���������
	}
	srand(seed);//�ô����seed��Ϊsrand�Ĳ���

	for (i = 0; i < strlen(pwdtable); i++)//���������seed��ȷ���ģ����ű�Ҳ����ȷ����
	{
		int a = rand() % strlen(pwdtable);
		int b = rand() % strlen(pwdtable);
		char c = pwdtable[b];
		pwdtable[b] = pwdtable[a];
		pwdtable[a] = c;
	}
	unsigned int len = strlen(src);
	int j;
	i = 0;
	while (i < len)//����������������
	{
		for (j = 0; j < 96; j++)
		{
			if (pwdtable[j] == src[i])
			{
				src[i] = (char)(j + 32);
				i++;
				break;
			}
		}
	}
}

int decode(char* src)//����seed�ĺ������ɹ�����0��������-1
{
	int i, j, ok;

	for (i = 0; i < 9; i++)
	{
		ok = 0;
		for (j = 0; j < 10; j++)
		{
			if (src[i] == seedstable[j])
			{
				src[i] = (char)(j + 48);
				ok = 1;
				break;
			}
		}
		if (ok == 0)
			return -1;
	}
	return 0;
}





int getseed(char* src)//ʮ����Ҫ��getseed��������������seed��ͬʱ��Ѵ����src��ֵΪ��������
{
	int seed;
	char seeds[9];
	char in[9+PWDMAX];
	memset(in, 0, 9+PWDMAX);
	unsigned int i, j;
	FILE* fp;
	fp = fopen("pwd", "r");
	if (fp == NULL)
	{
		return -1;
	}
	else
	{
		i = 0;

		if (fscanf(fp, "%[^\n]", in) == EOF) {
			puts("��ȡ�����ļ����ִ���");
			system("pause");
			return -1;
		}

		fclose(fp);

		if (strlen(in) > (9 + PWDMAX))
			//���볤�ȹ���
			return -1;
		else {
			for (i = 0; i < 9; i++)
			{
				seeds[i] = in[i];
			}
			if (decode(seeds) == -1) {
				//�����ʽ����
				return -1;
			}
			else {
				seed = atoi(seeds);
				for (i = 9, j = 0; i < strlen(in); i++)
				{
					src[j++] = in[i];
				}
				src[j] = '\0';
				return seed;
			}
		}
	}

}


int inandcmppwd(const char* rightpwd)
{
	char in[PWDMAX];
	int i = 0;
	while (i < PWDMAX)
	{
		in[i] = getch();

		if (in[i] == '\r' || in[i] == '\n')
		{
			in[i] = '\0';
			break;
		}
		else if (i == 15)
		{
			in[i + 1] = '\0';
		}

		if (in[i] == '\b')
		{
			if (i == 0)
			{
				continue;
			}
			else
			{
				printf("%s", "\b \b");
				i--;
			}
		}
		else
		{
			printf("*");
			i++;
		}
	}
	if (strcmp(in, rightpwd) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void changepwd()
{
	char pwd[PWDMAX];
	int seed = getseed(pwd);
	if (seed == -1)
    {
        puts("�������ļ�ʧ�ܻ������ļ���������ϵ����Ա������⣡");
        system("pause");
        return;
    }
	decypto(pwd, seed);
	char in2[PWDMAX];
	int i = 0;
	printf("%s", "\n������ԭ������ȷ����ݣ�");
	if (inandcmppwd(pwd) == 1)
	{
		printf("%s", "\n�����������룬���Ȳ�����16λ��");
		while (i < PWDMAX)
		{
			in2[i] = getch();

			if (in2[i] == '\r' || in2[i] == '\n')
			{
				in2[i] = '\0';
				break;
			}
			else if (i == PWDMAX-1 )
			{
				in2[i + 1] = '\0';
			}

			if (in2[i] == '\b')
			{
				if (i == 0)
				{
					continue;
				}
				else
				{
					printf("%s", "\b \b");
					i--;
				}
			}
			else
			{
				printf("*");
				i++;
			}
		}
		if (strcmp(in2, pwd) == 0)
		{
			puts("\n�������ԭ������ͬŶ���Զ�������");
			Sleep(1000);
			system("cls");
		}
		else
		{
			printf("%s", "\n���ٴ����������룺");
			while (1)
			{
				int state = inandcmppwd(in2);
				static int times = 0;
				if (state == 0)
				{

					puts("\n�������벻һ�£�");

					times++;
					if (times >= 5)
					{
						printf("%s", "�Ƿ�������룬���񣬽��������˵�(Y/N): ");
						char s;
						s = getch();
						printf("%c", s);
						if (s == 'Y' || s == 'y')
						{
							printf("%s", "\n���ٴ����������룺");
							continue;
						}
						else
						{
							puts("\n������ֹ�������Զ�����");
							times = 0;
							Sleep(1000);
							system("cls");
							break;
						}
					}
					printf("%s", "���ٴ����������룺");
				}
				else if (state == 1)
				{

					int seed = randnum();

					encypto(in2, seed);

					char seeds[9];
					tostring(seed, seeds, 9);

					char out[9 + PWDMAX];
					encode(seeds);

					strcpy(out, seeds);

					strcat(out, in2);

					FILE* fp;
					fp = fopen("pwd", "w");
					if (fp == NULL) {
						puts("�����ļ���ʧ�ܣ������Զ�����");
						break;
					}
					else {
						fprintf(fp, "%s", out);
						fclose(fp);
						puts("\n�����޸ĳɹ��������Զ�����");
					}
					Sleep(1000);
					system("cls");
					break;
				}
			}
		}
	}
	else
	{
		puts("\n�����������������ֹ�������Զ�����");
		Sleep(1000);
		system("cls");
	}
}

