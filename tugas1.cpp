#include <iostream>
#include <string>
using namespace std;

//jumlah buku maksimal yang dapat diinput
const int bk = 50; 

//struct menyimpan judul dan tahun terbit buku
struct Buku {
    string jdlBuku;
    int thTerbit;
};

//array menyimpan daftar buku
Buku dftBuku[bk];

//array untuk menyimpan data buku yang asli sebelum diurutkan
Buku dftBukuAsli[bk]; 
int jmlBuku = 0;

//fungsi untuk menyalin data
void salinanData(Buku sumber[], Buku tujuan[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        tujuan[i] = sumber[i];
    }
}

//fungsi untuk mereset data
void resetData() {
    salinanData(dftBukuAsli, dftBuku, jmlBuku);
}

//fungsi untuk memasukkan data buku ke dalam array
void inputan(Buku dftBuku[], int& jmlBuku) {
    int input;
    cout << "Masukkan jumlah buku yang ingin anda input: ";
    cin >> input;

//jika jumlah buku yang diinput kurang dari 10 atau lebih dari 50, maka akan muncul pesan error
    if (input < 10 || input > 50) {
        cout << "Jumlah buku yang anda input harus lebih dari 10 dan kurang dari 50!"<<endl;
        return;
    }

    cin.ignore();
    
    //input data buku
    for (int i = 0; i < input; i++) {
        cout << "Masukkan judul buku " << (jmlBuku + 1) << ": ";
        getline(cin, dftBuku[jmlBuku].jdlBuku);
        cout << "Masukkan tahun terbit: ";
        cin >> dftBuku[jmlBuku].thTerbit;
        cin.ignore();
        jmlBuku++;
    }

    //menyalin data buku ke array dftBukuAsli
    if (jmlBuku == input) {
        salinanData(dftBuku, dftBukuAsli, jmlBuku);
    }
}

//fungsi untuk menampilkan daftar buku
void tampilkan(const Buku dftBuku[], int jmlBuku) {
    for (int i = 0; i < jmlBuku; i++) {
        cout << dftBuku[i].jdlBuku << " - " << dftBuku[i].thTerbit << endl;
    }
}

//fungsi untuk menyorting data buku dengan bubble sort
void bubble(Buku dftBuku[], int jmlBuku) {

    //mengembalikan data buku ke kondisi semula sebelum diurutkan
    resetData();

    for (int i = 0; i < jmlBuku - 1; i++) {
        for (int u = 0; u < jmlBuku - i - 1; u++) {
            if (dftBuku[u].thTerbit > dftBuku[u + 1].thTerbit) {
                swap(dftBuku[u], dftBuku[u + 1]);
            }
        }
    }
}

//fungsi untuk menyorting data buku dengan quick sort
void quick(Buku dftBuku[], int awal, int akhir) {
    if (awal >= akhir) return;
    int low = awal, high = akhir;

    //memilih pivot di tengah
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

//rekursif untuk menyortir bagian kiri dan kanan pivot
   quick(dftBuku, awal, high);
   quick(dftBuku, low, akhir);
}

//fungsi untuk mencari tahun terbit buku dengan sequential search
int sequential(const Buku dftBuku[], int jmlBuku, int tahun) {
    for (int i = 0; i < jmlBuku; i++) {
        if (dftBuku[i].thTerbit == tahun) {
            return i;
        }
    }
    return -1;
}

//fungsi untuk mencari tahun terbit buku dengan binary search
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

//switch case untuk memilih menu
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