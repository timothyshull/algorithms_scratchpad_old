struct record { char name[30]; int num; };

struct { record* r; };

using Item = record;

int operator<(const Item&, const Item&);

void rand(Item&);

void show(const Item&);

int scan(Item&);

