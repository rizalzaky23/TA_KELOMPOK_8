#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sstream>

using namespace std;

struct lagu {
    string judul;
    string artis;
    string genre;
    int durasi;
    lagu* next;
    lagu* prev;
};

struct Account {
    string username;
    string password;
    string role;
};

lagu* head = NULL;
lagu* tail = NULL;

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

string formatDuration(int seconds) {
    int min = seconds / 60;
    int sec = seconds % 60;
    stringstream ss;
    ss << setfill('0') << setw(2) << min << ":" << setfill('0') << setw(2) << sec;
    return ss.str();
}

void tambahLagu() {
    string inputJudul, inputArtis, inputGenre;
    int inputDurasi;

    clearScreen();
    cout << "===============================" << endl;
    cout << "          TAMBAH LAGU          " << endl;
    cout << "===============================" << endl;

    cin.ignore();
    cout << "Judul Lagu     : ";
    getline(cin, inputJudul);
    cout << "Nama Artis     : ";
    getline(cin, inputArtis);
    cout << "Genre Lagu     : ";
    getline(cin, inputGenre);
    cout << "Durasi (detik) : ";
    cin >> inputDurasi;

    lagu* laguBaru = new lagu;
    laguBaru->judul = inputJudul;
    laguBaru->artis = inputArtis;
    laguBaru->genre = inputGenre;
    laguBaru->durasi = inputDurasi;
    laguBaru->next = NULL;
    laguBaru->prev = NULL;

    if (head == NULL) {
        head = laguBaru;
        tail = laguBaru;
    } else {
        tail->next = laguBaru;
        laguBaru->prev = tail;
        tail = laguBaru;
    }

    FILE* fileLagu = fopen("playlist.txt", "a");
    if (fileLagu != NULL) {
        fprintf(fileLagu, "%s,%s,%s,%d\n", inputJudul.c_str(), inputArtis.c_str(), inputGenre.c_str(), inputDurasi);
        fclose(fileLagu);
    }

    cout << "\n Lagu '" << inputJudul << "' berhasil ditambahkan!" << endl;
    pauseScreen();
}

void lihatLagu() {
    clearScreen();
    cout << "=================================================================================" << endl;
    cout << "                                DAFTAR SEMUA LAGU                                " << endl;
    cout << "=================================================================================" << endl;

    if (head == NULL) {
        cout << "\n[!] Playlist saat ini masih kosong." << endl;
        pauseScreen();
        return;
    }

    cout << left << setw(25) << "JUDUL LAGU" << setw(20) << "ARTIS" << setw(15) << "GENRE" << "DURASI" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    lagu* temp = head;
    while (temp != NULL) {
        cout << left << setw(25) << temp->judul
             << setw(20) << temp->artis
             << setw(15) << temp->genre
             << formatDuration(temp->durasi) << endl;
        temp = temp->next;
    }

    cout << "---------------------------------------------------------------------------------" << endl;
    pauseScreen();
}

void cariLagu() {
    string kataKunci;
    clearScreen();
    cout << "=================================================================================" << endl;
    cout << "                                   CARI LAGU                                     " << endl;
    cout << "=================================================================================" << endl;

    cin.ignore();
    cout << "Masukkan Judul, Artis, atau Genre: ";
    getline(cin, kataKunci);

    lagu* temp = head;
    bool ketemu = false;

    cout << "\n--- Hasil Pencarian ---" << endl;
    cout << left << setw(25) << "JUDUL LAGU" << setw(20) << "ARTIS" << setw(15) << "GENRE" << "DURASI" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    while (temp != NULL) {
        if (temp->judul.find(kataKunci) != string::npos || temp->artis.find(kataKunci) != string::npos || temp->genre.find(kataKunci) != string::npos) {
            cout << left << setw(25) << temp->judul << setw(20) << temp->artis << setw(15) << temp->genre << formatDuration(temp->durasi) << endl;
            ketemu = true;
        }
        temp = temp->next;
    }

    if (!ketemu) cout << "Lagu tidak ditemukan." << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    pauseScreen();
}

void tukarDataArray(lagu &a, lagu &b) {
    lagu temp = a;
    a = b;
    b = temp;
}

int partitionArray(lagu arr[], int low, int high) {
    string pivot = arr[high].judul;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].judul <= pivot) {
            i++;
            tukarDataArray(arr[i], arr[j]);
        }
    }
    tukarDataArray(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortArray(lagu arr[], int low, int high) {
    if (low < high) {
        int pi = partitionArray(arr, low, high);
        quickSortArray(arr, low, pi - 1);
        quickSortArray(arr, pi + 1, high);
    }
}

void urutLagu() {
    clearScreen();
    cout << "=================================================================================" << endl;
    cout << "                           LIHAT LAGU TERURUT (JUDUL)                            " << endl;
    cout << "=================================================================================" << endl;

    if (head == NULL) {
        cout << "\n[!] Playlist masih kosong." << endl;
        pauseScreen();
        return;
    }

    lagu arrayPlaylist[500];
    int jumlahLagu = 0;
    lagu* temp = head;

    while (temp != NULL && jumlahLagu < 500) {
        arrayPlaylist[jumlahLagu] = *temp;
        jumlahLagu++;
        temp = temp->next;
    }

    if (jumlahLagu > 1) quickSortArray(arrayPlaylist, 0, jumlahLagu - 1);

    cout << left << setw(25) << "JUDUL LAGU" << setw(20) << "ARTIS" << setw(15) << "GENRE" << "DURASI" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahLagu; i++) {
        cout << left << setw(25) << arrayPlaylist[i].judul << setw(20) << arrayPlaylist[i].artis << setw(15) << arrayPlaylist[i].genre << formatDuration(arrayPlaylist[i].durasi) << endl;
    }
    cout << "---------------------------------------------------------------------------------" << endl;
    pauseScreen();
}

void hapusLagu() {
    clearScreen();
    cout << "===============================================================" << endl;
    cout << "                          HAPUS LAGU                           " << endl;
    cout << "===============================================================" << endl;

    if (head == NULL) {
        cout << "\n Playlist kosong." << endl;
        pauseScreen();
        return;
    }

    string judulHapus;
    cin.ignore();
    cout << "Masukkan Judul Lagu yang ingin dihapus: ";
    getline(cin, judulHapus);

    lagu* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->judul == judulHapus) {
            ketemu = true;
            break;
        }
        bantu = bantu->next;
    }

    if (ketemu) {
        if (bantu == head && bantu == tail) {
            head = NULL; tail = NULL;
        } else if (bantu == head) {
            head = head->next; head->prev = NULL;
        } else if (bantu == tail) {
            tail = tail->prev; tail->next = NULL;
        } else {
            bantu->prev->next = bantu->next;
            bantu->next->prev = bantu->prev;
        }

        delete bantu;
        cout << "\n Lagu '" << judulHapus << "' berhasil dihapus!" << endl;

        FILE* fileOut = fopen("playlist.txt", "w");
        if (fileOut != NULL) {
            lagu* temp = head;
            while (temp != NULL) {
                fprintf(fileOut, "%s,%s,%s,%d\n", temp->judul.c_str(), temp->artis.c_str(), temp->genre.c_str(), temp->durasi);
                temp = temp->next;
            }
            fclose(fileOut);
        }
    } else {
        cout << "\n Lagu tidak ditemukan." << endl;
    }
    pauseScreen();
}

void tambahPlaylist(string username) {
    string judulPilih;
    clearScreen();
    cout << "=== DAFTAR LAGU TERSEDIA ===" << endl;
    
    if (head == NULL) {
        cout << "Belum ada lagu di sistem." << endl;
        pauseScreen();
        return;
    }

    lagu* temp = head;
    while (temp != NULL) {
        cout << "- " << temp->judul << " [" << temp->artis << "]" << endl;
        temp = temp->next;
    }

    cout << "\nMasukkan Judul Lagu untuk ditambah ke Playlist Anda: ";
    cin.ignore();
    getline(cin, judulPilih);

    temp = head;
    bool ditemukan = false;
    while (temp != NULL) {
        if (temp->judul == judulPilih) {
            ditemukan = true;
            string fileName = "playlist_" + username + ".txt";
            FILE* fUser = fopen(fileName.c_str(), "a");
            if (fUser != NULL) {
                fprintf(fUser, "%s,%s,%s,%d\n", temp->judul.c_str(), temp->artis.c_str(), temp->genre.c_str(), temp->durasi);
                fclose(fUser);
                cout << "\nBerhasil ditambahkan ke playlist pribadi!" << endl;
            }
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) cout << "Lagu tidak ditemukan." << endl;
    pauseScreen();
}

void menuUser(string username) {
    int pilihMenu;
    do {
        clearScreen();
        cout << "===============================" << endl;
        cout << "      MENU USER: " << username << endl;
        cout << "===============================" << endl;
        cout << "1. Lihat Semua Lagu" << endl;
        cout << "2. Tambah Lagu Ke Playlist Pribadi" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Urutkan Lagu" << endl;
        cout << "5. Hapus Lagu di playlist" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilih Menu : "; cin >> pilihMenu;

        switch(pilihMenu) {
            case 1: lihatLagu(); break;
            case 2: tambahPlaylist(username); break;
            case 3: cariLagu(); break;
            case 4: urutLagu(); break;
            case 5: hapusLagu(); break;
            case 0: return;
            default : cout << "Pilihan tidak valid" << endl; pauseScreen();
        }
    } while(pilihMenu != 0);
}

void menuAdmin() {
    int pilihMenu;
    do {
        clearScreen();
        cout << "===============================" << endl;
        cout << "           MENU ADMIN          " << endl;
        cout << "===============================" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Lihat Lagu" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Urutkan Lagu" << endl;
        cout << "5. Hapus Lagu" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilih Menu : "; cin >> pilihMenu;

        switch(pilihMenu) {
            case 1: tambahLagu(); break;
            case 2: lihatLagu(); break;
            case 3: cariLagu(); break;
            case 4: urutLagu(); break;
            case 5: hapusLagu(); break;
            case 0: return;
            default : cout << "Pilihan tidak valid" << endl; pauseScreen();
        }
    } while(pilihMenu != 0);
}

void loginUser() {
    string logUser, logPw;
    clearScreen();
    cout << "==============================" << endl;
    cout << "          Login User          " << endl;
    cout << "==============================" << endl;
    cin.ignore();
    cout << "Username : "; getline(cin, logUser);
    cout << "Password : "; getline(cin, logPw);

    FILE* file = fopen("login.txt", "r");
    if (file == NULL) {
        cout << "File login.txt tidak ditemukan!" << endl;
        pauseScreen();
        return;
    }

    char fUser[50], fPass[50], fRole[50];
    bool loginValid = false;
    while (fscanf(file, "%s %s %s", fUser, fPass, fRole) != EOF) {
        if (logUser == fUser && logPw == fPass && (string)fRole == "user") {
            loginValid = true;
            break;
        }
    }
    fclose(file);

    if (loginValid) {
        cout << "\n Login User Berhasil!" << endl;
        pauseScreen();
        menuUser(logUser);
    } else {
        cout << "Username/Password salah!" << endl;
        pauseScreen();
    }
}

void registerUser() {
    string regUser, regPw;
    clearScreen();
    cout << "==============================" << endl;
    cout << "         Register User        " << endl;
    cout << "==============================" << endl;
    cin.ignore();
    cout << "Masukkan Username baru : ";
    getline(cin, regUser);

    FILE* fileCek = fopen("login.txt", "r");
    if (fileCek != NULL) {
        char fUser[50], fPass[50], fRole[50];
        while (fscanf(fileCek, "%s %s %s", fUser, fPass, fRole) != EOF) {
            if (regUser == fUser) {
                cout << "\n Username sudah dipakai!" << endl;
                fclose(fileCek);
                pauseScreen();
                return;
            }
        }
        fclose(fileCek);
    }

    cout << "Masukkan Password baru : "; cin >> regPw;

    FILE* fileTambah = fopen("login.txt", "a");
    if (fileTambah != NULL) {
        fprintf(fileTambah, "%s %s user\n", regUser.c_str(), regPw.c_str());
        fclose(fileTambah);
        cout << "\n Registrasi berhasil!" << endl;
    }
    pauseScreen();
    loginUser();
}

void loginAdmin() {
    string logAdmin, logPw;
    clearScreen();
    cout << "==============================" << endl;
    cout << "          Login Admin         " << endl;
    cout << "==============================" << endl;
    cin.ignore();
    cout << "Username : "; getline(cin, logAdmin);
    cout << "Password : "; getline(cin, logPw);

    FILE* file = fopen("login.txt", "r");
    if (file == NULL) {
        cout << "File login.txt tidak ditemukan!" << endl;
        pauseScreen();
        return;
    }

    char fAdmin[50], fPass[50], fRole[50];
    bool loginValid = false;
    while (fscanf(file, "%s %s %s", fAdmin, fPass, fRole) != EOF) {
        if (logAdmin == fAdmin && logPw == fPass && (string)fRole == "admin") {
            loginValid = true;
            break;
        }
    }
    fclose(file);

    if (loginValid) {
        cout << "\n Login Admin Berhasil!";
        pauseScreen();
        menuAdmin();
    } else {
        cout << "\n Login Gagal!";
        pauseScreen();
    }
}

void menuLoginUser() {
    int pilihLogin;
    do {
        clearScreen();
        cout << "==========================================" << endl;
        cout << "           Login/Register User            " << endl;
        cout << "==========================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Kembali" << endl;
        cout << "Pilih : "; cin >> pilihLogin;

        switch(pilihLogin) {
            case 1: loginUser(); break;
            case 2: registerUser(); break;
            case 3: return;
            default : cout << "Pilihan tidak valid" << endl; pauseScreen();
        }
    } while(pilihLogin != 3);
}

void loadLagu() {
    FILE* file = fopen("playlist.txt", "r");
    if (file == NULL) return;

    char fJudul[100], fArtis[100], fGenre[100];
    int fDurasi;

    while (fscanf(file, " %[^,],%[^,],%[^,],%d", fJudul, fArtis, fGenre, &fDurasi) != EOF) {
        lagu* laguBaru = new lagu;
        laguBaru->judul = fJudul;
        laguBaru->artis = fArtis;
        laguBaru->genre = fGenre;
        laguBaru->durasi = fDurasi;
        laguBaru->next = NULL;
        laguBaru->prev = NULL;

        if (head == NULL) {
            head = laguBaru;
            tail = laguBaru;
        } else {
            tail->next = laguBaru;
            laguBaru->prev = tail;
            tail = laguBaru;
        }
    }
    fclose(file);
}

int main() {
    loadLagu();
    int pilihLogin;
    do {
        clearScreen();
        cout << "==============================" << endl;
        cout << "          Menu Utama          " << endl;
        cout << "==============================" << endl;
        cout << "1. Login Admin" << endl;
        cout << "2. Menu User" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih : "; cin >> pilihLogin;

        switch(pilihLogin) {
            case 1 : loginAdmin(); break;
            case 2 : menuLoginUser(); break;
            case 3 : cout << "Selamat Tinggal :)" << endl; return 0;
            default : cout << "Pilihan tidak valid" << endl; pauseScreen();
        }
    } while(pilihLogin != 3);
    return 0;
}
