#include <iostream>

class SparseTable{
    int number_of_elements;
    int** first;
    int** second;
    int* deg;
    int* arr;
public:
    SparseTable(int* arr, int n);
    int getSecondMin(int l, int r);
    ~SparseTable();
};
int SparseTable::getSecondMin( int l, int r){
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

int log_2(int i){
    if (i==0) return 0;
    int answer= log_2(i-1);
    if ( !((i+1)&i)){
        answer++;
    }
    return answer;
}

SparseTable::SparseTable(int *arr, int n) {
    number_of_elements=n;
    deg=new int[number_of_elements+1];

    for (int i=0; i<number_of_elements; i++){
        deg[i]= log_2(i);
    }
    /*
    Исходная версия подсчета массива логарифмов, чуть более быстрая, т.к подсчитывает очередное число за O(1)
    deg[0]=0;
    for (int i=1; i<number_of_elements+1; i++){
        deg[i]=deg[i-1];
        if ( !((i+1)&i)){
            deg[i]++;
        }
    }*/
    int k=deg[number_of_elements-1];
    first=new int*[k+1];
    second=new int*[k+1];
    for (int i=0; i<=k; i++){
        first[i]=new int[number_of_elements];
        second[i]=new int[number_of_elements];
    }
    for (int i=0; i<number_of_elements; i++){
        first[0][i]=i;
        second[0][i]=i;
    }
    for (int i=0; i<number_of_elements-1; i++){
        if (std::min(arr[i], arr[i+1])==arr[i]){
            first[1][i]=i;
            second[1][i]=i+1;
        }else{
            first[1][i]=i+1;
            second[1][i]=i;
        }
    }
    first[1][number_of_elements-1]=number_of_elements-1;
    second[1][number_of_elements-1]=number_of_elements-1;
    for ( int j=2; j<=k; j++){
        for (int i=0; i<number_of_elements; i++){
            if ( i+(1<<(j-1))>=number_of_elements){
                first[j][i]=first[j-1][i];
                second[j][i]=second[j-1][i];
                continue;
            }
            if (i+(1<<(j-1))==number_of_elements-1){
                if ( std::min( arr[first[j-1][i]], arr[first[j-1][number_of_elements-1]])== arr[first[j-1][i]]){
                    first[j][i]=first[j-1][i];
                    if ( std::min( arr[first[j-1][number_of_elements-1]], arr[second[j-1][i]])==arr[first[j-1][number_of_elements-1]]){
                        second[j][i]=first[j-1][number_of_elements-1];
                        continue;
                    }
                    second[j][i]=second[j-1][i];
                    continue;
                }
                first[j][i]=first[j-1][number_of_elements-1];
                second[j][i]=first[j-1][i];
                continue;
            }
            if ( std::min( arr[first[j-1][i]], arr[first[j-1][i+(1<<(j-1))]] )==arr[first[j-1][i]]){
                first[j][i]=first[j-1][i];
                if ( std::min( arr[second[j-1][i]], arr[first[j-1][i+(1<<(j-1))]] )==arr[second[j-1][i]]){
                    second[j][i]=second[j-1][i];
                    continue;
                }
                second[j][i]=first[j-1][i+(1<<(j-1))];
                continue;
            }
            int border=i+(1<<(j-1));
            first[j][i]=first[j-1][border];
            if ( std::min( arr[first[j-1][i]], arr[second[j-1][i+(1<<(j-1))]])==arr[second[j-1][i+(1<<(j-1))]]){
                second[j][i]=second[j-1][i+(1<<(j-1))];
                continue;
            }
            second[j][i]=first[j-1][i];
        }
    }
}

SparseTable::~SparseTable() {
    int k= deg[number_of_elements-1];
    for (int i=0; i<=k; i++){
        delete[] first[i];
        delete[] second[i];
    }
    delete[] first;
    delete[] second;
    delete[] deg;
    delete[] arr;
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
    SparseTable MySparseTable(arr, n);
    int l;
    int r;
    for (int i=0; i<m; i++){
        std::cin>>l;
        std::cin>>r;
        std::cout<< MySparseTable.getSecondMin(l-1, r-1)<<'\n';
    }
    MySparseTable.~SparseTable();

    return 0;
}
