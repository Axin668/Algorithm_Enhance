//
// Created by 陈艺欣 on 2022/11/11.
//

//275.传纸条(1027.方格取数 的变式)
//本题可以看做两个人传纸条都从相同的起点传送到终点, 而不是一来一回
//所以只是在稀疏图上作了修改, 其余不变
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 55;
int w[N][N];
int f[N * 2][N][N];
int n, m;
int a, b, c;

int main(){
    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
        {
            scanf("%d", &w[i][j]);
        }

    for(int k = 2; k <= n + m; k ++ )
        for(int i1 = 1; i1 <= n; i1 ++ )
            for(int i2 = 1; i2 <= n; i2 ++ ){
                int j1 = k - i1, j2 = k - i2;
                if(j1 >= 1 && j1 <= m && j2 >= 1 && j2 <= m){
                    int t = w[i1][j1];
                    if(i1 != i2) t += w[i2][j2];
                    int &x = f[k][i1][i2];
                    x = max(x, f[k - 1][i1 - 1][i2- 1] + t);
                    x = max(x, f[k - 1][i1][i2 - 1] + t);
                    x = max(x, f[k - 1][i1- 1][i2] + t);
                    x = max(x, f[k - 1][i1][i2] + t);
                }
            }

    cout << f[n + m][n][n] << endl;
    return 0;
}