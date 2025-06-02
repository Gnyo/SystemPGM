# System Programming Final Presentation
## Linux 명령어 명령어 구현
### 📌 옵션 처리 원칙
본 프로젝트에서 구현한 모든 Linux 명령어들은 GNU 명령어의 핵심 기능과 주요 옵션들을 충실히 반영하되, 사용자 편의성과 명확한 파싱 구조 유지를 위해 **옵션 결합(short option chaining)은 지원하지 않음.**
### [📜 명령어 리스트](https://github.com/Gnyo/SystemPGM/tree/main/0613/Linux_Commands) - 50개
- `basename` (7)
  - `-s`, `--suffix`: 확장자 제거
  - `-a`, `--multiple`: 다중 인자 처리
  - `-z`, `--zero`: 출력 시 널 문자

- `cat` (9)
  - `-n`, `--number`: 모든 줄에 번호 추가
  - `-b`, `--number-nonblank`: 비어있지 않은 줄에만 번호 추가
  - `-s`, `--squeeze-blank`: 연속된 빈 줄을 하나로 압축
  - `-E`, `--show-ends`: 각 줄 끝에 `$` 표시

- `clear` (1)

- `date` (5)
  - `-u`, `--utc`, `--universal`: UTC 시간 출력
  - `-R`, `--rfc-2822`: RFC 2822 형식 출력

- `dirname`

- `echo` (4)
  - `-n`: 줄 바꿈 없이 출력
  - `-e`: 이스케이프 문자 해석
  - `-E`: 이스케이프 문자 해석 안 함 (기본값)

- `head`
  - `-n`, `--lines`: 출력할 줄 수 지정
  - `-v`, `--verbose`: 파일 이름 출력

- `hostname`

- `printenv`

- `pwd`
  
- `rev`

- `sleep`

- `touch`

- `whoami`

- `yes`
