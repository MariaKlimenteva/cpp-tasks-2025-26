#include <iostream>
#include <memory>
#include <queue>
#include <vector>

class Tree {
public:
    struct Node {
        int value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;

        Node(int v) : value(v) {}
        
        ~Node() {
            std::cout << "Node " << value << " destroyed" << std::endl;
        }
    };

    std::shared_ptr<Node> root;

    void traverse_v1() const {
        if (!root) return;
        std::queue<std::shared_ptr<Node>> q;
        q.push(root);
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            std::cout << current->value << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }

    void traverse_v2() const {
        dfs(root);
        std::cout << std::endl;
    }

private:
    void dfs(const std::shared_ptr<Node>& node) const {
        if (!node) return;
        std::cout << node->value << " ";
        dfs(node->left);
        dfs(node->right);
    }
};

int main() {
    auto tree = std::make_unique<Tree>();

    tree->root = std::make_shared<Tree::Node>(1);

    tree->root->left = std::make_shared<Tree::Node>(2);
    tree->root->left->parent = tree->root;
    tree->root->right = std::make_shared<Tree::Node>(3);
    tree->root->right->parent = tree->root;

    tree->root->left->left = std::make_shared<Tree::Node>(4);
    tree->root->left->left->parent = tree->root->left;
    tree->root->left->right = std::make_shared<Tree::Node>(5);
    tree->root->left->right->parent = tree->root->left;

    tree->root->right->left = std::make_shared<Tree::Node>(6);
    tree->root->right->left->parent = tree->root->right;
    tree->root->right->right = std::make_shared<Tree::Node>(7);
    tree->root->right->right->parent = tree->root->right;

    std::cout << "BFS (traverse_v1): ";
    tree->traverse_v1();

    std::cout << "DFS (traverse_v2): ";
    tree->traverse_v2();

    std::cout << "--- Destruction sequence ---" << std::endl;
    tree.reset();

    return 0;
}

// g++ -std=c++23 02.cpp -o task2