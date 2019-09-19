# 한글 설치

### Locale 설정

![d](https://mblogthumb-phinf.pstatic.net/MjAxODA2MjlfMTEz/MDAxNTMwMjg0MTA0NjAw._Ep4BA1vMQS-Gl8Dicqsr-Dsh5AaB66rKQgjuhv9ldUg.pWg1Z17rtqYuR5hbjoYO1VzYGec4Y7VKfpgRhMOgWCkg.JPEG.21ahn/7.JPG?type=w2)

Preferences -> Raspberry Pi Configuration 또는 terminal 에서 sudo raspi-config를 통해 pi 설정창에 접속

Localisation에서 Locale, Timezone, Keyboard를 바꿔준다.

```
ibus의 경우 
Locale은 Language : en(English), Country : US(United States), Character Set  : UTF-8

fcitx의 경우
Locale은 Language : ko(Korean), Country : KR(Republic of Korea), Character Set : UTF-8
```

TimeZone

```
Area : Asia
Location : Seoul
```

Keyboard

```
Model : Generic 105-key(Intl) PC
Layout : Korean
Variant : Korean (101/104 key compatible)
```



### fcitx 한글 입력기 설치

설정을 위와 같이 변경하면 한글이 다음과 같이 깨져 보인다.

![ë¼ì¦ë² ë¦¬íì´ ë¼ì¦ë¹ì ë¦¬ëì¤ íê¸ ê¹¨ì§ ë¬¸ì í´ê²° ë°©ë²](https://t1.daumcdn.net/cfile/tistory/2228913F595B89B60D)

이를 해결하기 위해 Terminal을 키고 fonts-unfonts-core과 나눔폰트를 설치한다.

```
sudo apt-get upgrade; sudo apt-get update
sudo apt-get install fonts-nanum fonts-unfonts-core
```

apt-get upgrade와 update로 라이브러리 및 패키지들을 최신화한다.  ; 을 붙이면 명령어를 연속적으로 실행한다.

apt-get install의 경우 띄어쓰기 단위로 설치하기 때문에 위와 같이 입력하면 두 폰트 모두 설치된다.

```
sudo apt-get install fcitx fcitx-hangul
im-config -n fcitx
sudo vim ~/.config/fcitx/config -> ShowInputWindowAfterTriggering = False 로 변경 후 저장
reboot
```

마찬가지로 한글 입력기인 fcitx를 설치한다. 이후 im-config -n fcitx 를 한 후 reboot을 한다.



<!--Linux의 한글 입력기는 대표적으로 세 개가 있다.-->

1.  ibus : 가장 많이 사용하는 한글 입력기, Locale을 영어로 해야되고 띄어쓰기가 잘 안되는 단점이 있음.
2.  nabi : 업데이트가 다소 늦음.
3.  fcitx : 설치가 편리하고 사용하기 편함.