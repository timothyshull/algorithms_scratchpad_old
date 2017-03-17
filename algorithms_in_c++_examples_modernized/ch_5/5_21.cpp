void traverse(int k, void visit(int))
{
    visit(k);
    visited[k] = 1;
    for (link t = adj[k]; t != 0; t = t->next) {
        if (!visited[t->v]) { traverse(t->v, visit); }
    }
}

