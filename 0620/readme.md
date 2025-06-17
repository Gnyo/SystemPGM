# System Programming Final Exam

## 1. `open()`, `read()`, `write()`, `close()` 시스템 콜의 역할과 인자
### ❔ 문제
다음 시스템 콜 `open()`, `read()`, `write()`, `close()`를 사용하여 간단한 파일 복사 프로그램을 만든다고 할 때, 각 함수의 역할과 주요 인자에 대해 설명하시오.
또한, `open` 시 `O_CREAT`, `O_APPEND`, `O_TRUNC` 플래그의 의미와 사용 사례를 각각 서술하시오.

### ❗ 풀이
#### `open(const char *pathname, int flags[, mode_t mode])`
- 파일 열거나 없으면 생성
- **인자**: `pathname`(파일 경로), `flags`(열기 모드), `mode`(`O_CREAT` 시 파일 권한 지정)
  - `O_CREAT`: 파일이 없으면 새로 생성 (예: 로그 파일 최초 생성)
  - `O_APPEND`: 파일 끝에만 데이터를 추가 (예: 로그 누적)
  - `O_TRUNC`: 기존 내용 제거 (예: 로그 초기화)

#### `read(int fd, void *buf, size_t count)`
- `fd`로부터 `count` 바이트를 읽어 `buf`에 저장
- **인자**: `fd`(파일 디스크립터), `buf`(버퍼), `count`(읽을 크기)

#### `write(int fd, const void *buf, size_t count)`
- `buf`의 `count` 바이트를 `fd`에 씀
- **인자**: `fd`(파일 디스크립터), `buf`(버퍼), `count`(쓸 크기)

#### `close(int fd)`
- 파일 디스크립터를 닫고 자원을 해제
- **인자**: `fd`(디스크립터)



## 2. 파일 디스크립터와 `dup()`, `dup2()`
### ❔ 문제
파일 디스크립터의 개념을 설명하고, dup()과 dup2()를 사용하는 실제 상황(예: 표준 출력을 파일로 리디렉션하는 경우)을 코드와 함께 설명하시오.

### 풀이
- 파일 디스크립터(FD): 커널이 열려 있는 파일을 추적하기 위해 사용하는 정수
  - 0: `stdin`, 1: `stdout`, 2: `stderr`
- `dup(int oldfd)`: `oldfd`의 복사본을 최소 번호의 새 FD로 반환
- `dup2(int oldfd, int newfd)`: `newfd`로 복사, 이미 열려 있으면 닫고 덮어씀

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1); // stdout -> out.txt
    close(fd);

    printf("파일에 출력됨\n");
    return 0;
}
```


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
- OS 스케줄러에 따라 `부모 → 자식`, 또는 `자식 → 부모`


## 5. 파일 권한과 umask
### ❔ 문제
Linux에서 파일 생성 시 권한이 어떻게 결정되는지 설명하시오.
umask가 실제 파일 권한에 미치는 영향을 예를 들어 설명하고, open()을 사용해 권한이 rw-r--r--인 파일을 생성하려면 어떻게 해야 하는지 코드로 작성하시오.

### ❗ 풀이
- 파일 생성 시 권한은 `mode` - `umask`값으로 결정
- `umask`: 생성 시 제거할 권한 비트
  - 예: `umask 0022` = 그룹/기타 쓰기 권한 제거
```c
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    umask(0000); // umask 값 초기화
    int fd = open("myfile.txt", O_CREAT | O_WRONLY, 0644);
    close(fd);
    return 0;
}
```

## 6. `ls` 명령어 C 언어 구현 개요
### ❔ 문제
다음 조건을 만족하는 간단한 ls 명령어를 C 언어로 구현하시오.
(getopt()와 getopt_long()을 모두 사용하여 옵션 및 롱옵션을 처리할 것.)

인자로 주어진 디렉토리의 파일 목록을 출력한다. (없으면 현재 디렉토리)
다음 옵션을 지원할 것:
-a, --all : 숨김 파일 포함 출력
-l, --long : 파일의 권한, 크기, 수정 시간 등을 함께 출력
-h, --help : 사용법 출력

getopt()로 단일 문자 옵션을 처리하고, getopt_long()으로 롱옵션을 처리할 것.
디렉토리 탐색에는 opendir()과 readdir()을 사용.
파일 정보 조회에는 stat() 또는 lstat()을 사용.

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

void print_usage() {
    printf("사용법: ls [-a|--all] [-l|--long] [-h|--help] [디렉토리]\n");
}

void print_permissions(mode_t mode) {
    char perms[] = "----------";
    if (S_ISDIR(mode)) perms[0] = 'd';
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';
    printf("%s ", perms);
}

int main(int argc, char *argv[]) {
    int show_all = 0, show_long = 0;
    char *target_dir = ".";

    // 먼저 단일 문자 옵션 처리
    int opt;
    while ((opt = getopt(argc, argv, "alh")) != -1) {
        switch (opt) {
            case 'a': show_all = 1; break;
            case 'l': show_long = 1; break;
            case 'h': print_usage(); return 0;
            default: print_usage(); return 1;
        }
    }

    // 롱 옵션 처리
    optind = 1; // 다시 순회
    struct option long_opts[] = {
        {"all",  no_argument, 0, 'a'},
        {"long", no_argument, 0, 'l'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "", long_opts, NULL)) != -1) {
        switch (opt) {
            case 'a': show_all = 1; break;
            case 'l': show_long = 1; break;
            case 'h': print_usage(); return 0;
            default: print_usage(); return 1;
        }
    }

    // 디렉토리 인자 처리
    if (optind < argc) {
        target_dir = argv[optind];
    }

    DIR *dp = opendir(target_dir);
    if (!dp) {
        perror("디렉토리 열기 실패");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        if (!show_all && entry->d_name[0] == '.')
            continue;

        if (show_long) {
            struct stat st;
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", target_dir, entry->d_name);
            if (stat(path, &st) == 0) {
                print_permissions(st.st_mode);
                printf("%5ld ", (long)st.st_size);

                char timebuf[64];
                strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st.st_mtime));
                printf("%s ", timebuf);
            }
        }

        printf("%s\n", entry->d_name);
    }

    closedir(dp);
    return 0;
}
```

## 7. REST API 구조 및 AI API 호출
### ❔ 문제
REST API 구조와 AI API 호출 과정에 대해 기술하시오.

### ❗ 풀이
#### REST API 구조
- 자원을 URI로 표현하고, HTTP 메서드로 조작하는 방식
- 주요 메서드:
  - GET: 데이터 조회
  - POST: 데이터 생성
  - PUT: 데이터 전체 수정
  - DELETE: 데이터 삭제
- 클라이언트-서버 구조, 무상태(stateless), JSON 형식 데이터 주고받음

#### AI API 호출 과정
1. API 키 발급 → 인증에 사용
2. HTTP 요청 구성
   - URL, POST 메서드
   - 헤더: Authorization, Content-Type
   - 바디: prompt, max_tokens 등 JSON 데이터
3. 요청 전송
4. JSON 응답 수신 및 처리


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
