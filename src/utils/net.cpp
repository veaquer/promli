#include "utils/net.h"
#include "utils/logger.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

namespace utils {
std::string net::http_get(const std::string &url) {
  CURL *curl;
  CURLcode res;
  std::string response;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION,
        [](void *ptr, size_t size, size_t nmemb, std::string *data) -> size_t {
          data->append(reinterpret_cast<char *>(ptr), size * nmemb);
          return size * nmemb;
        });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      Logger::err(std::string("Request failed: ") + curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return response;
}
} // namespace utils
