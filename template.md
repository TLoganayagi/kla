When you read a problem, ask:

“Is there ordering with dependencies?” → Topo / Kahn

“Need smallest / largest repeatedly?” → Heap / PQ

“Shortest path / minimum cost?” → Dijkstra / BFS

“State → best value?” → DP

“Explore everything?” → DFS / BFS

“Optimal path with heuristic?” → A*

1️ KAHN’S ALGORITHM (BFS Topological Sort)
 When to use

Task dependencies

“Do X only after Y”

Scheduling, pipelines, workflows

 Core idea

Remove nodes with indegree = 0

 Template
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u])
            indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);

        for (int v : adj[u]) {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }
    return topo; // size < n → cycle exists
}

2️ HEAP (MIN & MAX)
 When to use

“Get min/max repeatedly”

Scheduling, greedy, shortest path

 Min Heap
priority_queue<int, vector<int>, greater<int>> minHeap;

 Max Heap
priority_queue<int> maxHeap;

Common pattern
minHeap.push(x);
int best = minHeap.top();
minHeap.pop();

3️ TOPOLOGICAL SORT (DFS VERSION)
 When to use

Need ordering

Detect cycles

 Template
void dfs(int u, vector<vector<int>>& adj, vector<int>& vis, vector<int>& st) {
    vis[u] = 1;
    for (int v : adj[u])
        if (!vis[v])
            dfs(v, adj, vis, st);
    st.push_back(u);
}

vector<int> topoSortDFS(int n, vector<vector<int>>& adj) {
    vector<int> vis(n, 0), st;
    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(i, adj, vis, st);
    reverse(st.begin(), st.end());
    return st;
}

4️ PRIORITY QUEUE (Generic Pattern)
 When to use

Best candidate first

Greedy + optimal choice

 Template
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
// (cost, node)

pq.push({0, start});
while (!pq.empty()) {
    auto [cost, u] = pq.top(); pq.pop();
}

5️ STACK
 When to use

Undo

Expression evaluation

DFS

Matching brackets

 Template
stack<int> st;
st.push(x);
st.pop();
int top = st.top();
bool empty = st.empty();

6️ DIJKSTRA’S ALGORITHM
 When to use

Shortest path

Weighted graph

“Minimum cost / time”

 Rule

 No negative weights

 Template
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

7️ A* ALGORITHM
 When to use

Pathfinding

“Best route”

Maps, grids

 Key idea

f(n) = g(n) + h(n)

 Template (Grid)
struct Node {
    int x, y, g, f;
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

priority_queue<Node, vector<Node>, greater<Node>> pq;


Heuristic (example):

int h(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

8️ DYNAMIC PROGRAMMING (Universal Patterns)
 When to use

Overlapping subproblems

“Best / minimum / maximum”

Choices per step

 1D DP
vector<int> dp(n+1, 0);
dp[0] = base;

for (int i = 1; i <= n; i++) {
    dp[i] = dp[i-1] + cost[i];
}

 2D DP
vector<vector<int>> dp(n, vector<int>(m, INF));
dp[0][0] = base;

Golden rule

Define state, transition, base case

9️ BFS
 When to use

Shortest path in unweighted graph

Level-wise traversal

 Template
queue<int> q;
vector<int> dist(n, -1);

q.push(src);
dist[src] = 0;

while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == -1) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}

 DFS
 When to use

Explore everything

Connectivity

Backtracking

 Template
void dfs(int u, vector<vector<int>>& adj, vector<int>& vis) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v])
            dfs(v, adj, vis);
    }
}

 Disjoint Set (Union-Find)

Use when:

Connectivity

Grouping

“Are X and Y connected?”

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n), r(n,0) { iota(p.begin(), p.end(), 0); }

    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) {
            if (r[a] < r[b]) swap(a,b);
            p[b] = a;
            if (r[a] == r[b]) r[a]++;
        }
    }
};

 Sliding Window

Use when:

Subarray / substring

“At most / at least K”

int l = 0;
for (int r = 0; r < n; r++) {
    // expand window
    while (invalid) {
        l++;
    }
}

 Two Pointers

Use when:

Sorted arrays

Pair / interval problems

int l = 0, r = n-1;
while (l < r) {
    if (condition) l++;
    else r--;
}

 3. TIME & SPACE COMPLEXITY SENSE (INTERVIEW GOLD)

You must quickly estimate:

Input size?

Can I do O(n²)?

Do I need O(n log n)?

Can I store everything in memory?

Golden rules:

n ≤ 10⁵ → O(n log n) max

Graph dense? → adjacency matrix

Graph sparse? → adjacency list


 THE MOST IMPORTANT TABLE (REMEMBER THIS)
Problem Hint	Data Structure
Dependency	Topo / Kahn
Smallest / Largest	Heap
Shortest path	BFS / Dijkstra
Optimal path	A*
State decisions	DP
Explore all	DFS
Level order	BFS