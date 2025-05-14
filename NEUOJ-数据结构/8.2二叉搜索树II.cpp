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
    void search(int num){
        if (root == nullptr) {
            printf("no\n");
        }
        else 
        {
            Node* point=root;
            while (true) {
                if (num==point->num)
                {
                    printf("yes\n");
                    return;
                }
                else if (num < point->num) {
                    if (point->left == nullptr) {
                        printf("no\n");
                        return;
                    }
                    point = point->left;
                } else if (num > point->num) {
                    if (point->right == nullptr) {
                        printf("no\n");
                        return;
                    }
                    point = point->right;
                }
            }
        }
        
    }
    void print_qianXu(Node* point) {
        if (point == nullptr) return;
        printf("%d ",point->num);
        print_qianXu(point->left);
        print_qianXu(point->right);
    }
    void print_zhongXu(Node* point) {
        if (point == nullptr) return;
        print_zhongXu(point->left);
        printf("%d ",point->num);
        print_zhongXu(point->right);
    }
};

int main() {
    int commands_num;
    scanf("%d",&commands_num);
    Tree tree;
    string command;
    for (int i = 0; i < commands_num; i++) {
        cin >> command;
        if (command == "insert") {
            int num;
            scanf("%d",&num);
            tree.insert(num);
        }
        else if (command=="find")
        {
            int num;
            scanf("%d",&num);
            tree.search(num);
        }
        else {
            tree.print_zhongXu(tree.root);
            printf("\n");
            tree.print_qianXu(tree.root);
            printf("\n");
        }
    }
    return 0;
}