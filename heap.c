//�ѡ�����ȫ������ʵ��
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define Maxdata 100000;  //���塰�ڱ�����ֵ

typedef int ElementType;

//���ѵĽṹ��
typedef struct Node* Heap;
struct Node
{
	ElementType* data;  //�洢��Ԫ�ص�����
	int size;  //�ѵĵ�ǰԪ�ظ���
	int capacity;  //���ѵ�����
};

//��������
Heap createHeap(int capacity);  //����һ����
bool isFull(Heap heap);  //�ж϶��Ƿ�����
bool isEmpty(Heap heap);  //�ж϶��Ƿ�Ϊ��
Heap insertData(Heap heap, ElementType X);  //����Ԫ��
ElementType deleteData(Heap heap);  //ɾ��Ԫ�أ��Ӷ���ȡ������Ԫ�أ�
int getHeight(Heap heap);  //��ȡ�߶�
int getSize(Heap heap);  //��ȡԪ�ظ���
void printHeap(Heap heap);  //��ӡ��
void freeHeap(Heap heap);  //�ͷŶ�

//����һ����
Heap createHeap(int capacity)
{
	Heap heap = (Heap)malloc(sizeof(struct Node));
	if (heap == NULL)
	{
		return NULL;
	}
	heap->size = 0;
	heap->capacity = capacity;
	heap->data = (ElementType*)malloc(sizeof(ElementType) * (capacity + 1));
	heap->data[0] = Maxdata;  //��������ĵ�һ��Ԫ��Ϊ���ڱ�������������������Ԫ�ض���
	return heap;
}

//�ж϶��Ƿ�����
bool isFull(Heap heap)
{
	return heap->size == heap->capacity;
}

//�ж϶��Ƿ�Ϊ��
bool isEmpty(Heap heap)
{
	return heap->size == 0;
}

//����Ԫ��
Heap insertData(Heap heap, ElementType X)
{
	//1.�ж϶��Ƿ�����
	if (isFull(heap))
	{
		printf("�������������ٲ���Ԫ�أ�\n");
		return heap;
	}
	//2.�ж϶��Ƿ�Ϊ��
	if (isEmpty(heap))
	{
		heap->data[1] = X;
		heap->size++;
		return heap;
	}
	//3.�ҵ�Ҫ�����λ��
	int i = ++heap->size;
	for (i; X > heap->data[i / 2] && i > 1; i = i / 2)
	{
		heap->data[i] = heap->data[i / 2];
	}
	//4.����Ԫ�ز�����
	heap->data[i] = X;
	return heap;
}

//ɾ��Ԫ�أ��Ӷ���ȡ������Ԫ�أ�
ElementType deleteData(Heap heap)
{
	if (isEmpty(heap))
	{
		printf("���ѿգ�����ɾ��Ԫ�أ�\n");
		return -1;
	}
	ElementType Max = heap->data[1];
	int parent = 0, child = 0;
	ElementType temp = heap->data[heap->size--];
	for (parent = 1; parent * 2 <= heap->size; parent = child)
	{
		child = parent * 2;
		if (child != heap->size && heap->data[child] < heap->data[child + 1])
		{
			child++;
		}
		if (temp >= heap->data[child])
		{
			break;
		}
		else
		{
			heap->data[parent] = heap->data[child];
		}
	}
	heap->data[parent] = temp;
	return Max;
 }

//��ȡ�߶�
int getHeight(Heap heap)
{
	if (heap->size == 0)
	{
		return 0;
	}
	int height = 1, num = 1;
	while (num * 2 < heap->size)
	{
		num = num * 2;
		height++;
	}
	return height;
}

//��ȡԪ�ظ���
int getSize(Heap heap)
{
	return heap->size;
}

//��ӡ��
void printHeap(Heap heap)
{
	printf("��ӡ�ѣ�");
	for (int i = 1; i <= heap->size; i++)
	{
		printf("%d ", heap->data[i]);
	}
	printf("\n");
}

//�ͷŶ�
void freeHeap(Heap heap)
{
	free(heap->data);
	heap->data = NULL;
	free(heap);
	heap = NULL;
}

// ���Ժ���
void testHeap() 
{
	printf("=== ��ʼ���Զ� ===\n");

	// ����1: ������
	printf("\n1. ���Դ�����:\n");
	Heap heap = createHeap(10);
	if (heap != NULL) 
	{
		printf("�Ѵ����ɹ�������: %d\n", heap->capacity);
	}
	else 
	{
		printf("�Ѵ���ʧ��\n");
		return;
	}

	// ����2: ���ԿնѲ���
	printf("\n2. ���ԿնѲ���:\n");
	printf("���Ƿ�Ϊ��: %s\n", isEmpty(heap) ? "��" : "��");
	printf("���Դӿն�ɾ��Ԫ��: ");
	ElementType deleted = deleteData(heap);
	if (deleted == -1) 
	{
		printf("��ȷ���ش���ֵ\n");
	}

	// ����3: ����Ԫ��
	printf("\n3. ���Բ���Ԫ��:\n");
	int testData[] = { 10, 20, 15, 30, 5, 25, 35, 40, 12, 8 };
	for (int i = 0; i < 10; i++) 
	{
		heap = insertData(heap, testData[i]);
		printf("���� %d ��Ѵ�С: %d\n", testData[i], getSize(heap));
	}
	printHeap(heap);
	printf("�Ѹ߶�: %d\n", getHeight(heap));

	// ����4: ���Զ������
	printf("\n4. ���Զ������:\n");
	printf("���Ƿ�����: %s\n", isFull(heap) ? "��" : "��");
	printf("���Բ����11��Ԫ��: ");
	heap = insertData(heap, 50); // Ӧ��ʧ��

	// ����5: ɾ��Ԫ��
	printf("\n5. ����ɾ��Ԫ��:\n");
	for (int i = 0; i < 5; i++) 
	{
		ElementType max = deleteData(heap);
		printf("ɾ�������Ԫ��: %d, ʣ���С: %d\n", max, getSize(heap));
	}
	printHeap(heap);

	// ����6: �ٴβ����ɾ��
	printf("\n6. �ٴβ����ɾ��:\n");
	heap = insertData(heap, 100);
	heap = insertData(heap, 1);
	printHeap(heap);

	while (!isEmpty(heap)) 
	{
		ElementType max = deleteData(heap);
		printf("ɾ��: %d, ʣ���С: %d\n", max, getSize(heap));
	}

	// ����7: �ͷŶ�
	printf("\n7. �ͷŶ�:\n");
	freeHeap(heap);
	printf("�����ͷ�\n");

	printf("\n=== ������� ===\n");
}

int main() 
{
	testHeap();
	return 0;
}