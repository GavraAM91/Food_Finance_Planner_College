// Deklrasi library yang akan digunakan
#include "ConnectionAPI.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// fungsi untuk menggunakan API

// menangkap request dari curl
size_t ConnectionAPI::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

// FUNGSI UNTUK MENERIMA CURL REQUEST
bool ConnectionAPI::performCurlRequest(const string &url, string &response)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        return false;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK);
}

// MENGIRIM DATA KE N8N
bool ConnectionAPI::postJSON(string &jsonData, string *response)
{

    CURL *curl = curl_easy_init();

    if (!curl)
    {
        return false;
    }

    // pakai url dari ConnectionAPI.h
    const string urlPOST = url_API_POST;

    // set URL
    curl_easy_setopt(curl, CURLOPT_URL, urlPOST.c_str());

    // POST method
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // body JSON
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

    // header to json
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Callback untuk membaca response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        cerr << "curl_easy_perform() gagal: " << curl_easy_strerror(res) << endl;
        return false;
    }

    return true;
}