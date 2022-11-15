//
// Created by axin on 2022/11/11.
//

//1016.最长上升子序列的和
//本题不再求长度, 而是更新上升序列的最大值
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010;
int n;
int a[N], f[N];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);

    int res = 0;
    for(int i = 1; i <= n; i ++ ){
        f[i] = a[i];
        for(int j = 1; j < i; j ++ ){
            if(a[i] > a[j])
                f[i] = max(f[i], f[j] + a[i]);
        }
        res = max(res, f[i]);
    }

    cout << res << endl;
    return 0;
}