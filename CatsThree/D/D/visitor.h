#include <unordered_map>
#include <memory>

template<class Vertex>
class BfsVisitor {
public:
    BfsVisitor() :
        container(new Container<Vertex>()) { }

    void ExamineVertex(const Vertex& vertex)
    {
        container->currentVertex = vertex;
    }

    void DiscoverVertex(const Vertex& vertex)
    {
        if (container->currentVertex == -1)
        {
            container->distance[vertex] = 0;
            container->parent[vertex] = vertex;
        } else {
            container->distance[vertex] = container->distance[container->currentVertex] + 1;
            container->parent[vertex] = container->currentVertex;
        }
    }

    size_t DistanceTo(const Vertex& target) const
    {
        return container->distance[target];
    }
    Vertex Parent(const Vertex& vertex) const
    {
        return container->parent[vertex];
    }

private:
    template<class Ver>
    class Container {
    public:
        std::unordered_map<Ver, size_t> distance;
        std::unordered_map<Ver, Ver> parent;
        Ver currentVertex = -1;
    };
    std::shared_ptr<Container<Vertex>> container;
};