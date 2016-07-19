#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "models/mapblock.hpp"

namespace model {

class Player final : public MapBlock
{
  public:

    Player(const std::string& name, const sf::Vector2f& position);

    void update(const sf::Time& elapsed_time);

    /*! Player being hit by a block
     *  First remove shield, then life.
     */
    void hit(int value);

    /*! Gain life
     *  \returns true if life has been updated (not already maxed)
     */
    bool gainLife(int value);

    /*! Gain shield
     *  \returns true if shield has been updated (not already maxed)
     */
    bool gainShield(int value);

    void gainScore(int value) { _score += value; }

    bool isDead() const { return _health <= 0; }

    const std::string& getName() const { return _name; }
    int getHealth() const { return _health; }
    int getShield() const { return _shield; }
    int getMaxHealth() const { return _max_health; }
    int getMaxShield() const { return _max_shield; }
    int getScore() const { return _score; }

  private:

    std::string _name;
    int _health;
    int _shield {0};
    int _score {0};

    unsigned int _last_score_update {0};

    static const int _max_health {100};
    static const int _max_shield {100};
    static const unsigned int _base_size {30};
    static const unsigned int _update_score_step {1000}; // in milliseconds
};

}

#endif // PLAYER_HPP
