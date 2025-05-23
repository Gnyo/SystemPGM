# System Programming 10

## 프로세스 관리

---
## 프로세스 생성

### fork() 시스템 호출
- **기능**: 부모 프로세스가 자신을 복제해 자식 프로세스를 생성, **자기 복제**
- **반환값**: 
  - 부모 프로세스: 자식의 PID 반환
  - 자식 프로세스: 0 반환
- **특징**: "한 번 호출, 두 번 리턴"

### 프로세스 동기화
- **`wait()`**: 부모가 자식 프로세스가 종료될 때까지 기다림
- **`waitpid(pid, ...)`**: 특정 자식 프로세스만 기다림

### 실습
- **`fork1.c`**: 자식 생성 후 PID 출력
```c
#include <stdio.h>
#include <unistd.h>
/* 자식 프로세스를 생성한다. */
int main() {
    int pid;
    printf("[%d] 프로세스 시작 \n", getpid());
    pid = fork();
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
}
```
![image](https://github.com/user-attachments/assets/ecff5fb4-cb02-4ea3-bb23-38c660262d55)

- **`fork2.c`**: 부모/자식이 다른 메시지를 출력
```c
#include <stdlib.h>
#include <stdio.h>
/* 부모 프로세스가 자식 프로세스를 생성하고 서로 다른 메시지를 프린트 */
int main() {
    int pid;
    pid = fork();
    if (pid ==0) { // 자식 프로세스
        printf("[Child] : Hello, world pid=%d\n", getpid());
    }
    else { // 부모 프로세스
        printf("[Parent] : Hello, world pid=%d\n", getpid());
    }
}
```
![image](https://github.com/user-attachments/assets/383e8474-3194-43a6-97a8-f455ebad9d0e)

- **`fork3.c`**: 두 자식 프로세스 생성
```c
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>  // fork(), getpid() 함수를 위해 필요
/* 부모 프로세스가 두 개의 자식 프로세스를 생성한다. */
int main() {
    int pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        printf("[Child 1] : Hello, world ! pid=%d\n", getpid());
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0) {
        printf("[Child 2] : Hello, world ! pid=%d\n", getpid());
        exit(0);
    }
    printf("[PARENT] : Hello, world ! pid=%d\n", getpid());
}
```
![image](https://github.com/user-attachments/assets/909e9f0e-1084-4402-9b88-def133569c36)

- **`forkwait.c`**: 프로세스 기다리기
```c
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>  // For wait()
#include <unistd.h>

/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main() {
    int pid, child, status;
    printf("[%d] 부모 프로세스 시작 \n", getpid());
    
    pid = fork();
    
    if (pid == 0) { // 자식 프로세스
        printf("[%d] 자식 프로세스 시작 \n", getpid());
        exit(1); // 자식 프로세스 종료, 상태값 1로 종료
    }
    
    child = wait(&status); // 자식 프로세스가 끝나기를 기다린다.
    
    printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", WEXITSTATUS(status)); // 자식 프로세스 종료 상태 출력
    return 0;
}
```
![image](https://github.com/user-attachments/assets/16cc27aa-e353-4bb1-a396-64783d7c20f1)

- **`waitpid.c`**: 특정 자식 프로세스 기다리기
```c
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid1, pid2, child, status;
    
    printf("[%d] 부모 프로세스 시작 \n", getpid());

    pid1 = fork();
    if (pid1 == 0) {  // 자식 프로세스 1
        printf("[%d] 자식 프로세스[1] 시작 \n", getpid());
        sleep(1);  // 자식 프로세스 1이 1초 동안 대기
        printf("[%d] 자식 프로세스[1] 종료 \n", getpid());
        exit(1);  // 종료 코드 1로 종료
    }

    pid2 = fork();
    if (pid2 == 0) {  // 자식 프로세스 2
        printf("[%d] 자식 프로세스[2] 시작 \n", getpid());
        sleep(2);  // 자식 프로세스 2가 2초 동안 대기
        printf("[%d] 자식 프로세스[2] 종료 \n", getpid());
        exit(2);  // 종료 코드 2로 종료
    }

    // 부모 프로세스가 자식 프로세스 #1의 종료를 기다린다.
    child = waitpid(pid1, &status, 0);
    printf("[%d] 자식 프로세스 #1 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", WEXITSTATUS(status));  // 자식 프로세스 #1의 종료 코드

    // 부모 프로세스가 자식 프로세스 #2의 종료를 기다린다.
    child = waitpid(pid2, &status, 0);
    printf("[%d] 자식 프로세스 #2 %d 종료 \n", getpid(), child);
    printf("\t종료 코드 %d\n", WEXITSTATUS(status));  // 자식 프로세스 #2의 종료 코드

    return 0;
}
```
![image](https://github.com/user-attachments/assets/0bab2cc5-5a41-4aa6-918c-0b7925f19d8e)

---
