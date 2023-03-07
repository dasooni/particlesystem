#include <tracy/Tracy.hpp>
#include <cstdlib>
#include <fmt/format.h>
#include <particlesystem/ParticleSystem.h>

int main(int, char**) try {
    rendering::Window window("Particle System v0.1.0 pre-release alpha", 1270, 900);
    /* Initialize a particle system as default */
    const size_t numParticles{200};
    auto particleSystems = std::vector<std::unique_ptr<ParticleSystem>>{};
    std::vector<glm::vec2> emitPos;
    
    auto uni = std::make_unique<Uniform>();
    auto dir = std::make_unique<Directional>();

    //emitter default position at origo
    glm::vec2 emitterPosition{0.0f, 0.0f};
    emitPos.push_back(emitterPosition);

    auto particleSystem = std::make_unique<ParticleSystem>(std::move(uni), 
        numParticles, emitterPosition);
    fmt::print("System initialized with: {} particles\n"
        ,particleSystem->getNumberOfParticles());
   
    particleSystems.emplace_back(std::move(particleSystem));
    /* */
    auto prevTime = 0.0;
    float speed = 1.0f;
    
    bool running = true;
    bool pause = false;
    // for the checkboxes
    bool gravity_on{false}, wind_on{false};
    
    // for the slider
    int min_number_of_particles{}
        ,set_number_of_particles{static_cast<int>(numParticles)}
        ,max_number_of_particles{1000};
    while (running) {
        window.beginFrame();

        const auto t = window.time();
        const auto dt = t - prevTime;
        prevTime = t;
        ZoneScopedN("Update particles"); 
        const float sim_dt{static_cast<float>(dt) * speed};
        for (size_t i = 0; i < particleSystems.size(); i++) {
            particleSystems[i]->setEmitterPosition(emitPos[i]);
            particleSystems[i]->update(sim_dt);
        }
        window.clear({0, 0, 0, 1});

        for (auto& system : particleSystems) {
            system->draw(window);
        }
        // UI
        {
            window.beginGuiWindow("UI");
            window.text("Simulation speed");
            window.sliderFloat("Speed", speed, 0.001f, 10.0f);
            
            window.sliderInt("Number of particles", set_number_of_particles,
                             min_number_of_particles, max_number_of_particles);
            for (auto& pSystem : particleSystems) {
                pSystem->setNumberOfParticles(set_number_of_particles);
            }

            window.text("Emitters");
            for (size_t i = 0; i < particleSystems.size(); i++) {
                window.sliderVec2(fmt::format("Move Emitter {}",i+1)
                    ,emitPos[i], -1.0f, 1.0f);
                particleSystems[i]->setEmitterPosition(emitPos[i]);
            }
                
            if (window.button("Emitter: uniform")) {
                gravity_on = false, wind_on = false;
                auto new_pos = glm::vec2{0.0f, 0.0f};
                auto new_uniform = std::make_unique<Uniform>();
                auto new_system = std::make_unique<ParticleSystem>
                    (std::move(new_uniform), numParticles, new_pos);

                emitPos.emplace_back(new_pos);
                particleSystems.emplace_back(std::move(new_system));
            }
            
            if (window.button("Emitter: Directional")) {
                gravity_on = false, wind_on = false;
                auto new_pos = glm::vec2{0.0f, 0.0f};
                auto new_directional = std::make_unique<Directional>();
                auto new_system = std::make_unique<ParticleSystem>
                    (std::move(new_directional), numParticles, new_pos);

                emitPos.emplace_back(new_pos);
                particleSystems.emplace_back(std::move(new_system));
            }
            
            window.text("Forces");
            if (window.checkbox("Gravity", gravity_on)) {
                for (auto& p : particleSystems) {
                    auto apply_gravity = std::make_unique<GravityWell>();
                    gravity_on ? p->addEffect(std::move(apply_gravity))
                               : p->removeEffect(std::move(apply_gravity));
                }
            }
            if (window.checkbox("Wind", wind_on)) {
                for (auto& p : particleSystems) {
                    auto apply_wind = std::make_unique<Wind>();
                    wind_on ? p->addEffect(std::move(apply_wind))
                            : p->removeEffect(std::move(apply_wind));
                }
            }
            if (window.checkbox("Pause", pause)) {
                pause ? speed = 0.0f : speed = 1.0f;
            }
            if (window.button("Close application")) {
                running = false;
            }
            window.endGuiWindow();
        }
        window.endFrame();
        running = running && !window.shouldClose();
    }
    return EXIT_SUCCESS;
} catch (const std::exception& e) {
    fmt::print("{}", e.what());
    return EXIT_FAILURE;
}
