#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>

class GameDatabase
{
 public:
    GameDatabase() = default;

    /// ��������� � ���� ������ � ������ [name] � �������� [x, y]
    /// ���� ������ � ����� id � ���� ��� ����, �������� ��� �����
    void Insert(ObjectId id, string name, size_t x, size_t y) {
        if (objects_container.find(id) != objects_container.end()) {
            obj_sorted_by_name[objects_container[id].name].erase(id);
            obj_sorted_by_pos[{objects_container[id].x, objects_container[id].y}].erase(id);
        }
        obj_sorted_by_name[name].insert(id);
        obj_sorted_by_pos[{x, y}].insert(id);
        objects_container[id] = { id, name, x, y };
    }

    /// ������� ������� �� id
    /// ���� ������ �������� ���, ������ �� ������
    void Remove(ObjectId id) {
        if (objects_container.find(id) != objects_container.end()) {
            obj_sorted_by_name[objects_container[id].name].erase(id);
            obj_sorted_by_pos[{ objects_container[id].x,
                objects_container[id].y }].erase(id);
            objects_container.erase(id);
        }
    }

    /// ���������� ������ �������� c ������ [name]
    /// ���������� �� �������� id
    vector<GameObject> DataByName(string name) {
        std::vector<GameObject> require;
        if (obj_sorted_by_name.find(name) != obj_sorted_by_name.end()) {
            for (auto iter = obj_sorted_by_name[name].begin();
                iter != obj_sorted_by_name[name].end(); iter++) {
                require.push_back(objects_container[*iter]);
            }
        }
        return require;
    }

    /// ���������� ������ ��������, ����������� � ������� [x, y]
    /// ���������� �� �������� id
    vector<GameObject> DataByPosition(size_t x, size_t y) {
        std::vector<GameObject> require;
        if (obj_sorted_by_pos.find({ x, y }) != obj_sorted_by_pos.end()) {
            for (auto iter = obj_sorted_by_pos[{ x, y }].begin();
                iter != obj_sorted_by_pos[{ x, y }].end(); iter++) {
                require.push_back(objects_container[*iter]);
            }
        }
        return require;
    }

    /// ���������� ������ ���� �������� �� ����
    /// ���������� �� �������� id
    vector<GameObject> Data() const {
        std::vector<GameObject> require;
        for (auto iter = objects_container.begin();
            iter != objects_container.end(); iter++) {
            require.push_back(iter->second);
        }
        return require;
    }

 protected:
    struct byIdDecrease {
        bool operator()(const ObjectId& lhs,
            const ObjectId& rhs) const {
            return lhs > rhs;
        }
    };
    std::map<ObjectId, GameObject, byIdDecrease> objects_container;
    std::map<std::string, std::set<ObjectId, byIdDecrease>> obj_sorted_by_name;
    std::map<std::pair<size_t, size_t>, std::set<ObjectId,
        byIdDecrease>> obj_sorted_by_pos;
};
