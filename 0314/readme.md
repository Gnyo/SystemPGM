# System Programming 01

## 목차
[1. 리눅스 파일시스템(Linux File System)](#1-리눅스-파일시스템)
[2. 실습](#2-실습)

## 1. 리눅스 파일시스템(Linux File System)

- tree 패키지 설치
```
sudo apt install tree
```

- directory
  + / &emsp;&emsp;: root directory 
  + ~ &emsp;&emsp;: home directory 
  + . &emsp;&emsp; : slef 
  + .. &emsp;&emsp;: parent 

- directory 생성
```
mkdir 디렉토리명
mkdir software
```

- directory 절대경로 이동
```
cd /디렉토리명
cd /home/stud/software
```
- directory 상대경로 이동(현재 디렉토리의 자식 디렉토리)
```
cd ./디렉토리명
cd ./software
```

- file 생성
  + 생성 후에는 파일 내용 입력 가능
  + ctrl+d: 저장 및 종료
```
cat > 생성파일명.파일확장자
cat > sample.txt
```
![image](https://github.com/user-attachments/assets/a782437f-35b9-4ac9-9579-e657168721ad)


- file 내용 확인
```
cat 생성파일명.파일확장자
cat sample.txt
```
![image](https://github.com/user-attachments/assets/a7184d23-f47e-4750-a07b-71b71186a539)

## 2. 실습
#### 디렉터리 및 파일 생성
![image](https://github.com/user-attachments/assets/70d3ea8e-ea85-49fd-b839-bdaa73c5ebc1)

