#include "constant.h"

struct Constants *InitConstant(void)
{
    int flag;
    struct Constants *consts = (struct Constants*)malloc(sizeof(struct Constants));
    
    if (consts == NULL)
        return NULL;
    
    else
    {
        mpf_init(consts->EARTH_MASS);
        mpf_set_ui(consts->EARTH_MASS,0);

        mpf_init(consts->EARTH_RADIUS_METER);
        mpf_set_ui(consts->EARTH_RADIUS_METER,0);

        mpf_init(consts->GRAVITATIONAL_CONSTANT);
        mpf_set_ui(consts->GRAVITATIONAL_CONSTANT,0);

        flag = mpf_set_str(consts->EARTH_MASS, E_M, 10);
        assert(flag == 0);

        flag = mpf_set_str(consts->EARTH_RADIUS_METER, E_R_M, 10);
        assert(flag == 0);

        flag = mpf_set_str(consts->GRAVITATIONAL_CONSTANT, G, 10);
        assert(flag == 0);


        return consts;
    }

}