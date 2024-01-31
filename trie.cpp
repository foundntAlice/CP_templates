//https://codeforces.com/contest/706/submission/141876882
//above is my submission for the exact same problem on codeforces years ago, lol
#include<bits/stdc++.h>

//https://www.acmicpc.net/problem/16903

using namespace std;
#define nl '\n'
#define fi first
#define se second
typedef long long ll;
int res = 0;

struct trieNode{
    struct trieNode *childs[2];
    int passed[2];
    int ans[2];
};
trieNode *getNode(){
    trieNode *p = new trieNode();
    p->childs[0] = p->childs[1] = NULL;
    p->passed[0] = p->passed[1] = 0;
    p->ans[0] = p->ans[1] = 0;
    return p;
}
void add(trieNode *root, int val){
    trieNode *cpy = root;
    for(long long i = 34; i >= 0; i--){
        if(i == 0){
            if(val == 0) cpy->ans[0]++;
            else cpy->ans[1]++;
            break;
        }
        if(val >= pow(2, i)){
            val -= pow(2, i);
            if(!cpy->childs[1]) cpy->childs[1] = getNode();
            cpy->passed[1]++;
            cpy = cpy->childs[1];
        }
        else{
            if(!cpy->childs[0]) cpy->childs[0] = getNode();
            cpy->passed[0]++;
            cpy = cpy->childs[0];
        }
    }
}
void sub(trieNode *root, int val){
    trieNode *cpy = root;
    for(long long i = 34; i >= 0; i--){
        if(i == 0){
            if(val == 0) cpy->ans[0]--;
            else cpy->ans[1]--;
            break;
        }
        if(val >= pow(2, i)){
            val -= pow(2, i);
            cpy->passed[1]--;
            cpy = cpy->childs[1];
        }
        else{
            cpy->passed[0]--;
            cpy = cpy->childs[0];
        }
    }
}
int get(trieNode *root, int val){
    trieNode *cpy = root;
    for(long long i = 34; i >= 0; i--){
        if(i == 0){
            if((val > 0 && cpy->ans[0] > 0) || (val == 0 && cpy->ans[1] > 0)) return res + 1;
            else return res;
        }
        if(cpy->passed[0] == 0 && cpy-> passed[1] == 0) return 0;
        if(val >= pow(2, i)){
            val -= pow(2, i);
            if(cpy->passed[0] > 0){
                res += pow(2, i);
                cpy = cpy->childs[0];
            }
            else cpy = cpy->childs[1];
        }
        else{
            if(cpy->passed[1] > 0){
                res += pow(2, i);
                cpy = cpy->childs[1];
            }
            else cpy = cpy->childs[0];
        }
    }
    return 0;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int q;
    cin>>q;
    trieNode * root = getNode();
    while(q--){
        char type;
        int val;
        cin>>type>>val;
        if(type == '1') add(root, val);
        else if(type == '2') sub(root, val);
        else{
            res = 0;
            cout<<max(val, get(root, val))<<nl;
        }
    }
    
}
