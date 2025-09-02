//ջ��������ʵ��
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

//�����ṹ��
typedef struct Node* Stack;
typedef struct Node* PtrToNode;
struct Node
{
	ElementType data;
	PtrToNode Next;
};

//ջ�Ļ�������������
Stack createStack();  //����һ����ջ
bool IsEmpty(Stack stack);  //�ж�ջ�Ƿ�Ϊ��ջ
void PushStack(Stack stack, ElementType X);  //��ջ
ElementType PopStack(Stack stack);  //��ջ
void DeleteStackTop(Stack stack);  //ɾ��ջ��Ԫ��
ElementType Top(Stack stack);  //����ջ��Ԫ��
void PrintStack(Stack stack);  //��ӡջ
void clearStack(Stack stack);  //���ջ


//����һ����ջ
Stack createStack()
{
	Stack stack = (Stack)malloc(sizeof(struct Node));
	if (stack == NULL)
	{
		printf("����ռ�ʧ�ܣ�\n");
		return NULL;
	}
	stack->Next = NULL;
	return stack;
}

//�ж�ջ�Ƿ�Ϊ��ջ
bool IsEmpty(Stack stack)
{
	return stack->Next == NULL;
}

//��ջ
void PushStack(Stack stack, ElementType X)
{
	Stack P = (Stack)malloc(sizeof(struct Node));
	if (P == NULL)
	{
		printf("������ʧ�ܣ�\n");
		return;
	}
	P->data = X;
	P->Next = stack->Next;
	stack->Next = P;
}

//��ջ
ElementType PopStack(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("ջ�ѿգ��޷���ջ\n");
		return 0;
	}
	Stack current = stack->Next;
	ElementType X = current->data;
	stack->Next = current->Next;
	free(current);
	current = NULL;
	return X;
}

//ɾ��ջ��Ԫ��
void DeleteStackTop(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("ջ�ѿգ�����ɾ��ջ��Ԫ��\n");
		return;
	}
	Stack current = stack->Next;
	stack->Next = current->Next;
	free(current);
	current = NULL;
}

//����ջ��Ԫ��
ElementType Top(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("ջ�ѿգ����ɷ���ջ��Ԫ��\n");
		return 0;
	}
	return stack->Next->data;
}

//��ӡջ
void PrintStack(Stack stack)
{
	if (IsEmpty(stack))
	{
		printf("ջ�ѿգ�\n");
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

//���ջ
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

//���Ժ���
void testStack()
{
    printf("=== ջ(����ʵ��)���� ===\n\n");

    // ����1: ����ջ
    printf("1. ����ջ����:\n");
    Stack stack = createStack();
    if (stack != NULL) 
    {
        printf("ջ�����ɹ�\n");
    }
    else 
    {
        printf("ջ����ʧ��\n");
        return;
    }
    printf("ջ�Ƿ�Ϊ��: %s\n", IsEmpty(stack) ? "��" : "��");
    printf("\n");

    // ����2: ��ջ��������
    printf("2. ��ջ��������:\n");
    printf("���Է��ʿ�ջ��Ԫ��: ");
    ElementType topValue = Top(stack);
    printf("\n���Ե�����ջԪ��: ");
    ElementType popValue = PopStack(stack);
    printf("\n����ɾ����ջ��Ԫ��: ");
    DeleteStackTop(stack);
    printf("\n��ӡ��ջ: ");
    PrintStack(stack);
    printf("\n");

    // ����3: ��ջ����
    printf("3. ��ջ����:\n");
    printf("��ջԪ��: 10, 20, 30, 40, 50\n");
    PushStack(stack, 10);
    PushStack(stack, 20);
    PushStack(stack, 30);
    PushStack(stack, 40);
    PushStack(stack, 50);

    printf("��ǰջ����: ");
    PrintStack(stack);
    printf("ջ�Ƿ�Ϊ��: %s\n", IsEmpty(stack) ? "��" : "��");
    printf("ջ��Ԫ��: %d\n", Top(stack));
    printf("\n");

    // ����4: ��ջ����
    printf("4. ��ջ����:\n");
    printf("����ջ��Ԫ��: %d\n", PopStack(stack));
    printf("��ǰջ����: ");
    PrintStack(stack);
    printf("ջ��Ԫ��: %d\n", Top(stack));
    printf("\n");

    // ����5: ɾ��ջ��Ԫ�ز���
    printf("5. ɾ��ջ��Ԫ�ز���:\n");
    printf("ɾ��ջ��Ԫ��\n");
    DeleteStackTop(stack);
    printf("��ǰջ����: ");
    PrintStack(stack);
    printf("ջ��Ԫ��: %d\n", Top(stack));
    printf("\n");

    // ����6: �ٴ���ջ����
    printf("6. �ٴ���ջ����:\n");
    printf("��ջԪ��: 100, 200\n");
    PushStack(stack, 100);
    PushStack(stack, 200);
    printf("��ǰջ����: ");
    PrintStack(stack);
    printf("ջ��Ԫ��: %d\n", Top(stack));
    printf("\n");

    // ����7: ���ջ����
    printf("7. ���ջ����:\n");
    printf("���ջǰջ�Ƿ�Ϊ��: %s\n", IsEmpty(stack) ? "��" : "��");
    clearStack(stack);
    printf("���ջ��ջ�Ƿ�Ϊ��: %s\n", IsEmpty(stack) ? "��" : "��");
    printf("��ǰջ����: ");
    PrintStack(stack);
    printf("\n");

    // ����8: ��պ��������
    printf("8. ��պ��������:\n");
    printf("���Է��ʿ�ջ��Ԫ��: ");
    topValue = Top(stack);
    printf("\n���Ե�����ջԪ��: ");
    popValue = PopStack(stack);
    printf("\n����ɾ����ջ��Ԫ��: ");
    DeleteStackTop(stack);
    printf("\n");

    // ����9: ����ʹ��ջ
    printf("9. ����ʹ��ջ����:\n");
    printf("��ջԪ��: 5, 15, 25\n");
    PushStack(stack, 5);
    PushStack(stack, 15);
    PushStack(stack, 25);
    printf("��ǰջ����: ");
    PrintStack(stack);
    printf("ջ��Ԫ��: %d\n", Top(stack));
    printf("\n");

    // ����10: ��γ�ջֱ����
    printf("10. ��γ�ջֱ����:\n");
    while (!IsEmpty(stack)) 
    {
        printf("����Ԫ��: %d\n", PopStack(stack));
        printf("��ǰջ����: ");
        PrintStack(stack);
    }
    printf("ջ�Ƿ�Ϊ��: %s\n", IsEmpty(stack) ? "��" : "��");
    printf("\n");

    // �ͷ�ջ�ڴ�
    free(stack);
    printf("������ɣ��ڴ����ͷš�\n");
}

int main() 
{
    testStack();
    return 0;
}