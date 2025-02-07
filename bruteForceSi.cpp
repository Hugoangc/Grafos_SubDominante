#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <cmath>
#include <chrono> 

using namespace std;
using namespace chrono;

int n;                   // Número de vértices
vector<vector<int>> adj; // Lista de adjacência
vector<int> bestSet;
int maxSize = 0;

bool isIndependentSet(const vector<int> &subset)
{
  set<int> nodes(subset.begin(), subset.end());
  for (int v : subset)
  {
    for (int u : adj[v])
    {
      if (nodes.count(u))
        return false; // Tem aresta entre dois vértices do subconjunto
    }
  }
  return true;
}

int main()
{
  auto start = high_resolution_clock::now();

  ifstream file("n28.txt"); 
  if (!file)
  {
    cerr << "Erro ao abrir o arquivo!" << endl;
    return 1;
  }

  file >> n;         // Número de vértices
  adj.resize(n + 1); // Lista de adjacência (1-indexado)

  int u, v;
  while (file >> u >> v)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // Gera todos os 2^n subconjuntos
  long long totalSubsets = (1LL << n); // 2^n
  for (long long mask = 0; mask < totalSubsets; mask++)
  {
    vector<int> subset;
    for (int i = 0; i < n; i++)
    {
      if (mask & (1LL << i))
        subset.push_back(i + 1);
    }

    if (isIndependentSet(subset) && subset.size() > maxSize)
    {
      maxSize = subset.size();
      bestSet = subset;
    }
  }

  auto end = high_resolution_clock::now(); 
  auto duration = duration_cast<milliseconds>(end - start);

  cout << "Tamanho do maior conjunto independente: " << maxSize << endl;
  cout << "Vértices: ";
  for (int v : bestSet)
    cout << v << " ";
  cout << endl;

  cout << "Tempo de execução: " << duration.count() / 1000.0 << " segundos" << endl;

  return 0;
}
