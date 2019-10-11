#include <stdio.h>
#include <wiringPi.h>

int main(void) {
	int i, a, b;
	int sevenseg [10][7] = {{0,0,0,0,0,0,1},
							{1,0,0,1,1,1,1},
							{0,0,1,0,0,1,0},
							{0,0,0,0,1,1,0},
							{1,0,0,1,1,0,0},
							{0,1,0,0,1,0,0},
							{0,1,0,0,0,0,0},
							{0,0,0,1,1,1,1},
							{0,0,0,0,0,0,0},
							{0,0,0,0,1,0,0}};

	wiringPiSetup();
	for(i = 0; i<8; i++)
		pinMode(i,OUTPUT);

	while(1){
		for(a = 0; a < 10; a++) {
			for(b = 0; b < 7; b++)
				digitalWrite(b, sevenseg[a][b]);
			delay(1000);
		}
	}
	return 0;
}
