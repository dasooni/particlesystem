#include <particlesystem/ParticleSystem.h>

constexpr ParticleSystem::ParticleSystem(const size_t& numParticles): particles(numParticles)
    {}

ParticleSystem::ParticleSystem(std::unique_ptr<Emitter>&& emitter
    ,const size_t& num_particles, const glm::vec2& position): particles(num_particles)
    ,emitterPosition(position) { 
    addEmitter(std::move(emitter), position);
}

// Need to acess particle life and numparticles
// to decide emitter rate.
void ParticleSystem::draw(rendering::Window& window) {
    std::vector<glm::vec2> positions(particles.size());
    std::vector<float> mass(particles.size());
    std::vector<glm::vec4> colors(particles.size());

    for (auto& emitter: emitters) {
        window.drawPoint(emitterPosition, 20.0f
            ,glm::vec4(1.0f, 0.98f, 0.98f, 0.5f));
        
        for (size_t i = 0; i < particles.size()/emitter->getLife(); ++i) {
            emitter->generateParticles(particles[i], emitterPosition);
            positions.push_back(particles[i].position);
            mass.push_back(particles[i].mass);
            colors.push_back(particles[i].color);
        }
    }
    window.drawPoints(positions, mass, colors);
}

void ParticleSystem::update(const float& dt) { 
    for (auto& particle: particles) {
        particle.life -= dt;
        if (particle.life <= 0.0f) {
            continue;
        }
        
        glm::vec2 acceleration{};
        for (auto& effect : effects) {
            acceleration += effect->applyEffect
            (particle) / particle.mass;
        }
        particle.velocity += acceleration * (dt);
		particle.position += particle.velocity * (dt);
	} 
}

void ParticleSystem::addEmitter(std::unique_ptr<Emitter>&& em
    ,glm::vec2 position) {
    
    setEmitterPosition(position);
    std::cout << typeid(*em).name() << " called" << std::endl;
    emitters.emplace_back(std::move(em));
}

void ParticleSystem::addEffect(std::unique_ptr<Effect>&& effect) { 
    effects.emplace_back(std::move(effect)); 
}

size_t ParticleSystem::getNumberOfParticles() const { 
    return particles.size(); 
}

void ParticleSystem::setNumberOfParticles(const size_t& num_particles) {
    particles.resize(num_particles); 
}

void ParticleSystem::setEmitterPosition(const glm::vec2& position) {
    emitterPosition = position; 
}

void ParticleSystem::removeEmitter(std::unique_ptr<Emitter>&& emitter) { 
    emitter.release();
}
void ParticleSystem::removeEffect(std::unique_ptr<Effect>&& effect) {

    auto it = std::find_if(effects.begin(), effects.end(),
        [&](auto& e) { 
            return typeid(*e) == typeid(*effect); 
        });

    if (it != effects.end()) {
        effects.erase(it);
    }
}
