#include <iostream>

struct TreeNode {

	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data) : data(data), left(nullptr), right(nullptr) {}

};

TreeNode* insert(TreeNode* root, int val) {

	if (!root) {
	
		root = new TreeNode(val);
		return root;
	
	}

	if (val < root->data)
		root->left = insert(root->left, val);
	else if (val > root->data)
		root->right = insert(root->right, val);
		
	return root;

}

void preorderTraversal(TreeNode* root) {

	if (!root)
		return;

	std::cout << root->data << " ";
	preorderTraversal(root->left);
	preorderTraversal(root->right);

}

// print BST in ascending order
void inorderTraversal(TreeNode* root) {

	if (!root)
		return;

	inorderTraversal(root->left);
	std::cout << root->data << " ";
	inorderTraversal(root->right);

}

void postorderTraversal(TreeNode* root) {

	if (!root)
		return;

	postorderTraversal(root->left);
	postorderTraversal(root->right);
	std::cout << root->data << " ";

}

void deleteTree(TreeNode* root) {

	if (!root)
		return;

	deleteTree(root->left);
	deleteTree(root->right);
	delete root;

}

int main() {
	
	TreeNode* root = new TreeNode(5);
	root->left = new TreeNode(3);
	root->right = new TreeNode(7);
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(4);
	root->right->left = new TreeNode(6);
	root->right->right = new TreeNode(8);

	inorderTraversal(root);

	deleteTree(root);

}
