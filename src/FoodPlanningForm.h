
#ifndef FOODPLANNINGFORM_H
#define FOODPLANNINGFORM_H

#define _HAS_STD_BYTE 0

#include <windows.h>
// deklrasi variabel
#include <iostream>              // untuk input output d.l.l
#include <string>                // untuk menggunakan libary dari string
#include <ctime>                 // digunakan untuk waktu c++
#include <iomanip>               // digunakan untuk merapikan tampilan c++
#include "backend/FoodPlanner.h" // koneksi ke bagian backend food planner

using namespace std;

// buat class untuk form
class FoodPlanningForm
{
private:
public:
    // variabel untuk set up path file
    string pathPlanner = "D:/Coding/UNESA/Project/Food-Finance-Planner/dataFile/Planner/DataFoodPlannerMahasiswa.txt"; // path planner
    string pathExpenses = "D:/Coding/UNESA/Project/Food-Finance-Planner/dataFile/Expenses/DailyExpenses.txt";          // path expenses

    // digunakan untuk membuat planner
    void makePlanner();
    // string readPlanner();        // di command atau deactive karena fungsi tidak digunakan                                                              // function untuk membaca planner
    string readDailyExpenses();                                                                // untuk membcaa pengeluaran hari ini
    string createDailyExpenses(int jumlahPengeluaran, double totalUangYangDikeluarkanHariIni); // untuk membuaat pengeluaaraan hariaan
    string checkAllPlanner();                                                                  // print seluruh plaannner ke screen
    void getPlannerAWeek();   
    
    // print planner untuk seminggu

    // FUNCTION UNTUK MENYIMPAN DATA MAKANAN
    void createFoodData();
};

#endif