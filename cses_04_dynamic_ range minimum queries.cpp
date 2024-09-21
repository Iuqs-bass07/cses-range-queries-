#include<bits/stdc++.h>
using namespace std;

class SGTree{
    
    vector<int> seg;
public:
    SGTree(int n){
        seg.resize(4*n+1);
    }
    
    int build(int ind, int low, int high, vector<int> &nums){
        
        if(low == high){
            return seg[ind] = nums[low];
        }
        int mid = (low + high)>>1;
        
        int l = build(2*ind+1, low, mid, nums);
        int r = build(2*ind+2, mid+1, high, nums);
        
        return seg[ind] = min(l, r);
    }
    
    
    int query(int ind, int low, int high, int l, int r){
        
        //no overlap
        if(l > high || r < low) return INT_MAX;
        
        //complete overlap
        if(low >= l && high <= r) return seg[ind];
        
        int mid = (low + high)>>1;
        int left = query(2*ind + 1, low, mid, l, r);
        int right = query(2*ind + 2, mid+1, high, l, r);
        
        return min(left, right);
    }
    
    void update(int ind, int low, int high, int idx, int val){
        
        if(low == high){
            seg[ind] = val;
            return;
        }
        
        int mid = (low + high)>>1;
        
        if(idx <= mid){
            update(2*ind+1, low, mid, idx, val);
        }
        else{
            update(2*ind+2, mid+1, high, idx, val);
        }
        
        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
        return;
    }
};


int main(){
    
    int n, q;
    cin>>n>>q;
    
    vector<int> nums(n);
    for(int i = 0; i<n; i++) cin>>nums[i];
    
    SGTree s(n);
    
    s.build(0, 0, n-1, nums);
    
    
    while(q--){
        
        int type;
        cin>>type;
        
        if(type == 1){
            int idx, val;
            cin>>idx>>val;
            
            nums[idx-1] = val;
            s.update(0, 0, n-1, idx-1, val);
            
        }
        else{
            int l, r;
            cin>>l>>r;
            
            cout<<s.query(0, 0, n-1, l-1, r-1)<<endl;
        }
        
    }
    
    return 0;
}