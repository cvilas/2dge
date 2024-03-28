#include "ecs/ecs.hpp"

namespace game {

void System::addEntity(Entity entity) {
  entities_.push_back(entity);
}

void System::removeEntity(Entity entity) {
  std::erase_if(entities_, [&entity](const auto& e) { return entity.id() == e.id(); });
}

auto System::entities() const -> const std::vector<Entity>& {
  return entities_;
}
auto System::components() const -> const Signature& {
  return components_;
}

}  // namespace game