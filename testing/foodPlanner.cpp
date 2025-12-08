void FoodPlanning::getFoodPlanner(string &response)
{
    try
    {
        // === TAHAP 1: BUKA BUNGKUS DARI N8N ===
        json rawResponse = json::parse(response);
        string contentString;

        // Cek struktur respon (Array atau Object)
        if (rawResponse.is_array() && !rawResponse.empty())
        {
            if (rawResponse[0].contains("output"))
            {
                contentString = rawResponse[0]["output"].get<string>();
            }
            else
            {
                // Fallback: Coba ambil elemen array langsung jika bukan bungkus 'output'
                contentString = rawResponse[0].dump();
            }
        }
        else if (rawResponse.is_object())
        {
            if (rawResponse.contains("output"))
            {
                contentString = rawResponse["output"].get<string>();
            }
            else
            {
                // Fallback: Jika n8n mengirim object json langsung tanpa key "output"
                contentString = response;
            }
        }
        else
        {
            cerr << "[Warning] Format respon tidak dikenali. Mencoba parsing raw..." << endl;
            contentString = response;
        }

        // === TAHAP 2: SAFETY NET (PEMBERSIH MARKDOWN) ===
        // Berguna jika AI tidak sengaja mengirim ```json lagi
        size_t jsonStart = contentString.find("```json");
        if (jsonStart != string::npos)
        {
            contentString.replace(jsonStart, 7, "");
        }

        size_t codeBlockStart = contentString.find("```");
        if (codeBlockStart != string::npos && jsonStart == string::npos)
        {
            contentString.replace(codeBlockStart, 3, "");
        }

        size_t jsonEnd = contentString.rfind("```");
        if (jsonEnd != string::npos)
        {
            contentString.replace(jsonEnd, 3, "");
        }

        // === TAHAP 3: PARSE JSON DATA ASLI ===
        json dataJSON = json::parse(contentString);

        // === TAHAP 4: TAMPILKAN KE LAYAR ===
        cout << "\n=============================================" << endl;
        cout << "           HASIL RENCANA MAKANAN             " << endl;
        cout << "=============================================" << endl;

        // 1. Status
        if (dataJSON.contains("status"))
        {
            string stat = dataJSON["status"];
            cout << "Status: " << (stat == "success" ? "Berhasil" : "Gagal/Perlu Cek") << endl;
        }

        // 2. Pesan Utama
        if (dataJSON.contains("message_for_user"))
        {
            cout << "\n[PESAN AI]: " << dataJSON["message_for_user"].get<string>() << endl;
        }

        // 3. Rencana Keuangan
        if (dataJSON.contains("rencana_keuangan"))
        {
            cout << "\n[KEUANGAN]:" << endl;
            auto keuangan = dataJSON["rencana_keuangan"];

            // Menggunakan 0.0 agar support desimal/double
            cout << "- Total Budget : Rp " << (long)keuangan.value("total_budget", 0.0) << endl;
            cout << "- Saving       : " << keuangan.value("opsi_saving_dipilih", "0%")
                 << " (Rp " << (long)keuangan.value("nominal_disimpan", 0.0) << ")" << endl;
            cout << "- Uang Makan   : Rp " << (long)keuangan.value("budget_harian_makan", 0.0) << " / hari" << endl;
        }

        // 4. Rekomendasi Menu
        if (dataJSON.contains("prediksi_menu") && !dataJSON["prediksi_menu"].empty())
        {
            cout << "\n[REKOMENDASI MENU]:" << endl;
            auto prediksiMenu = dataJSON["prediksi_menu"];

            // Header Tabel Sederhana
            printf("%-5s | %-25s | %-15s | %-10s\n", "Hari", "Nama Makanan", "Kantin", "Harga");
            cout << "----------------------------------------------------------------" << endl;

            for (auto &itemMenu : prediksiMenu)
            {
                // Ambil data
                int h = itemMenu.value("hari", 0);
                string n = itemMenu.value("nama_makanan", "-");
                string k = itemMenu.value("pemilik_kantin", "-"); // Atau nama kantin
                double p = itemMenu.value("harga", 0.0);

                // Tampilkan format rapi menggunakan printf agar lurus
                // %-25s artinya string rata kiri dengan lebar 25 karakter
                printf("  %-3d | %-25s | %-15s | Rp %-8.0f\n", h, n.substr(0, 25).c_str(), k.substr(0, 15).c_str(), p);
            }
        }
        else
        {
            cout << "\n[INFO]: Data menu tidak tersedia dalam respon." << endl;
        }
        cout << "=============================================" << endl;
    }
    catch (json::parse_error &e)
    {
        cerr << "\n[ERROR] Gagal parsing JSON. Format data mungkin salah." << endl;
        cerr << "Detail: " << e.what() << endl;
    }
    catch (exception &e)
    {
        cerr << "\n[ERROR] Kesalahan Sistem: " << e.what() << endl;
    }
}