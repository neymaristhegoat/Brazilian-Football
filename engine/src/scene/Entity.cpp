#include "scene/Entity.h"
#include "scene/Scene.h"

namespace bf {
namespace scene {

Entity::Entity(Scene* scene, uint64_t id)
    : m_Scene(scene)
    , m_ID(id)
    , m_Name("Entity")
    , m_Active(true)
{
}

Entity::~Entity() {
}

} // namespace scene
} // namespace bf
