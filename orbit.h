#ifndef __ORBIT_H__
#define __ORBIT_H__

#include <gmp.h>
#include <assert.h>

#include "constant.h"

mpf_t *computeVelocity(struct Constants *consts, mpf_t *distance_from_target);

#endif