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
내가 모바일 게임보다는 큰 화면에서 즐길 수 있는 PC/콘솔 게임을 선호해서.

### Q2. 왜 DirectX인가?

1. ~~CLI~~ --> 여러 측면에서 게임을 만드는 데 한계가 있음.   
2. ~~Game Engine~~ --> 나도 언젠가 누군가가 만든 엔진을 사용하겠지만,  
  지금은 좀 더 밑바닥부터 구현해보고 싶어서. (by [프로젝트 기본 전제](../README.md/#프로젝트-기본-전제전략))  
3. Graphics API --> 사용법을 익히기 어렵지만 그만큼 정교하게 고성능으로 게임을 만들 수 있음.

Windows에서 개발한다면 OpenGL보다는 DirectX를 택할 수밖에 없다.  
OpenGL 대신 새로 등장한 Vulkan이 있긴 한데, DirectX를 배워두는 게 앞으로의 내 커리어에 유리할 것 같아서.  
기회가 되면 Vulkan을 배우는 날도 오지 않을까?

### Q3. 구체적으로 어떤 라이브러리나 기술을 가져다 만들 것인가?

---

## 개발 문서

### 요구 사항 분석서

[본문](./requirements_analysis.md)

### 해결 방안

---

## 프로젝트 일지

그날 그날 내가 무엇을 했고 어떤 일이 있었는지를 다 기록해두면 좋겠다.  
어떤 점이 어려웠는지, 무엇 때문에 고생했는지, 어려움을 해결하기 위해 어떤 시도들을 했었는지.  

내 개발 방법론이나 일하는 방식에 있어서 어떤 점이 미숙하고 어떤 문제점이 있는지를 복기해서  
보완할 수 있는 기회가 되었으면 하는 바람.

(기술적인 내용은 따로 [위키](https://github.com/keunbum/Tetris/wiki)를 만들었으니 이곳에 작성바람)

---

<font size="3"> <details><summary>2023.05</summary><blockquote> </font>

  <details><summary>05.28(일)</summary>
  
  [왜 게임 개발자는 윈도우즈를 선호하는가?](https://softwareengineering.stackexchange.com/questions/60544/why-do-game-developers-prefer-windows)

  DOS를 게임 개발에 사용하던 마소는 다른 경쟁사와 뒤처지지 않기 위해,  
  Windows에서의 독자적인 게임 개발을 위한, 로우 레벨의 통일된 API가 필요했다.  

  성능 저하 없고, 모든 그래픽, 사운드 및 입력 하드웨어를 위한 단일 API.  
  그리하여 [DirectX](https://en.wikipedia.org/wiki/DirectX)가 탄생하게 되었다. ([나무위키 문서](https://namu.wiki/w/DirectX)도 읽어 보기)

  이에 대응하여 만든 API 규격이 [OpenGL](https://en.wikipedia.org/wiki/OpenGL)이라고 한다.  
  [OpenGL 나무위키](https://namu.wiki/w/OpenGL)도 읽어 볼 것. 

  
  ### Achievements of the day

  기본 문서 생성 및 작성

  깃허브에 [위키](https://github.com/keunbum/Tetris/wiki) 생성.  
  (이것도 내 공부 노하우를 찾기 위한 과정 중 하나)

  내일 [여기](https://learn.microsoft.com/en-us/windows/win32/learnwin32/what-is-a-window-)서부터 이어서 읽기.

  </details>

  [//]: # (End of 05.28)


  <details><summary>05.29(월)</summary>

  마이크로소프트 개발 문서에서 기초 Windows 프로그래밍 개념 습득 중.  
  [깃허브 위키](https://github.com/keunbum/Tetris/wiki)에 그걸 정리해보고 있는데 번역하느라 좀 시간이 걸리는 듯.  
  (넘 미련하게 공부하고 있는 건가. 흠..)
  
  ### Achievements of the day

  [What Is a Window?](https://learn.microsoft.com/en-us/windows/win32/learnwin32/what-is-a-window-)부터 진행 중..  
  낼 [Writing the Window Procedure](https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure)부터 이어서 하면 됨. (작성하다가 말았음)



  </details>

  [//]: # (End of 05.29)


  <details><summary>05.30(화)</summary>
  
  [Managing Application State](https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-) 문서 읽어 봤는데, 100% 이해 못했다..  
  어렵다...  
  이제 슬슬 언어 문법도 신경써야 할 듯.
  
  ### Achievements of the day

- [Writing the Window Procedure](https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure)부터 이어서 진행.

  내일 C++ Template 익힌 후에 [Managing Application State](https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-)부터 이어서 하기.

- [C++ 문서](https://github.com/keunbum/Tetris/wiki/CPP) 생성

  MSDN 읽으면서 이해 안되는 부분이 생기기 시작했기 때문에 C++ 문법 좀 익혀 보려고.

  내일 [정적 변수](https://github.com/keunbum/Tetris/wiki/Memory-model-and-namespace#%EC%A0%95%EC%A0%81-%EB%B3%80%EC%88%98)부터 이어서 작성.


  </details>

  [//]: # (End of 05.30)

  <details><summary>05.31(수)</summary>


  [Note](https://github.com/keunbum/Tetris/wiki/Memory-model-and-namespace#note)에 [translation unit](https://learn.microsoft.com/en-us/cpp/cpp/program-and-linkage-cpp?view=msvc-170) 정리하기
  
  ### Achievements of the day

  [정적 변수](https://github.com/keunbum/Tetris/wiki/Memory-model-and-namespace#%EC%A0%95%EC%A0%81-%EB%B3%80%EC%88%98)부터 작성.

  [Definition 문서](https://en.cppreference.com/w/cpp/language/definition) 읽다가 말았음.  
  내일 이거랑 [declarations](https://en.cppreference.com/w/cpp/language/declarations) 읽어 보고, 책에서 <정적 존속 시간, 외부 링크> 읽기

  </details>

  [//]: # (End of 05.31)   

</blockquote></details>

[//]: # (End of 2023.05)



<font size="3"> <details><summary>2023.06</summary><blockquote> </font>
  <details><summary>06.01(목)</summary>

  쉬는 날..  
  
  ### Achievements of the day

  </details>

  [//]: # (End of 06.01) 

  <details><summary>06.02(금)</summary>

  ### Achievements of the day

  [정적 존속 시간, 외부 링크](https://github.com/keunbum/Tetris/wiki/Memory-model-and-namespace#%EC%A0%95%EC%A0%81-%EC%A1%B4%EC%86%8D-%EC%8B%9C%EA%B0%84-%EC%99%B8%EB%B6%80-%EB%A7%81%ED%81%AC)부터 [using 지시자 대 using 선언](https://github.com/keunbum/Tetris/wiki/Memory-model-and-namespace#using-%EC%84%A0%EC%96%B8%EA%B3%BC-using-%EC%A7%80%EC%8B%9C%EC%9E%90) 전까지 작성.

  </details>

  [//]: # (End of 06.02)   

  <details><summary>06.03(토)</summary>

  쉬는 날.

  ### Achievements of the day

  </details>

  [//]: # (End of 06.03)  

  <details><summary>06.04(일)</summary>

  

  ### Achievements of the day

  [익명 이름 공간](https://github.com/keunbum/Tetris/wiki/Memory-model-and-namespace#%EC%9D%B5%EB%AA%85-%EC%9D%B4%EB%A6%84-%EA%B3%B5%EA%B0%84) 작성하다가 말았음.

  </details>

  [//]: # (End of 06.04) 

  <details><summary>06.05(월)</summary>


  ### Achievements of the day

  [Meet the new C++ standard](https://github.com/keunbum/Tetris/wiki/Meet-the-new-CPP-standard) 작성하다가 말았음.

  </details>

  [//]: # (End of 06.05)   

  <details><summary>06.06(화)</summary>

  쉬는 날.

  ### Achievements of the day

  </details>

  [//]: # (End of 06.06)  

  <details><summary>06.07(수)</summary>


  ### Achievements of the day

  [Meet the new C++ standard](https://github.com/keunbum/Tetris/wiki/Meet-the-new-CPP-standard)에서 예제 분석하다가 말았음.

  </details>

  [//]: # (End of 06.07)  

  <details><summary>06.08(목)</summary>

  클래스 템플릿 간단하게 다뤄 봄.

  ### Achievements of the day

  내일 [템플릿 클래스와 프렌드 함수](https://github.com/keunbum/Tetris/wiki/Recycling-of-CPP-Code#%ED%85%9C%ED%94%8C%EB%A6%BF-%ED%81%B4%EB%9E%98%EC%8A%A4%EC%99%80-%ED%94%84%EB%A0%8C%EB%93%9C-%ED%95%A8%EC%88%98)부터 이어서 작성. 단 그 전에 `프렌드`부터 제대로 알아야 할 듯.

  </details>

  [//]: # (End of 06.08)  

  <details><summary>06.09(금)</summary>

  클래스 템플릿 간단하게 다뤄 봄.

  요 근래 C++ 문법만 판 것 같아서 다시 개발 문서로 돌아 옴.  
  적절하게 왔다 갔다 하기.

  ### Achievements of the day

  [Managing Application State](https://github.com/keunbum/Tetris/wiki/Managing-Application-State) 작성하다가 문법적으로 막히는 거 있어서 아직 미완성.

  
  </details>

  [//]: # (End of 06.09)  


  <details><summary>06.12(월)</summary>

  ### Achievements of the day

  [오버로딩 제약](https://github.com/keunbum/Tetris/wiki/Use-of-Class#%EC%98%A4%EB%B2%84%EB%A1%9C%EB%94%A9-%EC%A0%9C%EC%95%BD) 작성.
  
  </details>

  [//]: # (End of 06.12)  

  <details><summary>06.13(화)</summary>

  ### Achievements of the day

  [프렌드 생성하기](https://github.com/keunbum/Tetris/wiki/Use-of-Class#%ED%94%84%EB%A0%8C%EB%93%9C-%EC%83%9D%EC%84%B1%ED%95%98%EA%B8%B0) 작성하다가 말았음.

  </details>

  [//]: # (End of 06.13) 

  <details><summary>06.14(수)</summary>

  ### Achievements of the day

  [프렌드: << 연산자의 오버로딩](https://github.com/keunbum/Tetris/wiki/Use-of-Class#%ED%94%84%EB%A0%8C%EB%93%9C--%EC%97%B0%EC%82%B0%EC%9E%90%EC%9D%98-%EC%98%A4%EB%B2%84%EB%A1%9C%EB%94%A9)까지 작성.  

  [Moudle 2. Using COM in Your Windows-Based Program](https://github.com/keunbum/Tetris/wiki/Module-2.-Using-COM-in-Your-Windows-Based-Program) 생성 및 일부 작성.
  

  </details>

  [//]: # (End of 06.14) 

  <details><summary>06.15(목)</summary>

  얼마 못 함..  
  컨디션 난조로 인한 휴식.

  ### Achievements of the day
  

  </details>

  [//]: # (End of 06.15) 

  <details><summary>06.16(금)</summary>

  [클래스 생성자와 파괴자](https://github.com/keunbum/Tetris/wiki/Object-and-Class#%ED%81%B4%EB%9E%98%EC%8A%A4-%EC%83%9D%EC%84%B1%EC%9E%90%EC%99%80-%ED%8C%8C%EA%B4%B4%EC%9E%90) 작성하다가 말았음

  ### Achievements of the day
  

  </details>

  [//]: # (End of 06.16) 


  <details><summary>06.19(월)</summary>

  [객체 배열](https://github.com/keunbum/Tetris/wiki/Object-and-Class#%EA%B0%9D%EC%B2%B4-%EB%B0%B0%EC%97%B4) 작성하다가 말았음

  ### Achievements of the day
  

  </details>

  [//]: # (End of 06.19) 

  <details><summary>06.20(화)</summary>

  [this 포인터](https://github.com/keunbum/Tetris/wiki/Object-and-Class#%EA%B0%9D%EC%B2%B4-%EB%93%A4%EC%97%AC%EB%8B%A4%EB%B3%B4%EA%B8%B0-this-%ED%8F%AC%EC%9D%B8%ED%84%B0)는 lvalue인가 rvalue인가 작성한 정도.  

 
  내 진로를 게임 업계로 잡는 게 현명한 선택인지 고민한답시고 너무 시간 뺏기는 듯...  
  완벽한 회사가 있겠느냐만, 내가 너무 큰 환상을 품고 있는 건가 싶기도 하고.  

  어렵다.. 취업하는 것 자체도 어렵고.  
  어떤 회사, 직장을 가야하는지 정하는 것도 어렵고.  
  그 회사가 어떤 회사인지 알기 위해 가장 좋은 건 직접 다녀보는 건데 그 기회조차 얻기가 쉽지 않으니 원...

  행복한 직장 생활이라는 건 애초에 불가능하다고 못박아 두는 게 현명한 건가.  
  어차피 불행할 수 밖에 없는 게 직장 생활이라면 그 중에서 내가 가장 의미를 느끼고 몰입할 수 있는 일을 하는 게 맞는 거겠지?
  
  ### Achievements of the day
  

  </details>

  [//]: # (End of 06.20) 

  <details><summary>06.21(수)</summary>

  [public 다형 상속](https://github.com/keunbum/Tetris/wiki/Class-Inheritance#public-%EB%8B%A4%ED%98%95-%EC%83%81%EC%86%8D) 작성하다가 말았음.
  
  ### Achievements of the day
  

  </details>

  [//]: # (End of 06.21) 
  
</blockquote></details>

[//]: # (End of 2023.06)


<font size="3"> <details><summary>2023.07</summary><blockquote> </font>
  <details><summary>07.03(월)</summary>

  [public 다형 상속](https://github.com/keunbum/Tetris/wiki/Class-Inheritance#public-%EB%8B%A4%ED%98%95-%EC%83%81%EC%86%8D)에서 예제 작성하다가 말았음.
  
  ### Achievements of the day
  

  </details>

  [//]: # (End of 07.03) 


  <details><summary>07.04(화)</summary>

  [포인터와 참조형의 호환](https://github.com/keunbum/Tetris/wiki/Class-Inheritance#%ED%8F%AC%EC%9D%B8%ED%84%B0%EC%99%80-%EC%B0%B8%EC%A1%B0%ED%98%95%EC%9D%98-%ED%98%B8%ED%99%98) 작성하다가 말았음.
  
  ### Achievements of the day
  

  </details>

  [//]: # (End of 07.04) 

  <details><summary>07.05(수)</summary>

  [가상 메서드 정리](https://github.com/keunbum/Tetris/wiki/Class-Inheritance#%EA%B0%80%EC%83%81-%EB%A9%94%EC%84%9C%EB%93%9C-%EC%A0%95%EB%A6%AC) 작성 중.
  
  ### Achievements of the day
  
  </details>

  [//]: # (End of 07.05) 

  <details><summary>07.06(목)</summary>

  [ABC 개념의 적용](https://github.com/keunbum/Tetris/wiki/Class-Inheritance#abc-%EA%B0%9C%EB%85%90%EC%9D%98-%EC%A0%81%EC%9A%A9)까지 작성함.
  
  ### Achievements of the day
  

  </details>

  [//]: # (End of 07.06) 

  
</blockquote></details>

[//]: # (End of 2023.07)