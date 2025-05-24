#include <bits/stdc++.h>

using namespace std;

class Node{
public:
    string node_type;
    Node *child;
    Node *sibling;
    int value;
    bool seen;

    Node(string node_type){
        this->node_type = node_type;
        this->child = NULL;
        this->sibling = NULL;
        if (node_type == "max")
            this->value = INT_MIN;
        else if (node_type == "min")
            this->value = INT_MAX;
        this->seen = false;
    }

    int search(int alpha, int beta){
        // Minimax (DFS) with alpha-beta pruning
        this->seen = true;
        if (node_type == "max"){
            for (Node *next=child; next; next=next->sibling){
                this->value = max(this->value, next->search(alpha, beta));
                alpha = max(alpha, this->value);
                if (alpha >= beta)
                    break;
            }
        }
        else if (node_type == "min"){
            for (Node *next = child; next; next = next->sibling){
                this->value = min(this->value, next->search(alpha, beta));
                beta = min(beta, this->value);
                if (alpha >= beta)
                    break;
            }
        }
        return this->value;
    }

    void display(bool showPruning){
        // level order display
        queue<Node*> level({this});
        int curCnt(1), nextCnt(0);
        while (not level.empty()){
            Node *cur = level.front();
            level.pop();
            if ((showPruning == true) && (not cur->seen))
                cout << "X ";
            else 
                cout << cur->value << " ";
            curCnt--;
            for (Node *i = cur->child; i; i = i->sibling){
                level.push(i);
                nextCnt++;
            }
            if (curCnt == 0){
                curCnt = nextCnt;
                nextCnt = 0;
                cout << endl;
            }
        }
    }
};

int main(){
    vector<int> leaves = {5,6,7,4,5,3,6,6,9,7,5,9,8,6};
    vector<pair<string, vector<int>>> combination_logic = 
    {
        {"min", {2, 3, 1, 1, 2, 1, 1, 2, 1}},
        {"max", {2, 1, 2, 1, 1, 2}},
        {"min", {2, 2, 2}},
        {"max", {3}}
    };
    vector<Node*> nodes;

    // initialize leaf nodes
    for (int i : leaves){
        Node *temp = new Node("max");
        temp->value = i;
        nodes.push_back(temp);
    }

    // build game tree
    for (auto logic : combination_logic){
        for (int i: logic.second){
            Node *node = new Node(logic.first);
            Node *prev;
            for (int j=0; j<i; j++){
                if (j == 0){
                    node->child = nodes[j];
                }
                else{
                    prev->sibling = nodes[j];
                }
                prev = nodes[j];
            }
            nodes.erase(nodes.begin(), nodes.begin()+i);
            nodes.push_back(node);
        }
    }
    Node *root = nodes[0];
    //root->search(INT_MIN, INT_MAX);
    root->search(INT_MIN, INT_MAX);
    root->display(false);
    return 0;
}