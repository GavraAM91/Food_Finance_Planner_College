// use header
#define _HAS_STD_BYTE 0
#define NOMINMAX
#include <windows.h>

#include "FoodPlanningForm.h" // header food planning form

// ===== DI KOMEN KARENA SUDAH AADA DI FOODPLANNING.CPP ====
// function untuk mendapatkan data tanggal
// string getDay()
// {
//     time_t now = time(0);
//     tm *ltm = localtime(&now);

//     // variabel untuk menampung hasil
//     char buffer[80];

//     // panggil fungsi bawaan ctime
//     strftime(buffer, 801., "%d-%m-%Y", ltm);

//     return string(buffer);
// }

// Method untuk membuat planner
void FoodPlanningForm::makePlanner()
{
    // deklarasi dulu ke true untuk statusnya
    bool statusProgram = true;
    while (statusProgram == true)
    {
        // deklarasi kelas foodPlaning :
        FoodPlanning planner;

        // deklarasi variabel yang diperlukan
        int id_mahasiswa, metode;
        string namaMahasiswa, jenisMakanan, tipeMakanan, tipeMinuman;
        double total_budget, sisa_uang;

        // digunakan untuk mengulang program
        statusProgram = false; // ganti ke false untuk jaga jaga apakah program akan dilanjutkan atau tidak

        // variabel untuk keperluan program
        int opsiUser, opsiUser2;
        char pilihanUser;

        // fungsi untuk membersihkan layar
        system("cls");

        cout << "=============================================" << endl;
        cout << "      FORM PERENCANAAN MAKAN MAHASISWA" << endl;
        cout << "=============================================" << endl;

        // ambil input id mahasiswa
        cout << left << setw(28) << "Masuukkan Id Mahasiswa : ";
        cin >> id_mahasiswa;
        cin.ignore();

        // input nama mahasiswa
        cout << left << setw(28) << "Masukkan nama Mahasiswa : ";
        getline(cin, namaMahasiswa);
        cin.ignore();

        // masukkan total budget
        cout << left << setw(28) << " Masukkan Total Budget : ";
        cin >> total_budget;
        cin.ignore();

        // perencanaan
        cout << left << setw(28) << " Pilih Metode Hemat " << endl;
        cout << "1. Boros " << endl;
        cout << "2. Saving 10% " << endl;
        cout << "3. Saving 20% " << endl;
        cout << "4. Saving 30% " << endl;
        cout << "5. Saving 50% " << endl;
        cout << "Masukkan Pilihan ( 1 - 5 ) : ";
        cin >> opsiUser;

        switch (opsiUser)
        {
        case 1:
            metode = 0;
            break;
        case 2:
            metode = 10;
            break;
        case 3:
            metode = 20;
            break;
        case 4:
            metode = 30;
            break;
        case 5:
            metode = 50;
            break;

        default:
            cout << "Pilihan tidak ada ulangi kembali ! " << endl;
            system("pause");
            break;
        }

        cin.ignore();

        // memasukkan jenis makan apa yang dia suka
        cout << left << setw(28) << "Jenis Makanan" << ": ";
        getline(cin, jenisMakanan);

        // memasukkan tipe maakanan apa yang dia suka
        cout << left << setw(28) << "Tipe Makanan" << ": ";
        getline(cin, tipeMakanan);

        // memasukkan tipe minuman apa yang dia suka
        cout << left << setw(28) << "Tipe Minuman" << ": ";
        getline(cin, tipeMinuman);

        json result = planner.createPlanner(
            id_mahasiswa,
            namaMahasiswa,
            total_budget,
            metode,
            sisa_uang,
            jenisMakanan,
            tipeMakanan,
            tipeMinuman);

        // response
        cout << " Lihat Response dari response... " << endl;
        system("pause"); // pause untuk melihat respon dari system

        // membersihkan layar
        system("cls");

        // tampilkan hasil ke user
        cout << "---        DATA PLANNING MAKANAN     ---" << endl;
        // handling error untuk data
        if (!planner.response.empty())
        {
            // langsung buka food planner
            planner.getFoodPlanner(planner.response);
        }
        else
        {
            cout << "Data planning makanan tidak tersedia untuk saat ini! " << endl;
        }
        cout << "-----------------------------------------------------------------------------------------\n";
        cout << " " << endl;
        cout << "Apakah ingin menyimpan hasil ini ? ( Y / T )";
        cin >> pilihanUser;

        if (pilihanUser == 'y' || pilihanUser == 'Y')
        {
            // Ambil data hasil response API
            if (!planner.response.empty())
            {
                planner.getFoodPlanner(planner.response); // isi struct pk & daftarMenu
                planner.savePlanner();                    // menyimpan ke file txt
                cout << "Planner berhasil disimpan ke DataFoodPlannerMahasiswa.txt! " << endl;
            }
            else
            {
                cout << " Tidak ada data dari server. Tidak bisa disimpan." << endl;
            }
        }
        else if (pilihanUser == 't' || pilihanUser == 'T')
        {
            system("cls");
            cout << "Apakah ingin keluar atau mengulangi prediksi ? " << endl;
            cout << "1. Ulangi Predikisi" << endl;
            cout << "2. Keluar Program" << endl;
            cout << "Opsi ( 1 - 2)  " << endl;
            cin >> opsiUser2;

            // handling for percabangan
            switch (opsiUser2)
            {
            case 1:
                statusProgram = true;
                system("cls");
                break;
            case 2:
                cout << "Program berhenti" << endl;
                break;

            default:
                break;
            }
            cout << " Mengulangi Prediksi......" << endl;
            system("pause");
        }
    }
}

// string FoodPlanningForm::readPlanner()
// {
//     ifstream MyFile("DataFoodPlannerMahasiswa.txt");
//     if (!MyFile)
//         return "File planner tidak ditemukan.\n";

//     string line, lastBlock = "";
//     bool collecting = false;

//     while (getline(MyFile, line))
//     {
//         // Jika ketemu tanggal → mulai blok baru
//         if (line.find("Tanggal :") != string::npos)
//         {
//             lastBlock = "";
//             collecting = true;
//         }

//         if (collecting)
//             lastBlock += line + "\n";

//         // blok selesai saat ketemu garis
//         if (line.find("---------------------------------------------") != string::npos)
//             collecting = false;
//     }

//     MyFile.close();

//     if (lastBlock.empty())
//         return "Tidak ada data planner tersimpan.\n";

//     return lastBlock;
// }

// method untuk melihat planner yang sudah dibuat untuk minggu ini
void FoodPlanningForm::getPlannerAWeek()
{
    // deklarasi variabel yang diperlukan
    string day, month, year;
    FoodPlanning fp; // deklarasi object class

    cout << "===        LIHAT DATA PLANNING     ===" << endl;
    cout << "Masukkan tanggal planning minggu ini : ";
    cin >> day;

    cout << "Masukkan Bulan : ";
    cin >> month;

    cout << "Masukkan tahun : ";
    cin >> year;

    // masukkan ke dalam function getsavedplanner
    fp.getSavedPlanner(day, month, year);

    // return
}

// method untuk melihat pengeluaran harian
string FoodPlanningForm::readDailyExpenses()
{
    // buka file
    ifstream MyFile("DailyExpenses.txt");
    if (!MyFile)
    {
        // return untuk notifikasi
        cout << "File pengeluaran harian tidak ditemukan." << endl;
    }

    string line, lastBlock = "";
    bool collecting = false;

    while (getline(MyFile, line))
    {
        if (line.find("Tanggal :") != string::npos)
        {
            lastBlock = "";
            collecting = true;
        }

        if (collecting)
            lastBlock += line + "\n";

        if (line.find("---------------------------------------------") != string::npos)
            collecting = false;
    }

    MyFile.close();

    if (lastBlock.empty())
        return "Belum ada pengeluaran harian.\n";

    return lastBlock;
}

// method untuk membua pengeluaran harian
string FoodPlanningForm::createDailyExpenses(int jumlahPengeluaran,
                                             double totalUangYangDikeluarkanHariIni)
{
    // deklarasikan foodplanner
    FoodPlanning fp;

    // variabel untuk menyimpan data tanggal
    string tanggal = fp.getDay();

    ofstream file("DailyExpenses.txt", ios::app);

    if (!file)
        return "Gagal membuka file pengeluaran harian!\n";

    // header tanggal
    file << tanggal << "\n";
    file << "------------------------------------------------\n";
    file << "Total Pengeluaran Hari Ini : Rp" << totalUangYangDikeluarkanHariIni << "\n";
    file << "Jumlah Item                : " << jumlahPengeluaran << "\n";
    file << "---------------------------------------------\n\n";

    file.close();

    return "Pengeluaran harian berhasil disimpan.\n";
}

// method untuk melihat seluruh planner
string FoodPlanningForm::checkAllPlanner()
{
    ifstream MyFile("DataFoodPlannerMahasiswa.txt");
    if (!MyFile)
        return "File planner tidak ditemukan.\n";

    string line, isi = "";

    while (getline(MyFile, line))
        isi += line + "\n";

    MyFile.close();

    if (isi.empty())
        return "Tidak ada data planner tersimpan.\n";

    return isi;
}