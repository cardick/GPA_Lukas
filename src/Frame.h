#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Frame_h
#define Frame_h

// #include <avr/pgmspace.h>
#include "DataStore.h"

enum FrameState
{
    Idle = 0b0 << 0,
    Prepare = 0b1 << 0,
    Activate = 0b11 << 0,
    Active = 0b111 << 0,
    Invalid = 0b1000 << 0
};

class Frame
{
public:
    Frame();

    ~Frame();

    inline const uint16_t size() const;

    Voxel voxel(uint16_t index) const;

    uint16_t get(uint16_t index) const;

    void set(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

    void set(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue);

    int getIndex(uint8_t x, uint8_t y, uint8_t z);

    void setAllOn();

    void setAllOff();

    const uint8_t getRows() const;

    const uint8_t getCols() const;

    const uint8_t getLayers() const;

    void reset();

    const bool isIdle();

    const bool canPrepare();

    const bool isPrepare();

    const bool isActivate();

    const bool isActive();

    void setPrepare();

    /// @brief Activates currently prepared state of the LEDs for an amount
    /// of time. Since time is measured in FPS the lifetime is in amount of
    /// repeated frames.
    /// @param lifetime number of frame repeats (or duty cycles)
    void activate(uint16_t lifetime);

    void decrementLifeCycle();

    void shiftLayerForTick(const uint8_t layerIndex, const uint8_t tick);

protected:
private:
    DataStore ds;
    FrameState state;
    uint16_t dirtyLifetime;
    uint16_t lifetime;
};

#endif
