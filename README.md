# SafeRide: Smart Safety Helmet
Proyek ini merupakan rancang bangun helm pintar berbasis mikrokontroler ATmega2560 yang berfungsi untuk memonitor kondisi pengendara, memberikan peringatan dini saat mengantuk, serta melakukan panggilan darurat otomatis apabila terjadi kecelakaan (deteksi ketika terjatuh) dan hal lain yang menyangkut keselamatan kerja 

---

## Tujuan Proyek

1. Implementasi Sistem Deteksi Kantuk: Mengintegrasikan sensor parameter fisik/fisiologis untuk mendeteksi tingkat kelelahan pengendara dan memberikan respons peringatan dini berupa getaran halus secara bertahap menggunakan output analog (PWM).

2. Implementasi Sistem Fall Detection: Memanfaatkan sensor giroskop dan akselerometer untuk mengenali perubahan sudut kemiringan ekstrem dan mendeteksi kondisi pengendara saat terjatuh secara real-time.

3. Sistem Panggilan Darurat Otomatis: Membangun modul komunikasi darurat yang dapat mengirimkan sinyal bantuan koordinat lokasi secara otomatis ketika insiden kecelakaan (jatuh) terkonfirmasi.

3. Optimasi Pemrosesan Data I/O: Menerapkan pengolahan sinyal berbasis interupsi dan pembacaan multi-parameter yang seimbang antara Analog Input/Output dan Digital Input/Output memanfaatkan kapasitas pin ekstensif pada arsitektur ATmega2560.

---

