#ifdef ARDUINO
#include <Arduino.h>
#endif

#include "Voxel.h"

#ifndef DataStore_h
#define DataStore_h

#define ROWS 8
#define COLS 8
#define LAYERS 8
#define BAM 4

#define BYTES (((ROWS*COLS*3) / 8) + ((ROWS*COLS*3) % 8 > 0 ? 1 : 0))

#define LAYER_1 0b00000001
#define LAYER_2 0b00000010
#define LAYER_3 0b00000100
#define LAYER_4 0b00001000
#define LAYER_5 0b00010000
#define LAYER_6 0b00100000
#define LAYER_7 0b01000000
#define LAYER_8 0b10000000

#define ALL_ON 0b11111111
#define ALL_OFF 0b00000000

/// @brief Data store holds the two states of the cube. The active state that 
/// is shifted out and a modyfication state to prepare the next active state 
/// of the cube.
class DataStore {
    public:
        DataStore();

        /// @brief Get the size of the rows.
        /// @return 
        const int getRows();

        /// @brief Get the size of the columns.
        /// @return 
        const int getCols();

        /// @brief Get the size of layers.
        /// @return 
        const int getLayers();

        /// @brief Make the complete cube on.
        /// @param force Force the changes to be directly synchronized with active state
        void setAllOn(bool force);

        /// @brief Make the complete cube off.
        /// @param force Force the changes to be directly synchronized with active state
        void setAllOff(bool force);

        /// @brief Get the active state of a voxel.
        /// @param index index of the voxel in the cube. A value between 0 .. (ROWS * COLS * LAYERS) - 1
        /// @return the 12-Bit rgb value in MSBFT order (4-Bit for each color) 
        uint16_t get(uint16_t index) const;

        /// @brief Get the active state of voxel with given coordinates
        /// @param x X-Axis coordinate (column in cube). A value between 0 and COLS-1.
        /// @param y Y-Axis coordinate (row in cube). A value between 0 and ROWS-1.
        /// @param z Z-Axis coordinate (layer in cube). A value between 0 and LAYERS-1.
        /// @return the 12-Bit RGB value in MSBFT order (4-Bit for each color) 
        uint16_t get(uint8_t x, uint8_t y, uint8_t z) const;

        /// @brief Set the 4-Bit RGB values for a voxel. 
        /// @param index the index of the voxel in the cube. A value between 0 .. (ROWS * COLS * LAYERS) -1 
        /// @param red 4-Bit BAM value for the red cathode.
        /// @param green 4-Bit BAM value for the green cathode.
        /// @param blue 4-Bit BAM value for the blue cathode.
        void set(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

        /// @brief Set the 4-Bit RGB values for a voxel with the given coordinates in the cube.
        /// @param x X-Axis coordinate (row in cube). A value between 0 and ROWS-1.
        /// @param y Y-Axis coordinate (column in cube). A value between 0 and COLS-1.
        /// @param z Z-Axis coordinate (layer in cube). A value between 0 and LAYERS-1.
        /// @param red 4-Bit BAM value for the red cathode.
        /// @param green 4-Bit BAM value for the green cathode.
        /// @param blue 4-Bit BAM value for the blue cathode.
        void set(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue);

        /// @brief Get the voxel at position from the displayed frame. 
        /// @param index the index [0 .. 511] 
        /// @return the voxel
        Voxel getVoxel(int index) const;

        /// @brief Evaluate the index of the voxel with the given coordinates in the cube.
        /// @param x X-Axis coordinate (row in cube). A value between 0 and ROWS-1.
        /// @param y Y-Axis coordinate (column in cube). A value between 0 and COLS-1.
        /// @param z Z-Axis coordinate (layer in cube). A value between 0 and LAYERS-1.
        /// @return the index in the cube or MAX uint16_t if a coordinate is out of range.
        const uint16_t getIndex(uint8_t x, uint8_t y, uint8_t z) const;

        /// @brief Shift the active state for a layer out to SPI, when layer and tick are within their ranges.
        /// @param layerIndex value between 0 .. LAYERS
        /// @param tick value between 0 .. 15
        void shiftLayerForTick(int layerIndex, int tick);

        /// @brief Shift the active state for a layer out to Serial, when layer and tick are within their ranges.
        /// @param layerIndex value between 0 .. LAYERS
        /// @param tick value between 0 .. 15
        void shiftLayerForTickToSerial(int layerIndex, int tick);

        /// @brief Indicates whether the data store is modified and out of sync with the active state.
        /// @return true if modifications are present, that are not already in sync; false otherwise
        bool changed();

        /// @brief Synchronize current  modifications from 'dirty state' with the active state.
        void synchronize();

    protected:
    private:
        const uint8_t gammaCorrect[3] = {0b00100100, 0b10010010, 0b01001001};
        uint8_t layeredStore[LAYERS][BAM][BYTES];
        uint8_t layeredStoreDirty[LAYERS][BAM][BYTES];
        bool isDirty;

        /// @brief Get the BAM index for tick in duty cycle. 
        /// @param tick the tick count 
        /// @return the BAM index
        int getBAM(int tick);

        /// @brief Shift out an 8 Bit unsigned int value to Serial with it's leading zeros.
        /// @param value the value to shift out
        inline void shiftToSerial(uint8_t value);
};
#endif