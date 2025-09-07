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
	int height;  //���߶�
};

//��������
int getHeight(AVLTree tree);  //��ȡ�߶�
int getMax(int a, int b);  //��ȡ���������е����ֵ
AVLTree createTree(ElementType X);  //��������
AVLTree rightRotate(AVLTree tree);  //����
AVLTree leftRotate(AVLTree tree);  //����
int getBalance(AVLTree tree);  //��ȡ����ƽ������
AVLTree insertNode(AVLTree tree, ElementType X);  //�����½��
AVLTree minNode(AVLTree tree);  //������Сֵ��� 
AVLTree deleteNode(AVLTree tree, ElementType X);  //��ֵɾ�����
void PrintMidOT(AVLTree tree);  //���������ӡ
void PrintPreOT(AVLTree tree);  //ǰ�������ӡ
void PrintPostOT(AVLTree tree);  //���������ӡ
AVLTree searchNode(AVLTree tree, ElementType X);  //��ֵ����
void freeAVLTree(AVLTree tree);  //�ͷ�AVL��



//��ȡ�߶�
int getHeight(AVLTree tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	return tree->height;
}

//��ȡ���������е����ֵ
int getMax(int a, int b)
{
	return (a > b) ? a : b;
}

//��������
AVLTree createTree(ElementType X)
{
	AVLTree root = (AVLTree)malloc(sizeof(struct Node));
	if (root == NULL)
	{
		printf("��������ʧ�ܣ���������ʧ�ܣ�\n");
		return NULL;
	}
	root->data = X;
	root->height = 1;
	root->right = NULL;
	root->left = NULL;
	return root;
}

//����
AVLTree rightRotate(AVLTree tree)
{
	AVLTree tree_left = tree->left;
	AVLTree tree_left_right = tree->left->right;
	tree_left->right = tree;
	tree->left = tree_left_right;
	//�޸ĸ߶�
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	tree_left->height = getMax(getHeight(tree_left->left), getHeight(tree_left->right)) + 1;
	return tree_left;
}

//����
AVLTree leftRotate(AVLTree tree)
{
	AVLTree tree_right = tree->right;
	AVLTree tree_right_left = tree->right->left;
	tree_right->left = tree;
	tree->right = tree_right_left;
	//�޸ĸ߶�
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	tree_right->height = getMax(getHeight(tree_right->left), getHeight(tree_right->right)) + 1;
	return tree_right;
}

//��ȡ����ƽ������
int getBalance(AVLTree tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	return getHeight(tree->left) - getHeight(tree->right);
}

//�����½��
AVLTree insertNode(AVLTree tree, ElementType X)
{
	//1.��ִ�б�׼�Ĳ���
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
		return tree;  //�������������ظ����
	}
	//2.���½��ĸ߶�
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	//3.����Ƿ�����ʧ��
	int balance = getBalance(tree);
	//4.��ʧ�⣬������ת����
	//�������������
	if (balance < -1 && tree->right->data < X)
	{
		return leftRotate(tree);
	}
	//�������������
	if (balance > 1 && tree->left->data > X)
	{
		return rightRotate(tree);
	}
	//���������������
	if (balance < -1 && tree->right->data > X)
	{
		tree->right = rightRotate(tree->right);
		return leftRotate(tree);
	}
	//���������������
	if (balance > 1 && tree->left->data < X)
	{
		tree->left = leftRotate(tree->left);
		return rightRotate(tree);
	}
	return tree;
}

//������Сֵ���
AVLTree minNode(AVLTree tree)
{
	AVLTree current = tree;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

//��ֵɾ�����
AVLTree deleteNode(AVLTree tree, ElementType X)
{
	//1.��ִ�б�׼��ɾ��
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
		//���ҵ�Ҫɾ���Ľ��
		//�����һ���ӽ������ӽ��
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
		//����������ӽ��
		else
		{
			AVLTree current = minNode(tree->right);
			tree->data = current->data;
			tree->right = deleteNode(tree->right, current->data);
		}
	}
	//�����ֻ��һ����㣬ɾ��ֱ�ӷ���
	if (tree == NULL)
	{
		return tree;
	}
	//2.���½��ĸ߶�
	tree->height = getMax(getHeight(tree->left), getHeight(tree->right)) + 1;
	//3.����Ƿ�����ʧ��
	int balance = getBalance(tree);
	//4.��ʧ�⣬������ת����
	//�������������
	if (balance < -1 && tree->right->data < X)
	{
		return leftRotate(tree);
	}
	//�������������
	if (balance > 1 && tree->left->data > X)
	{
		return rightRotate(tree);
	}
	//���������������
	if (balance < -1 && tree->right->data > X)
	{
		tree->right = rightRotate(tree->right);
		return leftRotate(tree);
	}
	//���������������
	if (balance > 1 && tree->left->data < X)
	{
		tree->left = leftRotate(tree->left);
		return rightRotate(tree);
	}
	return tree;
}


//���������ӡ
void PrintMidOT(AVLTree tree)
{
	if (tree != NULL)
	{
		PrintMidOT(tree->left);
		printf("%d ", tree->data);
		PrintMidOT(tree->right);
	}
}

//ǰ�������ӡ
void PrintPreOT(AVLTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->data);
		PrintPreOT(tree->left);
		PrintPreOT(tree->right);
	}
}

//���������ӡ
void PrintPostOT(AVLTree tree)
{
	if (tree != NULL)
	{
		PrintPostOT(tree->left);
		PrintPostOT(tree->right);
		printf("%d ", tree->data);
	}
}

//��ֵ����
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

//�ͷ�AVL��
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

//���Ժ���
void testAVLTree() 
{
	AVLTree root = NULL;
	printf("=== AVL������ ===\n\n");

	// ����1: ����ڵ�
	printf("1. ����ڵ����:\n");
	root = insertNode(root, 10);
	root = insertNode(root, 20);
	root = insertNode(root, 30);
	root = insertNode(root, 40);
	root = insertNode(root, 50);
	root = insertNode(root, 25);

	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("ǰ�����: "); PrintPreOT(root); printf("\n");
	printf("�������: "); PrintPostOT(root); printf("\n");
	printf("���߶�: %d\n", getHeight(root));
	printf("���ڵ�ƽ������: %d\n", getBalance(root));
	printf("\n");

	// ����2: �����ڵ�
	printf("2. �����ڵ����:\n");
	AVLTree searchResult = searchNode(root, 30);
	if (searchResult != NULL) {
		printf("�ҵ��ڵ� 30\n");
	}
	else {
		printf("δ�ҵ��ڵ� 30\n");
	}

	searchResult = searchNode(root, 100);
	if (searchResult != NULL) {
		printf("�ҵ��ڵ� 100\n");
	}
	else {
		printf("δ�ҵ��ڵ� 100\n");
	}
	printf("\n");

	// ����3: ɾ���ڵ�
	printf("3. ɾ���ڵ����:\n");
	printf("ɾ���ڵ� 10:\n");
	root = deleteNode(root, 10);
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("���߶�: %d\n", getHeight(root));
	printf("���ڵ�ƽ������: %d\n", getBalance(root));

	printf("ɾ���ڵ� 50:\n");
	root = deleteNode(root, 50);
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("���߶�: %d\n", getHeight(root));
	printf("���ڵ�ƽ������: %d\n", getBalance(root));

	printf("ɾ���ڵ� 25:\n");
	root = deleteNode(root, 25);
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("���߶�: %d\n", getHeight(root));
	printf("���ڵ�ƽ������: %d\n", getBalance(root));
	printf("\n");

	// ����4: �����ظ��ڵ�
	printf("4. �����ظ��ڵ����:\n");
	root = insertNode(root, 40); // �ظ�����40
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("\n");

	// ����5: ɾ�������ڵĽڵ�
	printf("5. ɾ�������ڵĽڵ����:\n");
	root = deleteNode(root, 100); // ɾ�������ڵĽڵ�
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("\n");

	// ����6: ��������
	printf("6. ��������:\n");
	AVLTree emptyTree = NULL;
	printf("�����������: "); PrintMidOT(emptyTree); printf("\n");
	printf("��������: %s\n", searchNode(emptyTree, 10) ? "�ҵ�" : "δ�ҵ�");
	emptyTree = deleteNode(emptyTree, 10); // ɾ�������еĽڵ�
	printf("ɾ�������еĽڵ��: "); PrintMidOT(emptyTree); printf("\n");
	printf("\n");

	// ����7: ���������ɾ������
	printf("7. ���������ɾ������:\n");
	AVLTree largeTree = NULL;
	for (int i = 0; i < 10; i++) {
		largeTree = insertNode(largeTree, i);
	}
	printf("����0-9���������: "); PrintMidOT(largeTree); printf("\n");
	printf("���߶�: %d\n", getHeight(largeTree));

	for (int i = 0; i < 10; i += 2) {
		largeTree = deleteNode(largeTree, i);
	}
	printf("ɾ��ż�����������: "); PrintMidOT(largeTree); printf("\n");
	printf("���߶�: %d\n", getHeight(largeTree));
	freeAVLTree(largeTree);
	printf("\n");

	// �ͷ��ڴ�
	freeAVLTree(root);
	printf("������ɣ��ڴ����ͷš�\n");
}


int main()
{
	testAVLTree();

	return 0;
}