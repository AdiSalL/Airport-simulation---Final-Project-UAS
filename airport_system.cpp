#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>


using namespace std;

// Menentukan jumlah maksimal pesawat yang dapat disimpan dalam sistem bandara
const int MAX_JADWAL = 20;

// Variabel global untuk melacak posisi antrian/queue
// head: menunjuk ke bagian depan antrian (dalam implementasi ini selalu 0)
// tail: menunjuk ke posisi berikutnya yang tersedia dalam antrian (juga mewakili jumlah total pesawat)
int head;
int tail;
int ticketCounter = 1; // dipakai di pesan tiket sebagai id

// Struktur untuk menyimpan informasi pesawat
// Ini merepresentasikan setiap penerbangan/pesawat dalam sistem

struct Jalur
{
    /* data */
    string tujuan;
    int waktu;
};

// Struk untuk sistem pemesanan tiket menggunakan linked list
// Setiap node merepresentasikan satu tiket yang dipesan
struct Tiket {
    int id;                    // ID unik tiket
    string nama_penumpang;     // Nama penumpang yang memesan tiket
    string nama_pesawat;       // Nama pesawat yang dipesan
    string destinasi;          // Tujuan penerbangan
    int harga;                 // Harga tiket
    Tiket* next;              // Pointer ke tiket berikutnya dalam linked list
};


struct Pesawat
{
    int id;                    // Pengenal unik untuk setiap pesawat
    string nama;               // Nama maskapai/pesawat
    int jam_penerbangan;       // Waktu keberangkatan (disimpan sebagai integer, misal: 1030 untuk jam 10:30)
    int harga_tiket;          // Harga tiket
    string destinasi;
};


Pesawat pesawat[MAX_JADWAL]; //deklarasi array of struct untuk menyimpan pesawat
//Graph data jalur pesawat
unordered_map<string, vector<Jalur>> jalurPesawat;  // simpan jalur pesawat pada edge tertentu

//Disini graph dipakai untuk menghubungkan dari asal mana dan akan kemana
void tambahJalur(string dari, string ke, int waktu) {
    jalurPesawat[dari].push_back({ke, waktu});
    jalurPesawat[ke].push_back({dari, waktu});
}

// Menampilkan rute tercepat dari asal ke tujuan menggunakan algoritma Dijkstra
void tampilkanRuteTercepat(string asal, string tujuan) {
    // Map untuk menyimpan jarak terpendek dari asal ke setiap kota
    unordered_map<string, int> jarak;

    // Map untuk menyimpan kota sebelumnya (untuk rekonstruksi rute akhir)
    unordered_map<string, string> sebelumnya;

    // Priority queue (min-heap) untuk memilih kota dengan waktu tempuh terkecil
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> antrian;

    // Inisialisasi semua jarak ke tak hingga (belum diketahui)
    for (auto& kota : jalurPesawat) {
        jarak[kota.first] = INT_MAX;
    }

    // Jarak dari kota asal ke dirinya sendiri = 0
    jarak[asal] = 0;
    antrian.push({0, asal}); // {waktu tempuh, nama kota}

    // Selama antrian masih ada (ada kota yang belum dikunjungi)
    while (!antrian.empty()) {
        pair<int, string> sekarang = antrian.top(); // Ambil kota dengan waktu terkecil
        antrian.pop(); // Hapus dari antrian

        int waktuSaatIni = sekarang.first;    // Total waktu tempuh sejauh ini
        string kotaSaatIni = sekarang.second; // Nama kota saat ini

        if (kotaSaatIni == tujuan) { // Jika sudah sampai tujuan, hentikan
            break;
        }

        // Periksa semua tetangga dari kota saat ini
        for (Jalur& tetangga : jalurPesawat[kotaSaatIni]) {
            int waktuBaru = waktuSaatIni + tetangga.waktu; // Total waktu jika lewat tetangga ini

            // Jika rute ini lebih cepat, perbarui data
            if (waktuBaru < jarak[tetangga.tujuan]) {
                jarak[tetangga.tujuan] = waktuBaru;
                sebelumnya[tetangga.tujuan] = kotaSaatIni; // kota sebelumnya
                antrian.push({waktuBaru, tetangga.tujuan});
            }
        }
    }

    // Jika jarak ke tujuan tetap tak hingga, tidak ada jalur
    if (jarak[tujuan] == INT_MAX) {
        cout << "Tidak ada jalur dari " << asal << " ke " << tujuan << endl;
        return;
    }

    // Rekonstruksi rute dari tujuan ke asal
    vector<string> rute;
    string kota = tujuan;

    // Telusuri kembali dari tujuan ke asal
    while (kota != asal) {
        rute.push_back(kota);
        kota = sebelumnya[kota]; // ambil kota sebelumnya
    }
    rute.push_back(asal);

    // Balik rutenya karena dari belakang
    reverse(rute.begin(), rute.end());

    // Cetak hasil rute dan total waktu
    cout << "Rute tercepat dari " << asal << " ke " << tujuan << ":\n";
    for (int i = 0; i < rute.size(); i++) {
        cout << rute[i];
        if (i != rute.size() - 1) cout << " -> ";
    }
    cout << endl;
    for(int i = 0; i <= tail; i++) {
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


// Fungsi untuk menginisialisasi sistem antrian pesawat
// Mengatur nilai awal head dan tail ke 0 (antrian kosong)
// Parameter: array pesawat dan pointer tiket (pass by reference)

// Fungsi untuk mengecek apakah antrian pesawat kosong atau tidak
// Return: true jika kosong, false jika ada pesawat
// Parameter: array pesawat
bool kosong() {
    if(tail == 0) {           // Jika tail = 0, berarti tidak ada pesawat dalam antrian
        cout << "Tidak ada penerbangan" << endl;
        return true;
    }else {
        return false;
    }
}

// Fungsi untuk mengecek apakah antrian pesawat sudah penuh atau belum
// Return: true jika penuh, false jika masih ada tempat
// Parameter: array pesawat
bool penuh() {
    if(tail == MAX_JADWAL) {  // Jika tail sama dengan batas maksimal, berarti penuh
        cout << "Bandara sudah penuh" << endl;
        return true;
    }else {
        return false;
    }
}

// Fungsi untuk menampilkan semua data penerbangan pesawat yang tersedia
// Melakukan iterasi melalui seluruh array pesawat dari index 0 sampai tail-1
// Parameter: array pesawat
void lihatDataPesawat() {
    if(!kosong()) {    // Jika antrian tidak kosong
        cout << "\n=== DATA PENERBANGAN ===\n";
        // Melakukan perulangan untuk menampilkan semua pesawat
        for(int i = 0; i < tail; i++) {
            cout << "ID: " << pesawat[i].id << endl;
            cout << "Nama: " << pesawat[i].nama << endl;
            cout << "Jam Penerbangan: " << pesawat[i].jam_penerbangan << " WIB"<< endl;
            cout << "Harga Tiket: " << pesawat[i].harga_tiket << endl;
            cout << "Destinasi Pesawat: " << pesawat[i].destinasi << endl;
            cout << "-------------------------\n";
        }
    }else {
        cout << "***Pesawat Masih Kosong***" << endl;
    }
}

// Fungsi untuk menambahkan pesawat baru ke dalam antrian
// Menggunakan konsep enqueue - menambah elemen di bagian belakang antrian
// Parameter: array pesawat, nama maskapai, jam penerbangan, harga tiket, destinasi
void masukkanPesawat(string nama, int jam_penerbangan, int harga, string destinasi) {
    if(penuh()) {      // Cek apakah antrian sudah penuh
        return;               // Jika penuh, keluar dari fungsi
    }

    // Mengisi data pesawat baru pada posisi tail
    pesawat[tail].nama = nama;
    pesawat[tail].jam_penerbangan = jam_penerbangan;
    pesawat[tail].harga_tiket = harga;
    pesawat[tail].destinasi = destinasi;
    pesawat[tail].id = tail + 1;  // ID dimulai dari 1, bukan 0
    tail++;                   // Increment tail untuk menunjuk ke posisi berikutnya
    cout << "Pesawat berhasil ditambahkan!" << endl;
}

void init(Tiket*& tiket) {
    head = 0;                 // Mengatur posisi depan antrian ke 0
    tail = 0;                 // Mengatur posisi belakang antrian ke 0
    tiket = nullptr;          // Menginisialisasi pointer tiket ke null

    // Inisialisasi data pesawat sesuai dengan destinasi dari data graph di bawahnya
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

    // Data rute bandara Indonesia beserta waktu tempuh rata-rata (dalam menit)
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


// Fungsi untuk memberangkatkan pesawat (dequeue operation)
// Mengurutkan pesawat berdasarkan jam keberangkatan, lalu memberangkatkan yang paling awal
// Parameter: array pesawat
void berangkatKanPesawat() {
    if(kosong()) {     // Cek apakah ada pesawat dalam antrian
        return;               // Jika kosong, keluar dari fungsi
    }
    
    // Mengurutkan pesawat berdasarkan jam penerbangan menggunakan insertion sort
    // Sorting dilakukan untuk memastikan pesawat yang berangkat paling awal di posisi pertama
    for(int i = 1; i < tail; i++) {           // Mulai dari index 1 karena elemen pertama sudah dianggap terurut
        Pesawat key = pesawat[i];             // Simpan data pesawat saat ini sebagai key
        int j = i - 1;                        // Mulai perbandingan dari elemen sebelumnya

        // Bandingkan key dengan elemen-elemen sebelumnya
        // Pindahkan elemen yang jam penerbangannya lebih besar ke kanan
        while (j >= 0 && pesawat[j].jam_penerbangan > key.jam_penerbangan) {
            pesawat[j + 1] = pesawat[j];      // Geser elemen ke kanan
            j--;                              // Pindah ke elemen sebelumnya
        }
        pesawat[j + 1] = key;                 // Tempatkan key pada posisi yang tepat
    }
    
    // Memberangkatkan pesawat pertama (yang paling awal jadwal keberangkatannya)
    cout << pesawat[0].nama << " dengan tujuan " << pesawat[0].destinasi 
         << " telah diberangkatkan pada " << pesawat[0].jam_penerbangan << " WIB" << endl;
    
    // Menggeser semua pesawat ke kiri untuk menghapus pesawat pertama (dequeue)
    for(int i = 0; i < tail - 1; i++) {
        pesawat[i] = pesawat[i + 1];          // Pindahkan data pesawat
        pesawat[i].id = i + 1;  // Update ID agar tetap berurutan               
    }                           
    tail--;     // Kurangi jumlah pesawat dalam antrian    
}

// Fungsi untuk mencari pesawat berdasarkan kriteria tertentu (searching)
// Menggunakan linear search untuk mencari pesawat
// Parameter: array pesawat, string target pencarian, tipe pencarian (1=nama, 2=destinasi)
void cariPesawat(string target, int tipe) {
    if(kosong()) {     // Cek apakah ada pesawat dalam sistem
        return;               // Jika kosong, keluar dari fungsi
    }
    
    bool ditemukan = false;   // Flag untuk menandai apakah pesawat ditemukan
    
    switch (tipe) {
    case 1:                   // Pencarian berdasarkan nama maskapai
        // Linear search melalui seluruh array pesawat
        for(int i = 0; i < tail; i++) {
            if(pesawat[i].nama == target) {   // Bandingkan nama dengan target
                cout << "Pesawat ditemukan dengan data: " << endl;
                // Tampilkan semua informasi pesawat yang ditemukan
                cout << "ID: " << pesawat[i].id << endl;
                cout << "Nama: " << pesawat[i].nama << endl;
                cout << "Jam Penerbangan: " << pesawat[i].jam_penerbangan << endl;
                cout << "Harga Tiket: " << pesawat[i].harga_tiket << endl;
                cout << "Destinasi Pesawat: " << pesawat[i].destinasi << endl; 
                ditemukan = true;
            }
        }
        if (!ditemukan) {     // Jika tidak ditemukan setelah seluruh pencarian
                cout << "Pesawat tidak ditemukan." << endl;
        }
        break;
        
    case 2:                   // Pencarian berdasarkan destinasi
        // Linear search melalui seluruh array pesawat
        for(int i = 0; i < tail; i++) {
            if(pesawat[i].destinasi == target) { // Bandingkan destinasi dengan target
                cout << "Pesawat ditemukan dengan data: " << endl;
                // Tampilkan semua informasi pesawat yang ditemukan
                cout << "ID: " << pesawat[i].id << endl;
                cout << "Nama: " << pesawat[i].nama << endl;
                cout << "Jam Penerbangan: " << pesawat[i].jam_penerbangan << endl;
                cout << "Harga Tiket: " << pesawat[i].harga_tiket << endl;
                cout << "Destinasi Pesawat: " << pesawat[i].destinasi << endl;
                cout << "-------------------------\n";
                ditemukan = true;
                // Tidak ada break di sini karena bisa ada beberapa pesawat dengan destinasi sama
            }
        }
        if (!ditemukan) {     // Jika tidak ditemukan setelah seluruh pencarian
            cout << "Pesawat tidak ditemukan." << endl;
        }
        break;
        
    default:                  // Jika pilihan tidak valid
        cout << "Pilihan tidak valid" << endl;
        break;
    }
}

// Fungsi untuk mengurutkan pesawat berdasarkan kriteria tertentu (sorting)
// Menggunakan algoritma insertion sort untuk mengurutkan data
// Parameter: array pesawat, tipe pengurutan (1=termurah, 2=termahal, 3=keberangkatan tercepat)
void sortingPesawat(int tipe) {
    if(kosong()) {     // Cek apakah ada pesawat dalam sistem
        return;               // Jika kosong, keluar dari fungsi
    }
    
    switch (tipe) {
    case 1:                   // Urutkan berdasarkan harga tiket termurah (ascending)
        // Implementasi insertion sort
        for(int i = 1; i < tail; i++) {       // Mulai dari index 1
            Pesawat key = pesawat[i];         // Simpan data pesawat saat ini
            int j = i - 1;                    // Index elemen sebelumnya

            // Bandingkan dan geser elemen yang harganya lebih mahal ke kanan
            while (j >= 0 && pesawat[j].harga_tiket > key.harga_tiket) {
                pesawat[j + 1] = pesawat[j];  // Geser elemen ke kanan
                j--;                          // Pindah ke elemen sebelumnya
            }
            pesawat[j + 1] = key;             // Tempatkan key pada posisi yang tepat
        }
        cout << "\nPesawat diurutkan berdasarkan harga termurah:\n";
        lihatDataPesawat();            // Tampilkan hasil pengurutan
        break;
        
    case 2:                   // Urutkan berdasarkan harga tiket termahal (descending)
        // Implementasi insertion sort
        for(int i = 1; i < tail; i++) {       // Mulai dari index 1
            Pesawat key = pesawat[i];         // Simpan data pesawat saat ini
            int j = i - 1;                    // Index elemen sebelumnya

            // Bandingkan dan geser elemen yang harganya lebih murah ke kanan
            while (j >= 0 && pesawat[j].harga_tiket < key.harga_tiket) {
                pesawat[j + 1] = pesawat[j];  // Geser elemen ke kanan
                j--;                          // Pindah ke elemen sebelumnya
            }
            pesawat[j + 1] = key;             // Tempatkan key pada posisi yang tepat
        }
        cout << "\nPesawat diurutkan berdasarkan harga termahal:\n";
        lihatDataPesawat();            // Tampilkan hasil pengurutan
        break;
        
    case 3:                   // Urutkan berdasarkan keberangkatan paling awal (ascending)
        // Implementasi insertion sort
        for(int i = 1; i < tail; i++) {       // Mulai dari index 1
            Pesawat key = pesawat[i];         // Simpan data pesawat saat ini
            int j = i - 1;                    // Index elemen sebelumnya

            // Bandingkan dan geser elemen yang jam keberangkatannya lebih siang ke kanan
            while (j >= 0 && pesawat[j].jam_penerbangan > key.jam_penerbangan) {
                pesawat[j + 1] = pesawat[j];  // Geser elemen ke kanan
                j--;                          // Pindah ke elemen sebelumnya
            }
            pesawat[j + 1] = key;             // Tempatkan key pada posisi yang tepat
        }
        cout << "\nPesawat diurutkan berdasarkan jam keberangkatan tercepat:\n";
        lihatDataPesawat();            // Tampilkan hasil pengurutan
        break;
        
    default:                  // Jika pilihan tidak valid
        cout << "Pilihan tidak valid" << endl;
        break;
    }
}

// Fungsi untuk memesan tiket pesawat
// Menggunakan linked list untuk menyimpan data tiket yang dipesan
// Parameter: array pesawat, pointer tiket (pass by reference untuk mengubah head linked list)
void pesanTiket(Tiket*& tiket) {
    if(kosong()) {     // Cek apakah ada pesawat tersedia
        return;               // Jika tidak ada, keluar dari fungsi
    }
    
    string namaPenumpang;     // Variabel untuk menyimpan nama penumpang
    int idPesawat;            // Variabel untuk menyimpan ID pesawat yang dipilih
    
    lihatDataPesawat(); // Tampilkan daftar pesawat yang tersedia
    cout << "\nMasukkan ID pesawat yang ingin dipesan: ";
    cin >> idPesawat;
    cin.ignore();             // Membersihkan buffer input

    // Validasi ID pesawat yang dimasukkan user
    if(idPesawat <= 0 || idPesawat > tail) {
        cout << "Pesawat tidak ada " << endl;
        return;               // Keluar jika ID tidak valid
    }

    cout << "Masukkan nama penumpang: ";
    getline(cin, namaPenumpang); // Input nama penumpang dengan spasi

    Pesawat p = pesawat[idPesawat - 1]; // Ambil data pesawat berdasarkan ID (index = ID-1)
    // Membuat node tiket baru menggunakan dynamic memory allocation
    Tiket* baru = new Tiket;
    baru->id = ticketCounter++;         // Generate ID tiket dari 1 sampai sekian
    baru->nama_penumpang = namaPenumpang; // Isi nama penumpang
    baru->nama_pesawat = p.nama;          // Isi nama pesawat
    baru->destinasi = p.destinasi;        // Isi destinasi
    baru->harga = p.harga_tiket;         // Isi harga tiket
    baru->next = tiket;                   // Hubungkan dengan node lama (insert at beginning)
    tiket = baru;                         // Update head linked list

    // Tampilkan konfirmasi pemesanan tiket
    cout << "\n=== TIKET BERHASIL DIPESAN! ===\n";
    cout << "ID Tiket: " << baru->id << endl;
    cout << "Nama Penumpang: " << namaPenumpang << endl;
    cout << "Pesawat: " << p.nama << endl;
    cout << "Destinasi: " << p.destinasi << endl;
    cout << "Harga Tiket: " << p.harga_tiket << endl;
}   

// Fungsi untuk menampilkan semua tiket yang telah dipesan
// Melakukan traversal pada linked list tiket
// Parameter: pointer head dari linked list tiket
void lihatSemuaTiket(Tiket* tiket) {
    if(tiket == nullptr) {    // Cek apakah linked list kosong
        cout << "Belum ada tiket yang dipesan." << endl;
        return;
    }
    
    cout << "\n=== DAFTAR SEMUA TIKET ===\n";
    Tiket* current = tiket;   // Pointer untuk traversal linked list
    
    // Traversal linked list dari head sampai tail
    while (current != nullptr) {
        // Tampilkan informasi tiket saat ini
        cout << "ID Tiket: " << current->id << endl;
        cout << "Nama Penumpang: " << current->nama_penumpang << endl;
        cout << "Nama Pesawat: " << current->nama_pesawat << endl;
        cout << "Destinasi: " << current->destinasi << endl;
        cout << "Harga: " << current->harga << endl;
        cout << "-------------------------\n";
        current = current->next; // Pindah ke node berikutnya
    }
}

void hapusTiket(Tiket*& tiket, int target) { // parameter struct pesawat, dereference dari pointer struck tiket, mengambil data target dari user
    if(tiket == nullptr) {
        cout << "Tidak ada tiket yang bisa dihapus, masih kosong" << endl;
        return;
    }

    Tiket* current = tiket; // ini adalah data tiket saat ini 
    Tiket* prev = nullptr; // variable untuk menyimpan tiket sebelum ini

    if(current->id == target) {
        tiket = current->next; // maka tiket maju dan bukan saat ini lagi
        delete current; // hapus tiket saat ini
        cout << "Tiket Dengan Id " << target << " berhasil dihapus " << endl;
        return;
    }
    
    //kalau tiket saat ini bukan null atau tidak kosong dan target bukan tiket dengan id saat ini
    while (current != nullptr && current->id != target)
    {
        //maka ubah variable tiket sebelumnya dengan tiket di depanya
        prev = current;
        //sampai dia current id adalah target
        current = current->next;
    }
    //kalo tiket saaat ini ternya null maka ia tidak ada
    if(current == nullptr) {
        cout << "Tiket dengan ID " << target << " tidak ditemukan.\n";
        return;
    }
        // Hapus tiket dan sambungkan node sebelumnya dengan node setelahnya
    prev->next = current->next;
    delete current;
    cout << "Tiket dengan ID " << target << " berhasil dihapus.\n";

}

// Fungsi utama program - entry point aplikasi
int main() {
   // Deklarasi array pesawat dengan ukuran maksimal
    Tiket* tiket = nullptr;      // Inisialisasi pointer head linked list tiket

    // Variabel untuk input data pesawat
    string nama, destinasi;
    int harga, jam;
    
    // Variabel untuk pencarian pesawat
    string targetCari; 
    int cariMenu;
    
    // Variabel untuk sorting pesawat
    int sortingMenu;
    
    init(tiket);        // Inisialisasi sistem

    int pilihan = 0;             // Inisialisasi variabel pilihan menu
    
    // Loop utama program - berjalan sampai user memilih keluar (pilihan 8)
    while (pilihan != 9) {
    
    // Membersihkan layar console
    system("cls");         

    // Menampilkan menu utama aplikasi
    cout << "****Selamat datang di aplikasi pengelolaan bandara AMIKOM YOGYAKARTA*****" << endl;
    cout << "****Bandara ini menyediakan layanan penerbangan antar provinsi di indonesia******" << endl;
    cout << "*******************************************" << endl;
    cout << "1. Lihat semua pesawat " << endl;
    cout << "2. Tambah Pesawat " << endl;
    cout << "3. Cari Pesawat" << endl;
    cout << "4. Urutkan Pesawat" << endl;
    cout << "5. Mulai Penerbangan Pesawat" << endl;
    cout << "6. Pesan Tiket" << endl;
    cout << "7. Lihat Semua Tiket" << endl;
    cout << "8. Hapus Tiket" << endl;
    cout << "9. Tambah Rute Penerbangan" << endl;
    cout << "10. Rekomendasi Rute Penerbangan" << endl;
    cout << "11. Keluar Aplikasi" << endl;
    cout << "Masukkan Pilihan: ";
    cin >> pilihan;

    // Switch case untuk menangani pilihan menu user
    switch (pilihan) {
        case 1: // Menampilkan semua data penerbangan
            lihatDataPesawat();
            break;
            
        case 2: // Menambah pesawat baru
            cout << "Masukkan nama maskapai: ";
            cin.ignore();                    // Membersihkan buffer
            getline(cin, nama);              // Input nama dengan spasi
            cout << "Masukkan jam keberangkatan [0000 dibaca 00:00]: ";
            cin >> jam;
            cout << "Masukkan harga tiket: ";
            cin >> harga;
            cout << "Masukkan tujuan destinasi: ";
            cin.ignore();                    // Membersihkan buffer
            getline(cin, destinasi);         // Input destinasi dengan spasi
            masukkanPesawat(nama, jam, harga, destinasi);
            break;
            
        case 3: // Mencari pesawat
            cout << "Cari Pesawat Berdasarkan:" << endl;
            cout << "1. Nama maskapai" << endl;
            cout << "2. Destinasi pesawat" << endl;
            cout << "Masukkan pilihan: ";
            cin >> cariMenu;
            cout << "Cari data: ";
            cin.ignore();                    // Membersihkan buffer
            getline(cin, targetCari);        // Input target pencarian
            if(targetCari == "") {           // Validasi input kosong
                cout << "Input tidak boleh kosong!" << endl;
                break;
            }
            cariPesawat( targetCari, cariMenu);
            break;
            
        case 4: // Mengurutkan pesawat
            cout << "Urutkan pesawat berdasarkan" << endl;
            cout << "1. Termurah" << endl;
            cout << "2. Termahal" << endl;
            cout << "3. Keberangkatan paling awal" << endl;
            cout << "Masukkan pilihan: ";
            cin >> sortingMenu;
            sortingPesawat( sortingMenu);
            break;
            
        case 5: // Memberangkatkan pesawat
            berangkatKanPesawat();
            break;
            
        case 6: // Memesan tiket
            pesanTiket( tiket);
            break;
            
        case 7: // Melihat semua tiket yang dipesan
            cout << endl;
            lihatSemuaTiket(tiket);
            break;
        case 8: 
            int idTarget; // deklarasi id target yang ingin dihapus
            lihatSemuaTiket(tiket);
            cout << "Masukkan ID tiket yang ingin dihapus" << endl;
            cin >> idTarget; // mengambil id target tiket yang ingin dihapus
            hapusTiket( tiket, idTarget);

            case 9:    

                {
                    string dari, ke;
                    int waktu;
                    cout << "Masukkan asal penerbangan: ";
                    cin.ignore();
                    getline(cin, dari);
                    cout << "Masukkan tujuan penerbangan: ";
                    getline(cin, ke);;
                    cout << "Masukkan waktu tempuh (menit): ";
                    cin >> waktu;
                    tambahJalur(dari, ke, waktu);
                }
                break;

            case 10:
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
        case 11: // Keluar dari aplikasi
            cout << "Keluar dari aplikasi..." << endl;
            break;
            
        default: // Pilihan tidak valid
            cout << "Pilihan tidak valid." << endl;
    }

    // Pause program agar user bisa melihat output sebelum layar dibersihkan
    if (pilihan != 9) {
        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.ignore();                        // Membersihkan buffer
        cin.get();                          // Tunggu input ENTER dari user
    }
}
    return 0;                               // Program berakhir dengan sukses
}