#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <memory>

#include <SFML/Graphics.hpp>

namespace graphics {

class Effect
{
  public:

    /*! Constructor
     *  \param target   - target to apply the effect.
     *  \param duration - duration of the effect. 0 means infinite.
     */
    Effect(const std::shared_ptr<sf::Transformable>& target, const sf::Time& duration);

    void update(const sf::Time& elapsed_time);

    bool isFinished() const;

  protected:

    virtual void applyUpdate(sf::Int32 elapsed_ms) = 0;

    /*! Helper method to call to prevent given duration to be equal to 0 (usefull for some effects) */
    void preventZeroDuration();

  protected:

    std::shared_ptr<sf::Transformable> _target;
    sf::Time _duration;
    bool _infinite;
};

}

#endif // EFFECT_HPP
