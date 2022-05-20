#include "parser.h"

struct json_object *returnObject(char *buffer, const char *key)
{
    struct json_object *parsed_json;
    struct json_object *asked_object;

    parsed_json  = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, key, &asked_object);
    return asked_object;
}

struct json_object *returnObjectFromList(json_object *obj_list, const char *key)
{
    int arraylen, i;

    struct json_object *tmp;
    arraylen = json_object_array_length(obj_list);

    for (i = 0; i < arraylen; i++)
    {
        tmp = json_object_array_get_idx(obj_list, i);
        tmp = json_object_object_get(tmp, key);
        if (tmp != NULL)
            return tmp;
    }
    return NULL;
}