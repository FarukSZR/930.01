# 930.01
Tırtıl Project

### Yapilacak degisiklikler:

1. speed_controller library'de bulanan def_speed max_speed min_speed HIZ_LIMITI parametresine gore tekrar duzenlenecek.
1. Sensor kalibrasyonlari eklenecek.
1. Cizgiden cikildiginda durma fonksiyonu eklenecek. 



### Yapilan degisiklikler:

##### 24 Agustos 2020 @Faruk:
1. PWM degerlerinini arttirilmasi icin DEBUG ifdef yapisi kuruldu. PWM debug kod icerisinde acilaksa eger "loopTaskMenuControl" fonksiyonu icerisindeki 
"stateMachine" fonksiyonu comment edilmeli ve main icerisinde bulunan #define DEBUG tanimlasi aktif edilmelidir.
1. 4x20 LCD ekran icin gerekli #ifdef yapisi kuruldu. ADC degerlerini ekrana basiyor.Bunu aktif etmek icin "fs_speed_controller.c" icerisinde #define LCD_4x20
tanimlamasi yapilmalidir.
1. KP ve KD degerlerinin artis ve azalis miktarlari 0.01 hassasiyetine indirildi.

##### 16 Agustos 2020 @Faruk:
1. Kullanilacak donanima uygun pin ayarlamalari yapildi.
1. Buton, LCD, ADC, PWM kutuphaneleri ilgili donanima gore guncellendi.
1. Timer icerisinde bulunan menu icerisinde gezerken saniye saymasi bug_fix giderildi.
1. stopMotor ve startMotor fonksiyonlari olusturuldu. 
   - startMotor fonksiyonu icerisinde adc cevrimlerinden gelen degiskenlerin durumuna gore PID algoritmasi kosuyor. Buna bagli olarak motorlara ilgili PWM'lerin gonderilmesi bu fonksiyonda isletiliyor.   
   - stopMotor fonksiyonu menu icerisinde gezerken, stop ve pause komutlarinda devreye aliniyor.
1. LCD ekranda acilis betigi eklendi.
1. LCD okuma yazma delay eklendi. (Yaklasik 40us)
1. ADC coversion time parametresi eklendi. Timer interrupti icerisinde 10ms'de bir adc cevrimleri kanallari gezer. 8 kanal x 10ms = 80ms Adc cevrim sureleri.

##### 11 Agustos 2020 @Faruk:
1. ADC pinleri schematic'e gore duzenlendi.
1. LCD pinleri schematic'e gore duzenlendi.
1. Buton pinleri schematic'e gore duzenlendi.
1. stopMotor ve startMotor fonksiyonlari eklendi.
1. startMotor fonksiyonu start butonuna basildinda aktiflesiyor.
1. stopMotor menu icerisinde dolanirken ve pause-stop butonlari aktif oldugunda aktiflesiyor.


##### 8 Agustos 2020 @Faruk:
1. LCD library'de bulunan birkac bug giderildi.
1. PWM fonksiyonlari yazildi.
1. PID algoritmasi duzenlendi.
1. eeprom kayit ve init eeprom degerleri yazildi.

##### 7 Agustos 2020 @Faruk:
1. Menu icin stateMachine fonksiyonu olusturuldu.
1. Olusturulan 4 adet ayar menusu 6 adet state bulunmaktadır. 
1. SecretMenu secenegi olusturuldu. Bu kısıma sadece "PAUSE_MENU" state'inde dallanilabilir. PID parametreleri buradan degistirilebilir.
1. Menuleri tek tek aciklayacak olursak;
   - MAIN_MENU: Surus algoritamsinin olacagi yer burasidir. "DRIVER_TIME_SETTING", "STOP_MENU", "PAUSE_MENU" buradan dalanilir.
   - DRIVER_TIME_SETTING: Surus zamaninin ayarlandigi yer burasidir. Menu tusu ile menuler arasinda gezinti yapilabilir. Menu tusuna uzun basilarak menuden cikis yaplabilir.
   - STOP_TIME_SETTING: Cizgiden cikildiginda aracin ne kadar zamanda duracagi burada ayarlanir.
   - SPEED_LIMIT_SETTING: PWM hiz limitlenmeleri 5 seviye seklinde burada ayarlanilir.
   - STOP_MENU: Surus zamani bittiginde bu state'te dallanir. START butonuna basilarak ayarlanmis olan zamana gore surus yeniden baslatilir.
   - START_MENU: Surus baslar.
   - PAUSE_MENU: Surus bekletilir.
   - EXIT_LINE: Cizgiden ciktiginda isletilecek algoritma.
   - SECRET_MENU: PID parametrelerini ayarlamak icin kullanilan menu. 
