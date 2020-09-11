#include <iostream>
using namespace std;

class Node{
public:
    int key;
    Node *lc;   // 左子树
    Node *rc;   // 右子树
    Node(int key){
        this->key = key;
        this->lc = this->rc = NULL;
    }
};
void DestroyNode(Node *node){
    if(node==NULL) return;
    DestroyNode(node->lc);
    DestroyNode(node->rc);
    node->lc = node->rc = NULL;
    delete node;
}
Node *SearchTree(int key, Node *root){
    if(root == NULL) return NULL;
    if(root->key == key) return root;
    if(key < root->key) return SearchTree(key, root->lc);
    else return SearchTree(key, root->rc);
}
void InsertKey(int key, Node *&root){
    if(root == NULL){
        root = new Node(key);
        return;
    }
    if(key < root->key) InsertKey(key, root->lc);
    else InsertKey(key, root->rc);
}
// 找到并删除一个成功，返回0，否则返回1
int RemoveKey(int key, Node *&root){
    if(root == NULL) return 1;
    if(root->key == key){
        if(root->rc != NULL){
            // 找到右子树 key 最小节点的父节点
            // 根节点的右节点即为最小key节点
            if(root->rc->lc==NULL){
                Node *rc = root->rc;
                root->key = rc->key;
                root->rc = rc->rc;
                delete rc;
            }else{
                Node *p = root->rc;
                while(p->lc->lc != NULL) p = p->lc;
                Node *lc = p->lc;
                root->key = lc->key;
                p->lc = lc->rc;
                delete lc;
            }
            return 0;
        }else if(root->lc != NULL){
            // 找到左子树 key 最大节点的父节点
            // 根节点的左节点即为最大key节点
            if(root->lc->rc==NULL){
                Node *lc = root->lc;
                root->key = lc->key;
                root->lc = lc->lc;
                delete lc;
            }else{
                Node *p = root->lc;
                while(p->rc->rc != NULL) p = p->rc;
                Node *rc = p->rc;
                root->key = rc->key;
                p->rc = rc->lc;
                delete rc;
            }
            return 0;
        }else{
            delete root;
            root = NULL;
            return 0;
        }
    }else if(key < root->key){
        return RemoveKey(key, root->lc);
    }else{
        return RemoveKey(key, root->rc);
    }
}
// 以中序遍历显示有序二叉树
void Display(Node *root, ostream& out = cout){
    if(root == NULL) return;
    Display(root->lc);
    out << root->key << ' ';
    Display(root->rc);
}
class NormalBST{
private:
    Node *root;
    // int cnt;
public:
    NormalBST(){
        this->root = NULL;
        // this->cnt = 0;
    }
    ~NormalBST(){
        DestroyNode(this->root);
    }
    Node* Search(int key){
        return SearchTree(key, this->root);
    }
    void Insert(int key){
        InsertKey(key, this->root);
    }
    int Remove(int key){
        return RemoveKey(key, root);
    }
    friend ostream& operator<<(ostream& o, NormalBST &bst){
        Display(bst.root, o);
        return o;
    }
};
int main(int argc, char *argv[]){
    NormalBST bst;
    int a[] = {20, 33, 68, 7, 19, 29, 58, 23, 17, 99,45};
    for(int i=0; i < sizeof(a)/sizeof(*a); ++i)
        bst.Insert(a[i]);
    cout << "origin   : " << bst << endl;
    bst.Remove(33);
    cout << "remove 33: " << bst << endl;
    bst.Remove(7);
    cout << "remove  7: " << bst << endl;
    bst.Remove(20);
    cout << "remove 20: " << bst << endl;
    cout << "remove 11 result: " << 
        (bst.Remove(11)==0?"success":"fail") << endl;
    bst.Insert(39);
    cout << "insert 39: " << bst << endl;
}

