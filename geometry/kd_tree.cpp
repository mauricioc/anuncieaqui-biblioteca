int tree[4*MAXSZ];
TYPE split[4*MAXSZ];
vector<pt> pts;

void kd_recurse(int root, int left, int right, bool x) {
    if(left == right) {
        tree[root] = left;
        return;
    }

    int mid = (right+left)/2;
    nth_element(pts.begin() + left, pts.begin() + mid,
                pts.begin() + right + 1, x ? compx : compy);
    split[root] = x ? pts[mid].x : pts[mid].y;

    kd_recurse(2*root+1, left, mid, !x);
    kd_recurse(2*root+2, mid+1, right, !x);
}

void kd_build() {
    memset(tree, -1, sizeof tree);
    kd_recurse(0, 0, pts.size() - 1, true);
}

int kd_query(int root, int a, int b, int c, int d, bool x) {
    if(tree[root] != -1)
        return a <= pts[tree[root]].x && pts[tree[root]].x <= b &&
               c <= pts[tree[root]].y && pts[tree[root]].y <= d;

    int ret = 0, l, r;
    if(x) l = a, r = b;
    else l = c, r = d;

    if(l <= split[root]) ret += kd_query(2*root + 1, a, b, c, d, !x);
    if(split[root] <= r) ret += kd_query(2*root + 2, a, b, c, d, !x);

    return ret;
}

pt kd_neighbor(int root, pt a, bool x) {
    if(tree[root] != -1)
        return a == pts[tree[root]] ? pt(2e9, 2e9) : pts[tree[root]];

    TYPE num = x ? a.x : a.y;
    int term = num <= split[root] ? 1 : 2;
    pt ret;

    TYPE d = norm(a - (ret = kd_neighbor(2*root + term, a, !x)));
    if((split[root] - num)*(split[root] - num) < d) {
        pt ret2 = kd_neighbor(2*root + 3 - term, a, !x);
        if(norm(a - ret2) < d)
            ret = ret2;
    }

    return ret;
}
