#include "head.h"
#define EPOCH 5             // �ظ����д���
#define PATH_SIZE 1024      // ·���ַ�����С

char* ChooseExample();

int main()
{
    int op = 1, literal_num, result, i;
    char filename[PATH_SIZE];
    clock_t t, t1, t2;
    ClauseNode* s;

    while(op)
    {
newone:
        system("cls");
        printf("\n\n");
        printf("         ����SAT�Ķ�����������Ϸ������\n");
        printf("-------------------------------------------------\n");
        printf("     1. SAT�������       2. ����������ɣ�\n");
        printf("     0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0-2]: ");
        scanf("%d", &op);

        // ����SAT�������
        if(op == 1)
        {
            strcpy(filename, ChooseExample());                        // ���·��
            CnfParser(&literal_num, filename, 1);                     // �Ȼ��������������1�����ǳ�ʼ��
            int truth_table[literal_num];                             // ��ֵ��
            for(i = 0; i < literal_num; i++)    truth_table[i] = 1;   // ��ʼ����ֵ������ѳ�ʼֵ��Ϊ1��Ҳ�ɸ�Ϊ0
            t = t1 = t2 = 0;                                          // ��ʼ����ʱ��
            // Print(s);                                              // �˾��ܹ����ӻ�����
            printf("\n    ������,���ظ�����%d��ȡƽ��ֵ...\n\n", EPOCH);

            // �ظ�����EPOCH�� ȡƽ��ֵ
            for(i = 0; i < EPOCH; i++)
            {
                t = clock();
                s = CnfParser(&literal_num, filename, 0);
                t1 += clock() - t;
                result = DpllSolver(s, truth_table);
                t2 += clock() - t;
            }

            // ������
            printf("    ���غ�ʱ��%ldms\n", t1 / EPOCH);           // ȡƽ��ʱ��
            printf("    ����ʱ��%ldms\n", t2 / EPOCH - t1 / EPOCH);
            printf("    �ܺ�ʱ  ��%ldms\n\n", t2 / EPOCH);
            if(result)
            {
                printf("    ������Ӿ伯�����㣬һ�������:\n");   // �н�
                printf("    ��Ϊ��");                              // ��ӡ��ֵΪ1�ı�Ԫ
                for(int k = 0; k < literal_num; k++)    if(truth_table[k])  printf("%d ", k + 1);
                printf("\n");
            }
            else    printf("    ������Ӿ伯�������㣡\n");        // �޽�
            Get2Char();
        }

        else if(op == 0) break;

        else
        {
            printf("\n    ���������룡\n");
            Get2Char();
            goto newone;
        }
    }
    return OK;
}

void Get2Char()
{
    getchar();
    getchar();
}

char* ChooseExample()
{
    int op = 0;
    printf("\n     1.���ܲ��� sud00009  2.���ܲ��� ais10\n");
    printf("     3.���ܲ��� sat20     4.���ܲ��� unsat-5\n");
    printf("     0.��������\n");
    printf("    ��������Ҫ���������[0-4]��");
    while(1)
    {
        scanf("%d", &op);
        if(op == 1) return  "./SAT���Ա�ѡ����/��׼����/���ܲ���/sud00009.cnf";
        else if(op == 2)    return "./SAT���Ա�ѡ����/��׼����/���ܲ���/ais10.cnf";
        else if(op == 3)    return "./SAT���Ա�ѡ����/��׼����/���ܲ���/sat-20.cnf";
        else if(op == 4)    return "./SAT���Ա�ѡ����/��׼����/���ܲ���/unsat-5cnf-30.cnf";
        else if(op == 0)
        {
            printf("    �����룺");
            static char filename[PATH_SIZE];
            scanf("%s", filename);
            return filename;
        }
        printf("    ����������:");
    }
}
