#include <wiringPi.h>
#include <stdio.h>

#define SW  2      /* GPIO24 */
#define LED 1      /* GPIO18 */

int switchControl()
{
   int i;
   int cnt = 1;
   pinMode(SW,  INPUT);                        /* Pin 모드를 입력으로 설정 */
   pinMode(LED, PWM_OUTPUT);
   while(1){
	   if(digitalRead(SW) == LOW) {          /* Push 버튼이 눌러지면(LOW) */
         pwmWrite(LED, cnt*100);                /* LED 켜기(On) */
         delay(1000); 
         cnt += cnt;
         if(cnt > 11){
		     cnt = 1;
         }
      }
   }

   return 0 ;
}

int main(int argc, char** argv)
{
   if (wiringPiSetup()<0){
		printf("read Error");
		return -1;
	}

   switchControl();                                    /* 스위치 사용을 위한 함수 */

   return 0 ;
}

