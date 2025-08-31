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
	return  list->Next;
}

//����ָ��λ��Ԫ��
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
	LinkedList current = list->Next;
	if (list->data == 0)
	{
		list->Next = P;
		list->data++;
	}
	else
	{
		while (current->Next != NULL)
		{
			current = current->Next;
		}
		current->Next = P;
		list->data++;
	}
	
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
		printf("��������%d��Ԫ�أ�\n", list->data);
		LinkedList P = list->Next;
		int i = 1;
		while (P != NULL)
		{
			printf("%d ", P->data);
			i++;
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
		current = NULL;
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
	else
	{
		LinkedList current = list;
		LinkedList ToDelete = list->Next;
		
		while (ToDelete->Next != NULL)
		{
			current = ToDelete;
			ToDelete = ToDelete->Next;
		}
		current->Next = NULL;
		free(ToDelete);
		ToDelete = NULL;
		list->data--;
	}
}

//ָ��λ�ò���
void InsertKth(LinkedList list, ElementType X, int K)
{
	if (K > list->data)
	{
		printf("����û����ô����\n");
	}
	else if (K <= 0)
	{
		printf("�������\n");
	}
	else
	{
		LinkedList P = (LinkedList)malloc(sizeof(struct Node));
		if (P == NULL)
		{
			printf("ָ��λ�ò���������ʧ�ܣ�\n");
			exit(4);
		}
		P->data = X;
		LinkedList current = list;
		K--;
		while (K && current->Next != NULL)
		{
			current = current->Next;
			K--;
		}
		P->Next = current->Next;
		current->Next = P;
		list->data++;
	}
}

//ָ��λ��ɾ��
void DeleteKth(LinkedList list, int K)
{
	if (list->Next == NULL)
	{
		printf("�����ѿգ�������ɾ��\n");
		return;
	}
	else
	{
		if (K > list->data)
		{
			printf("����û����ô����\n");
			return;
		}
		else if (K <= 0)
		{
			printf("�������\n");
			return;
		}
		else
		{
			LinkedList current = list;
			K--;
			while (K && current->Next != NULL)
			{
				current = current->Next;
				K--;
			}
			LinkedList ToDelete = current->Next;
			current->Next = ToDelete->Next;
			free(ToDelete);
			ToDelete = NULL;
			list->data--;
		}
	}
}

//��ȡ������
int GetLength(LinkedList list)
{
	if (list->Next == NULL)
	{
		printf("����Ϊ�գ�\n");
		return 0;
	}
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
	*list = NULL; // �Զ����ⲿָ����ΪNULL
}

// ����ǰ���ڵ�
LinkedList FindPrevious(LinkedList list, ElementType X)
{
	if (list == NULL) {
		printf("����δ��ʼ����\n");
		return NULL;
	}
	if (list->Next == NULL) {
		printf("����Ϊ�գ�û��ǰ���ڵ�ɲ��ң�\n");
		return NULL;
	}
	LinkedList current = list->Next; 
	LinkedList previous = list;      
	while (current != NULL && current->data != X) {
		previous = current;
		current = current->Next;
	}
	if (current != NULL && current->data == X) {
		if (previous == list) {
			printf("�ҵ�ֵΪ %d �Ľڵ㣬���ǵ�һ����Ч�ڵ㣬ǰ������Ԫͷ�ڵ�\n", X);
		}
		return previous;
	}
	printf("δ�ҵ�ֵΪ %d �Ľڵ�\n", X);
	return NULL;
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
	while ((current->Next != NULL) && (current->data != X))
	{
		previous = current;
		current = current->Next;
	}
	if (current->Next == NULL)
	{
		if (current->data == X)
		{
			free(current);
			current = NULL;
			previous->Next = NULL;
			list->data--;
			return;
		}
		else
		{
			printf("������������δ�ҵ���\n");
			return NULL;
		}
	}
	previous->Next = current->Next;
	free(current);
	current = NULL;
	list->data--;
}

void Test_1()
{
	LinkedList list = createList();
	HeadInsert(list, 10);
	EndInsert(list, 15);
	HeadInsert(list, 20);
	EndInsert(list, 30);
	HeadInsert(list, 40);
	EndInsert(list, 50);
	HeadInsert(list, 60);
	EndInsert(list, 70);
	HeadInsert(list, 80);
	HeadInsert(list, 10);
	PrintList(list);  // 10 80 60 40 20 10 15 30 50 70
	
	InsertKth(list, 25, 1);
	InsertKth(list, 35, 12);
	InsertKth(list, 36, 11);
	PrintList(list);  // 25 10 80 60 40 20 10 15 30 50 36 70

	DeleteKth(list, 12);
	DeleteKth(list, 12);
	LinkedList P = FindPrevious(list, 36);
	printf("%d\n", P->data);  //50
	P = FindPrevious(list, 25);
	P = FindPrevious(list, 26);
	DeleteValue(list, 60);  
	DeleteValue(list, 25);
	DeleteValue(list, 36);
	PrintList(list);  // 10 80 40 20 10 15 30 50

	int a = GetLength(list);
	printf("%d\n", a);  // 8
	DestroyList(&list);

	LinkedList list2 = createList();
	HeadDelete(list2);
	EndDelete(list2);
	HeadInsert(list2, 9);
	PrintList(list2);
	HeadDelete(list2);
	PrintList(list2);
	EndInsert(list2, 10);
	PrintList(list2);
	EndDelete(list2);
	PrintList(list2);

}

int main()
{
	Test_1();
	return 0;
}