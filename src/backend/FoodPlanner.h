#ifndef FOODPLANNER_H
#define FOODPLANNER_H
#define _HAS_STD_BYTE 0

// deklrasi variabel
#include <string>            // untuk operasi string
#include <vector>            // untuk array dinamis
#include <fstream>           // untuk operasi file
#include <iostream>          // untuk cin cout d.l.l
#include <curl/curl.h>       // untuk menangkap API
#include <nlohmann/json.hpp> // untuk json
#include "ConnectionAPI.h"
#include <ctime> // untuk menggunakan library waktu

using json = nlohmann::json;
using std::string;

// menyimpan data dari JSON
struct PrediksiDataKeuangan
{
    string status;
    string message;

    double total_budget = 0;
    double budget_harian = 0;
    double uang_disimpan = 0;
    int saving_rate;
};

// digunakan untuk menyimpan menu makanan
struct PrediksiMenu
{
    int hari;
    int waktu;
    int id_makanan;

    string nomor_kantin;
    string harga;
    string pemilik_kantin;
    string nama_makanan;
    string tipe_makanan;
};

class FoodPlanning
{
private:
    PrediksiMenu pm;
    PrediksiDataKeuangan pk;
    vector<PrediksiMenu> daftarMenu; // menggunakan vector untuk array dinamis

public:
    ConnectionAPI api;
    string response;

    // variabel untuk menyimpan path folder yang digunakan
    string pathPlanner = "D:/Coding/UNESA/Project/Food-Finance-Planner/dataFile/Planner/DataFoodPlannerMahasiswa.txt"; // path planner
    string pathExpenses = "D:/Coding/UNESA/Project/Food-Finance-Planner/dataFile/Expenses/DailyExpenses.txt";          // path expenses

    // untuk menggunakan tanggal
    string getDay();

    // mengambil dan menapilkan data planner yang tersimpan di txt
    void getSavedPlanner(string day, string month, string year);

    // untuk mengambil food planner
    void getFoodPlanner(string &response);

    // untuk menyimpan dalam bentuk file txt
    void savePlanner();

    // untuk membaca pengeluaraan harian
    // string readDailyExpenses();

    // untuk menyimpan pengeluaran harian
    string createDailyExpenses(string deksripsiPengeluaran, double totalUangYangDikeluarkanHariIni);

    // request user untuk membuat planner
    json createPlanner(string namaMahasiswa, double total_budget, int metode,
                       double sisa_uang, string jenisMakanan, string tipeMakanan, string tipeMinuman);
};
#endif