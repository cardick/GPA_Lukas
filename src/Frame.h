#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifndef Frame_h
#define Frame_h

#define FRAME_DEBUG_MODE 0

#include <avr/pgmspace.h>
#include "DataStore.h"

const char state_0[] PROGMEM = "Idle";
const char state_1[] PROGMEM = "Prepare";
const char state_2[] PROGMEM = "Activate";
const char state_3[] PROGMEM = "Active";
const char state_4[] PROGMEM = "Invalid";
const char *const frame_states[] PROGMEM = {state_0, state_1, state_2, state_3, state_4};

enum FrameState {
    Idle = 0b0 << 0,
    Prepare = 0b1 << 0,
    Activate = 0b11 << 0,
    Active = 0b111 << 0,
    Invalid = 0b1000 << 0
};

class Frame {
    public:
        Frame();

        ~Frame();

        const uint16_t size();

        Voxel voxel(int index) const;

        uint16_t get(int index) const;

        void set(int index, uint8_t red, uint8_t green, uint8_t blue);

        void set(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue);

        int getIndex(uint8_t x, uint8_t y, uint8_t z);

        void setAllOn();

        void setAllOff();

        const uint8_t getRows();

        const uint8_t getCols();

        const uint8_t getLayers();

        const String getState();

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
        void activate(long lifetime);

        void decrementLifeCycle();

        void shiftLayerForTick(const int layerIndex, const int tick);

    protected:
    
    private:
        DataStore * ds;
        FrameState state = FrameState::Idle;
        int dirtyLifetime = 0;
        int lifetime = 0;
};

#endif
