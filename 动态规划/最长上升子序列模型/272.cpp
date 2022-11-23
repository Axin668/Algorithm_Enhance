//
// Created by 陈艺欣 on 2022/11/23.
//

//272.最长公共上升子序列(LIS与LCS的结合体)
//以b[j]结尾体现为LIS, 是否包含a[i]体现为LCS
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 3010;

int n;
//存储a序列, b序列
int a[N], b[N];
//f[i][j] 表示 所有a[1 ~ i] 和 b[1 ~ j]中以b[j]结尾的所有公共上升子序列的集合, 其值等于所有子序列长度的最大值
int f[N][N];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i ++ ) scanf("%d", &b[i]);

    for(int i = 1; i <= n; i ++ ){
        //代表所有a[1 ~ i - 1] 和 b[1 ~ j] 中以b[j] 结尾的所有公共上升子序列 再加上a[i]的最大值
        //主要是为了方便计算a[i] == b[j] 的情况, 相当于一个预处理
        int maxv = 1;
        for(int j = 1; j <= n; j ++ ){
            //不包含a[i]
            f[i][j] = f[i - 1][j];
            //包含a[i] 先使用j - 1层的maxv
            if(a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
            //再更新j层的maxv 这样就省掉了一层循环
            if(a[i] > b[j]) maxv = max(maxv, f[i - 1][j] + 1);
        }
    }

    int res = 0;
    //由于答案最大值不一定以b[j]结尾, 所以需要取一下max
    for(int i = 1; i <= n; i ++ ) res = max(res, f[n][i]);
    printf("%d\n", res);

    return 0;
}