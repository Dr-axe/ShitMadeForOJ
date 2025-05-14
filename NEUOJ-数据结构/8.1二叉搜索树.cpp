#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    int num;
    Node* left;
    Node* right;
    Node(int num) : num(num), left(nullptr), right(nullptr) {}
};
class Tree {
public:
    Node* root;
    Tree() : root(nullptr) {}
    void insert(int num) {
        if (root == nullptr) {
            root = new Node(num);
        } else {
            Node* point = root;
            while (true) {
                if (num <= point->num) {
                    if (point->left == nullptr) {
                        point->left = new Node(num);
                        break;
                    }
                    point = point->left;
                } else if (num > point->num) {
                    if (point->right == nullptr) {
                        point->right = new Node(num);
                        break;
                    }
                    point = point->right;
                }
            }
        }
    }
    void print_qianXu(Node* point) {
        if (point == nullptr) return;
        cout << point->num << " ";
        print_qianXu(point->left);
        print_qianXu(point->right);
    }
    void print_zhongXu(Node* point) {
        if (point == nullptr) return;
        print_zhongXu(point->left);
        cout << point->num << " ";
        print_zhongXu(point->right);
    }
};

int main() {
    int commands_num;
    cin >> commands_num;
    Tree tree;
    string command;
    for (int i = 0; i < commands_num; i++) {
        cin >> command;
        if (command == "insert") {
            int num;
            cin >> num;
            tree.insert(num);
        } else {
            tree.print_zhongXu(tree.root);
            cout << endl;
            tree.print_qianXu(tree.root);
            cout << endl;
        }
    }
    return 0;
}