#ifndef EXAM_PLAYER_H
#define EXAM_PLAYER_H

#include <SDL_mixer.h>
#include "GameObject.h"
#include "Movable.h"
#include "EntityAnimator.h"
#include <thread>
#include <future>




class Player : public Movable {
public:
    Player(SDL_Texture *texturePtr, int x, int y, int id, int movementSpeed) :
            Movable(texturePtr, x, y, id, movementSpeed) {
        movementChange.x = 0;
        movementChange.y = 0;
    }

    void reset() override;

    void update() override;
    void die();

    Direction m_direction = UP;

    EntityAnimator m_animator = EntityAnimator({{UP,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-up.png",
                                                                "../resources/img/pacman/large-open-up.png",
                                                                "../resources/img/pacman/medium-open-up.png"
                                                        }
                                                },
                                                {DOWN,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-down.png",
                                                                "../resources/img/pacman/large-open-down.png",
                                                                "../resources/img/pacman/medium-open-down.png"
                                                        }
                                                },
                                                {LEFT,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-left.png",
                                                                "../resources/img/pacman/large-open-left.png",
                                                                "../resources/img/pacman/medium-open-left.png"
                                                        }
                                                },
                                                {RIGHT,
                                                        {
                                                                "../resources/img/pacman/base.png",
                                                                "../resources/img/pacman/medium-open-right.png",
                                                                "../resources/img/pacman/large-open-right.png",
                                                                "../resources/img/pacman/medium-open-right.png"
                                                        }
                                                }});

    EntityAnimator deathAnimator = EntityAnimator({{UP,
                                                           {
                                                                   "../resources/img/pacman/pacman_death_1.png",
                                                                   "../resources/img/pacman/pacman_death_2.png",
                                                                   "../resources/img/pacman/pacman_death_3.png",
                                                                   "../resources/img/pacman/pacman_death_4.png",
                                                                   "../resources/img/pacman/pacman_death_5.png",
                                                                   "../resources/img/pacman/pacman_death_6.png",
                                                                   "../resources/img/pacman/pacman_death_7.png",
                                                                   "../resources/img/pacman/pacman_death_8.png",
                                                                   "../resources/img/pacman/pacman_death_9.png"
                                                           }
                                                   }
                                                  });
private:
    SDL_Point movementChange;


    void updateDirection();

    SDL_Point updateMovementDirection();

    bool willCollideWithWall(SDL_Rect& possiblePosition);

    SDL_Rect moveOneFrame(SDL_Point potentialChange);
};


#endif
