#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef GpaAnimation_h
#define GpaAnimation_h

#include "Animation.h"
#include "Coloring.h"
#include "Voxel.h"

class GpaAnimation : public Animation
{
public:
    GpaAnimation();
    ~GpaAnimation();
    /// @brief Run the tunnel animation
    void run();

    /// @brief Run this tunnel animation
    /// @param runtime the animation runtime in millis
    /// @param coloring the coloring to use
    void run(unsigned long runtime, Coloring *coloring);

private:
    Coloring * coloring;

    /// @brief Animate a tunnel moving forward
    void moveTunnel();

    /// @brief Animate a tunnel moving backward
    void moveTunnelBack();

    /// @brief Draw animation frame front to back
    /// @param vox start voxel
    /// @param step current step
    /// @param size size of rectangle
    /// @param coloring coloring
    void drawFTB(Voxel vox, uint8_t step, uint8_t size);

    /// @brief Draw animation frame back to front
    /// @param vox start voxel
    /// @param step current step
    /// @param size size of rectangle
    /// @param coloring the coloring
    void drawBTF(Voxel vox, int8_t step, uint8_t size);
};

#endif