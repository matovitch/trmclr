#ifndef __TRMCLR_H__
#define __TRMCLR_H__

#include <cstdint>
#include <ostream>
#include <sstream>
#include <limits>
#include <string>

namespace trmclr
{

struct Style
{
    Style(uint32_t value) : _value(value) {}

    operator uint32_t() const { return _value; }

    uint32_t _value;
};

enum StyleTypes
{
    FOREGROUND,
    ATTRIBUTE,
    BACKGROUND,
    N_STYLE_TYPES
};

static const uint32_t STYLE_SHIFT =  std::numeric_limits<uint32_t>::digits / N_STYLE_TYPES;

struct Foreground : Style
{
    static const uint32_t SHIFT = STYLE_SHIFT * FOREGROUND;

    enum
    {
        BLACK           = 30 << SHIFT,
        RED             = 31 << SHIFT,
        GREEN           = 32 << SHIFT,
        YELLOW          = 33 << SHIFT,
        BLUE            = 34 << SHIFT,
        MAGENTA         = 35 << SHIFT,
        CYAN            = 36 << SHIFT,
        LIGHT_GRAY      = 37 << SHIFT,
        DEFAULT         = 39 << SHIFT,
        DARK_GRAY       = 90 << SHIFT,
        LIGHT_RED       = 91 << SHIFT,
        LIGHT_GREEN     = 92 << SHIFT,
        LIGHT_YELLOW    = 93 << SHIFT,
        LIGHT_BLUE      = 94 << SHIFT,
        LIGHT_MAGENTA   = 95 << SHIFT,
        LIGHT_CYAN      = 96 << SHIFT,
        WHITE           = 97 << SHIFT
    };
};

struct Background : Style
{
    static const uint32_t SHIFT = STYLE_SHIFT * BACKGROUND;

    enum
    {
        BLACK           =  40 << SHIFT,
        RED             =  41 << SHIFT,
        GREEN           =  42 << SHIFT,
        YELLOW          =  43 << SHIFT,
        BLUE            =  44 << SHIFT,
        MAGENTA         =  45 << SHIFT,
        CYAN            =  46 << SHIFT,
        LIGHT_GRAY      =  47 << SHIFT,
        DEFAULT         =  49 << SHIFT,
        DARK_GRAY       = 100 << SHIFT,
        LIGHT_RED       = 101 << SHIFT,
        LIGHT_GREEN     = 102 << SHIFT,
        LIGHT_YELLOW    = 103 << SHIFT,
        LIGHT_BLUE      = 104 << SHIFT,
        LIGHT_MAGENTA   = 105 << SHIFT,
        LIGHT_CYAN      = 106 << SHIFT,
        WHITE           = 107 << SHIFT
    };
};

struct Attribute : Style
{
    static const uint32_t SHIFT = STYLE_SHIFT * ATTRIBUTE;

    enum 
    {
        DEFAULT     = 0b1           << SHIFT,
        BOLD        = 0b10          << SHIFT,
        DIM         = 0b100         << SHIFT,
        UNDERLINED  = 0b10000       << SHIFT,
        BLINK       = 0b100000      << SHIFT,
        REVERSE     = 0b10000000    << SHIFT,
        HIDDEN      = 0b100000000   << SHIFT
    };

    static void toStream(std::ostream& os, uint32_t attribute)
    {
        for (unsigned i = 0; attribute != 0; attribute >>= 1, i++)
        {
            if (attribute & 1) 
            { 
                os << ";" << i;
            }
        }
    }
};

std::ostream& operator<< (std::ostream& os, const Style& style)
{
    const uint32_t divisor = 1 << STYLE_SHIFT;
          uint32_t divided = style;
          uint32_t modulus = style % divisor;
    
    os << "\e[" << (modulus ? modulus : Foreground::DEFAULT);

    divided = divided / divisor;
    modulus = divided % divisor;

    Attribute::toStream(os, modulus);

    divided = divided / divisor;
    modulus = divided % divisor;

    os << ";" << (modulus ? modulus : Background::DEFAULT) << "m";

    return os;
}

} // end trmclr namespace

#endif // end __TRMCLR_H__
