# System Programming 01

## 목차
[리눅스 파일시스템](#리눅스-파일시스템) </br>
[실습](#실습)

--- 
## 리눅스 파일시스템

### Directory(디렉토리)
파일 또는 다른 디렉토리를 분류하기 위해 사용하는 저장공간
  + `/` &emsp;&emsp;&emsp;&emsp;: root directory, 최상위 디렉토리
  + `~`(tild) &emsp;&emsp;: home directory, 사용자에게 할당된 개인 디렉토
  + `.` &emsp;&emsp;&emsp;&emsp; : slef, 현재 디렉토리
  + `..` &emsp;&emsp;&emsp;&emsp;: parent, 상위 디렉토리

### Directory 관련 기본 명령어
  + `cd`: change directory, 다른 디렉토리로 이동
  + `rm`: remove, 파일 또는 디렉토리 삭제
  + `mkdir`: make directory, 디렉토리 생성
  + `pwd`: print working directory, 현재 작업중인 디렉터리의 위치를 표시(출력)

---
## 실습
### 디렉터리 및 파일 생성

### `tree`
디렉토리의 계층 구조를 트리 모양으로 나타내는 명령어
#### tree 패키지 설치
```
sudo apt install tree
```

### `mkdir`
디렉토리를 생성하는 명령어
#### Directory 생성
```
mkdir 디렉토리명
mkdir software
```

### 경로 이동
#### Directory 절대경로 이동
```
cd /디렉토리명
cd /home/stud/software
```
#### Directory 상대경로 이동(현재 디렉토리의 자식 디렉토리)
```
cd ./디렉토리명
cd ./software
```

### `cat`
파일의 내용을 출력하는 명령어
#### file 생성 및 내용 작성
- 명령어 입력 후 파일 내용 작성 가능
- ```ctrl```+```d```: EOF(End of File)
```
cat > 생성파일명.파일확장자
cat > sample.txt
```
![image](https://github.com/user-attachments/assets/a782437f-35b9-4ac9-9579-e657168721ad)

#### file 내용 확인
```
cat 생성파일명.파일확장자
cat sample.txt
```
![image](https://github.com/user-attachments/assets/a7184d23-f47e-4750-a07b-71b71186a539)

---

![image](https://github.com/user-attachments/assets/70d3ea8e-ea85-49fd-b839-bdaa73c5ebc1)

