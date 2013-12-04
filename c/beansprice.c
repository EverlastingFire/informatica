
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

typedef struct cache {
	char *data;
	size_t size;
} cache;

size_t write_data_cb(void *contents, size_t size, size_t nmemb, void *user_data)
{
	size_t data_size = size * nmemb;
	cache *mem = (cache*) user_data;

	mem->data = malloc(data_size + 1);

	if (!mem->data) {
		printf("Error while allocating memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(mem->data, contents, data_size);
	mem->size += data_size;
	mem->data[mem->size] = '\0';

	return data_size;
}

int main(void)
{
	CURL *curl;
	CURLcode res;

	cache data;

	char *pos;
	char *price;

	data.data = NULL; /* will be allocated to handle the response content */
	data.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, "http://beans.itcarlow.ie/prices-loyalty.html");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_cb);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &data);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "testagent/1.0");

	res = curl_easy_perform(curl);

	if(res != CURLE_OK) {
		fprintf(stderr, "error while retrieving the web page: %s\n",
						curl_easy_strerror(res));
	}
	else {
		pos = strstr(data.data, ">$");

		if (pos) {
			price = strndup(pos + 2, 4);
			printf("Beans price: %s\n", price);
			free(price);
		}
	}

	curl_easy_cleanup(curl);

	if(data.data)
		free(data.data);

	curl_global_cleanup();

	return 0;
}