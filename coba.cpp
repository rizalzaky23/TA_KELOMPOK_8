#include <stdio.h>
#include <stdlib.h>

typedef int tipeinfo;
typedef struct node *tipeptr;

struct node {
    tipeinfo info;
    tipeptr kiri;
    tipeptr kanan;
};

tipeptr awal = NULL;
tipeptr akhir = NULL;

void buatnode(tipeinfo IB) {
    tipeptr baru = (tipeptr)malloc(sizeof(struct node));
    baru->info = IB;
    baru->kiri = NULL;
    baru->kanan = NULL;

    if (awal == NULL) {
        awal = baru;
        akhir = baru;
    } else {
        baru->kiri = akhir;
        akhir->kanan = baru;
        akhir = baru;
    }
}

void hapusnode(tipeinfo IH) {
    tipeptr hapus, bantu;

    if (awal == NULL) {
        printf("Linked list masih kosong\n");
        return;
    }

    hapus = awal;
    while (hapus != NULL && hapus->info != IH) {
        hapus = hapus->kanan;
    }

    if (hapus == NULL) {
        printf("Node %d tidak ditemukan\n", IH);
    } 
    else {
        if (hapus == awal && hapus == akhir) {
            awal = NULL;
            akhir = NULL;
        } 
        else if (hapus == awal) {
            awal = hapus->kanan;
            awal->kiri = NULL;
        } 
        else if (hapus == akhir) {
            akhir = hapus->kiri;
            akhir->kanan = NULL;
        } 
        else {
            bantu = hapus->kiri;
            bantu->kanan = hapus->kanan;
            hapus->kanan->kiri = bantu;
        }

        free(hapus);
        printf("Node %d berhasil dihapus.\n", IH);
    }
}

void tampilkan() {
    tipeptr bantu = awal;
    if (awal == NULL) {
        printf("List Kosong.\n");
    } else {
        printf("Isi List: ");
        while (bantu != NULL) {
            printf("%d ", bantu->info);
            bantu = bantu->kanan;
        }
        printf("\n");
    }
}

int main() {
    // 1. Tambah data
    buatnode(10);
    buatnode(20);
    buatnode(30);
    buatnode(40);
    buatnode(50);
    
    printf("Kondisi awal:\n");
    tampilkan();
    printf("--------------------------\n");

    // 2. Hapus Node Tengah (30)
    hapusnode(30);
    tampilkan();

    // 3. Hapus Node Awal (10)
    hapusnode(10);
    tampilkan();

    // 4. Hapus Node Akhir (50)
    hapusnode(50);
    tampilkan();

    // 5. Coba hapus yang tidak ada
    hapusnode(100);

    return 0;
}
