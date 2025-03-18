# System Programming 00
## 목차
① [OT](#OT) </br>
② [Unix(유닉스)](#Unix유닉스) </br>
③ [Linux(리눅스)](#Linux리눅스) </br>
④ [실습: WSL 설치](#실습-WSL-설치)

--- 
## OT

### 🖥️ 시스템 프로그래밍
#### 📅 2025-03-07 ~ 2025-06-20
#### ✏️ Linux(리눅스)
#### ⚠️ 매주 공부 자료 및 실습 업로드

---
## Unix(유닉스)

### 유닉스/리눅스 운영체제
- 1970년대 초에 AT&T 벨연구소에서 유닉스가 개발된 이후로 지속적으로 발전
- 스마트폰, PC, 서버 시스템, 슈퍼컴퓨터에까지 사용되고 있음

### Unix의 설계 철학
- 단순성
  + MIT MULTICS에 반대해, 최소한의 기능만 제공함
  + 자원에 대한 일관된 관점을 제공
- 이식성
  + 이시성을 위해 C 언어로 작성됨
  + 다양한 플랫폼에 이식 가능
- 개방성
  + 소스 코드 공개 등

### Unix의 특징
- 다중 사용자, 다중 프로세스
  + 여러 사용자가 동시에 사용 가능
  + 여러 프로그램이 동시에 실행됨
  + 관리자(Super user)가 있음
- 셸 프로그래밍
  + 명령어, 유틸리티 등을 사용해 작성한 프로그램
- 훌륭한 네트워킹
  + 유닉스에서 네트워킹이 시작됨
  + ftp, telnet, WWW, X-window 등

### Unix 운영체제 구조

![image](https://github.com/user-attachments/assets/e6a94903-59b6-458d-9641-8befc7f3dea0) |
---|

- **운영체제(OS)**
  + 컴퓨터의 하드웨어 자원을 운영·관리함
  + 프로그램을 실행할 수 있는 환경을 제공함

- **커널(kernel)**
  + 운영체제의 핵심
  + 하드웨어 운영 및 관리
- **시스템 호출(system call)**
  + 커널이 제공하는 서비스에 대한 프로그래밍 인터페이스 역할
- **셸(shell)**
  + 사용자와 운영체제 사이의 인터페이스
  + 사용자로부터 명령어를 입력 받고 해석 해, 수행해주는 명령어 해석기

## 커널(kernel)

![image](https://github.com/user-attachments/assets/e29a6b9f-6ba2-4517-a4f7-8da8e2f75f16) |
---|

**커널의 역할:** 하드웨어를 운영 관리하여 프로세스, 파일, 메모리, 통신, 주변장치 등을 관리하는 서비스 제공
- 프로세스 관리(Process management)
  + 여러 프로그램이 실행될 수 있도록 프로세스들을 CPU 스케줄링하여 동시에 수행되도록 한다.
- 파일 관리(File management)
  + 디스크와 같은 저장장치에 파일 시스템을 구성하여 파일을 관리한다.
- 메모리 관리(Memory management)
  + 메인 메모리가 효과적으로 사용될 수 있도록 관리한다.
- 통신 관리(Communication management)
  + 네트워크를 통해 정보를 주고받을 수 있도록 관리한다.
- 주변장치 관리(Device management)
  + 모니터, 키보드, 마우스와 같은 장치를 사용할 수 있도록 관리한다.

---
## Linux(리눅스)
- PC를 위한 효율적인 유닉스 시스템
  + 1991년 헬싱키 대학의 Linus Torvalds에 의해 개발됨
- 소스코드가 공개
  + 인터넷 상에서 자원자들에 의해서 기능 추가 및 확장됨
  + 공용 도메인 상의 무료 OS
- 다양한 하드웨어 플랫폼에 포팅 가능
  + PC, 워크스테이션, 서버, 메인프레임 등
  + 놀라운 성능 및 안정성
- GNU 소프트웨어와 함께 배포
  + GNU/Linux 운영체제
  + 다양한 응용 프로그램

### 리눅스 설치 방법들
- 배포판 설치
- 가상머신을 통한 설치
- 원격 로그인(telnet, PuTTy 등)
- WSL(Windows Subsystem for Linux)

---
## 실습: WSL 설치

### WSL(Windows Subsystem for Linux)
Linux용 Windows 하위 시스템</br>
별도의 가상 머신 또는 이중 부팅 없이 Windows 컴퓨터에서 Linux 환경을 실행할 수 있는 Windows의 기능

### WSL로 윈도우에서 리눅스 실행하기
참고 링크: https://200-rush.tistory.com/entry/WSLInstall

#### 1. Linux용 Windows 하위 시스템 기능이 켜져 있는지 확인
![image](https://github.com/user-attachments/assets/61a3bdda-3cad-4e08-a1f1-af77bed3f9ac)

#### 2. 

### 결과
![image](https://github.com/user-attachments/assets/1f6ed186-eba0-42bf-aeef-16e38edfa8af)
