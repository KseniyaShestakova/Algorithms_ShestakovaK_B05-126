#include <iostream>
#include <vector>
#include <queue>

std::vector<int> dijkstra(std::vector<std::vector<int>>& cost, std::vector<std::vector<int>>& capacity,
                          std::vector<std::vector<int>>& children, std::vector<std::vector<int>>& flow){
    //считаем расстояние от 2*n до всех остальных в терминах цены
    int n = (children.size() - 2) / 2;
    std::vector<int> dist (2 * n + 2, INT32_MAX);
    std::vector<int> used (2 * n + 2);
    std::priority_queue<std::pair<int, int>> q;
    dist[2 * n] = 0;
    q.emplace(0, 2 * n);
    std::vector<int> parent (2 * n + 2, -1);
    while (!q.empty()){
        auto top = q.top();
        q.pop();
        if (used[top.second]) continue;
        used[top.second] = true;
        for (auto u : children[top.second]){
            if (capacity[top.second][u] <= flow[top.second][u]) continue;
            if (used[u]) continue;
            if (dist[u] > dist[top.second] + cost[top.second][u]){
                parent[u] = top.second;
                dist[u] = dist[top.second] + cost[top.second][u];
                q.emplace(-dist[u], u);
            }
        }
    }
    //хотим выбрать кратчайший путь из истока в сток и по нему пустить единицу потока
    int end = 2 * n + 1;
    while (parent[end] != -1){
        flow[parent[end]][end] += 1;
        flow[end][parent[end]] -= 1;
        end = parent[end];
    }
    return dist;
}

std::vector<int> ford_bellman(std::vector<std::vector<int>>& cost, std::vector<std::vector<int>>& capacity,
                              std::vector<std::vector<int>>& children){
    //считаем расстояние от 2*n до всех остальных в терминах цены
    //ребра children ориентированы в обе стороны
    int n = (children.size() - 2) / 2;
    std::vector<std::vector<int>> dp (2 * n + 2); //применяем только в начале, когда нет циклов отрицательной длины
    for (int i = 0; i < 2 * n + 2; ++i){
        dp[i].assign(2 * n + 2, INT32_MAX);
    }
    dp[0][2 * n] = 0;
    for (int k = 1; k < 2 * n + 2; ++k){
        for (int v = 0; v < 2 * n + 2; ++v){
            dp[k][v] = dp[k - 1][v];
            for (auto to: children[v]){
                if (!capacity[to][v]) continue;
                if (dp[k - 1][to] == INT32_MAX) continue;
                dp[k][v] = std::min(dp[k][v], dp[k - 1][to] + cost[to][v]);
            }
        }
    }
    return dp[2 * n + 1];
}

void apply_potential(std::vector<std::vector<int>>& cost, std::vector<int>& potential){
    int sz = cost.size();
    for (int i = 0; i < sz; ++i){
        for (int j = 0; j < sz; ++j){
            cost[i][j] += potential[i] - potential[j];
        }
    }
}

std::vector<std::vector<int>> min_cost_k_flow(int k, std::vector<std::vector<int>>& capacity,
                                              std::vector<std::vector<int>>& cost, std::vector<std::vector<int>>& children){
    auto dist = ford_bellman(cost, capacity, children);
    apply_potential(cost, dist);
    int n = (children.size() - 2) / 2;
    std::vector<std::vector<int>> flow (2 * n + 2);
    for (int i = 0; i < 2 * n + 2; ++i){
        flow[i].resize(2 * n + 2);
    }
    for (int i = 0; i < k; ++i){
        auto new_dist = dijkstra(cost, capacity, children, flow);
        //пустить единицу потока
        apply_potential(cost, new_dist);
    }
    return flow;
}

std::pair<long long, std::vector<std::pair<int, int>>> assignment_problem(std::vector<std::vector<int>>& capacity,
                                                                          std::vector<std::vector<int>>& cost, std::vector<std::vector<int>>& children){
    auto initial_cost = cost;
    int n = (capacity.size() - 2) /2;
    auto flow = min_cost_k_flow(n, capacity, cost, children);
    std::vector<std::pair<int, int>> answer;
    long long min_cost = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (flow[i][j + n]){
                min_cost += initial_cost[i][j + n];
                answer.emplace_back(i, j);
                continue;
            }
        }
    }
    return {min_cost, answer};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> capacity (2 * n + 2);
    for (int i = 0; i < 2 * n + 2; ++i){
        capacity[i].resize(2 * n + 2);
    }
    capacity[2 * n].assign(n, 1);
    capacity[2 * n].resize(2 * n + 2, 0);
    for (int i = n; i < 2 * n; ++i){
        capacity[i][2 * n + 1] = 1;
    }
    std::vector<std::vector<int>> cost (2 * n + 2);
    for (int i = 0; i < 2 * n + 2; ++i){
        cost[i].resize(2 * n + 2);
    }
    std::vector<std::vector<int>> children (2 * n + 2);
    children[2 * n].reserve (n);
    children[2 * n + 1].reserve(n);
    for (int i = 0; i < 2 * n; ++i){
        children[i].reserve(n + 1);
        if (i < n){
            children[i].push_back(2 * n);
            children[2 * n].push_back(i);
        }
        else{
            children[i].push_back(2 * n + 1);
            children[2 * n + 1].push_back(i);
        }
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            std::cin >> cost[i][j + n];
            cost[j + n][i] = -cost[i][j + n];
            capacity[i][j + n] = 1;
            children[i].push_back(j + n);
            children[j + n].push_back(i);
        }
    }
    auto answer = assignment_problem(capacity, cost, children);
    std::cout << answer.first << '\n';
    for (auto p: answer.second){
        std::cout << ++(p.first) << " " << ++(p.second) << '\n';
    }
    return 0;
}
