#include<iostream>
#include<queue>
using namespace std;

struct node {
    string position;
    node* first;
    node* second;
};

struct org_tree{
    node* root;
    
    static org_tree create_org_structure(const string& pos) {
        org_tree tree;
        tree.root = new node {pos, NULL, NULL};
        return tree;
    }

    // ?듅?젙 吏곸콉 ?씠由꾩뿉 ?빐?떦?븯?뒗 ?끂?뱶瑜? 李얠븘?꽌 諛섑솚
    static node* find(node* root, const string& value) {
        cout << "root : " << root << endl;
        if (root == NULL)
            return NULL;
        
        if (root->position == value)
            return root;
        
        auto firstFound = org_tree::find(root->first, value);

        if (firstFound != NULL)
            return firstFound;
        
        return org_tree::find(root->second, value);
    }

    // ?깉濡쒖슫 ?썝?냼瑜? 異붽???븯?뒗 ?궫?엯 ?븿?닔
    bool addSubordinate(const string& manager, const string& subordinate) {
        auto managerNode = org_tree::find(root, manager);

        if (!managerNode){
            cout << manager << "을(를) 찾을 수 없습니다: " << endl;
            return false;
        }

        if (managerNode->first && managerNode->second) {
            cout << manager << " 아래에 " << subordinate << "을(를) 추가할 수 없습니다." << endl;
            return false;
        }

        if (managerNode->first)
            managerNode->first = new node {subordinate, NULL, NULL};
        else 
            managerNode->second = new node {subordinate, NULL, NULL};

        cout << manager << " 아래에 " << subordinate << "을(를) 추가했습니다." << endl;

        return true;
    }

    static void levelOrder(node* start) {
        if (!start)
            return;

        queue<node*> q;
        q.push(start);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i<size; i++) {
                auto current = q.front();
                q.pop();

                cout << current->position << ", ";
                if (current->first)
                    q.push(current->first);
                if (current->second)
                    q.push(current->second);
            }

            cout << endl;
        }
    }
};

int main() {
    auto tree = org_tree::create_org_structure("CEO");

    tree.addSubordinate("CEO", "부사장");
    tree.addSubordinate("부사장", "IT부장");
    tree.addSubordinate("부사장", "마케팅부장");
    tree.addSubordinate("IT부장", "보안팀장");
    tree.addSubordinate("IT부장", "앱개발팀장");
    tree.addSubordinate("마케팅부장", "물류팀장");
    tree.addSubordinate("마케팅부장", "홍보팀장");
    tree.addSubordinate("부사장", "재무부장");

    org_tree::levelOrder(tree.root);
    
    return 0;   
}