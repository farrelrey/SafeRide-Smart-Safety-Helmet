# SafeRide: Sistem Helm Kerja Pintar guna Keselamatan Berkendara Berbasis ATmega2560 untuk Mengatasi Risiko Kelelahan dan Kecelakaan pada Ojek Online Kota Surabaya dalam Mendukung SDG No. 3: Kehidupan Sehat dan Sejahtera
Proyek ini merupakan rancang bangun helm pintar berbasis mikrokontroler ATmega2560 yang berfungsi untuk memonitor kondisi pengendara, memberikan peringatan dini saat mengantuk, serta melakukan panggilan darurat otomatis apabila terjadi kecelakaan (deteksi ketika terjatuh) dan hal lain yang menyangkut keselamatan kerja 

---

## Tujuan Proyek

1. Implementasi Sistem Deteksi Kantuk: Memanfaatkan sensor inersia (IMU) untuk mendeteksi perubahan orientasi atau gerakan kepala berulang yang tidak wajar (indikasi mikro-tidur/nodding).
   
2. Implementasi Sistem Fall Detection: Mengintegrasikan data percepatan linier 3-sumbu dari akselerometer dan kecepatan sudut dari giroskop untuk mendeteksi deviasi kemiringan ekstrem secara real-time.

3. Early Warning System:  Respons peringatan dini kantuk berupa getaran menggunakan Vibration Motor yang dikendalikan melalui pin Analog Output / PWM (Pulse Width Modulation) ATmega2560.
   
4. Sistem Panggilan Darurat Otomatis dan tombol darurat: Komunikasi darurat yang dapat mengirimkan sinyal secara otomatis ketika insiden kecelakaan (jatuh) terkonfirmasi dan terdapat Tombol Manual Darurat Pemicu (Manual Trigger) sebagai cadangan (backup) jika sistem otomatis (fall detection) gagal mendeteksi kecelakaan.



---
### Support By

* Dosen Pengampu: Akhmad Hendriawan ST., MT. (NIP. 197501272002121003)
* Mata Kuliah: Mikrokontroler
* Program Studi: D4 Teknik Elektronika
* Politeknik Elektronika Negeri Surabaya

---
## Anggota Tim

| NRP | Nama | Jobdesk | Akun |
| :--- | :--- | :--- | :--- |
| 21246000 |  | Project Manager | []() |
| 21246000 |  | 3D Designer| []() |
| 21246000 |  | Progammer | []() |
| 2124600041 | Naurah Carina Wantoro | UI/UX Designer | []() |
| 2124600045 | Wahyu Rizky Setyawan | QA | [WahyuSetyawan](https://github.com/wahyusetiyawan71-glitch) |
| 21246000 |  | Hardware | []() |
