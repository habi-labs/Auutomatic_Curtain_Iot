# 🪟 Automatic Curtain IoT

> Gorden otomatis berbasis IoT yang membuka dan menutup sesuai kondisi atau perintah pengguna.

## 🎯 Latar Belakang
Proyek mandiri untuk membangun sistem smart home sederhana: gorden yang bergerak otomatis
tanpa perlu ditarik manual.

## ✨ Fitur
- Buka/tutup gorden otomatis
- [isi: trigger, mis. sensor cahaya (LDR) / jadwal waktu / kontrol manual]
- [isi: kontrol jarak jauh, mis. Wi-Fi / MQTT / Blynk / web]

## 🔧 Komponen Hardware
| Komponen | Keterangan |
|---|---|
| Mikrokontroler | [mis. ESP32 / ESP8266 / Arduino] |
| Aktuator | [mis. motor stepper / servo / motor DC + driver] |
| Sensor | [mis. LDR / limit switch] |
| Catu daya | [mis. 5V / 12V] |

## 🔌 Skema Rangkaian
_Tambahkan gambar wiring/skematik di sini._

## 🛠️ Tech Stack
C++ · PlatformIO · [Arduino Framework]

## 🚀 Cara Menjalankan
1. Install [PlatformIO](https://platformio.org/) (VS Code extension atau CLI)
2. Clone repo:
   ```bash
   git clone https://github.com/habi-labs/Auutomatic_Curtain_Iot.git
   cd Auutomatic_Curtain_Iot
   ```
3. Build dan upload ke board:
   ```bash
   pio run --target upload
   ```
4. Pantau output serial:
   ```bash
   pio device monitor
   ```

## 📸 Demo
_Tambahkan foto/GIF/video gorden saat bekerja._

## 📄 Lisensi
MIT
