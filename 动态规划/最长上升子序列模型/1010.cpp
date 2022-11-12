//
// Created by 陈艺欣 on 2022/11/11.
//

//1010.拦截炮弹(LIS + 贪心)
//此题可以类比 896.最长上升子序列II 贪心做法
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010;
int n;
int a[N], f[N], g[N];

int main(){
    //此处可以用stringstream流
    while(cin >> a[n]) n ++;

    int res = 0;
    //求最长不上升子序列
    for(int i = 0; i < n; i ++ ){
        f[i] = 1;
        for(int j = 0; j < i; j ++ )
            if(a[i] <= a[j])
                f[i] = max(f[i], f[j] + 1);
        res = max(res, f[i]);
    }
    cout << res << endl;

    int cnt = 0;
    //贪心计算 策略: 每次选取一个系统, 该系统满足末尾是最小的大于a[i]的数字, 把a[i]接在他的后边
    //同时更新该系统的末尾, 即把末尾缩小一点
    for(int i = 0; i < n; i ++ ){
        int k = 0;
        //贪心的寻找
        while(k < cnt && g[k] < a[i]) k ++;
        //更新末尾
        g[k] = a[i];
        //没找到, 就新开一个系统
        if(k >= cnt) cnt ++;
    }
    cout << cnt << endl;

    return 0;
}