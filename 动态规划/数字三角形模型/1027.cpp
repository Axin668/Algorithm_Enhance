//
// Created by 陈艺欣 on 2022/11/10.
//

//1027.方格取数(三维数字三角形模型)
//本题类似于1015.摘花生 1018.最低通行费
//时间复杂度O(n ^ 3 ), 避免了n ^ 4
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 15;

int a, b, c;
int w[N][N];
//f[k][i1][i2]表示 经过k步, 两条路径分别到达(i1, j1) 和 (i2, j2) 所能达到的最大数字和
//两条路径分别到达终点, 至少需要2 * n 步
int f[N * 2][N][N];
int n;

int main(){
    scanf("%d", &n);

    //读入稀疏图
    while(cin >> a >> b >> c, a || b || c) w[a][b] = c;

    //由于有三个维度, 先循环k, 即当前步数
    for(int k = 2; k <= 2 * n; k ++ )
        //循环第一条路径的横坐标
        for(int i1 = 1; i1 <= n; i1 ++ )
            //循环第一条路径的横坐标
            for(int i2 = 1; i2 <= n; i2 ++ ){
                //分别求出两条路径的纵坐标
                int j1 = k - i1, j2 = k - i2;
                //两个点必须有意义, 才可以进行状态转移
                if(j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n){
                    //判断两个点是否重合, 若重合则只加1次, 否则加两次
                    int t = w[i1][j1];
                    //不重合
                    if(i1 != i2) t += w[i2][j2];
                    //引用写法, 用于简写
                    int &x = f[k][i1][i2];
                    //四种状态转移
                    x = max(x, f[k - 1][i1 - 1][i2 - 1] + t);
                    x = max(x, f[k - 1][i1 - 1][i2] + t);
                    x = max(x, f[k - 1][i1][i2 - 1] + t);
                    x = max(x, f[k - 1][i1][i2] + t);
                }

            }

    //输出经历2 * n 步, 两条路径到达终点的数字和
    cout << f[n + n][n][n] << endl;
    return 0;
}