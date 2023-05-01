#include <iostream>
#include <vector>

//код написан с использованием https://e-maxx.ru/algo/assignment_hungary#6

std::pair<long long, std::vector<int>> AP(std::vector<std::vector<int>>& cost){
    int n = cost.size();
    std::vector<bool> used (n, false);
    std::vector<int> row_potential(n, 0);
    std::vector<int> column_potential (n, 0);
    std::vector<int> match (n, -1);
    std::vector<int> min_value (n, INT32_MAX); //для каждого столбца - минимальное значение, в него ведущее
    int counter = 0;
    //отим добавлять строчки по одной
    for (int i = 0; i < n; ++i){
        int delta = INT32_MAX;
        std::vector<int> parent (n, -1);
        used.assign(n, false);
        min_value.assign(n, INT32_MAX);
        int curr_i = i; //строка, которую пытаемся продолжить
        int curr_column = -1;
        int next_curr_column;
        while (curr_column == -1 || match[curr_column] != -1){
            if (curr_column != -1) used[curr_column] = true;
            delta = INT32_MAX;
            for (int j = 0; j < n; ++j){
                if (used[j]) continue;
                int diff = cost[curr_i][j] - column_potential[j] - row_potential[curr_i];
                if (min_value[j] > diff){
                    min_value[j] = diff;
                    parent[j] = curr_column;
                }
                if (min_value[j] < delta){
                    delta = min_value[j];
                    next_curr_column = j; //насчитываем столбец, в который перейти дешевле всего
                }
            }
            //считаем потенциалы
            row_potential[i] += delta;
            for (int j = 0; j < n; ++j){
                if (used[j]){
                    column_potential[j] -= delta;
                    row_potential[match[j]] += delta;
                }else{
                    min_value[j] -= delta;//уменьшилось ровно на текущую строку
                }
            }
            curr_column = next_curr_column;
            curr_i = match[curr_column];
        }
        while (curr_column != -1){
            next_curr_column = parent[curr_column];
            if (next_curr_column == -1) match[curr_column] = i;
            else
                match[curr_column] = match[next_curr_column];
            curr_column = next_curr_column;
        }

    }
    long long summary = 0;
    std::vector<int> answer (n);
    for (int i = 0;i < n; ++i){
        summary += cost[match[i]][i];
        answer[match[i]] = i;
    }
    return {summary, answer};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> cost (n);
    for (int i = 0; i < n; ++i){
        cost[i].resize (n);
        for (int j = 0; j < n; ++j){
            std::cin >> cost[i][j];
        }
    }
    auto x = AP(cost);
    std::cout << x.first << '\n';
    for (int i = 0; i < n; ++i){
        std::cout << (i + 1) << " " << ++x.second[i] << '\n';
    }
    return 0;
}
