#include <cstring>
#include <utility>

int cap[MAXE], cost[MAXE], flow[MAXE], adj[MAXE];
int pot[MAXV];

void bg_init()
{
    d_init();
    memset(pot, 0, sizeof pot);
}

void bg_aresta(int v, int w, int capacity, int cost)
{
    cap[nedges] = capacity;
    flow[nedges] = 0;
    cost[nedges] = cost;
    d_aresta(v, w, cost);

    cap[nedges] = 0;
    flow[nedges] = 0;
    cost[nedges] = -cost;
    d_aresta(v, w, 0);
}

inline int rev(int i) { return i ^ 1; }
inline int from(int i) { return adj[rev(i)]; }

pair<int, int> busacker_gowen(int src, int sink, int num_nodes = MAXV)
{
    int retFlow = 0, retCost = 0;

    dijkstra(src, num_nodes);
    for(int i = 0; i < MAXE; i++)
        weight[i] = cost[i];

    while(dist[src] < 0x3f3f3f3f)
    {
        int cur = sink;
        while(cur != src) {
            flow[ek_prev[cur]] -= capres[sink];
            flow[rev(ek_prev[cur])] += capres[sink];
            retCost += cost[rev(ek_prev[cur])] * capres[sink];
            cur = adj[ek_prev[cur]];
        }
        ret += capres[sink];

        for(int i = 0; i < MAXE; i++)
            weight[i] = weight[i] - (pot[from(i)] - pot[adj[i]])
                                  + (dist[from(i)] - dist[adj[i]]);

        memcpy(pot, dist, sizeof pot);
        dijsktra(src, num_nodes);
    }
    return make_pair(retFlow, retCost);
}

