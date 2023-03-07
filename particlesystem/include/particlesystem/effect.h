// File: effect.h
// Defines the rules that dictate the forces acting upon particles.
// a = F/m. m scalar constant, a is calculated using F. 
// This class defines the (F) part of the equation. Supports two forces:
// GravityWell: force that pulls particles towards a point.
// Wind: force that pushes particle in the positive x direction.
#pragma once
#include <vector>
#include <glm/glm.hpp>

#include <particlesystem/particle.h>
class Effect {
public:
    virtual glm::vec2 applyEffect(Particle& particle) = 0;
    Effect() = default;
    virtual ~Effect() = default;
};

// GravityWell: force that pulls particles towards a point.
class GravityWell : public Effect {
 public:
     
    using Effect::Effect;
    GravityWell(glm::vec2 position, float mass, float G)
         :wellPosition(position), mass(mass), G(G) {
    
    }
    
    glm::vec2 applyEffect(Particle& particle) override { 
        const glm::vec2 attractionDirection = wellPosition - particle.position;
        const float attractionDistance = glm::length(attractionDirection);
        
        const glm::vec2 strength = (G * mass * attractionDirection) 
            /(std::powf(attractionDistance, 2.0f));

        return glm::normalize(attractionDirection) * strength;
    } 

private:
    glm::vec2 wellPosition{0.5f, 0.5f};
    float mass{100.0f};
    float G{0.1f};
};

//Wind: force that pushes particle in the positive x direction.
class Wind : public Effect {
public:
    using Effect::Effect;
    Wind(glm::vec2 position, glm::vec2 strength): windPos(position), windStrength(strength) {}
    glm::vec2 applyEffect(Particle& particle) override {
        if (glm::length(particle.position - windPos) < 0.1f) {
            particle.velocity += windStrength;
        }
        return windStrength;
    }

private:
    glm::vec2 windPos{0.0f, 0.0f};
    glm::vec2 windStrength{0.05f, 0.0f};
};

