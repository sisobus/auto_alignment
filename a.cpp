#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
vector<string> inputVectorString(int n) {
    vector<string> ret;
    while ( n-- ) {
        char buf[128];
        scanf("%s",buf);
        ret.push_back(string(buf));
    }
    return ret;
}
void printVectorString(vector<string>& v) {
    for ( int i = 0 ; i < (int)v.size() ; i++ )
        printf("%s ",v[i].c_str());
    puts("");
}
/*
 * d[i][j][mask]: i번째 워드를 포함하며 mask만큼의 태그를 선택했을 때
 *              j상태인 얻을 수 있는 최대 스코어
 *              j = 연속에서 워드를 포함한 숫자
 *  O(n*m*(2^m))
 *  getScore  = word1 : tag1
 *  getScore2 = word2 : tag1
 */
int d[11][3][1<<7];
int getScore(string& s1, string& s2) {
    int ret = 0;
    for ( int i = 0 ; i < (int)s1.length() && i < (int)s2.length() ; i++ ) 
        ret += (s1[i] != s2[i]);
    return ret;
}
int getScore2(string& s1,string& s2,string& s3) {
    return 3;
}
vector<int> getPrevIndex(int mask) {
    vector<int> ret;
    for ( int i = 0 ; (1<<i) <= mask ; i++ ) 
        if ( (1<<i)&mask ) ret.push_back(i);
    return ret;
}
int main() {
    int n;
    scanf("%d",&n);
    vector<string> words = inputVectorString(n);
    int m;
    scanf("%d",&m);
    vector<string> tags = inputVectorString(m);
    printVectorString(words);
    printVectorString(tags);

    memset(d,0,sizeof d);
    for ( int i = 0 ; i < m ; i++ ) {
        d[0][1][(1<<i)] = getScore(words[0],tags[i]);
    }

    for ( int i = 1 ; i < n ; i++ ) 
        for ( int j = 0 ; j < (1<<m) ; j++ ) {
            d[i][0][j] = max(max(d[i-1][0][j],d[i-1][1][j]),d[i-1][2][j]);
            vector<int> prevIndex = getPrevIndex(j);
            d[i][1][j] = max(d[i][1][j],d[i-1][1][j]);
            for ( int k = 0 ; k < (int)prevIndex.size() ; k++ ) {
                int prevMask = j&(~(1<<prevIndex[k]));
                d[i][1][j] = max(d[i][1][j],d[i-1][0][prevMask]+getScore(words[i],tags[prevIndex[k]]));
                d[i][2][j] = max(d[i][2][j],d[i-1][1][prevMask]+getScore(words[i],tags[prevIndex[k]]));
                d[i][2][j] = max(d[i][2][j],d[i-1][0][prevMask]+getScore(words[i-1],words[i],tags[prevIndex[k]]));
            }
        }
    int ans = max(max(d[n-1][0][(1<<m)-1],d[n-1][1][(1<<m)-1]),d[n-1][2][(1<<m)-1]);
    printf("%d\n",ans);

    return 0;
}
