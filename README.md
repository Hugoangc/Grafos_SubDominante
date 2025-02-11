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

## 📌 **Conclusões**
- Para **n < 20**, a **Força Bruta Raiz** ainda é viável.
- Para **n < 500**, o **Branch and Bound** é a melhor opção, pois encontra a solução ótima rapidamente.
- Para **n > 500**, **GRASP** é a melhor escolha, pois roda em tempo curto e ainda encontra soluções próximas da ótima, mas acaba perdendo desempenho após **n > 5000**.
