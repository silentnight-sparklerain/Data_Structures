//栈——链表实现
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

//建立结构体
typedef struct Node* Stack;
typedef struct Node* PtrToNode;
struct Node
{
	ElementType data;
	PtrToNode Next;
};

//栈的基本函数的声明
Stack createStack();  //建立一个空栈
bool IsEmpty(Stack stack);  //判断栈是否为空栈
void PushStack(Stack stack, ElementType X);  //入栈
ElementType PopStack(Stack stack);  //出栈
void DeleteStackTop(Stack stack);  //删除栈顶元素
ElementType Top(Stack stack);  //访问栈顶元素
void PrintStack(Stack stack);  //打印栈
void clearStack(Stack stack);  //清空栈


//建立一个空栈
Stack createStack()
{
	Stack stack = (Stack)malloc(sizeof(struct Node));
	if (stack == NULL)
	{
		printf("申请空间失败！\n");
		return NULL;
	}
	stack->Next = NULL;
	return stack;
}

//判断栈是否为空栈
bool IsEmpty(Stack stack)
{
	return stack->Next == NULL;
}

//入栈
void PushStack(Stack stack, ElementType X)
{
	Stack P = (Stack)malloc(sizeof(struct Node));
	if (P == NULL)
	{
		printf("申请结点失败！\n");
		return;
	}
	P->data = X;
	P->Next = stack->Next;
	stack->Next = P;
}

//出栈
ElementType PopStack(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("栈已空！无法出栈\n");
		return 0;
	}
	Stack current = stack->Next;
	ElementType X = current->data;
	stack->Next = current->Next;
	free(current);
	current = NULL;
	return X;
}

//删除栈顶元素
void DeleteStackTop(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("栈已空！不可删除栈顶元素\n");
		return;
	}
	Stack current = stack->Next;
	stack->Next = current->Next;
	free(current);
	current = NULL;
}

//访问栈顶元素
ElementType Top(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("栈已空！不可访问栈顶元素\n");
		return 0;
	}
	return stack->Next->data;
}

//打印栈
void PrintStack(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("栈已空！\n");
		return;
	}
	Stack P = stack->Next;
	while (P != NULL)
	{
		printf("%d ", P->data);
		P = P->Next;
	}
	printf("\n");
}

//清空栈
void clearStack(Stack stack)
{
	while (stack->Next != NULL)
	{
		Stack current = stack->Next;
		stack->Next = current->Next;
		free(current);
		current = NULL;
	}
}

//测试函数
void testStack()
{
    printf("=== 栈(链表实现)测试 ===\n\n");

    // 测试1: 创建栈
    printf("1. 创建栈测试:\n");
    Stack stack = createStack();
    if (stack != NULL) 
    {
        printf("栈创建成功\n");
    }
    else 
    {
        printf("栈创建失败\n");
        return;
    }
    printf("栈是否为空: %s\n", IsEmpty(stack) ? "是" : "否");
    printf("\n");

    // 测试2: 空栈操作测试
    printf("2. 空栈操作测试:\n");
    printf("尝试访问空栈顶元素: ");
    ElementType topValue = Top(stack);
    printf("\n尝试弹出空栈元素: ");
    ElementType popValue = PopStack(stack);
    printf("\n尝试删除空栈顶元素: ");
    DeleteStackTop(stack);
    printf("\n打印空栈: ");
    PrintStack(stack);
    printf("\n");

    // 测试3: 入栈测试
    printf("3. 入栈测试:\n");
    printf("入栈元素: 10, 20, 30, 40, 50\n");
    PushStack(stack, 10);
    PushStack(stack, 20);
    PushStack(stack, 30);
    PushStack(stack, 40);
    PushStack(stack, 50);

    printf("当前栈内容: ");
    PrintStack(stack);
    printf("栈是否为空: %s\n", IsEmpty(stack) ? "是" : "否");
    printf("栈顶元素: %d\n", Top(stack));
    printf("\n");

    // 测试4: 出栈测试
    printf("4. 出栈测试:\n");
    printf("弹出栈顶元素: %d\n", PopStack(stack));
    printf("当前栈内容: ");
    PrintStack(stack);
    printf("栈顶元素: %d\n", Top(stack));
    printf("\n");

    // 测试5: 删除栈顶元素测试
    printf("5. 删除栈顶元素测试:\n");
    printf("删除栈顶元素\n");
    DeleteStackTop(stack);
    printf("当前栈内容: ");
    PrintStack(stack);
    printf("栈顶元素: %d\n", Top(stack));
    printf("\n");

    // 测试6: 再次入栈测试
    printf("6. 再次入栈测试:\n");
    printf("入栈元素: 100, 200\n");
    PushStack(stack, 100);
    PushStack(stack, 200);
    printf("当前栈内容: ");
    PrintStack(stack);
    printf("栈顶元素: %d\n", Top(stack));
    printf("\n");

    // 测试7: 清空栈测试
    printf("7. 清空栈测试:\n");
    printf("清空栈前栈是否为空: %s\n", IsEmpty(stack) ? "是" : "否");
    clearStack(stack);
    printf("清空栈后栈是否为空: %s\n", IsEmpty(stack) ? "是" : "否");
    printf("当前栈内容: ");
    PrintStack(stack);
    printf("\n");

    // 测试8: 清空后操作测试
    printf("8. 清空后操作测试:\n");
    printf("尝试访问空栈顶元素: ");
    topValue = Top(stack);
    printf("\n尝试弹出空栈元素: ");
    popValue = PopStack(stack);
    printf("\n尝试删除空栈顶元素: ");
    DeleteStackTop(stack);
    printf("\n");

    // 测试9: 重新使用栈
    printf("9. 重新使用栈测试:\n");
    printf("入栈元素: 5, 15, 25\n");
    PushStack(stack, 5);
    PushStack(stack, 15);
    PushStack(stack, 25);
    printf("当前栈内容: ");
    PrintStack(stack);
    printf("栈顶元素: %d\n", Top(stack));
    printf("\n");

    // 测试10: 多次出栈直到空
    printf("10. 多次出栈直到空:\n");
    while (!IsEmpty(stack)) 
    {
        printf("弹出元素: %d\n", PopStack(stack));
        printf("当前栈内容: ");
        PrintStack(stack);
    }
    printf("栈是否为空: %s\n", IsEmpty(stack) ? "是" : "否");
    printf("\n");

    // 释放栈内存
    free(stack);
    printf("测试完成，内存已释放。\n");
}

int main() 
{
    testStack();
    return 0;
}