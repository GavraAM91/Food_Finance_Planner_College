// DIGUNAKAN HANYA UNTUK TESTING !
// TESTING APAKAH LIBRARY CURL DAN JSON SUDAH AKTIF!
// DAN UNTUK PEMBELAJARAN SAJA! TIDAK DIPAKAI PADA KODE UTAMA!
// PERLU SET UP LEBIH LANJUT!

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// Callback function untuk CURL
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t totalSize = size * nmemb;
    ((string *)userp)->append((char *)contents, totalSize);
    return totalSize;
}

// GET request
bool performCurlRequest(const string &url, string &response)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        cerr << "Failed to initialize CURL" << endl;
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        return false;
    }

    return true;
}

int main()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);

    string api_url =
        "https://api.open-meteo.com/v1/forecast?latitude=-7.25&longitude=112.75&current_weather=true";

    string response;

    if (performCurlRequest(api_url, response))
    {
        cout << "=== Raw JSON ===\n"
             << response << "\n\n";

        try
        {
            json root = json::parse(response);

            if (root.contains("current_weather"))
            {
                auto w = root["current_weather"];

                cout << "=== CURRENT WEATHER ===\n";
                cout << "Temperature : " << w["temperature"] << " °C\n";
                cout << "Windspeed   : " << w["windspeed"] << " km/h\n";
                cout << "Weathercode : " << w["weathercode"] << "\n";
            }
        }
        catch (const json::parse_error &e)
        {
            cerr << "JSON Parse Error: " << e.what() << endl;
        }
    }

    curl_global_cleanup();
    return 0;
}
