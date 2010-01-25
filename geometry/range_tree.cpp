vector<pt> pts, tree[MAXSZ];
vector<TYPE> xs;
vector<int> lnk[MAXSZ][2];

int rt_recurse(int root, int left, int right) {
    if(left == right) {
        vector<pt>::iterator it;
        it = lower_bound(pts.begin(), pts.end(), pt(xs[left], -1e9));
        for(; it != pts.end() && it->x == xs[left]; it++)
            tree[root].push_back(*it);

        sort(tree[root].begin(), tree[root].end(), compy);
        return tree[root].size();
    }

    int mid = (left + right)/2, cl = 2*root + 1, cr = cl + 1;
    int sz1 = rt_recurse(cl, left, mid);
    int sz2 = rt_recurse(cr, mid + 1, right);

    int l = 0, r = 0, llink = 0, rlink = 0; pt last;
    while(l < sz1 || r < sz2) {
        if(r == sz2 || (l < sz1 && tree[cl][l].y <= tree[cr][r].y))
            tree[root].push_back(last = tree[cl][l++]);
        else tree[root].push_back(last = tree[cr][r++]);

        while(llink < tree[cl].size() && compy(tree[cl][llink].y, last))
            llink++;
        while(rlink < tree[cr].size() && compy(tree[cr][rlink].y, last))
            rlink++;

        lnk[root][0].push_back(llink);
        lnk[root][1].push_back(rlink);
    }

    return tree[root].size();
}

void rt_build() {
    sort(pts.begin(), pts.end());
    for(int i = 0; i < pts.size(); i++) xs.push_back(pts[i].x);
    rt_recurse(0, 0, xs.size() - 1);
}

int rt_query(int root, int l, int r, int a, int b, int c, int d,
             int posl = -1, int posr = -1) {
    if(root == 0 && pos == -1)
        pos = lower_bound(tree[0].begin(), tree[0].end(), c, compy)
            - tree[0].begin();

    int ret = 0;
    if(a <= xs[l] && xs[r] <= b) {
        while(pos < tree[root].size() && tree[root][pos].y <= d)
            ret++, pos++;
        return ret;
    }
    if(pos >= tree[root].size()) return 0;

    int mid = (l + r)/2;
    if(a <= xs[mid])
        ret += rt_query(2*root+1, l, mid, a, b, c, d, lnk[root][0][pos]);
    if(xs[mid+1] <= b)
        ret += rt_query(2*root+2, mid+1, r, a, b, c, d, lnk[root][1][pos]);

    return ret;
}
