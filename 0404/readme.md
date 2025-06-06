# System Programming 04

## 목차
① [1. 인공지능의 이해](#-1-인공지능의-이해) </br>
② [2. LLM의 이해와 기초 활용](#-2-llm의-이해와-기초-활용) </br>
③ [3. 챗봇 AI별 특징 알아보기](#-3-챗봇-ai별-특징-알아보기) </br>
④ [4. AI와 실무 문서 작성하기](#-4-ai와-실무-문서-작성하기) </br>
⑤ [5. 검색의 신세계 AI 검색](#-5-검색의-신세계-ai-검색) </br>
⑥ [6. 시각화부터 PPT까지 AI로 뚝딱](#-6-시각화부터-ppt까지-ai로-뚝딱) </br>
⑦ [7. AI로 이미지 생성하기](#-7-ai로-이미지-생성하기) </br>
⑧ [8. 무료 영상 생성](#-8-무료-영상-생성) </br>
⑨ [9. 오디오 AI 활용](#-9-오디오-ai-활용) </br>
⑩ [10. 반복되는 업무는 챗봇에게](#-10-반복되는-업무는-챗봇에게) </br>
⑪ [실습: 생성형 AI를 이용한 프로그래밍](#실습-생성형-AI를-이용한-프로그래밍)

---

## 📘 1. 인공지능의 이해
- 인공지능(AI)의 개념과 역사  
- 머신러닝 → 딥러닝 → 생성형 AI로의 진화  
- ChatGPT 사례 중심으로 AI의 급성장 소개  

---

## 📘 2. LLM의 이해와 기초 활용
- GPT 기반 LLM(Large Language Model)의 구조와 원리  
- 자연어 처리, 문서 생성, 상담 등 폭넓은 활용  
- OpenAI, Google 등 주요 기업들의 기술 동향  

---

## 📘 3. 챗봇 AI별 특징 알아보기
- ChatGPT Plus 등 챗봇의 차이점 소개  
- 실무에서 활용하는 챗봇 기능 예시  
- 다양한 챗봇 서비스 간의 비교  

---

## 📘 4. AI와 실무 문서 작성하기
- 프롬프트 설계를 통해 이메일, 제안서, 보고서 작성  
- AI 문서 자동화의 기본 흐름 소개  
- 전문성 있는 실무 문서 작성법  

---

## 📘 5. 검색의 신세계 AI 검색
- GPT 기반 검색 vs 기존 검색 비교  
- Open/Closed Book Search 개념  
- Perplexity, Bing Chat, ChatGPT의 검색 활용  

---

## 📘 6. 시각화부터 PPT까지 AI로 뚝딱
- 엑셀 데이터 기반 자동 차트/표 생성  
- 문서-슬라이드 자동 작성 예시  
- Word, PowerPoint, OneDrive 연동 가능  

---

## 📘 7. AI로 이미지 생성하기
- 텍스트 기반 이미지 생성 도구 소개 (DALL·E, Midjourney 등)  
- 다양한 스타일, 상상 이미지 생성  
- 콘텐츠 제작, 썸네일 활용  

---

## 📘 8. 무료 영상 생성
- 텍스트/이미지로 영상 제작 (Runway ML 등)  
- 자막, 편집, 배경음악까지 자동화  
- 발표 영상, 유튜브용으로 실용적  

---

## 📘 9. 오디오 AI 활용
- 텍스트 → 음성 합성 (ElevenLabs, Descript 등)  
- 목소리 편집, 노이즈 제거, 성우 AI 활용  
- 오디오북, 내레이션 영상에 활용 가능  

---

## 📘 10. 반복되는 업무는 챗봇에게
- 슬랙, 노션 등과 연동되는 자동화 챗봇 구축  
- 이메일 자동 회신, 스케줄 등록 등 업무 자동화  
- Zapier, Make 등의 워크플로우 활용  

---
## 실습: 생성형 AI를 이용한 프로그래밍
### 입·출력 조건
0~255 사이의 수를 입력 받아 2진수로 출력하고, 1의 개수가 몇 개 인지 출력하고, 8비트 중에 상위 4비트를 출력하시오.

### 프롬프트
생성형 AI: **ChatGPT-4o**

```prompt
0~255 사이의 수를 입력 받아 2진수로 출력하고, 1의 개수가 몇 개 인지 출력하고, 8비트 중에 상위 4비트를 출력하는 C언어 코드 작성해줘.
```

![screencapture-chatgpt-c-67f15c1b-a538-8001-872b-6d05e82157dd-2025-04-06-01_55_26](https://github.com/user-attachments/assets/0a056d3f-b973-493b-963c-f195d58e2fc7)

### 코드
```c
#include <stdio.h>

// 1의 개수 세기 함수
int countOnes(unsigned char n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// 8비트 이진수 출력 함수
void printBinary(unsigned char n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

int main() {
    int input;

    printf("0~255 사이의 정수를 입력하세요: ");
    scanf("%d", &input);

    if (input < 0 || input > 255) {
        printf("입력값이 범위를 벗어났습니다.\n");
        return 1;
    }

    unsigned char number = (unsigned char)input;

    printf("2진수: ");
    printBinary(number);
    printf("\n");

    int oneCount = countOnes(number);
    printf("1의 개수: %d개\n", oneCount);

    unsigned char upper4Bits = (number >> 4) & 0x0F;  // 상위 4비트 추출
    printf("상위 4비트: ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (upper4Bits >> i) & 1);
    }
    printf("\n");

    return 0;
}
```

### 결과
![image](https://github.com/user-attachments/assets/dd42370a-7737-4866-bd18-ab4bb6882240)

