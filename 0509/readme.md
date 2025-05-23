# System Programming 08

## 파일 입출력 고급 기법

---
## 파일 복사 프로그램 (copy.c)
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

main(int argc, char *argv[])
{
   int fd1, fd2, n;
   char buf[BUFSIZ];
   
   if (argc != 3) {
       fprintf(stderr,"사용법: %s file1 file2\n", argv[0]);
       exit(1);
   }
   
   if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
       perror(argv[1]);
       exit(2);
   }
   
   if ((fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1) {
       perror(argv[2]);
       exit(3);
   }
   
   while ((n = read(fd1, buf, BUFSIZ)) > 0)
       write(fd2, buf, n);
   
   exit(0);
}
```

---
## 파일 디스크립터 복제
### dup() / dup2() 시스템 호출
- 기존의 파일 디스크립터를 복제
```c
#include <unistd.h>

int dup(int oldfd);           // 새로운 디스크립터 번호 자동 할당
int dup2(int oldfd, int newfd); // 지정된 번호로 복제
```
- oldfd와 복제된 새로운 디스크립터는 하나의 파일을 공유

![image](https://github.com/user-attachments/assets/0aaa3f0d-73c4-44fd-b97d-1075aea6719d) |
---|

### dup.c
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd1, fd2;
    
    if((fd1 = creat("myfile", 0600)) == -1)
        perror("myfile");
    
    write(fd1, "Hello! Linux", 12);
    fd2 = dup(fd1);
    write(fd2, "Bye! Linux", 10);
    
    exit(0);
}
```
- 결과: `Hello! LinuxBye! Linux`

---
## 파일 위치 포인터 (File Position Pointer)
- **역할**: 파일 내에서 읽거나 쓸 위치를 가리킴
- **현재 파일 위치**(current file position) 추적

![image](https://github.com/user-attachments/assets/0b4d5457-8e4d-445a-b66b-656c78143d9c) |
---|

### lseek() 시스템 호출
```c
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```
- 성공: 현재 위치 반환
- 실패: -1 반환

### 파일 위치 포인터 이동 예시
```c
// 파일 위치 이동
lseek(fd, 0L, SEEK_SET);           // 파일 시작으로 이동(rewind)
lseek(fd, 100L, SEEK_SET);         // 파일 시작에서 100바이트 위치로
lseek(fd, 0L, SEEK_END);           // 파일 끝으로 이동(append)

// 레코드 단위로 이동
lseek(fd, n * sizeof(record), SEEK_SET);     // n+1번째 레코드 시작위치로
lseek(fd, sizeof(record), SEEK_CUR);         // 다음 레코드 시작위치로
lseek(fd, -sizeof(record), SEEK_CUR);        // 전 레코드 시작위치로

// 파일끝 이후로 이동
lseek(fd, sizeof(record), SEEK_END);         // 파일끝에서 한 레코드 다음 위치로
```

---
## 실습

### 학생 정보 데이터베이스 시스템
**`student.h`**
```c
#define MAX 24
#define START_ID 1401001

struct student {
    char name[MAX];
    int id;
    int score;
};
```

### 데이터베이스 생성
**`dbcreate.c`**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
    int fd;
    struct student record;
    
    if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
        perror(argv[1]);
        exit(2);
    }
    
    printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");
    while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3) {
        lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
        write(fd, (char *) &record, sizeof(record));
    }
    
    close(fd);
    exit(0);
}
```

### 데이터베이스 조회
**`dbquery.c`**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int main(int argc, char *argv[])
{
  int fd, id;
  struct student record;
  if (argc < 2) {
    fprintf(stderr, "사용법 : %s file\n", argv[0]);
    exit(1);
  }
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    perror(argv[1]);
    exit(2);
  }
do {
    printf("\n검색할 학생의 학번 입력:");
    if (scanf("%d", &id) == 1) {
        lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
        if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0))
            printf("이름:%s\t 학번:%d\t 점수:%d\n", record.name, record.id, record.score);
        else 
            printf("레코드 %d 없음\n", id);
    }
    printf("계속하겠습니까?(Y/N)");
    scanf(" %c", &c);
} while (c=='Y');
```

### 데이터베이스 수정
**`dbupdate.c`**
- 레코드 수정 과정: 파일로부터 해당 레코드를 읽어서 이 레코드를 수정한 후에 수정된 레코드를 다시 파일 내의 원래 위치에 쓰기

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
/* 학번을 입력받아 해당 학생 레코드를 수정한다. */
int main(int argc, char *argv[]) {
  int fd, id;
  char c;
  struct student record;
  if (argc < 2) {
    fprintf(stderr, "사용법 : %s file\n", argv[0]);
    exit(1);
  }
  if ((fd = open(argv[1], O_RDWR)) == -1) {
    perror(argv[1]);
    exit(2);
  }
  do {
    printf("수정할 학생의 학번 입력: ");
    if (scanf("%d", &id) == 1) {
      lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
      if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
        printf("학번:%8d\t 이름:%4s\t 점수:%4d\n",
        record.id, record.name, record.score);
        printf("새로운 점수: ");
        scanf("%d", &record.score);
        lseek(fd, (long) -sizeof(record), SEEK_CUR);
        write(fd, (char *) &record, sizeof(record));
      } else printf("레코드 %d 없음\n", id);
    } else printf("입력오류\n");
    printf("계속하겠습니까?(Y/N)");
    scanf(" %c",&c);
  } while (c == 'Y');
  close(fd);
  exit(0);
}
```
