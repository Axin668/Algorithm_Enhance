//
// Created by 陈艺欣 on 2022/11/15.
//

//102.最佳牛围栏(实数域二分)
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int N = 200010;
int a[N], b[N], c[N];
int lang[3 * N], ans[3 * N], cnt[3 * N];
int n, m;
int k, v;

int find(int x){
    return lower_bound(ans + 1, ans + 1 + v, x) - ans;
}

int main(){
    //将科学家们会的语言以及电影的语言和字母都放入容器lang中, 方便排序, 去重, 离散化
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ ){
        scanf("%d", &a[i]);
        lang[++ k] = a[i];
    }

    scanf("%d", &m);
    for(int i = 1; i <= m; i ++ ){
        scanf("%d", &b[i]);
        lang[++ k] = b[i];
    }
    for(int i = 1; i <= m; i ++ ){
        scanf("%d", &c[i]);
        lang[++ k] = c[i];
    }

    //排序
    sort(lang + 1, lang + k + 1);

    //去重
    for(int i = 1; i <= k; i ++ ){
        if(i == 1 || lang[i - 1] != lang[i])
            ans[++ v] = lang[i];
    }

    //统计科学家们会的语言的数量, cnt下标与ans中离散化之后的坐标是对应的
    for(int i = 1; i <= n; i ++ ) cnt[find(a[i])] ++;

    int res = 0, ans1 = 0, ans2 = 0;
    for(int i = 1; i <= m; i ++ ){
        int ansx = cnt[find(b[i])], ansy = cnt[find(c[i])];
        if(ansx > ans1 || (ansx == ans1 && ansy > ans2)){
            res = i, ans1 = ansx, ans2 = ansy;
        }
    }

    //注意边界的判断
    cout << (res == 0 ? 1 : res) << endl;
    return 0;
}