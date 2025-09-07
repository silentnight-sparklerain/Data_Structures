#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

typedef struct Node* AVLTree;
struct Node
{
	ElementType data;
	AVLTree left;
	AVLTree right;
	int height;  //结点高度
};

//函数声明
int getHeight(AVLTree tree);  //获取高度
int getMax(int a, int b);  //获取两个整数中的最大值
AVLTree createTree(ElementType X);  //建立新树
AVLTree rightRotate(AVLTree tree);  //右旋
AVLTree leftRotate(AVLTree tree);  //左旋
int getBalance(AVLTree tree);  //获取结点的平衡因子
AVLTree insertNode(AVLTree tree, ElementType X);  //插入新结点
AVLTree minNode(AVLTree tree);  //查找最小值结点 
AVLTree deleteNode(AVLTree tree, ElementType X);  //按值删除结点
void PrintMidOT(AVLTree tree);  //中序遍历打印
void PrintPreOT(AVLTree tree);  //前序遍历打印
void PrintPostOT(AVLTree tree);  //后序遍历打印
AVLTree searchNode(AVLTree tree, ElementType X);  //按值查找
void freeAVLTree(AVLTree tree);  //释放AVL树



//获取高度
int getHeight(AVLTree tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	return tree->height;
}

//获取两个整数中的最大值
int getMax(int a, int b)
{
	return (a > b) ? a : b;
}

//建立新树
AVLTree createTree(ElementType X)
{
	AVLTree root = (AVLTree)malloc(sizeof(struct Node));
	if (root == NULL)
	{
		printf("申请根结点失败，建立新树失败！\n");
		return NULL;
	}
	root->data = X;
	root->height = 1;
	root->right = NULL;
	root->left = NULL;
	return root;
}

//右旋
AVLTree rightRotate(AVLTree tree)
{
	AVLTree tree_left = tree->left;
	AVLTree tree_left_right = tree->left->right;
	tree_left->right = tree;
	tree->left = tree_left_right;
	//修改高度
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	tree_left->height = getMax(getHeight(tree_left->left), getHeight(tree_left->right)) + 1;
	return tree_left;
}

//左旋
AVLTree leftRotate(AVLTree tree)
{
	AVLTree tree_right = tree->right;
	AVLTree tree_right_left = tree->right->left;
	tree_right->left = tree;
	tree->right = tree_right_left;
	//修改高度
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	tree_right->height = getMax(getHeight(tree_right->left), getHeight(tree_right->right)) + 1;
	return tree_right;
}

//获取结点的平衡因子
int getBalance(AVLTree tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	return getHeight(tree->left) - getHeight(tree->right);
}

//插入新结点
AVLTree insertNode(AVLTree tree, ElementType X)
{
	//1.先执行标准的插入
	if (tree == NULL)
	{
		return createTree(X);
	}
	if (tree->data > X)
	{
		tree->left = insertNode(tree->left, X);
	}
	else if (tree->data < X)
	{
		tree->right = insertNode(tree->right, X);
	}
	else
	{
		return tree;  //不允许树中有重复结点
	}
	//2.更新结点的高度
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	//3.检查是否引起失衡
	int balance = getBalance(tree);
	//4.若失衡，进行旋转调整
	//右右情况，左旋
	if (balance < -1 && tree->right->data < X)
	{
		return leftRotate(tree);
	}
	//左左情况，右旋
	if (balance > 1 && tree->left->data > X)
	{
		return rightRotate(tree);
	}
	//右左情况，右左旋
	if (balance < -1 && tree->right->data > X)
	{
		tree->right = rightRotate(tree->right);
		return leftRotate(tree);
	}
	//左右情况，左右旋
	if (balance > 1 && tree->left->data < X)
	{
		tree->left = leftRotate(tree->left);
		return rightRotate(tree);
	}
	return tree;
}

//查找最小值结点
AVLTree minNode(AVLTree tree)
{
	AVLTree current = tree;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

//按值删除结点
AVLTree deleteNode(AVLTree tree, ElementType X)
{
	//1.先执行标准的删除
	if (tree == NULL)
	{
		return tree;
	}
	if (tree->data > X)
	{
		return deleteNode(tree->left, X);
	}
	else if (tree->data < X)
	{
		return deleteNode(tree->right, X);
	}
	else
	{
		//已找到要删除的结点
		//结点有一个子结点或无子结点
		if (tree->left == NULL || tree->right == NULL)
		{
			if (tree->left == NULL)
			{
				AVLTree current = tree->right;
				free(tree);
				tree = NULL;
				return current;
			}
			else
			{
				AVLTree current = tree->left;
				free(tree);
				tree = NULL;
				return current;
			}
		}
		//结点有两个子结点
		else
		{
			AVLTree current = minNode(tree->right);
			tree->data = current->data;
			tree->right = deleteNode(tree->right, current->data);
		}
	}
	//如果树只有一个结点，删完直接返回
	if (tree == NULL)
	{
		return tree;
	}
	//2.更新结点的高度
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	//3.检查是否引起失衡
	int balance = getBalance(tree);
	//4.若失衡，进行旋转调整
	//右右情况，左旋
	if (balance < -1 && tree->right->data < X)
	{
		return leftRotate(tree);
	}
	//左左情况，右旋
	if (balance > 1 && tree->left->data > X)
	{
		return rightRotate(tree);
	}
	//右左情况，右左旋
	if (balance < -1 && tree->right->data > X)
	{
		tree->right = rightRotate(tree->right);
		return leftRotate(tree);
	}
	//左右情况，左右旋
	if (balance > 1 && tree->left->data < X)
	{
		tree->left = leftRotate(tree->left);
		return rightRotate(tree);
	}
	return tree;
}


//中序遍历打印
void PrintMidOT(AVLTree tree)
{
	if (tree != NULL)
	{
		PrintMidOT(tree->left);
		printf("%d ", tree->data);
		PrintMidOT(tree->right);
	}
}

//前序遍历打印
void PrintPreOT(AVLTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->data);
		PrintPreOT(tree->left);
		PrintPreOT(tree->right);
	}
}

//后序遍历打印
void PrintPostOT(AVLTree tree)
{
	if (tree != NULL)
	{
		PrintPostOT(tree->left);
		PrintPostOT(tree->right);
		printf("%d ", tree->data);
	}
}

//按值查找
AVLTree searchNode(AVLTree tree, ElementType X)
{
	if (tree == NULL)
	{
		return tree;
	}
	if (tree->data < X)
	{
		return searchNode(tree->right, X);
	}
	else if (tree->data > X)
	{
		return searchNode(tree->left, X);
	}
	else
	{
		return tree;
	}
}

//释放AVL树
void freeAVLTree(AVLTree tree)
{
	if (tree != NULL)
	{
		freeAVLTree(tree->left);
		freeAVLTree(tree->right);
		free(tree);
		tree = NULL;
	}
}

//测试函数
void testAVLTree() 
{
	AVLTree root = NULL;
	printf("=== AVL树测试 ===\n\n");

	// 测试1: 插入节点
	printf("1. 插入节点测试:\n");
	root = insertNode(root, 10);
	root = insertNode(root, 20);
	root = insertNode(root, 30);
	root = insertNode(root, 40);
	root = insertNode(root, 50);
	root = insertNode(root, 25);

	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("前序遍历: "); PrintPreOT(root); printf("\n");
	printf("后序遍历: "); PrintPostOT(root); printf("\n");
	printf("树高度: %d\n", getHeight(root));
	printf("根节点平衡因子: %d\n", getBalance(root));
	printf("\n");

	// 测试2: 搜索节点
	printf("2. 搜索节点测试:\n");
	AVLTree searchResult = searchNode(root, 30);
	if (searchResult != NULL) {
		printf("找到节点 30\n");
	}
	else {
		printf("未找到节点 30\n");
	}

	searchResult = searchNode(root, 100);
	if (searchResult != NULL) {
		printf("找到节点 100\n");
	}
	else {
		printf("未找到节点 100\n");
	}
	printf("\n");

	// 测试3: 删除节点
	printf("3. 删除节点测试:\n");
	printf("删除节点 10:\n");
	root = deleteNode(root, 10);
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("树高度: %d\n", getHeight(root));
	printf("根节点平衡因子: %d\n", getBalance(root));

	printf("删除节点 50:\n");
	root = deleteNode(root, 50);
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("树高度: %d\n", getHeight(root));
	printf("根节点平衡因子: %d\n", getBalance(root));

	printf("删除节点 25:\n");
	root = deleteNode(root, 25);
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("树高度: %d\n", getHeight(root));
	printf("根节点平衡因子: %d\n", getBalance(root));
	printf("\n");

	// 测试4: 插入重复节点
	printf("4. 插入重复节点测试:\n");
	root = insertNode(root, 40); // 重复插入40
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("\n");

	// 测试5: 删除不存在的节点
	printf("5. 删除不存在的节点测试:\n");
	root = deleteNode(root, 100); // 删除不存在的节点
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("\n");

	// 测试6: 空树测试
	printf("6. 空树测试:\n");
	AVLTree emptyTree = NULL;
	printf("中序遍历空树: "); PrintMidOT(emptyTree); printf("\n");
	printf("搜索空树: %s\n", searchNode(emptyTree, 10) ? "找到" : "未找到");
	emptyTree = deleteNode(emptyTree, 10); // 删除空树中的节点
	printf("删除空树中的节点后: "); PrintMidOT(emptyTree); printf("\n");
	printf("\n");

	// 测试7: 大量插入和删除测试
	printf("7. 大量插入和删除测试:\n");
	AVLTree largeTree = NULL;
	for (int i = 0; i < 10; i++) {
		largeTree = insertNode(largeTree, i);
	}
	printf("插入0-9后中序遍历: "); PrintMidOT(largeTree); printf("\n");
	printf("树高度: %d\n", getHeight(largeTree));

	for (int i = 0; i < 10; i += 2) {
		largeTree = deleteNode(largeTree, i);
	}
	printf("删除偶数后中序遍历: "); PrintMidOT(largeTree); printf("\n");
	printf("树高度: %d\n", getHeight(largeTree));
	freeAVLTree(largeTree);
	printf("\n");

	// 释放内存
	freeAVLTree(root);
	printf("测试完成，内存已释放。\n");
}


int main()
{
	testAVLTree();

	return 0;
}