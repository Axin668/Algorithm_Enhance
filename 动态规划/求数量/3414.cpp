//
// Created by axin on 2022/11/22.
//

//3414.校门外的树 22次ccf-csp第四题
//动态规划-求数量类型
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long LL;

const int N = 1010, M = 100010, mod = 1e9 + 7;
int n;
//f[i]表示以第i个节点为右端点, 种树的总方案数
int a[N], f[N];
//存储数字的所有约数
vector<int> q[M];
//判断公差被使用的情况 已经被用过的话 后边就不可以继续用了 否则会冲突
bool st[M];

int main(){
    //预处理数据范围内所有数字的约数, 也即公差
    for(int i = 1; i < M; i ++ )
        for(int j = 2 * i; j < M; j += i )
            q[j].push_back(i);

    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);

    //以0号点结尾的区间种树方案为1, 啥都不种.
    f[0] = 1;
    for(int i = 1; i < n; i ++ ){
        //重新处理一下所有公差
        memset(st, 0, sizeof st);
        //倒着枚举的原因是不如倒着方便 因为之间所有障碍物与右端点构成的公差及其约数都不能使用 但是随着正着枚举的过程中刚开始不能用的 后续又可以用了.
        //不如直接倒着枚举, 边走边确定哪些彻底不能用.
        for(int j = i - 1; j >= 0; j -- ){
            //区间长度——用于计算公差
            int d = a[i] - a[j], cnt = 0;
            for(auto k : q[d])
                //如果公差没被使用过
                if(! st[k]){
                    cnt ++;
                    st[k] = true;
                }
            //d(本身)这个公差也不能用, 否则就种在了障碍物上
            st[d] = true;
            //更新一下方案数
            f[i] = (f[i] + (LL)f[j] * cnt) % mod;
        }
    }
    printf("%d\n", f[n - 1]);
    return 0;
}