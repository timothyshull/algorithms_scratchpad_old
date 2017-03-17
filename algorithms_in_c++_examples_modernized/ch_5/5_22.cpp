void traverse(int k, void visit(int))
{
    QUEUE<int> q(V* V);
    q.put(k);
    while (!q.empty()) {
        if (visited[k = q.get()] == 0) {
            visit(k);
            visited[k] = 1;
            for (link t = adj[k]; t != 0; t = t->next) {
                if (visited[t->v] == 0) { q.put(t->v); }
            }
        }
    }
}

