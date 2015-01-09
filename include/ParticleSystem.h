#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

//preprocessor directives & includes
#include <SFML/Graphics.hpp>
#include <cmath>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{

public:

    //ctr1
    /**
    * \brief constructor 1 of ParticlesSystem
    * \param unsigned int count (nomber of vertex)
    * \return nothing
    */
    ParticleSystem(unsigned int count);

    //ctr2
    /**
    * \brief constructor 2 of ParticlesSystem
    * \param unsigned int count (nomber of vertex), unsigned int lifetime (vertices lifetime),
    * unsigned int speed (vertices speed), sf::Color color (vertices color)
    * \return
    */
    ParticleSystem(unsigned int count, unsigned int lifetime, unsigned int speed, sf::Color color);

    //ctr3
    /**
    * \brief constructor 3 of ParticlesSystem
    * \param unsigned int count (nomber of vertex), unsigned int lifetime (vertices lifetime),
    * unsigned int speed (vertices speed), sf::Color color (vertices color), sf::Vector2f position (vertices emetteur position)
    * \return
    */
    ParticleSystem(unsigned int count, unsigned int lifetime, unsigned int speed, sf::Color color, sf::Vector2f position);


    /**
    * \brief setLifetime
    * \param int lifetime
    * \return void
    */
    void setLifetime(int lifetime);

    /**
    * \brief getLifetime(S) const
    * \param no param
    * \return unsigned int m_getLifetime in seconds
    */
    int getLifetimeS() const;


    /**
    * \brief setSpeed
    * \param int speed
    * \return void
    */
    void setSpeed(int speed);

    /**
    * \brief getSpeed const
    * \param no param
    * \return unsigned int m_speed
    */
    int getSpeed() const;


    /**
    * \brief setColor
    * \param sf::Color color (SFML)
    * \return void
    */
    void setColor(sf::Color color);

    /**
    * \brief changeColor of all vertices (update the color (SFML) in real time)
    * \param no param
    * \return void
    */
    void changeColor();

    /**
    * \brief getColor const
    * \param no param
    * \return sf::Color m_color (SFML)
    */
    sf::Color getColor() const;


    /**
    * \brief setEmitter of vertices (the position)
    * \param sf::Vector2f position (SFML)
    * \return void
    */
    void setEmitter(sf::Vector2f position);

    /**
    * \brief getEmitter const
    * \param no param
    * \return sf::Vector2f m_emitter (SFML)
    */
    sf::Vector2f getEmitter() const;


    /**
    * \brief resetAllParticles (color, position, lifetime, velocity (speed)) (SFML)
    * \param no param
    * \return void
    */
    void resetAllParticles();


    /**
    * \brief update the lifetime, position, velocity of vertices by the elapsed time (SFML)
    * \param sf::Time elapsed (SFML)
    * \return void
    */
    void update(sf::Time elapsed);

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
        sf::Time OldLifetime;
    };

    /**
    * \brief (virtual) draw the vertices with RenderStates const (SFML)
    * \param sf::RenderTarget& target, sf::RenderStates states (SFML)
    * \return void
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
    * \brief resetParticle (vertex) who is dead (over lifetime) (SFML)
    * \param std::size_t index of vertex in the VertexArray
    * \return void
    */
    void resetParticle(std::size_t index);

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Time m_OldLifetime;
    unsigned int m_speed;
    sf::Color m_color;
    sf::Vector2f m_emitter;
};

#endif // PARTICLESYSTEM_H
