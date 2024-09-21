#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class STree {
    
    vector<ll> seg;
public:

    STree(int n){
        seg.resize(4*n+1);
    }
    
    ll build(int idx, int low, int high, vector<int> &nums){
        
        if(low == high){
            return seg[idx] = nums[low]; 
        }
        
        int mid = (low + high) >> 1;
        ll left = build(2*idx+1, low, mid, nums);
        ll right = build(2*idx+2, mid+1, high, nums);
        
        return seg[idx] = left + right;  
    }
    
    ll query(int idx, int low, int high, int l, int r){
        
        if(high < l || r < low) return 0;
        if(low >= l && high <= r) return seg[idx];
        
        int mid = (low + high) >> 1;
        ll left = query(2*idx+1, low, mid, l, r);
        ll right = query(2*idx+2, mid+1, high, l, r);
        
        return left + right;
    }
    
    void update(int ind, int low, int high, int idx, ll val, vector<int> &nums){
        
        if(low == high){
            seg[ind] = val;  
            return;
        }
        
        int mid = (low + high) >> 1;
        
        if(idx <= mid){
            update(2*ind+1, low, mid, idx, val, nums);
        }
        else{
            update(2*ind+2, mid+1, high, idx, val, nums);
        }
        
        seg[ind] = seg[2*ind+1] + seg[2*ind+2]; 
    }
};

int main(){
    
    int n, q;
    cin >> n >> q;
    
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    
    STree s(n);
    s.build(0, 0, n-1, nums);
    
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << s.query(0, 0, n-1, l-1, r-1) << endl;
    }
    return 0;
}
