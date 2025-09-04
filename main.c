//队列——数组实现
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

//队列函数声明
Queue createQueue(int capacity);  //建立空队列
bool IsEmpty(Queue queue);  //判断队列是否为空
bool IsFull(Queue queue);  //判断队列是否已满
void EnQueue(Queue queue, ElementType X);  //入队
ElementType DeQueue(Queue queue);  //出队
ElementType HeadQueue(Queue queue);  //获取队头元素
int sizeQueue(Queue queue);  //获取队列大小
void PrintQueue(Queue queue);  //打印队列
void clearQueue(Queue queue);  //清空队列
void destroyQueue(Queue queue);  //销毁队列
void resizeQueue(Queue queue, int newcapacity);  //动态扩容队列

//建立空队列
Queue createQueue(int capacity)
{
	Queue queue = (Queue)malloc(sizeof(struct ArrayQueue));
	if (queue == NULL)
	{
		printf("建立空队列结点失败！\n");
		return NULL;
	}
	queue->capacity = capacity;
	queue->front = 0;
	queue->rear = -1;
	queue->size = 0;
	queue->array = (ElementType*)malloc(sizeof(ElementType) * capacity);
	if (queue->array == NULL)
	{
		printf("建立空队列数组失败！\n");
		free(queue);
		queue = NULL;
		return NULL;
	}
	return queue;
}

//判断队列是否为空
bool IsEmpty(Queue queue)
{
	return queue->size == 0;
}

//判断队列是否已满
bool IsFull(Queue queue)
{
	return queue->size == queue->capacity;
}

//入队
void EnQueue(Queue queue, ElementType X)
{
	if (IsFull(queue))
	{
		printf("队列已满，不可入队！\n");
		return;
	}
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = X;
	queue->size++;
}

//出队
ElementType DeQueue(Queue queue)
{
	if (IsEmpty(queue))
	{
		printf("队列已空，不可出队！\n");
		return 0;
	}
	ElementType X = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return X;
}

//获取队头元素
ElementType HeadQueue(Queue queue)
{
	if (IsEmpty(queue))
	{
		printf("队列已空，不可获取队头元素！\n");
		return 0;
	}
	return queue->array[queue->front];
}

//获取队列大小
int sizeQueue(Queue queue)
{
	return queue->size;
}

//打印队列
void PrintQueue(Queue queue)
{
	if (IsEmpty(queue))
	{
		printf("队列为空！\n");
		return 0;
	}
	printf("队列元素：（从头到尾）");
	int count = queue->size;
	for (int i = 0; i < count; i++)
	{
		printf("%d ", queue->array[(queue->front + i) % queue->capacity]);
	}
	printf("\n");
}

//清空队列
void clearQueue(Queue queue)
{
	queue->size = 0;
	queue->front = 0;
	queue->rear = -1;
}

//销毁队列
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

//动态扩容队列
void resizeQueue(Queue queue, int newcapacity)
{
	if (newcapacity <= queue->capacity)
	{
		printf("新容量太小，无法容纳原有数组！\n");
		return;
	}
	ElementType* newarray = (ElementType*)realloc(queue->array, sizeof(ElementType) * newcapacity);
	if (newarray == NULL)
	{
		printf("内存分配失败！\n");
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

// 测试函数
void testQueue() 
{
	printf("=== 开始队列测试 ===\n\n");

	// 测试1：创建队列
	printf("测试1：创建队列（容量为3）\n");
	Queue q = createQueue(3);
	if (q == NULL) 
	{
		printf("创建队列失败，测试终止！\n");
		return;
	}
	printf("队列创建成功，容量：%d\n", q->capacity);
	PrintQueue(q);
	printf("\n");

	// 测试2：空队列操作
	printf("测试2：空队列操作\n");
	printf("队列是否为空：%s\n", IsEmpty(q) ? "是" : "否");
	printf("队列是否已满：%s\n", IsFull(q) ? "是" : "否");
	printf("队列大小：%d\n", sizeQueue(q));
	DeQueue(q);  // 尝试从空队列出队
	HeadQueue(q); // 尝试获取空队列的队头
	printf("\n");

	// 测试3：正常入队/出队
	printf("测试3：正常入队/出队操作\n");
	EnQueue(q, 10);
	EnQueue(q, 20);
	EnQueue(q, 30);
	printf("入队10,20,30后队列：\n");
	PrintQueue(q);
	printf("队头元素：%d\n", HeadQueue(q));
	printf("队列大小：%d\n", sizeQueue(q));
	printf("出队元素：%d\n", DeQueue(q));
	printf("出队后队列：\n");
	PrintQueue(q);
	printf("队头元素：%d\n", HeadQueue(q));
	printf("\n");

	// 测试4：队列已满情况
	printf("测试4：队列已满测试\n");
	EnQueue(q, 40);  // 此时队列有20,30,40
	printf("入队40后队列：\n");
	PrintQueue(q);
	EnQueue(q, 50);  // 应显示队列已满
	printf("队列是否已满：%s\n", IsFull(q) ? "是" : "否");
	printf("\n");

	// 测试5：循环队列特性测试
	printf("测试5：循环队列特性测试\n");
	printf("出队元素：%d\n", DeQueue(q));  // 出队20
	printf("出队元素：%d\n", DeQueue(q));  // 出队30
	printf("出队后队列：\n");
	PrintQueue(q);
	EnQueue(q, 50);
	EnQueue(q, 60);
	printf("入队50,60后队列：\n");
	PrintQueue(q);
	printf("队列大小：%d\n", sizeQueue(q));
	printf("队头元素：%d\n", HeadQueue(q));
	printf("\n");

	// 测试6：清空队列
	printf("测试6：清空队列\n");
	clearQueue(q);
	printf("清空后队列：\n");
	PrintQueue(q);
	printf("队列大小：%d\n", sizeQueue(q));
	printf("\n");

	// 测试7：动态扩容
	printf("测试7：动态扩容测试\n");
	EnQueue(q, 100);
	EnQueue(q, 200);
	EnQueue(q, 300);
	printf("扩容前队列：\n");
	PrintQueue(q);
	printf("当前容量：%d\n", q->capacity);
	resizeQueue(q, 6);  // 扩容到6
	printf("扩容后队列：\n");
	PrintQueue(q);
	printf("当前容量：%d\n", q->capacity);
	EnQueue(q, 400);
	EnQueue(q, 500);
	EnQueue(q, 600);
	printf("入队400,500,600后队列：\n");
	PrintQueue(q);
	printf("队列是否已满：%s\n", IsFull(q) ? "是" : "否");
	printf("\n");

	// 测试8：销毁队列
	printf("测试8：销毁队列\n");
	destroyQueue(q);
	printf("队列已销毁\n");
	// 注意：q现在成为悬空指针，后续不应再使用
	q = NULL;

	printf("\n=== 队列测试完成 ===\n");
}

int main() 
{
	testQueue();
	return 0;
}