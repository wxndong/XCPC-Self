// url : https://oi-wiki.org/graph/save/

/*
    1 直接存储边，用于Kruskal等
*/
int n, m;
struct Edge {
    int u, v, w;
};
vector<Edge> edge;
vector<bool> vis;
edge.resize(m + 1);
vis.resize(n + 1, false);

/*
    2 邻接表
*/
vecetor<int> adj[N]  // or vector<vector<int> adj adj.resize(n + 1)


/*
    3 链式前向星 本质上是链表实现的邻接表
*/
int cnt;
int head[N];

struct Edge {
    int to, next, w;
}edge[N];

void add(int from, int to, int w) {
    edge[++ cnt].next = head[from];
    edge[cnt].to = to;
    edge[cnt].w = w;
    head[from] = cnt;
}
