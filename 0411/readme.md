# System Programming 05

## 목차
#### ① [vim](#vim)
#### ② [실습: 쉘 프로그래밍](#실습-쉘-프로그래밍)
#### ③ [실행 파일 변경](#실행-파일-변경)
#### ④ [쉘 스크립트](#쉘-스크립트)
#### ⑤ [자동 실행 프로그램](#자동-실행-프로그램)

---
## vim
- `vi`: 유닉스의 전통적인 텍스트 편집기
- `vim`: **"Vi IMproved (개선된 vi)"**의 줄임말

### 파일 생성 및 열기
```
vi test
```
- 중단(Stopped) 시 재실행 가능
  ```
  fg
  ```
`vi test`| `i`: 입력 모드 진입 | `ESC': 명령 모드로 돌아가기
---|---|---
![image](https://github.com/user-attachments/assets/196b376f-103c-4a9b-a6e2-5f5e49420021) | ![image](https://github.com/user-attachments/assets/fb94e6f7-52e3-4816-9fc9-f3eb4e1d0430) | ![image](https://github.com/user-attachments/assets/b473b5c7-2f16-4e65-9f34-47fd66b23240)

#### 저장 명령
명령 | 설명
---|---
:w|저장만
:q|종료만
:wq|저장하고 종료
:q!|저장 안 하고 강제 종료

---
## 실습: 쉘 프로그래밍
#### 파일 생성
```bash
vi hello.c
```
#### 입력 모드
키보드에서 `i`를 눌러 입력 모드 진입
```c
#include <stdio.h>

int main() {
  printf("Hello World!!");
  return 0;
}
```
#### 파일 저장
키보드에서 `ESC`를 눌러 명령 모드 진입
```
:wq
```

#### 컴파일 및 실행
```
gcc hello.c -o hello
./hello
```
![image](https://github.com/user-attachments/assets/f64a1337-ef11-49c1-8eee-aa5aefc5fba7)|
---|

---
## 실행 파일 변경
> [!NOTE]
> 지금까지는 gcc를 이용하여 파일을 컴파일 하여 실행 파일로 변경

### 권한 정보
- 실행 파일인지 확인하는 방법
```bash
ls -l
```
```diff
-rwxr-xr-x 1 gnyo gnyo  8544 Apr 11 10:30 hello
-rw-r--r-- 1 gnyo gnyo   123 Apr 11 10:20 hello.c
```
- 각 필드 설명
```
- rwx r-x r-x
│ │   │   └─ 다른 사용자(others) 권한
│ │   └───── 그룹 사용자 권한
│ └───────── 파일 소유자 권한
└─────────── 파일 타입 (- = 일반 파일)
```

### 실행 권한 추가
- test1 파일 생성
```
vi test1
```

- test1 파일 편집
```
date
```

- test1 파일 권한 변경
```
chmod +x test1
```
![image](https://github.com/user-attachments/assets/30158ddf-b723-4660-96d3-2ecffe9a7da7)|
---|

- test1 파일 실행
```
./test1
```
![image](https://github.com/user-attachments/assets/36475c97-a699-4a01-ac1c-a20a1007a2a0)|
---|

---
## 쉘 스크립트
### echo
`echo`: 화면에 글자나 변수 값을 출력하는 명령어
```bash
echo [출력할 내용]
echo hello
```
![image](https://github.com/user-attachments/assets/60034ba5-fcf6-4407-883c-1cd68b9a6aa1)|
---|

### 변수
- `$0`: 실행한 스크립트 이름
- `$1`: 첫 번째 인자 변수
- `$2`: 두 번째 인자 변수
- `$#`: 인자의 개수
- `$@`: 모든 인자 (배열처럼)
- `$?`: 직전 명령어의 **종료 상태(exit code)**

![image](https://github.com/user-attachments/assets/878a4a1e-8f94-44b6-857e-ead4dc159d6e)|
---|

### 실습
#### test2
```
echo "User info for userid: $USER"
echo UID: $UID
echo HOME: $HOME
```
- 실행 권한 변경 필요!
- 
![image](https://github.com/user-attachments/assets/83f587bd-ccd6-46aa-b3ba-34f1f349270b) |
---|

#### 결과
![image](https://github.com/user-attachments/assets/0ad70efd-3432-4784-965e-ec420231ba95)|
---|

---
## 자동 실행 프로그램
#### st
인자로 받은 파일(이름)을 자동으로 실행 파일로 만든 후 실행하는 프로그램
```
vi $1
chmod u+x $1
./$1
```
![image](https://github.com/user-attachments/assets/21e61eb2-e999-42b1-a9c9-def7cbbc1f43)|
---|

#### test3
```
days=10
guest="Katie"
echo "$guest checked in $days days ago"
days=5
guest="Jessica"
echo "$guest checked in $days days ago"
```

### 실행
```
./st test3
```
![image](https://github.com/user-attachments/assets/1aef88c4-1123-4045-a1d8-0fdc91b8f104)|![image](https://github.com/user-attachments/assets/d9102e5b-57d9-48fc-9de5-5fc7f342ef13)|
---|---
`vi test3` | `chmod u+x $1`</br>`./$1`
