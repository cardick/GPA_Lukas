#ifndef LightCube_h
#define LightCube_h

#include <Arduino.h>
#include "Frame.h"

class LightCube
{
public:
    /// @brief Get the instance of the LightCube class.
    /// @return the instance
    static LightCube &getInstance();

    /// @brief Initialize the cube. Should be called only once during lifecycle of the cube.
    /// @param frameRate currantly set frame rate
    void init(float frameRate);

    uint8_t getRowSize();

    uint8_t getColSize();

    uint8_t getLayerSize();

    Frame *getFrame();

    const float getFrameRate();

    /// @brief Indicates whether the cube has nothing to do
    /// @return true when cube is idle; false otherwise.
    bool isIdle();

    /// @brief Indicates whether the cube can be prepared.
    /// @return true if cube is busy and cannot be prepared; false otherwise
    bool isBusy();

    /// @brief Resetting the cube turns it off.
    void reset();

    /// @brief Set the complete cube on.
    void turnOn(long millis);

    /**
     * Shift a layer of the cube to SPI for the given BAM tick.
     *
     * @param index index of the layer
     * @param tick current BAM tick
     */
    void shiftLayerForTick(const int index, const int tick);

    /**
     * Let the cube prepare for the next duty cycle.
     */
    void prepareNextDutyCycle();

private:
    float frameRate;
    Frame *frame;
    bool initialized;

    LightCube();

    LightCube(const LightCube &) = delete;
    LightCube &operator=(const LightCube &) = delete;

    bool isInitialized();
};

#endif
