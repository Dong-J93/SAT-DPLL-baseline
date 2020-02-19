#include "head.h"

ClauseNode* AddClause(ClauseNode* s, int var);        // ���ӵ��Ӿ�
ClauseNode* IsUnitClause(ClauseNode* s);              // �ж��Ƿ���ڵ��Ӿ�
ClauseNode* CopyS(ClauseNode* s);                     // ���Ʊ�
ClauseNode* CopyClause(ClauseNode* s);                // ����һ���Ӿ�
ClauseNode* DeleteClause(ClauseNode* s);              // ɾ��һ���Ӿ�
ClauseNode* DeleteLiteral(ClauseNode* s, int var);    // ɾ������Ԫ
status Print(ClauseNode* s);                          // ��ӡ��
status IsEmptyClause(ClauseNode* s);                  // �ж��Ƿ���ڿ��Ӿ�
status EvaluateClause();                              // �����������״̬
status RecordTruth(ClauseNode* s, int* truth_table);  // ��¼���Ӿ���Ԫ�ص���ֵ
status RemoveVar(ClauseNode* s, int var);             // ɾ����Ԫ�����Ӿ��븺��Ԫ
int PickVar(ClauseNode* s);                           // ֱ��ȡ��һ���Ӿ�ĵ�һ����Ԫ

status DPLL(ClauseNode* s, int* truth_table)
{
    ClauseNode* tmp = s;
    ClauseNode* unit_clause = IsUnitClause(tmp);      // ��õ��Ӿ�

    // ���Ӿ����
    while(unit_clause)
    {
        RecordTruth(unit_clause, truth_table);        // ��¼���Ӿ��еı�Ԫ����ֵ
        int var = unit_clause->right->data;
        RemoveVar(s, var);

        if(s->down == NULL) return FOUND;             // SΪ��
        else if(IsEmptyClause(s))   return NOTFOUND;  // S�д��ڿ��Ӿ�

        tmp = s;
        unit_clause = IsUnitClause(tmp);              // �����ڵ��Ӿ������ѭ��
    }

    // ���Ѳ���
    int var = PickVar(s);                                            // ѡ��Ԫ
    if(DPLL(AddClause(CopyS(s), var), truth_table))  return FOUND;   // ��Ԫ����ֵѡ����,�˴�����S�Ŀ���
    return DPLL(AddClause(s, -var), truth_table);                    // ��Ԫ����ֵѡ����
}

ClauseNode* CopyS(ClauseNode* s)
{
    ClauseNode *s_new, *tmp, *s_origin = s->down;

    // ����root
    s_new = (ClauseNode *)malloc(sizeof(ClauseNode));
    s_new->right = NULL;
    tmp = s_new;

    // ѭ����ȡ�Ӿ�
    while(s_origin)
    {
        tmp->down = CopyClause(s_origin);
        tmp = tmp->down;
        s_origin = s_origin->down;
    }
    return s_new;
}

ClauseNode* CopyClause(ClauseNode* s)
{
    ClauseNode* clause_tmp;
    LiteralNode *literal_tmp, *s_tmp = s->right;

    // �����Ӿ���
    clause_tmp = (ClauseNode *)malloc(sizeof(ClauseNode));
    clause_tmp->down = NULL;
    clause_tmp->right = NULL;

    // ������һ�����ֽ��
    if(s_tmp)
    {
        literal_tmp = (LiteralNode *)malloc(sizeof(LiteralNode));
        literal_tmp->data = s_tmp->data;
        literal_tmp->right = NULL;
        s_tmp = s_tmp->right;
        clause_tmp->right = literal_tmp;
    }

    // ѭ���������ֽ��
    while(s_tmp)
    {
        literal_tmp->right = (LiteralNode *)malloc(sizeof(LiteralNode));
        literal_tmp->right->data = s_tmp->data;
        literal_tmp->right->right = NULL;
        literal_tmp = literal_tmp->right;
        s_tmp = s_tmp->right;
    }
    return clause_tmp;
}

ClauseNode* AddClause(ClauseNode* s, int var)
{
    ClauseNode* tmp;
    tmp = (ClauseNode *)malloc(sizeof(ClauseNode));
    tmp->right = (LiteralNode *)malloc(sizeof(LiteralNode));
    tmp->right->data = var;
    tmp->right->right = NULL;
    tmp->down = s->down;
    s->down = tmp;
    return s;
}

int PickVar(ClauseNode* s)
{
    int var = s->down->right->data;
    return var;
}

status RemoveVar(ClauseNode* s, int var)
{
    ClauseNode *c_tmp = s->down, *last_c_tmp = s;
    while(c_tmp)                                     // ѭ����ȡÿһ���Ӿ�
    {
        c_tmp = DeleteLiteral(c_tmp, var);           // ɾ������Ԫ���������������Ԫ�򷵻�NULL
        if(c_tmp == NULL)
        {
            c_tmp = DeleteClause(last_c_tmp->down);  // ������Ԫ��ͬ��ɾ���Ӿ�
            last_c_tmp->down = c_tmp;
            continue;
        }
        if(c_tmp == NULL)   break;
        last_c_tmp = c_tmp;  // ��һ���Ӿ�
        c_tmp = c_tmp->down;
    }
    return OK;
}

ClauseNode* DeleteClause(ClauseNode* s)
{
    ClauseNode* tmp = s;
    LiteralNode* l;
    while(s->right)                   // ��ɾ���Ӿ�����������
    {
        l = s->right;
        s->right = s->right->right;
        free(l);
    }
    s = s->down;
    free(tmp);                        // ��ɾ�����Ӿ�
    return s;
}

ClauseNode* DeleteLiteral(ClauseNode* s, int var)
{
    LiteralNode *l = s->right, *tmp;

    // �����һ������
    if(l->data == -var)                  // ����Ԫ
    {
        tmp = s->right->right;
        free(l);
        s->right = tmp;
        return s;
    }
    else if(l->data == var) return NULL; // ����Ԫ

    // ѭ�����������������
    while(l)
    {
        if(l->right && l->right->data == -var)
        {
            tmp = l->right;
            l->right = l->right->right;
            free(tmp);
        }
        else if(l->right && l->right->data == var)  return NULL;
        l = l->right;
    }
    return s;
}

status IsEmptyClause(ClauseNode* s)
{
    ClauseNode* tmp = s->down;
    while(tmp)
    {
        if(!tmp->right) return YES;
        tmp = tmp->down;
    }
    return NO;
}

status RecordTruth(ClauseNode* s, int* truth_table)
{
    int idx = abs(s->right->data) - 1;   // ���=����ֵ-1
    if(s->right->data > 0)  truth_table[idx] = 1;
    else    truth_table[idx] = 0;
    return OK;
}

ClauseNode* IsUnitClause(ClauseNode* s)
{
    ClauseNode* tmp = s;
    while(tmp)
    {
        if(tmp->right && !tmp->right->right)    return tmp;
        tmp = tmp->down;
    }
    return NULL;
}

status Print(ClauseNode* s)
{
    ClauseNode* c_tmp = s->down;
    LiteralNode* l_tmp;
    printf("\n-----Start-----\n");
    while(c_tmp)
    {
        l_tmp = c_tmp->right;
        while(l_tmp)
        {
            printf("%d ", l_tmp->data);
            l_tmp = l_tmp->right;
        }
        if(c_tmp->right)    printf("\n");
        else    printf("��\n");
        c_tmp = c_tmp->down;
    }
    printf("------End------\n");
    return OK;
}
