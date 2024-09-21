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

    SegmentTree stree(n);
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    stree.build(0, 0, n - 1, nums);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r, val;
            cin >> l >> r >> val;

            stree.update(0, 0, n - 1, l - 1, r - 1, val);
        } else {
            int l;
            cin >> l;

            cout << stree.query(0, 0, n - 1, l - 1) << endl;
        }
    }

    return 0;
}
