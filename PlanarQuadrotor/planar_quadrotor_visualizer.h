#pragma once

#include <memory>

#include <SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>

#include "planar_quadrotor.h"

class PlanarQuadrotorVisualizer {
private:
    PlanarQuadrotor *quadrotor_ptr;

    bool movement = false;
    int goal_x = 0;
    int goal_y = 0;

    float cur_x = 0;
    float cur_y = 0;
    float cur_ang = 0;
public:
    PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr);

    int frame = 0;
    int frame_0 = 0;

    void setMovement(bool move) { movement = move; }
    bool getMovement() const { return movement; }

    void set_x(float x) { goal_x = x; }
    float get_x() const { return goal_x; }

    void set_y(float y) { goal_y = y; }
    float get_y() const { return goal_y; }

    void set_xc(float x) { cur_x = x; }
    float get_xc() const { return cur_x; }

    void set_yc(float y) { cur_y = y; }
    float get_yc() const { return cur_y; }

    void set_ac(float a) { cur_ang = a; }
    float get_ac() const { return cur_ang; }

    void render(std::shared_ptr<SDL_Renderer> &gRenderer);
};