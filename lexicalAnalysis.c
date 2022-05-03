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
            佛祖保佑       永无BUG
*/
#include <stdio.h>
#include <string.h>
#define KEY_WORD_TABLE_LENGTH 35//关键字表
#define MAX_BINARY_FORMULA_LENGTH 500 //二元式的个数最大值
#define WORD_LENGTH 100 //单个字符长度


//二元式
struct BinaryFormula {
    int key;
    char word[WORD_LENGTH];
};

//关键字表
struct KeyWordsTable {
    int key;
    char word[WORD_LENGTH];
} keyWordsTable[KEY_WORD_TABLE_LENGTH];

//读代码
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

//读关键字表
void readKeyWordsTable(struct KeyWordsTable *table, char *filename) {
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open the file !\n");
    }
    for (int i = 0; fscanf(fp, "%s %d", table[i].word, &table[i].key) != EOF; ++i);
    fclose(fp);
}

//看是否为数字
int isNumber(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

//看是否为字母
int isLetter(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || ch >= 'a' && ch <= 'z')
        return 1;
    return 0;
}

//查找二元组
struct BinaryFormula findBinaryFormula(char *word, struct KeyWordsTable *table, int flag) {
    struct BinaryFormula binaryFormula;
    for (int i = 0; i < KEY_WORD_TABLE_LENGTH; ++i) {
        if (strcmp(word, table[i].word) == 0) {
            binaryFormula.key = table[i].key;
            strcpy(binaryFormula.word, table[i].word);
            return binaryFormula;
        }
    }
    //不在关键词中
    binaryFormula.key = flag;
    strcpy(binaryFormula.word, word);
    return binaryFormula;
}

//复制二元组
void copyBinaryFormula(struct BinaryFormula *binaryFormulas, struct BinaryFormula binaryFormula, int location) {
    binaryFormulas[location].key = binaryFormula.key;
    strcpy(binaryFormulas[location].word, binaryFormula.word);
}

//词法分析
void lexicalAnalysis(char *codes, struct KeyWordsTable *table, struct BinaryFormula binaryFormulas[]) {

    int binaryLocation = 0;//二元组的移动位置
    int i = 0;
    while (codes[i] != '\0') {
        //判断是不是空格或者回车
        if (codes[i] == ' ' || codes[i] == '\n')
            i++;
        //取出变量或者保留字
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
        //取出无符号数字
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
        //其他的暂时都认为是符号吧
        if ((codes[i] != ' ' && codes[i] != '\n' && codes[i] != '\0') && (!isNumber(codes[i] && !isLetter(codes[i])))) {
            //符号有一个的还有两个的，这里写的啰嗦了点。
            char word1[WORD_LENGTH] = "\0";
            char word2[WORD_LENGTH] = "\0";
            int j = 0;
            word1[j] = codes[i];//一个的
            word2[j] = codes[i];//两个的
            i++;
            j++;
            word2[j] = codes[i];
            if (strcmp(word2, "<=")==0
                || strcmp(word2, "==")==0
                || strcmp(word2, "!=")==0
                || strcmp(word2, ">=")==0
                || strcmp(word2, "&&")==0
                || strcmp(word2, "||")==0) {
                copyBinaryFormula(binaryFormulas, findBinaryFormula(word2, table, -1), binaryLocation);//出现-1说明出问题了
                binaryLocation++;
            } else {
                copyBinaryFormula(binaryFormulas, findBinaryFormula(word1, table, -1), binaryLocation);//出现-1说明出问题了
                binaryLocation++;
            }
        }
    }
}

void printBinaryFormulas(struct BinaryFormula *binaryFormula) {
    for (int i = 0;i < MAX_BINARY_FORMULA_LENGTH&&binaryFormula[i].key!=0; ++i) {
        if (binaryFormula[i].key==1)
            printf("\n标识符:%s",binaryFormula[i].word);
        else if (binaryFormula[i].key==2)
            printf("\n整数:%s",binaryFormula[i].word);
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