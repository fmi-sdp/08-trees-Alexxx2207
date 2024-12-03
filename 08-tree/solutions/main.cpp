#include <iostream>
#include <vector>

using namespace std;

// ex1 
template <typename T>
struct Tree {
    T data;
    vector<Tree*> children;

    Tree(T d, vector<Tree*> c) : data(d), children(c) {}

    int branchingFactor() const {
        if(children.empty()) {
            return 0;
        }

        int result = children.size();

        for (Tree const* child : children) {
            result = max(result, child->branchingFactor());
        }

        return result;
    }

    void printLevel(unsigned level) const {
        if(level == 0) {
            cout <<" " << this->data << " ";
            return;
        } 

        for(Tree const* child : this->children) {
            child->printLevel(level-1);
        }
    }

    int countLeaves() const {
        if(this->children.empty()) {
            return 1;
        }
        
        int acc = 0;
        for(Tree const* child : this->children) {
            acc += child->countLeaves();  
        }

        return acc;
    }
};

template <typename T>
struct BinaryTree {
    T data;
    BinaryTree* left;
    BinaryTree* right;

    BinaryTree(T d, BinaryTree* l = nullptr, BinaryTree* r = nullptr) : data(d), left(l), right(r) {}

    void inorder() const {
        if(left)
            left->inorder();
        std::cout << " " << data << " ";
        if(right) 
            right->inorder();
    }

    void preorder() const {
        std::cout << " " << data << " ";
        if(left)
            left->preorder();
        if(right) 
            right->preorder();
    }
    void postorder() const {
        if(left)
            left->postorder();
        if(right) 
            right->postorder();
        std::cout << " " << data << " ";
    }

    void trim() {
        if(!left && !right) {
            cout << "Tree becomes empty. Root node is removed" << endl;
        }

        if(left && !left ->left && !left ->right) {
            delete left;
            left = nullptr;
        } else if(left) {
            left->trim();
        }

        if (right && !right->left && ! right->right) {
            delete right;
            right = nullptr;
        } else if(right) {
            right->trim();
        }
    }

    void bloom() {
        if(left && !left->left && !left->right) {
            left->left = new BinaryTree(left->data);
            left->right = new BinaryTree(left->data);
        } else if (left) {
            left->bloom();
        }

        if(right && !right->left && !right->right) {
            right->left = new BinaryTree(right->data);
            right->right = new BinaryTree(right->data);
        } else if (right) {
            right->bloom();
        }
    }
};


int main(int, char**){
    BinaryTree bt(4,
        new BinaryTree (2,
            new BinaryTree(1),
            new BinaryTree(3)
        ),
        new BinaryTree (6,
            new BinaryTree(5),
            new BinaryTree(7)
        )
    );

    //bt.inorder();
    // cout << endl;
    // bt.preorder();
    // cout << endl;
    // bt.postorder();

    // bt.trim();
    // bt.inorder();
    // cout << endl;

    // BinaryTree bt1(1);
    // bt1.trim();
    // bt1.inorder();
    // cout << endl;

    // bt.bloom();
    // bt.inorder();


    Tree tree = Tree(0, {
        new Tree(1, {
            new Tree (4, {}),
            new Tree (5, {}),
            new Tree (6, {}),
        }), 
        new Tree(2, {
            new Tree (7, {}),
            new Tree (8, {}),
            new Tree (9, {}),
            new Tree (10, {
                new Tree(13, {})
            }),
        }), 
        new Tree(3, {
            new Tree (11, {}),
            new Tree (12, {}),
        }), 
    });

    // cout << "Factor: " << tree.branchingFactor() << endl;

    // tree.printLevel(0);
    // cout << endl;
    // tree.printLevel(1);
    // cout << endl;
    // tree.printLevel(2);
    // cout << endl;
    // tree.printLevel(3);
    // cout << endl;

    cout << "Leaves count: " << tree.countLeaves() << endl;
}
