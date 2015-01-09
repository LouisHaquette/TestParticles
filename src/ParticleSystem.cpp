//includes
#include "ParticleSystem.h"

//ctr1
ParticleSystem::ParticleSystem(unsigned int count) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(3)),
    m_OldLifetime(m_lifetime),
    m_speed(70),
    m_color(255, 255, 255),
    m_emitter(0, 0)
    {
    }

//ctr2
ParticleSystem::ParticleSystem(unsigned int count, unsigned int lifetime, unsigned int speed, sf::Color color) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(lifetime)),
    m_OldLifetime(m_lifetime),
    m_speed(speed),
    m_color(color),
    m_emitter(0, 0)
    {
    }

//ctr3
ParticleSystem::ParticleSystem(unsigned int count, unsigned int lifetime, unsigned int speed, sf::Color color, sf::Vector2f position) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(lifetime)),
    m_OldLifetime(m_lifetime),
    m_speed(speed),
    m_color(color),
    m_emitter(position)
    {
    }


void ParticleSystem::setLifetime(int lifetime)
{
    m_lifetime = sf::seconds(lifetime);
}

int ParticleSystem::getLifetimeS() const
{
    return int(m_lifetime.asSeconds());
}


void ParticleSystem::setSpeed(int speed)
{
    m_speed = speed;
}

int ParticleSystem::getSpeed() const
{
    return m_speed;
}


void ParticleSystem::setColor(sf::Color color)
{
    m_color = color;
}

void ParticleSystem::changeColor()
{
    for (unsigned int i(0); i < m_particles.size(); ++i)
    {
        m_vertices[i].color = m_color;
    }
}

sf::Color ParticleSystem::getColor() const
{
    return m_color;
}


void ParticleSystem::setEmitter(sf::Vector2f position)
{
    m_emitter = position;
}

sf::Vector2f ParticleSystem::getEmitter() const
{
    return m_emitter;
}


void ParticleSystem::resetAllParticles()
{
    for (unsigned int i(0); i < m_particles.size(); ++i)
    {
        resetParticle(i);
    }
}


void ParticleSystem::update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        //update the vertex lifetime
        Particle& p = m_particles[i];
        p.lifetime -= elapsed;

        //vertex kill
        if (p.lifetime <= sf::Time::Zero)
        {
            resetParticle(i);
        }

        //update the vertex position
        m_vertices[i].position += p.velocity * elapsed.asSeconds();

        //update the alpha vertex by his lifetime
        float ratio = p.lifetime.asSeconds() / p.OldLifetime.asSeconds();
        m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = NULL;

    target.draw(m_vertices, states);
}


void ParticleSystem::resetParticle(std::size_t index)
{
    //set random speed and lifetime
    float angle = (std::rand() % 360) * 3.14159f / 180.f;
    float speed = (std::rand() % m_speed) + m_speed;

    m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

    m_particles[index].lifetime = sf::milliseconds((std::rand() % int(round(m_lifetime.asMilliseconds() * 0.66)))
    + round(m_lifetime.asMilliseconds() * 0.33));

    m_particles[index].OldLifetime = m_lifetime;
    m_vertices[index].color = m_color;

    //reset the vertex position
    m_vertices[index].position = m_emitter;
}

