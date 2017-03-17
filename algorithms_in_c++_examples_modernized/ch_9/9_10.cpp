Item getmax()
{
    Item max;
    link x = head->next;
    for (link t = x; t->next != head; t = t->next) {
        if (x->item < t->item) { x = t; }
    }
    max = x->item;
    remove(x);
    return max;
}

void change(handle x, Item v) { x->key = v; }

void remove(handle x)
{
    x->next->prev = x->prev;
    x->prev->next = x->next;
    delete x;
}

void join(PQ <Item>& p)
{
    tail->prev->next = p.head->next;
    p.head->next->prev = tail->prev;
    head->prev = p.tail;
    p.tail->next = head;
    delete tail;
    delete p.head;
    tail = p.tail;
}

