#ifndef AVL_H_
#define AVL_H_

#include "bst.h"

#include <algorithm> // max
using namespace std;

class AVLTree : public BinaryTree {
public:
    // Mesma interface que BinaryTree

private:
    // Funções herdadas

    Node * _insert(Node * root, int key) override;
    Node * _remove(Node * root, int key) override;
    Node * _removeMax(Node * root, int & max) override;

    void _show(Node * root) override;
    int _validate(Node * root, int &min, int &max) override;

    // Funções novas

    static int BF(Node * node) { // Fator de balanceamento
		return H(node->left) - H(node->right);
	}

	static int balanced(Node * node) { // Balanceada?
		return node == nullptr || abs(BF(node)) < 2;
	}

	// Pesada para esquerda ou direita?
	static int leftHeavy(Node * node) { return H(node->left) > H(node->right); }
	static int rightHeavy(Node * node) { return H(node->left) < H(node->right); }

	// Funções de balanceamento e rotação
	static Node * rebalance(Node * node);
	static Node * rotateLeft(Node * node);
	static Node * rotateRight(Node * node);
};


#endif /* AVL_H_ */
