# 테트리스 프로젝트

이런 저런 테트리스 게임을 만들고자 한다.  

---

## Index

[Project](#project)

- [Linux](./Linux/)
- Windows

[개요](#개요)

[프로젝트 기본 전제(전략)](#프로젝트-기본-전제전략)  

---

## Project

### [Linux](./Linux/)

### Windows

---

## 개요

### Q1. 왜 개인 프로젝트인가?

혼자서 개발해도 커버될 만큼 가벼운 프로젝트라서.  
순수 내 의지, 아이디어가 반영된 소프트웨어를 만들고 싶어서.  
~~다른 사람과 협업하는게 얼마나 기구한 일인지 뼈저리게 느껴서~~


### Q2. 왜 게임인가?
내가 게임 개발자가 되고 싶으니까. (여기서 또 왜?를 물으면 자소서 하나 써야 한다.)  
게임 프로젝트를 포트폴리오로 제출해야 하니까.

게임 회사 간다고 포트폴리오로
반드시 게임을 만들어야 하는 건 아니겠지만,  
그렇다고 내가 자신 있게 내세울만한 프로젝트가  
있는 것도 아니니까.

지금 만드는 프로그램이 현재 내 실력을 증명하기에 가장 적합하니까.

### Q3. 왜 테트리스인가?

큰 이유는 없다.  
뭐 만들지 고민할 시간에 일단 뭐든 만들어 보는게 현명한 것 같아서.  

- 고전 게임 중 나에게 가장 친숙한 게임이고,  
- 적절한 구현 난이도,  
- 기술적으로 적용할 만한 요소가 많아서.  

개발하기 앞서 **테트리스**의 기원이나 본질 등을 알면 좋을 것 같다.  
- [About Tetris](https://tetris.com/about-us)
- [나무 위키 문서](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4)

### Q4. 어떤 식으로 프로젝트를 진행할 계획인가?

(이 질문을 제대로 답하려면 서술할 게 많은데,  
우선은 간단하게 쓰고 넘어간다.  
앞으로 프로젝트를 진행하면서 점차 보완해 나가는 걸로.)

- OS별로 따로 개발.  
    가장 근사한 건 Windows, Xbox, PS, NS에서 동시에 서비스되는 게임인데 (더 확장한다면 Android나 iOS까지?)  
    거기까진 너무 시간이 오래 걸리니까. (그럴 여력도 없고)

가장 쉬운 버전을 만들고 점차 어려운 버전을 만들어 보는 걸로.

### Q5. 향후 이 프로젝트를 더 근사하게 만든다면?

프로젝트가 수월하게 진행되면 온라인 대전으로 확장.  
이밖에 추가 구현할 아이디어는 얼마든지 다양할 수 있다.  

* 크로스 플랫폼 지원  

---

## 프로젝트 기본 전제(전략)

앞으로 프로젝트들을 진행하는데 있어서  

어떤 언어, 라이브러리, IDE, 자료구조, 알고리즘, 디자인 패턴, ...을 사용하는지 관계없이  

근본적으로 따라야 할 강령 등을 서술한다.



- 다른 사람들의 코드를 사용하지 않는다.
  
  이는 다른 사람들이 블로그나 깃허브에 올려 놓은 코드,  
  유튜브에 있을 법한 <테트리스 만들기> 콘텐츠 같은 걸 일절 보지 않음을 의미한다.  

  - 내가 가진 이론적인 베이스, 순수 프로그래밍 역량, 개성, 창의성 등을 최대한 발휘한다.  

  - 더 근사한 코드, 솔루션이 있을지언정 지금은 나만의 코드를 작성해보는 것이 중요하다.  

  - 다른 사람의 도움을 덜 받고, 가능한 한 가장 밑바닥부터 구현해보고, 스스로 문제를 해결해야 성장할 수 있으니까.  

  - 물론 유용한 시스템 콜이나 게임 로직, 디자인 패턴 등을 찾기 위해 검색은 많이 해봐야 한다.  



- OS가 제공하는 시스템 콜을 사용할 때는 제대로 알고 사용하자.  

  - 하나를 알더라도 확실하게 알고 깊게 이해해야 한다.  
    두루뭉술하게 많이 아는 것은 의미 없다.  
    API를 설계한 사람의 입장(왜 그렇게 설계할 수밖에 없었는지)을 이해할 정도로 온전히 내 것으로 만들어야 한다.

  - 레퍼런스 문서 읽기를 프로그래밍과 다르게 보지 말자. 레퍼런스 읽기도 개발을 하고 있는 거다.
    
  - **API의 사용법을 제대로 파악하지 않고 사용하여 발생하는  
    오류나 버그를 찾느라 삽질하는 비용이 더 크다는 걸 알아야 한다.**
  
    

- 유지 보수성(가독성) vs 생산성
  - 어느 한쪽에 절대적인 우위를 매기는 건 애매하고 주관적인 부분이긴 한데,  
  일단 **유지 보수성**을 최우선으로 한다.  

  - 누군가가 "이러 이렇게 수정해주세요.", "이러 이러한 기능도 추가되면 좋겠어요." 라고 말할 때,  
  그럴 줄 알았다는 듯이 유연하게 대처할 수 있는 코드가 좋은 코드라고 생각하기 때문.


---
