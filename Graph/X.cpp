#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
#define ll long long 
#define bits __builtin_clz
#define tp __builtin_popcount
#define TT template<class C>
using namespace __gnu_pbds; 
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, 
             tree_order_statistics_node_update> O; 
	     
struct compare { 
    bool operator()(const pair<ll, ll>& value,  
                                const ll& key) 
    { 
        return (value.first < key); 
    } 
    bool operator()(const ll& key,  
                    const pair<ll, ll>& value) 
    { 
        return (key < value.first); 
    } 
}; 
TT
class G{
    public:
    unordered_map<C,vector<C>> adj;
    unordered_map<C,vector<pair<C,int>>> wgh;
    int V;// of no use for debugging lol
    void add_w(int a,int b,int w){
        wgh[a].push_back(make_pair(b,w));
        wgh[b].push_back(make_pair(a,w));
    }
    void add_edge(C a, C b);
    void bfs(C s);
    void dfs1(C v,unordered_map<C,bool>&visited);
    void dfs(C s,unordered_map<C,bool>&vis);
    bool detect_cycle_utils(C v,unordered_map<C,bool>&visited,C parent);
    bool iscycle(C a);
    bool mother(C a);
   
};
TT
// change directive propertyu
void G<C>::add_edge(C a,C b){
    adj[a].push_back(b);
    
    
    
}
TT
void G<C>::bfs(C s){
    unordered_map<C,bool> visited(false);
    queue<C> Q;
    Q.push(s);
    visited[s]=true;
    while(!Q.empty()){
        C v=Q.front();
        cout<<v<<"\n";
        Q.pop();
        for(auto i=adj[v].begin();i!=adj[v].end();++i){
            if(!visited[*i]){
                Q.push(*i);
                visited[*i]=true;
            }
        }
    }
}
TT
void G<C>::dfs1(C v,unordered_map<C,bool>&visited){
    
    visited[v]=true;
    cout<<v<<" ";
    cout<<"\n";
    for(auto i=adj[v].begin();i!=adj[v].end();++i){
        if(!visited[*i])
            dfs1(*i,visited);
    }
}
TT
void G<C>::dfs(C s,unordered_map<C,bool>& vis){
    dfs1(s,vis);
}

TT
bool G<C>::detect_cycle_utils(C v,unordered_map<C,bool>& visited,C p){
    visited[v]=true;
    for(auto i=adj[v].begin();i!=adj[v].end();++i){
        if(!visited[*i]){
            if(detect_cycle_utils(*i,visited,v))
                return true;
        }
        else if(*i!=p)
            return true;
    }
    return false;
}

TT
bool G<C>::iscycle(C a){
    unordered_map<C,bool>vis(false);
    vector<C> A;
    for(auto x:adj){
        A.push_back(x.first);
    }
    for(C x:A){
        if(!vis[x]){
            if(detect_cycle_utils(x,vis,-1))
                return true;
        }
    }
    return false;
}


TT
int  nodes(G<C> g1,C s){
   unordered_map<C,bool> visited(false);
    queue<C> Q;
    Q.push(s);
    visited[s]=true;
    int c=0;
    while(!Q.empty()){
        C v=Q.front();
        if(v==(C)'n'){
            ++c;
            Q.pop();
            continue;
        }
        
        
        Q.pop();
        for(auto i=g1.adj[v].begin();i!=g1.adj[v].end();++i){
            if(!visited[*i]){
                Q.push(*i);
                visited[*i]=true;
            }
        }
        Q.push((C)'n');
    }
    return c;
}
TT 
bool G<C>::mother(C a){
    unordered_map<C,bool>vis(false);
    dfs1(a,vis);
    int c=1;
    vector<C> A;
    for(auto x:adj){
        A.push_back(x.first);
    }
    for(C x:A){
        if(!vis[x]){
           return false;
        }
    }
    return true;
    
}
// flood fill
template<class T>
void flood_fill(vector<vector<T>>& A,T n,T chg){
        int N=A.size();
        int M=A[0].size();
        unordered_map<int ,bool> vis1;
        unordered_map<int,bool> vis2;
        int pos1;
        int pos2;
        for(int i=0;i<N;i++){
            int flag=0;
            for(int j=0;j<M;j++){
                //debug :: cout<<A[i][j]<<"\n";
                if(A[i][j]==n){
                    pos1=i;
                    pos2=j;
                    flag=1;
                    break;
                }
            }
            if(flag)
                break;
        }
        
        queue<pair<int,int>> Q;
        pair<int,int> u;
        u.first=pos1;
        u.second=pos2;
        Q.push(u);
        vis1[pos1]=true;
        vis2[pos2]=true;
        while(!Q.empty()){
            auto y=Q.front();
            A[y.first][y.second]=chg;
            Q.pop();
            int a[8]={y.first-1,y.first-1,y.first-1,y.first,y.first,y.first+1,y.first+1,y.first+1};
            int b[8]={y.second-1,y.second,y.second+1,y.second-1,y.second+1,y.second-1,y.second,y.second+1};
            for(int i=0;i<8;i++){
                if((a[i]>=0 && a[i]<N) && (b[i]>=0 && b[i]<M)){
                    if(A[a[i]][b[i]]==n){
                        pair<int,int> u;
                        u.first=a[i];
                        u.second=b[i];
                        Q.push(u);
                        vis1[a[i]]=true;
                        vis2[b[i]]=true;
                    
                }
            }
        }
            
    } 


}
TT
ll connected_components(G<C> g){
    vector<C> A;
    for(auto x:g.adj)
        A.emplace_back(x.first);
    ll  c=0;
    unordered_map<C,bool> M;
    for(C a:A){
        if(!M[a]){
            g.dfs1(a,M);
            ++c;
        }
    }
    return c;
}



TT
int path(G<C> g,C s,C d){
    unordered_map<C,bool> vis(false);
    int l=0;
    queue<C> Q;
    Q.push(s);
    vis[s]=true;
    map<int,vector<C>> K;
    K[0].push_back(s);
    Q.push(INT_MIN);
    while(!Q.empty()){
        C v=Q.front();
        if(v==d)
            return l;
        if(v==INT_MIN){
            ++l;
            Q.pop();
            continue;
        }
        Q.pop();
        for(auto i=g.adj[v].begin();i!=g.adj[v].end();++i){
            if(!vis[*i]){
                Q.push(*i);
                vis[*i]=true;
            }
        }
        Q.push(INT_MIN);
        
        
        
    }
    return -1;
    
    
}

TT
int shortest_path(vector<vector<C>>A,C s,C d){
    int N=A.size();
    int M=A.at(0).size();
    unordered_map<C,bool> vis1(false);
    unordered_map<C,bool>vis2(false);
    int pos1;
    int pos2;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(A[i][j]==s){
            pos1=i;
            pos2=j;
            break;
            }
        }
    }
    vis1[pos1]=true;
    vis2[pos2]=true;
    queue<pair<int,int>> Q;
    
    Q.push(make_pair(pos1,pos2));
    Q.push(make_pair(INT_MIN,INT_MIN));
    int l=0;
    
    while(!Q.empty()){
        auto y=Q.front();
        if(y.first==INT_MIN){
            ++l;
            Q.pop();
            continue;
        }
        if(A[y.first][y.second]==d){
            return l;
        }
        int a[8]={y.first-1,y.first-1,y.first-1,y.first,y.first,y.first+1,y.first+1,y.first+1};
        int b[8]={y.second-1,y.second,y.second+1,y.second-1,y.second+1,y.second-1,y.second,y.second+1};
        Q.pop();
        
        for(int i=0;i<8;++i){
            if((a[i]>=0 && a[i]<N)&&(b[i]>=0 && b[i]<M)){
                if(!vis1[pos1] || !vis2[pos2]){
                    Q.push(make_pair(a[i],b[i]));
                    vis1[a[i]]=true;
                    vis2[b[i]]=true;
                }
            }
        }
        Q.push(make_pair(INT_MIN,INT_MIN));
        
    }
    
    
    return l;
    
    
}
TT 
ll No_componenets(G<C>g,unordered_map<C,vector<C>> adj){
        vector<C> A;
        ll cnt=0;
        for(auto x:adj)
            A.emplace_back(x.first);
        unordered_map<C,bool> M(false);
        for(auto x:A){
            if(!M[x]){
                g.dfs1(x,M);
                ++cnt;
            }
        }
        return cnt;
}
bool avg(vector<ll> A,ll h){
    for(int i=0;i<A.size();i++){
	ll temp=A[i]^h;
	if(find(A.begin(),A.end(),temp)==A.end())
	    return false;
    }
    return true;
}

vector<ll> prime_facs(ll n){
      vector<ll> P;
      for(int i=2;i*i<=n;i++){
	  if(n%i==0){
	    while(n%i==0){
		if(find(P.begin(),P.end(),i)==P.end())
		    P.emplace_back(i);
		n/=i;
	    }
	    
	}
      }
      if(n>1)
	  P.push_back(n);
      return P;
}
ll findSubarraySum(vector<ll> arr, ll n, ll sum) 
{ 
    
    unordered_map<ll, ll> prevSum; 
  
    ll res = 0; 
  
    
    ll currsum = 0; 
  
    for (int i = 0; i < n; i++) { 
  
        
        currsum += arr[i]; 
  
        
        if (currsum == sum) 
            res++; 
  
        
        if (prevSum.find(currsum - sum) != prevSum.end()) 
            res += (prevSum[currsum - sum]); 
  
       
        prevSum[currsum]++; 
    } 
  
    return res; 
} 

int main(){
   int t;
   cin>>t;
   while(t--){
      
      
    
      
    }

      
 
	
}  
    
       
       
       
       
       
       
    
    
        
       

