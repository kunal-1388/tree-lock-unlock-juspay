#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class Node
{
public:
    string s;
    bool isLocked = false;
    int id = -1;
    Node *parent = NULL;
    int anc_locked = 0;
    int dec_locked = 0;
    vector<Node *> children{};
    set<Node *> locked_desc_list;
};

int check_anc_locked_count(Node *node)
{

    int count = 0;
    while (node != NULL)
    {
        if (node->isLocked)
        {
            count++;
        }
        node = node->parent;
    }
    return count;
}

void inform_ancestors_to_add(Node *node, int val, Node *desc_locked)
{

    while (node != NULL)
    {
        node->dec_locked += 1;
        node->locked_desc_list.insert(desc_locked);
        node = node->parent;
    }
}

bool lock(Node *node, int id)
{

    if (node->isLocked)
    {
        return false;
    }

    if (node->dec_locked > 0)
    {
        return false;
    }

    if (check_anc_locked_count(node->parent) > 0)
    {
        return false;
    }

    node->isLocked = true;
    node->id = id;

    inform_ancestors_to_add(node->parent, 1, node);
    return true;
}

void inform_ancestors_to_remove(Node *node, int val, Node *desc_unlocked)
{

    while (node != NULL)
    {
        node->dec_locked += val;
        node->locked_desc_list.erase(desc_unlocked);
        node = node->parent;
    }
}

bool unlock(Node *node, int id)
{
    if (node->isLocked == false || node->id != id)
    {
        return false;
    }

    node->isLocked = false;
    node->id = -1;
    inform_ancestors_to_remove(node->parent, -1, node);
    return true;
}

bool upgrade(Node *node, int id)
{

    if (node->isLocked)
    {
        return false;
    }

    if (node->dec_locked == 0)
    {
        return false;
    }

    if (check_anc_locked_count(node) == 0)
    {
        return false;
    }

    node->isLocked = true;
    node->id = id;

    for (auto it = node->locked_desc_list.begin(); it != node->locked_desc_list.end(); it++)
    {
        unlock(*it, id);
    }
    return true;
}

int main()
{
    int n = 7; // number of nodes
    cin >> n;
    int k = 2; // number of children per node
    cin >> k;
    int q = 3; // number of queries
    cin >> q;

    map<string, Node *> mp;
    vector<string> v{"World", "Asia", "Africa", "China", "India", "SouthAfrica", "Egypt"};

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    queue<Node *> qu;
    Node *root = new Node();
    root->s = v[0];
    mp[v[0]] = root;
    int index = 1;
    qu.push(root);

    while (!qu.empty() && index < n)
    {
        int size = qu.size();
        while (size--)
        {
            Node *rem = qu.front();
            qu.pop();
            for (int i = 1; i <= k && index < n; i++)
            {
                Node *newNode = new Node();
                newNode->parent = rem;
                mp[v[index]] = newNode;
                newNode->s = v[index];
                (rem->children).push_back(newNode);
                qu.push(newNode);
                index++;
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        int val, id;
        string s;
        cin >> val >> s >> id;
        bool ans = false;
        if (val == 1)
        {
            cout << "if" << endl;
            ans = lock(mp[s], id);
        }
        else if (val == 2)
        {
            cout << "else if" << endl;
            ans = unlock(mp[s], id);
        }
        else if (val == 3)
        {
            cout << "else" << endl;
            ans = upgrade(mp[s], id);
        }
        cout << ans << endl;
    }
}
