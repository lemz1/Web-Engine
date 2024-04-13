#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

template<class T>
using Vector = std::vector<T>;

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Quat = glm::quat;
using Mat4 = glm::mat4;

template<class T>
using Scoped = std::unique_ptr<T>;

template<class T, class... Args>
Scoped<T> MakeScoped(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<class T>
using Ref = std::shared_ptr<T>;

template<class T, class... Args>
Ref<T> MakeRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

