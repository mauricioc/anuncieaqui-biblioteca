#include <cstring>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

int mm_pos[MAXSZ], mm_prm[MAXSZ], mm_count[MAXSZ];
bool mm_bh[MAXSZ + 1], mm_b2h[MAXSZ];
int mm_blast[256], mm_bprev[MAXSZ];
int mm_segtree[4*MAXSZ];
string mm_s;

inline void mm_regen_pos(int sz)
{
    for(int i = 0; i < sz; i++)
        mm_pos[mm_prm[i]] = i;
}

inline void mm_bubbleupbucket(int index)
{
    int& prm_ext = mm_prm[index];
    mm_count[prm_ext]++;
    prm_ext += mm_count[prm_ext] - 1;
    mm_b2h[prm_ext] = true;
}

void mm_updatetree(int root, int l, int r, int pos, int val)
{
    if(l == r) { mm_segtree[root] = val; return; }

    int m = (l + r + 1)/2;
    if(pos < m) mm_updatetree(2*root + 1, l, m - 1, pos, val);
    else mm_updatetree(2*root + 2, m, r, pos, val);

    mm_segtree[root] = min(mm_segtree[2*root + 1], mm_segtree[2*root + 2]);
}

int mm_querytree(int root, int l, int r, int begin, int end)
{
    if(l == r) return mm_segtree[root];

    int m = (l + r + 1)/2;
    if(begin < m && end < m) return mm_querytree(2*root + 1, l, m - 1, begin, end);
    else if(begin >= m && end >= m) return mm_querytree(2*root + 2, m, r, begin, end);
    else return min(mm_querytree(2*root + 1, l, m - 1, begin, m - 1),
                    mm_querytree(2*root + 2, m, r, m, end));
}

void mm_build(string s)
{
    mm_s = s;
    memset(mm_blast, -1, sizeof mm_blast);
    memset(mm_bh, 0, sizeof(bool) * s.size());
    memset(mm_segtree, 0x3f, sizeof(int) * 4 * s.size());
    mm_updatetree(0, 0, s.size() - 1, s.size() - 1, 0);

    for(int i = 0; i < s.size(); i++) {
        mm_bprev[i] = mm_blast[s[i]];
        mm_blast[s[i]] = i;
    }
    int let_count = 0;
    for(int i = 0; i < 256; i++) {
        if(mm_blast[i] != -1) {
            mm_bh[let_count] = true;
            if(let_count > 0)
                mm_updatetree(0, 0, s.size() - 1, let_count - 1, 0);
        }
        for(int j = mm_blast[i]; j != -1; j = mm_bprev[j])
            mm_prm[j] = let_count++;
    }
    mm_regen_pos(s.size());
    mm_bh[s.size()] = true;

    for(int st = 1; st < s.size(); st *= 2) {
        memset(mm_count, 0, sizeof(int) * s.size());
        memset(mm_b2h, 0, sizeof(bool) * s.size());

        for(int bl = 0, br = 0; br < s.size(); bl = br)
            for(; br == bl || !mm_bh[br]; br++)
                mm_prm[mm_pos[br]] = mm_prm[mm_pos[bl]];

        mm_bubbleupbucket(s.size() - st);
        for(int bl = 0, br = 0; br < s.size(); bl = br) {
            for(; bl == br || !mm_bh[br]; br++)
                if(mm_pos[br] - st >= 0)
                    mm_bubbleupbucket(mm_pos[br] - st);

            for(int i = bl; i < br; i++) {
                if(mm_pos[i] - st < 0) continue;
                int prm_ext = mm_prm[mm_pos[i] - st];
                if(mm_b2h[prm_ext])
                    for(int j = prm_ext + 1; !mm_bh[j] && mm_b2h[j]; j++)
                        mm_b2h[j] = false;
            }
        }

        mm_regen_pos(s.size());
        for(int i = 0; i < s.size(); i++)
            if(!mm_bh[i] && mm_b2h[i]) {
                mm_bh[i] = true;
                if(mm_pos[i - 1] + st < s.size() && mm_pos[i] + st < s.size())
                {
                    int m = min(mm_prm[mm_pos[i - 1] + st], mm_prm[mm_pos[i] + st]);
                    int M = max(mm_prm[mm_pos[i - 1] + st], mm_prm[mm_pos[i] + st]);
                    mm_updatetree(0, 0, s.size() - 1, i - 1,
                                  st + mm_querytree(0, 0, s.size() - 1, m, M - 1));
                }
                else
                    mm_updatetree(0, 0, s.size() - 1, i - 1, st);
            }
    }
}

inline int mm_lcp(string& s1, int p1, string& s2, int p2)
{
    int limit = std::min(s1.size() - p1, s2.size() - p2), i;
    for(i = 0; i < limit; i++) if(s1[p1 + i] != s2[p2 + i]) break;
    return i;
}

pair<bool, int> mm_find(string s)
{
    int l = mm_lcp(mm_s, mm_pos[0], s, 0);
    int r = mm_lcp(mm_s, mm_pos[mm_s.size() - 1], s, 0);

    if(l == s.size() || s[l] < mm_s[mm_pos[0] + l])
        return make_pair(l == s.size(), mm_pos[0]);
    else if(r == s.size() || s[r] > mm_s[mm_pos[mm_s.size() - 1] + r])
        return make_pair(r == s.size(), mm_pos[mm_s.size() - 1]);

    int low = 0, high = mm_s.size() - 1, next, st_n = 0, c_lcp;
    while(high - low > 1) {
        int mid = (low + high)/2;
        c_lcp = max(l, r);
        st_n = 2*st_n + 1 + (l < r);

        if(mm_segtree[st_n] >= c_lcp)
            next = c_lcp + mm_lcp(mm_s, mm_pos[mid] + c_lcp, s, c_lcp);
        else
            next = mm_segtree[st_n];

        if(next == s.size())
            return make_pair(true, mm_pos[mid]);
        else if(s[next] > mm_s[mm_pos[mid] + next]) {
            low = mid;
            l = next;
        }
        else {
            high = mid;
            r = next;
        }
    }

    return make_pair(false, mm_pos[high]);
}
