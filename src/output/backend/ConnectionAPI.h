#ifndef CONNECTIONAPI_H
#define CONNECTIONAPI_H

// deklrasi library yang digunakan
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;
using namespace std;

// class untuk memanggil API URL
class ConnectionAPI
{
private:
    // inisialisasi variabel yang akan digunakan untuk emngirim data ke N8N
    string url_API_POST = "https://Localhost::5678/webhook/foodplanner"; // mengirim data ke N8N
    string url_API_GET = "";  // menerima data dari N8N

public:

    // fungsi untuk menggunakan API

    // menangkap request dari curl
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    // FUNGSI UNTUK MENERIMA CURL REQUEST
    bool performCurlRequest(const string &url, string &response);

    // FUNGSI UNTUK MENGIRIM REQUEST DARI USER
    bool postJSON(string& jsonData, string* response );
};

#endif
