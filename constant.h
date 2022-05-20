#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include <gmp.h>
#include "stdlib.h"
#include <assert.h>

#define E_R_M "6378137.0"
#define E_M "5972200000000000000000000"
#define G "0.000000000066743"

struct Constants
{
    mpf_t EARTH_RADIUS_METER;
    mpf_t EARTH_MASS;
    mpf_t GRAVITATIONAL_CONSTANT;
};

struct Constants *InitConstant(void);


#endif