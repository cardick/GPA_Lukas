#include "Frame.h"

#include <avr/pgmspace.h>
#include "DataStore.h"
#include "MemoryFree.h"

Frame::Frame() : ds(new DataStore()), state(Idle), dirtyLifetime(0), lifetime(0)
{
    ds->setAllOff(true);
}

Frame::~Frame()
{
    delete ds;
}

const uint16_t Frame::size() const
{
    return (getRows() * getCols() * getLayers());
}

Voxel Frame::voxel(uint16_t index) const
{
    return ds->getVoxel(index);
}

uint16_t Frame::get(uint16_t index) const
{
    return ds->get(index);
}

void Frame::set(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    ds->set(index, red, green, blue);
}

void Frame::set(uint8_t x, uint8_t y, uint8_t z, uint8_t red, uint8_t green, uint8_t blue)
{
    ds->set(x, y, z, red, green, blue);
}

int Frame::getIndex(uint8_t x, uint8_t y, uint8_t z)
{
    return ds->getIndex(x, y, z);
}

void Frame::setAllOn()
{
    if (!isPrepare())
    {
        setPrepare();
    }
    ds->setAllOn(false);
}

void Frame::setAllOff()
{
    if (!isPrepare())
    {
        setPrepare();
    }
    ds->setAllOff(false);
}

const uint8_t Frame::getRows() const
{
    return ds->getRows();
}

const uint8_t Frame::getCols() const
{
    return ds->getCols();
}

const uint8_t Frame::getLayers() const
{
    return ds->getLayers();
}

const String Frame::getState() const
{
    char buffer[10];
    switch (state)
    {
        case Idle:
            strcpy_P(buffer, (char *)pgm_read_word(&(frame_states[0])));
            break;
        case Prepare:
            strcpy_P(buffer, (char *)pgm_read_word(&(frame_states[1])));
            break;
        case Activate:
            strcpy_P(buffer, (char *)pgm_read_word(&(frame_states[2])));
            break;
        case Active:
            strcpy_P(buffer, (char *)pgm_read_word(&(frame_states[3])));
            break;
        default:
            strcpy_P(buffer, (char *)pgm_read_word(&(frame_states[4])));
            break;
    }
    
    return String(buffer);
}

void Frame::reset()
{
    if (isActivate() || isPrepare() || lifetime > 0)
    {
        return;
    }

    lifetime = 0;
    state = Idle;
}

const bool Frame::isIdle()
{
    return lifetime == 0 && state == Idle;
}

const bool Frame::canPrepare()
{
    return isIdle() || (isActive() && !ds->changed());
}

const bool Frame::isPrepare()
{
    return state == Prepare; //(dirtyLifetime == 0) && (state == Prepare);
}

const bool Frame::isActivate()
{
    return dirtyLifetime > 0 && state == Activate;
}

const bool Frame::isActive()
{
    return lifetime > 0 && state == Active;
}

void Frame::setPrepare()
{
    if (canPrepare())
    {
        state = Prepare;
    }
}

void Frame::activate(uint16_t lifetime)
{
    if (isPrepare())
    {
        dirtyLifetime = lifetime;
        state = Activate;
    }
    else
    {
        Serial.println(F("[Frame] Cannot activate, not prepared."));
    }
}

void Frame::decrementLifeCycle()
{
    if (state == Idle)
    {
        return;
    }

    if (state != Prepare)
    {
        if (lifetime > 0)
        {
            lifetime -= 1;
        }

        if (lifetime <= 0 && !ds->changed())
        {
            reset();
        }
    }

    if (state == Activate && lifetime <= 0)
    {
#ifdef UNO_R3
        // stop interrupt timer
        TCCR1B &= ~(1 << CS22);
#elif defined(UNO_WIFI_R2)
#else
#error "Undefined target platform. Pleas select a correct target platform from platformio.ini."
#endif

        lifetime = dirtyLifetime;
        ds->synchronize();
        state = Active;
        dirtyLifetime = 0;
#ifdef UNO_R3
        // restart interrupt timer
        TCCR1B = B00001011;
#elif defined(UNO_WIFI_R2)
#else
#error "Undefined target platform. Pleas select a correct target platform from platformio.ini."
#endif
    }
}

void Frame::shiftLayerForTick(const uint8_t layerIndex, const uint8_t tick)
{
    if (ds != nullptr)
    {
        ds->shiftLayerForTick(layerIndex, tick);
    }
    else
    {
        Serial.println(F("[Frame] error: data store is nullptr."));
    }
}