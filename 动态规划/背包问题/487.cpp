//
// Created by 陈艺欣 on 2022/11/26.
//

//487.金明的预算方案(分组背包 + 二进制优化)
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

#define v first
#define w second

using namespace std;
typedef pair<int, int> PII;

const int N = 70, M = 32010;
//用n来存储购买物品的个数, m用来存储总钱数
int n, m;
//f[j] 表示总钱数不超过j的情况下最大价值
int f[M];
//用来存储主件, 包括价格和价值
PII master[N];
//用来存储主件的附件, 包括价格和价值
vector<PII> servent[N];

int main(){
    cin >> m >> n;
    for(int i = 1; i <= n; i ++ ){
        int v, p, q;
        cin >> v >> p >> q;
        //计算价值
        p *= v;
        //主件
        if(! q) master[i] = {v, p};
            //附件
        else servent[q].push_back({v, p});
    }

    for(int i = 1; i <= n; i ++ )
        //逆滚
        for(int j = m; j >= 0; j -- )
            //二进制优化, 枚举当前组背包所有方案选择
            //也就是说当前分组只选择一个最佳方案
            for(int dec = 0; dec < 1 << servent[i].size(); dec ++ ){
                int v = master[i].v, w = master[i].w;
                //枚举每一位
                for(int k = 0; k < servent[i].size(); k ++ ){
                    if(dec >> k & 1){
                        v += servent[i][k].v;
                        w += servent[i][k].w;
                    }
                }
                //如果分配的体积(钱数)满足要求, 则更新最大值
                if(j >= v) f[j] = max(f[j], f[j - v] + w);
            }

    cout << f[m] << endl;
    return 0;
}