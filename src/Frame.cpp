#include "Frame.h"
#include "MemoryFree.h"

Frame::Frame()
{
    this->ds = new DataStore1();
    this->reset();
}

Frame::~Frame()
{
}

const uint16_t Frame::size()
{
    return (getRows() * getCols() * getLayers());
}

uint16_t Frame::get(int led)
{
    return this->ds->get(led);
}

void Frame::set(int led, uint8_t red, uint8_t green, uint8_t blue)
{
    this->ds->set(led, red, green, blue);
}

void Frame::set(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue)
{
    this->ds->set(x, y, z, red, green, blue);
}

void Frame::setAllOn()
{
    if(!this->isPrepare()) {
        this->setPrepare();
    }
    this->ds->setAllOn(false);
}

void Frame::setAllOff()
{
    if(!this->isPrepare()) {
        this->setPrepare();
    }
    this->ds->setAllOff(false);
}

const uint8_t Frame::getRows()
{
    return this->ds->getRows();
}

const uint8_t Frame::getCols()
{
    return this->ds->getCols();
}

const uint8_t Frame::getLayers()
{
    return this->ds->getLayers();
}

const String Frame::getState()
{
    switch (this->state)
    {
        case Idle:
            return "Idle";
        case Prepare:
            return "Prepare";
        case Activate:
            return "Activate";
        case Active:
            return "Active";
        default:
            return "Invalid";
    }
}

void Frame::reset()
{
    if(isActivate() || isPrepare() || this->lifetime > 0) { return; }

    this->ds->setAllOff(true);
    this->lifetime = 0;
    this->state = Idle;
}

const bool Frame::isIdle()
{
    return (this->lifetime == 0) && (this->state == Idle);
}

const bool Frame::canPrepare()
{
    return this->isIdle() || (this->isActive() && !this->ds->changed());
}

const bool Frame::isPrepare()
{
    return (this->dirtyLifetime == 0) && (this->state == Prepare);
}

const bool Frame::isActivate()
{
    return (this->dirtyLifetime > 0) && (this->state == Activate);
}

const bool Frame::isActive()
{
    return this->lifetime > 0; //&& (this->state == Active);
}

void Frame::setPrepare()
{
    if(canPrepare()) {
        this->state = Prepare;
    }
    if(FRAME_DEBUG_MODE > 0) {
        Serial.print("[Fame::setPrepare] State::");
        Serial.println(getState());
    }
}

void Frame::activate(long lifetime)
{
    if(isPrepare()) {
        this->dirtyLifetime = lifetime;
        this->state = Activate;
    }

    if(FRAME_DEBUG_MODE > 0) {
        Serial.print("[Fame::activate] State::");
        Serial.print(getState());
        Serial.print(", ");
        Serial.println(this->dirtyLifetime);
    }
}

void Frame::decrementLifeCycle()
{
    if(this->state == Idle) {
        if(FRAME_DEBUG_MODE > 0) {
            Serial.println("[Frame::decrement] State::Idle");
        }
        return;
    }

    if(this->state != Prepare) {
        this->lifetime -= 1;

        if(FRAME_DEBUG_MODE > 0) {
            Serial.print("[Frame::decrement] decrement lifetime ");
            Serial.println(this->lifetime);
        }

        if(this->lifetime <= 0 && !this->ds->changed()) {
            if(FRAME_DEBUG_MODE > 0) {
                Serial.println("[Frame::decrement] reset datasource");
            }
            // stop interrupt timer
            //TCCR1B &= ~(1 << CS22);
            reset();
            // restart interrupt timer
            //TCCR1B = B00001011;
        }
    }

    if(this->state == Activate && this->lifetime <= 0) {
        if(FRAME_DEBUG_MODE > 0) {
            Serial.println("[Frame::decrement] synchronize datasource state");
        }
        // stop interrupt timer
        TCCR1B &= ~(1 << CS22);
        
        this->lifetime = this->dirtyLifetime;
        this->ds->synchronize();
        this->state = Active;
        this->dirtyLifetime = 0;
        if(FRAME_DEBUG_MODE > 0) {
            Serial.print("[Frame::decrement] activate with lifetime ");
            Serial.println(this->lifetime);
        }
        // restart interrupt timer
        TCCR1B = B00001011;
    }

    if(FRAME_DEBUG_MODE > 0) {
        Serial.print("[Frame::decrement] State::");
        Serial.println(getState());
    }
}

void Frame::shiftLayerForTick(const int layerIndex, const int tick)
{
    switch (FRAME_DEBUG_MODE)
    {
    case 2:
        this->ds->shiftLayerForTickToSerial(layerIndex, tick);
    default:
        this->ds->shiftLayerForTick(layerIndex, tick);
        break;
    }
}