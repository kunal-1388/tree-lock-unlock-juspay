#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    bool isLocked=false;
    int id=-1;
    Node * parent=NULL;
    int anc_locked=0;
    int dec_locked=0;
    vector<Node *>children{};
};

int check_anc_locked_count(Node * node){

    int count=0;
    while(node!=NULL){
        if(node->isLocked){
            count++;
        }
        node=node->parent;
    }
    return count;
}

void inform_ancestors(Node * node,int val){

    while(node!=NULL){
        node->dec_locked+=1;
        node=node->parent;
    }
}

bool lock(Node * node,int id){
   
   if(node->isLocked){
        return false;
   }

   if(node->dec_locked>0){
        return false;
   } 

   if(check_anc_locked_count(node->parent)>0){
        return false;
   }

    node->isLocked=true;
    node->id=id;

    inform_ancestors(node->parent,1);
}




bool unlock(Node * node,int id){
    if(node->isLocked==false || node->id!=id){
        return false;
    }

    node->isLocked=false;
    node->id=-1;
    inform_ancestors(node->parent,-1);
}



bool upgrade(Node * node,int id){
    
}














int main(){
    int n; // number of nodes
    cin>>n;
    int k; // number of children per node
    cin>>k;
    int q; // number of queries
    cin>>q;

    map<string,Node *>mp;
    vector<string>v(n);

    for(int i=0;i<n;i++){
        cin>>v[i];
    }

    queue<Node*>qu;
    Node *root=new Node();
    mp[v[0]]=root;
    int index=1;
    qu.push(root);

    while(!qu.empty() && index<n){
        int size=qu.size();
        while(size--){
            Node* rem=qu.front();
            qu.pop();
            for(int i=1;i<=k && index<n;i++){
                Node *newNode=new Node();
                newNode->parent=rem;
                mp[v[i]]=newNode;
                (rem->children).push_back(newNode);
                qu.push(newNode);
                index++;
            }
        }
    }

    
    for(int i=0;i<q;i++){
        int val,id;
        string s;
        cin>>val>>s>>id;
        bool ans=false;
        if(val==1){
            ans=lock(mp[s],id);
        }
        else if(val==2){
            ans=unlock(mp[s],id);
        }
        else if(ans==3){
            ans=upgrade(mp[s],id);
        }
        cout<<ans<<endl;
    }
    


}

