#include <stdio.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}node;

node *createNode()
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->data = NULL;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

node *insertNode(node *root, int data)
{
	node *q = createNode();
	q->data = data;
	if (root == NULL)
	{
		root = q;
		root->left = NULL;
		root->right = NULL;
		return root;
	}

	else if (root->data > data)
	{
		root->left = insertNode(root->left, data);
	}

	else if (root->data < data)
	{
		root->right = insertNode(root->right, data);
	}

	return root;

}

node *searchNode(node *root, int data)
{
	if (root == NULL)
	{
		return NULL;
	}

	else if (root->data == data)
	{
		return root;
	}

	else if (root->data < data)
	{
		root = root->right;
		searchNode(root, data);
	}

	else if (root->data > data)
	{
		root = root->left;
		searchNode(root, data);
	}

}

node *insertNULL(node *root, int data)
{

	if (root->data == data)
	{
		//	printf(" %d\n",root->data);
		root = NULL;
		return root;
	}

	else if (root->data > data)
	{
		root->left = insertNULL(root->left, data);
	}

	else if (root->data < data)
	{
		root->right = insertNULL(root->right, data);
	}

	return root;

}

node *insertNULLL(node *root, int data)
{

	if (root->data == data)
	{
		//	printf(" %d\n", root->data);
		root = root->right;
		return root;
	}

	else if (root->data > data)
	{
		root->left = insertNULLL(root->left, data);
	}

	else if (root->data < data)
	{
		root->right = insertNULLL(root->right, data);
	}

	return root;

}

node *insertNULLR(node *root, int data)
{

	if (root->data == data)
	{
		root = root->left;
		return root;
	}

	else if (root->data > data)
	{
		root->left = insertNULLR(root->left, data);
	}

	else if (root->data < data)
	{
		root->right = insertNULLR(root->right, data);
	}

	return root;

}

node *insertN(node *root, int data, node *findChild)
{
	int index = findChild->data;

	if (root->data == data)
	{

		if (findChild->left == NULL && findChild->right == NULL)
		{
			insertNULL(root, findChild->data);
			root->data = index;
		}


		else if (findChild->left == NULL && findChild->right != NULL)
		{
			insertNULLL(root, findChild->data);
			root->data = index;
		}

		return root;
	}

	else if (root->data > data)
	{
		root->left = insertN(root->left, data, findChild);
	}

	else if (root->data < data)
	{
		root->right = insertN(root->right, data, findChild);
	}

	return root;

}

node *deleteNode(node*root, int data)
{
	node *findNode = searchNode(root, data);
	node * findChild = findNode;

	node *tempNode = NULL;
	

	if (findNode->left != NULL && findNode->right != NULL)
	{
		findChild = findChild->right;
		while (findChild->left != NULL)
		{
			findChild = findChild->left;
		}
		insertN(root, data, findChild);

	}
	else if (findNode->left == NULL && findNode->right == NULL)
	{
		return insertNULL(root, data);
	}

	else if (findNode->left == NULL && findNode->right != NULL)
	{
		return insertNULLL(root, data);
	}

	else if (findNode->left != NULL && findNode->right == NULL)
	{
		return insertNULLR(root, data);
	}



}

void printTree(node *root)
{
	node *printNode = root;

	if (printNode != NULL)
	{
		printf(" %d", root->data);
		printTree(root->left);
		printTree(root->right);
	}

}

int main() {

	char order = NULL;
	int num;
	node *root = NULL;
	node *tempNode = NULL;

	while (1)
	{
		scanf("%c", &order);
		getchar();

		if (order == 'i')
		{
			scanf("%d", &num);
			getchar();

			tempNode = searchNode(root, num);

			if (tempNode == NULL)
			{
				root = insertNode(root, num);
			}
			else printf("중복입니다.\n");

			
		}
		else if (order == 's')
		{
			scanf("%d", &num);
			getchar();
			tempNode = searchNode(root, num);

			if (tempNode == NULL)
			{
				printf("X\n");
			}
			else printf("%d\n", tempNode->data);
		}

		else if (order == 'd')
		{
			scanf("%d", &num);
			getchar();
			tempNode = searchNode(root, num);

			if (tempNode == NULL)
			{
				printf("X\n");
			}
			else
			{
				printf("%d\n", num);
				root = deleteNode(root, num);
			}


		}

		else if (order == 'p')
		{

			printTree(root);
			printf("\n");

		}

		else if (order == 'q')
		{
			return 0;
		}
	}


	return 0;
}