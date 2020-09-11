// 红黑树的实现(参考 nginx 源码)
#include <iostream>
#include <queue>
using namespace std;

#define RBT_BLACK(node)     ((node)->color=0)
#define RBT_RED(node)       ((node)->color=1)
#define RBT_IS_RED(node)    ((node!=NULL) && (node)->color)

struct RBTreeNode{
    int key;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parent;
    char color;
    RBTreeNode(int key = 0){
        this->left = this->right = NULL;
        this->parent = NULL;
        this->key = key;
    }
};
class RBTree{
public:
    RBTreeNode *root;

    static void BST_Insert(RBTreeNode *temp, RBTreeNode *node){
        // 将 node 节点插入 temp 表示的红黑树中(普通插入，后续再调整)
        for( ; ; ){
            if(node->key < temp->key){
                if(temp->left == NULL){
                    temp->left = node;
                    break;
                }
                temp = temp->left;
            }else{
                if(temp->right == NULL){
                    temp->right = node;
                    break;
                }
                temp = temp->right;
            }
        }
        node->parent = temp;
        node->left = node->right = NULL;
        RBT_RED(node);  // node 节点设为红
    }
    // 将在 root 中的节点 node 进行左旋                node
    // 左旋条件：node 有右子节点，存在如右侧所示结构:         \
    //                                                  temp
    static void LeftRotate(RBTreeNode* &root, RBTreeNode *node){
        RBTreeNode *temp = node->right;
        node->right = temp->left;
        if(temp->left!=NULL){
            temp->left->parent = node;
        }
        temp->parent = node->parent;
        if(node==root){
            root = temp;
        }else if(node == node->parent->left){
            node->parent->left = temp;
        }else{
            node->parent->right = temp;
        }
        temp->left = node;
        node->parent = temp;
    }
    static void RightRotate(RBTreeNode* &root, RBTreeNode *node){
        RBTreeNode *temp = node->left;
        node->left = temp->right;
        if(temp->right!=NULL){
            temp->right->parent = node;
        }
        temp->parent = node->parent;
        if(node==root){
            root = temp;
        } else if(node == node->parent->right){
            node->parent->right = temp;
        }else{
            node->parent->left = temp;
        }
        temp->right = node;
        node->parent = temp;
    }
    
    RBTree(){
        this->root = NULL;
    }
    void Insert(int key){
        RBTreeNode *node = new RBTreeNode(key), *temp;
        if(this->root == NULL){ 
            // 红黑树为空, 创建节点, 设为黑, 传给 root 属性
            this->root = node;
            RBT_BLACK(this->root);
            return;
        }
        BST_Insert(this->root, node);
        // 通过变色、左旋与右旋等操作使红黑树再平衡
        while(node!=this->root && RBT_IS_RED(node->parent)){ // 父子节点都为红
            // 因为父节点为红色，而红色不能为根节点，因此 node 必定存在祖父节点
            if(node->parent == node->parent->parent->left){
                // node 的父节点是其祖父节点的左节点
                temp = node->parent->parent->right; // temp 为其叔节点
                if(RBT_IS_RED(temp)) {  // 父节点和叔节点都为红，通过变色调整
                    RBT_BLACK(node->parent);
                    RBT_BLACK(temp);
                    RBT_RED(node->parent->parent);
                    node = node->parent->parent;  // 变红的祖父节点视为新节点
                }else{  // 叔节点不为红，需要通过旋转进行调整
                    if(node == node->parent->right){  // 当前节点父节点的右节点
                        node = node->parent;  // 以新节点的父节点为轴进行左旋
                        LeftRotate(this->root, node);
                    }
                    RBT_BLACK(node->parent);
                    RBT_RED(node->parent->parent);
                    RightRotate(root, node->parent->parent);
                }
            } else{
                // node 的父节点是其祖父节点的右节点
                temp = node->parent->parent->left;
                if(RBT_IS_RED(temp)){
                    RBT_BLACK(node->parent);
                    RBT_BLACK(temp);
                    RBT_RED(node->parent->parent);
                    node = node->parent->parent;
                }else{
                    if(node == node->parent->left){
                        node = node->parent;
                        RightRotate(root, node);
                    }
                    RBT_BLACK(node->parent);
                    RBT_RED(node->parent->parent);
                    LeftRotate(root, node->parent->parent);
                }
            }
        }
        RBT_BLACK(root);
    }
};
void ShowTree(RBTreeNode *root){
    if(root==NULL) return;
    cout << " " << root->key << '[' << (RBT_IS_RED(root)?'R':'B') << ']';
    if(root->left==NULL && root->right==NULL){
        return;
    }
    cout << "(";  ShowTree(root->left);
    cout << " , "; ShowTree(root->right);
    cout << ")";
}
int main(int argc, char* argv[]){
    RBTree tree;
    tree.Insert(100); tree.Insert(50);  tree.Insert(150);
    tree.Insert(25);  tree.Insert(12);  tree.Insert(6);
    tree.Insert(9);
    ShowTree(tree.root);
    cout << endl;
    return 0;
}
