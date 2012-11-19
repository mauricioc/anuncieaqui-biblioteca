struct el { int n, d; } heap[MAXV]; int where[MAXV];
int prev_edge[MAXE], weight[MAXE], adj[MAXE], dist[MAXV], last_edge[MAXV];
int nedges;

void d_init() {
    nedges = 0;
    memset(last_edge, -1, sizeof last_edge);
}

void d_edge(int v, int w, int eweight) {
    prev_edge[nedges] = last_edge[v];
    weight[nedges] = eweight;
    adj[nedges] = w;
    last_edge[v] = nedges++;
}

void d_swap(int a, int b) {
    swap(heap[a], heap[b]);
    swap(where[heap[a].n], where[heap[b].n]);
}

void decrease_key(int n, int d) {
    heap[where[n]].d = d;
    for(int cur = where[n], up; cur && d < heap[up = (cur-1)/2].d; cur = up)
        d_swap(cur, up);
}

int pop_heap(int& sz) {
    int cur = 0;
    for(int next = 2; next < sz; cur = next, next = 2*next+2) {
        if(heap[next].d > heap[next-1].d) next--;
        d_swap(next, cur);
    }
    d_swap(cur, sz-1);
    return heap[--sz].n;
}

void dijkstra(int s, int sz = MAXV) {
    for(int i = 0; i < sz; ++i)
        heap[i].n = where[i] = i, heap[i].d = dist[i] = 0x3f3f3f3f;
    decrease_key(s, dist[s] = 0);

    while(sz)
        for(int v = pop_heap(sz), i = last_edge[v]; i != -1; i = prev_edge[i]) {
            int w = adj[i];
            if(dist[v] + weight[i] < dist[w])
                decrease_key(w, dist[w] = dist[v] + weight[i]);
        }
}
