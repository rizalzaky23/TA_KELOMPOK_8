#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
using namespace std;

struct lagu{
	string judul;
    string artis;
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

void tambahLagu(){
	string inputJudul, inputArtis;
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
    cout << "Durasi (detik) : ";
    cin >> inputDurasi;
    
    lagu* laguBaru = new lagu;
    laguBaru->judul = inputJudul;
    laguBaru->artis = inputArtis;
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
        fprintf(fileLagu, "%s,%s,%d\n", inputJudul.c_str(), inputArtis.c_str(), inputDurasi);
        fclose(fileLagu);
    }

    cout << "\n Lagu '" << inputJudul << "' berhasil ditambahkan ke dalam playlist!" << endl;
    pauseScreen();
}


void lihatLagu(){
	clearScreen();
    cout << "===============================================================" << endl;
    cout << "                         DAFTAR PLAYLIST                       " << endl;
    cout << "===============================================================" << endl;

 
    FILE* file = fopen("playlist.txt", "r");


    if (file == NULL) {
        cout << "\n[!] Playlist saat ini masih kosong atau belum ada lagu." << endl;
        pauseScreen();
        return; 
    }

    cout << left << setw(30) << "JUDUL LAGU" << setw(20) << "ARTIS" << "DURASI" << endl;
    cout << "---------------------------------------------------------------" << endl;

    char judul[100], artis[100];
    int durasi;

    while (fscanf(file, " %[^,],%[^,],%d", judul, artis, &durasi) != EOF) {
        
        cout << left << setw(30) << judul 
             << setw(20) << artis 
             << formatDuration(durasi) << endl;
    }

    fclose(file);

    cout << "---------------------------------------------------------------" << endl;
    pauseScreen();
}

void cariLagu(){
	string kataKunci;
    
    clearScreen();
    cout << "===============================================================" << endl;
    cout << "                         CARI LAGU                             " << endl;
    cout << "===============================================================" << endl;
    
    cin.ignore();
    cout << "Masukkan Judul atau Nama Artis yang dicari: ";
    getline(cin, kataKunci);

    FILE* file = fopen("playlist.txt", "r");
    if (file == NULL) {
        cout << "\n Playlist masih kosong. Tidak ada yang bisa dicari." << endl;
        pauseScreen();
        return;
    }

    char fJudul[100], fArtis[100];
    int fDurasi;
    bool ketemu = false;

    cout << "\n--- Hasil Pencarian ---" << endl;
    cout << left << setw(30) << "JUDUL LAGU" << setw(20) << "ARTIS" << "DURASI" << endl;
    cout << "---------------------------------------------------------------" << endl;

    while (fscanf(file, " %[^,],%[^,],%d", fJudul, fArtis, &fDurasi) != EOF) {
    
        string cariJudul = fJudul;
        string cariArtis = fArtis;

        if (cariJudul.find(kataKunci) != string::npos || cariArtis.find(kataKunci) != string::npos) {
            
            cout << left << setw(30) << cariJudul 
                 << setw(20) << cariArtis 
                 << formatDuration(fDurasi) << endl;
            
            ketemu = true;
        }
    }
    
    fclose(file);

    cout << "---------------------------------------------------------------" << endl;

    if (!ketemu) {
        cout << "Lagu dengan kata kunci '" << kataKunci << "' tidak ditemukan." << endl;
    }

    pauseScreen();
}

void tukarDataArray(lagu &a, lagu &b) {
    lagu temp = a; // Simpan data 'a' ke tempat sementara
    a = b;         // Timpa 'a' dengan 'b'
    b = temp;      // Isi 'b' dengan data sementara tadi
}

//Fungsi Partition: Memisah data berdasarkan Pivot
// low dan high di sini adalah ANGKA INDEKS (contoh: 0 sampai 9)
int partitionArray(lagu arr[], int low, int high) {
    string pivot = arr[high].judul; // Jadikan lagu terakhir sebagai Pivot
    int i = (low - 1); // Penanda untuk elemen yang lebih kecil

    // Mengecek dari awal sampai sebelum pivot
    for (int j = low; j <= high - 1; j++) {
        // Jika judul lebih kecil dari pivot (urutan A-Z)
        if (arr[j].judul <= pivot) {
            i++; 
            tukarDataArray(arr[i], arr[j]); // Tukar posisinya
        }
    }
    // Pindahkan pivot ke tengah (di antara kelompok kecil dan besar)
    tukarDataArray(arr[i + 1], arr[high]);
    
    return (i + 1); // Kembalikan posisi pivot yang baru
}

void quickSortArray(lagu arr[], int low, int high) {
    if (low < high) {
        // pi adalah indeks pembatas (Partition Index)
        int pi = partitionArray(arr, low, high);

        // Urutkan sebelah kiri pivot
        quickSortArray(arr, low, pi - 1);
        
        // Urutkan sebelah kanan pivot
        quickSortArray(arr, pi + 1, high);
    }
}


void urutLagu(){
	clearScreen();
    cout << "===============================================================" << endl;
    cout << "               LIHAT LAGU TERURUT (SEMENTARA)                  " << endl;
    cout << "===============================================================" << endl;

    // A. BACA DATA DARI FILE KE DALAM ARRAY SEMENTARA
    FILE* fileIn = fopen("playlist.txt", "r");
    if (fileIn == NULL) {
        cout << "\n[!] Playlist masih kosong. Tidak ada yang bisa diurutkan." << endl;
        pauseScreen();
        return;
    }

    // Menyiapkan Array penampung sementara
    lagu arrayPlaylist[100]; 
    int jumlahLagu = 0;

    char fJudul[100], fArtis[100];
    int fDurasi;
    
    // Menyedot isi file ke dalam Array
    while (fscanf(fileIn, " %[^,],%[^,],%d", fJudul, fArtis, &fDurasi) != EOF) {
        arrayPlaylist[jumlahLagu].judul = fJudul;
        arrayPlaylist[jumlahLagu].artis = fArtis;
        arrayPlaylist[jumlahLagu].durasi = fDurasi;
        jumlahLagu++;
    }
    fclose(fileIn);

    // B. JALANKAN QUICK SORT JIKA LAGU LEBIH DARI 1
    if (jumlahLagu > 1) {
        quickSortArray(arrayPlaylist, 0, jumlahLagu - 1);
    }

    // C. LANGSUNG TAMPILKAN ARRAY YANG SUDAH TERURUT KE LAYAR
    cout << left << setw(30) << "JUDUL LAGU" << setw(20) << "ARTIS" << "DURASI" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < jumlahLagu; i++) {
        cout << left << setw(30) << arrayPlaylist[i].judul 
             << setw(20) << arrayPlaylist[i].artis 
             << formatDuration(arrayPlaylist[i].durasi) << endl;
    }

    cout << "---------------------------------------------------------------" << endl;
    
    pauseScreen();
}

void hapusLagu() {
    clearScreen();
    cout << "===============================================================" << endl;
    cout << "                         HAPUS LAGU                            " << endl;
    cout << "===============================================================" << endl;

    if (head == NULL) {
        cout << "\n Playlist kosong, tidak ada lagu yang bisa dihapus." << endl;
        pauseScreen();
        return;
    }

    string judulHapus;
    cin.ignore();
    cout << "Masukkan Judul Lagu yang ingin dihapus (Harus Persis): ";
    getline(cin, judulHapus);

    // 1. CARI LAGU DI DALAM LINKED LIST
    lagu* bantu = head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bantu->judul == judulHapus) {
            ketemu = true;
            break; // Berhenti jika sudah ketemu gerbongnya
        }
        bantu = bantu->next;
    }

    // 2. PROSES PENGHAPUSAN JIKA KETEMU
    if (ketemu) {
        // Jika yang dihapus adalah satu-satunya lagu di playlist
        if (bantu == head && bantu == tail) {
            head = NULL;
            tail = NULL;
        }
        // Skenario A: Hapus di Depan (Head)
        else if (bantu == head) {
            head = head->next;
            head->prev = NULL;
        }
        // Skenario B: Hapus di Belakang (Tail)
        else if (bantu == tail) {
            tail = tail->prev;
            tail->next = NULL;
        }
        // Skenario C: Hapus di Tengah
        else {
            bantu->prev->next = bantu->next;
            bantu->next->prev = bantu->prev;
        }

        delete bantu; // Hapus gerbong dari memori RAM
        cout << "\n Lagu '" << judulHapus << "' berhasil dihapus dari playlist!" << endl;

        // 3. UPDATE FILE (Tulis ulang file playlist.txt dengan data terbaru)
        FILE* fileOut = fopen("playlist.txt", "w"); // Mode "w" menghapus isi lama
        if (fileOut != NULL) {
            lagu* temp = head;
            while (temp != NULL) {
                fprintf(fileOut, "%s,%s,%d\n", temp->judul.c_str(), temp->artis.c_str(), temp->durasi);
                temp = temp->next;
            }
            fclose(fileOut);
        }
    } else {
        cout << "\n Lagu dengan judul '" << judulHapus << "' tidak ditemukan." << endl;
    }

    pauseScreen();
}

void menuAdmin(){
	int pilihMenu;
	
	do{
		cout << "===============================" << endl;
		cout << "           MENU ADMIN          " << endl;
		cout << "===============================" << endl;
		cout << "1. Tambah Lagu" << endl;
		cout << "2. Lihat Lagu" << endl;
		cout << "3. Cari Lagu" << endl;
		cout << "4. Urutkan Lagu" << endl;
		cout << "5. Hapus Lagu" << endl;
		cout << "Pilih Menu : ";cin >> pilihMenu;
	
		switch(pilihMenu){
			case 1: tambahLagu();
			break;
			case 2: lihatLagu();
			break;
			case 3: cariLagu();
			break;
			case 4: urutLagu();
			break;
			case 5: hapusLagu();
			break;
			default : cout << "Pilihan tidak valid" << endl;
		}
	}while(pilihMenu != 0);
	
	
}
void loginUser(){
	string logUser, logPw;
	cout << "==============================" << endl;
	cout << "         Login User          " << endl;
	cout << "==============================" << endl;
	cin.ignore();
	cout << "Username : ";
	getline(cin, logUser);
	cout << "Password : ";
	getline(cin, logPw);
	
	FILE* file = fopen("login.txt", "r");
	if (file == NULL) {
        cout << "File login.txt tidak ditemukan!" << endl;
        pauseScreen();
        return;
    }
    
    char fUser[50], fPass[50], fRole[50];
    bool loginValid = false;
    
    while (fscanf(file, "%s %s %s", fUser, fPass, fRole) != EOF) {
        string role = fRole;
        
        if (logUser == fUser && logPw == fPass && role == "user") {
            loginValid = true;
            break; 
        }
    }
    fclose(file);

    if (loginValid) {
        cout << "\n Login User Berhasil!" << endl;
        pauseScreen();
    } else {
        cout << "Username/Password salah, atau Anda bukan User!" << endl;
        pauseScreen();
    }
}

void registerUser(){
	string regUser, regPw;
	cout << "==============================" << endl;
	cout << "         Register User       " << endl;
	cout << "==============================" << endl;
	cin.ignore();
	cout << "Masukkan Username baru : ";
	getline(cin, regUser);
	
	FILE* fileCek = fopen("login.txt", "r");
    if (fileCek != NULL) {
        char fUser[50], fPass[50], fRole[50];
       
        while (fscanf(fileCek, "%s %s %s", fUser, fPass, fRole) != EOF) {
            
            if (regUser == fUser) {
                cout << "\n Username '" << regUser << "' sudah dipakai! Silakan coba nama lain." << endl;
                fclose(fileCek); 
                pauseScreen();
                return; 
            }
        }
        fclose(fileCek);
    }
    
    cout << "Masukkan Password baru : "; cin >> regPw;
    
    FILE* fileTambah = fopen("login.txt", "a");
    if (fileTambah == NULL) {
        cout << "\nGagal membuka file untuk menyimpan data!";
        pauseScreen();
        return;
    }
    
    fprintf(fileTambah, "%s %s user", regUser.c_str(), regPw.c_str());
    fclose(fileTambah);

    cout << "\n Registrasi berhasil! Akun '" << regUser << "' sekarang bisa dipakai Login." << endl;
    pauseScreen();
    
    loginUser();
	
}

void loginAdmin(){
	string logAdmin, logPw;
	cout << "==============================" << endl;
	cout << "         Login Admin          " << endl;
	cout << "==============================" << endl;
	cin.ignore();
	cout << "Username : ";
	getline(cin, logAdmin);
	cout << "Password : ";
	getline(cin, logPw);
	
	FILE* file = fopen("login.txt", "r");
	if (file == NULL) {
        cout << "File login.txt tidak ditemukan!" << endl;
        pauseScreen();
        return;
    }
    
    char fAdmin[50], fPass[50], fRole[50];
    bool loginValid = false;
    
    while (fscanf(file, "%s %s %s", fAdmin, fPass, fRole) != EOF) {
        string role = fRole;
        
        if (logAdmin == fAdmin && logPw == fPass && role == "admin") {
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
        cout << "\n Username/Password salah, atau Anda bukan Admin!";
        pauseScreen();
    }
}

void menuLoginUser(){
	int pilihLogin;
	do{
		cout << "==========================================" << endl;
		cout << "             Login/Register User          " << endl;
		cout << "==========================================" << endl;
		cout << "Buat akun baru atau Login" << endl;
		cout << "1. Login(Jika sudah ada akun)" << endl;
		cout << "2. Register(Buat akun baru)" << endl;
		cout << "3. Exit" << endl;
		cout << "Pilih : "; cin >> pilihLogin;
	
		switch(pilihLogin){
			case 1: loginUser();
			break;
			case 2: registerUser();
			break;
			case 3 : cout << "Selamat Tinggal :)" << endl;
			return;
			default : cout << "Pilihan tidak valid" << endl;
		}
	}while(pilihLogin != 3);
}

void loadLagu() {
    // Buka file untuk dibaca
    FILE* file = fopen("playlist.txt", "r");
    
    // Jika file tidak ada, tidak perlu di-load (berarti aplikasi baru pertama kali dipakai)
    if (file == NULL) return; 

    char fJudul[100], fArtis[100];
    int fDurasi;

    // Baca file baris per baris
    while (fscanf(file, " %[^,],%[^,],%d", fJudul, fArtis, &fDurasi) != EOF) {
        
        // Buat gerbong baru untuk setiap lagu yang dibaca dari file
        lagu* laguBaru = new lagu;
        laguBaru->judul = fJudul;
        laguBaru->artis = fArtis;
        laguBaru->durasi = fDurasi;
        laguBaru->next = NULL;
        laguBaru->prev = NULL;

        // Sambungkan ke Linked List
        if (head == NULL) {
            head = laguBaru;
            tail = laguBaru;
        } else {
            tail->next = laguBaru;
            laguBaru->prev = tail;
            tail = laguBaru;
        }
    }
    
    // Tutup file setelah semua lagu masuk ke Linked List
    fclose(file);
}

int main (){
	loadLagu();
	
	int pilihLogin;
	
	do{
		cout << "==============================" << endl;
		cout << "           Menu Login	       " << endl;
		cout << "==============================" << endl;
		cout << "Login " << endl;
		cout << "1. Login Admin" << endl;
		cout << "2. Login User" << endl;
		cout << "3. Keluar " << endl;
		cout << "Pilih Login : "; cin >> pilihLogin;
	
		switch(pilihLogin){
			case 1 : loginAdmin();
			break;
			case 2 : menuLoginUser();
			break;
			case 3 : cout << "Selamat Tinggal :)" << endl;
			return 0;
			default : cout << "Pilihan tidak valid" << endl;
		}
	}while(pilihLogin != 0);
		
}
