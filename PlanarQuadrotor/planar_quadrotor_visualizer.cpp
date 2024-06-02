#include "planar_quadrotor_visualizer.h"


PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = state[0] + 640; // <---* D
    q_y = state[1] + 360; // <---* D
    q_theta = state[2];

    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xC8, 0x00, 0xFF);

    // <---* D
    SDL_Rect bodyRect;
    bodyRect.x = q_x - 50; 
    bodyRect.y = q_y - 5;  
    bodyRect.w = 100;      
    bodyRect.h = 10;
    // <---* D
    // <---* D
    SDL_RenderFillRect(gRenderer.get(), &bodyRect);
    SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(gRenderer.get(), q_x + 38, q_y -15, q_x + 52, q_y - 15);
    SDL_RenderDrawLine(gRenderer.get(), q_x + 45, q_y - 15, q_x + 45, q_y - 5);
    SDL_RenderDrawLine(gRenderer.get(), q_x - 38, q_y - 15, q_x - 52, q_y - 15);
    SDL_RenderDrawLine(gRenderer.get(), q_x - 45, q_y - 15, q_x - 45, q_y - 5);
    // <---* D
}