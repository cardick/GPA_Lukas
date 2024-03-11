#ifndef LightCube_h
#define LightCube_h

#include <Arduino.h>
#include "Frame.h"

/// @brief the digital representation of the light cube. The light cube is 
/// arranged in rows, columns and layers which are mapped to x,y and z  
/// coordinates of a cartesian coordinate system and each voxel has a unique 
/// index between 0 .. 511.
/// Rows are an y coordniate and the index can be count 0 .. 7 each row
/// Columns are on x axis and the index can be count 0 .. 56 each column stepwise by 8
/// Layers are on z axis and the index can be count 0 .. 448 each layer stepwise by 64
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
    void shiftLayerForTick(const uint8_t index, const uint8_t tick);

    /**
     * Let the cube prepare for the next duty cycle.
     */
    void prepareNextDutyCycle();

    bool isInitialized();
    
private:
    float frameRate;
    Frame *frame;
    bool initialized;

    LightCube();

    LightCube(const LightCube &) = delete;
    LightCube &operator=(const LightCube &) = delete;

};

#endif
