//
// Created by 陈艺欣 on 2022/11/26.
//

//10.有依赖的背包(树形DP + 分组背包)
//每一个子树的选择相当于分组背包
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110;

int n, m;
//定义各个子节点背包的容量以及价值
int v[N], w[N];
//邻接表存储树的结构
int h[N], e[N], ne[N], idx;
//f[i][j] 表示以i为根结点的子树, 总容量不超过j的最大价值
int f[N][N];

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u){
    //遍历所有子树
    for(int i = h[u]; ~i; i = ne[i]){
        //找到树的编号
        int son = e[i];
        //dfs一下这颗子树
        dfs(son);

        //可以给这颗子树分配的容量 由于是一维数组, 所以需要逆滚
        for(int j = m - v[u]; j >= 0; j -- )
            //作出决策, 应该给这颗子树分配多少容量, 相当于01背包
            for(int k = 0; k <= j; k ++ )
                //当前节点u容量不超过j - k, 子节点son容量不超过k
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
    }

    //上边更新了f[u][0 ~ m - v[u]], 这里更新一下f[u][v[u] ~ m]
    //注意上边dfs子树的过程相当于计算了f[u][i - v[u]], 还没有选择w[u]
    for(int i = m; i >= v[u]; i -- ) f[u][i] = f[u][i - v[u]] + w[u];
    //自己都选择不了, 自然为0
    for(int i = 0; i < v[u]; i ++ ) f[u][i] = 0;
}

int main(){
    cin >> n >> m;
    memset(h, -1, sizeof h);

    int root;
    for(int i = 1; i <= n; i ++ ){
        int p;
        cin >> v[i] >> w[i] >> p;
        if(p == -1) root = i;
            //当前的i 依赖于p 也即有i一定有p, 所以p指向i
        else add(p, i);
    }

    //dfs根结点root
    dfs(root);

    //输出以root为根的子树, 总容量不超过m的最大价值
    cout << f[root][m] << endl;
    return 0;
}