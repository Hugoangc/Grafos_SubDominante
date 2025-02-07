#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
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

// Branch and Bound para encontrar o maior conjunto independente
void branchAndBound(vector<int> &currentSet, vector<int> &candidates, int index)
{
    // Poda: se não há mais candidatos suficientes para superar maxSize, retorna
    if (currentSet.size() + (candidates.size() - index) <= maxSize)
        return;

    // Se chegamos ao final, verifica se encontrou um melhor conjunto independente
    if (index == candidates.size())
    {
        if (currentSet.size() > maxSize)
        {
            maxSize = currentSet.size();
            bestSet = currentSet;
        }
        return;
    }

    int v = candidates[index];

    // Verifica se pode adicionar 'v' sem quebrar a independência
    bool canAdd = true;
    for (int u : adj[v])
    {
        if (find(currentSet.begin(), currentSet.end(), u) != currentSet.end())
        {
            canAdd = false;
            break;
        }
    }

    // Escolhe incluir 'v'
    if (canAdd)
    {
        currentSet.push_back(v);
        branchAndBound(currentSet, candidates, index + 1);
        currentSet.pop_back();
    }

    // Escolhe não incluir 'v'
    branchAndBound(currentSet, candidates, index + 1);
}

int main()
{
    auto start = high_resolution_clock::now(); // Marca tempo de início

    ifstream file("n50.txt");
    if (!file)
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    file >> n;         // n de vértices
    adj.resize(n + 1); // Lista de adjacência (1-indexado)

    int u, v;
    while (file >> u >> v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Ordena os vértices por menor grau primeiro (heurística para reduzir a busca)
    vector<int> candidates(n);
    for (int i = 1; i <= n; i++)
        candidates[i - 1] = i;
    sort(candidates.begin(), candidates.end(), [](int a, int b)
         { return adj[a].size() < adj[b].size(); });

    vector<int> currentSet;
    branchAndBound(currentSet, candidates, 0);

    auto end = high_resolution_clock::now(); // Marca tempo de término
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Tamanho do maior conjunto independente: " << maxSize << endl;
    cout << "Vertices: ";
    for (int v : bestSet)
        cout << v << " ";
    cout << endl;

    cout << "Tempo de execucao: " << duration.count() / 1000.0 << " segundos" << endl;

    return 0;
}
