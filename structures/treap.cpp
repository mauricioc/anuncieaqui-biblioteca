typedef int TYPE;

struct treap {
    treap *lnk[2];
    int pri, nsons;
    TYPE val;

    treap(TYPE val) : val(val), nsons(1) { pri = rand(); lnk[0] = lnk[1] = 0; }
    ~treap() { delete lnk[0]; delete lnk[1]; }
    void fix_augment() {
        nsons = 1 + (lnk[0] ? lnk[0]->nsons : 0) + (lnk[1] ? lnk[1]->nsons : 0);
    }
};

void rotate(treap*& t, bool to_r) {
    treap* n = t->lnk[!to_r];
    t->lnk[!to_r] = n->lnk[to_r];
    n->lnk[to_r] = t;
    t->fix_augment(); n->fix_augment();
    t = n;
}

treap* find(treap* t, TYPE val) {
    for(;; t = t->lnk[val > t->val]) if(!t || t->val == val) return t;
}

treap* insert(treap*& t, TYPE val) {
    if(!t) return t = new treap(val);

    treap* n = insert(t->lnk[val > t->val], val);
    if(n->pri > t->pri) rotate(t, val <= t->val); else t->fix_augment();
    return n;
}

void remove_root(treap*& t) {
    if(!t->lnk[0] && !t->lnk[1]) { delete t; t = 0; return; }

    bool to_r = t->lnk[0] && (!t->lnk[1] || t->lnk[0]->pri > t->lnk[1]->pri);
    rotate(t, to_r); remove_root(t->lnk[to_r]); t->fix_augment();
}

void remove(treap*& t, TYPE val) {
    if(!t) return;

    if(t->val != val) { remove(t->lnk[val > t->val], val); t->fix_augment(); }
    else remove_root(t);
}
