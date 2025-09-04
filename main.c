//���С�������ʵ��
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

//������ṹ��
typedef struct Node* QueueNode;
struct Node
{
	ElementType data;
	QueueNode Next;
};

//������нṹ��
typedef struct linked* LinkedQueue;
struct linked
{
	QueueNode front;  //��ͷָ��
	QueueNode rear;  //��βָ��
	int size;  //���д�С
};


//���к�������
LinkedQueue createQueue();  //����һ������
bool IsEmpty(LinkedQueue queue);  //�ж϶����Ƿ�Ϊ��
int sizeQueue(LinkedQueue queue);  //��ȡ���д�С
void EnQueue(LinkedQueue queue, ElementType X);  //���
ElementType DeQueue(LinkedQueue queue);  //����
ElementType HeadQueue(LinkedQueue queue);  //��ȡ��ͷԪ��
void PrintQueue(LinkedQueue queue);  //��ӡ����
void clearQueue(LinkedQueue queue);  //��ն���


//����һ������
LinkedQueue createQueue()
{
	LinkedQueue queue = (LinkedQueue)malloc(sizeof(LinkedQueue));
	if (queue == NULL)
	{
		printf("�������ʧ�ܣ�\n");
		return NULL;
	}
	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;
	return queue;
}

//�ж϶����Ƿ�Ϊ��
bool IsEmpty(LinkedQueue queue)
{
	return queue->front == NULL;
}

//��ȡ���д�С
int sizeQueue(LinkedQueue queue)
{
	return queue->size;
}

//���
void EnQueue(LinkedQueue queue, ElementType X)
{
	QueueNode newnode = (QueueNode)malloc(sizeof(struct Node));
	if (newnode == NULL)
	{
		printf("������ʧ�ܣ�\n");
		return;
	}
	newnode->data = X;
	newnode->Next = NULL;
	if (IsEmpty(queue))
	{
		queue->front = newnode;
		queue->rear = newnode;
	}
	else
	{
		queue->rear->Next = newnode;
		queue->rear = newnode;
	}
	queue->size++;
}

//����
ElementType DeQueue(LinkedQueue queue)
{
	if (IsEmpty(queue))
	{
		printf("���ѿգ��޷����ӣ�\n");
		return 0;
	}
	QueueNode current = queue->front;
	ElementType X = current->data;
	queue->front = current->Next;
	if (queue->front == NULL)
	{
		queue->rear = NULL;
	}
	free(current);
	current = NULL;
	queue->size--;
	return X;
}

//��ȡ��ͷԪ��
ElementType HeadQueue(LinkedQueue queue)
{
	if (IsEmpty(queue))
	{
		printf("���ѿգ��޷���ȡ��ͷԪ�أ�\n");
		return 0;
	}
	return queue->front->data;
}

//��ӡ����
void PrintQueue(LinkedQueue queue)
{
	if (IsEmpty(queue))
	{
		printf("���ѿգ�\n");
		return;
	}
	QueueNode current = queue->front;
	printf("�������ݣ�����ͷ��β��");
	while (current != NULL)
	{
		printf("%d ", current->data);
		current = current->Next;
	}
	printf("\n");
}

//��ն���
void clearQueue(LinkedQueue queue)
{
	while (!IsEmpty(queue))
	{
		DeQueue(queue);
	}
}

// ���Ժ���
void test() 
{
	LinkedQueue queue = createQueue();
	if (queue == NULL) 
	{
		printf("��������ʧ�ܣ�\n");
		return -1;
	}
	printf("���д����ɹ���\n");

	// ���Կն��в���
	printf("\n1. ���Կն���:\n");
	printf("�����Ƿ�Ϊ��: %s\n", IsEmpty(queue) ? "��" : "��");
	printf("���д�С: %d\n", sizeQueue(queue));
	printf("���Ի�ȡ��ͷԪ��: ");
	ElementType head = HeadQueue(queue); // Ӧ��ӡ������Ϣ
	printf("���Գ���: ");
	ElementType deq = DeQueue(queue);    // Ӧ��ӡ������Ϣ

	// ������Ӳ���
	printf("\n2. ������Ӳ���:\n");
	EnQueue(queue, 10);
	EnQueue(queue, 20);
	EnQueue(queue, 30);
	printf("��� 10, 20, 30 ����д�С: %d\n", sizeQueue(queue));
	PrintQueue(queue); // Ӧ���: 10 20 30

	// ���Ի�ȡ��ͷԪ��
	printf("\n3. ���Ի�ȡ��ͷԪ��:\n");
	head = HeadQueue(queue);
	printf("��ͷԪ��: %d\n", head);

	// ���Գ��Ӳ���
	printf("\n4. ���Գ��Ӳ���:\n");
	deq = DeQueue(queue);
	printf("����Ԫ��: %d\n", deq);
	printf("���Ӻ���д�С: %d\n", sizeQueue(queue));
	PrintQueue(queue); // Ӧ���: 20 30

	// �ٴ���Ӻͳ��Ӳ���
	printf("\n5. �ٴ���Ӻͳ��Ӳ���:\n");
	EnQueue(queue, 40);
	printf("��� 40 ��:\n");
	PrintQueue(queue); // Ӧ���: 20 30 40

	deq = DeQueue(queue);
	printf("����Ԫ��: %d\n", deq);
	deq = DeQueue(queue);
	printf("����Ԫ��: %d\n", deq);
	printf("���γ��Ӻ���д�С: %d\n", sizeQueue(queue));
	PrintQueue(queue); // Ӧ���: 40

	// ������ն���
	printf("\n6. ������ն���:\n");
	clearQueue(queue);
	printf("��պ���д�С: %d\n", sizeQueue(queue));
	printf("�����Ƿ�Ϊ��: %s\n", IsEmpty(queue) ? "��" : "��");

	// ���Ա߽��������պ��ٴβ���
	printf("\n7. ���Ա߽��������պ������:\n");
	printf("���Ի�ȡ��ͷԪ��: ");
	head = HeadQueue(queue); // Ӧ��ӡ������Ϣ
	printf("���Գ���: ");
	deq = DeQueue(queue);    // Ӧ��ӡ������Ϣ

	// ������Ӳ��Զ����Ƿ���������
	printf("\n8. ������Ӳ���:\n");
	EnQueue(queue, 50);
	EnQueue(queue, 60);
	printf("������� 50, 60 ����д�С: %d\n", sizeQueue(queue));
	PrintQueue(queue); // Ӧ���: 50 60

	// �ͷŶ����ڴ�
	printf("\n9. �ͷŶ����ڴ�:\n");
	clearQueue(queue); // ��ն����ͷ����нڵ�
	printf("�����ڴ����ͷš�\n");
}

int main()
{
	test();
	return 0;
}