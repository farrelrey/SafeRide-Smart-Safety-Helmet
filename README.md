# SafeRide: Smart Safety Helmet
Proyek ini merupakan rancang bangun helm pintar berbasis mikrokontroler ATmega2560 yang berfungsi untuk memonitor kondisi pengendara, memberikan peringatan dini saat mengantuk, serta melakukan panggilan darurat otomatis apabila terjadi kecelakaan (deteksi ketika terjatuh) dan hal lain yang menyangkut keselamatan kerja 

---

## Tujuan Proyek

1. Implementasi Sistem Deteksi Kantuk: Memanfaatkan sensor inersia (IMU) untuk mendeteksi perubahan orientasi atau gerakan kepala berulang yang tidak wajar (indikasi mikro-tidur/nodding).
   
2. Implementasi Sistem Fall Detection: Mengintegrasikan data percepatan linier 3-sumbu dari akselerometer dan kecepatan sudut dari giroskop untuk mendeteksi deviasi kemiringan ekstrem secara real-time.

3. Early Warning System:  Respons peringatan dini kantuk berupa getaran menggunakan Vibration Motor yang dikendalikan melalui pin Analog Output / PWM (Pulse Width Modulation) ATmega2560.
   
4. Sistem Panggilan Darurat Otomatis dan tombol darurat: Komunikasi darurat yang dapat mengirimkan sinyal secara otomatis ketika insiden kecelakaan (jatuh) terkonfirmasi dan terdapat Tombol Manual Darurat Pemicu (Manual Trigger) sebagai cadangan (backup) jika sistem otomatis (fall detection) gagal mendeteksi kecelakaan.



---

