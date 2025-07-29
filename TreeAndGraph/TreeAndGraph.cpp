#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int lastPrinted = -1;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value):data(value), left(nullptr), right(nullptr){}
};

bool isRouteExisted(unordered_map<int, vector<int>> graph, int source, int dest) {

    if(source == dest) return true;

    unordered_set<int> visited;
    queue<int> q;

    q.push(source);

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(u == dest) return true;
        visited.insert(u);

        for(int i:graph[u]) {
            if(visited.find(i) == visited.end()) {
                q.push(i);
            }
        }
    }    
    return false;
}

vector<list<TreeNode*>> createLinkListFromTreeNodes(TreeNode* root) {
    vector<list<TreeNode*>> result;
    list<TreeNode*> current;

    current.push_back(root);
    cout<<"\n current size: "<<current.size();

    while(current.size() > 0) {
        result.push_back(current);
        
        list<TreeNode*> parents = current;
        current.clear();
        
        for(TreeNode* parent:parents) {
            if(parent->left != nullptr)
                current.push_back(parent->left);
            if(parent->right != nullptr)
                current.push_back(parent->right);    
        }
    }
    cout<<"\n result size: "<<result.size();
    return result;    
}

void printResult(vector<list<TreeNode*>> root) {
    for (int i = 0; i < root.size(); i++) {
        cout << "\n level " << i << ": ";
        for (TreeNode* node : root[i]) {
            cout << node->data << " ";
        }
    }
    cout << endl;
}

int getHeight(TreeNode* root) {
    if(root == nullptr) return -1;

    return max(getHeight(root->left), getHeight(root->right)) +1 ;
}

TreeNode* minValueNode(TreeNode* root) {
    TreeNode* current = root;
    while(current && current->left) {
        current = current->left;
    }
    return current;
}

TreeNode* findSuccessor(TreeNode* root, TreeNode* target) {
    TreeNode* succ = nullptr;

    while(root) {
        if(root->data > target->data) {
            root = root->left;
            succ = root;
        }
        else {
            root = root->right;
        }
    }
    return succ;
}

bool isBalancedTree(TreeNode* root) {
    if(root == nullptr) return true;

    int left = getHeight(root->left);
    int right = getHeight(root->right);

    int diff = left-right;

    if(abs(diff) > 1) {
        return false;
    }
    else {
        return isBalancedTree(root->left) && isBalancedTree(root->right);
    }
}

bool isBSTSecond(TreeNode* root, int min, int max) {

    if(root == nullptr) return true;

    if((root->data <= min) || (root->data > max)) return false;

    if(!isBSTSecond(root->left, min, root->data) || !isBSTSecond(root->right, root->data, max)) return false;
    return true;
}

bool isBST(TreeNode* root) {
    // First approach, chekcing the sorted element property. 
   /* if(root == nullptr) return true;
    if(!isBST(root->left)) return false;
    if(root->data <= lastPrinted) return false;
    lastPrinted = root->data;

    if(!isBST(root->right)) return false;
    return true; */

    // Second approach is to use the BST property, which is root.left.data<=root.data<root.right.data
    int min = -1;
    int max = -1;
    return isBSTSecond(root, min, max);
}

//LCA in binary tree.
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    if(!root || root == p || root == q) return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if(left && right) return root;

    return left?left:right;
}

//LCA in BST
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {

    if(!root) return root;
    int val = root->data;

    if(p->data > val && q->data > val) {
        return lowestCommonAncestorBST(root->right, p,q);
    }
    if(p->data < val && q->data < val) {
        return lowestCommonAncestorBST(root->left, p,q);
    }
    return root;
}

//T1 Tree contains T2 Tree 

bool matchTree(TreeNode* r1, TreeNode* r2) {
    if(!r1 && !r2) return true;
    //if(!r1 || !r2) return false;
    if(!r1) return false;
    if(!r2) return true;
    if(r1->data != r2->data) return false;
    return (matchTree(r1->left, r2->left) && matchTree(r1->right, r2->right));
}

bool containsTree(TreeNode* T1, TreeNode* T2) {
    if(!T2) return true;
    if(!T1) return false;
    if(matchTree(T1, T2)) return true;
    return containsTree(T1->left, T2) || containsTree(T1->right, T2);
}

TreeNode* createMinimalHeightTree(vector<int> array) {
    int size= array.size();

    return createMinimalHeightTreeHelper(array, 0, size-1);
}

TreeNode* createMinimalHeightTreeHelper(vector<int> array, int start, int end) {
    if(end < start) return nullptr;

    int mid = (start+end)/2;
    TreeNode* n = new TreeNode(mid);
    n->left = createMinimalHeightTreeHelper(array, start,mid-1);
    n->right = createMinimalHeightTreeHelper(array, mid+1, end);

    return n;
}

void printInOrderTree(TreeNode* root) {
    if(root == nullptr) return;

    printInOrderTree(root->left);
    cout<<"->"<<root->data;    
    printInOrderTree(root->right);
}

int main() {

    unordered_map<int, vector<int>> graph;
    graph[0] = {1,2};
    graph[1] = {3};
    graph[2] = {};
    graph[3] = {4};
    graph[4] = {};

    vector<int> inputArray = {1,2,3,4,5,6,7};

    TreeNode* minimalHeightTree = createMinimalHeightTree(inputArray);
    printInOrderTree(minimalHeightTree);

    //cout<<"\n route between nodes existed: "<<isRouteExisted(graph, 2,4);

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->left->left = new TreeNode(5);
    root->right->left = new TreeNode(6);

    TreeNode* root2 = new TreeNode(1);
    //root2->left = new TreeNode(2);
    //root2->right = new TreeNode(3);
    //root2->left->left = new TreeNode(4);

    //vector<list<TreeNode*>> result = createLinkListFromTreeNodes(root);
    //printResult(result);
    cout<<"\n Given tree is balanced?: "<<isBalancedTree(root);
    cout<<"\n Given tree is BST? : "<<isBST(root);

    cout<<"\n contains tree: "<<containsTree(root, root2);

    return 0;
}
