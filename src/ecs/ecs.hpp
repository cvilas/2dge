#pragma once
#include <bitset>
#include <vector>

namespace game {
static constexpr auto MAX_COMPONENTS = 32U;

// - Keeps track of which components and entity has
// - Keeps tracke of which entities a system is interested in
using Signature = std::bitset<MAX_COMPONENTS>;

struct IComponent {
protected:
  static int next_type_id_;
};

// Pure data. Does not implement logic
template <typename T>
class Component : public IComponent {
  static auto typeId() -> int {  // unique id per component type
    static auto type_id = next_type_id_++;
    return type_id;
  }
};

class Entity {
public:
  explicit Entity(int id) : id_(id) {
  }
  [[nodiscard]] auto id() const -> int {
    return id_;
  }

private:
  int id_;
};

/// Transforms state of components of related kind
class System {
public:
  void addEntity(Entity entity);
  void removeEntity(Entity entity);
  auto entities() const -> const std::vector<Entity>&;
  auto components() const -> const Signature&;

  template <typename TComponent>
  void requireComponent() {
    components_.set(TComponent::typeId());
  }

private:
  Signature components_;
  std::vector<Entity> entities_;
};

class IComponentPool {
public:
  virtual ~IComponentPool() = default;
};

template <typename T>
struct ComponentPool : public IComponentPool {
  std::vector<T> data;
};

// Manages creation and destruction of entities, components and systems
class Registry {
public:
  void createEntity();
  void destroyEntity();
  void addSystem();
  void addComponent();
  void removeComponent();

private:
  int num_entities_{ 0 };

  // each pool contains components of a certain type and within a pool, indices are organised by
  // entity id. so vector index is component type id and pool index is entity id
  std::vector<IComponentPool*> component_pools;
};

}  // namespace game