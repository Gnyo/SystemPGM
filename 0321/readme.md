# System Programming 02

## 목차

① [기본 명령어](#기본-명령어) </br>
② [파일과 디렉토리](#파일과-디렉토리) </br>
③ [디렉토리 명령어](#디렉토리-명령어) </br>
④ [실습: gcc](#실습-gcc) </br>
⑤ [실습: c언어 입·출력](#실습-c언어-입출력)</br>
⑥ [리눅스에서 생성한 파일 찾기](#리눅스에서-생성한-파일-찾기)</br>

## 기본 명령어

### `passwd`
패스워드 변경

### `clear`
화면 클리어

### `date`
날짜 및 시간 확인

### `man`
명령어의 메뉴얼/옵션 확인
```
man [명령어]
man ls
```

### `whatis`
명령어에 대한 간단한 설명 확인
```
whatis [명령어]
whatis ls
```

### `alias`
사용자가 명령어를 다른 이름으로 바꿔서 사용할 수 있는 쉘 내부 명령어
- alias egrep = 'egrep --color=auto'
- alias fgrep = 'fgrep --color=auto'
- alias grep = 'grep --color=auto'
- alias l = 'ls -CF'
- alias la = 'ls -A'
- alias ll='ls -alF'
- alias ls = 'ls --color=auto'

### 와일드 캐릭터(wild character)
- `*`: all
	+ ` l* `: l로 시작하는 것
- `?`: one
	+ ` ?? `: 두 글자로 이루어진 것

---
## 파일과 디렉토리

### 디렉토리 계층구조
리눅스의 디렉터리는 루트로부터 시작하여 트리 형태의 계층 구조를 이룸

![image](https://github.com/user-attachments/assets/853e1a82-5f38-4fd4-8322-3f66faee7730) |
---|

### 홈 디렉토리(home directory)
- 각 사용자마다 별도의 홈 디렉토리가 있음
- 사용자가 로그인하면 홈 디렉토리에서 작업을 시작함

![image](https://github.com/user-attachments/assets/07a029a1-2399-4554-96a6-f662d18fd6dc) |
---|

### 경로명
파일이나 디렉터리에 대한 정확한 이름
- 절대 경로명(absolute pathname)
  + 루트 디렉터리로부터 시작하여 경로 이름을 정확하게 적는 것
- 상대 경로명(relative path name)
  + 현재 작업 디렉터리부터 시작해서 경로 이름을 적는 것

---
## 디렉토리 명령어

### `pwd`
현재 작업 디렉토리의 절대 경로명 출력
```
pwd
```
![image](https://github.com/user-attachments/assets/52358208-01c5-4838-90bf-ce7c8d73d50e)

### `rmdir`(remove directory)
디렉토리(들)을 삭제, (⚠️ 빈 디렉토리만 삭제 가능)
```
rmdir 디렉토리
```
![image](https://github.com/user-attachments/assets/b9dbfede-366d-4d02-9581-7a21917d8a57)|![image](https://github.com/user-attachments/assets/94a2a33a-27c8-437e-bcda-e606b45428a9)
---|---
디렉터리가 삭제 됨 | 디렉터리가 비어있지 않아 삭제되지 않음

### `rm`
파일 삭제
```
rm 파일
```
![image](https://github.com/user-attachments/assets/d591cb6d-5329-42ca-aafa-9e569ab46ec2) | ![image](https://github.com/user-attachments/assets/0a57d524-a53d-42ae-afaa-1473ae02716c)
---|---
파일이 삭제됨 | 디렉토리는 삭제 불가능

#### `-r` 옵션
삭제하려는 디렉토리에 하위 디렉토리 또는 파일이 존재해도 연쇄적으로 삭제
- 디렉토리도 삭제 가능
```
rm 파일또는디렉토리명 -r
```
![image](https://github.com/user-attachments/assets/578dd421-7070-4ec1-9daf-b47532eaf18b) |
---|
하위에 다른 디렉토리가 있던 디렉토리가 삭제됨

### `ls`
현재 위치나 특정 경로의 디렉토리 내용의 리스트를 출력

### `cat`
간단한 파일 생성
- `ctrl`+`d`: EOF
```
cat > 파일
cat > hello.c
```

파일 확인
```
cat 파일
cat hello.c
```
![image](https://github.com/user-attachments/assets/5a79f57f-2c2d-4458-bac7-3349522377a1)

### `more`
파일을 페이지로 구분하여 확인

### `tail`
### `wc`

### `touch`
타임스탬프를 찍기 위해 파일 크기가 0인 이름만 존재하는 빈 파일 생성
```
touch 파일
```

---
## 실습: gcc
### gcc
C, C++, Objective-C, Fortran, Ada 등 다양한 프로그래밍 언어를 지원하는 오픈 소스 컴파일러 모음
- 기본적으로 gcc라고 하면 보통 C 언어 컴파일러를 의미
- C++은 g++이라는 이름으로 별도의 컴파일러가 포함되어 있음

### gcc 설치
#### 1. gcc 설치 명령어 입력
```
sudo apt install gcc
```
#### 2. gcc 버전 확인(설치 확인)
```
gcc --version
```

![image](https://github.com/user-attachments/assets/ca2e2194-e234-485f-8f84-d6becc1d325f) |
---|

### 컴파일
```
gcc hello.c
```
![image](https://github.com/user-attachments/assets/4840fa10-86fe-4bbf-9fa5-17eec0893669) | ![image](https://github.com/user-attachments/assets/c09d46b3-c5d0-4693-b2f7-4d142631ed6d)
---|---
따로 출력 파일 이름을 지정하지 않음 | 컴파일 결과가 자동으로 a.out이라는 이름으로 저장됨


### 프로그램 실행
```
./출력파일명
./a.out
```
![image](https://github.com/user-attachments/assets/05843390-0de0-41be-a959-052911f4228f) |
---|

### 출력 파일 이름 지정 후 컴파일 및 실행 방법
hello.c 파일을 컴파일해서 hello라는 실행 파일 생성
```
gcc hello.c -o hello
```
+ 대표 옵션
	- `-o`: 컴파일된 출력 파일 이름 설정
	- `-c`: 소스 코드를 오브젝트 파일(.o)로 컴파일 (링크 단계 생략)
	- `-Wall`: 모든 경고 메시지 출력
	- `-g`: 디버깅 정보 포함

hello 프로그램 실행
```
./hello
```
---
## 실습: c언어 입·출력

### 입·출력 조건
- 입력: 학번, 이름
- 출력: 학번, 이름

### 코드 입력
```c
#include <stdio.h>

int main() {
    char name[50];
    char studentId[20];

    printf("학번을 입력하세요: ");
    scanf("%s", studentId);

    printf("이름을 입력하세요: ");
    scanf("%s", name);

    printf("\n입력한 정보\n");
    printf("학번: %s\n", studentId);
    printf("이름: %s\n", name);

    return 0;
}
```

### 결과
![image](https://github.com/user-attachments/assets/370aefcf-57b6-4722-9140-aef9ff5a7a65)

---
## 리눅스에서 생성한 파일 찾기
### 사용하고 있는 Ubuntu 주소 찾기
윈도우 탐색기에서 실습 경로 쉽게 찾을 수 있음!
```
\\wsl$\
```
```
\\wsl.localhost\Ubuntu-24.04\home
```
![image](https://github.com/user-attachments/assets/8ea12bd3-7270-472f-bd28-dd77efe487d4) | ![image](https://github.com/user-attachments/assets/e1736152-5051-48c6-8022-2567a11cfffa)
---|---
Ubuntu | 내가 실습한 파일들


