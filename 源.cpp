#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <string>


using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//������������������ݹ飩
void perorder(TreeNode* head) {
    if (head == nullptr) {
        return;
    }
    cout << head->val << endl;
    perorder(head->left);
    perorder(head->right);
}

//������������������ݹ飩
void midorder(TreeNode* head) {
    if (head == nullptr) {
        return;
    }
    midorder(head->left);
    cout << head->val << endl;
    midorder(head->right);
}

//�������ĺ���������ݹ飩
void posorder(TreeNode* head) {
    if (head == nullptr) {
        return;
    }
    posorder(head->left);
    posorder(head->right);
    cout << head->val << endl;
}

//�����������������������ȣ�
void preorderunrecur(TreeNode* head) {
    if (head != nullptr) {
        stack<TreeNode*> st;
        st.push(head);
        while (!st.empty()) {
            //����ջ���ڵ�
            head = st.top();
            st.pop();
            cout << head->val << endl;
            //��ջ���ڵ�����ҽڵ����ջ��
            if (head->right != nullptr) {
                st.push(head->right);
            }
            if (head->left != nullptr) {
                st.push(head->left);
            }
        }
    }
}

//�������ĺ������
void posorderunrecur(TreeNode* head) {
    if (head != nullptr) {
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        s1.push(head);
        //s1��ջ˳��Ϊͷ����
        //s2��ջ˳��Ϊ����ͷ
        while (!s1.empty()) {
            head = s1.top();
            s1.pop();
            s2.push(head);
            if (head->left != nullptr) {
                s1.push(head->left);
            }
            if (head->right != nullptr) {
                s1.push(head->right);
            }
        }
        while (!s2.empty()) {
            cout << s2.top()->val << endl;
            s2.pop();

        }
    }
}

//���������������
void midordertree(TreeNode* head) {
    if (head != nullptr) {
        stack<TreeNode*> st;
        while (!st.empty() || head != nullptr) {
            //��������������ջ��
            if (head != nullptr) {
                st.push(head);
                head = head->left;
            }
            else {
                head = st.top();
                st.pop();
                cout << head->val << endl;//�����ս��Ϊ������Ϊ����������
                head = head->right;
            }
        }
    }
}

//��������������
void orderTree(TreeNode* head) {
    if (head == nullptr) {
        return;
    }
    queue<TreeNode*> q;
    q.push(head);
    unordered_map<TreeNode*, int> levelmap;
    levelmap.insert({ head,1 });
    int curlevel = 1;
    int curlevelNodes = 0;
    int maxwidth = 0;
    while (!q.empty()) {
        head = q.front();
        q.pop();
        int curNodelevel = levelmap[head];
        if (curNodelevel == curlevel) {
            curlevelNodes++;
        }
        else {
            maxwidth = max(maxwidth, curlevelNodes);
            curlevel++;
            curlevelNodes = 1;
        }
        cout << head->val << endl;
        if (head->left != nullptr) {
            levelmap.insert({ head->left,curNodelevel + 1 });
            q.push(head->left);
        }
        if (head->right != nullptr) {
            levelmap.insert({ head->right,curNodelevel + 1 });
            q.push(head->right);
        }
    }
};

//�������Ĳ������
void testTree(TreeNode* head) {
    if (head != nullptr) {
        queue<TreeNode*> q;
        q.push(head);
        while (!q.empty()) {
            head = q.front();
            q.pop();
            cout << head->val << endl;
            if (head->left != nullptr) {
                q.push(head->left);
            }
            if (head->right != nullptr) {
                q.push(head->right);
            }
        }
    }
};

//�ж�һ�����Ƿ�Ϊ��ȫ������
bool isCBT(TreeNode* head) {
    bool leaf = false;
    queue<TreeNode*> q;
    TreeNode* l = nullptr;
    TreeNode* r = nullptr;
    q.push(head);
    while (!q.empty()) {
        head = q.front();
        l = head->left;
        r = head->right;

        if (
            (leaf && (l != nullptr || r != nullptr))
            //��Ҷ�ӽڵ�����������ʱ����Ϊ��ȫ������
            ||
            (l == nullptr || r == nullptr))
            //��ĳ�ڵ���������û��������������ȫ������
        {
            return false;
        }
        if (l != nullptr) {
            q.push(l);
        }
        if (r != nullptr) {
            q.push(r);
        }
        //����һ�γ���������������ʱ������Ľڵ㶼ΪҶ�ӽڵ�
        if (l == nullptr || r == nullptr) {
            leaf = true;
        }
    }
    return true;
}


class edge;
//ͼ�ĵ㼯
class Node {
public:
    int value;
    int in;
    int out;
    vector<Node*> nexts;
    vector<edge> edges;
    Node(int val) : value(val), in(0), out(0) {}
};
//ͼ�ı߼�
class edge {
public:
    int weight;
    Node to;
    Node from;
    edge(int _weight, Node& _to, Node& _from) : weight(_weight), to(_to), from(_from) {}
    edge(Node& _to,Node& _from): weight(0),to(_to),from(_from){}
    bool operator<(const edge& other) const {
        return weight < other.weight;
    }
};
 
//ͼ
class Graph {
public:
    unordered_map<int, Node*> nodes;  
    vector<edge> edges;
};

class mysets :public Graph {
public:
    //��¼ÿ���ڵ����ڵļ���
    unordered_map<Node*, vector<Node*>> setmap;

    //��ʼ��myset��һ��ʼÿһ���ڵ�����Ӧ�ļ���ֻ���Լ�
    void init(){
        for (const auto& pair : nodes) {
            vector<Node*> set;
            set.push_back(pair.second);
            setmap[pair.second] = set;
        }
    }

    //�ж������ڵ�����Ӧ�ļ����Ƿ�Ϊͬһ������
    bool isSameSet(Node* from,Node* to) {
        vector<Node*> fromset = setmap[from];
        vector<Node*> toset = setmap[to];
        return fromset == toset;
    }

    //�������ڵ�ŵ�ͬһ��������
    void unionNode(Node* from, Node* to) {
        vector<Node*> fromset = setmap[from];
        vector<Node*> toset = setmap[to];
        for (Node* curNode : toset) {
            fromset.push_back(curNode);
            setmap[curNode] = fromset;
        }
    }
};

//Kruskal �㷨
vector<edge*> krusjakMST(Graph graph) {
    vector<edge*> mst;
    mysets sets;
    // ��ͼ�Ľڵ�ͱ���Ϣ���Ƶ�mysets������
    for (const auto& nodePair : graph.nodes) {
        sets.nodes[nodePair.first] = nodePair.second;
    }
    sets.edges = graph.edges;
    // ��ʼ���ڵ㼯��
    sets.init();
    // ��ͼ�ı�ת��Ϊָ����ʽ������һ����ʱ�������Ա�����
    std::vector<edge*> edgePointers;
    for (auto& e : sets.edges) {
        edgePointers.push_back(&e);
    }
    // ���ձߵ�Ȩ�ضԱ߽�������
    sort(edgePointers.begin(), edgePointers.end());
    // ���������ıߣ�������ӵ���С��������
    for (edge* e : edgePointers) {
        if (!sets.isSameSet(&e->from, &e->to)) {
            mst.push_back(e);
            sets.unionNode(&e->from, &e->to);
        }
    }
    return mst;
}
//ͼ�Ŀ�����ȱ���
void BFS(Node* head) {
    if (head == nullptr) {
        return;
    }
    queue<Node*> q;
    unordered_map<Node*, int> hashset;
    q.push(head);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        cout << cur->value << endl;
        for (auto next : cur->nexts) {
            if (hashset.count(next) == 0) {
                hashset[next] = 1;
                q.push(next);
            }
        }
    }
}

//ͼ��������ȱ���
void DFS(Node* head) {
    if (head == nullptr) {
        return;
    }
    stack<Node*> st;
    unordered_map<Node*, int> hashset;
    st.push(head);
    hashset[head] = 1;
    while (!st.empty()) {
        Node* cur = st.top();
        st.pop();
        for (auto next : cur->nexts) {
            if (hashset.count(next) == 0) {
                st.push(cur);
                st.push(next);
                hashset[next] = 1;
                cout << next->value << endl;
                break;
            }
        }
    }
}

//��������
vector<Node*> sortedTopology(Graph graph) {
    //keyΪĳһ��Node
    //valueΪʣ������
    unordered_map<Node*, int> hashset;
    //���Ϊ0�ĵ���ܽ������
    queue<Node*> q;
    //����ͼ�еĵ㼯�����е�͵����ȷ����ϣ����
    for (const auto& pair : graph.nodes) {
        hashset[pair.second] = pair.second->in;
        //�����Ϊ0�Ľڵ�������
        if (pair.second->in == 0) {
            q.push(pair.second);
        }
    }
    vector<Node*> result;
    while (!q.empty()) {
        //��¼���׽ڵ�
        Node* cur = q.front();
        result.push_back(cur);
        for (Node* next : cur->nexts) {
            //�����Ϊ0�Ľڵ�ĳ�������Ӧ�Ľڵ����ȼ�һ
            hashset[next]--;
            //���Ϊ��Ľڵ����
            if (hashset[next] == 0) {
                q.push(next);
            }
        }
    }
    return result;
}




//ǰ׺����Trie����һ���������ݽṹ����Ҫ���ڴ洢�ַ������ϣ��Ա���ټ����Ͳ��Ҿ��й�ͬǰ׺���ַ�                                                                                                   
//ǰ׺���Ľڵ� 
class TrieNode {
public:
    int pass;  //��ǰ׺��ʱ���ڵ㵽����Ĵ���
    int end;   //�ڵ��Ƿ����ַ����Ľ�β�ڵ㣬�Ƕ��ٸ��ַ����Ľ�β�ڵ�
    vector<TrieNode*> nexts;
    //map<char,TrieNode> nexts;���ַ�������ǳ���ʱ����ʹ�ù�ϣ�������·
    TrieNode() :pass(0), end(0), nexts(26,nullptr) {};
};

//ǰ׺��
class Trie {
private:
    TrieNode* head;
public:
    //���뵥��word
    void insert(string& word) {
        if (word.empty()) {
            return;
        }
        TrieNode* node = head;
        node->pass++;
        int index = 0;
        for (int i = 0; i < word.size(); i++) {
            index = word[i] - 'a';
            if (node->nexts[index] == nullptr) {
                node->nexts[index] = new TrieNode();
            }
            node = node->nexts[index];
            node->pass++;
        }
        node->end++;
    }
    //����word������ʲ��������
    int search(string word) {
        if (word.empty()) {
            return 0;
        }
        TrieNode* node = head;
        int index = 0;
        for (int i = 0; i < word.size(); i++) {
            index = word[i] - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }
        return node->end;
    }
    //�����м�����ַ����У��ж��ٵ�����preΪǰ׺
    int prefixnumber(string pre) {
        if (pre.empty()) {
            return 0;
        }
        TrieNode* node = head;
        int index = 0;
        for (int i = 0; i < pre.size(); i++) {
            index = pre[i] - 'a';
            if (node->nexts[index] == nullptr) {
                return 0;
            }
            node = node->nexts[index];
        }
        return node->pass;
    }
    void deleteword(string word) {
        if (search(word) != 0) {
            TrieNode* node = head;
            int index = 0;
            node->pass--;
            for (int i = 0; i < word.size(); i++) {
                index = word[i] - 'a';
                if (--node->nexts[index]->pass == 0) {
                    delete node->nexts[index];
                    node->nexts[index] = nullptr;
                    return;
                }
                node = node->nexts[index];
            }
            node->end--;
        }
    }
    void deleteNode(TrieNode* node) {
        if (node != nullptr) {
            for (int i = 0; i < 26; i++) {
                deleteNode(node->nexts[i]);
            }
            delete node;
        }
    }
    ~Trie() {
        deleteNode(head);
    }
}; 
int main() {
    return 0;
}