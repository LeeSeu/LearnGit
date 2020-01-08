#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;
//换硬币问题
/*
f(n)=0  if n==0
f(n)=1+min{f(n-ci)|i~[1,k]} ci为面值，n为总金额
*/
int coinChange(vector<int> &coins,int amount)
{
    if(amount==0)   return 0;
    int ans=INT_MAX;
    for(int i=0;i<coins.size();++i){
        if(amount-coins[i]<0)   continue;
        int subProb=coinChange(coins,amount-coins[i]);
        if(subProb==-1)   continue;
        ans=min(ans,subProb+1);
    }
    return ans==INT_MAX?-1:ans;
}

//自顶向下过程，将原问题逐渐分解成小规模的问题
int helper(vector<int> &coins,int amount,vector<int> &memo)
{
    if(amount==0)   return 0;
    if(memo[amount]!=-2)    return memo[amount];

    int ans=INT_MAX;
    for(int i=0;i<coins.size();++i){
        if(amount-coins[i]<0)   continue;
        int subProb=helper(coins,amount-coins[i],memo);//将递归想象成black box方法，对于某种币值来说，减去它后所需要的硬币数目
        if(subProb==-1)     continue;
        ans=min(ans,subProb+1);
    }
    //记录该例调用栈的解
    memo[amount]=(ans==INT_MAX?-1:ans);
    return memo[amount];
}

int coinChange2(vector<int> &coins,int amount)
{
    vector<int> memo(amount+1,-2);
    //带备忘录的解
    return helper(coins,amount,memo);
}

int coinChangeDp(vector<int> &coins,int amount)
{
    vector<int> dp(amount+1,amount+1);//amount+1个表格
    dp[0]=0;
    for(int i=0;i<dp.size();++i){
        for(int j=0;j<coins.size();++j){
            if(i-coins[j]<0)    continue;
            dp[i]=min(dp[i],1+dp[i-coins[j]]);

        }
    }
    return (dp[amount]==amount+1?-1:dp[amount]);
}









