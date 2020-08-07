# 930.01
Tırtıl Project

### Yapilan degisiklikler:



##### 7 Agustos 2020 @Faruk:
1. Menu icin stateMachine fonksiyonu olusturuldu.
1. Olusturulan 4 adet ayar menusu 6 adet state bulunmaktadır. 
1. SecretMenu secenegi olusturuldu. Bu kısıma sadece "PAUSE_MENU" state'inde dallanilabilir. PID parametreleri buradan degistirilebilir.
1. Menuleri tek tek aciklayacak olursak;
   a. MAIN_MENU: Surus algoritamsinin olacagi yer burasidir. "DRIVER_TIME_SETTING", "STOP_MENU", "PAUSE_MENU" buradan dalanilir.
   b. DRIVER_TIME_SETTING: Surus zamaninin ayarlandigi yer burasidir. Menu tusu ile menuler arasinda gezinti yapilabilir. Menu tusuna uzun basilarak menuden cikis yaplabilir.
   c. STOP_TIME_SETTING: Cizgiden cikildiginda aracin ne kadar zamanda duracagi burada ayarlanir.
   d. SPEED_LIMIT_SETTING: PWM hiz limitlenmeleri 5 seviye seklinde burada ayarlanilir.
   e. STOP_MENU: Surus zamani bittiginde bu state'te dallanir. START butonuna basilarak ayarlanmis olan zamana gore surus yeniden baslatilir.
   f. START_MENU: Surus baslar.
   g. PAUSE_MENU: Surus bekletilir.
   h. EXIT_LINE: Cizgiden ciktiginda isletilecek algoritma.
   i. SECRET_MENU: PID parametrelerini ayarlamak icin kullanilan menu. 
