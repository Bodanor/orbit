#ifndef __PARCER_H__
#define __PARCER_H__

#include<json-c/json.h>


struct json_object *returnObject(char *buffer, const char *key);
struct json_object *returnObjectFromList(json_object *obj_list, const char *key);
#endif