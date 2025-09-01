#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

//�����ṹ��
typedef struct Node* LinkedList;
struct Node
{
    ElementType data;
    LinkedList Next;
};

//����Ļ�������������
LinkedList createList();  //�����ձ�
int IsEmpty(LinkedList list);  //�ж�һ�����ǲ��ǿձ�
LinkedList Find(LinkedList list, ElementType X);  //����ָ��λ��Ԫ��
void HeadInsert(LinkedList list, ElementType X);  //ͷ��
void EndInsert(LinkedList list, ElementType X);  //β��
void PrintList(LinkedList list);  //��ӡ
void HeadDelete(LinkedList list);  //ͷɾ
void EndDelete(LinkedList list);  //βɾ
void InsertKth(LinkedList list, ElementType X, int K);  //ָ��λ�ò���
void DeleteKth(LinkedList list, int K);  //ָ��λ��ɾ��
int GetLength(LinkedList list);  //��ȡ������
void DestroyList(LinkedList* list);  //������������
LinkedList FindPrevious(LinkedList list, ElementType X);  //����ǰ�����
void DeleteValue(LinkedList list, ElementType X);  //��ֵɾ�����

//��������ͷ���Ŀձ�
LinkedList createList()
{
    LinkedList list = (LinkedList)malloc(sizeof(struct Node));
    if (list == NULL)
    {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    list->Next = NULL;
    list->data = 0;
    return list;
}

//�ж�һ�����ǲ��ǿձ�
int IsEmpty(LinkedList list)
{
    return list->Next == NULL;
}

//����ָ��ֵԪ��
LinkedList Find(LinkedList list, ElementType X)
{
    if (list == NULL)
    {
        printf("��������Ϊ�գ�\n");
        return NULL;
    }

    LinkedList P = list->Next;
    while (P != NULL && P->data != X)
    {
        P = P->Next;
    }
    return P;
}

//ͷ��
void HeadInsert(LinkedList list, ElementType X)
{
    LinkedList P = (LinkedList)malloc(sizeof(struct Node));
    if (P == NULL)
    {
        printf("ͷ��������ʧ�ܣ�\n");
        exit(2);
    }
    P->data = X;
    P->Next = list->Next;
    list->Next = P;
    list->data++;
}

//β��
void EndInsert(LinkedList list, ElementType X)
{
    LinkedList P = (LinkedList)malloc(sizeof(struct Node));
    if (P == NULL)
    {
        printf("β��������ʧ�ܣ�\n");
        exit(3);
    }
    P->data = X;
    P->Next = NULL;

    if (list->Next == NULL)
    {
        list->Next = P;
    }
    else
    {
        LinkedList current = list->Next;
        while (current->Next != NULL)
        {
            current = current->Next;
        }
        current->Next = P;
    }
    list->data++;
}

//��ӡ
void PrintList(LinkedList list)
{
    if (list->Next == NULL)
    {
        printf("����Ϊ�գ�\n");
    }
    else
    {
        printf("��������%d��Ԫ�أ�", list->data);
        LinkedList P = list->Next;
        while (P != NULL)
        {
            printf("%d ", P->data);
            P = P->Next;
        }
        printf("\n");
    }
}

//ͷɾ
void HeadDelete(LinkedList list)
{
    if (list->Next == NULL)
    {
        printf("�����ѿգ�������ͷɾ��\n");
    }
    else
    {
        LinkedList current = list->Next;
        list->Next = current->Next;
        free(current);
        list->data--;
    }
}

//βɾ
void EndDelete(LinkedList list)
{
    if (list->Next == NULL)
    {
        printf("�����ѿգ�������βɾ��\n");
        return;
    }

    LinkedList current = list;
    while (current->Next != NULL && current->Next->Next != NULL)
    {
        current = current->Next;
    }

    free(current->Next);
    current->Next = NULL;
    list->data--;
}

//ָ��λ�ò���
void InsertKth(LinkedList list, ElementType X, int K)
{
    if (K < 1 || K > list->data + 1)
    {
        printf("����λ����Ч��\n");
        return;
    }

    LinkedList P = (LinkedList)malloc(sizeof(struct Node));
    if (P == NULL)
    {
        printf("ָ��λ�ò���������ʧ�ܣ�\n");
        exit(4);
    }
    P->data = X;

    LinkedList current = list;
    for (int i = 1; i < K; i++)
    {
        current = current->Next;
    }

    P->Next = current->Next;
    current->Next = P;
    list->data++;
}

//ָ��λ��ɾ��
void DeleteKth(LinkedList list, int K)
{
    if (list->Next == NULL)
    {
        printf("�����ѿգ�������ɾ��\n");
        return;
    }

    if (K < 1 || K > list->data)
    {
        printf("ɾ��λ����Ч��\n");
        return;
    }

    LinkedList current = list;
    for (int i = 1; i < K; i++)
    {
        current = current->Next;
    }

    LinkedList ToDelete = current->Next;
    current->Next = ToDelete->Next;
    free(ToDelete);
    list->data--;
}

//��ȡ������
int GetLength(LinkedList list)
{
    return list->data;
}

//������������
void DestroyList(LinkedList* list)
{
    if (list == NULL || *list == NULL)
    {
        return;
    }

    LinkedList current = *list;
    LinkedList nextNode;

    while (current != NULL)
    {
        nextNode = current->Next;
        free(current);
        current = nextNode;
    }

    *list = NULL;
}

// ����ǰ���ڵ�
LinkedList FindPrevious(LinkedList list, ElementType X)
{
    if (list == NULL) 
    {
        printf("����δ��ʼ����\n");
        return NULL;
    }

    if (list->Next == NULL) 
    {
        printf("����Ϊ�գ�û��ǰ���ڵ�ɲ��ң�\n");
        return NULL;
    }

    LinkedList current = list->Next;
    LinkedList previous = list;

    // �����һ���ڵ����Ҫ�ҵĽڵ�
    if (current->data == X) 
    {
        printf("�ҵ�ֵΪ %d �Ľڵ㣬���ǵ�һ����Ч�ڵ㣬ǰ������Ԫͷ�ڵ�\n", X);
        return list; // ������Ԫͷ�ڵ�
    }

    // �������������ڵ�
    while (current != NULL && current->data != X) 
    {
        previous = current;
        current = current->Next;
    }

    if (current == NULL) 
    {
        printf("δ�ҵ�ֵΪ %d �Ľڵ�\n", X);
        return NULL;
    }

    return previous;
}


//��ֵɾ�����
void DeleteValue(LinkedList list, ElementType X)
{
    if (list->Next == NULL)
    {
        printf("�����ѿգ�������ɾ��\n");
        return;
    }

    LinkedList current = list->Next;
    LinkedList previous = list;

    while (current != NULL && current->data != X) 
    {
        previous = current;
        current = current->Next;
    }

    if (current == NULL) 
    {
        printf("δ�ҵ�ֵΪ %d �Ľڵ�\n", X);
        return;
    }

    previous->Next = current->Next;
    free(current);
    list->data--;
}

// ���Ժ���
void testLinkedList() 
{
    printf("=== ������� ===\n\n");

    // ����1: ��������
    printf("1. �����������:\n");
    LinkedList list = createList();
    printf("����������ɹ�\n");
    printf("�����Ƿ�Ϊ��: %s\n", IsEmpty(list) ? "��" : "��");
    printf("������: %d\n", GetLength(list));
    PrintList(list);
    printf("\n");

    // ����2: ͷ�巨����
    printf("2. ͷ�巨����:\n");
    HeadInsert(list, 10);
    HeadInsert(list, 20);
    HeadInsert(list, 30);
    PrintList(list);
    printf("������: %d\n", GetLength(list));
    printf("\n");

    // ����3: β�巨����
    printf("3. β�巨����:\n");
    EndInsert(list, 40);
    EndInsert(list, 50);
    EndInsert(list, 60);
    PrintList(list);
    printf("������: %d\n", GetLength(list));
    printf("\n");

    // ����4: ���Ҳ���
    printf("4. ���Ҳ���:\n");
    LinkedList found = Find(list, 30);
    if (found != NULL) 
    {
        printf("�ҵ�ֵΪ 30 �Ľڵ�\n");
    }
    else 
    {
        printf("δ�ҵ�ֵΪ 30 �Ľڵ�\n");
    }

    found = Find(list, 100);
    if (found != NULL) 
    {
        printf("�ҵ�ֵΪ 100 �Ľڵ�\n");
    }
    else 
    {
        printf("δ�ҵ�ֵΪ 100 �Ľڵ�\n");
    }
    printf("\n");

    // ����5: ����ǰ���ڵ����
    printf("5. ����ǰ���ڵ����:\n");
    LinkedList prev = FindPrevious(list, 30);
    if (prev != NULL) 
    {
        printf("ֵΪ 30 �Ľڵ��ǰ���ڵ��ֵΪ: %d\n", prev->data);
    }
    prev = FindPrevious(list, 60);
    if (prev != NULL) 
    {
        printf("ֵΪ 60 �Ľڵ��ǰ���ڵ��ֵΪ: %d\n", prev->data);
    }
    prev = FindPrevious(list, 10);
    if (prev != NULL) 
    {
        printf("ֵΪ 10 �Ľڵ��ǰ���ڵ��ֵΪ: %d\n", prev->data);
    }
    printf("\n");

    // ����6: ָ��λ�ò������
    printf("6. ָ��λ�ò������:\n");
    printf("��λ�� 3 ����ֵ 35:\n");
    InsertKth(list, 35, 3);
    PrintList(list);

    printf("��λ�� 1 ����ֵ 5:\n");
    InsertKth(list, 5, 1);
    PrintList(list);

    printf("��λ�� 9 ����ֵ 70:\n");
    InsertKth(list, 70, 9);
    PrintList(list);

    // ������Чλ�ò���
    printf("������λ�� 0 ����ֵ 0:\n");
    InsertKth(list, 0, 0);

    printf("������λ�� 20 ����ֵ 100:\n");
    InsertKth(list, 100, 20);
    printf("\n");

    // ����7: ͷɾ����
    printf("7. ͷɾ����:\n");
    printf("ɾ��ǰ: ");
    PrintList(list);
    HeadDelete(list);
    printf("ɾ����: ");
    PrintList(list);
    HeadDelete(list);
    printf("�ٴ�ɾ����: ");
    PrintList(list);
    printf("\n");

    // ����8: βɾ����
    printf("8. βɾ����:\n");
    printf("ɾ��ǰ: ");
    PrintList(list);
    EndDelete(list);
    printf("ɾ����: ");
    PrintList(list);
    EndDelete(list);
    printf("�ٴ�ɾ����: ");
    PrintList(list);
    printf("\n");

    // ����9: ָ��λ��ɾ������
    printf("9. ָ��λ��ɾ������:\n");
    printf("ɾ��ǰ: ");
    PrintList(list);
    printf("ɾ��λ�� 3:\n");
    DeleteKth(list, 3);
    PrintList(list);

    printf("ɾ��λ�� 1:\n");
    DeleteKth(list, 1);
    PrintList(list);

    // ������Чλ��ɾ��
    printf("����ɾ��λ�� 0:\n");
    DeleteKth(list, 0);

    printf("����ɾ��λ�� 10:\n");
    DeleteKth(list, 10);
    printf("\n");

    // ����10: ��ֵɾ������
    printf("10. ��ֵɾ������:\n");
    printf("ɾ��ǰ: ");
    PrintList(list);
    printf("ɾ��ֵΪ 40 �Ľڵ�:\n");
    DeleteValue(list, 40);
    PrintList(list);

    printf("ɾ��ֵΪ 35 �Ľڵ�:\n");
    DeleteValue(list, 35);
    PrintList(list);

    printf("����ɾ�������ڵ�ֵ 100:\n");
    DeleteValue(list, 100);
    PrintList(list);
    printf("\n");

    // ����11: �������������
    printf("11. �������������:\n");
    // �������
    while (!IsEmpty(list)) 
    {
        HeadDelete(list);
    }
    printf("��պ������: ");
    PrintList(list);

    printf("�����ڿ�����ͷɾ:\n");
    HeadDelete(list);

    printf("�����ڿ�����βɾ:\n");
    EndDelete(list);

    printf("�����ڿ��������:\n");
    found = Find(list, 10);
    if (found == NULL) 
    {
        printf("��������ҷ���NULL\n");
    }
    printf("\n");

    // ����12: �����������
    printf("12. �����������:\n");
    DestroyList(&list);
    if (list == NULL) 
    {
        printf("�����ѳɹ�����\n");
    }
    else 
    {
        printf("��������ʧ��\n");
    }

    printf("=== ������� ===\n");
}

int main() 
{
    testLinkedList();
    return 0;
}