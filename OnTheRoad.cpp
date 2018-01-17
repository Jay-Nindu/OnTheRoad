#include <bits/stdc++.h>
#define MAX_N INT_MAX/2
using namespace std;

int main(){
  int nodeAmount, edgeAmount, stallAmount, start, end;
  cin >> nodeAmount >> edgeAmount >> stallAmount >> start >> end;

  vector < vector< pair <int, int> > >adjacencyList;
  vector < pair <int, int> > emptyVector;
  for(int i = 0; i < nodeAmount; i++ ){
    adjacencyList.push_back(emptyVector);
  }

  int currentNode, otherNode, currentWeight;
  for(int i = 0; i < edgeAmount; i++){
    cin >> currentNode >> otherNode >> currentWeight;
    adjacencyList[currentNode].push_back(make_pair(currentWeight, otherNode));
    adjacencyList[otherNode].push_back(make_pair(currentWeight, currentNode));
  }

  vector<int> stalls(stallAmount);
  for(int i = 0; i < stallAmount; i++){
    cin >> currentNode;
    stalls[i] = currentNode;
  }

  vector <int> dist(nodeAmount, MAX_N);
  priority_queue <pair<int, int> > q;
  q.push(make_pair(0, start));
  int DistS;
  while(!q.empty()){
    currentNode = q.top().second;
    DistS = -1*(q.top().first);
    q.pop();
    if(dist[currentNode] > DistS){
      dist[currentNode] = DistS;
      for(pair<int, int> i : adjacencyList[currentNode]){
        if(dist[i.second] > i.first + DistS){
          q.push(make_pair( -1*(i.first + DistS), i.second));
        }
      }
     }
  }

  vector <int> newDist(nodeAmount, MAX_N);
  q.push(make_pair(0, end));
  while(!q.empty()){
    currentNode = q.top().second;
    DistS = -1*(q.top().first);
    q.pop();
    if(newDist[currentNode] > DistS){
      newDist[currentNode] = DistS;
      for(pair<int, int> i : adjacencyList[currentNode]){
        if(newDist[i.second] > i.first + DistS){
          q.push(make_pair( -1*(i.first + DistS), i.second));
        }
      }
    }
  }

  priority_queue <pair <int, int > > output;
  for(int i = 0; i < stallAmount; i++){
    output.push(make_pair(-1*(dist[stalls[i]]) + -1*(newDist[stalls[i]]), -1*(stalls[i])));
  }
  cout << -1*(output.top().first) << " " << -1*(output.top().second);
  return 0;
}
