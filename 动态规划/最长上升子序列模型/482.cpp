//
// Created by axin on 2022/11/11.
//

//482.合唱队形
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010;
int n;
int a[N], f[N], g[N];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);

    for(int i = 1; i <= n; i ++ ){
        f[i] = 1;
        for(int j = 1; j < i; j ++ ){
            if(a[i] > a[j])
                f[i] = max(f[i], f[j] + 1);
        }
    }

    for(int i = n; i; i -- ){
        g[i] = 1;
        for(int j = n; j > i; j -- ){
            if(a[i] > a[j])
                g[i] = max(g[i], g[j] + 1);
        }
    }

    int res = 0;
    for(int i = 1; i <= n; i ++ ){
        res = max(res, g[i] + f[i] - 1);
    }
    printf("%d\n", n - res);

    return 0;
}