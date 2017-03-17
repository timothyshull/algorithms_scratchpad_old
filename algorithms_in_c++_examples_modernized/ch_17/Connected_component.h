#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

template<class Graph>
class Connected_component {
private:
    // implementation-dependent code
public:
    Connected_component(const Graph&);

    int count();

    bool connect(int, int);
};

#endif //CONNECTED_COMPONENT_H
