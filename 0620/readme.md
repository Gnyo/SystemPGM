# System Programming Final Exam

## 1. `open()`, `read()`, `write()`, `close()` 시스템 콜의 역할과 인자
### ❔ 문제
다음 시스템 콜 `open()`, `read()`, `write()`, `close()`를 사용하여 간단한 파일 복사 프로그램을 만든다고 할 때, 각 함수의 역할과 주요 인자에 대해 설명하시오.
또한, `open` 시 `O_CREAT`, `O_APPEND`, `O_TRUNC` 플래그의 의미와 사용 사례를 각각 서술하시오.

### ❗ 풀이
#### `open(path, flags[, mode])`
- 파일 열기 또는 생성
- `flags`: 열기 모드
  - `O_CREAT`: 없으면 생성 (예: 최초 로그파일)
  - `O_APPEND`: 끝에 추가 (예: 로그 누적)
  - `O_TRUNC`: 내용 제거 (예: 로그 초기화)

#### `read(fd, buf, count)`
- `fd`로부터 `count`만큼 읽어 `buf`에 저장

#### `write(fd, buf, count)`
- `buf` 내용을 `fd`에 `count`만큼 기록

#### `close(fd)`
- 열린 파일 닫고 자원 해제


## 2. 파일 디스크립터와 `dup()`, `dup2()`
### ❔ 문제
파일 디스크립터의 개념을 설명하고, `dup()`과 `dup2()`를 사용하는 실제 상황(예: 표준 출력을 파일로 리디렉션하는 경우)을 코드와 함께 설명하시오.

### 풀이
- 파일 디스크립터(FD): 커널이 열려 있는 파일을 추적하기 위해 사용하는 정수
  - 0: `stdin`, 1: `stdout`, 2: `stderr`, 3 이상: 열려있는 파일들을 가리킴
  - `dup(fd)`: 3 이상의 비어있는 번호 중 가장 작은 번호로 복사
  - `dup2(oldfd, newfd)`: oldfd를 newfd로 복사, newfd가 이미 열려 있으면 닫음 (newfd는 덮임)

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("a.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(dup(fd), 1);
    printf("hello\n");
    close(fd);
    return 0;
}
```
- `dup()`으로 FD 복사 → `dup2()`로 stdout(1)를 덮기 → `printf()`는 파일로 출력됨


## 3. inode의 역할과 링크 비교
### ❔ 문제 
리눅스 파일 시스템에서 inode의 역할을 설명하시오.
또한, 하드 링크와 심볼릭 링크의 차이점을 inode 관점에서 비교하고 각각의 장단점을 설명하시오.

### ❗ 풀이
- **inode**: 파일의 메타데이터(크기, 소유자, 권한, 데이터 위치 등) 저장

| 링크 종류  | inode 공유   | 장점                | 단점                      |
| ------ | ---------- | ----------------- | ----------------------- |
| 하드 링크  | ✅ 공유       | 속도 빠름, 원본 삭제해도 유지 | 다른 디렉토리 불가, 디렉토리에 사용 불가 |
| 심볼릭 링크 | ❌ 별도 inode | 디렉토리도 링크 가능       | 원본 삭제 시 끊어짐, 느릴 수 있음    |


## 4. `fork()` 반환값과 메모리 분리
### ❔ 문제
`fork()` 함수의 반환값이 각각 어떤 경우에 해당하는지를 설명하고, 부모와 자식 프로세스가 어떤 방식으로 주소 공간을 분리하여 동작하는지 기술하시오.
간단한 `fork()` 예제를 작성하고, 출력 결과가 어떤 순서로 나올 수 있는지 분석하시오.

### ❗ 풀이
#### `fork()` 반환값
- 부모 프로세스: 자식 PID
- 자식 프로세스: 0
- 실패 시: -1
#### 메모리 분리 방식
- **Copy-On-Write(COW)**: 처음엔 메모리 공유, 수정 시 복사됨
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) printf("자식\n");
    else if (pid > 0) printf("부모\n");
    return 0;
}
```
#### 출력 순서
- 두 프로세스가 동시에 실행되기 때문에 OS 스케줄러에 따라 `부모 → 자식`, 또는 `자식 → 부모`


## 5. 파일 권한과 umask
### ❔ 문제
Linux에서 파일 생성 시 권한이 어떻게 결정되는지 설명하시오.
`umask`가 실제 파일 권한에 미치는 영향을 예를 들어 설명하고, `open()`을 사용해 권한이 `rw-r--r--`인 파일을 생성하려면 어떻게 해야 하는지 코드로 작성하시오.

### ❗ 풀이
- 파일 생성 시 권한은 `mode` - `umask`값으로 결정
- `umask`: 생성 시 제거할 권한 비트
  - 예: `umask 0022` = 그룹/기타 쓰기 권한 제거
```c
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    umask(0022);  // 그룹과 기타 쓰기 권한 제거
    int fd = open("myfile.txt", O_CREAT | O_WRONLY, 0666);  // 권한 0666으로 설정
    close(fd);
    return 0;
}
```

## 6. `ls` 명령어 C 언어 구현 개요
### ❔ 문제
다음 조건을 만족하는 간단한 `ls` 명령어를 C 언어로 구현하시오.
(`getopt()`와 `getopt_long()`을 모두 사용하여 옵션 및 롱옵션을 처리할 것.)

인자로 주어진 디렉토리의 파일 목록을 출력한다. (없으면 현재 디렉토리)
다음 옵션을 지원할 것:
`-a`, `--all` : 숨김 파일 포함 출력
`-l`, `--long` : 파일의 권한, 크기, 수정 시간 등을 함께 출력
`-h`, `--help` : 사용법 출력

`getopt()`로 단일 문자 옵션을 처리하고, `getopt_long()`으로 롱옵션을 처리할 것.
디렉토리 탐색에는 `opendir()`과 `readdir()`을 사용.
파일 정보 조회에는 `stat()` 또는 `lstat()`을 사용.

### ❗ 풀이
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int a = 0, l = 0;
    char *d = ".";
    int o;

    while ((o = getopt(argc, argv, "alh")) != -1) {
        if (o == 'a') a = 1;
        if (o == 'l') l = 1;
        if (o == 'h') { printf("사용법: ls [-a|--all] [-l|--long] [-h|--help] [디렉토리]\n"); return 0; }
    }

    struct option lo[] = {{"all", 0, 0, 'a'}, {"long", 0, 0, 'l'}, {"help", 0, 0, 'h'}, {0, 0, 0, 0}};
    optind = 1;
    while ((o = getopt_long(argc, argv, "", lo, NULL)) != -1) {
        if (o == 'a') a = 1;
        if (o == 'l') l = 1;
        if (o == 'h') { printf("사용법: ls [-a|--all] [-l|--long] [-h|--help] [디렉토리]\n"); return 0; }
    }

    if (optind < argc) d = argv[optind];
    DIR *dp = opendir(d);
    if (!dp) { perror("디렉토리 열기 실패"); return 1; }

    struct dirent *e;
    while ((e = readdir(dp)) != NULL) {
        if (!a && e->d_name[0] == '.') continue;

        if (l) {
            struct stat s;
            char p[1024];
            snprintf(p, sizeof(p), "%s/%s", d, e->d_name);
            if (stat(p, &s) == 0) {
                char m[] = "----------";
                if (S_ISDIR(s.st_mode)) m[0] = 'd';
                if (s.st_mode & S_IRUSR) m[1] = 'r';
                if (s.st_mode & S_IWUSR) m[2] = 'w';
                if (s.st_mode & S_IXUSR) m[3] = 'x';
                if (s.st_mode & S_IRGRP) m[4] = 'r';
                if (s.st_mode & S_IWGRP) m[5] = 'w';
                if (s.st_mode & S_IXGRP) m[6] = 'x';
                if (s.st_mode & S_IROTH) m[7] = 'r';
                if (s.st_mode & S_IWOTH) m[8] = 'w';
                if (s.st_mode & S_IXOTH) m[9] = 'x';
                printf("%s %5ld ", m, s.st_size);
                char t[64];
                strftime(t, sizeof(t), "%b %d %H:%M", localtime(&s.st_mtime));
                printf("%s ", t);
            }
        }

        printf("%s\n", e->d_name);
    }
    closedir(dp);
    return 0;
```

## 7. REST API 구조 및 AI API 호출
### ❔ 문제
REST API 구조와 AI API 호출 과정에 대해 기술하시오.

### ❗ 풀이
#### REST API 구조
- 자원을 URI로 표현하고, HTTP 메서드(GET, POST, PUT, DELETE)로 조작하는 방식
- 클라이언트-서버 구조, 무상태(stateless) 구조
- 주로 JSON 형식 데이터 주고받음

#### AI API 호출 과정
1. API 키로 인증
2. URL, POST, 헤더(JSON)와 바디 구성
3. 요청 전송
4. JSON 응답 처리


## 8. 인의예지신과 중도
### ❔ 문제
인의예지신과 중도에 대해 기술하시오.

### ❗ 풀이
- 인(仁): 타인을 사랑하고 배려하는 자애로운 마음, 측은지심(惻隱之心), 어진 인
- 의(義): 옳고 그름을 분별하며 정의를 실천하는 자세, 수오지심(羞惡之心), 옳을 의
- 예(禮): 예절과 도리를 지키는 태도, 사양지심(辭讓之心), 예절 예
- 지(智): 지혜롭고 슬기로운 판단력, 시비지심(是非之心), 지혜 지
- 신(信): 믿음과 신뢰를 중시하는 덕목, 광명지심(光明之心), 믿을 신
- 중도 : 지나친 쾌락과 극단적인 고행을 모두 배척하고 균형 잡힌 수행법을 따르는 것이 핵심
