# Sisop-5-2025-IT33

## Kelompok

Nama | NRP
--- | ---
Revalina Erica Permatasari | 5027241007
Kaisar Hanif Pratama | 5027241029
Ni'mah Fauziyyah Atok | 5027241103

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan
Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini. <br>

Berikut beberapa fungsi yang didefinisikan di header file:
- `kernel.h` <br>
Kode : <br>
```
extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);
unsigned int getBiosTick();

void printString(char* str); // Mencetak string ke layar.
void readString(char* buf); // Membaca string dari keyboard.
void clearScreen(int color); // Membersihkan layar dengan warna tertentu.
void setTextColor(int color); // Mengatur warna teks.
```

- `shell.h` <br>
Kode : <br>
```
void shell(); //Menjalankan shell utama
void parseCommand(char *buf, char *cmd, char arg[2][64]); //Memecah input jadi command dan argumen
void handleCommand(char *cmd, char *buf, char arg[2][64]); // Mengeksekusi perintah yang dimasukkan
void showPrompt();  //Menampilkan prompt shell
void setColor(int color); //Mengatur warna teks (aliansi dari setTextColor)
```

- `std_lib.h` <br>
Kode : <br>
```
int div(int a, int b); //operasi pembagian
int mod(int a, int b); // sisa pembagian

bool strcmp(char *str1, char *str2); //membandingkan dua string, hasil true jika sama
void strcpy(char *dst, char *src); //menyalin string dari src ke dst
void clear(byte *buf, unsigned int size); //mengosongkan buffer dengan ukuran tertentu

void atoi(char *str, int *num); //mengubah string jadi int
void itoa(int num, char *str); //mengubah int jadi string
```

- `std_type.h` <br>
Kode : <br>
```
typedef unsigned char byte; 

//tipe boolean sbg char
typedef char bool;
#define true 1 //true
#define false 0 // false
```

### Soal
1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan
anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```
   Jawaban :
   ```
   else {
    printString(buf); // echo
   }
   ```
   Penjelasan:
   Bagian ini terdapat di fungsi handleCommand dalam `shell.c`. Jika input pengguna (cmd) tidak cocok dengan perintah yang dikenali (misalnya user, grandcompany, add, dsb), maka program akan mencetak ulang isi dari buf (input pengguna), seperti efek "Echo".

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```
   Jawaban :
   ```
    else if (strcmp(cmd, "yo")) {
        printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt")) {
        printString("yo\r\n");
    }
   ```
   Penjelasan:
   - `"yo"` → output `"gurt"`
   - `"gurt"` → output `"yo"`

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```
   Jawaban :
   ```
   if (strcmp(cmd, "user")) {
    if (arg[0][0] == '\0') strcpy(username, "user");
    else strcpy(username, arg[0]);
    printString("Username changed to "); printString(username); printString("\r\n");
    }
   ```
   Penjelasan:
   Fungsi ini menangani perubahan username sesuai input. Bila hanya mengetik user, maka nama di-reset ke "user". Bila user <nama>, maka username diubah menjadi <nama>.

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```
   Jawaban :
   ```
   else if (strcmp(cmd, "grandcompany")) {
    if (strcmp(arg[0], "maelstrom")) {
        setColor(0x0C); strcpy(companyTag, "@Storm");
    }
    else if (strcmp(arg[0], "twinadder")) {
        setColor(0x0E); strcpy(companyTag, "@Serpent");
    }
    else if (strcmp(arg[0], "immortalflames")) {
        setColor(0x0B); strcpy(companyTag, "@Flame");
    }
    else printString("Unknown company\r\n");
    }
    .
    .
    else if (strcmp(cmd, "clear")) {
    setColor(0x07);
    companyTag[0] = '\0';
    }
   ```
   Penjelasan:
   Perintah `grandcompany` akan memanggil `setColor` untuk mengubah warna terminal:
   - Merah (0x0C) untuk `maelstrom`
   - Kuning (0x0E) untuk `twinadder`
   - Biru (0x0B) untuk `immortalflames`
   Nama pengguna juga diberi tambahan seperti `@Storm`, `@Serpent`, atau `@Flame`.
   Command `clear` mengatur ulang warna ke default (putih) dan menghapus tag grand company dari prompt.

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```
   Jawaban :
   Serpihan contoh dari `add`:
   ```
   else if (strcmp(cmd, "add")) {
    atoi(arg[0], &a); atoi(arg[1], &b);
    result = a + b;
    itoa(result, output);
    printString(output); printString("\r\n");
    }
   ```
   Penjelasan:
   - `atoi` mengonversi string ke integer.
   - Operasi matematika dilakukan (`a + b`, `a - b`, dst).
   - Hasil dikonversi kembali ke string dengan `itoa`.
   - `div` memiliki pengecekan pembagi nol.

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```
   Jawaban :
   ```
    else if (strcmp(cmd, "yogurt")) {
    unsigned int t = getBiosTick();
    int idx = mod(t, 3);
    printString("gurt> ");
    if (idx == 0) printString("yo\r\n");
    else if (idx == 1) printString("ts unami gng </3\r\n");
    else printString("sygau\r\n");
    }
   ```
   Penjelasan:
   - `"yogurt"` → secara acak (menggunakan BIOS tick count dan fungsi `mod`) memilih satu dari tiga respons berbeda: `"yo"`, `"ts unami gng </3"`, atau `"sygau"`.

7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini. <br>

   Jawaban :
   ```
    CFLAGS = -ansi -Iinclude

    prepare:
        mkdir -p bin
        dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

    bootloader:
        nasm -f bin src/bootloader.asm -o bin/bootloader.bin
        dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

    stdlib:
        bcc $(CFLAGS) -c src/std_lib.c -o bin/std_lib.o

    shell:
        bcc $(CFLAGS) -c src/shell.c -o bin/shell.o

    kernel:
        nasm -f as86 src/kernel.asm -o bin/kernel-asm.o
        bcc $(CFLAGS) -c src/kernel.c -o bin/kernel.o
        
    link:
        ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o bin/std_lib.o bin/shell.o
        dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc

    build: prepare bootloader stdlib shell kernel link

    clean:
        rm -f bin/*

    all: clean build
   ```
   Penjelasan:
   Makefile ini meng-otomatisasi proses kompilasi dan build untuk EorzeOS:
   - prepare: Membuat folder `bin` dan image kosong `floppy.img` sebesar 1.44MB.
   - bootloader: Meng-assemble `bootloader.asm` ke format binary, lalu menyalinnya ke sektor pertama disket (`floppy.img`).
   - stdlib, shell, kernel: Masing-masing meng-compile file `.c` dan `.asm` ke object file.
   - link: Menggabungkan seluruh object file menjadi satu binary (`kernel.bin`) lalu menaruhnya di sektor 1 image.
   - build: Memanggil seluruh tahapan di atas secara berurutan.
   - clean: Menghapus semua file dalam `bin/`.
   - all: Membersihkan lalu membangun ulang sistem.
