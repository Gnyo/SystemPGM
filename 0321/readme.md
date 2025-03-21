# System Programming 02

## 목차

① [기본 명령어](#기본-명령어)
② [파일과 디렉토리](#파일과-디렉토리)

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
- alias egrep = 'egrep --color=auto'
- alias fgrep = 'fgrep --color=auto'
- alias grep = 'grep --color=auto'
- alias l = 'ls -CF'
- alias la = 'ls -A'
- alias ll = 'ls -alF'
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
