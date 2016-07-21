#ifndef REMOVEFROM_HPP
#define REMOVEFROM_HPP

#include "graphics/effect.hpp"

namespace graphics {
namespace effect {

template <class T>
class RemoveFrom final : public Effect
{
  public:

    RemoveFrom(const std::shared_ptr<sf::Transformable>& target, const sf::Time& duration, T* container)
      : Effect {target, duration}
      , _container {container}
    {
      // We can't allow infinit duration in this case (would mean we remove the target an infinit amount of time from its container)
      preventZeroDuration();
    }

  private:

    void applyUpdate(sf::Int32 /*elapsed_ms*/)
    {
      if(isFinished() && _container)
        _container->erase(std::remove(_container->begin(), _container->end(), _target), _container->end());
    }

  private:

    T* _container;
};

}
}

#endif // REMOVEFROM_HPP
