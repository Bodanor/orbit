#ifndef __PARCER_H__
#define __PARCER_H__

#include<json-c/json.h>


struct json_object *returnObject(char *buffer, const char *key);
struct json_object *json_object_get_with_keys( struct json_object *obj, const char *keys[] );
#endif