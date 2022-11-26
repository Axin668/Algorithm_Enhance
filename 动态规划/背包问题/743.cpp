//
// Created by 陈艺欣 on 2022/11/26.
//

//743.能量石(贪心 + 01背包)
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110, M = 10010;

int n;
//f[i] 表示经历时间恰好为i时, 获得的最大能量
int f[M];

struct Stone{
    int s, e, l;
    bool operator< (const Stone &w)const {
        return s * w.l < l * w.s;
    }
}stone[N];

int main(){
    int T;
    cin >> T;
    for(int C = 1; C <= T; C ++ ){
        cin >> n;
        //累计吃完所有能量石所需要的时间, 相当于体积
        int m = 0;
        for(int i = 1; i <= n; i ++ ){
            int s, e, l;
            cin >> s >> e >> l;
            stone[i] = {s, e, l};
            m += s;
        }
        //贪心, 按照这样的顺序吃, 一定是局部最优的. 之后的dp是选择吃哪些
        sort(stone + 1, stone + n + 1);

        //初始化为负无穷
        memset(f, 0xcf, sizeof f);
        f[0] = 0;

        for(int i = 1; i <= n; i ++ ){
            int s = stone[i].s, e = stone[i].e, l = stone[i].l;
            for(int j = m; j >= s; j -- )
                //j为当前已经经历的时间, 相当于开始吃第i块石头的结束时间
                //j - s为当前石头的等待时间
                f[j] = max(f[j], f[j - s] + max(0, e - (j - s) * l));
        }

        //找一下全局最大值
        int res = 0;
        for(int i = 0; i <= m; i ++ ) res = max(res, f[i]);

        printf("Case #%d: %d\n", C, res);
    }
    return 0;
}
