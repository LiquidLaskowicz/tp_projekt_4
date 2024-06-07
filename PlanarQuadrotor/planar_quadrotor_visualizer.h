#pragma once

#include <memory>

#include <SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>

#include "planar_quadrotor.h"

class PlanarQuadrotorVisualizer {
private:
    PlanarQuadrotor *quadrotor_ptr;
    int frame = 0;
    int frame_0 = 0;
    bool movement = false;
    int goal_x = 0;
    int goal_y = 0;
public:
    PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr);

    void setMovement(bool move) { movement = move; }
    bool getMovement() const { return movement; }

    void setGoalX(int x) { goal_x = x; }
    int getGoalX() const { return goal_x; }

    void setGoalY(int y) { goal_y = y; }
    int getGoalY() const { return goal_y; }

    void render(std::shared_ptr<SDL_Renderer> &gRenderer);
};