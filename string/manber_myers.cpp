pair<bool, int> mm_find(string s) {
    int l = lcp(mm_s, pos[0], s, 0);
    int r = lcp(mm_s, pos[mm_s.size() - 1], s, 0);

    if(l == s.size() || s[l] < mm_s[pos[0] + l])
        return make_pair(l == s.size(), pos[0]);
    else if(r == s.size() || s[r] > mm_s[pos[mm_s.size() - 1] + r])
        return make_pair(r == s.size(), pos[mm_s.size() - 1]);

    int low = 0, high = mm_s.size() - 1, next, st_n = 0, c_lcp;
    while(high - low > 1) {
        int mid = (low + high)/2;
        c_lcp = max(l, r);
        st_n = 2*st_n + 1 + (l < r);

        if(mm_segtree[st_n] >= c_lcp)
            next = c_lcp + lcp(mm_s, pos[mid] + c_lcp, s, c_lcp);
        else
            next = mm_segtree[st_n];

        if(next == s.size())
            return make_pair(true, pos[mid]);
        else if(s[next] > mm_s[pos[mid] + next]) {
            low = mid;
            l = next;
        }
        else {
            high = mid;
            r = next;
        }
    }

    return make_pair(false, pos[high]);
}
