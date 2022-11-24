//
// Created by axin on 2022/11/23.
//

//1022.宠物小精灵之收服(二维花费背包问题)
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010, M = 510;

int n, V1, V2;
//f[i][j] 表示精灵球花费不超过i, 皮卡丘体力花费不超过j的收服精灵的最大数量
int f[N][M];

int main(){
    cin >> V1 >> V2 >> n;

    for(int i = 0; i < n; i ++ ){
        int v1, v2;
        cin >> v1 >> v2;
        for(int j = V1; j >= v1; j -- )
            for(int k = V2 - 1; k >= v2; k -- )
                f[j][k] = max(f[j][k], f[j - v1][k - v2] + 1);
    }

    cout << f[V1][V2 - 1] << " ";
    //正着找 k此时的位置就是最小的体力花费位置
    // int k = 0;
    // while(k < V2 && f[V1][k] != f[V1][V2 - 1]) k ++;

    //反着找 k此时的位置是最小体力花费的前一个
    // int k = V2 - 1;
    // while(k >= 0 && f[V1][k] == f[V1][V2 - 1]) k --;
    //cout << V2 - (k + 1) << endl;

    //或者反着找 k此时的位置就是最小的体力花费位置
    int k = V2 - 1;
    while(k > 0 && f[V1][k - 1] == f[V1][V2 - 1]) k --;
    cout << V2 - k << endl;

    return 0;
}