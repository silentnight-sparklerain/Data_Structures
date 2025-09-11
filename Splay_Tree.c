//��չ��SplayTree
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

//��������
SplayTree createNode(ElementType X);  //�����½��
SplayTree rightRotate(SplayTree tree);  //����
SplayTree leftRotate(SplayTree tree);  //����
SplayTree splay(SplayTree tree, ElementType X);  //��չ��������ֵΪX��Ԫ���Ƶ������
SplayTree searchNode(SplayTree tree, ElementType X);  //���Ҳ������Ȳ����ٰѸ�ֵ�Ƶ������
SplayTree insertNode(SplayTree tree, ElementType X);  //����������²����Ԫ����Ϊ�����
SplayTree deleteNode(SplayTree tree, ElementType X);  //ɾ������
void PrintMidOT(SplayTree tree);  //���������ӡ
void PrintPreOT(SplayTree tree);  //ǰ�������ӡ
void PrintPostOT(SplayTree tree);  //���������ӡ
void freeTree(SplayTree tree);  //�ͷ��ڴ�

//�����½��
SplayTree createNode(ElementType X)
{
	SplayTree root = (SplayTree)malloc(sizeof(struct Node));
	if (root == NULL)
	{
		printf("�ڴ����ʧ�ܣ������½��ʧ�ܣ�\n");
		return NULL;
	}
	root->data = X;
	root->left = NULL;
	root->right = NULL;
	return root;
}

//����
SplayTree rightRotate(SplayTree tree)
{
	SplayTree tree_left = tree->left;
	SplayTree tree_left_right = tree->left->right;
	tree_left->right = tree;
	tree->left = tree_left_right;
	return tree_left;
}

//����
SplayTree leftRotate(SplayTree tree)
{
	SplayTree tree_right = tree->right;
	SplayTree tree_right_left = tree->right->left;
	tree_right->left = tree;
	tree->right = tree_right_left;
	return tree_right;
}

//��չ��������ֵΪX��Ԫ���Ƶ������
SplayTree splay(SplayTree tree, ElementType X)
{
	//ֵΪ�������Ҳ���ֵ
	if (tree == NULL || tree->data == X)
	{
		return tree;
	}
	//ֵ������������
	if (tree->data > X)
	{
		if (tree->left == NULL)
		{
			return tree;
		}
		//Zig-Zig�������
		if (tree->left->data > X)
		{
			tree->left->left = splay(tree->left->left, X);
			tree = rightRotate(tree);
		}
		//Zig-Zag�������
		else if (tree->left->data < X)
		{
			tree->left->right = splay(tree->left->right, X);
			if (tree->left->right != NULL)
			{
				tree->left = leftRotate(tree->left);
			}
		}
		//���������һ��
		return (tree->left == NULL) ? tree : rightRotate(tree);
	}
	//ֵ������������
	else if (tree->data < X)
	{
		if (tree->right == NULL)
		{
			return tree;
		}
		//Zag-Zig�������
		if (tree->right->data > X)
		{
			tree->right->left = splay(tree->right->left, X);
			if (tree->right->left != NULL)
			{
				tree->right = rightRotate(tree->right);
			}
		}
		//Zag-Zag�������
		else if (tree->right->data < X)
		{
			tree->right->right = splay(tree->right->right, X);
			tree = leftRotate(tree);
		}
		//���������һ��
		return (tree->right == NULL) ? tree : leftRotate(tree);
	}
}

//���Ҳ������Ȳ����ٰѸ�ֵ�Ƶ������
SplayTree searchNode(SplayTree tree, ElementType X)
{
	return splay(tree, X);
}

//����������²����Ԫ����Ϊ�����
SplayTree insertNode(SplayTree tree, ElementType X)
{
	if (tree == NULL)
	{
		return createNode(X);
	}
	//��ֵ��ӽ�X�Ľ��ᵽ�����
	tree = splay(tree, X);
	//��������ֵΪX��ֱ�ӷ���
	if (tree->data == X)
	{
		return tree;
	}
	SplayTree newNode = createNode(X);
	//��������ֵС�ڸ�ֵ�����½����Ϊ����㣬ԭ�������Ϊ������
	if (tree->data > X)
	{
		newNode->right = tree;
		newNode->left = tree->left;
		tree->left = NULL;
	}
	//��������ֵ���ڸ�ֵ�����½����Ϊ����㣬ԭ�������Ϊ������
	else if (tree->data < X)
	{
		newNode->left = tree;
		newNode->right = tree->right;
		tree->right = NULL;
	}
	return newNode;
}

//ɾ������
SplayTree deleteNode(SplayTree tree, ElementType X)
{
	if (tree == NULL)
	{
		return tree;
	}
	//��Ŀ��ֵ�ᵽ�����
	tree = splay(tree, X);
	//Ŀ��ֵ������
	if (tree->data != X)
	{
		return tree;
	}
	//ֵ���ڣ�ɾ������㣬�������������ֵ��Ϊ����㣬û����������ֱ��ɾ�������
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

//���������ӡ
void PrintMidOT(SplayTree tree)
{
	if (tree != NULL)
	{
		PrintMidOT(tree->left);
		printf("%d ", tree->data);
		PrintMidOT(tree->right);
	}
}

//ǰ�������ӡ
void PrintPreOT(SplayTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->data);
		PrintPreOT(tree->left);
		PrintPreOT(tree->right);
	}
}

//���������ӡ
void PrintPostOT(SplayTree tree)
{
	if (tree != NULL)
	{
		PrintPostOT(tree->left);
		PrintPostOT(tree->right);
		printf("%d ", tree->data);
	}
}

//�ͷ��ڴ�
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

//���Ժ���
void testSplayTree()
{
	SplayTree root = NULL;
	printf("=== ��չ��(Splay Tree)���� ===\n\n");

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
	printf("��ǰ���ڵ�: %d\n", root->data);
	printf("\n");

	// ����2: �����ڵ�
	printf("2. �����ڵ����:\n");
	SplayTree searchResult = searchNode(root, 30);
	if (searchResult != NULL && searchResult->data == 30) {
		printf("�ҵ��ڵ� 30�����ڸ��ڵ���: %d\n", searchResult->data);
	}
	else {
		printf("δ�ҵ��ڵ� 30\n");
	}

	searchResult = searchNode(root, 100);
	if (searchResult != NULL && searchResult->data == 100) {
		printf("�ҵ��ڵ� 100�����ڸ��ڵ���: %d\n", searchResult->data);
	}
	else {
		printf("δ�ҵ��ڵ� 100����ǰ���ڵ���: %d\n", root->data);
	}
	printf("\n");

	// ����3: ɾ���ڵ�
	printf("3. ɾ���ڵ����:\n");
	printf("ɾ���ڵ� 10:\n");
	root = deleteNode(root, 10);
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("��ǰ���ڵ�: %d\n", root->data);

	printf("ɾ���ڵ� 50:\n");
	root = deleteNode(root, 50);
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("��ǰ���ڵ�: %d\n", root->data);

	printf("ɾ���ڵ� 25:\n");
	root = deleteNode(root, 25);
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("��ǰ���ڵ�: %d\n", root->data);
	printf("\n");

	// ����4: �����ظ��ڵ�
	printf("4. �����ظ��ڵ����:\n");
	root = insertNode(root, 40); // �ظ�����40
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("��ǰ���ڵ�: %d\n", root->data);
	printf("\n");

	// ����5: ɾ�������ڵĽڵ�
	printf("5. ɾ�������ڵĽڵ����:\n");
	root = deleteNode(root, 100); // ɾ�������ڵĽڵ�
	printf("�������: "); PrintMidOT(root); printf("\n");
	printf("��ǰ���ڵ�: %d\n", root->data);
	printf("\n");

	// ����6: ��������
	printf("6. ��������:\n");
	SplayTree emptyTree = NULL;
	printf("�����������: "); PrintMidOT(emptyTree); printf("\n");
	SplayTree searchEmpty = searchNode(emptyTree, 10);
	printf("��������: %s\n", (searchEmpty != NULL && searchEmpty->data == 10) ? "�ҵ�" : "δ�ҵ�");
	emptyTree = deleteNode(emptyTree, 10); // ɾ�������еĽڵ�
	printf("ɾ�������еĽڵ��: "); PrintMidOT(emptyTree); printf("\n");
	printf("\n");

	// ����7: ���������ɾ������
	printf("7. ���������ɾ������:\n");
	SplayTree largeTree = NULL;
	for (int i = 0; i < 10; i++) {
		largeTree = insertNode(largeTree, i);
	}
	printf("����0-9���������: "); PrintMidOT(largeTree); printf("\n");
	printf("��ǰ���ڵ�: %d\n", largeTree->data);

	for (int i = 0; i < 10; i += 2) {
		largeTree = deleteNode(largeTree, i);
	}
	printf("ɾ��ż�����������: "); PrintMidOT(largeTree); printf("\n");
	printf("��ǰ���ڵ�: %d\n", largeTree->data);
	freeTree(largeTree);
	printf("\n");

	// �ͷ��ڴ�
	freeTree(root);
	printf("������ɣ��ڴ����ͷš�\n");
}


int main()
{
	testSplayTree();

	return 0;
}