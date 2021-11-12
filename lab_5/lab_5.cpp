#include <iostream>
using namespace std;

struct node;
struct Binarytree; 
void add_node(int num, Binarytree* tree);// добавление узла в бинарное дерево
void PrintBinaryTree(Binarytree*); // вывести на экран бинарное дерево поиском в глубину
void DeleteTree(Binarytree*); // удалить дерево
void delete_node_tree(Binarytree* &tree, int num);// удалить узел дерева

struct node {
	node* left = NULL;
	node* right = NULL;
	int item;
	int nodes = 0;
	int heighe_difference = 0; //левый минус правый
};
struct Binarytree {
	node* first = NULL;
	int nodes = 0;
};
void add_node(int num,Binarytree *tree) {
	tree->nodes += 1;
	// добавление узла в бинарное дерево
	node* nd = new node;
	nd->item = num;
	if (tree->first == NULL) {
		tree->first = nd;
		return;
	}
	node* p1 = NULL,*p = tree->first;
	while (p != NULL) {
		p->nodes++;
		p1 = p;
		if (num < p->item) {
			p->heighe_difference += 1;
			p = p->left;
		}
		else {
			p->heighe_difference -= 1;
			p = p->right;
		}
	}
	if (nd->item <p1->item) {
		p1->left = nd;
	}
	else {
		p1->right = nd;
	}
}
node* minimum(node* nd) {
	node* p = nd;
	while (nd->left != NULL) {
		p = nd->left;
	}
	return p;
}
node* delete_node(int num, node*nd) {
	// удаление одного узла
	if (nd == NULL) {
		return nd;
	}
	if (num < nd->item) {
		nd->heighe_difference -= 1;
		nd->nodes -= 1;
		nd->left = delete_node(num,nd->left);
	}
	else if (num > nd->item) {
		nd->nodes -= 1;
		nd->heighe_difference += 1;
		nd->right = delete_node(num, nd->right);
	}
	else if (nd->left != NULL && nd->right != NULL) {
		nd->item = minimum(nd->right)->item;
		nd->right = delete_node(nd->item,nd->right);
		nd->heighe_difference += 1;
		nd->nodes -= 1;
	}
	else {
		if (nd->left != NULL) {
			node* p = nd->left;
			delete nd;
			nd = p;
		}
		else if (nd->right != NULL) {
			node* p = nd->right;
			delete nd;
			nd = p;
		}
		else {
			delete nd;
			nd = NULL;
		}
	}
	return nd;
	
}
void delete_node_tree(Binarytree*& tree, int num) {
	delete_node(num, tree->first);
	if (tree->first != NULL) {
		tree->nodes = tree->first->nodes + 1;
	}
}
void PrintMatrix(int** m, int n) {
	printf("  ");
	for (int i = 0; i < n; i++) {
		printf("%2d", i);
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%2d", i);
		for (int j = 0; j < n; j++) {
			printf("%2d", m[i][j]);
		}
		printf("\n");
	}
}
void print(int s, int n,int h) {
	if (n == 0)return;
	for (int i = 0; i < (h - n)/n; i++) {
		printf(" ");
	}
	printf("%d", s);
	for (int i = 0; i < (h - n) / n; i++) {
		printf(" ");
	}
}
void print(int n, int h) {
	if (n == 0)return;
	for (int i = 0; i < (h - n) / n ; i++) {
		printf(" ");
	}
	printf(" ");
	for (int i = 0; i < (h - n) / n ; i++) {
		printf(" ");
	}
}
void PrintBinaryTree(Binarytree* tree) {
	if (tree == NULL || tree->first == NULL) {
		return;
	}
	int* matrix = new int [tree->nodes*2];
	node** Stack = new node * [tree->nodes];
	Stack[0] = tree->first;
	int index = 0;
	for (int i = 0; i < 2*tree->nodes; i++) {
		matrix[i] = -1;
	}
	matrix[0] = 0;
	for (int i = 0; i < tree->nodes; i++) {
		if (Stack[i]->left) {
			Stack[++index] = Stack[i]->left;
			matrix[2 * i + 1] = index;
			
		}
		if (Stack[i]->right) {
			Stack[++index] = Stack[i]->right;
			matrix[2 * i + 2] = index;
		}
	}
	index = 0;
	int stop = 1;
	int k = 1;
	while (index < 2*tree->nodes) {
		if (matrix[index] == -1) {
			print(k, 10*tree->nodes );
		}
		else {
			print(Stack[matrix[index]]->item, k, 10*tree->nodes);
		}
		index += 1;
		if (index == stop) {
			printf("\n");
			k *= 2;
			stop =stop + k;
		}

	}	
	delete[]Stack;
}
void Deletenodes(node*nd) {
	if (nd != NULL) {
		Deletenodes(nd->left);
		Deletenodes(nd->right);
		delete nd;
	}
}
void DeleteTree(Binarytree* tree) {
	Deletenodes(tree->first);
	tree->first = NULL;
	tree->nodes = 0;
}
int main()
{
	Binarytree* tree = new Binarytree;
	add_node(1, tree);
	add_node(-1, tree);
	add_node(2, tree);
	add_node(3, tree);
	add_node(5, tree);
	add_node(0, tree);
	add_node(-2, tree);
	add_node(-10, tree);
	delete_node_tree(tree, 1);
	PrintBinaryTree(tree);

	cout << endl;

	return 0;
}

