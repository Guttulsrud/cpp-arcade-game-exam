#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Ghost.h"
#include "../include/Pellet.h"
#include "../include/InputManager.h"

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <fstream>

SDL_Renderer *Game::renderer = nullptr;

int Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
            // Error message if can't initialize
        }

        Mix_AllocateChannels(8);

        if (window) {
        }

        renderer = SDL_CreateRenderer(window, -1, flags);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        if (TTF_Init() == 0) {
            std::cout << "TTF init" << std::endl;
        }

        std::cout << "Game running" << std::endl;
        isRunning = true;

    }
    return 0;
}

void removeEatenPellets(std::vector<std::shared_ptr<StationaryObject>> &objects) {

    objects.erase(
            std::remove_if(objects.begin(), objects.end(),
                           [](const std::shared_ptr<StationaryObject> &pellet) {
                               return pellet->getType() == PELLET && dynamic_cast<Pellet *>(pellet.get())->eaten;
                           }),
            objects.end());
}

void Game::update() {
    std::vector<std::shared_ptr<MovableObject>> &movables = Game::getMovableGameObjects();
    std::vector<std::shared_ptr<StationaryObject>> &stationary = Game::getStationaryGameObjects();

    std::shared_ptr<Player> &player = Game::getPlayer();

    player->update();

    for (auto const &m : movables) {
        m->update();
    }

    for (auto const &s : stationary) {
        if (s->getType() == PELLET) {

        }
    }



    //count pellets. if none, load next map

    removeEatenPellets(Game::getStationaryGameObjects());
}

void Game::render() {
    std::vector<std::shared_ptr<MovableObject>> &movables = Game::getMovableGameObjects();
    std::vector<std::shared_ptr<StationaryObject>> &stationary = Game::getStationaryGameObjects();
    std::shared_ptr<Player> &player = Game::getPlayer();

    for (auto const &m :movables) {
        m->render();
    }
    for (auto const &s : stationary) {
        s->render();
    }

    if (getPlayer()->newHighScore > getPlayer()->highScore) {
        drawText("Highscore: %d", 35, 0, getPlayer()->newHighScore);
    } else {
        drawText("Highscore: %d", 35, 0, getPlayer()->highScore);
    }
    drawText("Points: %d", 400, 0, getPlayer()->points);
    drawText("Lives: %d", 775, 0, getPlayer()->lives + 1);
    player->render();
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void Game::clean() {
    TTF_Quit();
    FC_FreeFont(font);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Cleaned.." << std::endl;
}


void Game::setMap(Maps map) {
    getInstance().m_map = maps[map];
}

void Game::setPlayer(std::shared_ptr<Player> const &object) {
    getInstance().m_player = object;
}



Game::~Game() {

}

std::shared_ptr<Player> &Game::getPlayer() {
    return getInstance().m_player;
}

std::vector<std::shared_ptr<MovableObject>> &Game::getMovableGameObjects() {
    return getInstance().movableGameObjects;
}

void Game::addMovableGameObject(const std::shared_ptr<MovableObject> &object) {
    getMovableGameObjects().emplace_back(object);
}

std::vector<std::shared_ptr<StationaryObject>> &Game::getStationaryGameObjects() {
    return getInstance().stationaryGameObjects;
}

void Game::addStationaryGameObject(const std::shared_ptr<StationaryObject> &object) {
    getStationaryGameObjects().emplace_back(object);
}

void Game::setGameObjects() {

    setPlayer(std::make_shared<Player>(TextureManager::loadTexture("../resources/img/pacman/base.png"),
                                       30 * 14.5, 30 * 24, 0, 3,
                                       EntityAnimator({{UP,
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
                                                       }})

    ));



    //TODO: Draw with map class
    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/green_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/green_N1.png",
                                            "../resources/img/ghosts/green_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/green_S1.png",
                                            "../resources/img/ghosts/green_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/green_W1.png",
                                            "../resources/img/ghosts/green_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/green_E1.png",
                                            "../resources/img/ghosts/green_E2.png"
                                    }
                            }})));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/orange_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/purpleN1.png",
                                            "../resources/img/ghosts/purple_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/purple_S1.png",
                                            "../resources/img/ghosts/purple_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/purple_W1.png",
                                            "../resources/img/ghosts/purple_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/purple_E1.png",
                                            "../resources/img/ghosts/purple_E2.png"
                                    }
                            }})));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/red_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/red_N1.png",
                                            "../resources/img/ghosts/red_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/red_S1.png",
                                            "../resources/img/ghosts/red_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/red_W1.png",
                                            "../resources/img/ghosts/red_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/red_E1.png",
                                            "../resources/img/ghosts/red_E2.png"
                                    }
                            }})));

    addMovableGameObject(std::make_shared<Ghost>(
            TextureManager::loadTexture("../resources/img/ghosts/purple_E1.png"),
            30 * 15, 30 * 15, 0, 3,
            EntityAnimator({{UP,
                                    {
                                            "../resources/img/ghosts/orange_N1.png",
                                            "../resources/img/ghosts/orange_N2.png"
                                    }
                            },
                            {DOWN,
                                    {
                                            "../resources/img/ghosts/orange_S1.png",
                                            "../resources/img/ghosts/orange_S2.png"
                                    }
                            },
                            {LEFT,
                                    {
                                            "../resources/img/ghosts/orange_W1.png",
                                            "../resources/img/ghosts/orange_W2.png"
                                    }
                            },
                            {RIGHT,
                                    {
                                            "../resources/img/ghosts/orange_E1.png",
                                            "../resources/img/ghosts/orange_E2.png"
                                    }
                            }})));



    Game::getInstance().maps[LEVEL_ONE] = std::make_shared<Map>("../resources/maps/level_one.txt");
//    Game::getInstance().maps[LEVEL_TWO] = std::make_shared<Map>("../resources/maps/level_two.txt");
}

void Game::resetRound() {
    getPlayer()->reset();

    for (auto const &ghost : getMovableGameObjects()) {
        ghost->reset();
    }
    initFonts();
    render();
    getPlayer()->playSound(TEST, 5);
    while (Mix_Playing(5)) {}

}

void Game::gameOver() {

    if (getPlayer()->points > getPlayer()->highScore) {
        getPlayer()->writeHighScore(getPlayer()->points);
    }
    getPlayer()->points = 0;

    initFont(40);
    drawText("Press space to play again", 150, 500);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    InputManager IM = InputManager::getInstance();

    while (!IM.KeyDown(SDL_SCANCODE_SPACE)) {
        IM.update();
    }

    //getMap(1)->redrawPelletsOnMap();
    getPlayer()->lives = 3;
    resetRound();
}


void Game::startGame() {
    initFonts();
    setGameObjects();
    setMap(LEVEL_ONE);
    render();
    resetRound();
}


void Game::initFonts() {
    initFont(42);
    drawText("Ready!", 375, 545);
    initFont(24);
}


void Game::drawText(const char *text, float x, float y, int parameter) {
    FC_Draw(font, renderer, x, y, text, parameter);
}


void Game::initFont(int size) {
    font = FC_CreateFont();
    FC_LoadFont(font, renderer, "../resources/fonts/arial.ttf", size, FC_MakeColor(255, 255, 0, 255), TTF_STYLE_ITALIC);
}

