// Deklrasi library yang akan digunakan
#define _HAS_STD_BYTE 0
#define NOMINMAX
#include <windows.h>

#include "FoodPlanner.h"
using json = nlohmann::json;

// method yang digunakan untuk mengakses tanggal =
string getDay()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // variabel untuk menampung hasil
    char buffer[80];

    // panggil fungsi bawaan ctime
    strftime(buffer, 80, "%d-%m-%Y", ltm);

    return string(buffer);
}

// method untuk menyimpan pengeluaran haria
void FoodPlanning::dailyExpenses(long long totalPengeluaran, string tanggal, string deskripsiPengeluaran)
{
    // deklarasi variabel
    string text;
    bool status = false; // digunakan untuk status apakah berhasil atau tidak, default false

    // open file
    ofstream MyFile("DataFoodPlannerMahasiswa.txt");

    // error handling
    if (!MyFile)
    {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    // panggil method tanggal
    string tanggal = getDay();

    // memasukkan data dari struct PrediksiDataKeuangan ke file
    MyFile << tanggal << "\n";
    MyFile << "===    DATA PENGELUARAN HARI INI   ===\n";
    MyFile << "Total Pengeluaran            : " << totalPengeluaran << "\n";
    MyFile << "Tanggal                      : " << tanggal << "\n";
    MyFile << "Deskripsi Pengeluaran        : " << deskripsiPengeluaran << "\n";
    MyFile << "--------------------------------------------------\n";

    // change status jadi true
    status = true;

    // tutup file
    MyFile.close();

    if (status == true)
    {
        cout << "Data berhasil dimasukkan!" << endl;
    }
    else
    {
        cout << "Dat ggal dimasukkan!" << endl;
    }
}

// method untuk check data planner tersimpan berdasarkan tanggal
// TAHAP PENGEMBANGAN
void FoodPlanning::getSavedPlanner(string day, string month, string year)
{
    // check file
    string isiText;

    // variabel nama file
    string namaFile = "DataFoodPlannerMahasiswa_";
    string cariTanggalByUser = day + "-" + month + "-" + year + ".txt";
    string namaFileTanggal = namaFile + cariTanggalByUser;

    // buka file
    ifstream MyFile(namaFileTanggal);

    if (!MyFile)
    {
        return;
    }

    while (getline(MyFile, isiText))
    {
        // if else untuk check tanggal minggu ini :
        cout << isiText;
        system("pause"); // berhenti untuk membaca 
        return;
    }

    // tutup file
    MyFile.close();

    return;
}

// method berisi data untuk membuat planner
json FoodPlanning::createPlanner(int id_mahasiswa, string namaMahasiswa, double total_budget, int metode, double sisa_uang, string jenisMakanan, string tipeMakanan, string tipeMinuman)
{
    json dataJSON;

    // set data untuk json
    dataJSON["id_mahasiswa"] = id_mahasiswa;
    dataJSON["nama_mahasiswa"] = namaMahasiswa;
    dataJSON["total_budget"] = total_budget;
    dataJSON["metode"] = metode;
    dataJSON["sisa_uang"] = sisa_uang;
    dataJSON["tipeMakanan"] = tipeMakanan;
    dataJSON["jenisMakanan"] = jenisMakanan;
    dataJSON["tipeMinuman"] = tipeMinuman;

    // convert json ke string ( tapi struktur tetap json )
    string JsonString = dataJSON.dump();

    bool status = api.postJSON(JsonString, &response); //

    if (!status)
    {
        return json();
    }

    // mengembalikan nilai berbentuk json
    return json::parse(response);
}

// method untuk mengambil data dari json
void FoodPlanning::getFoodPlanner(string &response)
{
    // get data atau respon dari json
    json dataJSON = Json::parse(response);

    // masukkan ke rencana keuangan
    auto rk = dataJSON["rencana_keuangan"];

    pk.total_budget = rk["total_budget"];
    pk.saving_rate = rk["saving_rate"];
    pk.uang_disimpan = rk["nominal_disimpan"];
    pk.budget_harian = rk["budget_harian_makanan"];

    // digunakan untuk iterasi
    int i = 0;

    // masukkan ke planning makanan ( HELPED BY GPT BAGIAN AUTO )
    for (auto &item : dataJSON["prediksi_menu"])
    {
        pm.id_makanan = item["id_makanan"];
        pm.harga = item["harga"];
        pm.nama_makanan = item["nama_makanan"];
        pm.pemilik_kantin = item["pemilik_kantin"];
        pm.tipe_makanan = item["tipe_makanan"];
        pm.nomor_kantin = item["nomor_kantin"];
        i++;

        daftarMenu.push_back(pm);
    }

    // output ke pengguna
    cout << "====   Rencana Keuangan    ===" << endl;
    cout << "Total Budget : " << pk.total_budget << endl;
    cout << "Mode Tabungan : " << pk.saving_rate << endl;
    cout << "Uang disimpan : " << pk.uang_disimpan << endl;
    cout << "Budget Harian : " << pk.budget_harian << endl;

    cout << "====   Menu minggu ini     ===" << endl;
    for (auto &pm : daftarMenu)
    {
        cout << "Nama makanan " << pm.nama_makanan
             << " | " << pm.tipe_makanan
             << " | Rp " << pm.harga
             << " | Kantin " << pm.nomor_kantin
             << " (" << pm.pemilik_kantin << ")"
             << endl;
    }
}

// method untuk simpan data ke .txt
void FoodPlanning::savePlanner()
{
    // digunakana untuk sttus program
    // bool statusProgram = false;

    // digunakan untuk iterasi
    int i = 0;

    // buka file
    ofstream MyFile("DataFoodPlannerMahasiswa.txt");

    // handler error
    if (!MyFile)
    {
        cout << "File tidak dapat ditemukan" << endl;
        return;
    }

    // panggil method tanggal
    string tanggal = getDay();

    // memasukkan data dari struct PrediksiDataKeuangan ke file
    MyFile << tanggal << "\n";
    MyFile << "===    PREDIKSI DATA KEUANGAN  ===\n";
    MyFile << "Total Budget : " << pk.total_budget << "\n";
    MyFile << "Saving       : " << pk.saving_rate << "\n";
    MyFile << "Disimpan     : " << pk.uang_disimpan << "\n";
    MyFile << "Harian Makan : " << pk.budget_harian << "\n\n";
    MyFile << "--------------------------------------------------\n";

    // gunakan perulagnan for untuk penyimpanan list makanan
    MyFile << "===    PREDIKSI DATA MAKANAN  ===\n";
    for (auto &dataMenu : daftarMenu)
    {
        i++;
        MyFile << "Nomor : " << i
               << " | " << dataMenu.nama_makanan
               << " | " << dataMenu.nomor_kantin
               << " | " << dataMenu.pemilik_kantin
               << " | " << dataMenu.tipe_makanan
               << " | Rp" << dataMenu.harga << "\n";
    }

    // tutup file
    MyFile.close();

    // pesan konfirmasi
    cout << "Data finance berhasil disimpan " << endl;
};

// method untuk upload pengeluaran harian ke database
// json FoodPlanning

// menangkap request dari curl
size_t FoodPlanning::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}
