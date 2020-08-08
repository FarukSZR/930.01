# 930.01
Tırtıl Project

### Yapilacak degisiklikler:

1. speed_controller library'de bulanan def_speed max_speed min_speed HIZ_LIMITI parametresine gore tekrar duzenlenecek.
1. Sensor kalibrasyonlari eklenecek.
1. Cizgiden cikildiginda durma fonksiyonu eklenecek. 

### Yapilan degisiklikler:


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
