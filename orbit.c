#include "orbit.h"

mpf_t *computeVelocity(struct Constants *consts, mpf_t *distance_from_target)
{
    mpf_t TOTAL_RADIUS;
    mpf_t *Velocity = (mpf_t*)malloc(sizeof(mpf_t));
    if (Velocity == NULL)
        return NULL;
    

    mpf_init(*Velocity);
    mpf_init(TOTAL_RADIUS);
    mpf_set_ui(TOTAL_RADIUS, 0);
    mpf_set_ui(*Velocity, 0);

    mpf_add(TOTAL_RADIUS, TOTAL_RADIUS, consts->EARTH_RADIUS_METER);
    mpf_add(TOTAL_RADIUS, TOTAL_RADIUS, *distance_from_target);

    mpf_add(*Velocity, *Velocity, consts->GRAVITATIONAL_CONSTANT);
    mpf_mul(*Velocity, *Velocity, consts->EARTH_MASS);
    mpf_div(*Velocity, *Velocity, TOTAL_RADIUS);
    mpf_sqrt(*Velocity, *Velocity);
    
    return Velocity;
}