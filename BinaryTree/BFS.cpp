#include <iostream>
#include <queue>

struct TreeNode {

	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data) : data(data), left(nullptr), right(nullptr) {}

};

void BFS(TreeNode* root) {

    if (!root)
        return;
    
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
    
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
        
            TreeNode* current = q.front();
            q.pop();

            std::cout << current->data << " ";
        
            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);


        }

        std::cout << "\n";

    
    }

}

void deleteTree(TreeNode* root) {
    
    if (!root)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
    
}

int main() {

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    BFS(root);

    deleteTree(root);

}