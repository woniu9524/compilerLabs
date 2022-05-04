/*
 * �ݹ��½�����
 * (1)  E -> TE'          E' -> +TE'| ?
 * (2)  T -> FT'          T' -> *FT'| ?
 * (3)  F -> (E)| i
 * */
#include <stdio.h>
#include "lexical.h"
void E();void E_();void T();void T_();void F();

void E(struct BinaryFormula *binaryFormulas,int* i){
    T(binaryFormulas,i);
    E_(binaryFormulas,i);
}
void E_(struct BinaryFormula *binaryFormulas,int* i){
    if (binaryFormulas[*i].key==3){
        (*i)++;
        T(binaryFormulas,i);
        E_(binaryFormulas,i);
    }

}
void T(struct BinaryFormula *binaryFormulas,int* i){
    F(binaryFormulas,i);
    T_(binaryFormulas,i);
}
void T_(struct BinaryFormula *binaryFormulas,int* i){
    if(binaryFormulas[*i].key==5){
        (*i)++;
        F(binaryFormulas,i);
        T_(binaryFormulas,i);
    }
}
void F(struct BinaryFormula *binaryFormulas,int* i){
    if (binaryFormulas[*i].key==1||binaryFormulas[*i].key==2){
        (*i)++;
    } else if(binaryFormulas[*i].key==17){
        (*i)++;
        E(binaryFormulas,i);
        if (binaryFormulas[*i].key==18){
            (*i)++;
        } else{
            printf("�٣�\n");
        }
    } else{
        printf("��һ������");
    }
}

int main(){
    //�Ƚ��дʷ��������պ����ðɣ��Ժ��ٸ�
    char buff[20];
    scanf("%s",&buff);
    struct KeyWordsTable keyWordsTable[KEY_WORD_TABLE_LENGTH];
    readKeyWordsTable(keyWordsTable, "C:\\Users\\zhangcheng\\Desktop\\allProjects\\compileLabs\\data\\keywords.txt");
    struct BinaryFormula binaryFormulas[MAX_BINARY_FORMULA_LENGTH];
    lexicalAnalysis(buff, keyWordsTable, binaryFormulas);
    //��ʶ��1 ����2 +3 *5 (17 )18
    int start=0;
    int* i=&start;
    E(binaryFormulas,i);



}

