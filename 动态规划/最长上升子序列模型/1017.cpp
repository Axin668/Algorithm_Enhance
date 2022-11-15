//
// Created by axin on 2022/11/11.
//

//1017.怪盗基德的滑翔伞(最长上升与下降子序列 两遍即可)
//类似于1014.登山 482.合唱队形
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int a[N], f[N];
int n;

int main(){
    int T;
    scanf("%d", &T);

    while(T -- ){
        scanf("%d", &n);

        for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);

        int res = 0;
        //正向求解LIS
        for(int i = 1; i <= n; i ++ ){
            f[i] = 1;
            for(int j = 1; j < i; j ++ ){
                if(a[i] > a[j])
                    f[i] = max(f[i], f[j] + 1);
            }
            res = max(res, f[i]);
        }

        //反向求解LIS
        for(int i = n; i; i -- ){
            f[i] = 1;
            for(int j = n; j > i; j -- ){
                if(a[i] > a[j])
                    f[i] = max(f[i], f[j] + 1);
            }
            res = max(res, f[i]);
        }

        //输出全局最大值
        printf("%d\n", res);
    }
    return 0;
}