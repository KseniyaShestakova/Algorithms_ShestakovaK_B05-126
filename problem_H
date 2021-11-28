/*Шестакова Ксения, Б05-126
https://codeforces.com/group/PVbQ8eK2T4/contest/350943/submission/134496810


Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.

Для решения задачи используйте структуру данных Sparse Table. Требуемое время обработки каждого диапазона O(1). Время подготовки структуры данных O(nlogn).

Входные данные
В первой строке заданы 2 числа: размер последовательности N и количество диапазонов M.

Следующие N целых чисел задают последовательность. Далее вводятся M пар чисел - границ диапазонов.

Выходные данные
Для каждого из M диапазонов напечатать элемент последовательности - 2ю порядковую статистику. По одному числу в строке.
*/

#include <iostream>
int getSecond( int l, int r, int** first, int** second, int* deg,int* arr){
    if ( r-l+1==2){
        if (std::min( arr[l], arr[r])==arr[l]) return arr[r];
        else return arr[l];

    }

    int pow=deg[r-l];
    int first_stat;
    if ( std::min(arr[first[pow][l]], arr[first[pow][r+1-(1<<pow)]])==arr[first[pow][l]]){
        first_stat=first[pow][l];
        if ( first_stat>=r+1-(1<<pow)){// first stat лежит на обоих отрезках, т.е дальше можно сравнивать только вторые
            return std::min(arr[second[pow][l]], arr[second[pow][r+1-(1<<pow)]]);
        }else {//случай, когда максимум не лежит на правом отрезке, но лежит на левом
            return std::min(arr[second[pow][l]], arr[first[pow][r + 1 - (1 << pow)]]) ;
        }

    }else{
        first_stat=first[pow][r+1-(1<<pow)];//случай, когда максимум слева не максимум всего отрезка
        return std::min( arr[first[pow][l]], arr[second[pow][r+1-(1<<pow)]]);
    }


}

int main() {
    int n;
    std::cin>> n;
    int m;
    std::cin>>m;
    int* arr=new int[n];
    for (int i=0; i<n; i++){
        std::cin>> arr[i];
    }
    int* deg=new int[n+1];
    deg[0]=0;
    for (int i=1; i<n+1; i++){
        deg[i]=deg[i-1];
        if ( !((i+1)&i)){
            deg[i]++;
        }
    }
    int k=deg[n-1];
    int** first=new int*[k+1];
    int** second=new int*[k+1];
    for (int i=0; i<=k; i++){
        first[i]=new int[n];
        second[i]=new int[n];
    }
    for (int i=0; i<n; i++){
        first[0][i]=i;
        second[0][i]=i;
    }
    for (int i=0; i<n-1; i++){
        if (std::min(arr[i], arr[i+1])==arr[i]){
            first[1][i]=i;
            second[1][i]=i+1;
        }else{
            first[1][i]=i+1;
            second[1][i]=i;
        }
    }
    first[1][n-1]=n-1;
    second[1][n-1]=n-1;
    for ( int j=2; j<=k; j++){
        for (int i=0; i<n; i++){
            if ( i+(1<<(j-1))>=n){
                first[j][i]=first[j-1][i];
                second[j][i]=second[j-1][i];
            }else{
                if (i+(1<<(j-1))==n-1){
                    if ( std::min( arr[first[j-1][i]], arr[first[j-1][n-1]])== arr[first[j-1][i]]){
                        first[j][i]=first[j-1][i];
                        if ( std::min( arr[first[j-1][n-1]], arr[second[j-1][i]])==arr[first[j-1][n-1]]){
                            second[j][i]=first[j-1][n-1];
                        }else{
                            second[j][i]=second[j-1][i];
                        }
                    }else{
                        first[j][i]=first[j-1][n-1];
                        second[j][i]=first[j-1][i];
                    }
                }else{
                    if ( std::min( arr[first[j-1][i]], arr[first[j-1][i+(1<<(j-1))]] )==arr[first[j-1][i]]){

                        first[j][i]=first[j-1][i];
                        if ( std::min( arr[second[j-1][i]], arr[first[j-1][i+(1<<(j-1))]] )==arr[second[j-1][i]]){
                            second[j][i]=second[j-1][i];
                        }else{
                            second[j][i]=first[j-1][i+(1<<(j-1))];
                        }
                    }else{
                        int border=i+(1<<(j-1));

                        first[j][i]=first[j-1][border];
                        if ( std::min( arr[first[j-1][i]], arr[second[j-1][i+(1<<(j-1))]])==arr[second[j-1][i+(1<<(j-1))]]){
                            second[j][i]=second[j-1][i+(1<<(j-1))];
                        }else{
                            second[j][i]=first[j-1][i];
                        }
                    }
                }
                }
        }
    }
    int l;
    int r;
    for (int i=0; i<m; i++){
        std::cin>>l;
        std::cin>>r;
        std::cout<< getSecond(l-1, r-1, first, second, deg, arr)<<'\n';
    }
    for (int i=0; i<=k; i++){
        delete[] first[i];
        delete[] second[i];
    }
    delete[] first;
    delete[] second;
    delete[] deg;
    delete[] arr;

    return 0;
}
