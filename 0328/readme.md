# System Programming 03

## 목차

① [파일 복사](#파일-복사) </br>
② [파일 이동](#파일-이동) </br>
③ [링크](#링크) </br>
④ [파일 속성](#파일-속성) </br>
⑤ [접근권한](#접근권한) </br>
⑥ [실습: C언어 프로그램](#실습-C언어-프로그램)

---
## 파일 복사

### `cp`(copy)
파일1을 파일2에 복사
```
cp [-i] 파일1 파일2
```
- `-i`: 대화형 옵션, 복사 대상 파일과 이름이 같은 파일이 이미 존재하면 덮어쓰기

파일을 지정된 디렉터리에 복사
```
cp 파일 디렉터리
```
여러 개의 파일들을 지정된 디렉터리에 모두 복사
```
cp 파일1 ... 파일n 디렉터리
```

디렉터리1 전체를 디렉터리2에 복사
```
cp [–r] 디렉터리1 디렉터리2
```
- `r`: 리커전 옵션, 디렉토리도 복사 가능해짐

---
## 파일 이동
### `mv`(move)
파일1의 이름을 파일2로 변경
```
mv [-i] 파일1 파일2
```
- `-i`: 대화형 옵션

파일을 지정된 디렉터리로 이동
```
mv 파일 디렉터리
```

여러 개의 파일들을 지정된 디렉터리로 모두 이동
```
mv 파일1 ... 파일n 디렉터리
```

디렉터리1을 지정된 디렉터리2로 이름 변경
```
mv 디렉터리1 디렉터리2
```

---
## 링크
### 링크
기존 파일에 대한 또 하나의 새로운 이름

파일1에 대한 새로운 이름(링크)로 파일2를 만들어 줌
```
ln [-s] 파일1 파일2
```
- `-s 옵션`: 심볼릭 링크

파일1에 대한 링크를 지정된 디렉터리에 같은 이름으로 만들어 줌
```
ln [-s] 파일1 디렉터리
```

### 하드 링크(hard link)
기존 파일에 대한 새로운 이름, 실제로 기존 파일을 대표하는 i-노드를 가리켜 구현
```
ln hello.c hi
ls -l
```
![image](https://github.com/user-attachments/assets/a0ca4f2a-f79c-4aba-85dc-c79de852d36b) |
---|


### 심볼릭 링크(symbolic link)
다른 파일을 가리키고 있는 별도의 파일로, 실제 파일의 경로명을 저장하고 있는 일종의 특수 파일
- 이 경로명이 다른 파일에 대한 간접적인 포인터 역할을 함
```
ln -s hello.c ha
ls -l
```
![image](https://github.com/user-attachments/assets/0e9e727f-a74b-4cb6-b9fb-fac02b0c92c7) |
---|

---
## 파일 속성
### 파일 속성(file attribute)
블록 수, 파일 종류, 접근권한, 링크 수, 소유자 및 그룹, 수정 시간
```
ls -sl cs1.txt
```
![image](https://github.com/user-attachments/assets/044393a4-bd65-49db-a3a2-517f0580db5b) |
---|
![image](https://github.com/user-attachments/assets/782b72c6-c23b-49f4-8f12-9f77d6d013f1)

### 파일 종류
리눅스에서 지원하는 파일 종류 |
---|
![image](https://github.com/user-attachments/assets/356fbd96-a48d-49cc-8561-8af606c21a89) |

#### `file` 명령어
파일의 종류에 대한 자세한 정보를 출력
```
file 파일
```
![image](https://github.com/user-attachments/assets/46d37db0-5121-443b-bc15-0c4d727bc402) |
---|

---
## 접근권한
### 접근권한(permission mode)

![image](https://github.com/user-attachments/assets/f07f1ba5-691b-405b-bf90-38068c97baa4) |
---|


| 소유자(owner)/그룹(group)/기타(others)로 구분 | 
| --- | 
| <div align="center"> ![image](https://github.com/user-attachments/assets/917163e9-8bd4-4125-b0ef-008f217146b8) </div> | 
| <div align="center"> ![image](https://github.com/user-attachments/assets/06f10378-3b3f-4d64-8573-58df1469ec98) </div> |


### `chmod`(change mode)
파일 혹은 디렉터리의 접근권한을 변경
```
chmod [-R] 접근권한 파일 혹은 디렉터리
```
- `-R`: 지정된 디렉터리 아래의 모든 파일과 하위 디렉터리에 대해서도 접근권한을 변경

### 접근권한 표현
#### 8진수

![image](https://github.com/user-attachments/assets/05dee5a8-949d-47be-8447-11757be4374d) | ![image](https://github.com/user-attachments/assets/ca608518-607b-4f9f-825c-3f7e66105dd7)
---|---

> [!NOTE]
> ```
> $ chmod 644 cs1.txt
> $ ls -l cs1.txt
> -rw-r--r-- 1 chang … cs1.txt
> ```


### 기호

![image](https://github.com/user-attachments/assets/4e54c03a-2622-4733-98c2-70dfa19553ad) |
---|
![image](https://github.com/user-attachments/assets/fc78091b-6c2f-42a1-892e-fcddb5211652) |

> [!NOTE]
> ```
> $ chmod g-w cs1.txt
> $ ls -l cs1.txt
> –rw-r--r-- 1 chang chang 2088 4월 16 13:37 cs1.txt
> ```
> ```
> $ chmod o-r cs1.txt
> $ ls -l cs1.txt
> –rw-r----- 1 chang chang 2088 4월 16 13:37 cs1.txt
> ```
> ```
> $ chmod g+w,o+rw cs1.txt
> $ ls -l cs1.txt
> –rw-rw-rw- 1 chang chang 2088 4월 16 13:37 cs1.txt
> ```

---
## 실습: C언어 프로그램
### 입·출력 조건
대문자를 입력받고 소문자로 출력하고, 소문자를 입력받고 대문자로 출력하는 프로그램을 작성하시오.
단 0을 입력하면 종료하시오.

#### [입출력형식]
```
문자 입력 : A
A의 소문자는 a입니다.
문자 입력 : B
B의 소문자는 b입니다.
문자 입력 : c
c의 대문자는 C입니다.
문자 입력 : 0
```

### 코드
```c
#include <stdio.h>

int main() {
    char ch;

    while (1) {
        printf("문자 입력 : ");
        scanf(" %c", &ch);

        if (ch == '0') {
            break;
        }

        if (ch >= 'A' && ch <= 'Z') {
            printf("%c의 소문자는 %c입니다.\n", ch, ch + 32);
        }
        else if (ch >= 'a' && ch <= 'z') {
            printf("%c의 대문자는 %c입니다.\n", ch, ch - 32);
        }
        else {
            printf("영문자만 입력해주세요.\n");
        }
    }

    return 0;
}
```

### 결과
![image](https://github.com/user-attachments/assets/f38b9e41-1e50-42f1-b492-8175c00d1a66)
