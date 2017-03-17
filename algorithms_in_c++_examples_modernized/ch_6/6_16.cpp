link listselection(link h)
{
    node dummy(0);
    link head = &dummy, out = 0;
    head->next = h;
    while (head->next != 0) {
        link max = findmax(head), t = max->next;
        max->next = t->next;
        t->next = out;
        out = t;
    }
    return out;
}

