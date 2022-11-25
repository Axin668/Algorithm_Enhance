//
// Created by 陈艺欣 on 2022/11/25.
//

//1013.机器分配
//其实可以用一维数组, 但是由于要记录路径, 所以要改成二维数组. 所以这样也就不用逆着遍历了
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 11, M = 16;

int n, m;
//定义价值矩阵, w[i][j]即给每个公司i分配j台设备 可以收获w[i][j]价值
int w[N][M];
//f[i][j] 表示从前i个公司中选, 给他们分配的设备总个数 <= j时候得到的最大价值和
int f[N][M];
//记录应该给每个公司i分配多少台设备
int way[N];

int main(){
    cin >> n >> m;

    //读入价值矩阵
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= m; j ++ )
            cin >> w[i][j];

    //枚举所有子公司
    for(int i = 1; i <= n; i ++ )
        //由于已经记录了i - 1层的结果, 所以可以正着枚举所有的背包容量
        for(int j = 0; j <= m; j ++ )
            //枚举所有可以转移的状态 也就是可分配的设备数量不超过j
            for(int k = 0; k <= j; k ++ )
                //省略的写法 正规的写法如下
                f[i][j] = max(f[i][j], f[i - 1][j - k] + w[i][k]);
    // f[i][j] = f[i - 1][j];
    // for(int k = 1; k <= j; k ++ )
    //     f[i][j] = max(f[i][j], f[i - 1][j - k] + w[i][k]);

    cout << f[n][m] << endl;

    //逆着寻找最优解是由每个子公司分配多少台设备转移而来,
    int j = m;
    //每个子公司的编号
    for(int i = n; i; i -- )
        //可以由哪些状态转移而来
        for(int k = 0; k <= j; k ++ )
            //找到了直接break
            if(f[i][j] == f[i - 1][j - k] + w[i][k]){
                way[i] = k;
                j -= k;
                break;
            }

    for(int i = 1; i <= n; i ++ ) cout << i << " " << way[i] << endl;
    return 0;
}