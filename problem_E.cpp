/*Шестакова Ксения, Б05-126
https://codeforces.com/group/PVbQ8eK2T4/contest/350943/submission/134595681

+ x – добавить в мультимножество число x.
? x – посчитать сумму чисел не больших x.
Формат входных данных
В первой строке содержится число запросов 1 6 q 6 105
.
Далее каждая строка содержит один запрос.
Все числа x целые от 0 до 109 − 1.
Формат выходных данных
Ответы на все запросы вида ? x*/
#include <iostream>
#include <vector>

class DynamicTree{
    std::vector<long long> sum;
    std::vector<int> left_border;
    std::vector<int> right_border;
    std::vector<int> left;
    std::vector<int> right;
public:
    DynamicTree();
    void update(int v, long long pos, int x);
    long long getSum(int v, int left_border, int right_border, int l, int r);
};

DynamicTree::DynamicTree() {
    sum.resize(0);
    left_border.resize(0);
    right_border.resize(0);
    left.resize(0);
    right.resize(0);
    sum.push_back(0);
    left_border.push_back(0);
    right_border.push_back(999999999);
    left.push_back(-1);
    right.push_back(-1);
}

void DynamicTree::update( int v, long long pos, int x){
    sum[v]+=x;
    if ( left_border[v]==right_border[v] ) return;
    int tm=(left_border[v]+right_border[v])/2;
    if (left[v]==-1 && pos<=tm){
        sum.push_back(0);
        left_border.push_back(left_border[v]);
        right_border.push_back(tm);
        left.push_back(-1);
        right.push_back(-1);
        left[v]=sum.size()-1;
    }
    if ( pos<=tm) update( left[v], pos, x);
    if (right[v]==-1 && pos>tm){
        sum.push_back(0);
        left_border.push_back(tm+1);
        right_border.push_back(right_border[v]);
        left.push_back(-1);
        right.push_back(-1);
        right[v]=sum.size()-1;
    }
    if ( pos>tm) update(right[v], pos, x);
}

long long DynamicTree::getSum(int v, int _left_border, int _right_border, int l, int r){
    if ( _left_border==l && _right_border==r)  return sum[v];
    int tm=(_left_border+_right_border)/2;
    long long left_sum=0;
    long long right_sum=0;
    if ( l<=tm && (left[v]!=-1))
        left_sum= getSum(left[v], _left_border, tm, l, std::min(r, tm));
    if ( r>tm && right[v]!=-1)
        right_sum= getSum(right[v], tm+1, _right_border, std::max(l, tm+1), r);
    return left_sum+right_sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int q;
    std::cin>> q;
    DynamicTree MyDynamicTree;
    char ident;
    int x;
    for (int i=0; i<q; i++){
        std::cin>> ident;
        std::cin>> x;
        if ( ident=='+'){
            MyDynamicTree.update(0, x, x);

        }else{
            std::cout<< MyDynamicTree.getSum( 0, 0, 999999999, 0, x)<<'\n';
        }
    }
    return 0;
}
