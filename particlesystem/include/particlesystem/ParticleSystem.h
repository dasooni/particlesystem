// Define a system of particles with a set of emitters and effects.
// Takes care of rendering, updating, adding particles, emitters and effects.
// TODO: divide render and update into two seperate classes.
#pragma once

#include <rendering/window.h>
#include <particlesystem/emitter.h>
#include <particlesystem/effect.h>
class ParticleSystem {
private:
    std::vector<Particle> particles;
    glm::vec2 emitterPosition{0.0f, 0.0f};

    std::vector<std::unique_ptr<Effect>> effects;
    std::vector<std::unique_ptr<Emitter>> emitters;
    
public:
    // construct a particlesystem object with a set number of particles.
    constexpr ParticleSystem(const size_t& num_particles);
    // construct a particlesystem object with a set number of particles and an emitter.
    ParticleSystem(std::unique_ptr<Emitter>&& emitter, const size_t& num_particles,
           const glm::vec2& position);
    ~ParticleSystem() = default;

    // draw particles using emitter and window.
    void draw(rendering::Window& window);

    // update particles using euler integration with forces (ef).
    void update(const float& dt);
        
    // function to add emitters and effects to the system.
    void addEmitter(std::unique_ptr<Emitter>&& emitter
        ,glm::vec2 position);
    void addEffect(std::unique_ptr<Effect>&& effect);
    
    // getters
    size_t getNumberOfParticles() const;
    
    //setters
    void setNumberOfParticles(const size_t& num_particles);
    void setEmitterPosition(const glm::vec2& position);
    
    //deleters
    void removeEmitter(std::unique_ptr<Emitter>&& emitter);
    void removeEffect(std::unique_ptr<Effect>&& effect);
    
};
