#include <iostream>
using namespace std;

struct node;
struct Binarytree; 
void add_node(int num, Binarytree* tree);// добавление узла в бинарное дерево
void PrintBinaryTree(Binarytree*); // вывести на экран бинарное дерево поиском в глубину
void DeleteTree(Binarytree*); // удалить дерево
void delete_node_tree(Binarytree* tree, int num);// удалить узел дерева

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
void delete_node_tree(Binarytree* tree, int num) {
	delete_node(num, tree->first);
	tree->nodes = tree->first->nodes + 1;
}
void PrintBinaryTree(Binarytree* tree) {
	if (tree->first == NULL) {
		return;
	}
	node** Stack = new node * [tree->nodes];
	Stack[0] = tree->first;
	int index = 0;
	for (int i = 0; i < tree->nodes; i++) {
		printf("%d %d, diff = %2d, hight = %2d\n", Stack[i]->item, i + 1, Stack[i]->heighe_difference,Stack[i]->nodes);
		if (Stack[i]->left) {
			Stack[++index] = Stack[i]->left;
		}
		if (Stack[i]->right) {
			Stack[++index] = Stack[i]->right;
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
	Binarytree tree;
	add_node(2, &tree);
	add_node(3, &tree);
	add_node(1, &tree);
	add_node(4, &tree);
	add_node(5, &tree);
	add_node(0, &tree);
	PrintBinaryTree(&tree);
	delete_node_tree(&tree, 5);
	cout << endl;
	PrintBinaryTree(&tree);

	return 0;
}

