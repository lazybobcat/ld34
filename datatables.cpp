#include <datatables.hpp>
#include <resources/particle.hpp>


std::vector<ParticleData> initializeParticleData()
{
    std::vector<ParticleData> data(Particle::ParticleCount);

    data[Particle::Default].color = sf::Color(255, 255, 255);
    data[Particle::Default].lifetime = sf::seconds(1.3f);

    data[Particle::Trail].color = sf::Color(255, 255, 255, 255);
    data[Particle::Trail].lifetime = sf::seconds(0.7f);

    return data;
}

