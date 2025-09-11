//伸展树SplayTree
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

typedef struct Node* SplayTree;
struct Node
{
	ElementType data;
	SplayTree left;
	SplayTree right;
};

//函数声明
SplayTree createNode(ElementType X);  //创建新结点
SplayTree rightRotate(SplayTree tree);  //右旋
SplayTree leftRotate(SplayTree tree);  //左旋
SplayTree splay(SplayTree tree, ElementType X);  //伸展操作：将值为X的元素移到根结点
SplayTree searchNode(SplayTree tree, ElementType X);  //查找操作：先查找再把该值移到根结点
SplayTree insertNode(SplayTree tree, ElementType X);  //插入操作：新插入的元素作为根结点
SplayTree deleteNode(SplayTree tree, ElementType X);  //删除操作
void PrintMidOT(SplayTree tree);  //中序遍历打印
void PrintPreOT(SplayTree tree);  //前序遍历打印
void PrintPostOT(SplayTree tree);  //后序遍历打印
void freeTree(SplayTree tree);  //释放内存

//创建新结点
SplayTree createNode(ElementType X)
{
	SplayTree root = (SplayTree)malloc(sizeof(struct Node));
	if (root == NULL)
	{
		printf("内存分配失败，建立新结点失败！\n");
		return NULL;
	}
	root->data = X;
	root->left = NULL;
	root->right = NULL;
	return root;
}

//右旋
SplayTree rightRotate(SplayTree tree)
{
	SplayTree tree_left = tree->left;
	SplayTree tree_left_right = tree->left->right;
	tree_left->right = tree;
	tree->left = tree_left_right;
	return tree_left;
}

//左旋
SplayTree leftRotate(SplayTree tree)
{
	SplayTree tree_right = tree->right;
	SplayTree tree_right_left = tree->right->left;
	tree_right->left = tree;
	tree->right = tree_right_left;
	return tree_right;
}

//伸展操作：将值为X的元素移到根结点
SplayTree splay(SplayTree tree, ElementType X)
{
	//值为根结点或找不到值
	if (tree == NULL || tree->data == X)
	{
		return tree;
	}
	//值在左子树里面
	if (tree->data > X)
	{
		if (tree->left == NULL)
		{
			return tree;
		}
		//Zig-Zig左左情况
		if (tree->left->data > X)
		{
			tree->left->left = splay(tree->left->left, X);
			tree = rightRotate(tree);
		}
		//Zig-Zag左右情况
		else if (tree->left->data < X)
		{
			tree->left->right = splay(tree->left->right, X);
			if (tree->left->right != NULL)
			{
				tree->left = leftRotate(tree->left);
			}
		}
		//最后再右旋一次
		return (tree->left == NULL) ? tree : rightRotate(tree);
	}
	//值在右子树里面
	else if (tree->data < X)
	{
		if (tree->right == NULL)
		{
			return tree;
		}
		//Zag-Zig右左情况
		if (tree->right->data > X)
		{
			tree->right->left = splay(tree->right->left, X);
			if (tree->right->left != NULL)
			{
				tree->right = rightRotate(tree->right);
			}
		}
		//Zag-Zag右右情况
		else if (tree->right->data < X)
		{
			tree->right->right = splay(tree->right->right, X);
			tree = leftRotate(tree);
		}
		//最后再左旋一次
		return (tree->right == NULL) ? tree : leftRotate(tree);
	}
}

//查找操作：先查找再把该值移到根结点
SplayTree searchNode(SplayTree tree, ElementType X)
{
	return splay(tree, X);
}

//插入操作：新插入的元素作为根结点
SplayTree insertNode(SplayTree tree, ElementType X)
{
	if (tree == NULL)
	{
		return createNode(X);
	}
	//将值最接近X的结点搬到根结点
	tree = splay(tree, X);
	//如果根结点值为X，直接返回
	if (tree->data == X)
	{
		return tree;
	}
	SplayTree newNode = createNode(X);
	//如果插入的值小于根值，将新结点作为根结点，原根结点作为右子树
	if (tree->data > X)
	{
		newNode->right = tree;
		newNode->left = tree->left;
		tree->left = NULL;
	}
	//如果插入的值大于根值，将新结点作为根结点，原根结点作为左子树
	else if (tree->data < X)
	{
		newNode->left = tree;
		newNode->right = tree->right;
		tree->right = NULL;
	}
	return newNode;
}

//删除操作
SplayTree deleteNode(SplayTree tree, ElementType X)
{
	if (tree == NULL)
	{
		return tree;
	}
	//将目标值搬到根结点
	tree = splay(tree, X);
	//目标值不存在
	if (tree->data != X)
	{
		return tree;
	}
	//值存在，删除根结点，将左子树的最大值作为根结点，没有左子树就直接删除根结点
	SplayTree current = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
	}
	else
	{
		tree = splay(tree->left, X);
		tree->right = current->right;
	}
	free(current);
	current = NULL;
	return tree;
}

//中序遍历打印
void PrintMidOT(SplayTree tree)
{
	if (tree != NULL)
	{
		PrintMidOT(tree->left);
		printf("%d ", tree->data);
		PrintMidOT(tree->right);
	}
}

//前序遍历打印
void PrintPreOT(SplayTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->data);
		PrintPreOT(tree->left);
		PrintPreOT(tree->right);
	}
}

//后序遍历打印
void PrintPostOT(SplayTree tree)
{
	if (tree != NULL)
	{
		PrintPostOT(tree->left);
		PrintPostOT(tree->right);
		printf("%d ", tree->data);
	}
}

//释放内存
void freeTree(SplayTree tree)
{
	if (tree != NULL)
	{
		freeTree(tree->left);
		freeTree(tree->right);
		free(tree);
		tree = NULL;
	}
}

//测试函数
void testSplayTree()
{
	SplayTree root = NULL;
	printf("=== 伸展树(Splay Tree)测试 ===\n\n");

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
	printf("当前根节点: %d\n", root->data);
	printf("\n");

	// 测试2: 搜索节点
	printf("2. 搜索节点测试:\n");
	SplayTree searchResult = searchNode(root, 30);
	if (searchResult != NULL && searchResult->data == 30) {
		printf("找到节点 30，现在根节点是: %d\n", searchResult->data);
	}
	else {
		printf("未找到节点 30\n");
	}

	searchResult = searchNode(root, 100);
	if (searchResult != NULL && searchResult->data == 100) {
		printf("找到节点 100，现在根节点是: %d\n", searchResult->data);
	}
	else {
		printf("未找到节点 100，当前根节点是: %d\n", root->data);
	}
	printf("\n");

	// 测试3: 删除节点
	printf("3. 删除节点测试:\n");
	printf("删除节点 10:\n");
	root = deleteNode(root, 10);
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("当前根节点: %d\n", root->data);

	printf("删除节点 50:\n");
	root = deleteNode(root, 50);
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("当前根节点: %d\n", root->data);

	printf("删除节点 25:\n");
	root = deleteNode(root, 25);
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("当前根节点: %d\n", root->data);
	printf("\n");

	// 测试4: 插入重复节点
	printf("4. 插入重复节点测试:\n");
	root = insertNode(root, 40); // 重复插入40
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("当前根节点: %d\n", root->data);
	printf("\n");

	// 测试5: 删除不存在的节点
	printf("5. 删除不存在的节点测试:\n");
	root = deleteNode(root, 100); // 删除不存在的节点
	printf("中序遍历: "); PrintMidOT(root); printf("\n");
	printf("当前根节点: %d\n", root->data);
	printf("\n");

	// 测试6: 空树测试
	printf("6. 空树测试:\n");
	SplayTree emptyTree = NULL;
	printf("中序遍历空树: "); PrintMidOT(emptyTree); printf("\n");
	SplayTree searchEmpty = searchNode(emptyTree, 10);
	printf("搜索空树: %s\n", (searchEmpty != NULL && searchEmpty->data == 10) ? "找到" : "未找到");
	emptyTree = deleteNode(emptyTree, 10); // 删除空树中的节点
	printf("删除空树中的节点后: "); PrintMidOT(emptyTree); printf("\n");
	printf("\n");

	// 测试7: 大量插入和删除测试
	printf("7. 大量插入和删除测试:\n");
	SplayTree largeTree = NULL;
	for (int i = 0; i < 10; i++) {
		largeTree = insertNode(largeTree, i);
	}
	printf("插入0-9后中序遍历: "); PrintMidOT(largeTree); printf("\n");
	printf("当前根节点: %d\n", largeTree->data);

	for (int i = 0; i < 10; i += 2) {
		largeTree = deleteNode(largeTree, i);
	}
	printf("删除偶数后中序遍历: "); PrintMidOT(largeTree); printf("\n");
	printf("当前根节点: %d\n", largeTree->data);
	freeTree(largeTree);
	printf("\n");

	// 释放内存
	freeTree(root);
	printf("测试完成，内存已释放。\n");
}


int main()
{
	testSplayTree();

	return 0;
}