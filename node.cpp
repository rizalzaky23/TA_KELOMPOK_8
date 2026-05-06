void hapusnode(tipeinfo IH) 
{
    tipeptr hapus;

    if (listkosong()) {
        printf("Linked list masih kosong\n");
    } 
    else if (awal == akhir) {
        if (awal->info == IH) {
            hapus = awal;
            awal = NULL;
            akhir = NULL;
            free(hapus);
        } else {
            printf("Node tidak ditemukan\n");
        }
    } 
    else {
        tipeptr bantu;
        bantu = awal;

        while (bantu != NULL && bantu->info != IH) {
            bantu = bantu->kanan;
        }

        if (bantu == NULL) {
            printf("Node tidak ditemukan\n");
        } 
        else if (bantu == awal) {
            hapus = awal;
            awal = awal->kanan;
            awal->kiri = NULL;
            free(hapus);
        } 
        else if (bantu == akhir) {
            hapus = akhir;
            akhir = akhir->kiri;
            akhir->kanan = NULL;
            free(hapus);
        } 
        else {
            hapus = bantu;
            bantu->kiri->kanan = bantu->kanan;
            bantu->kanan->kiri = bantu->kiri;
            free(hapus);
        }
    }
}
