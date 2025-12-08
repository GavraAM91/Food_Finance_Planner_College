
#ifndef FOODPLANNINGFORM_H
#define FOODPLANNINGFORM_H

#define _HAS_STD_BYTE 0

#include <windows.h>
// deklrasi variabel
#include <iostream>
#include <string>
#include <chrono> // libary yang digunakan untuk waktu, link : https://en.cppreference.com/w/cpp/chrono.html

using namespace std;

// buat class untuk form
class FoodPlanningForm
{
private:
public:
    // digunakan untuk membuat planner
    void clearScreen();
    void makePlanner();
    string readPlanner();
    string readDailyExpenses();
    string createDailyExpenses(int jumlahPengeluaran, double totalUangYangDikeluarkanHariIni);
    string checkAllPlanner();
    string getPlannerAWeek();
};

#endif