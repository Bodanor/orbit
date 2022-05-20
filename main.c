#include <gmp.h>
#include <stdio.h>
#include <assert.h>

#include "constant.h"
#include "orbit.h"

int main()
{
    int flag;
    char inputDistance[1024];
    struct Constants *consts = InitConstant();
    mpf_t distance;
    mpf_t *Velocity;

    mpf_init(distance);

    printf("Enter the satellite distance in meter: ");
    scanf("%1023s", inputDistance);


    flag = mpf_set_str(distance, inputDistance, 10);
    assert(flag == 0);
    
    Velocity = computeVelocity(consts, &distance);

    gmp_printf("SAT DISTANCE  : %.Ff m\n", distance);
    gmp_printf("GRAV : %.Ff m3 kg-1 s-2\n", consts->GRAVITATIONAL_CONSTANT);
    gmp_printf("EARTH_RADIUS_METER : %.Ff m\n", consts->EARTH_RADIUS_METER);
    gmp_printf("EARTH_MASS : %.Ff kg\n\n", consts->EARTH_MASS);
    
    gmp_printf("VELOCITY : %.Ff m/s\n", *Velocity);

}