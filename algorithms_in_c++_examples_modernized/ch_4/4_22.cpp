private:

void deletelist()
{
    for (link t = head; t != 0; head = t) {
        t = head->next;
        delete head;
    }
}

public:

QUEUE(const QUEUE& rhs)
{
    head = 0;
    *this = rhs;
}

QUEUE& operator=(const QUEUE& rhs)
{
    if (this == &rhs) { return *this; }
    deletelist();
    link t = rhs.head;
    while (t != 0) {
        put(t->item);
        t = t->next;
    }
    return *this;
}

~QUEUE() { deletelist(); }

