//ջ��������ʵ��
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

// ����ջ�ṹ
struct Node 
{
    ElementType* array;     // �洢ջԪ�ص�����
    int top;        // ջ��ָ�루������
    int capacity;   // ջ������
};
typedef struct Node* ArrayStack;

//��������
ArrayStack createArrayStack(int capacity);  //������ջ
bool IsEmpty(ArrayStack stack);  //�ж�ջ�Ƿ�Ϊ��
bool IsFull(ArrayStack stack);  //�ж�ջ�Ƿ�����
void PushArrayStack(ArrayStack stack, ElementType X);  //��ջ
ElementType PopArrayStack(ArrayStack stack);  //��ջ
ElementType TopArrayStack(ArrayStack stack);  //��ȡջ��Ԫ��
int sizeArrayStack(ArrayStack stack);  //��ȡջ�Ĵ�С
void PrintArrayStack(ArrayStack stack);  //��ӡջ
void clearArrayStack(ArrayStack stack);  //���ջ
void destroyArrayStack(ArrayStack stack);  //����ջ
void resizeArrayStack(ArrayStack stack, int newcapacity);  //��̬����ջ


//������ջ
ArrayStack createArrayStack(int capacity)
{
    ArrayStack stack = (ArrayStack)malloc(sizeof(struct Node));
    if (stack == NULL)
    {
        printf("�ڴ����ʧ�ܣ�������ջʧ�ܣ�\n");
        return NULL;
    }
    stack->array = (ElementType*)malloc(sizeof(ElementType) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    if (stack->array == NULL)
    {
        printf("�ڴ����ʧ�ܣ���������ʧ�ܣ�\n");
        free(stack);
        stack = NULL;
        return NULL;
    }
    return stack;
}

//�ж�ջ�Ƿ�Ϊ��
bool IsEmpty(ArrayStack stack)
{
    return stack->top == -1;
}

//�ж�ջ�Ƿ�����
bool IsFull(ArrayStack stack)
{
    return stack->top == stack->capacity - 1;
}

//��ջ
void PushArrayStack(ArrayStack stack, ElementType X)
{
    if (IsFull(stack))
    {
        printf("ջ�������޷���ջ��\n");
        return;
    }
    stack->array[++stack->top] = X;
}

//��ջ
ElementType PopArrayStack(ArrayStack stack)
{
    if (IsEmpty(stack))
    {
        printf("ջ�ѿգ��޷���ջ��\n");
        return 0;
    }
    return stack->array[stack->top--];
}

//��ȡջ��Ԫ��
ElementType TopArrayStack(ArrayStack stack)
{
    if (IsEmpty(stack))
    {
        printf("ջ�ѿգ��޷���ȡջ��Ԫ�أ�\n");
        return 0;
    }
    return stack->array[stack->top];
}

//��ȡջ�Ĵ�С
int sizeArrayStack(ArrayStack stack)
{
    return stack->top + 1;
}

//��ӡջ
void PrintArrayStack(ArrayStack stack)
{
    if (IsEmpty(stack))
    {
        printf("ջ�ѿգ�\n");
        return 0;
    }
    printf("ջ���ݣ��Ӷ����ף�");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

//���ջ
void clearArrayStack(ArrayStack stack)
{
    stack->top = -1;
}

//����ջ
void destroyArrayStack(ArrayStack stack)
{
    if (stack) 
    {
        if (stack->array) 
        {
            free(stack->array);
            stack->array = NULL;
        }
        free(stack);
        stack = NULL;
    }
}

//��̬����ջ
void resizeArrayStack(ArrayStack stack, int newcapacity)
{
    if (newcapacity <= stack->capacity)
    {
        printf("������̫С���޷����ݣ�\n");
        return;
    }
    ElementType* newarray = (ElementType*)realloc(stack->array, sizeof(ElementType) * newcapacity);
    if (newarray == NULL)
    {
        printf("����ʧ�ܣ�\n");
        return;
    }
    stack->array = newarray;
    stack->capacity = newcapacity;
}

// ���Ժ���
void testArrayStack()
{
    printf("===== ��ʼ����ջ������ʵ�֣�=====\n\n");

    // ����1������ջ
    printf("1. ��������Ϊ3��ջ\n");
    ArrayStack stack = createArrayStack(3);
    if (stack == NULL)
    {
        printf("����ջʧ�ܣ�������ֹ��\n");
        return;
    }
    printf("   ջ�����ɹ���������%d\n", stack->capacity);
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    printf("   ջ�Ƿ�Ϊ�գ�%s\n", IsEmpty(stack) ? "��" : "��");
    PrintArrayStack(stack);
    printf("\n");

    // ����2����ջ��������
    printf("2. ��ջ��������\n");
    printf("   ���Դӿ�ջ����Ԫ�أ�");
    ElementType popped = PopArrayStack(stack);
    printf("\n");

    printf("   ���Ի�ȡ��ջջ��Ԫ�أ�");
    ElementType top = TopArrayStack(stack);
    printf("\n\n");

    // ����3����ջ����
    printf("3. ��ջ��������\n");
    printf("   ��ջԪ�أ�10\n");
    PushArrayStack(stack, 10);
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    printf("   ջ��Ԫ�أ�%d\n", TopArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    printf("   ��ջԪ�أ�20\n");
    PushArrayStack(stack, 20);
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    printf("   ջ��Ԫ�أ�%d\n", TopArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    printf("   ��ջԪ�أ�30\n");
    PushArrayStack(stack, 30);
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    printf("   ջ��Ԫ�أ�%d\n", TopArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    // ����4��ջ������
    printf("4. ջ������\n");
    printf("   ������ջԪ�أ�40������������\n");
    PushArrayStack(stack, 40);
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    // ����5����ջ����
    printf("5. ��ջ��������\n");
    printf("   ��ջԪ�أ�%d\n", PopArrayStack(stack));
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    printf("   ջ��Ԫ�أ�%d\n", TopArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    printf("   ��ջԪ�أ�%d\n", PopArrayStack(stack));
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    printf("   ջ��Ԫ�أ�%d\n", TopArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    printf("   ��ջԪ�أ�%d\n", PopArrayStack(stack));
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    // ����6���ٴο�ջ����
    printf("6. �ٴο�ջ��������\n");
    printf("   ���Դӿ�ջ����Ԫ�أ�");
    popped = PopArrayStack(stack);
    printf("\n");

    printf("   ���Ի�ȡ��ջջ��Ԫ�أ�");
    top = TopArrayStack(stack);
    printf("\n\n");

    // ����7���������ջ
    printf("7. �������ջ\n");
    for (int i = 1; i <= 3; i++)
    {
        PushArrayStack(stack, i * 5);
        printf("   ��ջԪ�أ�%d\n", i * 5);
    }
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    // ����8�����ջ
    printf("8. ���ջ\n");
    clearArrayStack(stack);
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    printf("   ջ�Ƿ�Ϊ�գ�%s\n", IsEmpty(stack) ? "��" : "��");
    PrintArrayStack(stack);
    printf("\n");

    // ����9�����ݲ���
    printf("9. ���ݲ���\n");
    printf("   �������ջ����\n");
    for (int i = 1; i <= 3; i++)
    {
        PushArrayStack(stack, i * 10);
        printf("   ��ջԪ�أ�%d\n", i * 10);
    }
    printf("   ��ǰջ��С��%d��������%d\n", sizeArrayStack(stack), stack->capacity);
    PrintArrayStack(stack);
    printf("\n");

    printf("   �������ݵ�5\n");
    resizeArrayStack(stack, 5);
    printf("   ��ǰջ������%d\n", stack->capacity);
    printf("   ������ջ����Ԫ��\n");
    PushArrayStack(stack, 40);
    PushArrayStack(stack, 50);
    printf("   ��ǰջ��С��%d\n", sizeArrayStack(stack));
    PrintArrayStack(stack);
    printf("\n");

    printf("   �������ݵ��ȵ�ǰ����С��3��\n");
    resizeArrayStack(stack, 3);
    printf("   ��ǰջ������%d\n", stack->capacity);
    printf("\n");

    // ����10������ջ
    printf("10. ����ջ\n");
    destroyArrayStack(stack);
    printf("   ջ������\n");

    printf("\n===== ջ������� =====\n");
}

int main()
{
    testArrayStack();
    return 0;
}
