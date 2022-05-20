#ifndef __REQUESTS_H__
#define __REQUESTS_H__

#include <curl/curl.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define API "https://api.n2yo.com/rest/v1/satellite/positions/44850/50.63373/5.56749/0/1/&apiKey="

struct MemoryStruct {
  char *memory;
  size_t size;
};


struct MemoryStruct *call_API(char *API_KEY);
#endif