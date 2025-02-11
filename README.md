# Grafos_SubDominante

# Comparação de Algoritmos para o Problema do Subconjunto Independente Máximo

Este repositório contém uma comparação de diferentes algoritmos utilizados para resolver o problema do **Subconjunto Independente**. Abaixo, apresentamos a análise de três abordagens principais:

1. **Força Bruta Raiz (Exaustiva)**
2. **Branch and Bound (Poda e Recursão)**
3. **GRASP (Greedy Randomized Adaptive Search Procedure - Heurística Avançada)**

---

## 🔹 **Descrição dos Algoritmos**
### ✅ **Força Bruta Raiz**
- Testa **todos os subconjuntos possíveis (`2^n`)** e verifica qual é o maior conjunto independente.
- **Vantagem:** Sempre encontra a solução ótima.
- **Desvantagem:** Impraticável para `n > 30`, pois cresce exponencialmente.
- **Melhor para:** Pequenos grafos (`n < 15`).

### ✅ **Branch and Bound**
- Usa **busca recursiva com poda** para evitar explorar soluções claramente ruins.
- **Vantagem:** Encontra a solução ótima muito mais rápido que a força bruta.
- **Desvantagem:** Ainda cresce exponencialmente, mas é **muito mais rápido** que a força bruta pura.
- **Melhor para:** `n < 100`, mas pode ser viável até `n ≈ 500`.

### ✅ **GRASP (Heurística Avançada)**
- Uma **heurística aleatória e gulosa**, que **gera boas soluções rapidamente**.
- **Vantagem:** Muito rápido (`O(n log n)`) e escala bem para `n > 1000`.
- **Desvantagem:** Não garante a solução ótima, mas chega muito perto.
- **Melhor para:** `n > 500`, podendo lidar com `n = 4000+` em minutos.

---

## 📊 **Tabela de Tempos de Execução**
| Algoritmo            | N=6  | N=7  | N=8  | N=15 | N=20  | N=28   | N=50   | N=450  | N=450  | N=595  | N=760  | N=1400 | N=1534 | N=4000  |
|----------------------|------|------|------|------|-------|--------|--------|--------|--------|--------|--------|--------|--------|---------|
| **Força Bruta Raiz** | 0s   | 0s   | 0s   | 0.1s | 4.124s| 1416.79s | -    | -    | -    | -    | -    | -    | -    | -    |
| **Branch and Bound** | 0s   | 0s   | 0s   | 0s   | 0.001s | 0.047s  | 803.88s | -    | -    | -    | -    | -    | -    | -    |
| **GRASP**            | 0.017s | 0.016s | 0.022s | 0.021s | 0.023s | 0.029s | 0.04s | 1.064s | 1s  | 1.468s | 2.15s | 5.327s | 6.205s | 316.952s |

---
## 🚨 Por que alguns algoritmos se tornam inviáveis?

O problema do **Subconjunto Independente** é **NP-difícil**, o que significa que não há um algoritmo conhecido que resolva todos os casos de forma eficiente para grandes `n`. Alguns métodos se tornam **inviáveis** dependendo do tamanho da entrada.  

---

### ❌ **Força Bruta é inviável para `n > 30`**
O algoritmo de **força bruta pura** testa **todos os subconjuntos possíveis** (`2^n`), o que cresce **exponencialmente**.  

📌 **O crescimento do número de subconjuntos (`2^n`)**:  
| **n**  | **Subconjuntos (2ⁿ)** | **Tempo estimado** (1 bilhão de ops/s) |
|--------|----------------------|--------------------------------|
| **10**  | `1.024`             | **Instantâneo** ✅            |
| **20**  | `1.048.576`         | **0.001s** ⚡                 |
| **30**  | `1.073 × 10⁹`       | **1 segundo** ⏳              |
| **40**  | `1.099 × 10¹²`      | **18 minutos** ⏳⏳            |
| **50**  | `1.126 × 10¹⁵`      | **13 dias** ⏳💀              |
| **100** | `10³⁰`              | **Idade do universo** 🌌💀  |


📢 **Por isso, a força bruta se torna inviável para `n > 30`, pois o tempo de execução cresce exponencialmente.** 🚀  

---

### ❌ **Branch and Bound é inviável para `n > 100`**
O **Branch and Bound** melhora a força bruta ao **eliminar ramos da busca** que claramente não levam à solução ótima.  

📌 **Por que ele ainda se torna inviável?**  
- No pior caso, o **número de ramos explorados** ainda pode ser **exponencial**.  
- Para **`n ≈ 100`**, mesmo com podas eficientes, o número de estados pode chegar a **milhões ou bilhões**, tornando o tempo de execução impraticável.  

📌 **Estimativa de tempo para Branch and Bound** (varia dependendo da estrutura do grafo):  
| **n**   | **Tempo esperado** |
|---------|--------------------|
| **50**  | **Segundos a minutos** ✅ |
| **80**  | **Minutos a horas** ⏳ |
| **100** | **Horas a dias** ❌ |
| **150** | **Dias a semanas** ❌ |
| **200+** | **Anos ou mais** 💀 |

📢 **Por isso, Branch and Bound se torna inviável para `n > 100` em instâncias difíceis.**  

---

### 🚀 **O que fazer para `n > 100`?**
✅ **Usar heurísticas como GRASP ou Algoritmos Genéticos** (rápidos, mas não garantem a solução ótima).  
✅ **Usar ILP (Integer Linear Programming) com Gurobi/GLPK para `n < 500`**.  
✅ **Aproximações baseadas em coloração de grafos para `n ≳ 1000`**.  

---
## 📌 **Conclusões**
- Para **n < 20**, a **Força Bruta Raiz** ainda é viável.
- Para **n < 500**, o **Branch and Bound** é a melhor opção, pois encontra a solução ótima rapidamente.
- Para **n > 500**, **GRASP** é a melhor escolha, pois roda em tempo curto e ainda encontra soluções próximas da ótima, mas acaba perdendo desempenho após **n > 5000**.
