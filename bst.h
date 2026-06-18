#ifndef BST_H_
#define BST_H_

#include <algorithm> // max
#include <system_error>
#include <vector>

using namespace std;

#define ASSERT(X, E) if(!(X)) throw (std::runtime_error(E));

class BinaryTree {
protected:
	struct Node {
		int key;
		int height; // altura da árvore em níveis
		Node * left;
		Node * right;
		explicit Node(int key) : key(key), height(1), left(nullptr), right(nullptr) {}
	};

	// Pega a altura. Simplifica código no caso de subárvore vazia (nullptr)
	static int H(Node * node) { return (node != nullptr)?node->height:0; }

	// Atualiza a altura de um nó da árvore. Assume que a altura das subárvore está correta.
	static void updateH(Node * node) { node->height = max(H(node->left), H(node->right)) + 1; }

	Node * root = nullptr;
    int num_items = 0;

public:
	BinaryTree() = default;

	virtual ~BinaryTree() {
        _deleteTree(root);
	}

	virtual void insert(int key) {
		root = _insert(root, key);
        num_items++;
		ASSERT(validate(), "inser(): invalid tree!");
	}

	virtual void remove(int key) {
		root = _remove(root, key);
        num_items--;
		ASSERT(validate(), "_remove(): invalid tree!");
	}

	virtual bool search(int key) {
		return _search(root, key) != nullptr;
	}

	virtual int  predecessor(int key) {
		Node * node = nullptr;
        _predecessor(root, node, key);
		return (node != nullptr)?node->key:-1;
	}

	virtual int  successor(int key) {
		Node * node = nullptr;
        _successor(root, node, key);
		return (node != nullptr)?node->key:-1;
	}

	virtual int  validate() {
		int min, max;
		return _validate(root, min, max);
	}

	virtual void show() {
        _show(root);
	}

    virtual void sort(vector<int> &res) {
        _sort(root, res);
    }

    virtual int size() {
        return num_items;
    }

protected:
	void _deleteTree(Node * node) {
		if (node == nullptr) return;
        _deleteTree(node->left);
        _deleteTree(node->right);
		delete node;
	}

	virtual Node * _insert(Node *_root, int key);
    virtual Node * _search(Node *_root, int key);
	virtual Node * _remove(Node *_root, int key);
	virtual Node * _removeMax(Node *_root, int & max);
	virtual void _predecessor(Node * _root, Node * & pred, int key);
	virtual void _successor(Node * _root, Node * & succ, int key);

	virtual void   _show(Node * _root);
    virtual void   _sort(Node * _root, vector<int> &res);
	virtual int    _validate(Node * _root, int &min, int &max);
};



#endif /* BST_H_ */
