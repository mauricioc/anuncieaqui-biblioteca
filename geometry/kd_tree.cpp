int tree[4*MAXSZ];
vector<pt> pts;

void kd_recurse(int root, int left, int right, bool x) {
    if(left == right) {
	tree[root] = left;
	return;
    }

    int mid = (right-left)/2 + 1;
    nth_element(pts.begin() + left, pts.begin() + mid, 
		pts.begin() + right, x ? compx : compy);

    kd_recurse(2*root+1, left, mid, !x);
    kd_recurse(2*root+2, mid+1, right, !x);
}

void kd_build() {
    memset(tree, -1, sizeof tree);
    kd_recurse(0, 0, pts.size() - 1, true);
}

