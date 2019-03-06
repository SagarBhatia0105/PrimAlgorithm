#include<iostream>
#include<fstream>

#define INF 10000
using namespace std;

void PrintKeys(int *key, int *parent, int vertices){
  for(int i=0; i<vertices; i++){
    cout<<"for vertex "<<i<<", the key is: "<<key[i]<<" and the parent is: ";
    cout<<parent[i]<<endl;
  }
}

int getShortestKey(int *key, int vertices, bool *pop){
  int min = INF;
  int p;
  for(int i = 0; i<vertices; i++){
    if(key[i]<min & pop[i] == false){
      min = key[i];
      p = i;
    }
  }

  return p;
}

bool *setPOP(bool *pop, int i){
  pop[i] = true;
  return pop;
}

//-1 for NIL
void Prim(int **adj, int r, int vertices){

  int *parent = new int[vertices];
  int *key = new int[vertices];
  bool *pop = new bool[vertices];
  int counter = 0;
  int check = 1, check2 = 1, p;
  int min = INF+100;

  for(int i=0; i<vertices; i++){
    parent[i] = -1;
    key[i] = INF;
    pop[i] = false;
  }

  key[r] = 0;
  while(counter<vertices){
    p = getShortestKey(key, vertices, pop);
    //cout<<"key selected is "<<p<<endl;
    pop = setPOP(pop, p);

    for(int i=0; i<vertices; i++){
      if(adj[p][i] != 0 && parent[p] != i){
        //check whether the adjacent key of popped vertex is in the queue
        if(pop[i] != true && adj[p][i]<key[i]){
          parent[i] = p;
          key[i] = adj[p][i];
        }
      }
    }
    counter++;
  }
  PrintKeys(key, parent, vertices);
}

int main(int argc, char const *argv[]) {

  //number of data sets
  int n, **adj;
  //number of edges and vertices
  int vertices, edges;
  fstream input(argv[1]);
  int u, v, w;

  if(!input){
    cout<<"Unable to read input file"<<endl;
  }

  input>>n;

  for(int i=0; i<n; i++){

    input>>vertices>>edges;

    adj = new int*[vertices];

    for(int j=0; j<vertices; j++){
      adj[j] = new int[vertices];
    }

    for(int j=0; j<vertices; j++){
      for(int k=0; k<vertices; k++){
        adj[j][k] = 0;
      }
    }

    cout<<vertices<<" "<<edges<<endl;
    for(int j=0; j<edges; j++){
      input>>u>>v>>w;
      adj[u][v] = w;
      adj[v][u] = w;
    }

    Prim(adj, 0, vertices);

  }
    input.close();
    return 0;
}
