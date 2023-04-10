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
        // size / life is the rate of emission.
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
            acceleration += effect->applyEffect(particle) / particle.mass;
        }
        particle.velocity += acceleration * (dt);
		particle.position += particle.velocity * (dt);
	} 
}

void ParticleSystem::addEmitter(std::unique_ptr<Emitter>&& em
    ,glm::vec2 position) {
    
    setEmitterPosition(position);
    fmt::print("[{}] {}(line {}): emitter {} added to system\n", __TIME__, __FUNCTION__, __LINE__, typeid(*em).name());
    emitters.emplace_back(std::move(em));
}

void ParticleSystem::addEffect(std::unique_ptr<Effect>&& effect) { 
    fmt::print("[{}] {}(line {}): effect {} added to system\n", __TIME__, __FUNCTION__, __LINE__, typeid(*effect).name());
    effects.emplace_back(std::move(effect)); 
}

size_t ParticleSystem::getNumberOfParticles() const { 
    fmt::print("[{}] {}(line {}): number of particles in the system is: {}\n", __TIME__, __FUNCTION__, __LINE__, particles.size());
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
            fmt::print("[{}] {}(line {}): effect {} removed from system" ,  __TIME__, __FUNCTION__, __LINE__, typeid(*effect).name());
            return typeid(*e) == typeid(*effect); 
        });

    if (it != effects.end()) {
        effects.erase(it);
    }
}
