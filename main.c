//���С�������ʵ��
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

typedef struct ArrayQueue* Queue;
struct ArrayQueue
{
	ElementType* array;
	int front;
	int rear;
	int capacity;
	int size;
};

//���к�������
Queue createQueue(int capacity);  //�����ն���
bool IsEmpty(Queue queue);  //�ж϶����Ƿ�Ϊ��
bool IsFull(Queue queue);  //�ж϶����Ƿ�����
void EnQueue(Queue queue, ElementType X);  //���
ElementType DeQueue(Queue queue);  //����
ElementType HeadQueue(Queue queue);  //��ȡ��ͷԪ��
int sizeQueue(Queue queue);  //��ȡ���д�С
void PrintQueue(Queue queue);  //��ӡ����
void clearQueue(Queue queue);  //��ն���
void destroyQueue(Queue queue);  //���ٶ���
void resizeQueue(Queue queue, int newcapacity);  //��̬���ݶ���

//�����ն���
Queue createQueue(int capacity)
{
	Queue queue = (Queue)malloc(sizeof(struct ArrayQueue));
	if (queue == NULL)
	{
		printf("�����ն��н��ʧ�ܣ�\n");
		return NULL;
	}
	queue->capacity = capacity;
	queue->front = 0;
	queue->rear = -1;
	queue->size = 0;
	queue->array = (ElementType*)malloc(sizeof(ElementType) * capacity);
	if (queue->array == NULL)
	{
		printf("�����ն�������ʧ�ܣ�\n");
		free(queue);
		queue = NULL;
		return NULL;
	}
	return queue;
}

//�ж϶����Ƿ�Ϊ��
bool IsEmpty(Queue queue)
{
	return queue->size == 0;
}

//�ж϶����Ƿ�����
bool IsFull(Queue queue)
{
	return queue->size == queue->capacity;
}

//���
void EnQueue(Queue queue, ElementType X)
{
	if (IsFull(queue))
	{
		printf("����������������ӣ�\n");
		return;
	}
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = X;
	queue->size++;
}

//����
ElementType DeQueue(Queue queue)
{
	if (IsEmpty(queue))
	{
		printf("�����ѿգ����ɳ��ӣ�\n");
		return 0;
	}
	ElementType X = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return X;
}

//��ȡ��ͷԪ��
ElementType HeadQueue(Queue queue)
{
	if (IsEmpty(queue))
	{
		printf("�����ѿգ����ɻ�ȡ��ͷԪ�أ�\n");
		return 0;
	}
	return queue->array[queue->front];
}

//��ȡ���д�С
int sizeQueue(Queue queue)
{
	return queue->size;
}

//��ӡ����
void PrintQueue(Queue queue)
{
	if (IsEmpty(queue))
	{
		printf("����Ϊ�գ�\n");
		return 0;
	}
	printf("����Ԫ�أ�����ͷ��β��");
	int count = queue->size;
	for (int i = 0; i < count; i++)
	{
		printf("%d ", queue->array[(queue->front + i) % queue->capacity]);
	}
	printf("\n");
}

//��ն���
void clearQueue(Queue queue)
{
	queue->size = 0;
	queue->front = 0;
	queue->rear = -1;
}

//���ٶ���
void destroyQueue(Queue queue)
{
	if (queue) 
	{
		if (queue->array) 
		{
			free(queue->array);
			queue->array = NULL;
		}
		free(queue);
		queue = NULL;
	}
}

//��̬���ݶ���
void resizeQueue(Queue queue, int newcapacity)
{
	if (newcapacity <= queue->capacity)
	{
		printf("������̫С���޷�����ԭ�����飡\n");
		return;
	}
	ElementType* newarray = (ElementType*)realloc(queue->array, sizeof(ElementType) * newcapacity);
	if (newarray == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return;
	}
	for (int i = 0; i < queue->size; i++)
	{
		newarray[i] = queue->array[(queue->front + i) % queue->capacity];
	}
	queue->front = 0;
	queue->rear = queue->size - 1;
	queue->array = newarray;
	queue->capacity = newcapacity;
}

// ���Ժ���
void testQueue() 
{
	printf("=== ��ʼ���в��� ===\n\n");

	// ����1����������
	printf("����1���������У�����Ϊ3��\n");
	Queue q = createQueue(3);
	if (q == NULL) 
	{
		printf("��������ʧ�ܣ�������ֹ��\n");
		return;
	}
	printf("���д����ɹ���������%d\n", q->capacity);
	PrintQueue(q);
	printf("\n");

	// ����2���ն��в���
	printf("����2���ն��в���\n");
	printf("�����Ƿ�Ϊ�գ�%s\n", IsEmpty(q) ? "��" : "��");
	printf("�����Ƿ�������%s\n", IsFull(q) ? "��" : "��");
	printf("���д�С��%d\n", sizeQueue(q));
	DeQueue(q);  // ���Դӿն��г���
	HeadQueue(q); // ���Ի�ȡ�ն��еĶ�ͷ
	printf("\n");

	// ����3���������/����
	printf("����3���������/���Ӳ���\n");
	EnQueue(q, 10);
	EnQueue(q, 20);
	EnQueue(q, 30);
	printf("���10,20,30����У�\n");
	PrintQueue(q);
	printf("��ͷԪ�أ�%d\n", HeadQueue(q));
	printf("���д�С��%d\n", sizeQueue(q));
	printf("����Ԫ�أ�%d\n", DeQueue(q));
	printf("���Ӻ���У�\n");
	PrintQueue(q);
	printf("��ͷԪ�أ�%d\n", HeadQueue(q));
	printf("\n");

	// ����4�������������
	printf("����4��������������\n");
	EnQueue(q, 40);  // ��ʱ������20,30,40
	printf("���40����У�\n");
	PrintQueue(q);
	EnQueue(q, 50);  // Ӧ��ʾ��������
	printf("�����Ƿ�������%s\n", IsFull(q) ? "��" : "��");
	printf("\n");

	// ����5��ѭ���������Բ���
	printf("����5��ѭ���������Բ���\n");
	printf("����Ԫ�أ�%d\n", DeQueue(q));  // ����20
	printf("����Ԫ�أ�%d\n", DeQueue(q));  // ����30
	printf("���Ӻ���У�\n");
	PrintQueue(q);
	EnQueue(q, 50);
	EnQueue(q, 60);
	printf("���50,60����У�\n");
	PrintQueue(q);
	printf("���д�С��%d\n", sizeQueue(q));
	printf("��ͷԪ�أ�%d\n", HeadQueue(q));
	printf("\n");

	// ����6����ն���
	printf("����6����ն���\n");
	clearQueue(q);
	printf("��պ���У�\n");
	PrintQueue(q);
	printf("���д�С��%d\n", sizeQueue(q));
	printf("\n");

	// ����7����̬����
	printf("����7����̬���ݲ���\n");
	EnQueue(q, 100);
	EnQueue(q, 200);
	EnQueue(q, 300);
	printf("����ǰ���У�\n");
	PrintQueue(q);
	printf("��ǰ������%d\n", q->capacity);
	resizeQueue(q, 6);  // ���ݵ�6
	printf("���ݺ���У�\n");
	PrintQueue(q);
	printf("��ǰ������%d\n", q->capacity);
	EnQueue(q, 400);
	EnQueue(q, 500);
	EnQueue(q, 600);
	printf("���400,500,600����У�\n");
	PrintQueue(q);
	printf("�����Ƿ�������%s\n", IsFull(q) ? "��" : "��");
	printf("\n");

	// ����8�����ٶ���
	printf("����8�����ٶ���\n");
	destroyQueue(q);
	printf("����������\n");
	// ע�⣺q���ڳ�Ϊ����ָ�룬������Ӧ��ʹ��
	q = NULL;

	printf("\n=== ���в������ ===\n");
}

int main() 
{
	testQueue();
	return 0;
}