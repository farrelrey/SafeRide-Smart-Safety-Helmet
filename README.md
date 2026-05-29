# SafeRide: Sistem Helm Pintar guna Keselamatan Berkendara Berbasis ATmega2560 untuk Mengatasi Risiko Kelelahan dan Kecelakaan pada Ojek Online Kota Surabaya dalam Mendukung SDG No. 3 Kehidupan Sehat dan Sejahtera
Proyek ini merupakan rancang bangun helm pintar berbasis mikrokontroler ATmega2560 yang berfungsi untuk memonitor kondisi pengendara, memberikan peringatan dini saat mengantuk, serta melakukan panggilan darurat otomatis apabila terjadi kecelakaan (deteksi ketika terjatuh) dan hal lain yang menyangkut keselamatan berkendara, difokuskan untuk membantu pengemudi ojek online di Kota Surabaya, mengingat tingginya mobilitas dan risiko kerja yang mereka hadapi di jalan raya. 

---

## 🎯 Tujuan Proyek

1. **Implementasi Sistem Deteksi Kantuk (Anti-Nodding):** Memanfaatkan sensor IMU untuk mendeteksi perubahan orientasi atau gerakan kepala berulang ke arah depan secara tidak wajar yang menjadi indikasi mikro-tidur (*micro-sleep/nodding*).
   
2. **Implementasi Sistem Fall Detection:** Mengintegrasikan data percepatan linier 3-sumbu dari akselerometer dan kecepatan sudut dari giroskop untuk mendeteksi deviasi kemiringan ekstrem dan hentakan kinetik secara *real-time* saat terjadi kecelakaan.

3. **Early Warning System (Feedback Motor Vibrator & Buzzer):** Memberikan respons peringatan instan kepada pengendara yang terindikasi mengantuk berupa getaran melalui *Vibration Motor & Buzzer* yang dikendalikan via pin PWM (Pulse Width Modulation) ATmega2560.
   
4. **Sistem Darurat Terintegrasi Server & Manual Trigger:** Mengirimkan data telemetri dan sinyal bahaya secara otomatis ke *server* ketika insiden jatuh terkonfirmasi. Menyediakan Tombol Manual Darurat (*Emergency Button*) pada helm sebagai cadangan (*redundancy system*) jika sistem otomatis gagal mendeteksi atau dalam kondisi bahaya lainnya.

---
### 🏫 Supported By

* **Dosen Pengampu:** Akhmad Hendriawan ST., MT. (NIP. 197501272002121003)
* **Mata Kuliah:** Mikrokontroler
* **Program Studi:** D4 Teknik Elektronika
* **Institusi:** Politeknik Elektronika Negeri Surabaya

---
## 👥 Anggota Tim

| NRP | Nama | Jobdesk | Akun |
| :--- | :--- | :--- | :--- |
| 2124600033 | Farrel Reyhan Priyatnah | Project Manager | [farrelrey](https://github.com/farrelrey) |
| 2124600036 | Rafie Islamay Murdianto | 3D Designer| [RafieIslamay](https://github.com/rafieislamaym-blip) |
| 2123600043 | Rifkie Surya Rahmaputra | Progammer | [RifkieSurya](https://github.com/Rifkiesurya44) |
| 2124600053 | Arda Arinal Chusna | Hardware | []() |
| 2124600041 | Naurah Carina Wantoro | UI/UX Designer | [NaurahCarina](https://github.com/NaurahCarinaW) |
| 2124600045 | Wahyu Rizky Setyawan | QA | [WahyuSetyawan](https://github.com/wahyusetiyawan71-glitch) |

