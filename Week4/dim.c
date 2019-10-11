#include <wiringPi.h>
#include <stdio.h>

#define LedPin 1

int main(void)
{
	int i;

	if(wiringPiSetup() < 0) { //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1;
	}

	pinMode(LedPin, PWM_OUTPUT); //pwm output mode

	while(1) {
		for(i=0;i<1024;i++) {
			pwmWrite(LedPin, i);
			delay(1);
		}
		delay(1000);
		for(i=1023;i>=0;i--) {
			pwmWrite(LedPin, i);
			delay(1);
		}
	}

	return 0;
}
