// Deklrasi library yang akan digunakan
#define _HAS_STD_BYTE 0
#define NOMINMAX
#include <windows.h>

#include "FoodPlanner.h"

// method yang digunakan untuk mengakses tanggal =
string FoodPlanning::getDay()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // variabel untuk menampung hasil
    char buffer[80];

    // panggil fungsi bawaan ctime
    strftime(buffer, 80, "%d-%m-%Y", ltm);

    return string(buffer);
}

// method untuk check data planner tersimpan berdasarkan tanggal
void FoodPlanning::getSavedPlanner(string day, string month, string year)
{
    // check file
    string inputTanggalUser = day + '-' + month + '-' + year;
    string isiText;
    bool statusFileDitemukan = false;

    // variabel nama file
    // digunakan untuk penyimpanan file berdasarkan tanggal atau per minggu
    // string namaFile = "DataFoodPlannerMahasiswa_";
    // string cariTanggalByUser = day + "-" + month + "-" + year + ".txt";
    // string namaFileTanggal = namaFile + cariTanggalByUser;

    // buka file
    // ifstream MyFile(namaFileTanggal); // digunakan untuk yang function atas

    // membuka file dari path yang sudha ditentukan
    ifstream MyFile(pathPlanner);

    if (!MyFile)
    {
        cout << "File Tidak ditemukan" << endl;
        return;
    }

    // perulangan ini digunakan untuk function file yang dibuat per minggu
    //  while (getline(MyFile, isiText))
    //  {
    //      // if else untuk check tanggal minggu ini :
    //      cout << isiText;
    //      system("pause"); // berhenti untuk membaca
    //      return;
    //  }

    // perulangan ini digunakan untuk function file yang dibuat dalam satu file saja
    while (getline(MyFile, isiText))
    {
        // logika if else untuk check status dulu
        if (!statusFileDitemukan)
        {
            // apakah tanggal ditemukan ?
            if (isiText.find(inputTanggalUser) != string::npos)
            {
                statusFileDitemukan = true; // ubah jadi true untuk statusnya
                cout << isiText << endl;    // tampilkan isinya
            }
        }
        else
        {
            if (isiText.find("=======BAGIAN AKHIR========") != string::npos)
            {
                cout << isiText << endl;
                break;
            }

            cout << isiText << endl;
        }
    }

    // tutup file
    MyFile.close();

    return;
}

// method berisi data untuk membuat planner
json FoodPlanning::createPlanner(string namaMahasiswa, double total_budget, int metode, double sisa_uang, string jenisMakanan, string tipeMakanan, string tipeMinuman)
{
    json dataJSON;

    // set data untuk json
    // dataJSON["id_mahasiswa"] = id_mahasiswa;
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

// method untuk mengambil data dari json dan menampilkan data ke layar
void FoodPlanning::getFoodPlanner(string &response)
{
    // get data atau respon dari json

    daftarMenu.clear(); // membersihkan vector

    // 1. Parse string response mentah ke JSON object
    json rawJSON = json::parse(response);
    json dataJSON;

    // 2. Cek apakah response berupa Array (Format n8n baru)
    // Format n8n: [ { "status": "success", ... } ]
    if (rawJSON.is_array() && !rawJSON.empty())
    {
        dataJSON = rawJSON[0]; // Ambil item pertama
    }
    else
    {
        // Fallback jika n8n mengembalikan object langsung
        dataJSON = rawJSON;
    }

    // masukkan ke rencana keuangan
    auto rk = dataJSON["rencana_keuangan"];
    pk.total_budget = rk.value("total_budget", 0.0);
    pk.saving_rate = rk.value("opsi_saving_dipilih", 0);
    pk.uang_disimpan = rk.value("nominal_disimpan", 0.0);
    pk.budget_harian = rk.value("budget_harian_makan", 0.0);

    // masukkan ke planning makanan ( HELPED BY GPT BAGIAN AUTO )
    for (auto &item : dataJSON["prediksi_menu"])
    {
        // Gunakan .value() agar aman jika ada field null/hilang
        pm.hari = item.value("hari", 0);
        pm.waktu = item.value("waktu", 0);
        pm.id_makanan = item.value("id_makanan", 0);

        pm.nama_makanan = item.value("nama_makanan", "Tanpa Nama");
        pm.nomor_kantin = item.value("nomor_kantin", "0");
        pm.pemilik_kantin = item.value("pemilik_kantin", "-");
        pm.harga = item.value("harga", "0");
        pm.tipe_makanan = item.value("tipe_makanan", "-");

        daftarMenu.push_back(pm);
    }

    // TAMPILAKN KE PENGGUNA

    int i = 1;
    string tanggal = getDay();

    cout << tanggal << endl;
    cout << "=============================================" << endl;
    cout << "----        PREDIKSI DATA KEUANGAN       ----" << endl;
    cout << "=============================================" << endl;

    cout << endl;
    cout << "--- RENCANA KEUANGAN ---" << endl;
    cout << "Total Budget : " << pk.total_budget << endl;
    cout << "Saving       : " << pk.saving_rate << endl;
    cout << "Disimpan     : " << pk.uang_disimpan << endl;
    cout << "Harian Makan : " << pk.budget_harian << endl;
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    // cout << "====   Menu minggu ini     ===" << endl;
    // for (auto &pm : daftarMenu)
    // {
    //     cout << "Nama makanan " << pm.nama_makanan
    //          << " | " << pm.tipe_makanan
    //          << " | Rp " << pm.harga
    //          << " | Kantin " << pm.nomor_kantin
    //          << " (" << pm.pemilik_kantin << ")"
    //          << endl;
    // }

    cout << "===    PREDIKSI DATA MAKANAN  ===\n";
    for (auto &pm : daftarMenu)
    {
        cout << setw(4) << i++
             << setw(25) << pm.nama_makanan
             << setw(10) << pm.nomor_kantin
             << setw(20) << pm.pemilik_kantin
             << setw(18) << pm.tipe_makanan
             << setw(10) << pm.tipe_makanan
             << endl;
    }

    cout << endl;
    cout << "=============================================" << endl;
    cout << "----           BAGIAN_AKHIR        ----" << endl;
    cout << "=============================================" << endl;
    cout << endl;
}

// method untuk simpan data ke .txt
void FoodPlanning::savePlanner()
{
    // digunakan untuk iterasi
    int i = 1;

    // buka file
    ofstream MyFile(pathPlanner, ios::app);

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
    MyFile << "=============================================\n";
    MyFile << "----        PREDIKSI DATA KEUANGAN       ----\n";
    MyFile << "=============================================\n";

    MyFile << "\n";
    MyFile << "--- RENCANA KEUANGAN ---" << "\n";
    MyFile << "Total Budget : " << pk.total_budget << "\n";
    MyFile << "Saving       : " << pk.saving_rate << "\n";
    MyFile << "Disimpan     : " << pk.uang_disimpan << "\n";
    MyFile << "Harian Makan : " << pk.budget_harian << "\n\n";
    MyFile << "\n";
    MyFile << "--------------------------------------------------\n";

    // gunakan perulagnan for untuk penyimpanan list makanan
    MyFile << "===    PREDIKSI DATA MAKANAN  ===\n";

    // set bentuk tabel
    MyFile << left
           << setw(4) << "Nomor"
           << setw(25) << "Nama Makanan"
           << setw(10) << "Nomor Kantin"
           << setw(20) << "Pemilik Kantin"
           << setw(18) << "Tipe Makanan"
           << setw(10) << "Harga Makanan"
           << "\n";

    for (auto &dataMenu : daftarMenu)
    {

        MyFile << setw(4) << i++
               << setw(25) << dataMenu.nama_makanan
               << setw(10) << dataMenu.nomor_kantin
               << setw(20) << dataMenu.pemilik_kantin
               << setw(18) << dataMenu.tipe_makanan
               << setw(10) << dataMenu.tipe_makanan
               << "\n";
    }

    MyFile << "=============================================\n";
    MyFile << "----           BAGIAN_AKHIR        ----" << "\n";
    MyFile << "=============================================\n";

    // tutup file
    MyFile.close();

    // pesan konfirmasi
    cout << "Data finance berhasil disimpan " << endl;
};

// method untuk membuat pengeluaran harian ( simpan ke .txt )
string FoodPlanning::createDailyExpenses(string deskripsiPengeluaaran, double totalUangYangDikeluarkanHariIni)
{
    // Mengambil tanggal hari ini dari backend
    string tanggal = getDay();
    string text;
    // status ditemukan
    bool statusTanggal = false;

    double totalPengeluaran = 0;

    // membaca file dulu
    ifstream readFile(pathExpenses);

    // error handling
    if (!readFile)
    {
        return "Gagal membuka file expenses";
    }

    while (getline(readFile, text))
    {
        if (text.find("Tanggal : " + tanggal) != string::npos)
        {
            statusTanggal = true;
        }

        // logika untuk mencaari bagian total pengeluaran1
        if (text.find("Total Pengeluaran : Rp") != string::npos)
        {
            // ambil total pengeluaaran terakhir
            string angka = text.substr(text.find("Rp") + 3);
            // jadikan bentuk angka ( double )
            totalPengeluaran = stod(angka);
        }
    }
    readFile.close(); // tutup file

    // // Membuka file dengan mode append (menambah tanpa menghapus yang lama)
    ofstream file(pathExpenses, ios::app);
    // error handling
    if (!file)
    {
        return "Gagal membuka file expenses. Cek 'dataFile/Expenses' sudah ada!\n";
    }

    if (statusTanggal == false)
    {
        // buat baru
        file << "\n";
        file << "---------------------------------------------\n";
        file << "Tanggal : " << tanggal << "\n";
        file << "---------------------------------------------\n";
        file << "           FILE PENGELUARAN HARI INI :         \n";
        file << "---------------------------------------------\n";
    }
    else if (statusTanggal == true)
    {
        // beri pembatas saja
        file << "---------------------------------------------\n";
    }

    // penjumlahan total :
    totalPengeluaran += totalUangYangDikeluarkanHariIni;

    // isi file
    file << "Deskripsi Pengeluaran : " << deskripsiPengeluaaran << "\n";
    file << "Pengeluaran saat ini  : " << totalUangYangDikeluarkanHariIni << "\n";
    file << "Total Pengeluaran : Rp " << fixed << setprecision(0) << totalPengeluaran << "\n";
    file << "\n";

    // tututp file
    file.close();

    return "Pengeluaran harian berhasil disimpan.\n";
}

// method untuk upload pengeluaran harian ke database
// json FoodPlanning

// menangkap request dari curl
size_t FoodPlanning::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}
