#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MAX_JADWAL = 20;

int head;
int tail;
int ticketCounter = 1;

struct Jalur
{
    string tujuan;
    int waktu;
};

struct Tiket {
    int id;
    string nama_penumpang;
    string nama_pesawat;
    string destinasi;
    int harga;
    Tiket* next;
};

struct Pesawat
{
    int id;
    string nama;
    int jam_penerbangan;
    int harga_tiket;
    string destinasi;
};

Pesawat pesawat[MAX_JADWAL];

bool kosong() {
    if(tail == 0) {
        cout << "Tidak ada penerbangan" << endl;
        return true;
    }else {
        return false;
    }
}

bool penuh() {
    if(tail == MAX_JADWAL) {
        cout << "Bandara sudah penuh" << endl;
        return true;
    }else {
        return false;
    }
}

void lihatDataPesawat() {
    if(!kosong()) {
        cout << setw(25) <<"\n=== DATA PENERBANGAN ===\n";
        for(int i = 0; i < tail; i++) {
            if (i == 0) {
                cout << left
                     << setw(5) << "ID"
                     << setw(25) << "Nama"
                     << setw(15) << "Jam"
                     << setw(15) << "Harga"
                     << setw(20) << "Destinasi" << endl;
                cout << string(80, '-') << endl;
            }
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

void masukkanPesawat(string nama, int jam_penerbangan, int harga, string destinasi) {
    if(penuh()) {
        return;
    }
    pesawat[tail].nama = nama;
    pesawat[tail].jam_penerbangan = jam_penerbangan;
    pesawat[tail].harga_tiket = harga;
    pesawat[tail].destinasi = destinasi;
    pesawat[tail].id = tail + 1;
    tail++;
    cout << "Pesawat berhasil ditambahkan!" << endl;
}

void berangkatKanPesawat() {
    if(kosong()) {
        return;
    }
    for(int i = 1; i < tail; i++) {
        Pesawat key = pesawat[i];
        int j = i - 1;
        while (j >= 0 && pesawat[j].jam_penerbangan > key.jam_penerbangan) {
            pesawat[j + 1] = pesawat[j];
            j--;
        }
        pesawat[j + 1] = key;
    }
    cout << pesawat[0].nama << " dengan tujuan " << pesawat[0].destinasi
         << " telah diberangkatkan pada " << pesawat[0].jam_penerbangan << " WIB" << endl;
    for(int i = 0; i < tail - 1; i++) {
        pesawat[i] = pesawat[i + 1];
        pesawat[i].id = i + 1;
    }
    tail--;
}

void cariPesawat(string target, int tipe) {
    if(kosong()) {
        return;
    }
    bool ditemukan = false;
    switch (tipe) {
    case 1:
        for(int i = 0; i < tail; i++) {
            if(pesawat[i].nama == target) {
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
    case 2:
        for(int i = 0; i < tail; i++) {
            if(pesawat[i].destinasi == target) {
                cout << "Pesawat ditemukan dengan data: " << endl;
                cout << "ID: " << pesawat[i].id << endl;
                cout << "Nama: " << pesawat[i].nama << endl;
                cout << "Jam Penerbangan: " << pesawat[i].jam_penerbangan << "WIB" << endl;
                cout << "Harga Tiket: " << pesawat[i].harga_tiket << endl;
                cout << "Destinasi Pesawat: " << pesawat[i].destinasi << endl;
                cout << "-------------------------\n";
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Pesawat tidak ditemukan." << endl;
        }
        break;
    default:
        cout << "Pilihan tidak valid" << endl;
        break;
    }
}

void sortingPesawat(int tipe) {
    if(kosong()) {
        return;
    }
    switch (tipe) {
    case 1:
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
    case 2:
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
    case 3:
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


void pesanTiket(Tiket*& tiket) {
    if(kosong()) {
        return;
    }
    string namaPenumpang;
    int idPesawat;
        double bayar;
    lihatDataPesawat();
    cout << "\nMasukkan ID pesawat yang ingin dipesan: ";
    cin >> idPesawat;
    cin.ignore();
    if(idPesawat <= 0 || idPesawat > tail) {
        cout << "Pesawat tidak ada " << endl;
        return;
    }
    cout << "Masukkan nama penumpang: ";
    getline(cin, namaPenumpang);

          cout << "Masukkan Uang Pembayaran" << endl;
        cin >> bayar;


    Pesawat p = pesawat[idPesawat - 1];

                if(bayar < p.harga_tiket) {
        cout << "Maaf uang anda kurang" << endl;
                    return;
    }
    Tiket* baru = new Tiket;
    baru->id = ticketCounter++;
    baru->nama_penumpang = namaPenumpang;
    baru->nama_pesawat = p.nama;
    baru->destinasi = p.destinasi;
    baru->harga = p.harga_tiket;
    baru->next = tiket;
    tiket = baru;
    cout << "\n=== TIKET BERHASIL DIPESAN! ===\n";
    cout << "ID Tiket: " << baru->id << endl;
    cout << "Nama Penumpang: " << namaPenumpang << endl;
    cout << "Pesawat: " << p.nama << endl;
    cout << "Destinasi: " << p.destinasi << endl;
    cout << "Harga Tiket: " << p.harga_tiket << endl;
}

void lihatSemuaTiket(Tiket* tiket) {
    if(tiket == nullptr) {
        cout << "Belum ada tiket yang dipesan." << endl;
        return;
    }
    cout << "\n=== DAFTAR SEMUA TIKET ===\n";
    Tiket* current = tiket;
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

void hapusTiket(Tiket*& tiket, int target) {
    if(tiket == nullptr) {
        cout << "Tidak ada tiket yang bisa dihapus, masih kosong" << endl;
        return;
    }
    Tiket* current = tiket;
    Tiket* prev = nullptr;
    if(current->id == target) {
        tiket = current->next;
        delete current;
        cout << "Tiket Dengan Id " << target << " berhasil dihapus " << endl;
        return;
    }
    while (current != nullptr && current->id != target)
    {
        prev = current;
        current = current->next;
    }
    if(current == nullptr) {
        cout << "Tiket dengan ID " << target << " tidak ditemukan.\n";
        return;
    }
    prev->next = current->next;
    delete current;
    cout << "Tiket dengan ID " << target << " berhasil dihapus.\n";
}



unordered_map<string, vector<Jalur>> jalurPesawat;

void tambahJalur(string dari, string ke, int waktu) {
    jalurPesawat[dari].push_back({ke, waktu});
    jalurPesawat[ke].push_back({dari, waktu});
}

void tampilkanRuteTercepat(string asal, string tujuan) {
    unordered_map<string, int> jarak;
    unordered_map<string, string> sebelumnya;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> antrian;
    for (auto& kota : jalurPesawat) {
        jarak[kota.first] = INT_MAX;
    }
    jarak[asal] = 0;
    antrian.push({0, asal});
    while (!antrian.empty()) {
        pair<int, string> sekarang = antrian.top();
        antrian.pop();
        int waktuSaatIni = sekarang.first;
        string kotaSaatIni = sekarang.second;
        if (kotaSaatIni == tujuan) {
            break;
        }
        for (Jalur& tetangga : jalurPesawat[kotaSaatIni]) {
            int waktuBaru = waktuSaatIni + tetangga.waktu;
            if (waktuBaru < jarak[tetangga.tujuan]) {
                jarak[tetangga.tujuan] = waktuBaru;
                sebelumnya[tetangga.tujuan] = kotaSaatIni;
                antrian.push({waktuBaru, tetangga.tujuan});
            }
        }
    }
    if (jarak[tujuan] == INT_MAX) {
        cout << "Tidak ada jalur dari " << asal << " ke " << tujuan << endl;
        return;
    }
    vector<string> rute;
    string kota = tujuan;
    while (kota != asal) {
        rute.push_back(kota);
        kota = sebelumnya[kota];
    }
    rute.push_back(asal);
    reverse(rute.begin(), rute.end());
    cout << "Rute tercepat dari " << asal << " ke " << tujuan << ":\n";
    for (int i = 0; i < rute.size(); i++) {
        cout << rute[i];
        if (i != rute.size() - 1) cout << " -> ";
    }
    cout << endl;
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

void init(Tiket*& tiket) {
    head = 0;
    tail = 0;
    tiket = nullptr;
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


int main() {
    Tiket* tiket = nullptr;
    string nama, destinasi;
    int harga, jam;
    string targetCari;
    int cariMenu;
    int sortingMenu;
    init(tiket);
    int pilihan = 0;
    while (pilihan != 10) {
    system("cls");
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
    switch (pilihan) {
        case 1:
            lihatDataPesawat();
            break;
        case 2:
            cout << "Masukkan nama maskapai: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan jam keberangkatan [0000 dibaca 00:00]: ";
            cin >> jam;
            cout << "Masukkan harga tiket: ";
            cin >> harga;
            cout << "Masukkan tujuan destinasi: ";
            getline(cin, destinasi);
            masukkanPesawat(nama, jam, harga, destinasi);
            break;
        case 3:
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
            cariPesawat( targetCari, cariMenu);
            break;
        case 4:
            cout << "Urutkan pesawat berdasarkan" << endl;
            cout << "1. Termurah" << endl;
            cout << "2. Termahal" << endl;
            cout << "3. Keberangkatan paling awal" << endl;
            cout << "Masukkan pilihan: ";
            cin >> sortingMenu;
            sortingPesawat( sortingMenu);
            break;
        case 5:
            berangkatKanPesawat();
            break;
        case 6:
            pesanTiket( tiket);
            break;
        case 7:
            cout << endl;
            lihatSemuaTiket(tiket);
            break;
        case 8:
            int idTarget;
            lihatSemuaTiket(tiket);
            cout << "Masukkan ID tiket yang ingin dihapus" << endl;
            cin >> idTarget;
            hapusTiket( tiket, idTarget);
            break;
            case 9:
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
        case 10:
            cout << "Keluar dari aplikasi..." << endl;
            
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
    }
    if (pilihan != 10) {
        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.ignore();
        cin.get();
    }else {
        break;
    }
}
    return 0;
}
