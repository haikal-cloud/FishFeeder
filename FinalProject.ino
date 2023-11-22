//RTC
#include "RTClib.h" //Library real time clock.lib yang zipnya sudah didownload
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"}; //Array variabel cchar untuk data hari
String hari;//menyimpan nilai hari
int tanggal, bulan, tahun, jam, menit, detik;//deklarasi tanggal, bulan, tahun dll.
float suhu; //deklarasi suhu dalam bentuk float

//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//set address I2C dan besar karakter untuk LCD 16X2

//SERVO
#include <Servo.h>
Servo mekanik;

void setup () {
  Serial.begin(9600); //Menentukan kecepatan dan penerimaan data melalui port serial , yaitu 9600 detik

  //LCD
  lcd.begin(); // inisialisasi LCD

  //SERVO
  mekanik.attach(4); //deklarasi servo pada pin (sinyal data kabel motor servo diconnectan dipin 4 arduino)
  mekanik.write(0); //mengontrol motor servo agar berputar kesiudut 0 derajat

  //RTC
  if (! rtc.begin()) { //Fungsi ketika rtc tidak ditemukan, yang bisa disebabkan karena kerusakan kabel, kesalahan pemasangan dll.
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush(); //Untuk pengosongan data pembacaan pad abuffer
    abort(); //Perintah untuk membatalkan jalannya suatu program secara paksa dan mengembalikan ke sistem operasi
  }

  //Atur Waktu
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Pengatur waktu berdasar waktu yang ada dikomputer kita
  //  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void KasihPakan(int jumlah){
  for (int i = 1; i <= jumlah; i++){
    mekanik.write(150);
    delay(100);
    mekanik.write(0);
    delay(100);
    
  }
}


void loop () {  //Untuk memanggil data-data yang realtime
  //RTC 
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()]; //Hari dalam angka , sesuai urutan dimulai dari minggu 
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
  suhu    = rtc.getTemperature();
  Serial.println(String() + hari + ", " + tanggal + "-" + bulan + "-" + tahun);
  Serial.println(String() + jam + ":" + menit + ":" + detik);
  Serial.println(String() + "Suhu: " + suhu + " C");
  Serial.println();

  //LCD.LOOP
  lcd.setCursor(0,0);
  lcd.print(String() + hari + "," + tanggal + "-" + bulan + "-" + tahun);
  lcd.print(" ");
  lcd.setCursor(0,1);
  lcd.print(String() + jam + ":" + menit + ":" + detik);
  lcd.print(" | ");
  lcd.print(suhu);
  lcd.print(" ");

  //KONDISI/LOGIKA
 if(jam == 16 & menit == 25 & detik == 1){
   KasihPakan(2);

 }
 if(jam == 16 & menit == 25 & detik == 10 ){
   KasihPakan(3);
 }

 if(jam == 16 & menit == 25 & detik == 18 ){
   KasihPakan(5);
 }

 if(jam == 16 & menit == 25 & detik == 28 ){
   KasihPakan(5);
 }
  delay(1000);
}