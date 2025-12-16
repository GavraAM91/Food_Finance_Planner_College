// use header
#define _HAS_STD_BYTE 0
#define NOMINMAX
#include <windows.h>

#include "FoodPlanningForm.h" // header food planning form

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
        system("cls"); // cls kepanjangan dari clear screen

        cout << "=============================================" << endl;
        cout << "      FORM PERENCANAAN MAKAN MAHASISWA" << endl;
        cout << "=============================================" << endl;

        // input nama mahasiswa
        cout << left << setw(28) << "Masukkan nama Mahasiswa " << left << setw(5) << ": ";
        getline(cin, namaMahasiswa);

        // masukkan total budget
        cout << left << setw(28) << "Masukkan Total Budget " << left << setw(5) << ": ";
        cin >> total_budget;
        cin.ignore();

        // perencanaan
        cout << endl;
        cout << "-------------------------------" << endl;
        cout << left << setw(28) << "Pilih Metode Hemat : " << endl;
        cout << "-------------------------------" << endl;
        cout << "1. Boros " << endl;
        cout << "2. Saving 10% " << endl;
        cout << "3. Saving 20% " << endl;
        cout << "4. Saving 30% " << endl;
        cout << "5. Saving 50% " << endl;
        cout << "-------------------------------" << endl;
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
        cout << endl;
        cout << left << setw(28) << "Jenis Makanan (ayam, sayur)" << ": ";
        getline(cin, jenisMakanan);

        // memasukkan tipe maakanan apa yang dia suka
        cout << endl;
        cout << left << setw(28) << "Tipe Makanan (berat, ringan)" << ": ";
        getline(cin, tipeMakanan);

        // memasukkan tipe minuman apa yang dia suka
        cout << endl;
        cout << left << setw(28) << "Tipe Minuman (air mineral, manis)" << ": ";
        getline(cin, tipeMinuman);

        planner.createPlanner(
            namaMahasiswa,
            total_budget,
            metode,
            sisa_uang,
            jenisMakanan,
            tipeMakanan,
            tipeMinuman);

        // response
        cout << endl;
        cout << " Lihat Response dari response... " << endl;
        system("pause"); // pause untuk melihat respon dari system

        // membersihkan layar
        system("cls");

        // tampilkan hasil ke user
        cout << endl;
        cout << "---        DATA PLANNING MAKANAN     ---" << endl;
        cout << endl;
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

        cout << " " << endl;
        cout << "Apakah ingin menyimpan hasil ini ? ( Y / T )";
        cin >> pilihanUser;
        cin.ignore();

        if (pilihanUser == 'y' || pilihanUser == 'Y')
        {
            // Ambil data hasil response API
            if (!planner.response.empty())
            {
                // HASIL LIVECODE :
                // deklraasi variabel
                // string inputFile;

                // cout << "Masukkan nama file : ";
                // getline(cin, inputFile);

                system("cls");
                planner.getFoodPlanner(planner.response); // isi struct pk & daftarMenu
                // planner.savePlanner(inputFile);           // menyimpan ke file txt // LIVE CODE 
                planner.savePlanner();           // menyimpan ke file txt
                cout << endl;
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

// method untuk melihat planner yang sudah dibuat untuk minggu ini
void FoodPlanningForm::getPlannerAWeek()
{
    // deklarasi variabel yang diperlukan
    string day, month, year;
    FoodPlanning fp; // deklarasi object class

    // bersihkan layaaar duulu
    system("cls");

    cout << "---------------------------------------" << endl;
    cout << "===        LIHAT DATA PLANNING     ===" << endl;
    cout << "---------------------------------------" << endl;
    cout << endl;

    cout << left << setw(25) << "Masukkan tanggal planning minggu ini : ";
    cin >> day;

    cout << endl;
    cout << left << setw(10) << "Masukkan Bulan : ";
    cin >> month;

    cout << endl;
    cout << left << setw(10) << "Masukkan tahun : ";
    cin >> year;

    system("cls");

    // masukkan ke dalam function getsavedplanner
    fp.getSavedPlanner(day, month, year);

    // return
}

/// method untuk membaca pengeluaran hari ini
string FoodPlanningForm::readDailyExpenses()
{
    // deklarasi function foodPlanner
    FoodPlanning fp;

    // deklarasi variabel
    string tanggal = fp.getDay();
    ifstream MyFile(pathExpenses);

    if (!MyFile)
    {
        return "File pengeluaran harian belum dibuat atau tidak ditemukan.\n";
    }

    string line, blokTerakhir = "";
    bool sedangMengambil = false;

    system("cls");

    // Membaca baris per baris
    while (getline(MyFile, line))
    {
        // Logika: Jika menemukan kata "Tanggal :", berarti data baru dimulai
        // Kita reset blokTerakhir agar hanya mengambil data yang paling baru
        if (line.find("Tanggal : ") != string::npos)
        {
            if (line.find(tanggal) != string::npos)
            {
                sedangMengambil = true;
            }
            else
            {
                sedangMengambil = false;
            }
            blokTerakhir = "";
        }

        if (sedangMengambil)
        {
            blokTerakhir += line + "\n";
        }
    }

    MyFile.close();

    if (blokTerakhir.empty())
        return " [INFO] Belum ada data pengeluaran yang terekam.\n";

    return blokTerakhir;
};

// method untuk membua pengeluaran harian
string FoodPlanningForm::createDailyExpenses()
{
    // deklarasi variabel dan kelas
    FoodPlanning fp;
    string deskripsiPengeluaran;
    double totalUangYangDikeluarkanHariIni;

    string inputFile;

    // output user
    system("cls");

    cout << "---------------------------------------" << endl;
    cout << "===    PENGELUARAN HARI INI    ====" << endl;
    cout << "---------------------------------------" << endl;

    cout << endl;

    cout << "Alasan Pengeluaran hari ini : ";
    getline(cin, deskripsiPengeluaran);

    cout << endl;
    cout << "Jumlah uang yang dikeluarkan  : ";
    cin >> totalUangYangDikeluarkanHariIni;
    cin.ignore();

    cout << endl;
    cout << "Nama file yang ingin diinput : ";
    getline(cin, inputFile);

    // panggil kelas foodPlanning
    fp.createDailyExpenses(deskripsiPengeluaran, totalUangYangDikeluarkanHariIni, inputFile);

    return "Data berhaasaail";
}
