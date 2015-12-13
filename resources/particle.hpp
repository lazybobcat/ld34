#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

struct Particle
{
    enum Type
    {
        Default,
        Trail,
        ParticleCount
    };

    sf::Vector2f    position;
    sf::Color       color;
    sf::Time        lifetime;
    float           direction;
};

#endif // PARTICLE_H
