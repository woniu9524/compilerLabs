//
// Created by zhangcheng on 2022/4/10.
//
/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            ���汣��       ����BUG
*/
#include <stdio.h>
#include <string.h>
#define KEY_WORD_TABLE_LENGTH 35//�ؼ��ֱ�
#define MAX_BINARY_FORMULA_LENGTH 500 //��Ԫʽ�ĸ������ֵ
#define WORD_LENGTH 100 //�����ַ�����


//��Ԫʽ
struct BinaryFormula {
    int key;
    char word[WORD_LENGTH];
};

//�ؼ��ֱ�
struct KeyWordsTable {
    int key;
    char word[WORD_LENGTH];
} keyWordsTable[KEY_WORD_TABLE_LENGTH];

//������
void readCodes(char *codes, char *filename) {
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open the file !\n");
    }
    char ch;
    for (int i = 0; (ch = fgetc(fp)) != EOF; ++i) {
        codes[i] = ch;
    }
    fclose(fp);
}

//���ؼ��ֱ�
void readKeyWordsTable(struct KeyWordsTable *table, char *filename) {
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open the file !\n");
    }
    for (int i = 0; fscanf(fp, "%s %d", table[i].word, &table[i].key) != EOF; ++i);
    fclose(fp);
}

//���Ƿ�Ϊ����
int isNumber(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

//���Ƿ�Ϊ��ĸ
int isLetter(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || ch >= 'a' && ch <= 'z')
        return 1;
    return 0;
}

//���Ҷ�Ԫ��
struct BinaryFormula findBinaryFormula(char *word, struct KeyWordsTable *table, int flag) {
    struct BinaryFormula binaryFormula;
    for (int i = 0; i < KEY_WORD_TABLE_LENGTH; ++i) {
        if (strcmp(word, table[i].word) == 0) {
            binaryFormula.key = table[i].key;
            strcpy(binaryFormula.word, table[i].word);
            return binaryFormula;
        }
    }
    //���ڹؼ�����
    binaryFormula.key = flag;
    strcpy(binaryFormula.word, word);
    return binaryFormula;
}

//���ƶ�Ԫ��
void copyBinaryFormula(struct BinaryFormula *binaryFormulas, struct BinaryFormula binaryFormula, int location) {
    binaryFormulas[location].key = binaryFormula.key;
    strcpy(binaryFormulas[location].word, binaryFormula.word);
}

//�ʷ�����
void lexicalAnalysis(char *codes, struct KeyWordsTable *table, struct BinaryFormula binaryFormulas[]) {

    int binaryLocation = 0;//��Ԫ����ƶ�λ��
    int i = 0;
    while (codes[i] != '\0') {
        //�ж��ǲ��ǿո���߻س�
        if (codes[i] == ' ' || codes[i] == '\n')
            i++;
        //ȡ���������߱�����
        if (isLetter(codes[i])) {
            char word[WORD_LENGTH] = "\0";
            int j = 0;
            word[j] = codes[i];
            i++;
            j++;
            while (isLetter(codes[i]) || isNumber(codes[i])) {
                word[j] = codes[i];
                j++;
                i++;
            }
            copyBinaryFormula(binaryFormulas, findBinaryFormula(word, table, 1), binaryLocation);
            binaryLocation++;
        }
        //ȡ���޷�������
        if (isNumber(codes[i])) {
            char word[WORD_LENGTH] = "\0";
            int j = 0;
            word[j] = codes[i];
            i++;
            j++;
            while (isNumber(codes[i])) {
                word[j] = codes[i];
                j++;
                i++;
            }
            copyBinaryFormula(binaryFormulas, findBinaryFormula(word, table, 2), binaryLocation);
            binaryLocation++;
        }
        //��������ʱ����Ϊ�Ƿ��Ű�
        if ((codes[i] != ' ' && codes[i] != '\n' && codes[i] != '\0') && (!isNumber(codes[i] && !isLetter(codes[i])))) {
            //������һ���Ļ��������ģ�����д�Ć����˵㡣
            char word1[WORD_LENGTH] = "\0";
            char word2[WORD_LENGTH] = "\0";
            int j = 0;
            word1[j] = codes[i];//һ����
            word2[j] = codes[i];//������
            i++;
            j++;
            word2[j] = codes[i];
            if (strcmp(word2, "<=")==0
                || strcmp(word2, "==")==0
                || strcmp(word2, "!=")==0
                || strcmp(word2, ">=")==0
                || strcmp(word2, "&&")==0
                || strcmp(word2, "||")==0) {
                copyBinaryFormula(binaryFormulas, findBinaryFormula(word2, table, -1), binaryLocation);//����-1˵����������
                binaryLocation++;
            } else {
                copyBinaryFormula(binaryFormulas, findBinaryFormula(word1, table, -1), binaryLocation);//����-1˵����������
                binaryLocation++;
            }
        }
    }
}

void printBinaryFormulas(struct BinaryFormula *binaryFormula) {
    for (int i = 0;i < MAX_BINARY_FORMULA_LENGTH&&binaryFormula[i].key!=0; ++i) {
        if (binaryFormula[i].key==1)
            printf("\n��ʶ��:%s",binaryFormula[i].word);
        else if (binaryFormula[i].key==2)
            printf("\n����:%s",binaryFormula[i].word);
        printf("\n%d:%s",binaryFormula[i].key,binaryFormula[i].word);
    }
}

int main() {
    char codes[1000] = "\0";
    readCodes(codes, "C:\\Users\\zhangcheng\\Desktop\\allProjects\\compileLabs\\data\\test.txt");
    printf("%s", codes);
    readKeyWordsTable(keyWordsTable, "C:\\Users\\zhangcheng\\Desktop\\allProjects\\compileLabs\\data\\keywords.txt");
    struct BinaryFormula binaryFormulas[MAX_BINARY_FORMULA_LENGTH];
    lexicalAnalysis(codes, keyWordsTable, binaryFormulas);
    printBinaryFormulas(binaryFormulas);
}