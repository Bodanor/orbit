#include "parcer.h"

struct json_object *returnObject(char *buffer, const char *key)
{
    struct json_object *parsed_json;
    struct json_object *asked_value;

    parsed_json  = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, key, &asked_value);
    return asked_value;
}

struct json_object *json_object_get_with_keys( struct json_object *obj, const char *keys[] ) {
    while( keys[0] != NULL ) {
        if( !json_object_object_get_ex(obj, keys[0], &obj) ) {
            
            return NULL;
        }

        keys++;
    }

    return obj;
}