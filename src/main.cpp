#define _HAS_STD_BYTE 0
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>

#include "backend/ConnectionAPI.h"
#include "backend/FoodPlanner.h"
#include "FoodPlanningForm.h"

using namespace std;

int main()
{
    system("cls");
    FoodPlanningForm FP;
    int opsiUser;

    while (true)
    {
        system("cls");
        cout << "===    TAMPILAN    ===" << endl;
        cout << "1. Pengeluaran Hari Ini" << endl;
        cout << "2. Lihat pengeluaran hari ini" << endl;
        cout << "3. Lihat planning minggu ini" << endl;
        cout << "4. Buat Planning minggu ini" << endl;
        cout << "5. Keluar" << endl;
        cout << "-------------------------" << endl;

        cout << " Input Opsi (1 - 5): ";
        cin >> opsiUser;
        cin.ignore();

        switch (opsiUser)
        {
        // digunakna untuk membuat pengeluaran hari ini
        case 1:
        {
            int jumlah;
            double total;

            cout << "Jumlah item pengeluaran hari ini : ";
            cin >> jumlah;

            cout << "Total uang yang dikeluarkan hari ini : Rp";
            cin >> total;

            string hasil = FP.createDailyExpenses(jumlah, total);
            cout << hasil << endl;
            system("pause");
            break;
        }

        case 2:
            cout << FP.readDailyExpenses();
            system("pause");
            break;

        case 3:
            FP.getPlannerAWeek();
            system("pause");
            break;

        case 4:
            FP.makePlanner();
            system("pause");

            break;

        case 5:
            return 0;
        }
    }

    return 0;
}