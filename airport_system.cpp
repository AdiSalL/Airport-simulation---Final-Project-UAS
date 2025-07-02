using namespace std;
#include "library.h"
const int MAX_JADWAL = 20; // Maksimal 20 pesawat yang bisa dijadwalkan

// Variabel global untuk mengatur antrian dan nomor tiket
int head;
int tail;
int ticketCounter = 1; // Counter untuk nomor ID tiket

// Struct untuk menyimpan informasi jalur penerbangan (untuk algoritma rute tercepat)
struct Jalur
{
    string tujuan;  // Kota tujuan
    int waktu;      // Waktu tempuh dalam menit
};

// Struct untuk tiket (menggunakan linked list)
struct Tiket {
    int id;                 // ID tiket unik
    string nama_penumpang;  // Nama yang memesan tiket
    string nama_pesawat;    // Nama maskapai
    string destinasi;       // Kota tujuan
    int harga;             // Harga tiket
    Tiket* next;           // Pointer ke tiket berikutnya (linked list)
};

// Struct untuk data pesawat
struct Pesawat
{
    int id;                // ID pesawat
    string nama;           // Nama maskapai
    int jam_penerbangan;   // Jam keberangkatan (format 24 jam)
    int harga_tiket;       // Harga tiket
    string destinasi;      // Kota tujuan
};

Pesawat pesawat[MAX_JADWAL]; // Array untuk menyimpan data pesawat

// Fungsi untuk mengecek apakah tidak ada pesawat (kosong)
bool kosong() {
    if(tail == 0) {
        cout << "Tidak ada penerbangan" << endl;
        return true;
    }else {
        return false;
    }
}

// Fungsi untuk mengecek apakah bandara sudah penuh
bool penuh() {
    if(tail == MAX_JADWAL) {
        cout << "Bandara sudah penuh" << endl;
        return true;
    }else {
        return false;
    }
}

// Fungsi untuk menampilkan semua data pesawat dalam bentuk tabel
void lihatDataPesawat() {
    if(!kosong()) {
        // Menampilkan header tabel
        cout << "\n================================= DATA PENERBANGAN ====================================\n";
        for(int i = 0; i < tail; i++) {
            if (i == 0) {
                // Menampilkan judul kolom
                cout << left
                     << setw(5) << "ID"
                     << setw(25) << "Nama"
                     << setw(15) << "Jam"
                     << setw(15) << "Harga"
                     << setw(20) << "Destinasi" << endl;
                cout << string(80, '-') << endl; // Garis pemisah
            }
            // Menampilkan data setiap pesawat
            cout << left
                 << setw(5) << pesawat[i].id
                 << setw(25) << pesawat[i].nama
                 << setw(15) << (to_string(pesawat[i].jam_penerbangan) + " WIB")
                 << setw(15) << pesawat[i].harga_tiket
                 << setw(20) << pesawat[i].destinasi << endl;
        }
    }else {
        cout << "***Pesawat Masih Kosong***" << endl;
    }
}

// Fungsi untuk menambah pesawat baru ke dalam jadwal
void masukkanPesawat(string nama, int jam_penerbangan, int harga, string destinasi) {
    if(penuh()) {
        return; // Keluar jika bandara penuh
    }
    // Mengisi data pesawat baru
    pesawat[tail].nama = nama;
    pesawat[tail].jam_penerbangan = jam_penerbangan;
    pesawat[tail].harga_tiket = harga;
    pesawat[tail].destinasi = destinasi;
    pesawat[tail].id = tail + 1; // ID otomatis
    tail++; // Menambah jumlah pesawat
    cout << "Pesawat berhasil ditambahkan!" << endl;
}

// Fungsi untuk memberangkatkan pesawat (pesawat dengan jam keberangkatan tercepat)
void berangkatKanPesawat() {
    if(kosong()) {
        return;
    }
    
// Sorting pesawat berdasarkan jam keberangkatan menggunakan insertion sort
for(int i = 1; i < tail; i++) {
    // Ambil elemen saat ini sebagai 'key' yang akan disisipkan ke posisi yang tepat
    Pesawat key = pesawat[i];

    // Mulai membandingkan dengan elemen sebelumnya di bagian array yang sudah terurut
    int j = i - 1;

    // Selama posisi valid (j lebih dari atau sama dengan 0) dan jam keberangkatan sebelumnya lebih besar dari 'key'
    while (j >= 0 && pesawat[j].jam_penerbangan > key.jam_penerbangan) {
        // Geser elemen yang lebih besar ke kanan untuk memberi ruang bagi 'key'
        pesawat[j + 1] = pesawat[j];
        j--; // Pindah ke elemen sebelumnya kalau j nya 0 diatas maka ga akan berjalan maka j >= 0 diatas maka dia buat ngecek kalo udah sampai ke ujung 
    }

    // Sisipkan 'key' ke posisi yang telah ditemukan
    pesawat[j + 1] = key;
}

    // Memberangkatkan pesawat pertama (jam tercepat)
    cout << pesawat[0].nama << " dengan tujuan " << pesawat[0].destinasi
         << " telah diberangkatkan pada " << pesawat[0].jam_penerbangan << " WIB" << endl;
    
    // Menghapus pesawat yang sudah diberangkatkan dari array
    for(int i = 0; i < tail - 1; i++) {
        pesawat[i] = pesawat[i + 1];
        pesawat[i].id = i + 1; // Update ID
    }
    tail--; // Mengurangi jumlah pesawat
}

// Fungsi untuk mencari pesawat berdasarkan nama atau destinasi
void cariPesawat(string target, int tipe) {
    if(kosong()) {
        return;
    }
    bool ditemukan = false;
    switch (tipe) {
    case 1: // Cari berdasarkan nama maskapai
        for(int i = 0; i < tail; i++) {
            if(pesawat[i].nama == target) {
                // Menampilkan detail pesawat yang ditemukan
                cout << "Pesawat ditemukan dengan data: " << endl;
                cout << "ID: " << pesawat[i].id << endl;
                cout << "Nama: " << pesawat[i].nama << endl;
                cout << "Jam Penerbangan: " << pesawat[i].jam_penerbangan << "WIB" << endl;
                cout << "Harga Tiket: " << pesawat[i].harga_tiket << endl;
                cout << "Destinasi Pesawat: " << pesawat[i].destinasi << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
                cout << "Pesawat tidak ditemukan." << endl;
        }
        break;
    case 2: // Cari berdasarkan destinasi
      for(int i = 0; i < tail; i++) { // Melakukan iterasi dari indeks 0 sampai sebelum tail
    if(pesawat[i].destinasi == target) { // Mengecek apakah destinasi pesawat pada indeks ke-i sama dengan target
        cout << "Pesawat ditemukan dengan data: " << endl; // Menampilkan pesan bahwa pesawat ditemukan
        cout << "ID: " << pesawat[i].id << endl; // Menampilkan ID pesawat
        cout << "Nama: " << pesawat[i].nama << endl; // Menampilkan nama pesawat
        cout << "Jam Penerbangan: " << pesawat[i].jam_penerbangan << "WIB" << endl; // Menampilkan jam penerbangan pesawat
        cout << "Harga Tiket: " << pesawat[i].harga_tiket << endl; // Menampilkan harga tiket pesawat
        cout << "Destinasi Pesawat: " << pesawat[i].destinasi << endl; // Menampilkan destinasi pesawat
        cout << "-------------------------\n"; // Menampilkan garis pemisah
        ditemukan = true; // Menandai bahwa pesawat telah ditemukan
    }
}
if (!ditemukan) { // Jika tidak ada pesawat yang ditemukan
    cout << "Pesawat tidak ditemukan." << endl; // Menampilkan pesan bahwa pesawat tidak ditemukan
}
break; // Keluar dari blok switch/case atau loop (tergantung konteks)
    default:
        cout << "Pilihan tidak valid" << endl;
        break;
    }
}

// Fungsi untuk mengurutkan pesawat berdasarkan kriteria tertentu
void sortingPesawat(int tipe) {
    if(kosong()) {
        return;
    }
    switch (tipe) {
    case 1: // Urutkan berdasarkan harga termurah (ascending)
        for(int i = 1; i < tail; i++) {
            Pesawat key = pesawat[i];
            int j = i - 1;
            while (j >= 0 && pesawat[j].harga_tiket > key.harga_tiket) {
                pesawat[j + 1] = pesawat[j];
                j--;
            }
            pesawat[j + 1] = key;
        }
        cout << "\nPesawat diurutkan berdasarkan harga termurah:\n";
        lihatDataPesawat();
        break;
    case 2: // Urutkan berdasarkan harga termahal (descending)
        for(int i = 1; i < tail; i++) {
            Pesawat key = pesawat[i];
            int j = i - 1;
            while (j >= 0 && pesawat[j].harga_tiket < key.harga_tiket) {
                pesawat[j + 1] = pesawat[j];
                j--;
            }
            pesawat[j + 1] = key;
        }
        cout << "\nPesawat diurutkan berdasarkan harga termahal:\n";
        lihatDataPesawat();
        break;
    case 3: // Urutkan berdasarkan jam keberangkatan tercepat
        for(int i = 1; i < tail; i++) {
            Pesawat key = pesawat[i];
            int j = i - 1;
            while (j >= 0 && pesawat[j].jam_penerbangan > key.jam_penerbangan) {
                pesawat[j + 1] = pesawat[j];
                j--;
            }
            pesawat[j + 1] = key;
        }
        cout << "\nPesawat diurutkan berdasarkan jam keberangkatan tercepat:\n";
        lihatDataPesawat();
        break;
    default:
        cout << "Pilihan tidak valid" << endl;
        break;
    }
}

// Fungsi untuk memesan tiket (menggunakan linked list)
// Dengan mengambil reference ke pointer agar bisa mengubah alamat pointer dari luar fungsi
void pesanTiket(Tiket*& tiket) {
    if(kosong()) {
        return;
    }
    string namaPenumpang;
    int idPesawat;
    double bayar;
    
    lihatDataPesawat(); // Tampilkan daftar pesawat
    cout << "\nMasukkan ID pesawat yang ingin dipesan: ";
    cin >> idPesawat;
    cin.ignore();
    
    // Validasi ID pesawat
    if(idPesawat <= 0 || idPesawat > tail) {
        cout << "Pesawat tidak ada ID Lain Yang Ada Dong" << endl;
        return;
    }
    
    cout << "Masukkan nama penumpang: ";
    getline(cin, namaPenumpang);
    
    cout << "Masukkan Uang Pembayaran" << endl;
    cin >> bayar;

    Pesawat p = pesawat[idPesawat - 1]; // Ambil data pesawat yang dipilih
    
    // Validasi pembayaran
    if(bayar < p.harga_tiket) {
        cout << "Maaf uang anda kurang" << endl;
        return;
    }
    
    // Buat tiket baru dan tambahkan ke linked list
    Tiket* baru = new Tiket;
    baru->id = ticketCounter++; // ID tiket otomatis
    baru->nama_penumpang = namaPenumpang;
    baru->nama_pesawat = p.nama;
    baru->destinasi = p.destinasi;
    baru->harga = p.harga_tiket;
    baru->next = tiket; // Tambahkan di depan linked list
    tiket = baru;
    
    // Tampilkan konfirmasi pemesanan
    cout << "\n=== TIKET BERHASIL DIPESAN! ===\n";
    cout << "ID Tiket: " << baru->id << endl;
    cout << "Nama Penumpang: " << namaPenumpang << endl;
    cout << "Pesawat: " << p.nama << endl;
    cout << "Destinasi: " << p.destinasi << endl;
    cout << "Harga Tiket: " << p.harga_tiket << endl;
}

// Fungsi untuk menampilkan semua tiket yang sudah dipesan
void lihatSemuaTiket(Tiket* tiket) {
    if(tiket == nullptr) {
        cout << "Belum ada tiket yang dipesan." << endl;
        return;
    }
    cout << "\n=== DAFTAR SEMUA TIKET ===\n";
    Tiket* current = tiket;
    // Traverse linked list untuk menampilkan semua tiket
    while (current != nullptr) {
        cout << "ID Tiket: " << current->id << endl;
        cout << "Nama Penumpang: " << current->nama_penumpang << endl;
        cout << "Nama Pesawat: " << current->nama_pesawat << endl;
        cout << "Destinasi: " << current->destinasi << endl;
        cout << "Harga: " << current->harga << endl;
        cout << "-------------------------\n";
        current = current->next;
    }
}

// Fungsi untuk menghapus tiket berdasarkan ID
void hapusTiket(Tiket*& tiket, int target) {
    if(tiket == nullptr) {
        cout << "Tidak ada tiket yang bisa dihapus, masih kosong" << endl;
        return;
    }
    
    Tiket* current = tiket;
    Tiket* prev = nullptr;
    
    // Jika tiket yang akan dihapus adalah tiket pertama
    if(current->id == target) {
        tiket = current->next;
        delete current;
        cout << "Tiket Dengan Id " << target << " berhasil dihapus " << endl;
        return;
    }
    
    // Cari tiket yang akan dihapus
    while (current != nullptr && current->id != target)
    {
        prev = current;
        current = current->next;
    }
    
    // Jika tiket tidak ditemukan
    if(current == nullptr) {
        cout << "Tiket dengan ID " << target << " tidak ditemukan.\n";
        return;
    }
    
    // Hapus tiket dari linked list
    prev->next = current->next;
    delete current;
    cout << "Tiket dengan ID " << target << " berhasil dihapus.\n";
}

// Map untuk menyimpan graf jalur penerbangan (untuk algoritma Dijkstra)
unordered_map<string, vector<Jalur>> jalurPesawat;

// Fungsi untuk menambah jalur penerbangan (graf tidak berarah)
void tambahJalur(string dari, string ke, int waktu) {
    jalurPesawat[dari].push_back({ke, waktu});
    jalurPesawat[ke].push_back({dari, waktu}); // Jalur bolak-balik
}

// Fungsi untuk mencari rute tercepat menggunakan algoritma Dijkstra
void tampilkanRuteTercepat(string asal, string tujuan) {
    unordered_map<string, int> jarak;        // Menyimpan jarak terpendek ke setiap kota
    unordered_map<string, string> sebelumnya; // Menyimpan kota sebelumnya untuk merekonstruksi path
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> antrian; // Min-heap
    
    // Inisialisasi jarak semua kota ke infinity
    for (auto& kota : jalurPesawat) {
        jarak[kota.first] = INT_MAX;
    }
    
    jarak[asal] = 0; // Jarak ke kota asal = 0
    antrian.push({0, asal});
    
    // Algoritma Dijkstra
    while (!antrian.empty()) {
        pair<int, string> sekarang = antrian.top();
        antrian.pop();
        int waktuSaatIni = sekarang.first;
        string kotaSaatIni = sekarang.second;
        
        if (kotaSaatIni == tujuan) {
            break; // Sudah sampai tujuan
        }
        
        // Periksa semua tetangga dari kota saat ini
        for (Jalur& tetangga : jalurPesawat[kotaSaatIni]) {
            int waktuBaru = waktuSaatIni + tetangga.waktu;
            if (waktuBaru < jarak[tetangga.tujuan]) {
                jarak[tetangga.tujuan] = waktuBaru;
                sebelumnya[tetangga.tujuan] = kotaSaatIni;
                antrian.push({waktuBaru, tetangga.tujuan});
            }
        }
    }
    
    // Jika tidak ada jalur ke tujuan
    if (jarak[tujuan] == INT_MAX) {
        cout << "Tidak ada jalur dari " << asal << " ke " << tujuan << endl;
        return;
    }
    
    // Rekonstruksi rute dari tujuan ke asal
    vector<string> rute;
    string kota = tujuan;
    while (kota != asal) {
        rute.push_back(kota);
        kota = sebelumnya[kota];
    }
    rute.push_back(asal);
    reverse(rute.begin(), rute.end()); // Balik urutan untuk menampilkan asal -> tujuan
    
    // Tampilkan rute tercepat
    cout << "Rute tercepat dari " << asal << " ke " << tujuan << ":\n";
    for (int i = 0; i < rute.size(); i++) {
        cout << rute[i];
        if (i != rute.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    // Tampilkan pesawat yang tersedia ke tujuan
    for(int i = 0; i < tail; i++) {
        if(pesawat[i].destinasi == tujuan) {
            cout << "Berikut pesawat yang dapat anda pesan" << endl;
            cout << "ID: " << pesawat[i].id << endl;
            cout << "Nama: " << pesawat[i].nama << endl;
            cout << "Jam Penerbangan: " << pesawat[i].jam_penerbangan << endl;
            cout << "Harga Tiket: " << pesawat[i].harga_tiket << endl;
            cout << "Destinasi Pesawat: " << pesawat[i].destinasi << endl;
        }
    }
    cout << "\nTotal waktu perjalanan: " << jarak[tujuan] << " menit\n";
}

// Fungsi inisialisasi - mengisi data awal pesawat dan jalur penerbangan
void init(Tiket*& tiket) {
    head = 0;
    tail = 0;
    tiket = nullptr;
    
    // Menambahkan data pesawat awal
    masukkanPesawat("Garuda Indonesia", 1200, 1200000, "Jakarta");
    masukkanPesawat("Citilink", 1030, 950000, "Surabaya");
    masukkanPesawat("Air Asia", 1000, 1300000, "Denpasar");
    masukkanPesawat("Lion Air", 1330, 1100000, "Medan");
    masukkanPesawat("Sriwijaya Air", 1400, 1150000, "Makassar");
    masukkanPesawat("Batik Air", 900, 1000000, "Yogyakarta");
    masukkanPesawat("Wings Air", 1230, 900000, "Balikpapan");
    masukkanPesawat("Super Air Jet", 1430, 950000, "Pontianak");
    masukkanPesawat("NAM Air", 1530, 1050000, "Padang");
    masukkanPesawat("Pelita Air", 1630, 1200000, "Pekanbaru");
    masukkanPesawat("TransNusa", 1730, 950000, "Semarang");
    
    // Menambahkan jalur penerbangan dengan waktu tempuh (dalam menit)
    tambahJalur("Jakarta", "Surabaya", 85);
    tambahJalur("Jakarta", "Denpasar", 110);
    tambahJalur("Jakarta", "Medan", 135);
    tambahJalur("Jakarta", "Makassar", 140);
    tambahJalur("Jakarta", "Yogyakarta", 60);
    tambahJalur("Jakarta", "Balikpapan", 110);
    tambahJalur("Jakarta", "Pontianak", 80);
    tambahJalur("Jakarta", "Padang", 95);
    tambahJalur("Jakarta", "Pekanbaru", 90);
    tambahJalur("Jakarta", "Semarang", 60);
    tambahJalur("Surabaya", "Denpasar", 50);
    tambahJalur("Surabaya", "Makassar", 90);
    tambahJalur("Surabaya", "Balikpapan", 80);
    tambahJalur("Surabaya", "Yogyakarta", 55);
    tambahJalur("Denpasar", "Makassar", 90);
    tambahJalur("Denpasar", "Yogyakarta", 80);
    tambahJalur("Medan", "Pekanbaru", 65);
    tambahJalur("Medan", "Padang", 70);
    tambahJalur("Makassar", "Balikpapan", 65);
    tambahJalur("Yogyakarta", "Semarang", 40);
    tambahJalur("Yogyakarta", "Balikpapan", 90);
}

// Fungsi main - program utama
int main() {
    Tiket* tiket = nullptr; // Pointer untuk linked list tiket
    string nama, destinasi;
    int harga, jam;
    string targetCari;
    int cariMenu;
    int sortingMenu;
    
    init(tiket); // Inisialisasi data awal
    
    int pilihan = 0;
    // Loop menu utama
    while (pilihan != 10) {
        system("cls"); // Clear screen
        
        // Tampilkan menu utama
        cout << "Selamat datang di aplikasi pengelolaan bandara AMIKOM YOGYAKARTA" << endl;
        cout << "Bandara ini menyediakan layanan penerbangan antar provinsi di indonesia" << endl;
        cout << "___________________________________________________________________________________" << endl;
        cout << endl;
        cout << "1. Lihat semua pesawat " << endl;
        cout << "2. Tambah Pesawat " << endl;
        cout << "3. Cari Pesawat" << endl;
        cout << "4. Urutkan Pesawat" << endl;
        cout << "5. Mulai Penerbangan Pesawat" << endl;
        cout << "6. Pesan Tiket" << endl;
        cout << "7. Lihat Semua Tiket" << endl;
        cout << "8. Hapus Tiket" << endl;
        cout << "9. Rekomendasi Rute Penerbangan" << endl;
        cout << "10. Keluar Aplikasi" << endl;
        cout << "____________________________" << endl;
        cout << endl;
        cout << "Masukkan Pilihan: " << endl;
        cin >> pilihan;
        
        // Switch case untuk menangani pilihan menu
        switch (pilihan) {
            case 1: // Lihat semua pesawat
                lihatDataPesawat();
                break;
            case 2: // Tambah pesawat baru
                cout << "Masukkan nama maskapai: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan jam keberangkatan [0000 dibaca 00:00]: ";
                cin >> jam;
                cout << "Masukkan harga tiket: ";
                cin >> harga;
                cout << "Masukkan tujuan destinasi: ";
                cin.ignore();
                getline(cin, destinasi);
                masukkanPesawat(nama, jam, harga, destinasi);
                break;
            case 3: // Cari pesawat
                cout << "Cari Pesawat Berdasarkan:" << endl;
                cout << "1. Nama maskapai" << endl;
                cout << "2. Destinasi pesawat" << endl;
                cout << "Masukkan pilihan: ";
                cin >> cariMenu;
                cout << "Cari data: ";
                cin.ignore();
                getline(cin, targetCari);
                if(targetCari == "") {
                    cout << "Input tidak boleh kosong!" << endl;
                    break;
                }
                cariPesawat(targetCari, cariMenu);
                break;
            case 4: // Urutkan pesawat
                cout << "Urutkan pesawat berdasarkan" << endl;
                cout << "1. Termurah" << endl;
                cout << "2. Termahal" << endl;
                cout << "3. Keberangkatan paling awal" << endl;
                cout << "Masukkan pilihan: ";
                cin >> sortingMenu;
                sortingPesawat(sortingMenu);
                break;
            case 5: // Berangkatkan pesawat
                berangkatKanPesawat();
                break;
            case 6: // Pesan tiket
                pesanTiket(tiket);
                break;
            case 7: // Lihat semua tiket
                cout << endl;
                lihatSemuaTiket(tiket);
                break;
            case 8: // Hapus tiket
                int idTarget;
                lihatSemuaTiket(tiket);
                cout << "Masukkan ID tiket yang ingin dihapus" << endl;
                cin >> idTarget;
                hapusTiket(tiket, idTarget);
                break;
            case 9: // Rekomendasi rute penerbangan
                {
                    string dari, ke;
                    cout << "Dari Asal" << endl;
                    cin.ignore();
                    getline(cin, dari);
                    cout << "Ke destinasi" << endl;
                    getline(cin, ke);
                    tampilkanRuteTercepat(dari, ke);
                }
                break;
            case 10: // Keluar aplikasi
                cout << "Keluar dari aplikasi..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
        
        // Pause untuk melihat hasil sebelum kembali ke menu
        if (pilihan != 10) {
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore();
            cin.get();
        } else {
            break;
        }
    }
    return 0;
}
