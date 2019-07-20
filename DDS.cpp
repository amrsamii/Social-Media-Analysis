#include <iostream>
#include "vector"
#include "string"
#include "algorithm"
#include "queue"
#include "numeric"
#include  "iomanip"
using namespace std;


int n;
vector<vector<int>> adjMax;

vector<vector<int>> previous(n);
vector<int> dist(n,1e8);
int dijkstra(vector<vector<int>> adjMax,int src,int dest=-1){


    vector<bool> vis(n,0);
    dist=vector<int>(n,1e8);
    previous=vector<vector<int>>(n);
    dist[src] = 0;
    while (true){
        int val=1e8, idx=-1;
        //smallest node
        for(int i=0;i<n;i++){
            if(!vis[i] && dist[i]<val)
            {
                val= dist[i];
                idx=i;
            }
        }
        if(idx==-1)
            break;
        vis[idx] = true;


        for(int i=0;i<n;i++){
            if(dist[i]>= (val=dist[idx]+adjMax[idx][i]))
            {
                if(dist[i] ==dist[idx]+adjMax[idx][i]||previous[i].empty())
                    previous[i].push_back(idx);
                else {

                    previous[i][previous[i].size() - 1] = idx;
                }

                //Relax
                dist[i]=val;


            }
        }
    }

    return dest==-1?0:dist[dest];
}
int isNotVisited(int x, vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}
void printpath(vector<int>& path)
{
    reverse(path.begin(),path.end());
    int size = path.size();
    for (int i = 0; i < size; i++)
        cout << path[i] << " ";
    cout << endl;
}
vector<vector<int>> getPaths(vector<vector<int>> previous,int src,int dest){

    vector<vector<int>> paths;
    queue<vector<int >> q;
    vector<int> path;
    path.push_back(src);
    q.push(path);
    while (!q.empty()){
        path = q.front();
        q.pop();
        int last = path[path.size()-1];

        if(last==dest) {
            reverse(path.begin(),path.end());
            paths.push_back(path);
        }

        for(int i=0;i<previous[last].size();i++){

            if(isNotVisited(previous[last][i],path)){
                vector<int> newPath(path);
                newPath.push_back(previous[last][i]);
                q.push(newPath);
            }
        }
    }


    return paths;
}

int Degree(int node){
    int degree=0;
    for(int i=0;i<n;i++){
        if(adjMax[node][i]<1e9)
            degree++;
    }
    return degree;
}

double Closeness(int node){
    double sum=0;
    dijkstra(adjMax,node);
    sum = accumulate(dist.begin(),dist.end(),0);

    return double((n-1))/sum;
}

double Betweenness(int node){
    double sum =0;
    double numPaths=0;
    for(int i=0;i<n-1;i++){
        if(i==node)
            continue;


        dijkstra(adjMax,i);
        for(int j=i+1;j<n;j++){
            if(j==node||j==i)
                continue;
            numPaths=0;
         vector<vector<int>> paths = getPaths(previous,j,i);
         for(auto k : paths){
             if(find(k.begin(),k.end(),node)!=k.end())
                 numPaths++;
         }
         sum+=numPaths/paths.size();

        }
    }
    return sum;
}
int main() {

    int a,b,c;
    int m;
    cin>>n>>m;
    adjMax = vector<vector<int>>(n,vector<int>(n,1e9));

    while (m--){
       cin>>a>>b>>c;
       adjMax[a][b]=c;
       adjMax[b][a]=c;

   }
   for(int i=0;i<n;i++){
       cout<<fixed;
       cout<<setprecision(9);
       cout<<Betweenness(i)<<'\n';
       system("python degree.py");
   }

    return 0;
}

