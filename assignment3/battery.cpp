#include <bits/stdc++.h>

#define _len(x1, y1, x2, y2) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))

using namespace std;

class _Node;
class Node;
class Graph;
class cmp;

class _Node{
friend class cmp;
friend Graph;
public:
    _Node(int n=0, float w=0):name(n), weight(w){};
private:
    int name;
    float weight;
};

class Node{
friend class Graph;
friend class cmp;
public:
    Node(int p=0, int q=0):x(p), y(q){}
private:
    vector<_Node> Child;
    int x, y;
};


class cmp{
public:
    inline bool operator()(_Node x, _Node y){
        return x.weight<y.weight;
    }
};

class Graph{
public:
    Graph(int z):sz(1), minlen(1), maxlen(z*1.414){
        float buf = _len(0,0,z,z);
        lst[0].Child.push_back(_Node(1001,buf));
        lst[1001].Child.push_back(_Node(0,buf));
        lst[0].x = lst[0].y = 0;
        lst[1001].x = lst[1001].y = z;
    }
    void Insert(int p, int q);
    int minBattery(){
        for(int i=0; i<=sz; ++i)
            sort(lst[i].Child.begin(), lst[i].Child.end(), cmp());
        return _minBattery(0, lst[1001].x*1.414);
    };
private:
    Node lst[1002];
    int sz;
    float minlen, maxlen;
    int _minBattery(float _min, float _max);
    bool BFS(float len);
};

void Graph::Insert(int p, int q){
    float buf;
    for(int i=0; i<sz; ++i){
        buf = _len(p,q,lst[i].x,lst[i].y);
        lst[i].Child.push_back(_Node(sz, buf));
        lst[sz].Child.push_back(_Node(i,buf));
    }
    buf = _len(p,q,lst[1001].x, lst[1001].y);
    lst[1001].Child.push_back(_Node(sz, buf));
    lst[sz].Child.push_back(_Node(1001, buf));
    lst[sz].x = p; lst[sz].y = q;
    ++sz;
}

int Graph::_minBattery(float _min, float _max){
    float buf;
    while(1){
        if((int)_min == (int)_max)
            return (int)_min + (_min-(int)_min>0);
        buf = (_min+_max)/2;
        if(BFS(buf))
            _max = buf;
        else
            _min = buf;
    }
}

bool Graph::BFS(float len){
    int explored[1002]={0,}, it=0;
    queue<int> bag;
    _Node buf;
    bag.push(it);
    while(!bag.empty()){
        it = bag.front();
        bag.pop();
        for(int i=0; i<sz; ++i){
            buf = lst[it].Child[i];
            if(buf.weight<=len){
                if( buf.name == 1001)
                    return true;
                else if(!explored[buf.name]){
                    bag.push(buf.name);
                    explored[buf.name] = 1;
                }
            }
            else
                break;
        }
    }
    return false;
}

int main(void){
    ifstream input("battery.inp");
    ofstream output("battery.out");
    Graph *myG;
    int n,z,x,y;
    input>>n>>z;
    myG = new Graph(z);
    for(int i=0; i<n; ++i){
        input>>x>>y;
        myG->Insert(x,y);
    }
    output<<myG->minBattery()<<'\n';
    return 0;
}
