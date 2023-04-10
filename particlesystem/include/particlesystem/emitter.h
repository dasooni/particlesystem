// File: emitter.h
// Emitters are used to generate particles.
// This file supports two types of emitters: uniform and directional.
// Uniform: random direction.
// Directional: specified direction.
#pragma once
#include <random>
#include <iostream>
#include <vector>
#include <numbers>

#include <glm/glm.hpp>
#include <particlesystem/particle.h>


class Emitter {
public:
    virtual void generateParticles(Particle& particle, glm::vec2& pos) = 0;
    Emitter() = default;
    virtual ~Emitter() = default;
    
    void setMass(float m) { mass = m; }
    void setLife(float l) { life = l; }
    void setVelocityX(float vX) { velocityX = vX; }
    void setVelocityY(float vY) { velocityY = vY; }
    
    float getMass() { return mass; }
    float getLife() { return life; }
    float getVelocityX() { return velocityX; }
    float getVelocityY() { return velocityY; }
    
protected:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;
    std::uniform_real_distribution<float> vel;

    float mass{10.0f};
    float life{4.0f};
    float velocityX{1.0f};
    float velocityY{1.0f};
};

// Uniform: specified point, fixed rate, random direction.
class Uniform : public Emitter {
public:
    void generateParticles(Particle& particle, glm::vec2& position) override {
       
        if (particle.life <= 0.005f) {
            gen = std::mt19937(rd());
            dis = std::uniform_real_distribution(0.0f, 1.0f);
            vel = std::uniform_real_distribution(-1.0f, 1.0f);
            
            particle.position = position;
            particle.velocity = {velocityX * vel(gen), velocityY * vel(gen)};
            particle.mass = dis(gen) * (mass + 1.0f); 
            particle.life = dis(gen) * (life + 1.0f); 
            particle.color = glm::vec4(dis(gen), dis(gen), dis(gen)
                ,std::min(particle.life, 1.0f));
        }
    }
};

// Directional: specified point, fixed rate, positive x-direction.
class Directional : public Emitter {
public:
    void generateParticles(Particle& particle, glm::vec2& position) override {
        
        if (particle.life <= 0.005f) {
            gen = std::mt19937(rd());
            dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
            vel = std::uniform_real_distribution<float>(-1.0f, 1.0f);

            particle.position = position;
            particle.velocity = {velocityX - 0.5, velocityY * dis(gen)};
            particle.mass = dis(gen) * mass + 1.0f; 
            particle.life = dis(gen) * life + 1.0f; 
            particle.color = glm::vec4(dis(gen), dis(gen)
                ,dis(gen), std::min(particle.life, 1.0f));
        }
    }
};

// Explosion: specified point, high rate, random direction
class Explosion : public Emitter {
public:
    void generateParticles(Particle& p, glm::vec2& pos) override {
        velocityX = 1.0f;
        velocityY = 1.0f;
        constexpr double pi{std::numbers::pi};
        if (p.life <= 0.005f) {
            gen = std::mt19937(rd());
            dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
            vel = std::uniform_real_distribution<float>(0.0f, 360.0f);

		    p.position = pos;

		    p.velocity = {0.2f * dis(gen) * std::sinf(vel(gen))
                ,0.2f * dis(gen) * std::cosf(vel(gen))};
		    p.mass = dis(gen) * mass + 1.0f;
            p.life = dis(gen)*10.0f * life + 1.0f;
		    p.color = glm::vec4(dis(gen), dis(gen)
                					,dis(gen), std::min(p.life, 1.0f));
			
			
        }
    }
};

