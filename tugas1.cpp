#include <iostream>
#include <string>
using namespace std;

const int bk = 50; 

struct Buku {
    string jdlBuku;
    int thTerbit;
};

Buku dftBuku[bk];
Buku dftBukuAsli[bk]; 
int jmlBuku = 0;

void salinanData(Buku sumber[], Buku tujuan[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        tujuan[i] = sumber[i];
    }
}

void resetData() {
    salinanData(dftBukuAsli, dftBuku, jmlBuku);
}

void inputan(Buku dftBuku[], int& jmlBuku) {
    int input;
    cout << "Masukkan jumlah buku yang ingin anda input: ";
    cin >> input;

    if (input < 10 || input > 50) {
        cout << "Jumlah buku yang anda input harus lebih dari 10 dan kurang dari 50!"<<endl;
        return;
    }

    cin.ignore();
    
    for (int i = 0; i < input; i++) {
        cout << "Masukkan judul buku " << (jmlBuku + 1) << ": ";
        getline(cin, dftBuku[jmlBuku].jdlBuku);
        cout << "Masukkan tahun terbit: ";
        cin >> dftBuku[jmlBuku].thTerbit;
        cin.ignore();
        jmlBuku++;
    }

    if (jmlBuku == input) {
        salinanData(dftBuku, dftBukuAsli, jmlBuku);
    }
}

void tampilkan(const Buku dftBuku[], int jmlBuku) {

    for (int i = 0; i < jmlBuku; i++) {
        cout << dftBuku[i].jdlBuku << " - " << dftBuku[i].thTerbit << endl;
    }
}

void bubble(Buku dftBuku[], int jmlBuku) {
    resetData();
    for (int i = 0; i < jmlBuku - 1; i++) {
        for (int u = 0; u < jmlBuku - i - 1; u++) {
            if (dftBuku[u].thTerbit > dftBuku[u + 1].thTerbit) {
                swap(dftBuku[u], dftBuku[u + 1]);
            }
        }
    }
}

void quick(Buku dftBuku[], int awal, int akhir) {
    if (awal >= akhir) return;

    int low = awal, high = akhir;
    int pivot = dftBuku[(awal + akhir) / 2].thTerbit;

    do {
        while (dftBuku[low].thTerbit < pivot) low++;
        while (dftBuku[high].thTerbit > pivot) high--;

        if (low <= high) {
            swap(dftBuku[low], dftBuku[high]);
            low++;
            high--;
        }
    } while (low <= high);

   quick(dftBuku, awal, high);
   quick(dftBuku, low, akhir);
}

int sequential(const Buku dftBuku[], int jmlBuku, int tahun) {
    for (int i = 0; i < jmlBuku; i++) {
        if (dftBuku[i].thTerbit == tahun) {
            return i;
        }
    }
    return -1;
}

int binary(const Buku dftBuku[], int low, int high, int tahun) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (dftBuku[mid].thTerbit == tahun) {
            return mid;
        }
        if (dftBuku[mid].thTerbit < tahun) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int menu;

    do {
        cout<<endl;
        cout << "---------- Menu ----------"<<endl;
        cout << "1. Input data buku"<<endl;
        cout << "2. Menampilkan daftar buku"<<endl;
        cout << "3. Mengurutkan daftar buku dengan Bubble Sort"<<endl;
        cout << "4. Mengurutkan daftar buku dengan Quick Sort"<<endl;
        cout << "5. Mencari buku berdasarkan tahun terbit dengan Sequential Search"<<endl;
        cout << "6. Mencari buku berdasarkan tahun terbit dengan Binary Search"<<endl;
        cout << "7. Keluar dari program"<<endl;
        cout << "Pilih Menu: ";
        cin >> menu;
        cout<<endl;

        switch (menu) {
            case 1:
                cout<<"---------- Input Data Buku ----------"<<endl;
                inputan(dftBuku, jmlBuku);
                break;
            case 2:
                if (jmlBuku == 0) {
                    cout << "Maaf anda belum menambahkan buku. Silahkan menginput buku terlebih dahulu"<<endl;
                }else {
                    cout<<"---------- Menampilkan Daftar Buku ----------"<<endl;
                    tampilkan(dftBuku, jmlBuku);
                }
                break;
            case 3:
                if (jmlBuku == 0){
                    cout<<"Maaf belum ada buku yang tersimpan. Silahkan menginput terlebih dahulu"<<endl;
                }else{
                    cout<<"---------- Mengurutkan Daftar Buku dengan Bubble Sort ----------"<<endl;
                    cout<<"Daftar buku sebelum disorting : "<<endl;
                    tampilkan(dftBuku, jmlBuku);
                    bubble(dftBuku, jmlBuku);
                    cout<<endl;
                    cout <<"Daftar buku setelah disorting dengan Bubble Sort : "<<endl;;
                    tampilkan(dftBuku, jmlBuku);
                }
                break;
            case 4:
                if (jmlBuku == 0){
                    cout<<"Maaf belum ada buku yang tersimpan. Silahkan menginput terlebih dahulu"<<endl;
                }else{
                    cout<<"---------- Mengurutkan Daftar Buku dengan Quick Sort ----------"<<endl;
                    resetData();
                    cout<<"Daftar buku sebelum disorting : "<<endl;
                    tampilkan(dftBuku,jmlBuku);
                    quick(dftBuku, 0, jmlBuku - 1);
                    cout<<endl;
                    cout << "Daftar buku setelah disorting dengan Quick Sort :"<<endl;
                    tampilkan(dftBuku, jmlBuku);
                }
                break;
            case 5: 
                if (jmlBuku == 0){
                cout<<"Maaf belum ada buku yang tersimpan. Silahkan menginput terlebih dahulu"<<endl;
                }else{
                    int cari;
                    cout<<"---------- Mencari Tahun Terbit dengan Sequential Search ----------"<<endl;
                    cout << "Masukkan tahun terbit yang akan dicari: ";
                    cin >> cari;
                    int index = sequential(dftBuku, jmlBuku, cari);
                    if (index != -1) {
                        cout << "Buku ditemukan: " << dftBuku[index].jdlBuku << " - " << dftBuku[index].thTerbit <<endl;
                    } else {
                        cout << "Buku dengan tahun terbit "<<cari<<" tidak ditemukan"<<endl;
                    }
                }
                    break;
            case 6: 
                if (jmlBuku == 0){
                    cout<<"Maaf belum ada buku yang tersimpan. Silahkan menginput terlebih dahulu"<<endl;
                }else{
                    int cari;
                    cout<<"---------- Mencari Tahun Terbit dengan Binary Search ----------"<<endl;
                    cout << "Masukkan tahun terbit yang akan dicari: ";
                    cin >> cari;
                    int index = binary(dftBuku, 0, jmlBuku - 1, cari);
                    if (index != -1) {
                        cout << "Buku ditemukan: " << dftBuku[index].jdlBuku << " - " << dftBuku[index].thTerbit << endl;
                    } else {
                        cout << "Buku dengan tahun terbit "<<cari<<" tidak ditemukan"<<endl;
                    }
                }
                    break;
            case 7:
                cout << "Keluar dari program..."<<endl;
                break;
            default:
                cout << "Pilihan tidak valid."<<endl;
        }
    } while (menu != 7);

    return 0;
}