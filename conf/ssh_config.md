# SSH / VNC 설정

### SSH 설정

![1568878701732](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1568878701732.png)

Preferences -> Raspberry Pi Configuration 또는 terminal 에서 sudo raspi-config를 통해 pi 설정창에 접속

Interfaces에서 SSH와 VNC를 Enable로 바꿔준다. (Default : Disable) 

하단의 화면은 sudo raspi-config를 실행하여 설정을 변경하는 것이다.

![1568879657679](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1568879657679.png)

![1568879673108](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1568879673108.png)

재접속 이 후 ssh pi@yourip 를 통해 ssh 접속이 가능하다.



### VNC 설정

앞서 설정한 ssh로 라즈베리 파이에 접속한다.

```
pi@raspberrypi:~$ sudo apt-get install tightvncserver
pi@raspberrypi:~$ vncserver :1 -geometry 1280x720 -depth 16 -pixelformat rgb565
```

vnc 통신을 하기 위해 tightvncserver를 설치하고, vncserver를 실행시켜 세션을 생성한다.

**New 'X' Desktop is raspberrypi:1** 이 나오면 정상적으로 세션이 생성된 것이다.

이후 Ubuntu에도 똑같이 세팅을 한 후 viewer를 킨다.

```
sudo apt-get install tightvncserver
vncviewer yourip:5901
```

vncviewer를 종료할 때는 vncserver -kill :1(세션번호) 로 종료하거나 

라즈베리 파이의 전원을 끄면 자동적으로 vnc가 종료된다.