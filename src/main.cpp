/// Control a common anode RGB LED cube or cuboid - inspired by the projects of 
/// Kevin Darrah and Tiemen Waterreus. 
///
/// The driver methods use SPI to control the shift registers. 
///
/// @see SPI Tutorial: https://core-electronics.com.au/guides/spi-arduino-tutorial/ 
/// @author Carsten Dick (carsten.dick@googlemail.com)
#include <Arduino.h>
#include <SPI.h>

// #include "avr8-stub.h"
// #include "app_api.h"

#include "LightCube.h"
#include "Coloring.h"
#include "MemoryFree.h"

// includes for animations
#include "CubeCheck.h"
#include "GpaAnimation.h"
#include "SinusAnimation.h"
#include "SnakeAnimation.h"


// PINs are the same for ATmega328P (Uno R3) and ATmega4809 (Uno wifi R2)

// must be 13 defined by SPI (SRCLK - Shift Register Clock)
#define CLOCK_PIN 13
// must be 11 defined by SPI
#define DATA_PIN 11
// RCLK (Register Clock or Latch)
#define LATCH_PIN 2
// OE - Output enable
#define BLANK_PIN 4

// The driver logic is based on rows and columns from the top view onto the cube.
// LEDs theoretical numbering on a layer is from back left to front right (columns
// from left to right; rows from back to front; layers from bottom to top).
//
// 2x2x2     4x4x4           ...
// 00 01     00 01 02 03
// 02 04     04 05 06 07
//           08 09 10 11
//           12 13 14 15
//
// The logic also assumes that this is the logic how the LEDs are connected to the
// daisy chained shift registers; each LED with the rgb pins side by side, connected
// in the pin order R-G-B (e.g. LED 00 R-G-B, LED 01 R-G-B and so on).
// Anodes are connected first in the daisy chained shift register; from 0 - n, whereas
// 0 is the anode for the bottom layer.

// the current tick in interrupt frequency - needed in ISR
uint8_t currentTick = 0;
// the layer of the cube currently shifted - needed in ISR
uint8_t currentLayer = 0;

void setup() {
  // debug_init();
  Serial.begin(115200);

  // disable interrupts
  cli();

  // initialize SPI
  SPI.begin();

  // Set LSB as bit order, this means we will send the least significant bit 
  // first and it will be written to Q7 = Register Pin 7 with the most 
  // significant bit being written last to Q0 or Pin 15

  // most significant bit first vs. least significant bit first
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  // initialize the timer interrupts to enable multiplexing and 4 Bit-BAM
  // duty cycle so the overall duty cycle is 16 ticks nedded for 4-Bit BAM 
  // and amount of layers needed for multiplexing.
  //
  // Arduino Uno R3 with ATmega 328 and Uno wifi R2 with ATmega4809 have a 
  // CPU Frequency of 16MHz
  //
  // Formula for CTC-Mode: 
  //    CPU Frequency 16MHz / Prescale / Interrupt frequency = Comparative value
  //
  // To get the target frame rate for the cube divide interrupt frequency by 
  // duty cycle.
  //
  // Comparative value for the prescaled ticks, when comparative value is 
  // reached an interrupt is triggered
  //
  // To reach 120 FPS for a 4x4x4 cube with 4-Bit BAM, the target interrupt 
  // frequency (tIF) is calculated: 
  //    tIF = 120 (target FPS) * 16 (BAM) * 4 (Layers) = 7.680
  // Therefore the comparative value has to be set to prescaled ticks divided by target
  // interrupt frequency which is then 250.000 / 7.680 = 32,55 ~ 32
  // For the 8x8x8 cube a comparative value of 30 -> ~60FPS, 19 -> ~100FPS, 16 -> ~120FPS  

#ifdef UNO_R3

  // set TCCR1A register to zero for CTC-Mode
  TCCR1A = B00000000;

  // set TCCR1B register B00001XXX for CTC-Mode
  // TCCR1B = B00001010; // Prescale 8 
  TCCR1B = B00001011; // Prescale 64
  // TCCR1B = B00001100; // Prescale 256 
  
  //Comparative value 
  OCR1A = 30;

  // TIMSK register is responsible for the usage of the timer in scope of the 
  // interrupts
  TIMSK1 = B00000010;

  float frameRate = 250000 / OCR1A / (Brightness::Full + 1) / LAYERS;

#elif defined(UNO_WIFI_R2)
  // not sure if CTRLA value is the right one and if and if the clock prescaler in CLKCTRL must be set

  // Set Prescaler to 64 (equivilant to Uno R3 setting B00001011)
  // TCB0.CTRLA |= TCB_CLKSEL_CLKDIV1_gc; // sleep mode
  TCB0.CTRLA |= TCB_CLKSEL_CLKDIV2_gc; //

  // Configure TCB in Periodic Timeout mode
  // TCB0.CTRLB = TCB_CNTMODE_TIMEOUT_gc;
  // TCB_CNTMODE_INT_gc

  // set compare value (eauivilant OCR1A at ATmega328P)
  TCB0.CCMP = 30;  

  // activate the compare-interrupt
  TCB0.INTCTRL = TCB_CAPT_bm;

  float frameRate = 250000 / TCB0.CCMP / (Brightness::Full + 1) / LAYERS;

#else
  #error "Undefined target platform. Pleas select a correct target platform from platformio.ini."
#endif

  // Configure the Arduino pins used as OUTPUT, so they can send data to the 
  // Shift Register
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(BLANK_PIN, OUTPUT);

  // setup frame rate for cube

  // initialize the cube
  LightCube::getInstance().init(frameRate);

  // allow interrupts
  sei();
}

/// @brief Within the loop only the bytes should be manipulated that are written out in ISR method
void loop() {
  Animation* animation = new CubeCheck();
  animation->run();

  // Animation* animation = new SnakeAnimation();
  // animation->run();

  // put your animation here
  // Animation* animation = new GpaAnimation();
  // for (int i = 0; i < 20; i++)
  // {
    // ((GpaAnimation*)animation)->run(120000);
  // }
  
  // Animation* animation = new SinusAnimation();
  // delay(200);
  // ((SinusAnimation*)animation)->run(0, 10000);
  // ((SinusAnimation*)animation)->run(1, 5000);
    
  // animation = new GpaAnimation();
  // animation->run();
  while (true)
  {
    /* code */
  }
  
}

/// @brief ISR is the interrupt method executed by the arduino. Multiplexing and BAM is realized here.
///
/// Tutorial 1: https://www.simsso.de/?type=arduino/timer-interrupts
/// Tutorial 2: https://electronoobs.com/eng_arduino_tut140.php 
/// https://medium.com/@tiemenwaterreus/4-bit-angle-modulating-16-leds-using-arduino-and-shift-registers-8b2b738d4ced
/// https://medium.com/@tiemenwaterreus/building-a-4x4x4-led-cube-part-ii-the-software-813a5207bca8


#ifdef UNO_R3
  ISR(TIMER1_COMPA_vect) {
#elif defined(UNO_WIFI_R2)
  ISR(TCB0_INT_vect) {
#else
  #error "Undefined target platform. Pleas select a correct target platform from platformio.ini."
#endif

  // shift current layer for current BAM tick to the shift registers
  LightCube::getInstance().shiftLayerForTick(currentLayer, currentTick);

#ifdef UNO_R3
  // set OE to high disables outputs of shift registers
  PORTD |= 1 << BLANK_PIN;

  // setting RCLK to HIGH than to LOW copies the state of the shift register clock to the register clock
  PORTD |= 1 << LATCH_PIN;
  PORTD &= ~(1 << LATCH_PIN);

  // set OE to low enables outputs of shift registers
  PORTD &= ~(1 << BLANK_PIN);

#elif defined(UNO_WIFI_R2)
  // do the equivilant for R2
#else
  #error "Undefined target platform. Pleas select a correct target platform from platformio.ini."
#endif
  
  // reset current layer to the first one, when all layers have been shifted out
  currentLayer = ((currentLayer < LightCube::getInstance().getLayerSize() - 1) ? (currentLayer + 1) : 0);

  // when all layers for this tick were shifted out repeat for next tick
  if (currentLayer == 0) {
    // prepare for next tick or restart for next duty cycle
    currentTick = currentTick < Brightness::Full ? (currentTick + 1) : 0;
    if(currentTick == 0) {
      LightCube::getInstance().prepareNextDutyCycle();
    }
  }
}