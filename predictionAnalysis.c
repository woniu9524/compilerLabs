#include <stdio.h>
#include "lexical.h"
#include "signStick.h"
/*
 * Ԥ�����
 * (1)  E -> TE'          E' -> +TE'| ?
 * (2)  T -> FT'          T' -> *FT'| ?
 * (3)  F -> (E)| i
 * */



//д����emmm
int getVtId(struct BinaryFormula *binaryFormulas,int* i){
    //��ʶ��1 ����2 +3 *5 (17 )18
    switch (binaryFormulas[*i].key) {
        case 1:return 5;
        case 2:return 5;
        case 3:return 6;
        case 5:return 7;
        case 17:return 8;
        case 18:return 9;
        case 100:return 10;
        default: return -1;
    }
}

void predict(struct BinaryFormula *binaryFormulas,int* i,struct SignStack *signStack,int (*table)[6][10]){
    Push(signStack,10);
    Push(signStack,0);
    int a=getVtId(binaryFormulas,i);

    int flag=1;
    while (flag){
        int x=Pop(signStack);
        if (x>=5&&x<=10){
            if (x==a){
                if (a==10){
                    flag=0;
                } else{
                    //Pop(signStack);
                    (*i)++;//���ﲻӦ��������ģ���Ϊ���ǵݹ飬���ˣ����ø���
                    a=getVtId(binaryFormulas,i);
                }
            } else{
                printf("������");
                break;
            }
        } else if (x>=0&&x<=4){
            int t=table[0][0][1];
            if (table[x][a-5][0]!=-1){//û�г���
                //Pop(signStack);
                int temp_p=1;
                char temp_char[20];//����Ƿ������ͽ�ȥ�ģ�û���ǵ�emmm

                while (table[x][a-5][temp_p]!=-1&&table[x][a-5][temp_p]!=-2){
                    temp_char[temp_p-1]=table[x][a-5][temp_p];
                    temp_p++;
                }
                for (int j = temp_p-2; j >=0 ; j--) {
                    Push(signStack,temp_char[j]);
                }

            } else{
                printf("������");
                break;
            }

        }
    }

}
int main(){
    struct SignStack signStack;
    ClearStack(&signStack);

    //����Ԥ���
    /*
     * E E_ T T_ F    i + * ( ) #   ��
     * 0 1  2 3  4    5 6 7 8 9 10  -2
     *
     * */
    int table[5][6][10]={
            {
                    {0,2,1,-1},{-1,-1,-1},{-1,-1,-1},{0,2,1,-1},{-1,-1,-1},{-1,-1,-1}
            },{
                    {-1,-1,-1},{1,6,2,1,-1},{-1,-1,-1},{-1,-1,-1},{1,-2,-1},{1,-2}
            },{
                    {2,4,3,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}
            },{
                    {-1,-1,-1},{3,-2,-1},{3,7,4,3,-1},{-1,-1,-1},{3,-2},{3,-2}
            },{
                    {4,5,-1},{-1,-1,-1},{-1,-1,-1},{4,8,0,9,-1},{-1,-1,-1},{-1,-1,-1}
            }
    };


    //��������
    char buff[20];
    scanf("%s",&buff);
    struct KeyWordsTable keyWordsTable[KEY_WORD_TABLE_LENGTH];
    readKeyWordsTable(keyWordsTable, "C:\\Users\\zhangcheng\\Desktop\\allProjects\\compileLabs\\data\\keywords.txt");
    struct BinaryFormula binaryFormulas[MAX_BINARY_FORMULA_LENGTH];
    lexicalAnalysis(buff, keyWordsTable, binaryFormulas);
    for (int i = 0; i < 100; ++i) {
        if (binaryFormulas[i].key==0){
            binaryFormulas[i].key=100;//�������һ����
            break;
        }
    }
    //��ʶ��1 ����2 +3 *5 (17 )18
    int start=0;
    int* i=&start;
    predict(binaryFormulas,i,&signStack,table);







}