#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "constant.h"
#include "orbit.h"
#include "requests.h"
#include "parcer.h"

int main()
{
    int flag;
    const char *test;
    struct Constants *consts = InitConstant();
    mpf_t distance;
    mpf_t *Velocity;

    mpf_init(distance);





    char API_KEY[100];
    struct MemoryStruct *data;
    struct json_object *asked;

    printf("Enter the API-KEY : ");
    scanf("%99s", API_KEY);

    do
    {
        data = call_API(API_KEY);
        asked = returnObject(data->memory, "positions");
        asked = json_object_array_get_idx(asked, 0);
        json_object_object_get_ex(asked, "sataltitude", &asked);
        if (data != NULL)
        {
            test = json_object_get_string(asked);
            flag = mpf_set_str(distance, test, 10);
            assert(flag == 0);
            
            mpf_mul_ui(distance, distance, 1000);
            Velocity = computeVelocity(consts, &distance);

            gmp_printf("SAT DISTANCE  : %.Ff m\n", distance);
            gmp_printf("GRAV : %.Ff m3 kg-1 s-2\n", consts->GRAVITATIONAL_CONSTANT);
            gmp_printf("EARTH_RADIUS_METER : %.Ff m\n", consts->EARTH_RADIUS_METER);
            gmp_printf("EARTH_MASS : %.Ff kg\n\n", consts->EARTH_MASS);
            
            gmp_printf("VELOCITY : %.Ff m/s\n", *Velocity);
        }

    }while (data != NULL);



}