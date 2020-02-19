#include "head.h"
#define BUFF_SIZE 256
#define PATH_SIZE 256

// ����
char base_path[PATH_SIZE] = "C:\\Users\\vince\\Desktop\\������ƿ���\\ָ��\\SAT���Ա�ѡ����";

status SkipComments(char* buff, FILE* fp);                                    // ����comment
status GetPInfo(char* buff, int* var_num, int* clause_num);                   // ���p���м�¼���Ӿ�ͱ�Ԫ����
ClauseNode* ReadClauses(char* buff, FILE* fp, int* var_num, int clause_num);  // ��ȡ�������Ӿ�
ClauseNode* CreateClauseUnit(char* buff, FILE* fp);                           // ���������Ӿ�
LiteralNode* CreateLiteralUnit(char* buff);                                   // ����һ���ı���Ԫ

ClauseNode* CreateClause(int* var_num, char* filename)
{
    int clause_num;
    char buff[BUFF_SIZE];
    ClauseNode* s;

    // ��ȡ�ļ�
    strcat(base_path, filename);         // ����ļ�����·��
    FILE* fp = fopen(base_path, "r");
    if(!fp)
    {
        printf("   ·�����䲻�Ի�����˼�����룿\n");
        return ERROR;
    }

    // �����ļ�
    SkipComments(buff, fp);
    GetPInfo(buff, var_num, &clause_num);
    s = ReadClauses(buff, fp, var_num, clause_num);

    fclose(fp);
    return s;
}

status SkipComments(char* buff, FILE* fp)
{
    while(fgets(buff, BUFF_SIZE, fp))
    {
        if(buff[0] == 'p')  break;
    }
    return OK;
}

status GetPInfo(char* buff, int* var_num, int* clause_num)
{
    // p cnf var_num clause_num
    char* token = strtok(buff, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    *var_num = atoi(token);
    token = strtok(NULL, " ");
    *clause_num = atoi(token);
    return OK;
}

ClauseNode* ReadClauses(char* buff, FILE* fp, int* var_num, int clause_num)
{
    ClauseNode *s, *tmp;

    // ����root
    s = (ClauseNode *)malloc(sizeof(ClauseNode));
    s->right = NULL;
    tmp = s;

    // ѭ����ȡ�Ӿ�
    for(int i = 0; i < clause_num; i++)
    {
        tmp->down = CreateClauseUnit(buff, fp);
        tmp = tmp->down;
    }
    return s;
}

ClauseNode* CreateClauseUnit(char* buff, FILE* fp)
{
    ClauseNode *c;
    LiteralNode *e, *tmp;

    // �����Ӿ俪ͷ
    c = (ClauseNode *)malloc(sizeof(ClauseNode));
    c->right = NULL;
    c->down = NULL;


    // �����һ��Ԫ��
    fscanf(fp, "%s", buff);
    c->right = CreateLiteralUnit(buff);
    tmp = c->right;

    // ����ʣ�µ�Ԫ��
    fscanf(fp, "%s", buff);
    while(strcmp(buff, "0"))
    {
        e = CreateLiteralUnit(buff);
        tmp->right = e;
        tmp = tmp->right;
        fscanf(fp, "%s", buff);
    }
    return c;
}

LiteralNode* CreateLiteralUnit(char* buff)
{
    LiteralNode *e;
    e = (LiteralNode *)malloc(sizeof(LiteralNode));
    e->data = atoi(buff);
    e->right = NULL;
    return e;
}
