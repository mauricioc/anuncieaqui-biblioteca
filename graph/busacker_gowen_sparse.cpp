#include <iostream>
#include <cstring>
#include <queue>

int dist[MAXV], last_edge[MAXV], d_visited[MAXV], bg_prev[MAXV], pot[MAXV], capres[MAXV];
int prev_edge[MAXE], adj[MAXE], cap[MAXE], cost[MAXE], flow[MAXE];

int nedges;
std::priority_queue<std::pair<int, int> > d_q;

inline void bg_aresta_aux(int v, int w, int capacity, int cst)
{
    prev_edge[nedges] = last_edge[v];

    adj[nedges] = w;
    cap[nedges] = capacity;
    flow[nedges] = 0;
    cost[nedges] = cst;

    last_edge[v] = nedges++;
}

inline void bg_aresta(int v, int w, int capacity, int cost)
{
    bg_aresta_aux(v, w, capacity, cost);
    bg_aresta_aux(w, v, 0, -cost);
}

inline int rev(int i) { return i ^ 1; }
inline int from(int i) { return adj[rev(i)]; }

inline void bg_init()
{
    nedges = 0;
    memset(last_edge, -1, sizeof last_edge);
    memset(pot, 0, sizeof pot);
}

void dijkstra(int s, int num_nodes = MAXV)
{
    memset(dist, 0x3f, sizeof dist);
    memset(d_visited, 0, sizeof d_visited);
    d_q.push(std::make_pair(dist[s] = 0, s));
    capres[s] = 0x3f3f3f3f;

    while(!d_q.empty()) {
        int v = d_q.top().second; d_q.pop();
        if(d_visited[v]) continue; d_visited[v] = true;

        for(int i = last_edge[v]; i != -1; i = prev_edge[i]) {
            if(cap[i] - flow[i] == 0) continue;
            int w = adj[i], new_dist = dist[v] + cost[i] + pot[v] - pot[w];
            assert(cost[i] + pot[v] - pot[w] >= 0);

            if(new_dist < dist[w])
            {
                d_q.push(std::make_pair(-(dist[w] = new_dist), w));
                bg_prev[w] = rev(i);
                capres[w] = min(capres[v], cap[i] - flow[i]);
            }
        }
    }
}

std::pair<int, int> busacker_gowen(int src, int sink, int num_nodes = MAXV)
{
    int retFlow = 0, retCost = 0;

    dijkstra(src, num_nodes);
    while(dist[sink] < 0x3f3f3f3f)
    {
        int cur = sink;
        while(cur != src) {
            flow[bg_prev[cur]] -= capres[sink];
            flow[rev(bg_prev[cur])] += capres[sink];
            retCost += cost[rev(bg_prev[cur])] * capres[sink];
            cur = adj[bg_prev[cur]];
        }
        retFlow += capres[sink];

        for(int i = 0; i < MAXV; i++)
            pot[i] = min(pot[i] + dist[i], 0x3f3f3f3f);

        dijkstra(src, num_nodes);
    }
    return std::make_pair(retFlow, retCost);
}

