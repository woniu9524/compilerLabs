//
// Created by zhangcheng on 2022/5/5.
//

#ifndef COMPILELABS_SIGNSTICK_H
#define COMPILELABS_SIGNSTICK_H

#define SIGN_STACK_MAX 100 //符号栈的最大长度
//符号栈
typedef struct SignStack {
    char Signs[SIGN_STACK_MAX];// 存储元素的数组
    int top;//栈顶指针
};

void ClearStack(struct SignStack *L){
    L->top=-1;
}


char Push(struct SignStack *L, char e) {
    // 栈已满
    if (L->top >= SIGN_STACK_MAX - 1) {
        return 0;
    }
    // 加入栈中
    L->Signs[++L->top] = e;
    // 返回自身
    return e;
}

// 移除栈顶元素
char Pop(struct SignStack *L){
    // 栈空
    if(L->top <0){
        return 0;
    }
    return L->Signs[L->top--];
}

//判断栈s是否为空
int isEmpty(struct SignStack s)
{
    // 如果下标在0，说明栈中无元素
    if(s.top <0){
        return 0;
    }
    return 1;
}
// 判断栈是否已满.
int isFull(struct SignStack s){
    if(s.top >= SIGN_STACK_MAX -1){
        return 0;
    }
    return 1;
}

#endif //COMPILELABS_SIGNSTICK_H
