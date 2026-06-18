#include <iostream>
#include "avl.h"

using namespace std;

// Execute com debug para ver que as chamadas de
//  BST::insert() e AVL::_insert() se alternam na pilha de execução.
//  BST::_insert() realiza a inserção de fato, e na volta da recursão
//  AVL::_insert() verifica se está balanceado e faz as rotações se preciso.
BinaryTree::Node * AVLTree::_insert(Node *root, int key) {
	root = BinaryTree::_insert(root, key);

	root = rebalance(root);

	return root;
}

BinaryTree::Node * AVLTree::_remove(Node *root, int key) {
	root = BinaryTree::_remove(root, key);

	root = rebalance(root);

	return root;
}

BinaryTree::Node * AVLTree::_removeMax(Node *root, int & max) {
	root = BinaryTree::_removeMax(root, max);

	root = rebalance(root);

	return root;
}

BinaryTree::Node * AVLTree::rebalance(Node * node) {
	if (node == nullptr || balanced(node)) return node;

	if (leftHeavy(node)) {
		if (rightHeavy(node->left))
            node->left = rotateLeft(node->left);

        node = rotateRight(node);
	} else { // rightHeavy
		if (leftHeavy(node->right))
            node->right = rotateRight(node->right);

        node = rotateLeft(node);
	}

	ASSERT(balanced(node), "Rebalanceamento falhou!");
	return node;
}

// Realiza a rotação a esquerda sobre "node" retornando a nova raiz
BinaryTree::Node * AVLTree::rotateLeft(Node * node) {
	Node * X = node;
	Node * R = node->right;
	Node * RL = node->right->left;

	X->right = RL;
	R->left = X;

	updateH(X); // Primeiro X,
	updateH(R); // Altura de L depedende de X

	node = R;
	return node;
}


BinaryTree::Node * AVLTree::rotateRight(Node * node) {

	Node * X = node;
	Node * L = node->left;
	Node * LR = node->left->right;

	X->left = LR;
	L->right = X;

	updateH(X); // Primeiro X,
	updateH(L); // Altura de L depedende de X

	node = L;
	return node;
}

void AVLTree::_show(Node * root) {
	if (root == nullptr)
		return;
    _show(root->left);
	cout << "(" << root->key << ", "
			<< root->height << ", "
			<< BF(root) << ") ";
    _show(root->right);
}

int AVLTree::_validate(Node * root, int &min, int &max) {
	int valid = BinaryTree::_validate(root, min, max);

	return valid && balanced(root);
}
