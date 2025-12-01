// Deklrasi library yang akan digunakan
#include "FoodPlanner.h"
#include "ConnectionAPI.h" // memanggil header agar class connection api bisa digunakan
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// koneksi ke class ConnectionAPI

// class untuk koneksi API
class foodPlanning
{
private:
public:
    // fungsi untuk menggunakan API
    ConnectionAPI api; // menggunakan class dari connectionAPI untuk mengakses penggunaan API
    string response;   // untuk menangkap response

    void getFoodPlanner (string& response){
        if()
    };

    // method untuk get planer
    void getDataPlanner{


    };

    // method untuk simpan data ke .txt
    void savePlanner{

    };

    // method berisi data untuk membuat planner
    json createPlanner(string namaMahasiswa, double total_budget, const string &metode, double sisa_uang, string jenisMakanan, string tipeMakanan, string tipeMinuman)
    {
        json dataJSON;

        // set data untuk json
        dataJSON["nama_mahasiswa"] = namaMahasiswa;
        dataJSON["total_budget"] = total_budget;
        dataJSON["metode"] = metode;
        dataJSON["sisa_uang"] = sisa_uang;
        dataJSON["tipeMakanan"] = tipeMakanan;
        dataJSON["jenisMakanan"] = jenisMakanan;
        dataJSON["tipeMinuman"] = tipeMinuman;

        // convert json ke string ( tapi struktur tetap json )
        string JsonString = dataJSON.dump();

        // kirim ke API
        bool statusData = api.postJSON(JsonString, &response);

        if (!statusData)
        {
            return false;
        }

        return true;
    }

    // menangkap request dari curl
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }

    // FUNGSI UNTUK MENERIMA CURL REQUEST
    bool performCurlRequest(const string &url, string &response)
    {
        CURL *curl = curl_easy_init();
        if (!curl)
        {
            cerr << "Gagal untuk inisialisasi curl" << endl;
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
};