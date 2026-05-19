
# 🎵 PlaylistCLI

Aplikasi manajemen playlist musik berbasis terminal yang dibangun menggunakan **C++** dengan implementasi struktur data **Doubly Linked List**. Mendukung sistem multi-akun dengan peran Admin dan User.

---

## 📋 Deskripsi

**PlaylistCLI** adalah program konsol interaktif untuk mengelola koleksi musik. Admin dapat mengelola database lagu global, sementara setiap user dapat membuat dan mengelola playlist pribadi mereka sendiri. Data lagu dan akun disimpan secara persisten menggunakan file teks.

---

## ✨ Fitur

### 👑 Admin
| Fitur | Keterangan |
|-------|------------|
| Tambah Lagu | Menambahkan lagu baru ke database global |
| Lihat Lagu | Menampilkan seluruh daftar lagu |
| Cari Lagu | Mencari lagu berdasarkan judul, artis, atau genre |
| Urutkan Lagu | Mengurutkan lagu secara alfabetis (Quick Sort) |
| Edit Lagu | Mengubah informasi lagu yang ada |
| Hapus Lagu | Menghapus lagu dari database |

### 👤 User
| Fitur | Keterangan |
|-------|------------|
| Lihat Semua Lagu | Melihat seluruh lagu yang tersedia |
| Playlist Pribadi | Membuat dan melihat playlist milik sendiri |
| Tambah ke Playlist | Menambahkan lagu dari database ke playlist pribadi |
| Cari Lagu | Mencari lagu berdasarkan kata kunci |
| Urutkan Lagu | Melihat lagu dalam urutan alfabetis |
| Urutkan Playlist | Mengurutkan playlist pribadi |
| Hapus dari Playlist | Menghapus lagu di playlist pribadi |
| Ganti Password | Mengubah password akun |

### 🔐 Autentikasi
- Login sebagai **Admin** atau **User**
- Registrasi akun baru
- Perubahan password

---

## 🗂️ Struktur File

```
PlaylistCLI/
├── tugas-akhir.cpp       # Source code utama
├── tugas-akhir.exe       # Executable (Windows)
├── playlist.txt          # Database lagu global
├── login.txt             # Database akun pengguna
├── playlist_<user>.txt   # Playlist pribadi per user
└── README.md
```

---

## 🛠️ Cara Kompilasi & Menjalankan

### Prasyarat
- Compiler C++ (g++ / MinGW)

### Kompilasi

```bash
# Linux / macOS
g++ -o playlistcli tugas-akhir.cpp

# Windows (MinGW)
g++ -o playlistcli.exe tugas-akhir.cpp
```

### Menjalankan

```bash
# Linux / macOS
./playlistcli

# Windows
playlistcli.exe
```

> ⚠️ Pastikan file `playlist.txt` dan `login.txt` berada di direktori yang sama dengan executable saat dijalankan.

---

## 🔑 Akun Default

| Username | Password | Role |
|----------|----------|------|
| `admin` | `admin123` | Admin |
| `rizal` | `password` | User |
| `budi` | `budi123` | User |
| `dosen` | `pass123` | Admin |
| `alea` | `sean` | User |

---

## 🧠 Implementasi Struktur Data & Algoritma

| Komponen | Detail |
|----------|--------|
| **Struktur Data** | Doubly Linked List untuk menyimpan dan menavigasi daftar lagu |
| **Sorting** | Quick Sort untuk mengurutkan lagu berdasarkan judul |
| **Pencarian** | Linear Search dengan pencocokan substring pada judul, artis, dan genre |
| **Penyimpanan** | File I/O berbasis CSV (`.txt`) untuk persistensi data |

---

## 📁 Format Data

### `playlist.txt`
```
judul_lagu,nama_artis,genre,durasi_detik
bohemian rhapsody,queen,rock,354
shape of you,ed sheeran,pop,233
```

### `login.txt`
```
username password role
admin admin123 admin
rizal password user
```

### `playlist_<username>.txt`
```
judul_lagu,nama_artis,genre,durasi_detik
adore you,harry styles,pop,207
```

---

## 👥 Tim Pengembang

**Kelompok 8** — Tugas Akhir Mata Kuliah Struktur Data

---

## 📄 Lisensi

Proyek ini dibuat untuk keperluan akademik.
