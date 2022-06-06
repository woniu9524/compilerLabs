#include <stdio.h>
#include "lexical.h"
#include "signStick.h"

/*
标识符 1
整数 2
+ 3
- 4
* 5
/ 6
( 17
) 18
# 这里设置成7吧
 * */
//设置映射关系
void f(struct BinaryFormula *binaryFormulas) {
    int flag = 0;
    for (int i = 0; i < 100; ++i) {
        switch (binaryFormulas[i].key) {
            case 0: {
                flag = 1;
                binaryFormulas[i].key = 7;//随便设的
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
//将字符串转换成数字
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

//两个数运算
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
    //构建优先分析表
    int precedenceTable[8][8] = {
            {2, 2, 0, 0, 0,  2,  0,  2},
            {2, 2, 0, 0, 0,  2,  0,  2},
            {2, 2, 2, 2, 0,  2,  0,  2},
            {2, 2, 2, 2, 0,  2,  0,  2},
            {0, 0, 0, 0, 0,  1,  0,  -1},
            {2, 2, 2, 2, -1, 2,  -1, 2},
            {0, 0, 0, 0, 0,  -1, 0,  1}
    };
    //开始计算
    int flag=0;//判断式子是不是到头了
    Push(numStack,  strToNum(binaryFormulas[0].word));//前两个我直接push进去，正常输入的话问题不大，就不处理了
    Push(signStack, binaryFormulas[1].key);
    for (int i = 2; i < 100; ++i) {
        if (binaryFormulas[i].key == 6) {
            Push(numStack, strToNum(binaryFormulas[i].word));
        } else {
            int left = Pop(signStack);//下推机栈顶【左】
            int right = binaryFormulas[i].key;//SYM【右】
            switch (precedenceTable[left][right]) {
                case 0: {
                    //小于号入栈
                    Push(signStack, left);
                    Push(signStack, right);
                    break;
                }
                case 2:{
                    //大于号出栈
                    int sign=left;
                    int arg2=Pop(numStack);
                    int arg1=Pop(numStack);
                    int res=calculatorTwo(arg1,arg2,sign);
                    Push(numStack,res);
                    Push(signStack,binaryFormulas[i].key);
                    //当走到最后了
                    if (right==7){
                        Pop(signStack);//把#弹出去
                        flag=1;
                    }
                }
                /*case 1:{
                    //等于号时
                    Pop(signStack);
                    break;
                }*/
            }
            //需要从新判断一下()这种等于的情况
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
    //最后把下推机里的清理掉就行了，写的有点乱
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
    //输入表达式转化成二元式
    char buff[20] = "\0";
    scanf("%s", &buff);
    struct KeyWordsTable keyWordsTable[KEY_WORD_TABLE_LENGTH];
    readKeyWordsTable(keyWordsTable, "C:\\Users\\zhangcheng\\Desktop\\allProjects\\compileLabs\\data\\keywords.txt");
    struct BinaryFormula binaryFormulas[MAX_BINARY_FORMULA_LENGTH];
    lexicalAnalysis(buff, keyWordsTable, binaryFormulas);
    //符号栈和数字栈
    struct SignStack signStack;
    struct SignStack numStack;
    ClearStack(&signStack);
    ClearStack(&numStack);
    Push(&signStack, 7);
    //重新映射
    f(binaryFormulas);
    //计算
    int res=calculator(binaryFormulas, &signStack, &numStack);
    printf("结果是:%d",res);


}