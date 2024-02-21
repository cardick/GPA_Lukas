#ifndef LightCube_h
#define LightCube_h

#include <Arduino.h>
#include "Frame.h"

struct LED {
    public: 
        LED(uint8_t px, uint8_t py, uint8_t pz, uint8_t red, uint8_t green, uint8_t blue)
        {
            this->px = px;
            this->py = py;
            this->pz = pz;
            this->red = red;
            this->green = green;
            this->blue = blue;
            this->setIndex();
        }

        const uint8_t getX() { return this->px; }
        const uint8_t getY() { return this->py; }
        const uint8_t getZ() { return this->pz; }
        const uint8_t getRed() { return this->red; }
        const uint8_t getGreen() { return this->green; }
        const uint8_t getBlue() { return this->blue; }
        const uint8_t getIndex() { return this->index; }

        String toString() {
            String tmp = "LED [Index ";
            tmp += index;
            tmp += ", Point (";
            tmp += px;
            tmp += ", ";
            tmp += py;
            tmp += ", ";
            tmp += pz;
            tmp += "), Color(";
            tmp += red;
            tmp += ", ";
            tmp += green;
            tmp += ", ";
            tmp += blue;
            tmp += ")]";
            return tmp;
        }

    private: 
        uint8_t px;
        uint8_t py;
        uint8_t pz;
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint16_t index;

        void setIndex() {
            if(px >= COLS) { index = -1; return; }
            if(py >= ROWS) { index = -1; return; };
            if(pz >= LAYERS) { index = -1; return; };

            int ledNumber = ((pz == 0) ? 0 : (pz - 1) * (ROWS * COLS));
            ledNumber += (py == 0 ? 0 : (py - 1) * ROWS);
            ledNumber += px;
            index = ledNumber;
        }
};

class LightCube {

    public:
        /// @brief Get the instance of the LightCube class. 
        /// @return the instance
        static LightCube& getInstance();

        /// @brief Initialize the cube. Should be called only once during lifecycle of the cube.
        /// @param frameRate currantly set frame rate
        void init(float frameRate);

        uint8_t getRowSize();

        uint8_t getColSize();

        uint8_t getLayerSize();

        Frame* getFrame();

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

    protected:
    
    private:
        float frameRate;
        Frame * frame;
        bool initialized;

        LightCube();

        LightCube(const LightCube&) = delete;
        LightCube& operator=(const LightCube&) = delete;

        bool isInitialized();

        // /**
        //  * Transfer the prepared transfer byte to SPI and prepare for the next transfer byte.
        //  * 
        //  * @param shift current shift position
        //  * @param transferByte current state of the transfer byte
        //  */
        // void shiftToSPI(int *shift, uint8_t *transferByte);
    };

#endif
