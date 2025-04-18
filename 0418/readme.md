# System Programming 06

## 목차
#### ① [프로세스](#프로세스)
#### ② [인터넷과 서버](#인터넷과-서버)
#### ③ [파일 유틸리티](#파일-유틸리티)
#### ④ [유틸리티](#유틸리티)
#### ⑤ [Bash 쉘 스크립트](#bash-쉘-스크립트)
#### ⑥ [프로그래밍 환경](#프로그래밍-환경)
---
## 프로세스

- **프로세스 정의**: 실행 중인 프로그램
- **종류**: 시스템 프로세스 / 사용자 프로세스
- **조회 명령어**:
  - `ps`, `pgrep`, `ps -ef | grep 패턴`

### 작업 제어
- **후면 실행**: `명령어 &`
- **중지**: `Ctrl + Z` → `fg` (전면 복귀) / `bg` (후면 복귀)
- **입출력 제어**: `명령어 > 출력파일 &` / `명령어 < 입력파일 &`

### 프로세스 제어
- **종료**: `kill [PID]` / `exit 코드`
- **대기**: `wait [PID]`
- **우선순위**: `nice`, `renice`

### 사용자 ID
- **ID 확인**: `id`, `$UID`, `$EUID`
- **특수 권한 실행 파일**:
  - `set-user-id`: `chmod 4755 파일`
  - `set-group-id`: `chmod 2755 파일`

### 시그널
- **종류**: SIGKILL, SIGINT(Ctrl-C), SIGTSTP(Ctrl-Z) 등
- **전송**: `kill -시그널 PID`, `kill -9 PID`

---
## 인터넷과 서버

### 네트워크 구성
- **LAN / 이더넷 / 라우터 / 게이트웨이**
- **IP / 호스트명 확인**: `ip addr`, `hostname`
- **DNS 조회**: `nslookup 도메인`

### 인터넷
- **프로토콜**: TCP/IP
- **도메인 → IP 변환**: DNS
- **사용자 정보 확인**: `finger 사용자명`

### 서버 설치
- **웹서버**: Apache, PHP, MariaDB (APM)
  - 설치: `apt install apache2 php mariadb-server`
  - 구동: `systemctl start|enable|status 서비스명`
- **FTP 서버**: vsftpd
- **SSH 서버**: `apt install ssh`

### 파일 전송
- **FTP/SFTP 사용**:
  - 접속: `ftp`, `sftp`
  - 업로드: `put`, `mput`
  - 다운로드: `get`, `mget`

### 원격 접속
- **SSH**: `ssh 사용자@호스트`
- **원격 명령 실행**: `ssh 호스트 명령어`
- **상태 확인**: `ping 호스트명`

### 원격 데스크톱
- **xrdp 설치 및 포트 허용**
  - `apt install xrdp`
  - `systemctl start xrdp`, `ufw allow 3389`

### 월드와이드웹(WWW)
- **HTML, HTTP, URL**
- **브라우저 종류**: Chrome, Firefox, Safari 등

---

## 파일 유틸리티

### 파일 찾기 (find)
- **기본 사용법**: `find 디렉터리 -옵션`
- **옵션**:
  - `-name`, `-user`, `-size`, `-type`, `-perm`, `-mtime`, `-exec`

### 필터링 (grep)
- **기본 사용법**: `grep 패턴 파일`
- **옵션**: `-i`, `-l`, `-n`, `-v`, `-w`, `-c`
- **정규표현식 지원**

### 정렬 (sort)
- **기본 사용법**: `sort [-옵션] 파일`
- **옵션**: `-r`, `-k`, `-n`, `-t`, `-o`

### 비교 (cmp, diff)
- `cmp`: 바이트 단위 비교
- `diff`: 줄 단위 차이 비교 (추가, 삭제, 변경)

### 기타 파일 조작
- **분할**: `split -l n 파일`
- **합병**: `cat`, `paste`

---
## 유틸리티

### 명령어 스케줄링
- **cron (주기적 실행)**:
  - 등록: `crontab 파일`, `crontab -e`
  - 예: `30 18 * * * rm /home/chang/tmp/*`
- **at (1회 실행)**:
  - 등록: `at 시간`, 조회: `atq`, 삭제: `at -r 작업번호`

### 디스크 및 아카이브
- **디스크 사용량**: `df`, `du`
- **tar 아카이브**:
  - 생성: `tar -cvf 파일.tar 파일들`
  - 해제: `tar -xvf 파일.tar`
  - 확인: `tar -tvf 파일.tar`

### 파일 압축
- **gzip / gunzip**: `.gz`
- **compress / uncompress**: `.Z`
- **통합 사용 예**:

### AWK
- **기본 구조**: `조건 { 액션 }`
- **내장 변수**: `NR`, `NF`, `$0`, `$1`, ...  
- **조건**: `BEGIN`, `END`, 정규표현식`
- **액션 예시**:
  - `print`, `printf`
  - 조건문: `if`, `for`, `while`
  - 흐름제어: `next`, `exit`

### AWK 예제
- **예제 1: 파일 시작/끝 출력**
```bash
awk 'BEGIN { print "파일 시작:", FILENAME } { print $1, $NF } END { print "파일 끝" }' 파일명
```
- **예제 2: 줄 수 / 단어 수 계산**
```bash
awk 'BEGIN { print "파일 시작" }
{
  printf "line %d: %d \n", NR, NF;
  word += NF
}
END {
  printf "줄 수 = %d, 단어 수 = %d\n", NR, word
}' 파일명
```
- **예제 3: 홀수 번째 필드 출력**
```bash
awk '{
  for (i = 1; i <= NF; i += 2)
    printf "%s ", $i
  printf "\n"
}' 파일명
```
- **예제 4: 정규표현식 포함 줄 출력 `(st.*e)`**
```bash
awk '/st.*e/ { print NR, $0 }' 파일명
```
- **예제 5: 특정 구간 출력 (`strong`부터 `heart`까지)**
```bash
awk '/strong/, /heart/ { print NR, $0 }' 파일명
```
- **예제 6: 특정 단어 등장 횟수 세기**
```bash
awk '/raise/ { ++line } END { print line }' 파일명
```
- **예제 7: 단어별 출현 빈도수 계산**
```bash
awk 'BEGIN {
  FS="[^a-zA-Z]+"
}
{
  for (i=1; i<=NF; i++)
    words[tolower($i)]++
}
END {
  for (i in words)
    print i, words[i]
}' 파일명
```
- **예제 8: wc 명령어 구현**
```bash
awk 'BEGIN { print "파일 시작" }
{
  printf "line %d: %d %d\n", NR, NF, length($0);
  word += NF;
  char += length($0)
}
END {
  printf "줄 수 = %d, 단어 수 = %d, 문자 수 = %d\n", NR, word, char
}' 파일명
```

---
## Bash 쉘 스크립트

### Bash 쉘 소개
- Bash는 리눅스 및 macOS의 기본 쉘이며 본 쉘(Bourne Shell)의 확장판
- 시작 파일 종류
  - `/etc/profile`, `/etc/bash.bashrc` (시스템 전체)
  - `~/.bash_profile`, `~/.bashrc` (사용자 개별 설정)

### 별명 및 히스토리 기능
- `alias`: 명령어에 별명 지정
  - 예: `alias ll='ls -al'`, `unalias ll`
- `history`: 명령 기록 확인, 재실행
  - `!!`, `!n`, `!gcc`, `!?test.c`

### 변수
- 단순 변수: `city=Seoul`, `echo $city`
- 리스트 변수: `cities=(서울 부산 목포)`, `${cities[1]}` → 부산
- 표준 입력: `read x y` → 공백 기준 분리 저장

### 지역변수와 환경변수
- 지역변수는 현재 쉘에만, 환경변수는 자식 프로세스에도 전달
- `export country`: 환경변수로 설정
- 사전 정의 변수: `$USER`, `$HOME`, `$PATH`, `$SHELL` 등
- 명령줄 인수 관련 변수: `$0`, `$1`, `$*`, `$$`, `$#`

### Bash 쉘 스크립트
- 스크립트 작성 → `chmod +x script.sh` → 실행
- `if`, `if-else` 조건문 예시
  ```bash
  if [ $# -eq 1 ]; then
    wc $1
  else
    echo 사용법: $0 파일
  fi
  ```

### 수식

- **비교 연산**
  - 정수 비교: `-eq`, `-ne`, `-gt`, `-lt`, `-ge`, `-le`
  - 문자열 비교: `==`, `!=`, `-z` (빈 문자열), `-n` (비어있지 않음)
- **파일 연산자**
  - `-e 파일`: 존재
  - `-f 파일`: 일반 파일
  - `-d 파일`: 디렉토리
  - `-r 파일`: 읽기 가능
  - `-w 파일`: 쓰기 가능
  - `-x 파일`: 실행 가능
- **논리 연산자**
  - `&&`: AND
  - `||`: OR
  - `!`: NOT
- **산술 연산**
  - `let 변수=수식`
  - `expr 2 + 3`
  - `declare -i 변수`: 정수형
  - `declare -r 변수=값`: 읽기 전용

### 조건문
- `if`, `if-else`, `if-elif-else` 구조 지원
- `case` 문으로 스위치 처리 가능
  ```bash
  if (( score >= 90 )); then
    echo "A"
  elif (( score >= 80 )); then
    echo "B"
  else
    echo "노력 요함"
  fi
  ```
  ```bash
  case $grade in
    10 | 9) echo "A";;
    8) echo "B";;
    7) echo "C";;
    *) echo "노력 요함";;
  esac
  ```

### 반복문
- `for` 구문
  ```bash
  for name in lee kim park; do
    echo "$name 님 초대합니다."
  done
  ```
- `while` 구문
  ```bash
  let i=1
  while (( i <= 5 )); do
    echo "반복 $i"
    let i++
  done
  ```
- `shift`: 인수 목록을 한 칸씩 이동

### 고급 기능
- 함수 정의 및 호출
  ```bash
  say_hello() {
    echo "Hello, $1!"
  }
  say_hello 사용자
  ```
- 재귀 호출 (리커전)
  ```bash
  search_dir() {
    for file in *; do
      [ -d "$file" ] && (cd "$file" && search_dir)
    done
  }
  search_dir
  ```
- 디버깅
  + `bash -v`: 스크립트 출력하며 실행
  + `bash -x`: 실행되는 각 명령을 추적
---
## 프로그래밍 환경
### 프로그램 작성과 컴파일

#### gedit 문서편집기
- GNOME 환경의 기본 GUI 텍스트 편집기
- 터미널 실행:  
  ```bash
  $ gedit [파일이름] &
  ```
#### gcc 컴파일러
- C 언어 컴파일 명령어
- 단일 모듈:
  ```bash
  gcc longest.c         # a.out 실행 파일 생성
  ./a.out               # 실행
  gcc -o longest longest.c  # 실행 파일명 지정
  ```
- 다중 모듈:
  ```bash
  gcc -c main.c         # 목적 파일 생성
  gcc -c copy.c
  gcc -o main main.o copy.o
  ```
예시 프로그램 구조
- `main.c`:
  ```c
  #include <stdio.h>
  #include <string.h>
  #include "copy.h"
  
  int main() {
    ...
    copy(line, longest);
    ...
  }
  ```
- `copy.c`:
  ```c
  void copy(char from[], char to[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') i++;
  }
  ```
- `copy.h`:
  #define MAXLINE 100
  void copy(char from[], char to[]);
  ```

### 자동 빌드 도구 (make)
#### Makefile 예시
```make
main: main.o copy.o
	gcc -o main main.o copy.o

main.o: main.c copy.h
	gcc -c main.c

copy.o: copy.c
	gcc -c copy.c
```
- 실행
  ```bash
  $ make
  $ make main
  ```

### gdb 디버거
#### 컴파일
```
gcc -g -o longest longest.c
```

#### 주요 명령어

| 명령어         | 설명                                        |
|----------------|---------------------------------------------|
| `break n`      | n번째 줄에 중단점(breakpoint) 설정         |
| `break 함수명` | 해당 함수 시작 지점에 중단점 설정          |
| `run`          | 프로그램 실행                               |
| `next`         | 현재 줄 실행 후 다음 줄로 이동 (함수 내부 진입 X) |
| `step`         | 현재 줄 실행 및 함수 내부 진입              |
| `continue`     | 다음 중단점까지 계속 실행                   |
| `print 변수`   | 변수 값 출력                                |
| `list`         | 소스 코드 보기                              |
| `info locals`  | 현재 함수의 지역 변수 목록 보기             |
| `finish`       | 현재 함수 실행 종료 후 복귀 지점으로 이동   |
| `return`       | 현재 함수 종료                              |
| `delete`       | 모든 중단점 삭제                            |
| `clear`        | 특정 줄의 중단점 삭제                       |
| `quit`         | gdb 종료                                    |

#### 예시 사용
```bash
$ gcc -g -o main main.c
$ gdb ./main
(gdb) break main
(gdb) run
(gdb) next
(gdb) print longest
(gdb) list
(gdb) continue
(gdb) quit
```

### 이클립스 통합개발환경
- Eclipse IDE for C/C++ Developers 설치
- 프로젝트 생성:
  `File → New → C/C++ Project`
→ [Hello World ANSI C Project] 또는 [Empty Project] 선택
- `src/`, `include/` 폴더로 구성

### 에디터

#### vi 개요
- 유닉스 기본 텍스트 에디터
- 명령 모드와 입력 모드로 구성됨
- 시작 시 기본적으로 **명령 모드**에서 실행됨

---

#### 모드 전환

| 모드 종류       | 설명                               |
|----------------|------------------------------------|
| 명령 모드       | 기본 모드, 커서 이동 및 명령 수행       |
| 입력 모드       | 텍스트 입력 가능 (`i`, `a`, `o` 등) |
| 마지막 줄 모드   | 저장 및 종료 명령 (`:w`, `:q` 등)      |

---

#### 저장 및 종료

| 명령어      | 설명                              |
|-------------|-----------------------------------|
| `:w`        | 저장                              |
| `:q`        | 종료                              |
| `:wq`       | 저장 후 종료                       |
| `:q!`       | 저장하지 않고 강제 종료             |
| `ZZ`        | 저장 후 종료 (단축 명령)           |

---

#### 커서 이동 명령어

| 명령어      | 설명                          |
|-------------|-------------------------------|
| `h`, `l`    | 좌/우 이동                     |
| `j`, `k`    | 아래/위 이동                   |
| `0`, `$`    | 줄의 처음 / 끝으로 이동        |
| `G`, `nG`   | 마지막 줄 / n번째 줄로 이동     |
| `/pattern`  | pattern을 정방향 검색          |
| `?pattern`  | pattern을 역방향 검색          |

---

#### 입력 모드 전환 명령어

| 명령어 | 설명                         |
|--------|------------------------------|
| `i`    | 커서 앞에 삽입               |
| `a`    | 커서 뒤에 삽입               |
| `I`    | 현재 줄의 맨 앞에 삽입        |
| `A`    | 현재 줄의 맨 뒤에 삽입        |
| `o`    | 다음 줄에 새로운 줄 삽입      |
| `O`    | 현재 줄 위에 새로운 줄 삽입   |

---

#### 삭제/수정 명령어

| 명령어     | 설명                              |
|------------|-----------------------------------|
| `x`        | 현재 커서의 문자 삭제             |
| `dd`       | 현재 줄 삭제                      |
| `dw`       | 현재 단어 삭제                    |
| `D`        | 커서부터 줄 끝까지 삭제           |
| `r`        | 커서 위치 문자 1개 수정           |
| `R`        | 입력하는 대로 덮어쓰기 모드       |
| `cw`       | 현재 단어 삭제 후 입력 모드 전환   |
| `cc`       | 현재 줄 삭제 후 입력 모드 전환     |

---

#### 복사 / 붙여넣기

| 명령어       | 설명                                    |
|--------------|-----------------------------------------|
| `yy`         | 현재 줄 복사                            |
| `nyy`        | n줄 복사                                |
| `p`          | 복사한 줄을 커서 아래(뒤)에 붙여넣기     |
| `P`          | 복사한 줄을 커서 위(앞)에 붙여넣기       |

---

#### 실행 취소 / 반복

| 명령어 | 설명                      |
|--------|---------------------------|
| `u`    | 마지막 작업 실행 취소     |
| `U`    | 현재 줄에서 모든 변경 취소|
| `.`    | 마지막 명령 반복 실행     |

---

#### 문자열 대체 (치환)

| 명령어                  | 설명                                   |
|-------------------------|----------------------------------------|
| `:s/old/new/`           | 현재 줄에서 첫 번째 일치 항목 변경     |
| `:s/old/new/g`          | 현재 줄에서 모든 일치 항목 변경        |
| `:n,m s/old/new/g`      | n~m 줄 사이의 모든 일치 항목 변경      |

---

#### 기타 유용한 명령

| 명령어           | 설명                               |
|------------------|------------------------------------|
| `:set number`    | 줄 번호 표시                       |
| `:set nonumber`  | 줄 번호 숨기기                     |
| `:!command`      | vi 내부에서 외부 쉘 명령 실행       |
| `:e filename`    | 다른 파일 열기                      |
| `:e#`            | 이전에 편집하던 파일로 돌아가기     |

