// Menambahkan graph dengan fungsi mencapai penerbangan tercepat ke mana  (Ubah Graph)
#include <limits>
#include <vector>
#include <queue>
#include <unordered_map>

// Struktur untuk menyimpan edge/jalur antar kota
struct Jalur {
string tujuan;
int waktu; // Waktu tempuh (misalnya dalam menit)
};

// Struktur graf sebagai adjacency list
unordered_map<string, vector<Jalur>> graph;

// Menambahkan edge/jalur ke graf
void tambahJalur(string dari, string ke, int waktu) {
graph[dari].push_back({ke, waktu});
graph[ke].push_back({dari, waktu}); // Jika jalur dua arah
}

// Implementasi algoritma Dijkstra
void cariRuteTercepat(string asal, string tujuan) {
unordered_map<string, int> dist;
unordered_map<string, string> prev;
priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    for (auto& node : graph) {
        dist[node.first] = numeric_limits<int>::max();
    }
    dist[asal] = 0;
    pq.push({0, asal});

    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        if (currentNode == tujuan) break;

        for (auto& jalur : graph[currentNode]) {
            int newDist = currentDist + jalur.waktu;
            if (newDist < dist[jalur.tujuan]) {
                dist[jalur.tujuan] = newDist;
                prev[jalur.tujuan] = currentNode;
                pq.push({newDist, jalur.tujuan});
            }
        }
    }

    if (dist[tujuan] == numeric_limits<int>::max()) {
        cout << "Tidak ada rute dari " << asal << " ke " << tujuan << endl;
        return;
    }

    // Menampilkan hasil rute
    vector<string> path;
    for (string at = tujuan; !at.empty(); at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "\nRute tercepat dari " << asal << " ke " << tujuan << ":\n";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nTotal waktu tempuh: " << dist[tujuan] << " menit\n";

}

cariRuteTercepat("Yogyakarta", "Denpasar");
