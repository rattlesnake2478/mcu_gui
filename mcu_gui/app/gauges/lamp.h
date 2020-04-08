#ifndef LAMP_H
#define LAMP_H

#include "gauge.h"
#include "../components/lamps.h"

namespace McuGui {



class Lamp: public AbstractGauge<bool> {
public:
    enum Type {
       SQARE = 1,
    };

    const Dimension StandartDimension = {40, 40};

    Lamp(const Mask& glyph,
         Type type = Type::SQARE,
         Color active_color = COLOR_RED,
         Color active_glyph_color = COLOR_WHITE,
         Color inactive_color = COLOR_TRANSPARENT,
         Color inactive_glyph_color = COLOR_WHITE):
        glyph_(glyph),
        type_(type),
        active_color_(active_color),
        active_glyph_color_(active_glyph_color),
        inactive_color_(inactive_color),
        inactive_glyph_color_(inactive_glyph_color)
    { setValue(false); };

    virtual void paint(PainterInterface& painter) const override;

protected:
    const Mask& glyph_;
    Type type_;
    Color active_color_;
    Color active_glyph_color_;
    Color inactive_color_;
    Color inactive_glyph_color_;
};

// Lamp predefined
class LeftTurnLamp:  public Lamp { public: LeftTurnLamp(Type type = Type::SQARE): Lamp(LEFT_TURN_GLYPH, type, COLOR_YELLOW, COLOR_BLACK) {}};
class RightTurnLamp: public Lamp { public: RightTurnLamp(Type type = Type::SQARE): Lamp(RIGHT_TURN_GLYPH, type, COLOR_YELLOW, COLOR_BLACK) {}};
class BatteryLamp:   public Lamp { public: BatteryLamp(Type type = Type::SQARE): Lamp(BATTERY_GLYPH, type, COLOR_RED, COLOR_WHITE) {}};
class NeutralLamp:   public Lamp { public: NeutralLamp(Type type = Type::SQARE): Lamp(NEUTRAL_GLYPH, type, COLOR_GREEN, COLOR_WHITE) {}};
class HighBeamLamp:  public Lamp { public: HighBeamLamp(Type type = Type::SQARE): Lamp(HIGH_BEAM_GLYPH, type, COLOR_BLUE, COLOR_WHITE) {}};
class GpsLamp:       public Lamp { public: GpsLamp(Type type = Type::SQARE): Lamp(GPS_GLYPH, type, COLOR_TRANSPARENT, COLOR_WHITE, COLOR_TRANSPARENT, COLOR_TRANSPARENT) {}};
class TempLamp:      public Lamp { public: TempLamp(Type type = Type::SQARE): Lamp(TEMP_GLYPH, type) {}};

} // end namespace McuGui


#endif // LAMP_H
