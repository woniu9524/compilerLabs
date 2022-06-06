#include <stdio.h>
#include "lexical.h"
#include "signStick.h"

/*
��ʶ�� 1
���� 2
+ 3
- 4
* 5
/ 6
( 17
) 18
# �������ó�7��
 * */
//����ӳ���ϵ
void f(struct BinaryFormula *binaryFormulas) {
    int flag = 0;
    for (int i = 0; i < 100; ++i) {
        switch (binaryFormulas[i].key) {
            case 0: {
                flag = 1;
                binaryFormulas[i].key = 7;//������
                break;
            }
            case 1:
                binaryFormulas[i].key = 6;
                break;
            case 2:
                binaryFormulas[i].key = 6;
                break;
            case 3:
                binaryFormulas[i].key = 0;
                break;
            case 4:
                binaryFormulas[i].key = 1;
                break;
            case 5:
                binaryFormulas[i].key = 2;
                break;
            case 6:
                binaryFormulas[i].key = 3;
                break;
            case 17:
                binaryFormulas[i].key = 4;
                break;
            case 18:
                binaryFormulas[i].key = 5;
                break;
        }
        if (flag)
            break;
    }
}
//���ַ���ת��������
int strToNum(char str[]){
    int sum=0;
    for (int i = 0; i < 10; ++i) {
        if (str[i]!='\0'){
            sum*=10;
            sum+=str[i]-'0';
        } else
            break;
    }
    return sum;
}

//����������
int calculatorTwo(int arg1,int arg2,int sign){
    switch (sign) {
        case 0:{
            return arg1+arg2;
        }
        case 1:{
            return arg1-arg2;
        }
        case 2:{
            return arg1*arg2;
        }
        case 3:{
            return arg1/arg2;
        }
        default:printf("calculator error");
    }
}

int calculator(struct BinaryFormula *binaryFormulas, struct SignStack *signStack, struct SignStack *numStack) {
    //�������ȷ�����
    int precedenceTable[8][8] = {
            {2, 2, 0, 0, 0,  2,  0,  2},
            {2, 2, 0, 0, 0,  2,  0,  2},
            {2, 2, 2, 2, 0,  2,  0,  2},
            {2, 2, 2, 2, 0,  2,  0,  2},
            {0, 0, 0, 0, 0,  1,  0,  -1},
            {2, 2, 2, 2, -1, 2,  -1, 2},
            {0, 0, 0, 0, 0,  -1, 0,  1}
    };
    //��ʼ����
    int flag=0;//�ж�ʽ���ǲ��ǵ�ͷ��
    Push(numStack,  strToNum(binaryFormulas[0].word));//ǰ������ֱ��push��ȥ����������Ļ����ⲻ�󣬾Ͳ�������
    Push(signStack, binaryFormulas[1].key);
    for (int i = 2; i < 100; ++i) {
        if (binaryFormulas[i].key == 6) {
            Push(numStack, strToNum(binaryFormulas[i].word));
        } else {
            int left = Pop(signStack);//���ƻ�ջ������
            int right = binaryFormulas[i].key;//SYM���ҡ�
            switch (precedenceTable[left][right]) {
                case 0: {
                    //С�ں���ջ
                    Push(signStack, left);
                    Push(signStack, right);
                    break;
                }
                case 2:{
                    //���ںų�ջ
                    int sign=left;
                    int arg2=Pop(numStack);
                    int arg1=Pop(numStack);
                    int res=calculatorTwo(arg1,arg2,sign);
                    Push(numStack,res);
                    Push(signStack,binaryFormulas[i].key);
                    //���ߵ������
                    if (right==7){
                        Pop(signStack);//��#����ȥ
                        flag=1;
                    }
                }
                /*case 1:{
                    //���ں�ʱ
                    Pop(signStack);
                    break;
                }*/
            }
            //��Ҫ�����ж�һ��()���ֵ��ڵ����
            if (signStack->top>=2){
                right=Pop(signStack);
                left=Pop(signStack);
                if (precedenceTable[left][right]!=1){
                    Push(signStack,left);
                    Push(signStack,right);
                }
            }



        }
        if (flag)
            break;
    }
    //�������ƻ��������������ˣ�д���е���
    while (1){
        int sign=Pop(signStack);
        if (sign==7){
            return Pop(numStack);
        } else{
            int arg2=Pop(numStack);
            int arg1=Pop(numStack);
            int res=calculatorTwo(arg1,arg2,sign);
            Push(numStack,res);
        }
    }
}

int main() {
    //������ʽת���ɶ�Ԫʽ
    char buff[20] = "\0";
    scanf("%s", &buff);
    struct KeyWordsTable keyWordsTable[KEY_WORD_TABLE_LENGTH];
    readKeyWordsTable(keyWordsTable, "C:\\Users\\zhangcheng\\Desktop\\allProjects\\compileLabs\\data\\keywords.txt");
    struct BinaryFormula binaryFormulas[MAX_BINARY_FORMULA_LENGTH];
    lexicalAnalysis(buff, keyWordsTable, binaryFormulas);
    //����ջ������ջ
    struct SignStack signStack;
    struct SignStack numStack;
    ClearStack(&signStack);
    ClearStack(&numStack);
    Push(&signStack, 7);
    //����ӳ��
    f(binaryFormulas);
    //����
    int res=calculator(binaryFormulas, &signStack, &numStack);
    printf("�����:%d",res);


}