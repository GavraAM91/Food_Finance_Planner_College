
#ifndef FOODPLANNINGFORM_H
#define FOODPLANNINGFORM_H

#define _HAS_STD_BYTE 0

#include <windows.h>
// deklrasi variabel
#include <iostream>
#include <string> 
#include <ctime> // digunakan untuk waktu c++
#include <iomanip> // digunakan untuk merapikan tampilan c++
#include "backend/FoodPlanner.h" // koneksi ke bagian backend food planner

using namespace std;

// buat class untuk form
class FoodPlanningForm
{
private:
public:
    // digunakan untuk membuat planner
    void makePlanner();
    string readPlanner();
    string readDailyExpenses();
    string createDailyExpenses(int jumlahPengeluaran, double totalUangYangDikeluarkanHariIni);
    string checkAllPlanner();
    string getPlannerAWeek();
};

#endif