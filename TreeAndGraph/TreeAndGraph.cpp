#include<iostream>
#include<bits/stdc++.h>

using namespace std;

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
int main() {

    unordered_map<int, vector<int>> graph;
    graph[0] = {1,2};
    graph[1] = {3};
    graph[2] = {};
    graph[3] = {4};
    graph[4] = {};

    //cout<<"\n route between nodes existed: "<<isRouteExisted(graph, 2,4);

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->left->left = new TreeNode(5);
    root->right->left = new TreeNode(6);

    //vector<list<TreeNode*>> result = createLinkListFromTreeNodes(root);
    //printResult(result);
    cout<<"\n Given tree is balanced?: "<<isBalancedTree(root);


    return 0;
}
