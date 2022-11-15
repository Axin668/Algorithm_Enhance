//
// Created by axin on 2022/11/12.
//

//187.导弹防御系统(本题其实是贪心思路, 借鉴了贪心思路来剪枝, 主体是爆搜)
//首先注意本题与最长上升子序列2的区别. 前者数组含义是：每个长度不同的最长上升子序列的末尾值(末尾值最小, 横坐标即为长度, 构造结果单调上升)。而后者是所有不同的单调序列的末尾值(通过构造策略, up构成下非上升, down
//构造成非下降)
//主要解决枚举的高度应该放在上升序列还是下降序列里边, 如下:
//i: 放在上升序列, 在所有比它低的高度结尾中, 接在那个最大的后边(这样会留下更多小结尾, 方便后续插入), 当之前的所有高度结尾都大于当前高度, 就创建一个新的系统。
//   由此可见, 构造的up数组是单调不上升序列, 因为只有找不到比它小的才会新建。
//ii: 放在下降序列, 在所有比它高的高度结尾中, 接在那个最小的后边(这样会留下更多大结尾, 方便后续插入), 当之前的所有高度结尾都小于当前高度, 就创建一个新的系统。
//   由此可见, 构造的down数组是单调不下降序列, 因为只有找不到比它大的才会新建。
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 55;

int n;
//高度数组
int h[N];
//所有不同序列(贪心成的不同系统)的末尾值
int up[N], down[N];
int ans;

void dfs(int u, int su, int sd){
    //超过没必要更新
    if(su + sd >= ans) return;
    //看看是否可以更新更小的ans
    if(u == n ){
        ans = min(ans, su + sd);
        return;
    }

    int k = 0;
    while(k < su && h[u] <= up[k]) k ++;
    //在单调不上升的up序列中找到可以接的位置
    if(k < su){
        int t = up[k];
        up[k] = h[u];
        dfs(u + 1, su, sd);
        up[k] = t;
    }
    //找不到
    else{
        up[k] = h[u];
        dfs(u + 1, su + 1, sd);
    }

    k = 0;
    while(k < sd && h[u] >= down[k]) k ++;
    //在单调不下降的序列中找到可以接的位置
    if(k < sd){
        int t = down[k];
        down[k] = h[u];
        dfs(u + 1, su, sd);
        down[k] = t;
    }
    //找不到
    else{
        down[k] = h[u];
        dfs(u + 1, su, sd + 1);
    }
}

int main(){
    while(cin >> n, n){
        for(int i = 0; i < n; i ++ ) cin >> h[i];

        //ans最多为n, 用于更新min
        ans = n;
        dfs(0, 0, 0);

        cout << ans << endl;
    }
    return 0;
}