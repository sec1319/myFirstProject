





### 8주차 _1 Python을 이용한 GPIO 제어

#### LED 제어하기

![1](C:\Users\MS\Desktop\raspberry\myFirstProject\Week8\1.png)

LED는 짧은 쪽이 음극, 긴 쪽이 양극을 나타낸다.



#### 서킷 연결

따라서 아래 그림과 같이 서킷을 연결해준다.

![A Single LED](https://cdn.shopify.com/s/files/1/0176/3274/files/LEDs-BB400-1LED_bb_grande.png?6398700510979146820)

GND는 저항220Ω을 연결한 후 Cathode에 연결해주고, Anode는 GPIO 핀에 직접적으로 연결해준다.



#### GPIO (General Purpose Input Output)

GPIO 모드

* GPIO.BOARD -- Board 번호 체계
* GPIO.BCM      -- BCM 번호 체계![2](C:\Users\MS\Desktop\raspberry\myFirstProject\Week8\2.jpg)

1) 입력모드(Input Mode) : 라즈베리파이와 연결된 전자  부품으로부터 0 또는 1의 신호를 읽기 위한 모드로 핀을 설정한다. ex) 스위치 버튼, 센서

2) 출력모드(Output Mode)  : 라즈베리파이와 연결된 전자 부품에 1 또는 0의 값을 내보내기 위한 모드로 핀을 설정한다. ex) LED, 서브모터 등

* GPIO 라이브러리를 사용하려면 사전에 import를 해야한다.
* GPIO 포트들은 사용하기 전에 먼저 입력 또는 출력으로 초기화 해야한다.
* GPIO output : 출력 port로 지정된 port에 대해서는 지정된 값을 출력할 수 있다.
  - GPIO.output(<port>, <output>)
  - [GPIO.HIGH, True, 1] --- 전류 ON
  - [GPIO.LOW, False, 0] --- 전류 OFF
  - ex) GPIO.output(11, True)



#### Python을 이용한 PWM 제어

 https://sourceforge.net/p/raspberry-gpio-python/wiki/BasicUsage/ 

python에서 GPIO를 사용하기 위해서는 먼저 필요한 gpio 라이브러리를 받아준다.

```
sudo apt-get install python-rpi.gpio python3-rpi.gpio
```

RPi(Raspberry Pi).GPIO 를 임포트 해준 후 사용한다.

코드를 실행하기 위해서는 root 권한이 필요하다. 그러므로 sudo 명령어를 사용하여 코드를 실행하도록 한다.

실행은 터미널에서 다음과 같이 실행한다.

sudo python pwm.py

```python
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

pwm = GPIO.PWM(18, 50)
pwm.start(0)

for i in range(0, 3):
    for dc in range(0, 101, 5):
        pwm.ChangeDutyCycle(dc)
        time.sleep(0.1)
    for dc in range(100, -1, -5):
        pwm.ChangeDutyCycle(dc)
        time.sleep(0.1)
pwm.stop()
GPIO.cleanup()
```



### 8주차_2 OPEN CV를 활용한 이미지 제어

#### 1. open cv를 이용한 이미지 출력

 OpenCV (Open source Computer Vision)는 실시간 컴퓨터 비젼을 처리하는 목적으로 만들어진 라이브러리로서, 인텔에 의해 처음 만들어져서 현재는 Itseez (2016년 인텔에 편입)에 의해 지원되고 있다. 

파이썬에서 OpenCV는 pip을 통해 아래와 같이 설치할 수 있다.

```
    pip install opencv-python
```



#### 2. 이미지 파일 읽고 쓰기

 https://pypi.org/project/opencv-python/ 

* `cv2.imread(fileName, flag)` : fileName은 이미지 파일의 경로, flag는 이미지 파일을 읽을 때 옵션

  flag는 총 3가지가 있다. 명시적으로 써줘도 되고 숫자를 사용해도 된다
  `cv2.IMREAD_COLOR`(1) : 이미지 파일을 Color로 읽음. 투명한 부분은 무시하며 Default 설정
  `cv2.IMREAD_GRAYSCALE`(0) : 이미지 파일을 Grayscale로 읽음. 실제 이미지 처리시 중간 단계로 많이 사용
  `cv2.IMREAD_UNCHAGED`(-1) : 이미지 파일을 alpha channel 까지 포함해 읽음

*  `image.shape` 함수는 이미지 파일의 모양을 return한다. 순서대로 Y축, X축, 채널의 수를 의미한다.

*  `cv2.imshow(tital, image)` : title은 윈도우 창의 제목을 의미하며 image는 `cv2.imread()` 의 return값 이다.

* `cv2.waitKey() ` : 키보드 입력을 대기하는 함수로 0이면 key 입력이 있을때까지 무한대기한다. 특정 시간동안 대기를 하려면 ms값을 넣어주면 된다. 또한 ESC를 누를 경우 27을 리턴한다. 

* `cv2.destroyAllWindows()` : 화면에 나타난 윈도우를 종료합니다. 일반적으로 위 3개는 같이 사용된다.

* `cv2.imwrite(fileName, img)` : fileName은 저장할 이미지 파일의 경로, img는 opencv 등으로 읽은 img 파일을 의미한다.



##### Show Image

```python
import cv2

import cv2

fname = 'filename'

original = cv2.imread(fname, cv2.IMREAD_COLOR)
gray = cv2.imread(fname, cv2.IMREAD_GRAYSCALE)
# img_gray = cv2.cvtColor(img_color, cv2.COLOR_BGR2GRAY)
unchange = cv2.imread(fname, cv2.IMREAD_UNCHANGED)

cv2.imshow('Original', original)
cv2.imshow('Gray', gray)
cv2.imshow('Unchange', unchange)

cv2.waitKey(0)
cv2.destroyAllWindows()
```



##### Save Image

```python
import cv2

img = cv2.imread('filename', cv2.IMREAD_GRAYSCALE)
cv2.imshow('image',img)
k = cv2.waitKey(0)
if k == 27: # esc key
    cv2.destroyAllWindow()
elif k == ord('s'): # 's' key
    cv2.imwrite('testgray.png',img)
    cv2.destroyAllWindow()
```

