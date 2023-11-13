# 테트리스 프로젝트

이런 저런 [테트리스(TETRIS)](https://en.wikipedia.org/wiki/Tetris)를 만들고자 한다.  

프로젝트 수행할 때 읽은 개발 문서를 정리하는 [Wiki](https://github.com/keunbum/Tetris/wiki) 만듬.  

작성한 문서 자주 읽어 버릇해서 익숙해져야 한다.  
하루아침에 익힐 수 있는 내용이 아님.  

---

## Index

[Project](#project)

- Linux
- Windows

[개요](#개요)

[프로젝트 기본 전제(전략)](#프로젝트-기본-전제전략)  

---

## Project

### [Linux](./Linux/README.md)

### [Windows](./Windows/README.md)

---

## 개요

### Q1. 왜 개인 프로젝트인가?

혼자서 개발해도 커버될 만큼 가벼운 프로젝트라서.  
한 번쯤은 순수 내 의지, 아이디어가 반영된 소프트웨어를 만들어 보고 싶어서.  

### Q2. 왜 게임인가?

내가 게임 개발자가 되고 싶으니까. (여기서 또 '왜?'를 물으면 자소서 하나 써야 한다.)  

학교 다니면서 나름 이런저런 프로젝트를 수행해봤지만,  
정작 게임을 만들어 본 적은 없다.  


### Q3. 왜 테트리스인가?

큰 이유는 없다.  
뭐 만들지 고민할 시간에 일단 뭐든 만들어 보는게 현명한 것 같아서.  

- 고전 게임 중 나에게 가장 친숙한 게임이고,  
([타임지 선정 50대 비디오 게임](https://time.com/4458554/best-video-games-all-time/)에서 1위로 뽑힌 게임이기도 하다.)
- 적절한 구현 난이도,  
- 기술적으로 적용할 만한 요소가 많아서.  

실제로 서비스 할 제품을 만든다기보다는  
나의 게임 개발 역량을 가늠하기 위한 테스트 수단이라고 볼 수 있다.  
'2023년도의 내가 테트리스를 만든다면 이 정도 코드 퀄리티로 구현할 수 있다' 이런 느낌?

---

왜 테트리스였을까를 곱씹어보니,  
닌텐도 스위치 타이틀 중 [<테트리스 99>](https://namu.wiki/w/TETRIS%2099)를 인상 깊게 플레이 했던 경험이 있다.  

게임을 플레이 해보면  
그래픽이 화려하거나, 스토리가 감명 깊거나, 전투 타격감이 좋다든가 하는 그런 요소가 없다.  
근데 재밌어서 몇 시간씩 하게 된다. 

살아남는다는 것에 대한 원초적인 쾌감, 라인을 클리어할 때의 각종 이펙트, 포스 피드백 등이  
조화를 이루면서 순간적으로 황홀경을 느꼈다. 몰입할 수 있게 만들어준 게임이었다.

게임에 투자된 비용과 게임의 재미 여부는 큰 관계가 없다는 걸 배웠다.  
그런 정신을 본받고 싶어서 시작한 프로젝트일지도 모르겠다.


### Q4. 어떤 식으로 프로젝트를 진행할 계획인가?

가장 간단하고 쉬운 버전의 테트리스를 만든 후 점차 기능을 붙이고 개선해 나가는 방식.  

### Q5. 향후 이 프로젝트를 더 근사하게 만든다면?

ex. 크로스 플랫폼 지원, 온라인 멀티 플레이  

이밖에 추가 구현할 아이디어는 얼마든지 다양할 수 있다.  

---

## 프로젝트 기본 전제(전략)

앞으로 프로젝트들을 진행하는데 있어서  

어떤 언어, 라이브러리, IDE, 자료구조, 알고리즘, 디자인 패턴, ...을 사용하는지 관계없이  

근본적으로 따라야 할 강령 등을 서술한다.



- 다른 사람들의 코드를 사용하지 않는다. 언어나 OS가 제공하는 시스템 콜에 의존하는 정도.
  
  이는 다른 사람들이 블로그나 깃허브에 올려 놓은 코드,  
  유튜브에 있을 법한 <테트리스 만들기> 강좌 같은 걸 일절 보지 않음을 의미한다.  

  - 내가 가진 이론적인 베이스, 순수 프로그래밍 역량, 개성, 창의성을 최대한 발휘한다.  

  - 더 근사한 코드, 솔루션이 있을지언정 지금은 나만의 코드를 작성해보는 것이 중요하다.  

  - 다른 사람의 도움을 덜 받고, 가능한 한 가장 밑바닥부터 구현해보고, 스스로 문제를 해결해야 성장할 수 있으니까.  

  - 물론 유용한 시스템 콜이나 게임 로직, 디자인 패턴 등을 찾기 위해 검색은 많이 해봐야 한다.  



- 라이브러리를 사용할 때는 제대로 알고 사용하자.  

  - 하나를 알더라도 확실하게 알고 깊게 이해해야 한다. 두루뭉술하게 많이 아는 것은 의미 없다.  
    API를 설계한 사람의 입장(왜 그렇게 설계할 수밖에 없었는지)을 이해할 정도로 온전히 내 것으로 만들어야 한다.

  - 레퍼런스 문서 읽기를 프로그래밍과 다르게 보지 말자. 레퍼런스 읽기도 개발을 하고 있는 거다.
    
  - **API 사용법을 제대로 숙지하지 않아 발생하는  
    오류나 버그를 찾느라 삽질하는 비용이 더 크다는 걸 알아야 한다.**
  
    

- 유지 보수성(가독성) vs 생산성
  - 어느 한쪽에 절대적인 우위를 매기는 건 애매하고 주관적인 부분이긴 한데,  
  일단 **유지 보수성**을 최우선으로 한다.  

  - 누군가가 **"이러 이렇게 수정해주세요."** 혹은 **"이러 이러한 기능도 추가되면 좋겠어요."** 라고 말할 때,  
  그럴 줄 알았다는 듯이 유연하게 대처할 수 있는 코드가 좋은 코드라고 생각하기 때문.


---
