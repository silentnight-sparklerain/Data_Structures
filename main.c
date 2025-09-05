//�������������������ṹ��ʵ��
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

//�������Ľ��ṹ��
typedef struct Node* TreeNode;
struct Node
{
	ElementType data;
	TreeNode left;
	TreeNode right;
};

//��������
TreeNode CreateTreeNode(ElementType X);  //���������
TreeNode InsertTreeNode(TreeNode root, ElementType X);  //������
TreeNode SearchTreeNode(TreeNode root, ElementType X);  //���ҽ��
TreeNode FindMin(TreeNode root);  //������СԪ�ؽ��
TreeNode FindMax(TreeNode root);  //�������Ԫ�ؽ��
TreeNode DeleteTreeNode(TreeNode root, ElementType X);  //��ֵɾ�����
void PrintMOT(TreeNode root);  //���������ӡ
int getHeight(TreeNode root);  //��ȡ���ĸ߶�
void FreeTree(TreeNode root);  //����������


//���������
TreeNode CreateTreeNode(ElementType X)
{
	TreeNode root = (TreeNode)malloc(sizeof(struct Node));
	if (root == NULL)
	{
		printf("�ڴ�����ʧ�ܣ��������Ľ��ʧ�ܣ�\n");
		return NULL;
	}
	root->data = X;
	root->left = NULL;
	root->right = NULL;
	return root;
}

//������
TreeNode InsertTreeNode(TreeNode root, ElementType X)
{
	if (root == NULL)
	{
		return CreateTreeNode(X);
	}
	if (root->data < X)
	{
		root->right = InsertTreeNode(root->right, X);
	}
	else if (root->data > X)
	{
		root->left = InsertTreeNode(root->left, X);
	}
	return root;
}

//���ҽ��
TreeNode SearchTreeNode(TreeNode root, ElementType X)
{
	if (root == NULL || root->data == X)
	{
		return root;
	}
	if (root->data > X)
	{
		return SearchTreeNode(root->left, X);
	}
	else
	{
		return SearchTreeNode(root->right, X);
	}
}

//������СԪ�ؽ��
TreeNode FindMin(TreeNode root)
{
	TreeNode current = root;
	while (current && (current->left != NULL))
	{
		current = current->left;
	}
	return current;
}

//�������Ԫ�ؽ��
TreeNode FindMax(TreeNode root)
{
	TreeNode current = root;
	while (current && (current->right != NULL))
	{
		current = current->right;
	}
	return current;
}

//��ֵɾ�����
TreeNode DeleteTreeNode(TreeNode root, ElementType X)
{
	if (root == NULL)
	{
		return root;
	}
	if (root->data < X)
	{
		root->right = DeleteTreeNode(root->right, X);
	}
	else if (root->data > X)
	{
		root->left = DeleteTreeNode(root->left, X);
	}
	else
	{
		//1.ֻ����������ֻ����������û��
		if (root->left == NULL)
		{
			TreeNode current = root->right;
			free(root);
			root = NULL;
			return current;
		}
		else if(root->right == NULL)
		{
			TreeNode current = root->left;
			free(root);
			root = NULL;
			return current;
		}
		//2.������������
		TreeNode current = FindMin(root->right);
		root->data = current->data;
		root->right = DeleteTreeNode(root->right, current->data);
	}
	return root;
}

//���������ӡ
void PrintMOT(TreeNode root)
{
	if (root == NULL)
	{
		return;
	}
	PrintMOT(root->left);
	printf("%d ", root->data);
	PrintMOT(root->right);
}

//��ȡ���ĸ߶�
int getHeight(TreeNode root)
{
	if (root == NULL)
	{
		return 0;
	}
	int leftheight = getHeight(root->left);
	int rightheight = getHeight(root->right);
	return (leftheight > rightheight ? leftheight : rightheight) + 1;
}

//����������
void FreeTree(TreeNode root)
{
	if (root != NULL)
	{
		FreeTree(root->right);
		FreeTree(root->left);
		free(root);
		root = NULL;
	}
}

// ���Ժ���
void testBST() {
    printf("=== �������������� ===\n\n");

    TreeNode root = NULL;

    // 1. ���Կ���
    printf("1. ���Կ���:\n");
    printf("   ���ĸ߶�: %d\n", getHeight(root));
    printf("   ��Сֵ: %s\n", FindMin(root) ? "����" : "������");
    printf("   ���ֵ: %s\n", FindMax(root) ? "����" : "������");
    printf("   ����10: %s\n", SearchTreeNode(root, 10) ? "�ҵ�" : "δ�ҵ�");
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 2. ���Բ��뵥���ڵ�
    printf("2. ���Բ��뵥���ڵ�(50):\n");
    root = InsertTreeNode(root, 50);
    printf("   ���ĸ߶�: %d\n", getHeight(root));
    printf("   ��Сֵ: %d\n", FindMin(root)->data);
    printf("   ���ֵ: %d\n", FindMax(root)->data);
    printf("   ����50: %s\n", SearchTreeNode(root, 50) ? "�ҵ�" : "δ�ҵ�");
    printf("   ����10: %s\n", SearchTreeNode(root, 10) ? "�ҵ�" : "δ�ҵ�");
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 3. ���Բ������ڵ�
    printf("3. ���Բ������ڵ�(30, 70, 20, 40, 60, 80):\n");
    root = InsertTreeNode(root, 30);
    root = InsertTreeNode(root, 70);
    root = InsertTreeNode(root, 20);
    root = InsertTreeNode(root, 40);
    root = InsertTreeNode(root, 60);
    root = InsertTreeNode(root, 80);
    printf("   ���ĸ߶�: %d\n", getHeight(root));
    printf("   ��Сֵ: %d\n", FindMin(root)->data);
    printf("   ���ֵ: %d\n", FindMax(root)->data);
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 4. ���Բ����ظ�ֵ
    printf("4. ���Բ����ظ�ֵ(50):\n");
    TreeNode beforeInsert = root;
    root = InsertTreeNode(root, 50); // Ӧ�ò���ı����ṹ
    printf("   ���ṹ�Ƿ�ı�: %s\n", (beforeInsert == root) ? "��" : "��");
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 5. ���Բ��Ҹ������
    printf("5. ���Բ���:\n");
    printf("   ���Ҵ��ڵ�ֵ(40): %s\n", SearchTreeNode(root, 40) ? "�ҵ�" : "δ�ҵ�");
    printf("   ���Ҳ����ڵ�ֵ(100): %s\n", SearchTreeNode(root, 100) ? "�ҵ�" : "δ�ҵ�");
    printf("   ������Сֵ(20): %s\n", SearchTreeNode(root, 20) ? "�ҵ�" : "δ�ҵ�");
    printf("   �������ֵ(80): %s\n", SearchTreeNode(root, 80) ? "�ҵ�" : "δ�ҵ�\n");

    // 6. ����ɾ��Ҷ�ӽڵ�
    printf("6. ����ɾ��Ҷ�ӽڵ�(20):\n");
    root = DeleteTreeNode(root, 20);
    printf("   ����20: %s\n", SearchTreeNode(root, 20) ? "�ҵ�" : "δ�ҵ�");
    printf("   ��Сֵ: %d\n", FindMin(root)->data);
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 7. ����ɾ��ֻ��һ���ӽڵ�Ľڵ�
    printf("7. ����ɾ��ֻ��һ���ӽڵ�Ľڵ�(30):\n");
    root = DeleteTreeNode(root, 30); // 30��һ�����ӽڵ�40
    printf("   ����30: %s\n", SearchTreeNode(root, 30) ? "�ҵ�" : "δ�ҵ�");
    printf("   ����40: %s\n", SearchTreeNode(root, 40) ? "�ҵ�" : "δ�ҵ�");
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 8. ����ɾ���������ӽڵ�Ľڵ�
    printf("8. ����ɾ���������ӽڵ�Ľڵ�(50 - ���ڵ�):\n");
    root = DeleteTreeNode(root, 50);
    printf("   ����50: %s\n", SearchTreeNode(root, 50) ? "�ҵ�" : "δ�ҵ�");
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 9. ����ɾ�������ڵĽڵ�
    printf("9. ����ɾ�������ڵĽڵ�(100):\n");
    TreeNode beforeDelete = root;
    root = DeleteTreeNode(root, 100);
    printf("   ���ṹ�Ƿ�ı�: %s\n", (beforeDelete == root) ? "��" : "��");
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 10. ����ɾ�����нڵ�
    printf("10. ����ɾ�����нڵ�:\n");
    root = DeleteTreeNode(root, 40);
    root = DeleteTreeNode(root, 60);
    root = DeleteTreeNode(root, 70);
    root = DeleteTreeNode(root, 80);
    printf("   ���ĸ߶�: %d\n", getHeight(root));
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 11. ���Կ���ɾ��
    printf("11. ���Կ���ɾ��:\n");
    root = DeleteTreeNode(root, 100); // ����ɾ�������еĽڵ�
    printf("   ������ɣ�û�б���\n\n");

    // 12. �������²���
    printf("12. �������²���ڵ�:\n");
    root = InsertTreeNode(root, 25);
    root = InsertTreeNode(root, 15);
    root = InsertTreeNode(root, 35);
    printf("   ���ĸ߶�: %d\n", getHeight(root));
    printf("   ��Сֵ: %d\n", FindMin(root)->data);
    printf("   ���ֵ: %d\n", FindMax(root)->data);
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    // 13. ����������
    printf("13. ����������:\n");
    FreeTree(root);
    root = NULL;
    printf("   ��������\n");
    printf("   ���ĸ߶�: %d\n", getHeight(root));
    printf("   �������: "); PrintMOT(root); printf("\n\n");

    printf("=== ������� ===\n");
}

int main()
{
	testBST();

	return 0;
}