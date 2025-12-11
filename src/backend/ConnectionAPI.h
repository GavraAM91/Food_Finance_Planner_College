#ifndef CONNECTIONAPI_H
#define CONNECTIONAPI_H

// deklrasi library yang digunakan
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using Json = nlohmann::json; // digunakan untuk memakai class atau library dari nlohman json
using namespace std;

// class untuk memanggil API URL
class ConnectionAPI
{
private:
    // inisialisasi variabel yang akan digunakan untuk emngirim data ke N8N
    string url_API_POST = "http://localhost:5678/webhook-test/cd0697cd-ad14-4eef-bd32-df25df5543d0"; // mengirim data ke N8N
    string url_API_GET = "";                                                                         // menerima data dari N8N

public:
    // fungsi untuk menggunakan API
    // FUNGSI UNTUK MENERIMA CURL REQUEST
    bool performCurlRequest(const string &url, string &response);

    // FUNGSI UNTUK MENGIRIM REQUEST DARI USER
    bool postJSON(string &jsonData, string *response);
};

#endif
