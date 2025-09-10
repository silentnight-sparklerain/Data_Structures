//堆——完全二叉树实现
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define Maxdata 100000;  //定义“哨兵”的值

typedef int ElementType;

//最大堆的结构体
typedef struct Node* Heap;
struct Node
{
	ElementType* data;  //存储堆元素的数组
	int size;  //堆的当前元素个数
	int capacity;  //最大堆的容量
};

//函数声明
Heap createHeap(int capacity);  //建立一个堆
bool isFull(Heap heap);  //判断堆是否已满
bool isEmpty(Heap heap);  //判断堆是否为空
Heap insertData(Heap heap, ElementType X);  //插入元素
ElementType deleteData(Heap heap);  //删除元素（从堆中取出最大的元素）
int getHeight(Heap heap);  //获取高度
int getSize(Heap heap);  //获取元素个数
void printHeap(Heap heap);  //打印堆
void freeHeap(Heap heap);  //释放堆

//建立一个堆
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
	heap->data[0] = Maxdata;  //定义数组的第一个元素为“哨兵”，比数组里面所有元素都大
	return heap;
}

//判断堆是否已满
bool isFull(Heap heap)
{
	return heap->size == heap->capacity;
}

//判断堆是否为空
bool isEmpty(Heap heap)
{
	return heap->size == 0;
}

//插入元素
Heap insertData(Heap heap, ElementType X)
{
	//1.判断堆是否已满
	if (isFull(heap))
	{
		printf("堆已满！不可再插入元素！\n");
		return heap;
	}
	//2.判断堆是否为空
	if (isEmpty(heap))
	{
		heap->data[1] = X;
		heap->size++;
		return heap;
	}
	//3.找到要插入的位置
	int i = ++heap->size;
	for (i; X > heap->data[i / 2] && i > 1; i = i / 2)
	{
		heap->data[i] = heap->data[i / 2];
	}
	//4.插入元素并返回
	heap->data[i] = X;
	return heap;
}

//删除元素（从堆中取出最大的元素）
ElementType deleteData(Heap heap)
{
	if (isEmpty(heap))
	{
		printf("堆已空！不可删除元素！\n");
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

//获取高度
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

//获取元素个数
int getSize(Heap heap)
{
	return heap->size;
}

//打印堆
void printHeap(Heap heap)
{
	printf("打印堆：");
	for (int i = 1; i <= heap->size; i++)
	{
		printf("%d ", heap->data[i]);
	}
	printf("\n");
}

//释放堆
void freeHeap(Heap heap)
{
	free(heap->data);
	heap->data = NULL;
	free(heap);
	heap = NULL;
}

// 测试函数
void testHeap() 
{
	printf("=== 开始测试堆 ===\n");

	// 测试1: 创建堆
	printf("\n1. 测试创建堆:\n");
	Heap heap = createHeap(10);
	if (heap != NULL) 
	{
		printf("堆创建成功，容量: %d\n", heap->capacity);
	}
	else 
	{
		printf("堆创建失败\n");
		return;
	}

	// 测试2: 测试空堆操作
	printf("\n2. 测试空堆操作:\n");
	printf("堆是否为空: %s\n", isEmpty(heap) ? "是" : "否");
	printf("尝试从空堆删除元素: ");
	ElementType deleted = deleteData(heap);
	if (deleted == -1) 
	{
		printf("正确返回错误值\n");
	}

	// 测试3: 插入元素
	printf("\n3. 测试插入元素:\n");
	int testData[] = { 10, 20, 15, 30, 5, 25, 35, 40, 12, 8 };
	for (int i = 0; i < 10; i++) 
	{
		heap = insertData(heap, testData[i]);
		printf("插入 %d 后堆大小: %d\n", testData[i], getSize(heap));
	}
	printHeap(heap);
	printf("堆高度: %d\n", getHeight(heap));

	// 测试4: 测试堆满情况
	printf("\n4. 测试堆满情况:\n");
	printf("堆是否已满: %s\n", isFull(heap) ? "是" : "否");
	printf("尝试插入第11个元素: ");
	heap = insertData(heap, 50); // 应该失败

	// 测试5: 删除元素
	printf("\n5. 测试删除元素:\n");
	for (int i = 0; i < 5; i++) 
	{
		ElementType max = deleteData(heap);
		printf("删除的最大元素: %d, 剩余大小: %d\n", max, getSize(heap));
	}
	printHeap(heap);

	// 测试6: 再次插入和删除
	printf("\n6. 再次插入和删除:\n");
	heap = insertData(heap, 100);
	heap = insertData(heap, 1);
	printHeap(heap);

	while (!isEmpty(heap)) 
	{
		ElementType max = deleteData(heap);
		printf("删除: %d, 剩余大小: %d\n", max, getSize(heap));
	}

	// 测试7: 释放堆
	printf("\n7. 释放堆:\n");
	freeHeap(heap);
	printf("堆已释放\n");

	printf("\n=== 测试完成 ===\n");
}

int main() 
{
	testHeap();
	return 0;
}