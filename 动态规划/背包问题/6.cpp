//
// Created by axin on 2022/11/24.
//

//6.多重背包 单调队列优化
//时间复杂度为 O(n * m)
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 20010;

int n, m;
//g存储i - 1层的f数组.
//q为单调队列, 存储的是每个特定的余数下, 滑动窗口大小为s + 1的前提下, 单调下降的最大价值的下标
int f[N], g[N], q[N];

int main(){
    cin >> n >> m;
    //枚举所有的背包
    for(int i = 0; i < n; i ++ ){
        int v, w, s;
        cin >> v >> w >> s;
        //拷贝存储i - 1层的f
        memcpy(g, f, sizeof f);
        //枚举所有的余数, 相当于进行分类 分成了v类
        for(int j = 0; j < v; j ++ ){
            int hh = 0, tt = -1;
            //更新单调队列
            for(int k = j; k <= m; k += v ){
                //当前滑动窗口的大小超过了s + 1 即 (k - q[hh]) / v + 1 > s + 1, 需要弹出队首
                //由于每个元素最多出队入队一次, 所以此处if即可, 当然换成while也行
                if(hh <= tt && k - q[hh] > s * v) hh ++;
                //当且仅当 由 i - 1层的g[q[tt]]转移到 i层的g[k]时, 如果比他小, 那么就没有了存在的必要
                //注意这里为什么是i层的g[k], 因为他至少从i - 1层g[k]开始, 由于是一维数组, 所以不需要额外更新
                while(hh <= tt && g[q[tt]] + (k - q[tt]) / v * w <= g[k]) tt --;
                //i层的k入队
                q[ ++ tt] = k;
                //更新f[k], 由单调队列的定义来看,从i - 1层的队首转移而来, 最大.
                f[k] = g[q[hh]] + (k - q[hh]) / v * w;
            }
        }
    }
    //f[m]即为容量不超过m的最大价值和.
    cout << f[m] << endl;
    return 0;
}