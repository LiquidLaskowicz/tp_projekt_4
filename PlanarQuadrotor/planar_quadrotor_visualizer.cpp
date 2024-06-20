#include "planar_quadrotor_visualizer.h"


PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */

 //<--
int move_side(int f, int f0)
{
    int z = 0;

    if ((f0 % 20) < 10) z = f0 % 20;
    else z = 20 - (f0 % 20);

    return z;
}
//<--

void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    //<--
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

    SDL_Rect rightLine;
    rightLine.x = q_x + 40;
    rightLine.y = q_y - 10;
    rightLine.w = 2;
    rightLine.h = 10;

    SDL_Rect leftLine;
    leftLine.x = q_x - 40;
    leftLine.y = q_y - 10;
    leftLine.w = 2;
    leftLine.h = 10;

    SDL_Rect rightProp;
    rightProp.x = q_x - 50 + move_side(frame, frame_0);
    rightProp.y = q_y - 10;
    rightProp.w = 10;
    rightProp.h = 2;

    SDL_Rect leftProp;
    leftProp.x = q_x + 40 - move_side(frame, frame_0);
    leftProp.y = q_y - 10;
    leftProp.w = 10;
    leftProp.h = 2;



    SDL_Texture* quadTexture = SDL_CreateTexture(gRenderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, szerok, wysok);

    SDL_Point rotationCenter = { static_cast<int>(q_x), static_cast<int>(q_y) };
    
    SDL_SetRenderTarget(gRenderer.get(), quadTexture);
    
    SDL_SetRenderDrawColor(gRenderer.get(), 255, 165, 0, 255);

    SDL_RenderClear(gRenderer.get());
    
    SDL_SetRenderTarget(gRenderer.get(), nullptr);

    SDL_RenderCopyEx(gRenderer.get(), quadTexture, nullptr, &bodyRect, q_theta * 8, &rotationCenter, SDL_FLIP_NONE);

    SDL_RenderCopyEx(gRenderer.get(), quadTexture, nullptr, &leftLine, q_theta * 8, &rotationCenter, SDL_FLIP_NONE);

    SDL_RenderCopyEx(gRenderer.get(), quadTexture, nullptr, &rightLine, q_theta * 8, &rotationCenter, SDL_FLIP_NONE);

    SDL_SetRenderTarget(gRenderer.get(), quadTexture);

    SDL_SetRenderDrawColor(gRenderer.get(), 0, 0, 0, 255);

    SDL_RenderClear(gRenderer.get());

    SDL_SetRenderTarget(gRenderer.get(), nullptr);

    SDL_RenderCopyEx(gRenderer.get(), quadTexture, nullptr, &leftProp, q_theta * 8, &rotationCenter, SDL_FLIP_NONE);

    SDL_RenderCopyEx(gRenderer.get(), quadTexture, nullptr, &rightProp, q_theta * 8, &rotationCenter, SDL_FLIP_NONE);

    SDL_DestroyTexture(quadTexture);

    ++frame;
    
    if (getMovement())
    {
        filledCircleColor(gRenderer.get(), get_x(), get_y(), 5, 0xFF0000FF);
    }

    if (q_x >= (get_x() - 5) && q_x <= (get_x() + 5) && q_y >= (get_y() - 5) && q_y <= (get_y() + 5)) setMovement(false);

    if (frame % 100 == 0) frame_0 += 1;

    if (frame == 200) frame = 0;
    if (frame_0 == 200) frame_0 = 0;

    set_xc(q_x);
    set_yc(q_y);
    set_ac(q_theta);

    //<--
}