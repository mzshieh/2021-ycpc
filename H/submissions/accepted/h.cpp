#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    vector<int> a;
    int Min=0;
    int Max=0;
    for(int i = 0;i<n;i++){
        char c[105];
        scanf("%s",c);
        a.push_back(strlen(c));
        Min=max(Min,(int)strlen(c));
        Max+=strlen(c);
    }
    Min--;
    while(Max>Min+1){
        int mid=(Max+Min)/2;
        int cnt=0,now=mid;
        for(auto it:a){
            if(now+it+1>mid){
                now=it;
                cnt++;
            }
            else{
                now+=it+1;
            }
        }
        if(cnt>24)Min=mid;
        else Max=mid;
    }
    printf("%d\n",Max);
}