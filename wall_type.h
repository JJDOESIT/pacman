#ifndef _WALL_TYPE_
#define _WALL_TYPE_

enum wall_type
{
    TOPRIGHTCORNERCONNECTOR,
    TOPLEFTCORNERCONNECTOR,
    TOPLEFTCORNERDOUBLE,
    TOPRIGHTCORNERDOUBLE,
    BOTTOMRIGHTCORNERDOUBLE,
    BOTTOMLEFTCORNERDOUBLE,
    TOPLEFTCORNERSINGLE,
    TOPRIGHTCORNERSINGLE,
    BOTTOMRIGHTCORNERSINGLE,
    BOTTOMLEFTCORNERSINGLE,
    TOPLEFTCORNERSINGLECONNECTOR,
    TOPRIGHTCORNERSINGLECONNECTOR,
    BOTTOMRIGHTCORNERSINGLECONNECTOR,
    BOTTOMLEFTCORNERSINGLECONNECTOR,
    STRAIGHTVERTICALLEFTDOUBLE,
    STRAIGHTVERTICALRIGHTDOUBLE,
    STRAIGHTVERTICALMIDDLELEFT,
    STRAIGHTVERTICALMIDDLERIGHT,
    STRAIGHTHORIZONTALTOPDOUBLE,
    STRAIGHTHORIZONTALBOTTOMDOUBLE,
    STRAIGHTHORIZONTALTOPSINGLE,
    STRAIGHTHORIZONTALBOTTOMSINGLE,
    FILLED,
};

#endif