# System Programming 06

## 목차
#### ① [프로세스](#프로세스)
#### ② [인터넷과 서버](#인터넷과-서버)
#### ③ [파일 유틸리티](#파일-유틸리티)
#### ④ [유틸리티](#유틸리티)

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
