#include<bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    vector<long long> seg, lazy;

    SegmentTree(int n) {
        seg.resize(4*n + 1);
        lazy.resize(4*n + 1, 0);
    }

    long long build(int ind, int low, int high, vector<int>& nums) {
        if (low == high) {
            return seg[ind] = nums[low];
        }
        int mid = (low + high) >> 1;
        long long left = build(2*ind + 1, low, mid, nums);
        long long right = build(2*ind + 2, mid + 1, high, nums);

        return seg[ind] = left + right;
    }

    void update(int ind, int low, int high, int l, int r, int val) {
        // Propagate any pending lazy updates 
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind]; 
            if (low != high) {
                lazy[2*ind + 1] += lazy[ind];  
                lazy[2*ind + 2] += lazy[ind];  
            }
            lazy[ind] = 0;  
        }

        // No overlap
        if (r < low || l > high) return;

        // Complete overlap
        if (low >= l && high <= r) {
            seg[ind] += (high - low + 1) * val;
            if (low != high) {
                lazy[2*ind + 1] += val;
                lazy[2*ind + 2] += val;
            }
            return;
        }

        int mid = (low + high) >> 1;
        update(2*ind + 1, low, mid, l, r, val);
        update(2*ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2*ind + 1] + seg[2*ind + 2];
    }

    long long query(int ind, int low, int high, int idx) {
        // Propagate any pending lazy updates
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];
            if (low != high) {
                lazy[2*ind + 1] += lazy[ind];
                lazy[2*ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // If we have reached the desired index
        if (low == high) {
            return seg[ind];
        }

        int mid = (low + high) >> 1;
        if (idx <= mid) {
            return query(2*ind + 1, low, mid, idx);
        } else {
            return query(2*ind + 2, mid + 1, high, idx);
        }
    }
};


int main() {
    int n, q;
    cin >> n >> q;
    
    vector<vector<char>> nums(n, vector<char>(n));
    for (int i = 0; i < n; i++){
        for(int j = 0; j<n; j++){
            cin>>nums[i][j];
        }
    }
    
    vector<vector<int>> pref(n+1, vector<int>(n+1, 0));
    
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            
            pref[i][j] = (nums[i-1][j-1] == '*') + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
        }
    }
    
    
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        
        l1--, r1--, l2--, r2--;
        
        int result = pref[l2+1][r2+1] 
                   - (l1 > 0 ? pref[l1][r2+1] : 0)
                   - (r1 > 0 ? pref[l2+1][r1] : 0)
                   + (l1 > 0 && r1 > 0 ? pref[l1][r1] : 0);
        
        cout << result << endl;
    }

    return 0;
}
