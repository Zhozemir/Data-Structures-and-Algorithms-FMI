#include <iostream>

struct TreeNode {

	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data) : data(data), left(nullptr), right(nullptr) {}

};

int countNodes(TreeNode* root) {

	if (!root)
		return 0;

	if (!root->left && !root->right)
		return 1;

	return 1 + countNodes(root->left) + countNodes(root->right);

}

int sumNodes(TreeNode* root) {

	if (!root)
		return 0;

	return root->data + sumNodes(root->left) + sumNodes(root->right);

}

int maxElement(TreeNode* root) {

	if (!root)
		throw std::invalid_argument("Tree is nullptr");

	if (!root->left && !root->right)
		return root->data;

	return std::max(root->data, std::max(maxElement(root->left), maxElement(root->right)));

}

bool contains(TreeNode* root, int value) {

	if (!root)
		return false;

	if (root->data == value)
		return true;

	return contains(root->left, value) || contains(root->right, value);

}

bool isLeaf(TreeNode* node) {

	return node && !node->left && !node->right;

}

int getHeight(TreeNode* root) {

	if (!root)
		return -1;

	return 1 + std::max(getHeight(root->left), getHeight(root->right));

}

void deleteTree(TreeNode* root) {

	if (!root)
		return;

	deleteTree(root->left);
	deleteTree(root->right);

	delete root;
	
}

int main() {

	TreeNode* root = new TreeNode(6);
	root->left = new TreeNode(3);
	root->right = new TreeNode(8);
	root->left->left = new TreeNode(7);
	root->left->right = new TreeNode(1);
	root->right->left = new TreeNode(5);
	root->right->right = new TreeNode(6);

	std::cout << maxElement(root) << std::endl;
	
	deleteTree(root);

}


