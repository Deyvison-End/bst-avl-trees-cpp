#include <iostream>
#include <climits> // INT_MIN e INT_MAX

#include "bst.h"

BinaryTree::Node * BinaryTree::_insert(Node *_root, int key) {

   if (_root == nullptr) {
        _root = new Node(key); 
    }

    else if (key < _root->key) {
        _root->left = _insert(_root->left, key);  
    }
    
    else if (key > _root->key) {
        _root->right = _insert(_root->right, key);  
    }
    
    updateH(_root);
   
    return _root;
}

BinaryTree::Node * BinaryTree::_search(Node *_root, int key) {

	 if (_root == nullptr) {
        return nullptr; 
    }

    else if (key == _root->key ){
        return _root;
    }
    else if (key < _root->key) {
        return _search(_root->left, key);  
    }
    
    else if (key > _root->key) {
       return _search(_root->right, key); 
    }

    return _root;
}

void BinaryTree::_show(Node * _root) {
    if (_root == nullptr) return;

    _show(_root->left);
    cout << "(" << _root->key << ", " << _root->height << ") ";
    _show(_root->right);
}

void BinaryTree::_sort(Node * _root, vector<int> &res) {
    // TODO
    if (_root == nullptr)
        return;

    _sort(_root->left, res);      // esquerda
    res.push_back(_root->key);    // nó
    _sort(_root->right, res);    //direita
    
}

BinaryTree::Node * BinaryTree::_remove(Node *_root, int key) {

	if (_root == nullptr) return nullptr; // (sub) árvore vazia, nada a fazer

	if (key == _root->key) { // Chave encontrada!
		if (_root->left != nullptr && _root->right != nullptr) { // Caso 3
			int maxLeft;
			// Removo o maior filho da esquerda e
			// substituo o valor do nó atual com o valor que era dele
			_root->left = _removeMax(_root->left, maxLeft);
            _root->key = maxLeft;
		} else { // Casos 1 e 2
			Node * tmp = _root;
            _root = (_root->right != nullptr) ? _root->right : _root->left;
			delete tmp;
		}
	} else {
		if (key > _root->key)
            _root->right = _remove(_root->right, key);
		else
            _root->left = _remove(_root->left, key);
	}

	// Lembrar sempre de atualizar a altura; importante para a AVL
	if (_root != nullptr) updateH(_root);

	return _root;
}

BinaryTree::Node * BinaryTree::_removeMax(Node *_root, int & max) {
	if (_root == nullptr) throw std::runtime_error("N�o deveria estar vazia");

	if (_root->right != nullptr) {
        _root->right = _removeMax(_root->right, max);
	} else {
		max = _root->key;
		Node * tmp = _root;
        _root = _root->left;
		delete tmp;
	}

	if (_root != nullptr)
		updateH(_root);

	return _root;
}

// Acha nó _predecessor (pred) a chave (key)
void BinaryTree::_predecessor(Node * _root, Node * & pred, int key) {
	if (_root == nullptr) return;

	if (_root->key == key) { 		// Chave encontrada
		_root = _root->left;			// Desce a esquerda, pred não é mexido inicialmente
		while (_root != nullptr) {
			pred = _root;			// pred vai ser o elemento mais a direita
			_root = _root->right;
		}
	} else {
		if (key < _root->key)		// Chave se encontra a esquerda da raiz
			// não mexemos em pred aqui
            _predecessor(_root->left, pred, key);
		else						// Chave se encontra a direita
			// No caso de _predecessor, pred é atualizado quando descemos a direita
            _predecessor(_root->right, pred = _root, key);
	}
}

// Acha nó sucessor (succ) a chave (key)
void BinaryTree::_successor(Node * _root, Node * & succ, int key) {
    // TODO Desafio
	
}

// Valida a árvore
// min e max são o menor e o maior valores contidas na �rvore, respectivamente
int BinaryTree::_validate(Node * _root, int &min, int &max) {

	if (_root == nullptr) { 
		min = INT_MAX;
		max = INT_MIN;
		return 1;
	}

	int lmin, lmax; // menor e maior a esquerda
	int rmin, rmax; // menor e maior a direita

	
	if (!_validate(_root->left, lmin, lmax) || (lmax > _root->key)) return 0;

	
	if (!_validate(_root->right, rmin, rmax) || (rmin < _root->key)) return 0;

	
	min = (_root->left != nullptr) ? lmin : _root->key;
	max = (_root->right != nullptr) ? rmax : _root->key;

	return 1;
}
