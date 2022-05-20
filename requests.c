#include "requests.h"

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}



struct MemoryStruct *call_API(char *API_KEY)
{
    assert(API_KEY != NULL);

    char API_URL[1024];
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct *chunk = (struct MemoryStruct*)malloc(sizeof(struct MemoryStruct));
    if (chunk == NULL)
        return NULL;

    chunk->memory = malloc(1);
    chunk->size = 0;

    API_URL[0] = '\0';
    strcat(API_URL, API);
    strcat(API_URL, API_KEY);

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, API_URL);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    res = curl_easy_perform(curl_handle);

    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
    }
    else
    {
        curl_easy_cleanup(curl_handle);
        //curl_global_cleanup();
        return chunk;
    }
    return NULL;
}