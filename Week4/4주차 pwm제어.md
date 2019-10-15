### 4주차 _1 LED Dimming(Fading)

#### PWM(Pulse Width Modulation)

PWM 은 펄스 폭 변조로써 디지털 출력으로 아날로그 회로를 제어하는 기법이다.

* GPIO 핀은 디지털이기 때문에 PWM을 이용하여 아날로그 신호를 제어한다.

![1570770575881](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1570770575881.png)

하단의 그림을 보면 Duty(한 주기 동안 High 가 차지하는 비율)에 따라 평균 전압이 달라지는 것을 알 수 있다. 

* 예를 들어 duty cycle = 50 % 이면 2.5V, duty cycle = 10% 이면 0.5V

![1570770653786](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1570770653786.png)



간단히 말해서 PWM 제어는 Duty Cycle을 통해 LED의 전압을 제어하여 빛의 세기를 조절하는 방식이다.

dim.c

```C
#include <wiringPi.h>
#include <stdio.h>
#define LedPin 1
int main(void) { 
	int i;
	if(wiringPiSetup() < 0) {
        //wiringPi 초기화 실패시 메시지 출력
        printf("setup wiringPi failed !\n");
        return -1;
    }
    //LED 핀이기 때문에 PWM_OUTPUT 모드로 설정
    pinMode(LedPin, PWM_OUTPUT);
    while(1) { 
        for(i=0;i<1024;i++) { 
            //pwmWrite 함수를 이용하여 빛의 세기 증가
            pwmWrite(LedPin, i); 
            delay(1); 
        } 
        delay(1000); 				
        for(i=1023;i>=0;i--) { 
            //pwmWrite 함수를 이용하여 빛의 세기 감소
            pwmWrite(LedPin, i); 
            delay(1); 
        }
    } 
    return 0;
}

```

 코드를 빌드하기 위해선 터미널에서 gcc를 이용한다.

```
gcc -o dim dim.c -lwiringPi
```

빌드된 코드를 실행하려면 root 권한이 필요하다. 그러므로 sudo 명령어를 사용하여 코드를 실행하도록 한다.

```
sudo ./dim
```

코드를 실행하면 LED핀의 빛의 세기가 증가하다가 최대치가 되면 감소한다.



### 서킷연결

![1570774932216](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1570774932216.png)

LED 다리가 짧은 쪽이 Cathode(-)이므로 라즈베리파이의 6번핀(GND)와 연결해주고, 

LED 다리가 긴쪽이 Anode 이므로 GPIO핀 12(wpi - 1)과 연결해준다.



### Switch를 이용한 PWM 제어

dimswitch.c

```c
#include <wiringPi.h>
#include <stdio.h>

#define SW  2      /* GPIO 13 */
#define LED 1      /* GPIO 12 */

int switchControl()
{
   int i;
   int cnt = 1;
   pinMode(SW,  INPUT);                        /* Pin 모드를 입력으로 설정 */
   pinMode(LED, PWM_OUTPUT);                   /* Pin 모드를 PWM_OUTPUT으로 설정 */

   while(1) {
      if(digitalRead(SW) == HIGH) {          /* Push 버튼이 눌러지면(LOW) */
         pwmWrite(LED, cnt*100);                /* LED 밝기 변화 */
         cnt += cnt;                        /* cnt 값 증가 */
	 delay(1000);
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

 코드를 빌드하기 위해선 터미널에서 gcc를 이용한다.

```
gcc -o dimswitch dimswitch.c -lwiringPi
```

빌드된 코드를 실행하려면 root 권한이 필요하다. 그러므로 sudo 명령어를 사용하여 코드를 실행하도록 한다.

```
sudo ./dimswitch
```

코드를 실행하고 스위치를 누르면 빛이 점점 강해진다.

> **스위치를 누르면 빛이 약해지는 코드를 짜고, 스위치를 두 개 꽂아 빛이 세지고, 약해지게 만드시오.**



### 서킷연결

![1570778681377](C:\Users\MS\AppData\Roaming\Typora\typora-user-images\1570778681377.png)

