#ifndef	GLOBAL_H
#define  GLOBAL_H
//���ͷ�ļ������������Ҫ�õ������ֽṹ����������
typedef struct table//�������ӽṹ��
{
    int id;//���ӱ��
    int capacity;//��������
    int state;//����״̬�����ֵΪ0��ʾ���У�1��ʾ���ˣ�order.c��changetablestate_infile������calculate.c�Ľ�β���ֻ�ֱ�����ļ����޸����ֵ
    struct table *next;//����ı�׼����������һ��ָ����һ���ڵ��ָ��

} Table;
typedef Table *tableptr;//����ο��˿α�����Table* typedef��һ�£��������ʹ��

typedef struct menu//����˵��ṹ��
{
    int id;//�˵ı��
    char name[22];//�˵����֣��������ԣ�22�ĳ��������Դ���10�����֣��������ʲô��ֵķ���
    int times;//�˱���Ĵ���
    float money;//�˵ļ۸���floatӦ�þ͹��ˣ�����λ��������λС���ǲ��ᷢ������ģ�һ�㲻������λ���۸�Ĳ˰�
    struct menu *next;//�����׼����

} Menu;
typedef Menu *menuptr;//�����ǲο��α���typedef���������ʹ��

typedef struct order//�����ṹ�壬ÿһ��order���͵�����ֻ��һ����
{
    int tid;//����
    int id;//��Ʒ���
    char name[22];//��Ʒ��
    float money;//��Ʒ����
    int times;//������ڱ�������Ĵ���
    struct order *next;//�����׼����
} Order;
typedef Order *orderptr;//��Ȼ�ǲο��α���typedef���������ʹ��


#endif
