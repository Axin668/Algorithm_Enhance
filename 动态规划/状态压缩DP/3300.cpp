//
// Created by axin on 2022/11/22.
//

//3300.食材运输 21次ccf-csp第4题
//状态压缩DP + 二分 + 贪心

#include <iostream>
#include <algorithm>
#include <cstring>

#define x first
#define y second

using namespace std;

//x存储从当前位置i出发, 送完当前物资j的距离的两倍. y存贮路途中距离i的最远的距离
//因为送完指定物资不用回来, 所以送该物资的最短距离为 x(不变) - y(越大越好)
typedef pair<int, int> PII;
const int N = 110, M = 10, S = 1 << M;

int n, m, k;
//各个酒店对于各种物资的需要
int need[N][M];
//存储无向边
int h[N], e[N * 2], w[N * 2], ne[N * 2], idx;
//d存储从i出发送完所有j所需要的最短距离 贪心的思想
int d[N][M];
//f表示所有状态, state表示每个酒店对于一个特定的mid是否能够满足任务(可以满足该列为1 否则为0)
int f[S], state[N];

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

PII dfs(int u, int fa, int v){
    //总和为0, 最大距离为-1 表示不存在
    PII res(0, -1);
    //当前点正好需要, 自己距离自己为0
    if(need[u][v]) res.y = 0;

    //遍历所有子树
    for(int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        //由于是双向边, 指向父亲的边不算
        if(j == fa) continue;
        //查看结果
        auto t = dfs(j, u, v);
        //t.y == -1 表示子树中没有需要物资v的酒店
        if(t.y != -1){
            //更新总距离(2倍), 最大距离
            res.x += t.x + w[i] * 2;
            res.y = max(res.y, t.y + w[i]);
        }
    }
    return res;
}

//对于mid, 选择若干行或运算之后state为全1 表明可以满足所有运输要求
bool check(int mid){
    //重置一下state 重新对于新的mid判断一下
    memset(state, 0, sizeof state);
    for(int i = 1; i <= n; i ++ )
        for(int j = 0; j < k; j ++)
            //只要小于mid, 就可以派一辆车满足该物资要求
            if(d[i][j] <= mid)
                state[i] |= 1 << j;
    //重置一下f
    memset(f, 0x3f, sizeof f);
    //所有物资都不需要, 覆盖它要0行
    f[0] = 0;
    for(int i = 0; i < 1 << k; i ++ )
        for(int j = 1; j <= n; j ++ )
            f[i | state[j]] = min(f[i | state[j]], f[i] + 1);

    //满足所有运输要求后 用车量是否 <= m
    return f[(1 << k) - 1] <= m;
}

int main(){
    scanf("%d%d%d", &n, &m, &k);

    for(int i = 1; i <= n; i ++ )
        for(int j = 0; j < k; j ++ )
            cin >> need[i][j];
    memset(h, -1, sizeof h);
    for(int i = 0; i < n - 1; i ++ ){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    //求一下d(贪心思想)
    for(int i = 1; i <= n; i ++ )
        for(int j = 0; j < k; j ++){
            auto t = dfs(i, -1, j);
            if(t.y != -1) d[i][j] = t.x - t.y;
        }

    //二分一个mid
    int l = 0, r = 2e8;
    while(l < r){
        int mid = l + r >> 1;
        //最小最大值
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", r);
    return 0;
}