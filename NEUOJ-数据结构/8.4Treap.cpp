/*写的有亿点乱*/
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int num, priority;
    Node* left;
    Node* right;
    Node(int num, int pr) : num(num), priority(pr), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;
    Tree() : root(nullptr) {}

    void search(int num) {
        Node* point = root;
        while (point != nullptr) {
            if (num == point->num) {
                cout << "yes" << endl;
                return;
            } else if (num < point->num) {
                point = point->left;
            } else {
                point = point->right;
            }
        }
        cout << "no" << endl;
    }

    void del(int num) {
        root = del(root, num);
    }

    Node* del(Node* t, int key) {
        if (t == nullptr) {
            return nullptr;
        }
        if (key < t->num) {
            t->left = del(t->left, key);
        } else if (key > t->num) {
            t->right = del(t->right, key);
        } else {
            if (t->left == nullptr && t->right == nullptr) {
                delete t;
                return nullptr;
            } else if (t->left == nullptr) {
                Node* temp = t->right;
                delete t;
                t = temp;
            } else if (t->right == nullptr) {
                Node* temp = t->left;
                delete t;
                t = temp;
            } else {
                if (t->left->priority > t->right->priority) {
                    t = rightRotate(t);
                    t->right = del(t->right, key);
                } else {
                    t = leftRotate(t);
                    t->left = del(t->left, key);
                }
            }
        }
        return t;
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

    Node* rightRotate(Node* t) {
        Node* s = t->left;
        t->left = s->right;
        s->right = t;
        return s;
    }

    Node* leftRotate(Node* t) {
        Node* s = t->right;
        t->right = s->left;
        s->left = t;
        return s;
    }

    void treap_Insert(int key, int priority) {
        root = treap_Insert(root, key, priority);
    }

    Node* treap_Insert(Node* t, int key, int priority) {
        if (t == nullptr) {
            return new Node(key, priority);
        }
        if (key == t->num) {
            return t;
        } else if (key < t->num) {
            t->left = treap_Insert(t->left, key, priority);
            if (t->priority < t->left->priority) {
                t = rightRotate(t);
            }
        } else {
            t->right = treap_Insert(t->right, key, priority);
            if (t->priority < t->right->priority) {
                t = leftRotate(t);
            }
        }
        return t;
    }
};

int main() {
    int commands_num;
    cin >> commands_num;
    Tree tree;
    string command;
    int priority = 0;
    for (int i = 0; i < commands_num; i++) {
        cin >> command;
        if (command == "insert") {
            int num;
            cin >> num >> priority;
            tree.treap_Insert(num, priority);
        } else if (command == "find") {
            int num;
            cin >> num;
            tree.search(num);
        } else if (command == "delete") {
            int num;
            cin >> num;
            tree.del(num);
        } else {
            tree.print_zhongXu(tree.root);
            cout << endl;
            tree.print_qianXu(tree.root);
            cout << endl;
        }
    }
    return 0;
}