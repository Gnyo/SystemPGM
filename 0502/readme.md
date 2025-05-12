# System Programming 07

## 목차
#### ① [컴퓨터 시스템 구조](#컴퓨터-시스템-구조)
#### ② [시스템 호출](#시스템-호출)
---
## 컴퓨터 시스템 구조

### 유닉스 커널(kernel)
|![image](https://github.com/user-attachments/assets/865fdd31-7b83-4a6f-a262-98bdab619751)|
|---|

하드웨어를 운영 관리하여 다음과 같은 서비스를 제공:
- 파일 관리(File management)
- 프로세스 관리(Process management)
- 메모리 관리(Memory management)
- 통신 관리(Communication management)
- 주변장치 관리(Device management)

### 시스템 호출이란?
- 시스템 호출은 커널에 서비스 요청을 위한 프로그래밍 인터페이스
- 응용 프로그램은 시스템 호출을 통해서 커널에 서비스를 요청함

|![image](https://github.com/user-attachments/assets/1a4e0d74-3007-49c9-b78e-811ed3d34e60)|
|---|

### 시스템 호출 과정

|![image](https://github.com/user-attachments/assets/d2632a7b-a6aa-4e26-beb0-bbe3fa7784fd)|
|---|

### 시스템 호출 요약
주요 자원 | 시스템 호출
---|---
파일 | open(), close(), read(), write(), dup(), lseek() 등
프로세스 | fork(), exec(), exit(), wait(), getpid(), getppid() 등
메모리* | malloc(), calloc(), free() 등
시그널 | signal(), alarm(), kill(), sleep() 등
프로세스 간 통신 | pipe(), socket() 등

### 유닉스에서 파일
- 연속된 바이트의 나열
- 특별한 다른 포맷을 정하지 않음
- 디스크 파일뿐만 아니라 외부 장치에 대한 인터페이스

|![image](https://github.com/user-attachments/assets/cc0addf6-c275-4e32-81f8-846f2da33445)|
|---|

---
## 시스템 호출
### 파일 열기: open()
open() 시스템 호출
- 파일을 사용하기 위해서는 먼저 open() 시스템 호출을 이용하여 파일을 열어야 함
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open (const char *path, int oflag, [ mode_t mode ]);

/* 파일 열기에 성공하면 파일 디스크립터를, 실패하면 -1을 리턴 */
```
  + 파일 디스크립터는 열린 파일을 나타내는 번호임

- oflag
  + O_RDONLY: 읽기 모드, read() 호출은 사용 가능
  + O_WRONLY: 쓰기 모드, write() 호출은 사용 가능
  + O_RDWR: 읽기/쓰기 모드, read(), write() 호출 사용 가능
  + O_APPEND: 데이터를 쓰면 파일끝에 첨부됨
  + O_CREAT: 해당 파일이 없는 경우에 생성하며 mode는 생성할 파일의 사용권한을 나타냄
  + O_TRUNC: 파일이 이미 있는 경우 내용을 지움
  + O_EXCL: O_CREAT와 함께 사용되며 해당 파일이 이미 있으면 오류
  + O_NONBLOCK: 넌블로킹 모드로 입출력 하도록 함
  + O_SYNC: write() 시스템 호출을 하면 디스크에 물리적으로 쓴 후 반환됨

#### 파일 열기 예
```c
fd = open("account",O_RDONLY);
fd = open(argv[1], O_RDWR);
fd = open(argv[1], O_RDWR | O_CREAT, 0600);
fd = open("tmpfile", O_WRONLY|O_CREAT|O_TRUNC, 0600);
fd = open("/sys/log", O_WRONLY|O_APPEND|O_CREAT, 0600);

if ((fd = open("tmpfile", O_WRONLY|O_CREAT|O_EXCL, 0666))==-1)
```

#### openex.c
```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int fd;
  if ((fd = open(argv[1], O_RDWR)) == -1)
  printf("파일 열기 오류\n");
  else printf("파일 %s 열기 성공 : %d\n", argv[1], fd);

  close(fd);
  exit(0);
} 
```

### 파일 생성: creat()
creat() 시스템 호출
- path가 나타내는 파일을 생성하고 쓰기 전용으로 엶
- 생성된 파일의 사용권한은 mode로 정함
- 기존 파일이 있는 경우에는 그 내용을 삭제하고 엶
- 다음 시스템 호출과 동일
  + `open(path, WRONLY | O_CREAT | O_TRUNC, mode);`
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int creat (const char *path, mode_t mode );
파일 생성에 성공하면 파일 디스크립터를, 실패하면 -1을 리턴
```

### 파일 닫기: close()
close() 시스템 호출
- fd가 나타내는 파일을 닫음
```c
#include <unistd.h>
int close( int fd );
fd가 나타내는 파일을 닫는다.
성공하면 0, 실패하면 -1을 리턴한다.
```

### 데이터 읽기: read()
read() 시스템 호출
- fd가 나타내는 파일에서 nbytes 만큼의 데이터를 읽고 읽은 데이터는 buf에 저장
```c
#include <unistd.h>
ssize_t read ( int fd, void *buf, size_t nbytes );
파일 읽기에 성공하면 읽은 바이트 수, 파일 끝을 만나면 0,
실패하면 -1을 리턴
```

### 데이터 쓰기: write()
write() 시스템 호출
- buf에 있는 nbytes 만큼의 데이터를 fd가 나타내는 파일에 씀
```c
#include <unistd.h>
ssize_t write (int fd, void *buf, size_t nbytes);
파일에 쓰기를 성공하면 실제 쓰여진 바이트 수를 리턴하고,
실패하면 -1을 리턴
```
