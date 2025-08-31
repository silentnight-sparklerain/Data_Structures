#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

//建立结构体
typedef struct Node* LinkedList;
struct Node
{
	ElementType data;
	LinkedList Next;
};


//链表的基本函数的声明
LinkedList createList();  //创建空表
int IsEmpty(LinkedList list);  //判断一个表是不是空表
LinkedList Find(LinkedList list, ElementType X);  //查找指定位置元素
void HeadInsert(LinkedList list, ElementType X);  //头插
void EndInsert(LinkedList list, ElementType X);  //尾插
void PrintList(LinkedList list);  //打印
void HeadDelete(LinkedList list);  //头删
void EndDelete(LinkedList list);  //尾删
void InsertKth(LinkedList list, ElementType X, int K);  //指定位置插入
void DeleteKth(LinkedList list, int K);  //指定位置删除
int GetLength(LinkedList list);  //获取链表长度
void DestroyList(LinkedList* list);  //销毁整个链表
LinkedList FindPrevious(LinkedList list, ElementType X);  //查找前驱结点
void DeleteValue(LinkedList list, ElementType X);  //按值删除结点


//创建带有头结点的空表
LinkedList createList()
{
	LinkedList list = (LinkedList)malloc(sizeof(struct Node));
	if (list == NULL)
	{
		printf("内存分配失败\n");
		exit(1);
	}
	list->Next = NULL;
	list->data = 0;
	return list;
}

//判断一个表是不是空表
int IsEmpty(LinkedList list)
{
	return  list->Next;
}

//查找指定位置元素
LinkedList Find(LinkedList list, ElementType X)
{
	if (list == NULL)
	{
		printf("错误，链表为空！\n");
		return NULL;
	}

	LinkedList P = list->Next;
	while (P != NULL && P->data != X)
	{
		P = P->Next;
	}
	return P;
}

//头插
void HeadInsert(LinkedList list, ElementType X)
{
	LinkedList P = (LinkedList)malloc(sizeof(struct Node));
	if (P == NULL)
	{
		printf("头插申请结点失败！\n");
		exit(2);
	}
	P->data = X;
	P->Next = list->Next;
	list->Next = P;
	list->data++;
}

//尾插
void EndInsert(LinkedList list, ElementType X)
{
	LinkedList P = (LinkedList)malloc(sizeof(struct Node));
	if (P == NULL)
	{
		printf("尾插申请结点失败！\n");
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

//打印
void PrintList(LinkedList list)
{
	if (list->Next == NULL)
	{
		printf("链表为空！\n");
	}
	else
	{
		printf("该链表有%d个元素！\n", list->data);
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

//头删
void HeadDelete(LinkedList list)
{
	if (list->Next == NULL)
	{
		printf("链表已空，不可再头删！\n");
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

//尾删
void EndDelete(LinkedList list)
{
	if (list->Next == NULL)
	{
		printf("链表已空，不可再尾删！\n");
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

//指定位置插入
void InsertKth(LinkedList list, ElementType X, int K)
{
	if (K > list->data)
	{
		printf("链表没有这么长！\n");
	}
	else if (K <= 0)
	{
		printf("输入错误！\n");
	}
	else
	{
		LinkedList P = (LinkedList)malloc(sizeof(struct Node));
		if (P == NULL)
		{
			printf("指定位置插入申请结点失败！\n");
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

//指定位置删除
void DeleteKth(LinkedList list, int K)
{
	if (list->Next == NULL)
	{
		printf("链表已空，不可再删！\n");
		return;
	}
	else
	{
		if (K > list->data)
		{
			printf("链表没有这么长！\n");
			return;
		}
		else if (K <= 0)
		{
			printf("输入错误！\n");
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

//获取链表长度
int GetLength(LinkedList list)
{
	if (list->Next == NULL)
	{
		printf("链表为空！\n");
		return 0;
	}
	return list->data;
}

//销毁整个链表
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
	*list = NULL; // 自动将外部指针设为NULL
}

// 查找前驱节点
LinkedList FindPrevious(LinkedList list, ElementType X)
{
	if (list == NULL) {
		printf("链表未初始化！\n");
		return NULL;
	}
	if (list->Next == NULL) {
		printf("链表为空，没有前驱节点可查找！\n");
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
			printf("找到值为 %d 的节点，它是第一个有效节点，前驱是哑元头节点\n", X);
		}
		return previous;
	}
	printf("未找到值为 %d 的节点\n", X);
	return NULL;
}

//按值删除结点
void DeleteValue(LinkedList list, ElementType X)
{
	if (list->Next == NULL)
	{
		printf("链表已空，不可再删！\n");
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
			printf("输入数据有误，未找到！\n");
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