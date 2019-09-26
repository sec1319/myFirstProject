### 라이브러리 -업데이트

sudo apt-get upgrade; sudo apt-get update

### 개발 환경 설정
sudo apt-get install gcc xterm git-core subversion vim

```
gcc option
-v : 버전정보 출력
-c : 소스 코드에 대한 컴파일을 수행해서 목적 코드 생성
-o : 실행 파일에 대한 이름을 부여함. 기본적으로 a.out이라는 이름으로 실행파일을 생성
-E : 프리프로세서 과정만 수행
-S : 프리프로세서 과정과 컴파일 과정만 수행해서 어셈블러 파일을 생성
-I : 컴파일 시 사용되는 헤더 파일의 위치를 지정(기본 디렉터리 /usr/include)
-l : 링크 시 사용되는 라이브러리를 지정
-L : 링크 시 사용되는 라이브러리의 위치를 지정 (기본 디렉터리 /usr/lib)
-g : 디버그 정보를 실행 파일에 추가
-D 매크로 : 컴파일 시 사용할 매크로를 지정 
-O, -O2, -O3 : 컴파일 시 최적화 옵션 수행
-nostdinc : 기본 include 디렉터리를 사용하지 않음
```

make 유틸리티
make [--makefile=파일명] : 이름을 별도로 지정하고 싶다면 --makefile 또는 -f 옵션을 사용

### Wiring Pi 다운로드

git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build

### Fritzing 다운로드

Fritzing Download(https://fritzing.org/download/)
getconf LONG_BIT으로 운영체제의 bit 수 확인 후 다운로드



### 책에서 제공하는 소스 다운로드

git clone https://github.com/Jpub/LinuxProgrammingWithRaspberryPi.git



