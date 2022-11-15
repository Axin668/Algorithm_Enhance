//
// Created by axin on 2022/11/11.
//

//1012.友好城市(最长上升子序列)
//若南边的城市已经有序排列, 合理建桥之后, 选定的北方城市也一定要单调递增(是一个上升序列), 否则就会交叉.
//因此问题转化为: 先把南边城市升序排好, 再对北方城市求最长上升子序列的长度, 此即为最多建桥数量(不相交)
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 5010;

struct Pair{
    int north, south;

    bool operator< (const Pair &w)const{
        return south < w.south;
    }
}p[N];

int n;
int f[N];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ ){
        int north, south;
        scanf("%d%d", &south, &north);
        p[i] = {south, north};
    }
    sort(p + 1, p + n + 1);

    int res = 0;
    for(int i = 1; i <= n; i ++ ){
        f[i] = 1;
        for(int j = 1; j < i; j ++ ){
            if(p[i].north > p[j].north)
                f[i] = max(f[i], f[j] + 1);
        }
        res = max(res, f[i]);
    }

    cout << res << endl;
    return 0;
}