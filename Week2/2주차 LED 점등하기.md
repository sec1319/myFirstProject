### 2주차 _1 LED 점등하기

#### GPIO(General-Purpose Input/Output) 핀맵

먼저, 이번 GPIO Output 테스트에 활용될 GPIO는 18번이다. GPIO 핀맵은 다음과 같이 되어있다.

![gpio-2-4](https://i1.wp.com/www.rasplay.org/wp-content/uploads/gpio-2-4.png?resize=400%2C449)

#### Wiring Pi 핀맵

Wiring Pi에서 핀맵은 다음과 같이 정의된다.

![wiring pi gpio pinì ëí ì´ë¯¸ì§ ê²ìê²°ê³¼](https://zhihuicao.files.wordpress.com/2016/04/pinbelegung-wiringpi.png?w=957)

우리는 여기서 WiringPi Pin 1번인 GPIO18 번 핀과 6번에 있는 GND 핀을 사용하여 LED 전구에 불을 키려 한다.



#### LED 극성 구성

LED는 다음과 같이 구성된다.

![gpio-2-1](https://i1.wp.com/www.rasplay.org/wp-content/uploads/gpio-2-1.jpg?resize=279%2C181)

다리가 짧은 쪽이 Cathode(음극), 다리가 긴 쪽이 Anode(양극) 전극을 띈다. 

#### 서킷 연결

따라서 아래 그림과 같이 서킷을 연결해준다.

![A Single LED](https://cdn.shopify.com/s/files/1/0176/3274/files/LEDs-BB400-1LED_bb_grande.png?6398700510979146820)

GND는 저항220Ω을 연결한 후 Cathode에 연결해주고, Anode는 GPIO 핀에 직접적으로 연결해준다.

#### 저항 색상표 읽기

저항의 색상표를 읽는 법은 다음과 같다.

![img](https://mblogthumb-phinf.pstatic.net/20150319_24/roboholic84_1426744589763G4WfA_PNG/BBF6B6ECC0FAC7E2_C0%AC%D2E2.png?type=w2)

```
220옴 ±5% : 빨강 - 빨강 - 갈색 - 금색
1K옴 ±10% : 갈색 - 검정 - 빨강 - 은색
10K옴 ±1% : 갈색 - 검정 - 주황 - 갈색
330옴 ±5% : 주황 - 주황 - 검정 - 검정 - 금색
10옴 ±1% : 갈색 - 검정 - 검정 - 금색 - 갈색
```



#### echo 명령어와 LED의 점멸

GPIO 제어를 위한 기본적인 디바이스 파일로 /sys/class/gpio를 사용한다. GPIO 18번 핀을 사용하기 위해서 /sys/class/gpio/export에 "18"을 출력하면 /sys/class/gpio/gpio18 폴더가 생성된다.

```
echo "18" > /sys/class/gpio/export #GPIO 18번을 사용
echo "out" > /sys/class/gpio/gpio18/direction #GPIO의 방향을 out으로 사용
echo "1" > /sys/class/gpio/gpio18/value #GPIO의 값을 1(High)로 변경 (LED 점등)
echo "0" > /sys/class/gpio/gpio18/value #GPIO의 값을 0(LOW)로 변경 (LED 소등)
echo "18" > /sys/class/gpio/unexport #GPIO 18번 사용 중지
```

* /sys/class/gpio/gpio18 폴더 안의 파일들을 이용해서  GPIO 18번 핀을 제어할 수 있다.

* "out" 문자열을 direction 파일로 출력하여 핀을 출력모드로 설정한다.

* "1"과 "0"을 value 파일로 출력하여 LED를 켜거나 끌 수 있다.

* 마지막으로 사용이 끝나면 /sys/class/gpio/unexport 파일에 "18"을 출력해서 사용한 핀을 해제하면 된다.



#### GPIO 명령어와 LED의 점멸

라즈베리 파이에서 GPIO를 쉽게 사용할 수 있도록 하는 gpio 명령어가 있는데, 다음에 나오는 wiringPi를 설치하면 사용할 수 있다. 이 gpio는 root 권한이 아니더라도 사용할 수 있기 때문에 일반 유저도 쉽게 다룰 수 있다.

wiring Pi의 설치 방법은 아래와 같다.

* sudo apt-get update; sudo apt-get upgrade
* sudo apt-get install git-core
* git clone git://git.drogon.net/wiringPi
* cd wiringPi
* ./build

이 gpio의 명령어를 이용하면 보다 쉽게 LED를 켜고 끌 수 있다. 먼저 GPIO 핀의 모드(입력, 출력, PWM) 등을 설정하고, 값을 직접 수정하여 LED를 켜거나 끄면 된다.

```
gpio -g mode 18 out #GPIO 18번의 방향을 out으로 사용
gpio -g write 18 1 #GPIO 18번의 값을 1(High)로 변경 (LED 점등)
gpio -g write 18 0  #GPIO 18번의 값을 0(Low)로 변경 (LED 소등)
```

gpio 명령어는 sysfs의 /sys/class/gpio 파일 시스템의 사용도 지원하고 있는데, 사용법은 앞의 echo 명령어를 사용하는 방법과 비슷하다. export로 해당 GPIO 핀을 사용 설정한 후 값을 읽거나 쓰고, 사용이 끝나면 unexport로 사용된 핀을 해제한다.

```
gpio export 18 out
gpio -g write 18 1
gpio unexport 18
```

gpio -v gpio readall을 사용하면 Wiring Pin Map을 확인할 수 있다.



#### gpioled.c 코드 분석

먼저 Jpub에서 제공하는 라즈베리파이 소스코드를 다운로드 받는다.

* git clone https://github.com/Jpub/LinuxProgrammingWithRaspberryPi.git 

* cd LinuxProgrammingWithRaspberryPi/Example/Chapter3
* vim gpioled.c

```c
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int ledControl(int gpio)
{
   int fd;
   char buf[BUFSIZ];

   fd = open("/sys/class/gpio/export", O_WRONLY);          /* 해당 GPIO 장치 사용 준비 */
   sprintf(buf, "%d", gpio);
   write(fd, buf, strlen(buf));
   close(fd);

   sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);      /* 해당 GPIO 장치의 방향 설정 */
   fd = open(buf, O_WRONLY);
   /* 장치를 LED 출력을 위해서 설정 : 입력의 경우 write(fd, "in", 2); 사용 */
   write(fd, "out", 4);                                                          
   close(fd);

   sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);          /* 장치에 값 출력 */
   fd = open(buf, O_WRONLY);
   write(fd, "1", 2);
   close(fd);

   fd = open("/sys/class/gpio/unexport", O_WRONLY);     /* 사용한 GPIO 장치 해제하기 */
   sprintf(buf, "%d", gpio);
   write(fd, buf, strlen(buf));
   close(fd);

   return 0;
}

int main(int argc, char** argv)
{
   int gno;

   if(argc < 2) {
      printf("Usage : %s GPIO_NO\n", argv[0]);
      return -1;
   }
   gno = atoi(argv[1]);

   ledControl(gno);

   return 0;
}
```



gcc 를 사용하여 해당 파일을 실행 파일로 만들어준다. 

```
gcc -o gpioled gpioled.c
```

빌드된 파일을 실행하기 위해서는 디바이스 파일에 접근할 수 있는 root 권한이 필요하다.

```
sudo ./gpioled 18
```



#### wiringPi를 이용한 GPIO 프로그래밍

Chapter3에 wiringled.c를 확인한다. 

wiringPi의 기본적인 설정은 wiringPiSetup() 함수의 호출을 통해 이루어진다. 

wiringPiSetup() 함수가 호출된 후 pinMode() 함수를 이용해서 사용하려는 핀의 입출력 모드를 설정할 수 있다. 입력핀이면 INPUT 값을 사용하고, 출력 핀이면 OUTPUT 값을 사용하면 된다. 출력 핀으로 설정하면 핀을 통해서 전류가 출력되는데, 이 전류를 이용해서 LED를 켤 수 있다.

```c
#include <wiringPi.h> /* WiringPi 함수를 사용하기 위한 헤더 파일 */
#include <stdio.h>

int ledControl(int gpio)
{
   int  i;

   pinMode(gpio, OUTPUT) ;             /* Pin의 출력 설정 */

   for (i = 0; i < 5; i++) {
      digitalWrite(gpio, HIGH);           /* HIGH(1) 값을 출력 : LED 켜기 */
      delay(1000);                               /* 1초(1000ms) 동안 대기 */
      digitalWrite(gpio,  LOW);             /* LOW(0) 값을 출력 : LED 끄기 */ 
      delay(1000);
   };

   return 0;
}

int main(int argc, char** argv)
{
   int gno; 

   if(argc < 2) {
      printf("Usage : %s GPIO_NO\n", argv[0]);
      return -1;
   }
   gno = atoi(argv[1]); /* 문자열을 정수로 변환하는 함수 */

   wiringPiSetup();                           /* wiringPi 초기화 */

   ledControl(gno);

   return 0;
}
```

wiringPi를 사용하면 훨씬 더 간편하게 gpio 조작을 할 수 있다.

위의 코드를 빌드하기 위해서는 wiringPi 라이브러리가 필요하다. 라이브러리 사용을 위해서 gcc 유틸리티에 앞 장에서 살펴본 -l(소문자 L) 옵션을 사용한다.

```
gcc -o wiringled wiringled.c -lwiringPi
```

빌드된 코드를 실행하려면 root 권한이 필요하다. 그러므로  sudo 명령어를 사용하여 코드를 실행하도록 한다.

이때 라즈베리 파이의 핀 번호와 wiringPi에서 사용하는 핀 번호가 서로 다르므로 주의해야 한다. gpio 프로그램의 readall 옵션을 사용하면 전체 핀에 대한 번호를 알 수 있다.

```
sudo ./wiringled 1
```

GPIO 18번 핀에 대한 wiringPi의 핀 번호는 1이다. 애플리케이션 시작 시 인자로 1을 사용하면 앞의 코드의 for 루프에 의해서 LED가 5회 연속 깜박인다.



#### Python을 이용한 GPIO 프로그래밍

python에서 GPIO를 사용하기 위해서는 먼저 gpio 라이브러리를 받아준다.

```
sudo apt-get install python-rpi.gpio python3-rpi.gpio
```

RPi(Raspberry Pi).GPIO 를 임포트 해준 후 사용한다.

코드를 실행하기 위해서는 root 권한이 필요하다. 그러므로 sudo 명령어를 사용하여 코드를 실행하도록 한다.

실행은 다음과 같이 하면 된다.

sudo python gpio-test.py

```python
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM) #BCM(Broadcom chip-specific pin numbers)모드

print "Setup LED pins as outputs"

GPIO.setup(18, GPIO.OUT) #GPIO를 Out으로 설정
GPIO.output(18, True) #GPIO 18의 값을 TRUE(High)로 설정

time.sleep(1) #1초 쉼

GPIO.output(18, False) #GPIO 18의 값을 False(Low)로 설정

raw_input('press enter to exit program')
GPIO.cleanup() #GPIO 핀 초기화
```

GPIO 메서드들은 다음과 같다.

![1569485663752](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1569485663752.png)



### 2주차 _2 스위치로 LED 점등하기

GPIO를 사용하면 데이터의 출력뿐만 아니라 스위치나 센서 같은 데이터의 입력도 가능하다.

빛 감지 센서를 이용하면 빛을 감지할 수 있는데, 빛의 양에 따라 전등을 켜고 끄거나 커튼을 여닫는 기능을 만들 수 있다. 또한, 온도 센서를 이용하여 에어컨을 켜고 끄는 등 실생활에 이로운 다양한 기능들을 사용할 수 있다.

Chapter3 에 wiringswitch.c의 코드를 확인한다.

```c
#include <wiringPi.h>
#include <stdio.h>

#define SW  5      /* GPIO24 */
#define LED 1      /* GPIO18 */

int switchControl()
{
   int i;

   pinMode(SW,  INPUT);                        /* Pin 모드를 입력으로 설정 */
   pinMode(LED, OUTPUT);

   for (i = 0; i < 10000000; i++) {
      if(digitalRead(SW) == LOW) {          /* Push 버튼이 눌러지면(LOW) */
         digitalWrite(LED, HIGH);                /* LED 켜기(On) */
         delay(1000); 
         digitalWrite(LED, LOW);                 /* LED 끄기(Off) */
      }
   };

   return 0 ;
}

int main(int argc, char** argv)
{
   wiringPiSetup();

   switchControl();                                    /* 스위치 사용을 위한 함수 */

   return 0 ;
}
```



서킷은 다음과 같이 되어 있다.

![1569488073666](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1569488073666.png)



```
gcc -o wiringswitch wiringswitch.c -lwiringPi
```

빌드된 코드를 실행하려면 root 권한이 필요하다. 그러므로  sudo 명령어를 사용하여 코드를 실행하도록 한다.

```
./wiringswitch
```

코드를 실행하면 LED가 점등이 된다. 스위치를 누르면 1초간 기다렸다가 끈다. 회로를 보면 GPIO 18번 핀에 3.3V 출력 핀이 바로 연결되어 있어서 기본값이 on이 되는데, 스위치를 누르면 전원이 GND로 흘러가면서 off가 된다.



#### Python으로 스위치 제어하기

```python
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO.setup(23, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)

GPIO.setup(18 , GPIO.IN)

print "Press the button"

try:

  while True :

    GPIO.output(23, False)
    GPIO.output(24, False)


    if GPIO.input(18)==0:
      print "  Button pressed!"

      GPIO.output(23, True)
      GPIO.output(24, True)

      time.sleep(1)

      print "Press the button (CTRL-C to exit)"

except KeyboardInterrupt:
GPIO.cleanup()
```

