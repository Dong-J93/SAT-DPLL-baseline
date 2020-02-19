#include "head.h"

int main()
{
    int op = 1, var_num, result;
    while(op)
    {
newone:
        system("cls");
        printf("\n\n");
        printf("         ����SAT�Ķ�����������Ϸ������\n");
        printf("-------------------------------------------------\n");
        printf("     1. ���дһ��       2. ����ɴ಻д��\n");
        printf("     0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~2]: ");
        scanf("%d",&op);

        // ����SAT�������
        if(op == 1)
        {
            clock_t start_time, end_time;
            start_time = clock();  // ��ʼ��ʱ

            // �������ѡ��Ҫ���е�����
            char filename[] =  "\\��׼����\\���ܲ���\\ais10.cnf";
            //char filename[] = "\\��׼����\\���ܲ���\\unsat-5cnf-30.cnf";
            //char filename[] = "\\����������\\u-problem10-100.cnf";
            //char filename[] = "\\��������\\L\\ec-iso-ukn009.shuffled-as.sat05-3632-1584.cnf";
            //char filename[] = "\\��׼����\\���ܲ���\\sud00009.cnf";

            // ��ȡ�ļ�����ʼ��
            ClauseNode* f = CreateClause(&var_num, filename);        // �ȶ�ȡcnf�ļ�������Clause
            int truth_table[var_num];                                // ��ֵ��
            for(int k = 0; k < var_num; k++)    truth_table[k] = 1;  // ��ʼ����ֵ������ѳ�ʼֵ��Ϊ1��Ҳ�ɸ�Ϊ0
            // Print(s);                                             // �˾��ܿ��ӻ�����

            // dpll
            result = DPLL(f, truth_table);
            end_time = clock();  // ������ʱ

            // ������
            printf("\n    ��ʱ: %ldms\n", end_time - start_time);
            if(result)  printf("\n    ������ٺٺ�~\n");  // �н�
            else    printf("\n    �����������ƨ��!\n");  // �޽�

            // ��ӡ��ֵΪ1�ı�Ԫ
            printf("\n    ��Ϊ��");
            for(int k = 0; k < var_num; k++)    if(truth_table[k])  printf("%d ", k + 1);
            Get2Char();
        }

        else if(op == 0) break;

        else
        {
            printf("\n    �᲻��ѡ����ү����\n");
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
