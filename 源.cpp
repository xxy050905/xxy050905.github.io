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

//二叉树的先序遍历（递归）
void perorder(TreeNode* head) {
    if (head == nullptr) {
        return;
    }
    cout << head->val << endl;
    perorder(head->left);
    perorder(head->right);
}

//二叉树的中序遍历（递归）
void midorder(TreeNode* head) {
    if (head == nullptr) {
        return;
    }
    midorder(head->left);
    cout << head->val << endl;
    midorder(head->right);
}

//二叉树的后序遍历（递归）
void posorder(TreeNode* head) {
    if (head == nullptr) {
        return;
    }
    posorder(head->left);
    posorder(head->right);
    cout << head->val << endl;
}

//二叉树的先序遍历（深度优先）
void preorderunrecur(TreeNode* head) {
    if (head != nullptr) {
        stack<TreeNode*> st;
        st.push(head);
        while (!st.empty()) {
            //弹出栈顶节点
            head = st.top();
            st.pop();
            cout << head->val << endl;
            //将栈顶节点的左右节点放入栈中
            if (head->right != nullptr) {
                st.push(head->right);
            }
            if (head->left != nullptr) {
                st.push(head->left);
            }
        }
    }
}

//二叉树的后序遍历
void posorderunrecur(TreeNode* head) {
    if (head != nullptr) {
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        s1.push(head);
        //s1进栈顺序为头右左
        //s2进栈顺序为左右头
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

//二叉树的中序遍历
void midordertree(TreeNode* head) {
    if (head != nullptr) {
        stack<TreeNode*> st;
        while (!st.empty() || head != nullptr) {
            //将所有左树放入栈中
            if (head != nullptr) {
                st.push(head);
                head = head->left;
            }
            else {
                head = st.top();
                st.pop();
                cout << head->val << endl;//若最终结果为升序则为搜索二叉树
                head = head->right;
            }
        }
    }
}

//求二叉树的最大宽度
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

//二叉树的层序遍历
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

//判断一棵树是否为完全二叉树
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
            //当叶子节点有左右子树时，不为完全二叉树
            ||
            (l == nullptr || r == nullptr))
            //当某节点有右子树没有左子树不是完全二叉树
        {
            return false;
        }
        if (l != nullptr) {
            q.push(l);
        }
        if (r != nullptr) {
            q.push(r);
        }
        //当第一次出现左右子树不满时，后面的节点都为叶子节点
        if (l == nullptr || r == nullptr) {
            leaf = true;
        }
    }
    return true;
}


class edge;
//图的点集
class Node {
public:
    int value;
    int in;
    int out;
    vector<Node*> nexts;
    vector<edge> edges;
    Node(int val) : value(val), in(0), out(0) {}
};
//图的边集
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
 
//图
class Graph {
public:
    unordered_map<int, Node*> nodes;  
    vector<edge> edges;
};

class mysets :public Graph {
public:
    //记录每个节点所在的集合
    unordered_map<Node*, vector<Node*>> setmap;

    //初始化myset，一开始每一个节点所对应的集合只有自己
    void init(){
        for (const auto& pair : nodes) {
            vector<Node*> set;
            set.push_back(pair.second);
            setmap[pair.second] = set;
        }
    }

    //判断两个节点所对应的集合是否为同一个集合
    bool isSameSet(Node* from,Node* to) {
        vector<Node*> fromset = setmap[from];
        vector<Node*> toset = setmap[to];
        return fromset == toset;
    }

    //将两个节点放到同一个集合中
    void unionNode(Node* from, Node* to) {
        vector<Node*> fromset = setmap[from];
        vector<Node*> toset = setmap[to];
        for (Node* curNode : toset) {
            fromset.push_back(curNode);
            setmap[curNode] = fromset;
        }
    }
};

//Kruskal 算法
vector<edge*> krusjakMST(Graph graph) {
    vector<edge*> mst;
    mysets sets;
    // 将图的节点和边信息复制到mysets对象中
    for (const auto& nodePair : graph.nodes) {
        sets.nodes[nodePair.first] = nodePair.second;
    }
    sets.edges = graph.edges;
    // 初始化节点集合
    sets.init();
    // 将图的边转换为指针形式并存入一个临时向量，以便排序
    std::vector<edge*> edgePointers;
    for (auto& e : sets.edges) {
        edgePointers.push_back(&e);
    }
    // 按照边的权重对边进行排序
    sort(edgePointers.begin(), edgePointers.end());
    // 遍历排序后的边，尝试添加到最小生成树中
    for (edge* e : edgePointers) {
        if (!sets.isSameSet(&e->from, &e->to)) {
            mst.push_back(e);
            sets.unionNode(&e->from, &e->to);
        }
    }
    return mst;
}
//图的宽度优先遍历
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

//图的深度优先遍历
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

//拓扑排序
vector<Node*> sortedTopology(Graph graph) {
    //key为某一个Node
    //value为剩余的入度
    unordered_map<Node*, int> hashset;
    //入度为0的点才能进入队列
    queue<Node*> q;
    //遍历图中的点集将所有点和点的入度放入哈希表中
    for (const auto& pair : graph.nodes) {
        hashset[pair.second] = pair.second->in;
        //将入度为0的节点放入队中
        if (pair.second->in == 0) {
            q.push(pair.second);
        }
    }
    vector<Node*> result;
    while (!q.empty()) {
        //记录队首节点
        Node* cur = q.front();
        result.push_back(cur);
        for (Node* next : cur->nexts) {
            //将入度为0的节点的出度所对应的节点的入度减一
            hashset[next]--;
            //入度为零的节点入队
            if (hashset[next] == 0) {
                q.push(next);
            }
        }
    }
    return result;
}




//前缀树（Trie）是一种树形数据结构，主要用于存储字符串集合，以便快速检索和查找具有共同前缀的字符                                                                                                   
//前缀树的节点 
class TrieNode {
public:
    int pass;  //加前缀树时。节点到达过的次数
    int end;   //节点是否是字符串的结尾节点，是多少个字符串的结尾节点
    vector<TrieNode*> nexts;
    //map<char,TrieNode> nexts;在字符的种类非常多时可以使用哈希表来表达路
    TrieNode() :pass(0), end(0), nexts(26,nullptr) {};
};

//前缀树
class Trie {
private:
    TrieNode* head;
public:
    //插入单词word
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
    //查找word这个单词插入过几次
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
    //在所有加入的字符串中，有多少单词以pre为前缀
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