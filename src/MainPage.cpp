// deklarasi library
#include "FoodPlanningForm.h"
#include "MainPage.h"

void MainPage()
{
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
        cout << "5. History Planning " << endl;
        cout << "6. Keluar" << endl;

        cout << " Input Opsi (1 - 6): ";
        cin >> opsiUser;

        switch (opsiUser)
        {
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
            cout << FP.readPlanner();
            system("pause");
            break;

        case 4:
            FP.makePlanner();
            system("pause");
            break;

        case 5:
            return;
        }
    }
}
