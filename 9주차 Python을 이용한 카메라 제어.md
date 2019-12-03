





### 9주차 _1 Python을 이용한 카메라 제어

#### picamera를 이용해 사진 찍기

Python에서 카메라를 제어하기 위해 picamera라는 모듈을 사용한다.

picamera로 사진을 찍는 코드는 다음과 같다.

```python
import picamera
import time

with picamera.PiCamera() as camera:
	camera.start_preview() # 카메라 preview 화면을 보여줌
	time.sleep(5) # 5s 만큼 기다림
	camera.capture('filepath/filename.jpg') # filepath에 filename이라는 이미지 파일을 저장함
	camera.stop_preview() # 카메라 preview 화면 종료
```



#### picamera를 이용해 동영상 찍기

```python
import picamera
import time

with picamera.PiCamera() as camera:
	camera.start_preview()
	camera.start_recording('filepath/filename.h264') # 영상 녹화 시작
	time.sleep(10)
	camera.stop_recording() # 영상 녹화 종료
	camera.stop_preview
```



#### picamera를 이용한 해상도 조절

```python
import picamera
import time

with picamera.PiCamera() as camera:
	camera.resolution = (2592, 1944) # 영상 해상도 설정 최대 가로 2592 / 세로 1944
    camera.framerate = 15 # 카메라 프레임비율 설정
    camera.start_preview()
	time.sleep(10)
	camera.capture('filepath/filename.jpg')
	camera.stop_preview
```



#### picamera를 이용하여 사진에 글자 표시

```python
import picamera
import time

with picamera.PiCamera() as camera:
	camera.start_preview()
	camera.annotate_text_size = 50
    camera.annotate_background = picamera.Color('black')
    camera.annotate_foreground = picamera.Color('yellow')
    camera.annotate_text = "Your Name Here"
    time.sleep(10)
	camera.capture('filepath/filename.jpg')
	camera.stop_preview
```

