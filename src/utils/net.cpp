#include "utils/net.h"
#include "utils/logger.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

namespace utils {
static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

std::string net::http_get(const std::string &url) {
  CURL *curl;
  CURLcode res;
  std::string response;

  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
      Logger::err(std::string("Request failed: ") + curl_easy_strerror(res));
    }
  }

  return response;
}
} // namespace utils
