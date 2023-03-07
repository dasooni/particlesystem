// File: particle.h
// Defines the properties of a particle.
#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct Particle {
    float mass{}, life{};

    glm::vec2 position{}, velocity{};
    glm::vec4 color{};

    // Make sure that the constructor(s) is evaluted 
    // at compile time
    constexpr Particle() = default;
    constexpr Particle(float mass, float life
       ,glm::vec2 position, glm::vec2 velocity
       ,glm::vec4 color): mass(mass), life(life)
       ,position(position), velocity(velocity)
       ,color(color) {}
};