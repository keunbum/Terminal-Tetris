# Windows based Tetris

Windows에서 돌아가는 테트리스를 만들어 보려고 한다.

---

## Index

[개요](#개요)  

[프로젝트 구상](#프로젝트-구상)  

[개발 문서](#개발-문서)

  - [요구 사항 분석서](#요구-사항-분석서)
  - [해결 방안](#해결-방안)

[프로젝트 일지](#프로젝트-일지)

---

## 개요

- 개발 기간: 2023-05-28 ~ (ing)  
  (프로젝트 수행 전, 개발 문서(ex. DirectX)를 읽고 API에 익숙해지는 과정도 개발 기간에 포함시킨다.)

- 개발 환경:
  - OS: Windows11
  - IDE: Visual Studio 2022 (편집뿐만 아니라 컴파일, 디버깅 등을 도움 받을 수 있음)
  - LANG: Microsoft Visual C++

- 타겟 플랫폼:  
  Windows10이나 11 정도.  
  (UWP라고 있긴 한데, 우선은 데스크톱 전용으로 배워보고 싶음)

---

## 프로젝트 구상

### Q1. 왜 Windows인가?

그야 Windows가 두터운 사용자(게이머)층을 보유하고 있기 때문.  
그에 따라 현업에서도 주요 타겟이 Windows인 경우가 많고.

게임 개발에 유용한 DirectX를 사용할 수 있어서.

### Q2. 왜 DirectX인가?

~~1. CLI --> 여러 측면에서 게임을 만드는 데 한계가 있음.~~  
~~2. Game Engine --> 나도 언젠가 누군가가 만든 엔진을 사용하겠지만, 지금은 좀 더 밑바닥부터 구현하고 싶어서.~~  
3. DirectX

Windows에서 개발한다면 OpenGL보다는 DirectX를 택할 수밖에 없다.  
OpenGL 대신 Vulkan이 있긴 한데, DirectX를 배워두는 게 내 앞으로의 커리어에 있어 유리할 것 같아서.

### Q3. 구체적으로 어떤 라이브러리나 기술을 가져다 만들 것인가?

---

## 개발 문서

### 요구 사항 분석서

### 해결 방안

---

## 프로젝트 일지

레퍼런스 문서 읽으면서 중요한 내용 잘 기록해 놓을 것.  
단순히 기록하는데 그치지 말고 출처 링크도 다 명시해 놓을 것. (나중에 직접 가봐야할 필요 다분)  
기억력 믿지 말자. 다음날만 되어도 다 까먹는다.  
(그래서 따로 노션이나 위키를 만들까도 생각 중)

꼭 기술적인 내용이 아니더라도  
그날 그날 내가 무엇을 했고 어떤 일이 있었는지를 다 기록해두면 좋겠다.  
어떤 점이 어려웠는지, 무엇 때문에 고생했는지, 어려움을 해결하기 위해 어떤 시도들을 했었는지.  

내 개발 방법론이나 일하는 방식에 있어서 어떤 점이 미숙하고 어떤 문제점이 있는지를 복기해서  
보완할 수 있는 기회가 되었으면 하는 바람.

---

<font size="3"> <details><summary>2023.05</summary><blockquote> </font>


  <details><summary>05.28(일)</summary>
  
  기본 문서 생성 및 작성

  - [왜 개발자는 윈도우즈를 선호하는가?](https://softwareengineering.stackexchange.com/questions/60544/why-do-game-developers-prefer-windows)

  DOS를 게임 개발에 사용하던 마소는 다른 경쟁사와 뒤처지지 않기 위해,  
  Windows에서의 독자적인 게임 개발을 위한, 로우 레벨의 통일된 API가 필요했다.  

  성능 저하 없고, 모든 그래픽, 사운드 및 입력 하드웨어를 위한 단일 API.  
  그리하여 [DirectX](https://en.wikipedia.org/wiki/DirectX)가 탄생하게 되었다.

  이에 대응하여 만든 API 규격이 [OpenGL](https://en.wikipedia.org/wiki/OpenGL)이라고 한다.  
  [OpenGL 이야기](https://namu.wiki/w/OpenGL)도 읽어 볼 것.

  
  ### Achievements of the day

  [위키](https://github.com/keunbum/Tetris/wiki) 생성.  
  이것도 내 공부법을 찾기 위한 과정 중 하나.

  내일 [여기](https://learn.microsoft.com/en-us/windows/win32/learnwin32/working-with-strings#unicode-and-ansi-functions)서부터 이어서 읽기.


  [//]: # (End of 05.28)


  </blockquote></details>

[//]: # (End of 2023.05)