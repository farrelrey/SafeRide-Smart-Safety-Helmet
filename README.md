![SafeRide](ASSET/Banner.png)

---
<h2 align="center">Quick Links</h2>
<p align="center">
  <a href="https://youtu.be/9iiEuZCZQvA"><img src="https://img.shields.io/badge/-VIDEO%20INTRO-64C5EB?style=flat-square&logo=youtube&logoColor=white" alt="Video Intro"></a>
  <br><br>
  <a href="https://wokwi.com/projects/466427513857531905"><img src="https://img.shields.io/badge/-SIMULASI%20WOKWI-64C5EB?style=flat-square&logo=arduino&logoColor=white" alt="Simulasi Wokwi"></a>
  <a href="https://canva.link/0y12v4yw2tn06bz"><img src="https://img.shields.io/badge/-PPT%20CANVA-64C5EB?style=flat-square&logo=canva&logoColor=white" alt="PPT Canva"></a>
</p>

---

# SafeRide: Sistem Helm Pintar guna Keselamatan Berkendara Berbasis ATmega2560 untuk Mengatasi Risiko Kelelahan dan Kecelakaan pada Ojek Online Kota Surabaya dalam Mendukung SDGs No. 3 Kehidupan Sehat dan Sejahtera

> **Sering merasa lelah, mengantuk, atau khawatir dengan risiko tak terduga saat membelah jalanan kota?** 

Bagi para pejuang jalanan khususnya rekan-rekan **Ojek Online di Kota Surabaya** yang setiap hari menantang padatnya lalu lintas dengan mobilitas super tinggi keselamatan adalah taruhan utama. Di sinilah **SafeRide** hadir membawa perubahan! Kami mendefinisikan ulang fungsi helm pelindung: dari sekadar alat pasif penahan benturan, menjadi **Asisten Keselamatan Aktif berbasis IoT** yang cerdas dan responsif. Dengan SafeRide, kamu tidak lagi berkendara sendirian. Kami mengintegrasikan teknologi mikrokontroler demi memastikan kamu berangkat produktif, dan **pulang ke rumah dengan selamat**. 

*Bersama SafeRide, mari buat perjalanan menjadi lebih aman, tenang, dan terlindungi di setiap kilometer!* 🏁🛡️

---

## 🎯 Tujuan Proyek

1. **Implementasi Sistem Deteksi Kantuk (Anti-Nodding):** Memanfaatkan sensor IMU untuk mendeteksi perubahan orientasi atau gerakan kepala berulang ke arah depan secara tidak wajar yang menjadi indikasi mikro-tidur (*micro-sleep/nodding*).
   
2. **Implementasi Sistem Fall Detection:** Mengintegrasikan data percepatan linier 3-sumbu dari akselerometer dan kecepatan sudut dari giroskop untuk mendeteksi deviasi kemiringan ekstrem dan hentakan kinetik secara *real-time* saat terjadi kecelakaan.

3. **Early Warning System (Feedback Motor Vibrator & Buzzer):** Memberikan respons peringatan instan kepada pengendara yang terindikasi mengantuk berupa getaran melalui *Vibration Motor & Buzzer* yang dikendalikan via pin PWM (Pulse Width Modulation) ATmega2560.
   
4. **Sistem Darurat Terintegrasi Server & Manual Trigger:** Mengirimkan data telemetri dan sinyal bahaya secara otomatis ke *server* ketika insiden jatuh terkonfirmasi. Menyediakan Tombol Manual Darurat (*Emergency Button*) pada helm sebagai cadangan (*redundancy system*) jika sistem otomatis gagal mendeteksi atau dalam kondisi bahaya lainnya.

---
## 👥 Anggota Tim
![SafeRide](PPT/SLIDE1.png)

| NRP | Nama | Jobdesk | Akun |
| :--- | :--- | :--- | :--- |
| 2124600033 | Farrel Reyhan Priyatnah | Project Manager | [farrelrey](https://github.com/farrelrey) |
| 2124600036 | Rafie Islamay Murdianto | 3D Designer| [RafieIslamay](https://github.com/rafieislamaym-blip) |
| 2123600043 | Rifkie Surya Rahmaputra | Progammer | [RifkieSurya](https://github.com/Rifkiesurya44) |
| 2124600053 | Arda Arinal Chusna | Hardware | [ArdaArinal](https://github.com/ardaarinalc-ux) |
| 2124600041 | Naurah Carina Wantoro | UI/UX Designer | [NaurahCarina](https://github.com/NaurahCarinaW) |
| 2124600045 | Wahyu Rizky Setyawan | QA | [WahyuSetyawan](https://github.com/wahyusetiyawan71-glitch) |

### 🏫 Supported By

* **Dosen Pengampu:** Akhmad Hendriawan ST., MT. (NIP. 197501272002121003)
* **Mata Kuliah:** Mikrokontroler
* **Program Studi:** D4 Teknik Elektronika
* **Institusi:** Politeknik Elektronika Negeri Surabaya

---
## 🎬 Video Produk


https://github.com/user-attachments/assets/c504996d-90f0-4de0-bc77-203e64780596


---
## 🖼️ Preview Presentasi

[![Lihat Presentasi](https://img.shields.io/badge/LIHAT-PRESENTASI-0084FF?style=flat-square)](https://canva.link/0y12v4yw2tn06bz)

> Klik tombol di atas untuk membuka presentasi secara penuh di Canva.
---
## 🛠️ Komponen 
1. **Arduino Mega (ATmega2560):** Otak utama sistem yang berfungsi memproses seluruh data dari sensor dan mengendalikan modul keluaran secara cepat dan efisien.
2. **Sensor IMU MPU6050 (Gyroscope + Accelerometer):** Sensor inersia presisi tinggi yang bertugas membaca orientasi, tingkat kemiringan helm, dan mendeteksi gerakan mengangguk (*nodding*) saat mengantuk maupun kondisi ekstrem saat terjatuh.
3. **Motor Vibrator:** Modul aktuator yang memberikan respons getaran instan langsung ke helm sebagai peringatan taktil agar pengendara segera terjaga saat terdeteksi *micro-sleep*.
4. **Buzzer:** Output peringatan suara (*auditory alert*) yang bekerja bersamaan dengan vibrator untuk memberikan alarm peringatan ganda saat kondisi darurat.
5. **Panic Button Switch:** Tombol darurat fisik yang ditempatkan pada posisi strategis helm sebagai pemicu manual (*manual trigger*) untuk mengirim sinyal bahaya ke server dalam kondisi darurat lainnya.
---

## ⚙️ HARDWEAR
desain hardware SafeRide dirancang sebagai sistem helm pintar guna keselamatan berbasis ATmega256 untuk mengatasi risiko kelelahan dan kecelakaan pada ojek online Kota Surabaya. sistem ini mengunakan sensor guna memantau gerakan pada helm dan memberikan output secara langsung bila terjadi gerakan yang di tentukan 

##  🔋 PCB
> Schematic
<img width="2387" height="1658" alt="schematic" src="https://github.com/user-attachments/assets/8dd8d0d6-5741-4d8a-a544-583d6f0a56cf" />

> Layout PCB
<img width="424" height="796" alt="Layout 2D" src="https://github.com/user-attachments/assets/b77f74a6-45b1-4bd5-ac8c-83ce20110544" />

> 3D PCB
<img width="667" height="545" alt="Layout 3D" src="https://github.com/user-attachments/assets/5847e991-36bc-476a-853d-e87d3a52b040" />

---
## ⚙️ 3D Produk
<img width="689" height="532" alt="3D SRH" src="https://github.com/user-attachments/assets/728f0835-bd6a-4073-9e50-563e0bf6c0d6" />
<img width="1012" height="556" alt="3D SR" src="https://github.com/user-attachments/assets/4fa0129c-5a7d-408d-b2a0-8e876595c48b" />
<img width="974" height="653" alt="3D SR (2)" src="https://github.com/user-attachments/assets/a7f48a3a-0cbd-4e74-9d4b-5d6654798721" />
<img width="706" height="425" alt="3D SR (3)" src="https://github.com/user-attachments/assets/2b4efaa1-4c6a-4c1a-967a-1814bcf62e4c" />

## 🏗️ Visualisasi Sistem
<img width="843" height="587" alt="image" src="https://github.com/user-attachments/assets/b6f2c31a-b717-4034-ace2-bab56c2d034b" />


---
## 💡PROGRAM

## 🖥️ Tampilan UI/UX
![SafeRide](UI%20UX/SafeRIde.jpg)

---
## SIMULASI
[![Lihat Simulasi](https://img.shields.io/badge/LIHAT-SIMULASI-0084FF?style=flat-square)](https://wokwi.com/projects/466427513857531905)

> Klik tombol di atas untuk membuka simulasi secara penuh pada wokwi.

---
## 💻 Software Tools
---
