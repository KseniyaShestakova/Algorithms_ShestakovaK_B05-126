#include <iostream>
class PosSum {

    long long *pos_sum;
public:
    void update(int pos, long long val, int k);
    long long signed_sum(int v, int tl, int tr, int l, int r);
    PosSum(long long* array);
    ~PosSum();
};
PosSum::PosSum(long long*  array) {
    pos_sum=array;
}
PosSum::~PosSum() {
    delete[] pos_sum;
}
void PosSum::update( int pos, long long val, int k){
    int v=k-1+pos;
    pos_sum[v]=val;
    v=(v-1)/2;
    pos_sum[v]=pos_sum[2*v+1]-pos_sum[2*v+2];

    while( v!=0){
        v=(v-1)/2;
        pos_sum[v]=pos_sum[2*v+1]+pos_sum[2*v+2];
    }
}
long long PosSum::signed_sum( int v, int tl, int tr, int l, int r){
    if (tl==l && tr==r){
        return pos_sum[v];
    }
    int tm=(tl+tr)/2;
    long long left_pos_sum=0;
    long long right_pos_sum=0;
    if (l<=tm){
        left_pos_sum=signed_sum(2*v+1, tl, tm, l, std::min(r, tm));
    }
    if (r>tm){
        right_pos_sum= signed_sum(2*v+2, tm+1, tr, std::max(l, tm+1), r);
    }
    if ( tm>=l && (std::min(r, tm)-l+1)%2==0){
        return left_pos_sum+right_pos_sum;
    }
    if (tm< l){
        return right_pos_sum;
    }
    if ( (std::min(r, tm)-l+1)%2==1){
        return left_pos_sum-right_pos_sum;
    }

}
int main() {
    int n;
    std::cin>>n;
    int k=1;
    while ( k<n){
        k*=2;
    }
    long long* pos_sum=new long long [2*k-1];
    for (int i=k-1; i<k-1+n; i++ ){
        std::cin>>pos_sum[i];
    }
    for (int i=k-1+n; i<2*k-1; i++){
        pos_sum[i]=0;

    }
    for (int i=(k/2)-1; i<k-1; i++){
        pos_sum[i]=pos_sum[2*i+1]-pos_sum[2*i+2];
    }
    for (int i=(k/2)-2; i>=0; i--){
        pos_sum[i]=pos_sum[2*i+1]+pos_sum[2*i+2];
    }
    PosSum MyArray(pos_sum);
    int m;
    std::cin>> m;
    int ident;
    int x;
    int y;
    for (int i=0; i<m; i++){
        std::cin>>ident>>x>>y;
        if (ident==0){
            MyArray.update(x-1, y, k);

        }else{
            std::cout<<MyArray.signed_sum( 0, 0, k-1, x-1, y-1)<<'\n';
        }
    }
    delete[] pos_sum;
    MyArray.~PosSum();
    return 0;
}
