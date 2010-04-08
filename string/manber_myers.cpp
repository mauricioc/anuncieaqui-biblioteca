int pos[MAXSZ], prm[MAXSZ], cnt[MAXSZ];
bool bh[MAXSZ + 1], b2h[MAXSZ];
int blast[256], bprev[MAXSZ];
int mm_segtree[4*MAXSZ];
string mm_s;

inline void regen_pos(int sz) {
    for(int i = 0; i < sz; ++i)
        pos[prm[i]] = i;
}

inline void bubbleupbucket(int index) {
    if(index < 0) return;

    int& prm_ext = prm[index];
    ++cnt[prm_ext];
    prm_ext += cnt[prm_ext] - 1;
    b2h[prm_ext] = true;
}

void updatetree(int root, int l, int r, int pos, int val) {
    if(l == r) { mm_segtree[root] = val; return; }

    int m = (l + r + 1)/2;
    if(pos < m) updatetree(2*root + 1, l, m - 1, pos, val);
    else updatetree(2*root + 2, m, r, pos, val);

    mm_segtree[root] = min(mm_segtree[2*root + 1], mm_segtree[2*root + 2]);
}

int querytree(int root, int l, int r, int begin, int end) {
    if(begin == l && end == r) return mm_segtree[root];

    int m = (l + r + 1)/2;
    if(begin < m && end < m)
        return querytree(2*root + 1, l, m - 1, begin, end);
    else if(begin >= m && end >= m)
        return querytree(2*root + 2, m, r, begin, end);
    else return min(querytree(2*root + 1, l, m - 1, begin, m - 1),
                    querytree(2*root + 2, m, r, m, end));
}

void mm_build(string s) {
    mm_s = s;
    memset(blast, -1, sizeof blast);
    memset(bh, 0, sizeof(bool) * s.size());
    memset(mm_segtree, 0x3f, sizeof(int) * 4 * s.size());
    updatetree(0, 0, s.size() - 1, s.size() - 1, 0);

    for(int i = 0; i < s.size(); ++i) {
        bprev[i] = blast[s[i]];
        blast[s[i]] = i;
    }
    int let_count = 0;
    for(int i = 0; i < 256; ++i) {
        if(blast[i] != -1) {
            bh[let_count] = true;
            if(let_count > 0)
                updatetree(0, 0, s.size() - 1, let_count - 1, 0);
        }
        for(int j = blast[i]; j != -1; j = bprev[j])
            prm[j] = let_count++;
    }
    regen_pos(s.size());
    bh[s.size()] = true;

    for(int st = 1; st < s.size(); st *= 2) {
        memset(cnt, 0, sizeof(int) * s.size());
        memset(b2h, 0, sizeof(bool) * s.size());

        for(int bl = 0, br = 0; br < s.size(); bl = br++)
            for(; !bh[br]; ++br)
                prm[pos[br]] = bl;

        bubbleupbucket(s.size() - st);
        for(int bl = 0, br = 0; br < s.size(); bl = br) {
            bubbleupbucket(pos[bl] - st);
            for(++br; !bh[br]; ++br)
                bubbleupbucket(pos[br] - st);

            for(int i = bl; i < br; ++i) {
                if(pos[i] - st < 0) continue;
                int prm_ext = prm[pos[i] - st];
                if(b2h[prm_ext])
                    for(int j = prm_ext + 1; !bh[j] && b2h[j]; ++j)
                        b2h[j] = false;
            }
        }

        regen_pos(s.size());
        for(int i = 0; i < s.size(); ++i)
            if(!bh[i] && b2h[i]) {
                bh[i] = true;
                if(pos[i - 1] + st < s.size() && pos[i] + st < s.size()) {
                    int m = min(prm[pos[i - 1] + st], prm[pos[i] + st]);
                    int M = max(prm[pos[i - 1] + st], prm[pos[i] + st]);
                    updatetree(0, 0, s.size() - 1, i - 1,
                               st + querytree(0, 0, s.size() - 1, m, M - 1));
                }
                else
                    updatetree(0, 0, s.size() - 1, i - 1, st);
            }
    }
}

inline int lcp(string& s1, int p1, string& s2, int p2) {
    int limit = min(s1.size() - p1, s2.size() - p2), i;
    for(i = 0; i < limit; ++i) if(s1[p1 + i] != s2[p2 + i]) break;
    return i;
}

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
