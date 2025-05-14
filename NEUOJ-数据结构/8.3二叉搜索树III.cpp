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
    void del(int num){
        if (root == nullptr) {
            return;
        }
        else 
        {
            Node* point=root;
            Node* old;
            while (true) {
                if (num==point->num)
                {
                    int l=point->left==nullptr;
                    int r=point->right==nullptr;//判断器
                    if (!r&&!l)
                    {
                        int w;
                        old=point;
                        point=point->right;
                        while (point->left!=nullptr)
                        {
                            point=point->left;
                        }
                        w=point->num;
                        del(w);
                        old->num=w;
                    }
                    else if (!r)
                    {
                        point->num=point->right->num;
                        point->left=point->right->left;
                        point->right=point->right->right;
                    }
                    else if (!l)
                    {
                        point->num=point->left->num;
                        point->right=point->left->right;
                        point->left=point->left->left;
                    }
                    else
                    {
                        if (old->left==point)
                        {
                            old->left=nullptr;
                        }
                        else if (old->right==point)
                        {
                            old->right=nullptr;
                        }
                    }
                    return;
                }
                else if (num < point->num) {
                    if (point->left == nullptr) {
                        return;
                    }
                    old=point;
                    point = point->left;
                } else if (num > point->num) {
                    if (point->right == nullptr) {
                        printf("no\n");
                        return;
                    }
                    old=point;
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
        else if (command=="delete")
        {
            int num;
            scanf("%d",&num);
            tree.del(num);
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