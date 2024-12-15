#include "search.h"
#include "utils.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <cjson/cJSON.h>

static void build_search_url(const char *query, char *url, size_t url_size) {
    snprintf(url, url_size, "https://sources.debian.org/api/search/%s/", query);
}

static void parse_json_response(const char *response, char ***results, int *result_count) {
    cJSON *json = cJSON_Parse(response);
    if (!json) {
        fprintf(stderr, "Failed to parse JSON response.\n");
        return;
    }

    cJSON *results_obj = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (!results_obj) {
        cJSON_Delete(json);
        return;
    }

    cJSON *exact = cJSON_GetObjectItemCaseSensitive(results_obj, "exact");
    cJSON *other = cJSON_GetObjectItemCaseSensitive(results_obj, "other");

    int count = 0;
    if (exact && cJSON_IsObject(exact)) count++;
    if (other && cJSON_IsArray(other)) count += cJSON_GetArraySize(other);

    *results = malloc(count * sizeof(char *));
    *result_count = count;

    int idx = 0;
    if (exact && cJSON_IsObject(exact)) {
        cJSON *name = cJSON_GetObjectItemCaseSensitive(exact, "name");
        if (cJSON_IsString(name)) {
            (*results)[idx++] = strdup(name->valuestring);
        }
    }

    if (other && cJSON_IsArray(other)) {
        cJSON *entry = NULL;
        cJSON_ArrayForEach(entry, other) {
            cJSON *name = cJSON_GetObjectItemCaseSensitive(entry, "name");
            if (cJSON_IsString(name)) {
                (*results)[idx++] = strdup(name->valuestring);
            }
        }
    }

    cJSON_Delete(json);
}

void search_package(const char *query, char ***results, int *result_count) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk = {NULL, 0};

    *results = NULL;
    *result_count = 0;

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL.\n");
        return;
    }

    char url[512];
    build_search_url(query, url, sizeof(url));

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        parse_json_response(chunk.memory, results, result_count);
    }

    curl_easy_cleanup(curl);
    free(chunk.memory);
}
