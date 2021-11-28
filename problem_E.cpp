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
void update( int v, long long pos, int x, std::vector<long long> &sum, std::vector<int> &tl,
             std::vector<int> &tr, std::vector<int> &left, std::vector<int> &right){
    sum[v]+=x;
    if ( tl[v]==tr[v] ) return;
    int tm=(tl[v]+tr[v])/2;
    if (left[v]==-1 && pos<=tm){
        sum.push_back(0);
        tl.push_back(tl[v]);
        tr.push_back(tm);
        left.push_back(-1);
        right.push_back(-1);
        left[v]=sum.size()-1;
    }
    if ( pos<=tm) update( left[v], pos, x, sum, tl, tr, left, right);
    if (right[v]==-1 && pos>tm){
        sum.push_back(0);
        tl.push_back(tm+1);
        tr.push_back(tr[v]);
        left.push_back(-1);
        right.push_back(-1);
        right[v]=sum.size()-1;
    }
    if ( pos>tm) update(right[v], pos, x, sum, tl, tr, left, right);
}
long long getSum(int v, int left_border, int right_border, int l, int r, std::vector<long long> &sum, std::vector<int> &tl,
                 std::vector<int> &tr, std::vector<int> &left, std::vector<int> &right){
    if ( left_border==l && right_border==r)  return sum[v];
    int tm=(left_border+right_border)/2;
    long long left_sum=0;
    long long right_sum=0;
    if ( l<=tm && (left[v]!=-1))
        left_sum= getSum(left[v], left_border, tm, l, std::min(r, tm), sum, tl, tr, left, right);
    if ( r>tm && right[v]!=-1)
        right_sum= getSum(right[v], tm+1, right_border, std::max(l, tm+1), r,sum, tl, tr, left, right);
    return left_sum+right_sum;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int q;
    std::cin>> q;
    std::vector<long long> sum(0);
    std::vector<int> tl (0);
    std::vector<int> tr (0);
    std::vector<int> left (0);
    std::vector<int> right (0);
    sum.push_back(0);
    tl.push_back(0);
    tr.push_back(999999999);
    left.push_back(-1);
    right.push_back(-1);
    char ident;
    int x;

    for (int i=0; i<q; i++){
        std::cin>> ident;
        std::cin>> x;
        if ( ident=='+'){
            update(0, x, x, sum, tl, tr, left, right);

        }else{
            std::cout<< getSum( 0, 0, 999999999, 0, x, sum, tl, tr, left, right)<<'\n';
        }
    }
    return 0;
}
