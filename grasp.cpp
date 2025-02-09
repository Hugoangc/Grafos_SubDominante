#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

int n;                    // Número de vértices
vector<vector<int>> adj;  // Lista de adjacência
vector<int> bestSolution; // Melhor conjunto encontrado

// Função para calcular um conjunto independente guloso randomizado
vector<int> greedyRandomized(float alpha)
{
  vector<int> degree(n + 1);
  vector<bool> selected(n + 1, false);

  // Calcula o grau de cada vértice
  for (int v = 1; v <= n; v++)
    degree[v] = adj[v].size();

  // Lista de vértices ordenada pelo grau (com randomização controlada)
  vector<int> vertices(n);
  for (int i = 1; i <= n; i++)
    vertices[i - 1] = i;

  random_device rd;
  mt19937 gen(rd());
  shuffle(vertices.begin(), vertices.end(), gen); // Embaralha os vértices

  vector<int> independentSet;
  for (int v : vertices)
  {
    if (!selected[v])
    {
      independentSet.push_back(v);
      // Marca os vizinhos para não serem escolhidos
      for (int u : adj[v])
        selected[u] = true;
    }
  }

  return independentSet;
}

// Busca Local para Refinamento da Solução
vector<int> localSearch(vector<int> solution)
{
  set<int> currentSet(solution.begin(), solution.end());

  for (int v = 1; v <= n; v++)
  {
    if (currentSet.count(v))
      continue; // Já está no conjunto

    bool canAdd = true;
    for (int u : adj[v])
    {
      if (currentSet.count(u))
      {
        canAdd = false;
        break;
      }
    }

    if (canAdd)
      currentSet.insert(v); // Expande o conjunto
  }

  return vector<int>(currentSet.begin(), currentSet.end());
}

// Algoritmo GRASP
vector<int> grasp(int maxIterations, float alpha)
{
  vector<int> bestSet;
  int bestSize = 0;

  for (int i = 0; i < maxIterations; i++)
  {
    vector<int> solution = greedyRandomized(alpha);
    solution = localSearch(solution);

    if (solution.size() > bestSize)
    {
      bestSize = solution.size();
      bestSet = solution;
    }
  }

  return bestSet;
}

void readGraph(const string &filename)
{
  ifstream file(filename);
  if (!file)
  {
    cerr << "Erro ao abrir o arquivo!" << endl;
    exit(1);
  }

  file >> n;
  adj.resize(n + 1);
  int u, v;
  while (file >> u >> v)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

int main()
{
  string nome_arquivo;
  cout << "Informe o nome do arquivo a ser analisado: ";
  cin >> nome_arquivo;
  auto start = high_resolution_clock::now();

  readGraph(nome_arquivo);

  bestSolution = grasp(1000, 0.3); // 1000 iterações, alpha = 0.3

  auto end = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end - start);

  cout << "Tamanho do maior conjunto independente encontrado: " << bestSolution.size() << endl;
  cout << "Vertices: ";
  for (int v : bestSolution)
    cout << v << " ";
  cout << endl;

  cout << "Tempo de execucao: " << duration.count() / 1000.0 << " segundos" << endl;

  return 0;
}
