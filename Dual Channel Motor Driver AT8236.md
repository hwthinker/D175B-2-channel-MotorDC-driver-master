# D157B Dual Channel Motor Driver AT8236

![image-20260109072653406](./assets/image-20260109072653406.png)

## Diskripsi

Modul driver motor AT8236 ini dirancang khusus untuk mengendalikan dua motor DC dengan encoder-tachometer. Dengan performa tinggi, proteksi lengkap, dan desain yang kompatibel dengan Raspberry Pi, modul ini cocok untuk robot, mobil pintar, maupun sistem otomasi.

## Fitur Utama

- Mendukung rentang tegangan input 5.5 – 15V
- Regulator internal dengan keluaran 5V/5A dan 3.3V/0.5A
- Arus kontinu 3A per channel, arus puncak hingga 6A per channel
- Proteksi lengkap: arus lebih, hubung singkat, suhu berlebih, tegangan rendah, TVS
- Sirkuit deteksi tegangan VM onboard untuk memantau suplai secara real-time
- Dua pilihan input daya: terminal 2P atau jack DC (bisa digunakan untuk charging baterai)
- Mendukung PWM dengan frekuensi hingga 100 kHz dengan dead zone lebih kecil dibanding L298N
- Konektor catu daya: Terminal 2P atau jack DC 5.5×2.1 mm
- Konektor motor: XH2.54 6P
- Tegangan suplai: VM, 5V, 3.3V
- Dimensi produk: 66 × 56 mm
- Berat produk: 24.9 g
- Fungsi utama: mendukung kendali motor DC dengan encoder, rotasi maju/mundur, PWM presisi
- Deteksi tegangan: input sampling ADC untuk pembacaan suplai real-time
- Suplai logika: tidak perlu catu daya logika terpisah (ambil dari output internal 5V)
- Lubang pemasangan 49 × 58 mm, kompatibel dengan Raspberry Pi untuk stacking dan integrasi mudah

## Deskripsi Pin

- E1A, E1B : sinyal encoder motor 1 (A & B)
- E2A, E2B : sinyal encoder motor 2 (A & B)
- ADC : input sampling tegangan suplai (VM)
- GND : ground
- 5V : keluaran catu daya 5V
- 3V3 : keluaran catu daya 3.3V
- AIN1, AIN2 : sinyal kontrol motor 1 (Input 1 & 2)
- BIN1, BIN2 : sinyal kontrol motor 2 (Input 1 & 2)
- AO1, AO2 : output motor 1 (terminal positif & negatif)
- BO1, BO2 : output motor 2 (terminal positif & negatif)
- 5V (Motor Output) : suplai motor
- E1A, E1B (Motor Output) : sinyal encoder motor 1
- E2A, E2B (Motor Output) : sinyal encoder motor 2
- GND (Motor Output) : ground

Catatan tambahan: menggunakan konektor berlapis emas, lebih tahan oksidasi dan koneksi stabil

---

## Spesifikasi Modul Driver Motor AT8236 (MD220A)

| **Parameter** | **Spesifikasi** |
| --- | --- |
| **Model** | MD220A |
| **Arus Kontinu per Kanal** | 3A |
| **Arus Puncak per Kanal** | 6A |
| **Rentang Tegangan Input** | 5.5V ~ 15V |
| **Konektor Catu Daya** | Terminal 2P atau jack DC 5.5×2.1 mm |
| **Konektor Motor** | XH2.54 6P |
| **Tegangan Suplai** | VM, 5V, 3.3V |
| **Keluaran 5V** | 5A |
| **Frekuensi PWM** | 0 ~ 100 kHz |
| **Keluaran 3.3V** | 0.5A |
| **Dimensi Produk** | 66 × 56 mm |
| **Berat Produk** | 24.9 g |
| **Fitur Proteksi** | Proteksi arus lebih, proteksi suhu lebih, proteksi hubung singkat, proteksi TVS, kunci tegangan rendah |
| **Fungsi Utama** | Dapat mengendalikan motor DC dengan encoder, mendukung rotasi maju/mundur, mendukung PWM dengan dead zone lebih kecil dibanding L298N |
| **Deteksi Tegangan** | Ada input sampling ADC, mendukung pembacaan tegangan suplai |
| **Suplai Logika** | Tidak butuh catu daya logika terpisah (bisa ambil dari output internal 5V) |
| **Lubang Pemasangan** | 49 × 58 mm (kompatibel dengan lubang Raspberry Pi) |
| **Catatan Tambahan** | Menggunakan konektor berlapis emas, tahan oksidasi, koneksi lebih baik |

## Perbandingan Modul Driver Motor TB6612 vs AT8236

| **Nama Produk** | TB6612 Modul Driver Motor | AT8236 Modul Driver Motor |
| --- | --- | --- |
| **Model Modul** | TK-MD220A | TK-MD320A |
| **Model Chip** | TB6612FNG | AT8236 |
| **Paket Chip** | SSOP24 | ESOP-8 |
| **Rentang Tegangan VM** | 5.5 ~ 15V | 5.5 ~ 15V |
| **Frekuensi Output PWM** | 0 ~ 100K | 0 ~ 100K |
| **Jumlah Kanal Output** | 2 | 2 |
| **Arus Kontinu** | 1.2A | 3A |
| **Arus Puncak** | 3.2A | 6A |
| **Fitur Proteksi** | Proteksi arus lebih, proteksi suhu lebih | Proteksi arus lebih, proteksi suhu lebih, proteksi hubung singkat, kunci tegangan rendah |
| **Kelebihan Modul** | Driver motor klasik, penggunaan lebih luas | Performa lebih baik, dilengkapi proteksi arus lebih, kontrol panas lebih sedikit |

## Tabel Deskripsi Pin Modul Driver Motor

| **Jenis Port** | **Nama Pin** | **Deskripsi Pin** |
| --- | --- | --- |
| **MCU / Port Kendali Utama** | E1A | Sinyal encoder motor 1 A |
|  | E1B | Sinyal encoder motor 1 B |
|  | E2A | Sinyal encoder motor 2 A |
|  | E2B | Sinyal encoder motor 2 B |
|  | ADC | Sinyal input VM (tegangan suplai) |
|  | GND | Ground |
|  | 5V | Keluaran catu daya 5V |
|  | 3V3 | Keluaran catu daya 3.3V |
|  | AIN1 | Sinyal kontrol motor 1 – Input 1 |
|  | AIN2 | Sinyal kontrol motor 1 – Input 2 |
|  | BIN1 | Sinyal kontrol motor 2 – Input 1 |
|  | BIN2 | Sinyal kontrol motor 2 – Input 2 |

| **Jenis Port** | **Nama Pin** | **Deskripsi Pin** |
| --- | --- | --- |
| **Port Motor** | AO1 | Motor 1 output – terminal positif |
|  | 5V | Suplai motor 1 |
|  | E1B | Sinyal encoder motor 1 B |
|  | E1A | Sinyal encoder motor 1 A |
|  | GND | Ground |
|  | AO2 | Motor 1 output – terminal negatif |
|  | BO1 | Motor 2 output – terminal positif |
|  | 5V | Suplai motor 2 |
|  | E2B | Sinyal encoder motor 2 B |
|  | E2A | Sinyal encoder motor 2 A |
|  | GND | Ground |
|  | BO2 | Motor 2 output – terminal negatif |

## Tabel Deskripsi Pin Lengkap Modul Driver Motor

| **Jenis Port** | **Nama Pin** | **Deskripsi Pin** |
| --- | --- | --- |
| MCU / Kontrol | E1A | Sinyal encoder motor 1 A |
| MCU / Kontrol | E1B | Sinyal encoder motor 1 B |
| MCU / Kontrol | E2A | Sinyal encoder motor 2 A |
| MCU / Kontrol | E2B | Sinyal encoder motor 2 B |
| MCU / Kontrol | ADC | Sinyal input VM (tegangan suplai) |
| MCU / Kontrol | GND | Ground |
| MCU / Kontrol | 5V | Keluaran catu daya 5V |
| MCU / Kontrol | 3V3 | Keluaran catu daya 3.3V |
| MCU / Kontrol | AIN1 | Sinyal kontrol motor 1 – Input 1 |
| MCU / Kontrol | AIN2 | Sinyal kontrol motor 1 – Input 2 |
| MCU / Kontrol | BIN1 | Sinyal kontrol motor 2 – Input 1 |
| MCU / Kontrol | BIN2 | Sinyal kontrol motor 2 – Input 2 |
| Motor Output | AO1 | Motor 1 output – terminal positif |
| Motor Output | 5V | Suplai motor 1 |
| Motor Output | E1B | Sinyal encoder motor 1 B |
| Motor Output | E1A | Sinyal encoder motor 1 A |
| Motor Output | GND | Ground |
| Motor Output | AO2 | Motor 1 output – terminal negatif |
| Motor Output | BO1 | Motor 2 output – terminal positif |
| Motor Output | 5V | Suplai motor 2 |
| Motor Output | E2B | Sinyal encoder motor 2 B |
| Motor Output | E2A | Sinyal encoder motor 2 A |
| Motor Output | GND | Ground |
| Motor Output | BO2 | Motor 2 output – terminal negatif |
