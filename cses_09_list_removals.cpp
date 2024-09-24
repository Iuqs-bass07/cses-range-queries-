#include<bits/stdc++.h>
using namespace std;

// class SegmentTree{

// public:
//     vector<int> seg;
//     SegmentTree(int n){
//         seg.resize(4*n+1, 0);
//         for(int i = 0; i < n; i++){
//             update(0, 0, n-1, i);
//         }
//     }
    
//     int query(int ind, int low, int high, int k){
//         if(low == high){
//             return low;
//         }
        
//         int mid = (low + high)>>1;
//         if(k <= seg[2*ind+1]){
//             query(2*ind+1, low, mid, k);
//         }
//         else{
//             query(2*ind+2, mid+1, high, k - seg[2*ind+1]);
//         }
//     }
    
//     void update(int ind, int low, int high, int idx){
        
//         if(low == high){
//             seg[ind] = 1 - seg[ind];
//             return;
//         }
        
//         int mid = (low + high)>>1;
        
//         if(idx <= mid){
//             update(2*ind+1, low, mid, ind);
//         }
//         else{
//             update(2*ind+2, mid+1, high, idx);
//         }
//         seg[ind] = seg[2*ind+1] + seg[2*ind+2];
//     }
// };

using vi = vector<int>;
 
struct SegmentTree {
    int n;
    vi t;
    SegmentTree(int x) {
        n = x, t.resize(4*n + 1, 0);
        for(int i = 0;i<n;++i) {
            update(1, 0, n - 1, i);
        }
        return;
    }
    void update(int v, int tl, int tr, int p) {
        if (tl == tr) {
            t.at(v) = 1 - t.at(v);
        }
        else {
            int tm = (tl + tr)/2;
            (p <= tm ? update(v*2, tl, tm, p):update(v*2 + 1, tm + 1, tr, p));
            t.at(v) = t.at(v*2) + t.at(v*2 + 1);
        }
        return;
    }
    int query(int v, int tl, int tr, int k) {
        if (tl == tr) {
            return tl;
        }
        int tm = (tl + tr)/2;
        return (k <= t.at(v*2) ? query(v*2, tl, tm, k):query(v*2 + 1, tm + 1, tr, k - t.at(v*2)));
    }
};
// int main(){
    
//     int n;
//     cin>>n;
    
//     vector<int> nums(n);
//     for(int i = 0; i<n; i++) cin>>nums[i];
    
//     SegmentTree stree(n);
    
//     for(int i = 0; i<n; i++){
        
//         int idx;
//         cin>>idx;
        
//         int val = stree.query(0, 0, n-1, idx);
//         cout<<nums[val]<<" ";
//         stree.update(0, 0, n-1, val);
//     }
// }

int main() {
    int n;
    cin >> n;
    int a[n];
    for(int& v:a) {
        cin >> v;
    }
    SegmentTree T(n);
    for(int i = 0, x;i<n;++i) {
        cin >> x;
        int p = T.query(1, 0, n - 1, x);
        cout << a[p] << ' ';
        T.update(1, 0, n - 1, p);
    }
    cout << endl;
    return 0;
}
