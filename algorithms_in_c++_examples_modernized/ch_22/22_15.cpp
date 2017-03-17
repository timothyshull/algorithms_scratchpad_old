int old = 0;

for (

valid = 1;

valid !=

old;

)
{
old = valid;

for (

int v = 0;

v<G.

V();

++v)
{
typename Graph::adjIterator A(G, v);

for (

Edge* e = A.beg();

!A.

end();

e = A.nxt()

)
if (e->

capRto(e

->

other(v)

) > 0)
if (e->

capRto(v)

== 0)
{
update(augment(e), e

); ++

valid;

}
}
}