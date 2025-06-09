# System Programming Final Presentation
## Linux 명령어 명령어 구현
### 📌 옵션 처리 원칙
본 프로젝트에서 구현한 모든 Linux 명령어들은 GNU 명령어의 핵심 기능과 주요 옵션들을 충실히 반영하되, 사용자 편의성과 명확한 파싱 구조 유지를 위해 **옵션 결합(short option chaining)은 지원하지 않음.**
### [📜 명령어 리스트](https://github.com/Gnyo/SystemPGM/tree/main/0613/Linux_Commands) - 50개
- `basename` (8개)
  > 파일 경로에서 마지막 요소(파일명)만 추출하는 명령어
  - `-s`, `--suffix`, `--suffix=SUFFIX`: 지정 접미사 제거
  - `-a`, `--multiple`: 다중 인자 처리
  - `-z`, `--zero`: 출력 시 널 문자

- `cat` (9개)
  > 파일의 내용을 출력하거나 여러 파일을 연결하여 출력하는 명령어
  - `-n`, `--number`: 모든 줄에 번호 추가
  - `-b`, `--number-nonblank`: 비어있지 않은 줄에만 번호 추가
  - `-s`, `--squeeze-blank`: 연속된 빈 줄을 하나로 압축
  - `-E`, `--show-ends`: 각 줄 끝에 `$` 표시

- `clear` (1개)
  > 터미널 화면을 깨끗하게 지우는 명령어

- `date` (6개)
  > 현재 날짜와 시간을 출력하는 명령어
  - `-u`, `--utc`, `--universal`: UTC 기준 시간 출력 (ex. Sun Jun  9 06:58:01 UTC 2025)
  - `-R`, `--rfc-2822`: RFC 2822 형식 출력 (ex. Sun, 09 Jun 2025 15:58:01 +0900)

- `dirname` (1개)
  > 파일 경로에서 디렉토리 경로만 추출하는 명령어

- `echo` (4개)
  > 문자열을 출력하는 명령어. <br>
  > 줄바꿈 생략, escape 문자 해석 등 다양한 출력 옵션 제공  
  - `-n`: 마지막에 줄바꿈(`\n`) 생략
  - `-e`: 백슬래시 escape 문자 해석
  - `-E`: escape 문자 해석 안 함 (기본값)

- `false` (1개)
  > 항상 실패(exit code 1)을 반환하는 명령어

- `head` (5개)
  > 파일의 처음 몇 줄을 출력하는 명령어
  - `-n`, `--lines`: 출력할 줄 수 지정 (기본 10줄)
  - `-v`, `--verbose`: 파일 이름을 헤더로 출력

- `hostname` (1개)  
  > 현재 시스템의 호스트 이름(컴퓨터 이름)을 출력하는 명령어  

- `printenv` (3개)  
  > 현재 환경 변수 목록을 출력하는 명령어
  - `-0`, `--null`: 줄바꿈(`\n`) 대신 널 문자(`\0`)로 출력

- `pwd` (3개)  
  > 현재 디렉토리의 경로를 출력하는 명령어  
  - `-L`: 심볼릭 링크 경로 출력 (기본값)  
  - `-P`: 실제 경로(물리적 경로) 출력

- `rev`

- `sleep`

- `touch`

- `true` (1개)
  > 항상 성공(exit code 0)을 반환하는 명령어

- `whoami`

- `yes`
