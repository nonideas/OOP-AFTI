#pragma once
#include <cstdint>
#include <unordered_map>
#include <vector>

class vertex
{
    uint64_t id_;
public:
    vertex() : id_(0) {}
    explicit vertex(const uint64_t id) : id_(id) {}
    [[nodiscard]] uint64_t get_id() const noexcept
    {
        return id_;
    }
    bool operator==(const vertex& other) const {
        return id_ == other.id_;
    }
};

template <>
struct std::hash<vertex>
{
    size_t operator()(const vertex& k) const noexcept
    {
        size_t res = 17;
        res = res * 31 + hash<uint64_t>()(k.get_id());
        return res;
    }
};

class graph final {

	std::unordered_map<vertex, std::vector<vertex>, std::hash<vertex>> graph_;
public:
    graph() = default;
    explicit graph(const std::vector<std::pair<vertex, vertex>>& v);
    void add_edge(const vertex& start_edge, const vertex& end_edge);
    [[nodiscard]] const std::vector<vertex>& adjacent_vertices(const vertex& vertex) const;
    [[nodiscard]] size_t count_of_vertices() const noexcept;
};

