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

    
    q_x = (state[0]*1000 + 640); 
    q_y = (state[1]*1000 + 360); 
    q_theta = state[2];

    int szerok = 100;
    int wysok = 50;

    SDL_Rect bodyRect;
    bodyRect.x = q_x - 50;
    bodyRect.y = q_y - 5;
    bodyRect.w = 100;
    bodyRect.h = 10;

    SDL_Texture* quadTexture = SDL_CreateTexture(gRenderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, szerok, wysok);

    SDL_Point rotationCenter = { static_cast<int>(q_x), static_cast<int>(q_y) };
    
    SDL_SetRenderTarget(gRenderer.get(), quadTexture);
    
    SDL_SetRenderDrawColor(gRenderer.get(), 255, 165, 0, 255);

    SDL_RenderClear(gRenderer.get());
    
    SDL_SetRenderTarget(gRenderer.get(), nullptr);

    SDL_RenderCopyEx(gRenderer.get(), quadTexture, nullptr, &bodyRect, q_theta * 10, &rotationCenter, SDL_FLIP_NONE);

}