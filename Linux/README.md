# Linux based Tetris

리눅스(대표적으로 우분투)에서 돌아가는 테트리스 게임을 만들어 보려고 한다.

본 문서는 개발 과정에서 끊임 없이 수정/보완할 예정.

결과물인 안나온 미완성 프로젝트이지만 일단 깃허브에 올려 놓는다.

(원래는 [소켓 프로그래밍 공부](https://github.com/keunbum/connection-to-the-other-world)를 끝내고 프로젝트를 진행하려고 했는데,
당장의 포트폴리오가 시급하기 때문에 동시에 진행.)

---

## 구현 현황

마크다운 동영상 지원 안돼서 유튜브 링크로 대체  

<details><summary>2023.03.30</summary>

https://youtu.be/hotEwiW4uZQ  

- 아직 못움직임.
- 라인 클리어 못함.
- 난수 생성 빈약함.

</details>
 

<details><summary>2023.04.01</summary>
 
https://youtu.be/ffQKhxhylG8  

어제 상황에서 추가로 구현한 건 없고 테트리스 블록만 바꿈.  
- 이제보니 시간 오차도 있음. (최대한 1초에 가깝게 구현하기.)   

</details>

<details><summary>2023.04.06</summary>
 
https://youtu.be/J76D3ZUa2Nc

- 테트로미노 스폰 위치 랜덤화

</details>


<details><summary>2023.04.07</summary>
 
https://youtu.be/fuThpI5kqPI

- 실루엣 구현 (렉이 좀 있음)

</details>

<details><summary>2023.04.09</summary>
 
https://www.youtube.com/watch?v=mRXKvNAepy0

- 회전 개념 적용 (아직 입력 못받음)

</details>

<details><summary>2023.04.10</summary>
 
https://youtu.be/a-AEmpm-fSU

- 테트로미노 분포 통계 제시 (for 의사 난수 테스트)  
- 의사 난수 알고리즘 업그레이드(feat. mt19937)  
  --> 근데 테스트 해보니까 rand()보다 더 말도 안되는 경우도 있는데;  
      확률 분포가 골고루 나오게끔 조작을 가해야하나..

</details>

<details><summary>2023.04.18</summary>

https://youtu.be/gPueVyOEVMs     

기본 조작 및 라인 클리어만 구현..  
(라인 클리어 후 블록 이동X)

</details>

<details><summary>2023.04.19</summary>

https://youtu.be/7kN9u0RXD_s

라인 클리어 후 블록 이동 구현.  
버그의 향연..ㅠㅠㅠ

</details>

<details><summary>2023.04.25</summary>

https://youtu.be/GoYNYvaGNYA  
https://youtu.be/IzYS_XyzfK8

Xbox Controller 테스트.

치명적인 버그는 없음.  
(~~영상에는 컨트롤러만 쓰긴 했는데  
게임 도중 키보드와 혼용하면 커맨드가 2번 적용되는 버그가 있긴함..  
원인은 아직 모름. 파일 디스크립터가 다른데 대체 왜?~~  
인덱싱 실수로 키보드 파일 디스크립터만 닫지 않아서 생긴 문제였음. 해결함.)

키보드와 달리 게임 패드는 계속 눌림을 지원해주지 않는다.  
그래서 빨리 움직이려면 방향키 연타해야 함.  
소프트웨어적으로 계속 눌림을 구현해야 하는데 쉽진 않을 듯..

의사 난수 어느 한쪽으로 몰리는 경향 있음.  
알고리즘을 바꾸거나 인위적으로 조작 가해야 할지도.

</details>

<details><summary>2023.04.27</summary>

https://youtu.be/dU2VdnSt04k

실루엣 및 보조 HUD 구현

계속 눌림이 좀 아쉬움.  
반응 속도가 느린 게 프로그램 문제인지, 가상 머신 그래픽 한계인지는 아직 불분명.  
터미널 출력의 한계일 수도 있고.

</details>

<details><summary>2023.04.29</summary>

https://youtu.be/ef0avagY-WU

7 bag 시스템 구현 및 UI 변경  
난이도 그럴 듯 하게 조절해야 할 듯

</details>

<details><summary>2023.04.30</summary>

https://youtu.be/WRsyfd3xiZM

조작키 설명 추가.


</details>

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

(이런 식으로 작성하는게 맞는진 모르겠지만
일단 내 스타일대로 서술하자.)

- 개발 기간: 2023-03-09 ~ (ing)

  목표로 하는 개발 기간은 따로 없다.  
  이 프로젝트를 수행하기 위해서 어느 정도 시간이 필요할지 가늠할 수 없음.

- 개발 환경:
  - OS: Ubuntu 22.04 (in VirtualBox on Windows)
  - IDE: Visual Studio Code
  - LANG: GNU C17

- 타겟 플랫폼:  
  우분투를 비롯한 데비안 기반 리눅스 정도.

---

## 프로젝트 구상

### Q1. 왜 리눅스인가?

실용성/효용성을 고려한다면 리눅스에서  
게임을 만드는 건 현명하지 못한 선택일 수 있다.  
특별한 이유는 없고 그냥 한번쯤은 리눅스에서 게임을 만들어 보고 싶었음.  

굳이 이유를 든다면 (리눅스 상에서 개발하여 얻을 수 있는 이점)

- 윈도우즈의 여러 API도 그 원형은 리눅스에서의 그것과 비슷한 점이 있기 때문에
  윈도우즈 프로그래밍도 금방 배우지 않을까?
- 리눅스 관련 프로젝트 경험을 어필할 때 필요할 수 있으니까.

### Q2. 왜 CLI인가?

1. ~~웹(크롬 등의 인터넷 브라우저를 이용)~~
2. ~~그래픽 API를 이용한 GUI~~
3. 터미널(GNOME 터미널 에뮬레이터로 대변되는 bash shell 위에서)

인터페이스 관련하여 내 기준에선 크게 세 가지의 선택지가 있는데  
이 중 터미널의 방식을 택하려고 한다.  

- 웹은 제대로 된 게임을 서비스하기엔 한계가 있으니까.
  - 테트리스 정도면 무리없을 듯.
  - 아님 터미널에서 만든 게임을 그대로 웹 상으로 포팅하기?
  - 사실 가장 큰 이유는 내가 웹을 잘 몰라서.  

- GUI보다는 구현 난이도나 낮거나 개발 기간이 덜 걸릴 것 같아서.  
(사실 지금 와서는 좀 후회되긴 하는데 나름 좋은 경험이었다고 생각함.   
Windows 버전부터는 DirectX 사용하는 걸로..)

위에는 형식적인 답을 써본 거다.  

가장 큰 이유는  
'그래도 명색이 게임 개발자의 길을 가겠다는 사람이 이 정도는 만들어봐야 하는 거 아니야?'  
하는 소신이 있어서.

7-80년대 프로그래머들이 겪었던 과정을 비슷하게나마 경험해보고 싶은?  
근데 그때보다 훨씬 프로그래밍 하기 좋은 환경이라..  
제대로 간접 경험해보려면 어셈블리어로 짜야 하는데 그럴 자신은 없음.



### Q3. 구체적으로 어떤 라이브러리나 기술을 가져다 만들 것인가?

- 주 개발 언어: GCC 컴파일러
  - 내가 요즘 C 언어로 소켓 프로그래밍을 공부하고 있던 중이라서.  
  - 사실 C++만 되어도 구현 난이도가 한폭 낮아질 거다. OOP, Template, STL 등이 워낙 강력하니까.  
  - 그러나 비교적 손이 많이 가는 C로 무언가를 만들 수 있다면 그것으로 개발 역량을 보여줄 수 있다고 생각해서.


- 전반적으로 리눅스 운영체제가 제공해주는 시스템 콜, 라이브러리 함수 등을 많이 사용할 듯. (아마 유닉스 기반?)

### Q5. 구현하려는 테트리스 게임의 규칙(로직)은?
이건 [요구 분석서](./requirements_analysis.md)에서 본격적으로 써보는 걸로.

### Q6. 향후 이 프로젝트를 확장 한다면 어떻게 발전시킬 수 있을까?
지금 생각나는 건 다른 유저들과 경쟁할 수 있는 온라인 서비스.  
여기에 추가로 크로스 플랫폼 지원(Windows, macOS, ...)  

---


## 개발 문서

### 요구 사항 분석서
[본문](./requirements_analysis.md) 

### 해결 방안
[본문](./solution.md)

---

## 프로젝트 일지

#### Helpful Docs

- [markdown toggle](https://codex.so/collapsed-block-for-github-markdown)  
- [markdown set font size](https://linuxhint.com/markdown-font-size/)

레퍼런스 문서 읽으면서 중요한 내용 잘 기록해 놓을 것.  
단순히 기록하는데 그치지 말고 출처 링크도 다 명시해 놓을 것. (나중에 직접 가봐야할 필요 다분)  
기억력 믿지 말자. 다음날만 되어도 다 까먹는다.

꼭 기술적인 내용이 아니더라도  
그날 그날 내가 무엇을 했고 어떤 일이 있었는지를 다 기록해두면 좋겠다.  
어떤 점이 어려웠는지, 무엇 때문에 고생했는지, 어려움을 해결하기 위해 어떤 시도들을 했었는지.  

내 개발 방법론이나 일하는 방식에 있어서 어떤 점이 미숙하고 어떤 문제점이 있는지를 복기해서  
보완할 수 있는 기회가 되었으면 하는 바람.

---

<details><summary>template(문서 작성용)</summary>

### Achievements of the day

</details>

[//]: # (template)


<font size="3"> <details><summary>difficulties during the project</summary><blockquote> </font>

  - [ ] ~~현재 내 로직에서는 둘 이상의 스레드가 표준 출력을 하는데,  
      printf가 thread-safe 하지 않기 때문에 의도한 대로 출력되지 않을 가능성이 있다.~~

      [pthread 문서](https://man7.org/linux/man-pages/man7/pthreads.7.html#:~:text=Thread%2Dsafe%20functions,NULL%0A%20%20%20%20%20%20%20%20%20%20%20wcstombs()%0A%20%20%20%20%20%20%20%20%20%20%20wctomb())에 따르면 
      printf, write 모두 thread-safe한 것 같음.  
      thread-safe한 줄 모르고 mutex로 해결했었는데, 그냥 printf 사용해도 될 듯. (검색할 때 더 꼼꼼하게 확인하기)  
      --> 근데, wgotoxy랑 같이 쓰이면 mutex 필요하긴 할 듯.  
      --> mutex 말고 spinlock 사용해도 충분.  
      --> spin lock 써봤더니 버그 있음. 스레드 우선순위 문제 때문에 잘 사용해야 함. 안 그럼 무한루프 도는 것 같음;  
          일단 다시 mutex로 해결함.

  - [X] ~~리얼 타임 타이머가 fork일 때는 예상대로 잘 동작했었는데  
        pthread 돌리니까 예상밖의 행동(시그널 핸들러 호출 이후에 하던 일 계속 안하고 계속 블로킹 당하고 있음)을 함.  
        하; 어렵다. 병렬 프로그래밍..  
        핸들러 안에서 로직을 수행하는 걸로 수정하긴 했는데, 왜 그런지는 알고 싶음..  
        (혹시 [sigaltstack](https://man7.org/linux/man-pages/man2/sigaltstack.2.html) 이거 안써서 그런건가? 확실치는 않음)  
        물론 fork를 쓰면 원래대로 잘되긴 하겠지만, 바람직한 솔루션은 아님.~~

      스레드들의 시그널 마스크에 대한 이해 부족이었음.  
      아직 100% 알겠는 건 아닌데, 일단 해결은 함.

  - [X] timer_create 시스템 콜을 사용하려고 했는데 WSL에는 구현이 안되어 있다고 한다. 어떡하지; 
    
    ~~해결책 1. setitimer나 alarm 함수 사용.  
      -> 아쉽지만, 지금 상황에선 적절한 타협책이긴 함.  
         근데 이거 쓰면 내가 조사한게 너무 아까운데ㅠㅠㅠㅠ.~~

    해결책 2. 버츄얼 박스 깔아서 우분투 배포판 띄우기. 이러면 에디터 설정도 해야 함.  
      -> 컴퓨터 사양은 좋아서 문제 안됨.  
      -> 컴퓨터 용량..도 괜찮음.  
      -> 그리고 리눅스 버전 게임을 만들 거면 이렇게 만드는 게 가장 확실한 방법이긴 함.  
      -> 무엇보다도 대체 불가능한 라이브러리 함수를 사용해야 하는 상황이 올 수도 있기 때문에.  
      ~~-> (근데 나 무슨 생각으로 리눅스에서 테트리스 게임 만들 생각을 한 거지?  
          리눅스는 소켓 프로그래밍 할 때나 사용하면 될 것 같은데..
          지금이라도 Windows로 넘어갈까?)  
      -> 검색 좀 해봤는데, 이거 관련 세팅 하느라 하루 다 가겠는데? 흠...~~
    
    ~~그밖에 AWS 서버를 빌리는 방법도 있긴 한데.. 개발할 때는 좀 불편할 듯.~~

    일단 리눅스 프로젝트는 마무리 하는 게 맞는 것 같음 --> 가상 머신 사용

  - [ ] `evdev`로 이벤트 기반 입력 처리 하려고 했는데, `ssh`로는 키보드 이벤트를 전달하지 못한다고 한다.  
        그럼.. 버추얼 박스에 우분투 데스크톱 버전 깔아야 함.  
        아님 우분투 설치된 노트북으로 테스트 할 수도 있음.

  - [ ] 컨트롤러와 같은 디바이스를 `open`으로 미리 열지 않고  
        게임이 실행되는 도중에 입력 장치를 감지하게끔 하고 싶은데.. 어떻게 해야하는 거지?  



</details>

[//]: # (difficulties during the project)


<font size="3"> <details><summary>miscellaneous tip</summary><blockquote> </font>

  - Visual Studio Code format 설정.  
    **Ctrl+,** -> **C_Cpp: Clang_format_style 검색** -> **값 WebKit으로 설정** -> **Alt+Shift+F(자동 포맷 완성)**

  - [The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/index.html)  
    man page 외 유용한 레퍼런스 문서.

</details>

[//]: # (miscellaneous tip)


<font size="3"> <details><summary>miscellaneous search</summary><blockquote> </font>


<details><summary>const int*와 int* const의 차이</summary>
  
  const int* and int* const are two different types of pointers.

  const int* is a pointer to a const int. This means that the int value pointed to by the pointer cannot be modified through the pointer.  
  However, the pointer itself can be modified to point to a different const int.

  For example:

  ```c
  const int x = 10;
  const int y = 20;
  const int* p = &x; // p points to x
  p = &y; // p can be modified to point to y
  //*p = 30; // error: cannot modify the value pointed to by p
  ```

  On the other hand, int* const is a const pointer to an int. This means that the pointer itself cannot be modified to point to a different int,  
  but the int value pointed to by the pointer can be modified.

  For example:

  ```c
  int x = 10;
  int y = 20;
  int* const p = &x; // p points to x
  //p = &y; // error: p cannot be modified to point to y
  *p = 30; // the value pointed to by p can be modified
  ```

  </details>


  <details><summary>getopt</summary>

  [getopt](https://man7.org/linux/man-pages/man3/getopt.3.html)  
  그동안 리눅스 명령행에서 프로그램 실행할 때  
  `-a`나 `--version` 같은 옵션 처리 어떻게 하나 했더니 라이브러리가 다 있었네...  

  </details>


  <details><summary>poll, select</summary>
  
  시간 되면 poll, select 공부하기
  
  </details>  


  <details><summary>signal</summary>
  
  signal, sigsuspend 등 이어서 조사하기
  
  </details>  


  <details><summary>abort()와 _Exit()</summary>

  </details>  



</details>

[//]: # (miscellaneous search)


---




<font size="3"> <details><summary>2023.03</summary><blockquote> </font>
  <details><summary>03.09(목)</summary>
  
  **기본 문서 생성 및 작성**  
  **테트로미노 디자인 시도**
      
  아마 수정될 사항이 많을 것으로 예상.  
  오늘은 일단 테트로미노를 화면에 출력하는 것까지 목표로.

  하.. wchar_t 제대로 몰라서 삽질함.  
  어쨌든 이제 wchar_t 쓰는 것까진 익힌 듯.  

  검색하면서 유용했던 링크들은 소스 코드에 주석 달아 놓음.

  ### Achievements of the day

  Compile:

  ```bash
  $ gcc main.c tetromino.c -o main -Wall
  ```

  Execute:

  ```bash
  $ ./main
  ⬛⬛⬛⬛

  ⬛⬛
  ⬛⬛

  ⬛⬛⬛
  ⬜⬛⬜

  ⬜⬛
  ⬜⬛
  ⬛⬛

  ⬛⬜
  ⬛⬜
  ⬛⬛

  ⬜⬛⬛
  ⬛⬛⬜

  ⬛⬛⬜
  ⬜⬛⬛
  ```
  </details>

  [//]: # (End of 03.09)

  <details><summary>03.10(금)</summary>

  큰 틀의 HUI 출력하고 그 안에서
  시간의 흐름에 따라 테트로미노가 아래로 이동하도록 화면에 출력하기.

  자식들 기다릴 동안 부모 프로세스는 뭐해야 하나 고민이었는데, 이를 해결할 시스템 콜 찾은듯.  
  무턱대고 쓰지 말고 제대로 알고 사용하자.  
  (API의 사용법을 제대로 파악하지 않음으로 인해 삽질하는 시간이 생각보다 크다.)
  * [sigsuspend](https://man7.org/linux/man-pages/man2/sigsuspend.2.html)


  하.. 테트리스 괜히 하기로 한 것 같다. 진행이 너무 안된다. 큰일인데.

  일단 시간 표시 모듈은 대충 구현되었으니 내일부턴 게임의 핵심 모듈 부분 구현 해보는 걸로.  
  코드에 주석으로 써놓긴 했지만 한글로도 정리해 놓자.

    모듈을 너무 잘게 쪼갤 필요는 없다.  
    순차적인 걸 먼저 구상해보고 정 안되면 프로세스 하나씩 추가하기.  
    (물론 퍼포먼스 측면에서 멀티 프로세싱을 사용할 수도 있음)

    이제 보니 B(A), D(C), E 이렇게 3개만 있으면 될 것 같다.
    잘하면 B(A, C, D), E 이렇게 2개도 가능할지도..  
    단, 추후에 변경될 소지가 있다는 점 감안하고 설계하기.

    * A: 블록을 생성하고 MAX_QUEUE_SIZE가 FULL이 될 때까지 que에 푸시.
    
    * B: que에서 테트로미노를 가져와 스카이라인에서 출발 시키고, A에게 큐를 채우도록 요청. (이 모듈의 관리자가 될 가능성 높음)
    
    * C: 사용자로부터(키보드로) 입력 값을 읽고 누군가(아마도 D?)에게 값을 주는 사람.  
        (이제보니 D가 혼자해도 될 것 같기도 하고..)
    
    * D: 주기마다 테트로미노의 위치 값을 변경하는 사람.

      1-1. 스카이라인(시작점)에 나오는 순간부터 테트로미노는 일정 속도로 떨어진다.  
      1-2. D는 사용자의 입력이 들어올 때 그에 맞게 위치를 변경해야 한다.  
      2-1. 테트로미노가 바닥(또는 다른 테르로미노)에 닿아 멈추면 B에게 새로운 테트로미노 출고를 요청한다.  
      2-2. 스카이라인에서 테트로미노가 멈추면 B에게 게임 오버 메시지를 보낸다.  

    * E: 매 주기마다 밖으로 나온 테트로미노의 현재 위치를 비롯해 모든 화면의 변화를 게임 화면에 그리는 사람.

  
### Achievements of the day

  근데 콘솔 출력 Visual Studio Code에서만 예쁘게 나오는 것 같은데..

  Compile: 

  ```bash
  $ gcc ./*.c -o main -Wall
  ```

  Execute:

  사진 올리기 귀찮아서 생략.

  </details>

  [//]: # (End of 03.10)


  <details><summary>03.11(토)</summary>

  - 지금든 생각인데 버츄얼 박스나 우분투 깔린 노트북 이용해서 제대로 테스트 해보긴 해야 할 듯.  
  (유니코드 깨지는 것 땜에..) 급한 건 아니니 나중에 해도 괜찮.

  - Makefile 어떻게 만들지 고민이었는데 Bing AI가 알려줬다.. 대박..  
  `HDRDIR`, `EXEFILE` 정도만 따로 추가한 정도.

    ```makefile
    # Makefile
    # Bing AI's answer for the Question("Could you please create a Makefile to compile and run a C project with multiple folder structure?")

    CC = gcc
    CFLAGS = -Wall -Wextra -Werror
    SRCDIR = src
    OBJDIR = obj
    BINDIR = bin
    HDRDIR = src
    EXEFILE = tetris

    SOURCES := $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
    OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

    $(BINDIR)/$(EXEFILE): $(OBJECTS)
      @mkdir -p $(@D)
      $(CC) $(CFLAGS) $^ -o $@

    $(OBJDIR)/%.o: $(SRCDIR)/%.c
      @mkdir -p $(@D)
      $(CC) $(CFLAGS) -c $< -o $@ -I $(HDRDIR)

    .PHONY: clean run

    clean:
      rm -rfv $(BINDIR)/* $(OBJDIR)/*

    run:
      ./$(BINDIR)/$(EXEFILE)
    ```

    Compile: 

    ```bash
    $ make
    ```

    Execute:
    
    ```bash
    $ make run
    ```

    Clean:

    ```bash
    $ make clean
    ```

  - 간단한 콘솔 테트리스 게임 만드는데도 조사해봐야할 API가 너무 많다.  
  C언어를 많이 안써 버릇해서 그런건가...

    일단, **사용자 입력 처리**는 검색 결과 발견한 것들.

    ~~1. curses.h의 getch.\
      --> Windows의 conio.h에서 제공.\
      --> Linux에서도 설치해서 쓸 수 있긴 한데.. 그닥 추천하진 않는 듯.~~  
    2. termios.h의 [tcgetattr](https://man7.org/linux/man-pages/man3/tcgetattr.3p.html).  
      --> 리눅스에서 사용 가능.  
      --> OK!


  - 검색 해보니 **게임 루프 구현** 관련하여 대체적으로 해주는 조언은 간단한 단일 스레드 게임 루프로 시작하고,  
  복잡한 기능을 추가하거나,  
  멀티 프로세스를 도입하지 않으면 해결할 수 없는 문제가 발생한 경우에만 (ex. 최적화를 했음에도 눈에 띄는 성능 저하)  
  다중 프로세싱 도입을 고려하라는 입장..

### Achievements of the day
  
  - 소스 코드 폴더 구조로 분류.
  - Makefile 도입
  - 게임 루프 로직 구현에 대한 고찰 및 통찰. (구현은 아직 X)
  - 사용자 입력 어떻게 받을지 힌트 얻기.
  
  </details>

  [//]: # (End of 03.11)


  <details><summary>03.12(일)</summary>

  - 어제 조사한 거 + 구상한 거 바탕으로 게임 루프 로직 설계  
  종이에 구조 그려본 다음, 간단한 버전부터 구현해보기.

  - 전반적인 프로젝트 구조 개선.  
  (Makefile을 좀 더 정교하게 사용할 줄 알면, 더 체계적인 프로젝트 구조 갖출 수 있을 듯)

  - main2() 관련 로직 고민하느라, 게임 루프 로직 설계 못함.  
  일단 실행 시 문제 없게 끔 수정해놨으니까, 내일부터 Game Play 로직 구현하면 됨.  
  한번에 다 짜려고 하지 말고, 단계적으로 차근차근 구현하기.

### Achievements of the day

  </details>

  [//]: # (End of 03.12)

  <details><summary>03.13(월)</summary>

  ~~게임 루프 정교화 과정 & 사용자 입력 처리 구현 예정.~~

  - 전반적인 프로젝트 구조 변경 for 가독성 향상

### Achievements of the day

  </details>

  [//]: # (End of 03.13)

  <details><summary>03.14(화)</summary>

  게임 루프 정교화 과정 & 사용자 입력 처리 구현 예정.

  게임 루프 만들기 전에 사용자 입력 처리하는 모듈 구현 하기. 멀티 프로세스 돌릴 수 있게끔.  
  항상 좀비 프로세스 발생하지 않게끔 조심.

  - 시그널 조사

    - [시그널 속성](https://man7.org/linux/man-pages/man7/signal.7.html#:~:text=Signal%20dispositions%0A%20%20%20%20%20%20%20Each,are%20left%20unchanged.)

      프로세스는 특정 시그널에 대해 어떻게 반응할 것인가에 대한 속성을 지니고 있다.  

      그렇기에 멀티 스레드 환경이라면 모든 스레드는 동일한 시그널 속성을 공유한다.  

      [fork](https://man7.org/linux/man-pages/man2/fork.2.html)는 부모의 시그널 속성을 물려 받고, 시그널 마스크는 초기화 되는 반면,  
      [execve](https://man7.org/linux/man-pages/man2/execve.2.html)는 시그널 속성이 초기화되고, 시그널 마스크는 보존된다고 한다.

      여기서 시그널 마스크란, blocked signal들의 비트마스크를 의미한다.


    - **calling process**와 **caller process**의 차이(크게 중요한 건 아닌데 혹시나 헷갈릴까봐)  
      'calling process’는 시스템 콜을 호출하는 프로세스를 의미한다.  
      반면에 'caller process’는 다른 프로세스(스레드)의 실행을 시작하는 프로세스를 의미.

    - [시그널을 보내는 다양한 시스템 콜](https://man7.org/linux/man-pages/man7/signal.7.html#:~:text=Sending%20a%20signal,a%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20specified%20process.)

    - [특정 시그널이 잡히기를 기다리기](https://man7.org/linux/man-pages/man7/signal.7.html#:~:text=Waiting%20for%20a,signals%20is%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20caught.)

      - [sigsuspend](https://man7.org/linux/man-pages/man2/sigsuspend.2.html):  
        주로 크리티컬 섹션을 실행할 때 방해를 받지 않기 위해 실행.

    - [동기적으로 신호 잡기](https://man7.org/linux/man-pages/man7/signal.7.html#:~:text=Synchronously%20accepting%20a,describing%20the%20signal.)

      <details><summary>여기서 잠깐. 동기화와 비동기화란?</summary>
      In computer science, synchronous and asynchronous are two types of programming models that define how software is designed and executed.

      **Synchronous** operation means that a process runs only as a result of some other process being completed or handed off. In other words, things “wait” for other things.  
      On the other hand, **asynchronous** operation means that a process operates independently of other processes. In this case, things don’t “wait” for other things. Asynchronous models are critical for performance reasons and to more efficiently use computing resources.

    - [시그널 마스크와 보류 시그널](https://man7.org/linux/man-pages/man7/signal.7.html#:~:text=Signal%20mask%20and%20pending,an%20execve(2).)

      시그널은 크게 프로레스-지향과 스레드-지향이 있는데 프로세스-지향은 시그널이 막히지 않은 스레드들 중 커널이 임의로  
      하나를 고른다고 한다.

      스레드는 [sigpending](https://man7.org/linux/man-pages/man2/sigpending.2.html)를 통해서 보류된 시그널 집합을 얻을 수 있다. 여기서 보류된 시그널 집합(이하 pending signal)이란 시그널이 발생했지만, 시그널 핸들러 등에 의해서 처리되지 않은 시그널을 일컫는다.


    - [시그널 핸들러 실행하기](https://man7.org/linux/man-pages/man7/signal.7.html#:~:text=Execution%20of%20signal,sensible%20software%20design!)

      커널 모드에서 유저 모드로 전환(context switching)될 때 마다 커널은 열린 시그널(프로세스가 등록한 핸들러가 목적으로 한)이 있는지 확인한다.


### Achievements of the day

  시그널 관련 문서 읽다가 쓰레드도 써야겠다는 결론..

  </details>

  [//]: # (End of 03.14)


  <details><summary>03.15(수)</summary>

  - 스레드 조사

    이제 보니 멀티 스레드를 사용할 수도 있기 때문에  
    관련하여 공부한 후 프로젝트 이어서 하기.

    ---

    [pthread](https://man7.org/linux/man-pages/man7/pthreads.7.html)는 [POSIX](https://en.wikipedia.org/wiki/POSIX) thread를 의미한다.
    나는 그중에서 [nptl](https://man7.org/linux/man-pages/man7/nptl.7.html) 구현체를 사용.  
    읽을게 많네..? 근데 충분히 읽을 만한 가치가 있는 문서인 듯.

    ---
    
    스레드들은 전역 메모리(데이터, 힙 영역)를 공유하고 각자의 스택 영역을 가지고 있다.  
    따라서 정적(static) 지역 변수를 사용한다면 이는 공유되므로 주의할 것.  
    (그래서 스택 영역을 지칭할 때 `지역 변수`와 구분하기 위해 `자동 변수`라는 용어가 나온다.)


    - 하나의 프로세스에 속한 스레드들은 다음의 속성을 공유한다.  
      - process ID  
      - parent process ID  
      - prcess group ID and session ID  
      - controlling terminal  
      - user and group IDs (credentials)
      - open file descriptors
      - record locks (see [fcntl](https://man7.org/linux/man-pages/man2/fcntl.2.html))  
      - signal dispositions  
      - file mod creation mask  
      - currently directory and root directory  
      - interval timers and POSIX timers  
      - nice value  
      - resource limits  
      - measurements of the comsumption of CPU time and resources  



    - 스택 외에도 스레드들은 고유의 속성들을 지니는데 다음과 같다.  
      - thread ID (pthread_t)  
      - signal mask (pthread_sigmask(3))  
      - the errno variable  
      - alternate signal stack  
      - real-time scheduling policy and priority  
      다음과 같은 특정 리눅스 기능도 있음  
      - capabilities (see capabilities(7))
      - CPU affinity (see sched_setaffinity(2)))


    - pthread 함수들은 errno를 설정하지 않는다.

    - 표준 함수 중에는 thread-safe하지 않은 것도 있다.  
      자세한 건 [man page 본문](https://man7.org/linux/man-pages/man7/pthreads.7.html#:~:text=Thread%2Dsafe%20functions,NULL%0A%20%20%20%20%20%20%20%20%20%20%20wcstombs()%0A%20%20%20%20%20%20%20%20%20%20%20wctomb()) 참고.

    - `async-cancel-safe`라는 낯선 용어가 나오는데 일단 넘어감.  

    - `cancellation points`.. 강제되는 것도 있고, 해도 좋은 것도 있고. 무슨 말인지 이해 못함. 넘어감.

    - 스레딩을 구현할 때 [clone](https://man7.org/linux/man-pages/man2/clone.2.html)을, 스레드 동기화 프리미티브(뮤텍스, 스레드 조인 등)는
    [futex](https://man7.org/linux/man-pages/man2/futex.2.html)를 사용하여 구현된다고 한다.

    ---

  - About [NPTL](https://man7.org/linux/man-pages/man7/nptl.7.html)

    `NPTL (Native POSIX Threads Library) is the GNU C library POSIX threads implementation  
    that is used on modern Linux systems.`

    NPTL은 관리자 스레드(manager thread)를 사용하지 않는다고 한다.  

    스택 사이즈 설정 관련해서는 [getrlimit](https://man7.org/linux/man-pages/man2/setrlimit.2.html) 참조.


    NPTL 사용시 signul number 32([timer_create](https://man7.org/linux/man-pages/man2/timer_create.2.html) 참조), 33은 사용할 수 없음.  
    웬만한 라이브러리 함수도 사용자의 32, 33 사용을 막거나 무시하게끔 설계한다고 한다.

    한 프로세스 내 스레드들은 credential을 공유하기 때문에 한 스레드가 이를 변경하면  
    내부적으로 설계된 wrapper funtion 덕에 모든 스레드가 한꺼번에 변경된다고 한다. ([본문](https://man7.org/linux/man-pages/man7/nptl.7.html#:~:text=NPTL%20and%20process,setgroups(2).))


    ---

  - About [pthreads](https://man7.org/linux/man-pages/man7/pthreads.7.html)

    - [pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html)

      스레드 사용시 컴파일 명령에 -pthread 추가해야 함.

    - [pthread_exit](https://man7.org/linux/man-pages/man3/pthread_exit.3.html)
    
    - [pthread_attr_init](https://man7.org/linux/man-pages/man3/pthread_attr_init.3.html)

    - [pthread_self](https://man7.org/linux/man-pages/man3/pthread_self.3.html): 자신의 스레드 ID 확인

    ---

  - 그밖에 자잘한 정보들

    스레드를 새로 생성하면 부모 스레드의 blocked signal mask를 그대로 물려받고, pending signal은 초기화된다고 한다.  
    그밖에 물려 받는 것들이 많은데, 어차피 일일이 기억 못함. 일단 읽고 넘어갈 것.

    ---

    스레드 ID를 '=='로 비교하는 건 바람직하지 않다고 한다.
    [pthread_equal](https://man7.org/linux/man-pages/man3/pthread_equal.3.html)를 이용할 것.

    ---

    스레드는 `joinable`과 `detached` 두 가지 타입이 있다.  

    새로 생성된 스레드의 결과나 종료 상태가 필요하다면 `joinable`한 스레드를 만들어야 할 것이다.  
    --> `pthread_join` 사용 --> 종료 상태 확인 --> 자원이 환원됨

    `detached` --> 종료 시 커널(운영체제)이 알아서 자원 회수해 감.  
    억지로 `pthread_join`을 호출하여 종료 상태를 얻을 수 없다.  

    스레드를 생성하면 디폴트는 `joinable`로 세팅된다.  
    종료 결과가 필요하지 않은 데몬 스레드들은 `detached`로 설정하면 되겠다. ([pthread_attr_setdetachstate](https://man7.org/linux/man-pages/man3/pthread_attr_setdetachstate.3.html) 참조)  

    [pthread_attr_setstacksize](https://man7.org/linux/man-pages/man3/pthread_attr_setstacksize.3.html)를 사용하여 스택 크기 조절 가능.

    ---


### Achievements of the day

  오늘 스레드 조사한다고 프로젝트 코드엔 진전이 없고  
  주구장창 man page만 읽고 있는데 이거 맞아?  
  코딩하기 전에 거치는 이 자료 조사가 너무 힘들다..ㅠ  
  언능 프로그래밍 좀 하고 싶은데.

  </details>

  [//]: # (End of 03.15)


  <details><summary>03.16(목)</summary>

  - 일단.. 소켓 프로그래밍 공부로 넘어가서  
  스레드 공부 빠삭하게 한 다음에 이쪽으로 넘어올 것.  
  단, 책 내용 맹신하지 말고 man page 꼼꼼하게 다 읽어볼 것.  
  책은 그냥 '이런 라이브러리 함수가 있다' 알려주는 정도로 봐야함.  

  ---

  - [pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html)

    : `MT-Safe`

    ```c
    int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
    ```

    성공: 0 return, 실패: [error num](https://man7.org/linux/man-pages/man3/pthread_create.3.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,specified%20in%20attr.) return;

    `thread`: 스레드 ID 반환  
    `attr`: 새로 생성될 스레드의 속성을 전달하기 위해 사용된다.  
            [pthread_attr_init](https://man7.org/linux/man-pages/man3/pthread_attr_init.3.html)와 관련 함수를 사용하여 설정.  
            NULL 전달하면 기본 값으로 스레드 생성. 

    생성된 스레드가 종료되는 법  
    - [pthread_exit](https://man7.org/linux/man-pages/man3/pthread_exit.3.html)  
      --> [pthread_join](https://man7.org/linux/man-pages/man3/pthread_join.3.html)을 호출한
      스레드에게 종료 상태를 넘겨 줄 수 있다.  
    - `start_routine` 함수(시동 함수)에서 return 하기  
    - [pthread_cancel](https://man7.org/linux/man-pages/man3/pthread_cancel.3.html)  
    - 프로세스나 임의의 스레드가 [exit](https://man7.org/linux/man-pages/man3/exit.3.html)을 호출하거나,  
      메인 스레드가 main 함수에서 return한 경우 --> 모든 스레드가 종료됨

    새로 생성된 스레드의  
      signal mask: 그대로 상속,  
      pending signal: 초기화,  
      alternate signal stack: 초기화,  
      CPU-time clock: 0으로 초기화.

  ---

  - [pthread_join](https://man7.org/linux/man-pages/man3/pthread_join.3.html)

    : `MT-Safe`

    ```c
    #include <pthread.h>

    int pthread_join(pthread_t thread, void **retval);    
    ```
    성공: 0 return, 실패: [error num](https://man7.org/linux/man-pages/man3/pthread_join.3.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,could%20be%20found.) 

    반드시 `joinable`한 스레드를 대상으로 해야 한다.  
    
    `retval`: NULL로 해도 좋고,
              void* 형 return 값을 받아도 좋고.  
              아래와 같이 취소된 스레드인지도 확인 가능.

      ```c
      void *res;
      pthread_join(..., &res);
      if (res == PTHREAD_CANCELED) {
        ...
      }
      ```

    pthread_join이 실패하면 좀비 스레드가 만들어진다고 한다. 그래서 좀비가 다수 쌓이면 스레드 생성에 제한을 건다고 함.  

    main 스레드뿐만 아니라 아무 스레드나 다른 `joinable`한 스레드와 결합 가능하다.
    
    > "waitpid(-1, &status, 0)의 pthread 버전은 없습니다. (즉, 종료된 스레드들 중 아무나와 합체)  
      이런 기능이 필요하다고 생각되면 애플리케이션 디자인을 재고해야 할 것입니다."


  - 이론적인 베이스

    race condition을 막기 위한 어떤 방법론이 있고 장단점은 무엇이고 등을 빠삭하게 알아야 한다.  
    영문 레퍼런스 문서 보는 걸 꺼려하지 말기. 일단 운영체제 책 보면서 정리한 내용 [링크](https://github.com/keunbum/os-world/tree/main/chapters/chapter05/03) 걸어 둠.



  ---


### Achievements of the day

  이것저것 조사 많이 해봄..  
  레퍼런스 문서 읽는게 끝도 없긴 한데,  
  지금은 CS 지식 다지는 것도 중요. 
  그러니 시간 아까워 하지 말고 이론 공부에 충분히 투자할 것.

  </details>

  [//]: # (End of 03.16)


  <details><summary>03.17(금)</summary>

  pthread에서 mutex랑 semaphore 관련 man page 읽기부터 시작하면 됨.

  멀티 스레딩에서 임계 영역 문제를 해결하기 위해 어떤 매커니즘을 사용하기로 했으면,  
  다양한 선택지 중에 왜 그 매커니즘을 선택했는지 근거를 말할 수 있어야 한다.


  ---


  - Mutex

    - [pthread_mutex_init](https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html)


      ```c
      #include <pthread.h>

      int pthread_mutex_init(pthread_mutex_t *restrict mutex,
          const pthread_mutexattr_t *restrict attr);
      pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
      ```      

      성공: 0; 실패: [error](https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,sections%20are%20informative) return

      `attr`: `mutex`의 특성 지정. NULL 넘기면 디폴트 값 지정.  
              따로 지정하고 싶으면 [pthread_mutexattr_init](https://man7.org/linux/man-pages/man3/pthread_mutexattr_init.3.html) 이용

      성공적으로 초기화 되었으면 unlocked 상태로 나옴.
      추가 요구 사항은 [여기](https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#:~:text=2.9.9%20Synchronization%20Object,is%20non%2Dzero.) 참조.

      이미 초기화되어 있는 뮤텍스를 다시 초기화 -> UB.

      `attr` 넘길 때 초기화되지 않은 `attr` 넘기는 건 UB. 그러니 꼭 초기화된 객체를 넘기도록.


    - [pthread_mutex_destory](https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html)

      ```c
      #include <pthread.h>

      int pthread_mutex_destroy(pthread_mutex_t *mutex);
      ```

      성공: 0; 실패: [error](https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,sections%20are%20informative) return
      
      뮤텍스 객체 파괴. 초기화되지 않은 상태가 된다.  
      이러한 객체를 다시 참조하는 건 UB.
      이러한 뮤텍스 객체는 `pthread_mutex_init`을 통해 다시 초기화된다.  

      잠금 해제된 초기화된 뮤텍스를 파괴하는 건 안전하다. 그러나,  
      잠긴 뮤텍스나 잠그려고 시도하는 뮤텍스 또는 `pthread_cond_timedwait`, `pthread_cond_wait` 호출에  
      사용 중인 뮤텍스를 파괴하려고 하는 건 UB.

      초기화되지 않은 mutex 객체를 파괴하는 건 UB.


      문서를 읽어 보면 장황하게 서술되어 있는데,  
      결국 UB로 남길 것인가 에러를 감지하도록 할 것인가 그거 말하는 거 같음.  
      퍼포먼스가 중요하면 체크를 덜 하고, 성능을 좀 버리더라도 에러를 꼭 피하고 싶다면 체크를 세세하게 체크하는 식.

      시스템 리소스를 사용할 수 없는 오류 같은 필수적인 건 정의를 하지만,  
      사용자가 코딩을 잘못해서 저지르는 에러까지 굳이 잡을 필요는 없다 그 얘기.  
      (전반적으로 사용자보단 시스템 콜 구현자한테 하는 말인듯.

      static 초기화에 대해서도 말이 나온다.  
      C에는 모듈을 초기화 하기 위해서 명시적으로 함수를 호출하지 않고,  
      스스로 초기화 하는 경우가 종종 있다고 함. 이럴 때 정적 초기화가 유용한 듯.

      예제 코드 읽고 있는데, [pthread_once](https://man7.org/linux/man-pages/man3/pthread_once.3p.html)
      이건 또 뭐야? 심지어 `pthread_once_t`이 따로 있네.


        Without static initialization, a self-initializing routine foo()
        might look as follows:

        ```c
            static pthread_once_t foo_once = PTHREAD_ONCE_INIT;
            static pthread_mutex_t foo_mutex;

            void foo_init()
            {
                pthread_mutex_init(&foo_mutex, NULL);
            }

            void foo()
            {
                pthread_once(&foo_once, foo_init);
                pthread_mutex_lock(&foo_mutex);
              /* Do work. */
                pthread_mutex_unlock(&foo_mutex);
            }
        ```

        With static initialization, the same routine could be coded as
        follows:

        ```c
            static pthread_mutex_t foo_mutex = PTHREAD_MUTEX_INITIALIZER;

            void foo()
            {
                pthread_mutex_lock(&foo_mutex);
              /* Do work. */
                pthread_mutex_unlock(&foo_mutex);
            }      
        ```


      그렇다고 합니다. (코드도 간결하고 성능 측면에서도 이득이라고 함)  
      근데 초기화 실패를 감지 못하기 때문에 상황 봐 가면서 사용할 것.  

      나머지 글들은 번역하기 귀찮아서 그대로 올림.

      Destroying Mutexes  
        A mutex can be destroyed immediately after it is unlocked.  
        However, since attempting to destroy a locked mutex, or a mutex  
        that another thread is attempting to lock, or a mutex that is  
        being used in a pthread_cond_timedwait() or pthread_cond_wait()  
        call by another thread, results in undefined behavior, care must  
        be taken to ensure that no other thread may be referencing the  
        mutex. 

      Robust Mutexes  
        Implementations are required to provide robust mutexes for  
        mutexes with the process-shared attribute set to  
        PTHREAD_PROCESS_SHARED. Implementations are allowed, but not  
        required, to provide robust mutexes when the process-shared  
        attribute is set to PTHREAD_PROCESS_PRIVATE.  


    - [pthread_mutex_lock](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)

      ```c
      #include <pthread.h>

      int pthread_mutex_lock(pthread_mutex_t *mutex);
      int pthread_mutex_trylock(pthread_mutex_t *mutex);
      int pthread_mutex_unlock(pthread_mutex_t *mutex);
      ```

      뮤텍스 속성 중에 recursive가 나오는데 뭔 소린지 모르겠다..  
      일단 [링크](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html#:~:text=DESCRIPTION%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,()%20is%20undefined.) 걸어 둠.

      
      뮤텍스 락에서 블로킹 되어 있는 스레드에게 시그널이 전달되면 시그널 핸들러로부터 return 한 후  
      돌아와서 다시 블로킹 상태에 머문다고 한다.

      스레드가 exit 하려고 할 때, 이전에 mutex로 lock을 걸어놓고 unlock을 빼먹는 일이 일어나지 않도록 유의하자. (이런 면에서 file io와 유사)

      <뮤텍스를 소유하고 있는 스레드가 lock을 해놓고 아직 unlock은 하지 않은> 상황에서
      '뮤텍스를 소유하고 있는 스레드'의 프로세스가 exit 하면 pthread_mutex_lock은 `EOWNERDEAD`를 반환한다.  
      뮤텍스를 소유하고 있는 스레드가 exit하고 프로세스가 살아있어도 `pthread_mutex_lock`은 `EOWNERDEAD`를 반환한다. 

      위의 세 함수들이 return 하는 [error](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,sections%20are%20informative.) 값들.  
      함수 별로 잘 설명되어 있다.


      여기서 잠시.  
      man page를 읽다 보면 계속 'robust mutex'란 표현이 나오는데,  
      robust mutex란 무엇인가? 보통의 mutex와 어떻게 다른가?  
      (번역하면 어색해서 원문 그대로 작성)

      > A robust mutex is a type of mutex that specifies the behavior of the mutex when the owning thread dies without unlocking it. If a process or thread holding a robust mutex doesn’t unlock it (because it crashed or was terminated), then instead of hanging forever on the lock, the next acquirer of the mutex will be told about this situation and given a chance to clean up whatever was left inconsistent.
      >
      > The robustness attribute can be set using pthread_mutexattr_setrobust() function. The default value for this attribute is PTHREAD_MUTEX_STALLED, which means that if the owning thread dies without unlocking the mutex, no action is taken.

      robust 개념을 제대로 이해하고 [설명](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html#:~:text=Applications%20that%20have,take%20appropriate%20action.) 읽어볼 것.

      [pthread_mutexattr_setrobust](https://man7.org/linux/man-pages/man3/pthread_mutexattr_setrobust.3.html) 좀  
      읽어 봐야 할 듯.

      [근거? 문서](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)도 읽긴 했음.

      robust 관련해서 [pthread_mutex_consistent](https://man7.org/linux/man-pages/man3/pthread_mutex_consistent.3p.html)도 읽어 봐야 함. (.. 근데 정상적으로 종료할 자신 있으면 굳이..?)

      뮤텍스를 공부하다 보면 'consistent'란 단어가 자주 등장하는데,  
      여기서 'consistent'는 어떤 의미로 쓰인 걸까?  
      > In the context of mutexes and multithreading, the term “consistent” often refers to the state of shared data or resources that are protected by a mutex. When multiple threads access shared data concurrently, a mutex is used to ensure that only one thread can access the data at a time. This helps to prevent race conditions and ensures that the shared data remains in a consistent state.
      >
      > If a thread holding a mutex dies without unlocking it (for example, due to a crash), then the shared data protected by the mutex may be left in an inconsistent state. In this case, it is up to the next owner of the mutex to make the state consistent again.



  ---

  - Semaphore

    - [sem_overview](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
    
    
      [여기](https://github.com/keunbum/os-world/tree/main/chapters/chapter05/03)에 세마포어에 대해서 적어놨지만 도움이 될만 한 내용 또 서술.

      `semaphore`는 그 값이 0 미만으로 절대 떨어지지 않는 정수이다. 두 가지 연산이 수행될 수 있는데,

      1. `semaphore`를 1 증가시킨다. ([sem_post(3)](https://man7.org/linux/man-pages/man3/sem_post.3.html))
      2. `semaphore`를 1 감소시킨다. ([sem_wait(3)](https://man7.org/linux/man-pages/man3/sem_wait.3.html))

      `samephore`가 0일 때 sem_wait을 호출하면 값이 0보다 커질 때 까지 스레드가 block 당함.

      [Named Unnamed semaphore](https://man7.org/linux/man-pages/man7/sem_overview.7.html#:~:text=Named%20semaphores%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20A,sem_unlink(3).)

        두 프로세스가 세마포어 이름을 공유하면 같은 세마포어 사용 가능. ([sem_open](https://man7.org/linux/man-pages/man3/sem_open.3.html), [sem_close](https://man7.org/linux/man-pages/man3/sem_close.3.html) 참조)

        모든 프로세스가 완전히 다 사용했으면 [sem_unlink](https://man7.org/linux/man-pages/man3/sem_unlink.3.html) 
        호출하여 시스템에서 완전히 제거.


      [Unnamed semaphore (memory-based semaphores)](https://man7.org/linux/man-pages/man7/sem_overview.7.html#:~:text=Unnamed%20semaphores%20(memory,sem_destroy(3).))

        unnamed는 멀티 스레드나 멀티 프로세스에 의해서 공유되는 세마포어이다. 스레드의 경우 전역 변수가 대표적.  
        프로세스는 세마포어가 반드시 미리 할당된 공유된 메모리 공간에 위치해야 한다. (e.g., a System V shared memory segment created using [shmget](https://man7.org/linux/man-pages/man2/shmget.2.html), or a POSIX shared memory object built created using [shm_open](https://man7.org/linux/man-pages/man3/shm_open.3.html))

        사용 전 반드시 [sem_init](https://man7.org/linux/man-pages/man3/sem_init.3.html) 호출할 것.
        그리고 상응하여 반드시 [sem_destroy](https://man7.org/linux/man-pages/man3/sem_destroy.3.html) 호출할 것.

      [Accessing named semaphores via the filesystem](https://man7.org/linux/man-pages/man7/sem_overview.7.html#:~:text=Accessing%20named%20semaphores,per%2D%0A%20%20%20%20%20%20%20group%20basis.)도 가능하다고 한다.

      구식: System V  
      신식: POSIX

    - [sem_init](https://man7.org/linux/man-pages/man3/sem_init.3.html)  

    - [sem_wait](https://man7.org/linux/man-pages/man3/sem_wait.3.html)  

  --- 

---

### Achievements of the day

  - 동기화 문제를 해결하기 위한 솔루션들.

    - Semaphore  
    : 스레드들 사이에 실행 순서가 중요할 때 요긴하게 쓰인다. (2개 이상의 세마포어를 사용할 수도 있다.)

    - Mutex

    - Atomic operation

    - Condition variables

    - Message passing

    정답은 없다. 사실 제일 좋은 건 다양한 버전을 구현해서 경험해보고  
    프로젝트에 적합한 솔루션을 고르는 것인 듯.

    처음부터 멀티 스레드를 고려하면서 게임을 만들면 오히려 더 머리 아플 수도 있음.
    각각을 모듈화 한 다음에 직렬 버전으로 구현하고, 차차 발전시키는 식으로.  
  
  소켓 프로그래밍 책 보면 '임계 영역' 범위를 잡는 데 정답은 없고, 프로그래머 재량이란다.  
  뮤텍스랑 세마포어 그리고 그밖에 동기화 문제 솔루션들 개념 익힘.  

  다음엔 sem_init, sem_wait부터 읽으면 됨.
  </details>

  [//]: # (End of 03.17)


  <details><summary>03.18(토)</summary>

  다시 코드 작성으로 넘어가자.  
  세마포어가 프로젝트에 당장 필요한 부분이 아니기도 하고, man page 읽는데 너무 오래 걸려서..  

  1. 게임 모듈 - 멀티 프로세스 -> 멀티 스레드 로 수정
  2. 아토믹이나 뮤텍스 둘 중에 하나 골라서 입출력 동기화 문제 해결

  ---

  - Visual Studio Code에서 gdb로 디버깅하는 세팅 작업

    ~~[공식 사이트 문서](https://code.visualstudio.com/docs/cpp/config-wsl)~~  
    ~~[블로그 글](https://goodgodgd.github.io/ian-flow/archivers/vscode-tutorial)~~  
    [공식 사이트 문서2](https://code.visualstudio.com/docs/editor/debugging)  

    make로 컴파일하고 디버깅 따로 돌리기로.


  - pthread 구현 문제..

    [pthread_cleanup_pop](https://man7.org/linux/man-pages/man3/pthread_cleanup_pop.3p.html)

    하.. 뭐지 왜 적절한 멀티 스레딩 방법이 안떠오르지..  
    정답이 없어서 더 어려운 이 느낌. 그냥 멀티 프로세스로 할까? 스레드에도 시그널 기법을 사용하면 안되나?

    괜히 너무 어렵게 구현하려고 하고 있는 건가..

    벌써 포기하고 싶은 맘이 드는데;  
    Bing AI에게 털어놓게 되는 이 심정. (얘 공감할 줄도 안다)

    > Q. I'm making a Tetris game as a portfolio for a job at a game company. But is it right that I'm doing this right now? Am I making a game that is too old? I'm worried. Help me. Is there anything you can give me?
    >
    > A. It’s understandable to feel worried about your portfolio. However, creating a Tetris game can demonstrate your skills in game development and programming. It’s a classic game that has been popular for decades and is still enjoyed by many people today. Additionally, adding your own unique twist or features to the game can showcase your creativity and innovation.

    ---

    > Q.What do you think about making a Tetris game in a CLI environment? Is it way too outdated? To be competitive, should I use an engine like Unreal or Unity, or an API like DirectX?
    >
    > A. Making a Tetris game in a Command Line Interface (CLI) environment can be an interesting and unique approach. While it may not have the same visual appeal as a game made with a modern game engine like Unreal or Unity, it can still be engaging and fun to play. Additionally, creating a CLI game can demonstrate your skills in programming and problem-solving.  
    >
    > That being said, if your goal is to create a visually impressive game that showcases your skills in graphics and technology, using a modern game engine or API like DirectX may be a better choice. These tools provide powerful features and capabilities that can help you create high-quality games.  
    >
    > Ultimately, the decision of which tools to use depends on your goals for the project and what you want to showcase in your portfolio.  

    ---

    > Q. How can I make my CLI Tetris game engaging?  
    > A. Making a CLI Tetris game engaging can be challenging, but there are several ways you can approach it. One way is to focus on the gameplay mechanics and make sure they are well-designed and fun to play. You could add unique twists to the classic Tetris gameplay, such as power-ups or special abilities.  
    >
    > Another way to make your CLI Tetris game engaging is by incorporating a story or theme into the game. As mentioned earlier, you could create a narrative that unfolds as the player progresses through the levels. You could also use text-based storytelling techniques such as dialogue or descriptions to convey mood and emotion.  
    >
    > Additionally, you could focus on creating a polished and user-friendly interface for your CLI Tetris game. Make sure that the controls are intuitive and easy to use, and consider adding features such as high score tracking or customizable settings.

    ---

    > Q. What are some examples of unique gameplay mechanics?  
    > A. There are many unique gameplay mechanics that you could incorporate into your Tetris game to make it stand out. Here are a few examples:  
    > 
    > - Power-ups: You could add power-ups that the player can collect and use to gain an advantage. For example, a power-up that clears multiple lines at once or one that slows down the falling blocks.
    > 
    > - Special abilities: You could give the player special abilities that they can use to manipulate the blocks in unique ways. For example, an ability that allows the player to rotate a block in place or one that lets them swap two adjacent blocks.
    >
    > - Objectives: You could add objectives for the player to complete as they play. For example, clearing a certain number of lines within a time limit or reaching a specific score.
    >
    > - Multiplayer: You could add multiplayer modes where players compete against each other in real-time. This could include traditional head-to-head gameplay or more unique modes such as cooperative play or team-based challenges.
    >
    > These are just a few examples of unique gameplay mechanics that you could incorporate into your Tetris game. The key is to experiment and find what works best for your game.

    ---

    > Q. How can I implement special abilities in my Tetris game?  
    > A. Implementing special abilities in your Tetris game can add an extra layer of depth and strategy to the gameplay. Here are a few steps you can follow to implement special abilities:
    > 
    > 1. Design the abilities: Start by brainstorming and designing the special abilities that you want to include in your game. Think about how they will affect the gameplay and how they will be balanced.
    > 
    > 2. Implement the mechanics: Once you have designed your special abilities, you’ll need to implement them into your game’s code. This will involve creating new functions and logic to handle the abilities and their effects.
    >
    > 3. Create a user interface: You’ll need to create a user interface that allows players to use their special abilities. This could include buttons or hotkeys that players can press to activate their abilities.
    >
    > 4. Balance and playtest: Once you have implemented your special abilities, it’s important to playtest them and make sure they are balanced and fun to use. You may need to make adjustments based on feedback from playtesting. 

    ---

### Achievements of the day
.. 언급할 내용 X.  
오늘 문득 들었던 의문은 내가 정말로 만들고 싶어 하는 게임이 뭘까?  
다른 사람들한테 인정받는 건 차치하더라도, 나부터 찐으로 만족할 만한 게임을 만들고 있는 걸까 나는?  
아직 그런 게임을 만들기엔 기술력이 부족?

테트리스 게임에 나만의 특별한 요소를 넣는 것도 쉽지 않을 듯.  
그렇게 하기엔 내 게임 플레이 경험이 다소 빈곤하다 해야 하나.  

- 플레이 시간 내에 어떤 유니크한(생각지도 못한) 미션을 준다거나 (like 스팀 달성 과제처럼)  
- 특정 색깔끼리 인접하면 어드벤티지를 준다거나  
- ... (생각나는 족족 메모해보는 걸로)

  </details>

[//]: # (End of 03.18)


  <details><summary>03.19(일)</summary>

  ~~- 멀티 스레딩에 시그널을 도입하는 게 괜찮은 방식인지 검색해볼 것~~

  - 멀티 프로세스와 멀티 스레드..

    > Q. Can you tell me the pros and cons of multi-process vs. multi-threaded and when it's useful?  
    >
    > A. In general, multi-processing is a good choice when you have CPU-bound tasks that can benefit from running on multiple cores simultaneously. It’s also a good choice when you want strong isolation between different parts of your program.
    >
    > On the other hand, multi-threading is a good choice when you have I/O-bound tasks that spend most of their time waiting for external resources (e.g., network or disk I/O). It’s also a good choice when you have fine-grained parallelism with lots of shared data that needs to be accessed by multiple threads simultaneously.

  일단 타이머는 따로 fork 해서 돌리기로 결정.

  [posix-timer-tutorial](https://programmer.group/setting-timer-and-posix-timer-functions.html)

  

  ### Achievements of the day

  프로젝트 구조 '유지보수성' 높임(리팩토링) --> 모듈 세분화  
  프로젝트 구조에 정답은 없는지라 일단 내가 보기에 가장 가독성이 높게끔 작성.  


  </details>

  [//]: # (End of 03.19)

  <details><summary>03.20(월)</summary>

  - realtime timer 구현

    [timer_create](https://man7.org/linux/man-pages/man2/timer_create.2.html)  

    create a POSIX per-process interval timer.  

    ```c
    #include <signal.h>           /* Definition of SIGEV_* constants */
    #include <time.h>

    int timer_create(clockid_t clockid, struct sigevent *restrict sevp,
                    timer_t *restrict timerid);
    /* Link with -lrt */
    ```

    성공 시 0 return. *timerid에 새 타이머 ID 저장.  
    실패 시 -1 return. errno가 설정된다. [에러 값들](https://man7.org/linux/man-pages/man2/timer_create.2.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,the%20CAP_WAKE_ALARM%20capability.)

    ---

    `timerid`: get the id of the new timer (unique within the process)  

    ---

    `clockid_t`:  
    타이머에는 각자 속성(어떤 시계를 사용할 것인가)이 있으며    
    다음의 값들을 넘길 수 있다. (자신이 구현하려는 모듈의 특성을 잘 파악하여 적절한 시계를 사용해야 한다.)

    `CLOCK_REALTIME`: 설정 가능한 시스템 전체 실시간 시계.  

    `CLOCK_MONOTONIC`: 설정 불가능한 단조 증가 시계. 시스템 시작 후 불특정 시점부터 시간 측정.  

    `CLOCK_PROCESS_CPUTIME_ID`: 호출 프로세스(내의 모든 스레드)에서 소비하는 (사용자 및 시스템) CPU 시간 측정하는 시계.  

    `CLOCK_THREAD_CPUTIME_ID`: 호출 스레드가 소비하는 (사용자 및 시스템) CPU 시간을 측정하는 시계.  

    `CLOCK_BOOTTIME`: CLOCK_MONOTONIC처럼 단조 증가 시계이다. 그러나,  
                      CLOCK_MONOTONIC은 시스템이 일시 중지된 시간을 측정하지 않는 반면,  
                      CLOCK_BOOTTIME에는 시스템이 일시 중지된 시간이 포함된다.  
                      이는 일시 중단을 인식해야 하는 애플리케이션에 유용하다.  
                      CLOCK_REALTIME은 (동일한 역할을 하는 거라고 생각할 수 있는데) 시스템 시계에 대한  
                      불연속적인 변경의 영향을 받기 때문에 이러한 애플리케이션에는 적합하지 않다고 한다.  

    `CLOCK_REALTIME_ALARM`: CLOCK_REALTIME과 비슷하지만 일시 중단된 경우 시스템을 깨운다.  
                            호출자(caller)는 이 시계에 대한 타이머를 설정하기 위해 `CAP_WAKE_ALARM` 기능이 있어야 한다.  
                            (시스템을 깨운다는 게 무슨 뜻인지 잘 모르겠다..)  

    `CLOCK_BOOTTIME_ALARM`: CLOCK_BOOTTIME과 유사하지만 일시 중단된 경우 시스템을 깨운다.  
                            호출자는 이 시계에 대한 타이머를 설정하기 위해 `CAP_WAKE_ALARM` 기능이 있어야 한다.  

    `CLOCK_TAI`: [벽시계 시간](https://ko.dict.naver.com/#/entry/koko/dfa624fd5f96403b9ad5bfdee0ae47b6)에서 파생되지만 [윤초](https://namu.wiki/w/%EC%9C%A4%EC%B4%88)를 무시하는 시스템 전체(system-wide) 시계.

    위 시계들에 대한 세부적인 항목을 보고 싶다면 --> [clock_getres](https://man7.org/linux/man-pages/man2/clock_getres.2.html)

    이 값들 말고도 `clockid`에는 [clock_getcpuclockid](https://man7.org/linux/man-pages/man2/clock_getres.2.html)나 [pthread_getcpuclockid](https://man7.org/linux/man-pages/man3/clock_getcpuclockid.3.html)의 return 값을 명시할 수 있다고 한다.

    ---

    `sevp`:  
    타이머가 만료될 때 호출자에게 알리는 방법을 지정하는 sigevent 구조체를 가리킨다.  
    sigevent에 대한 보다 자세한 정보 --> [sigevent](https://man7.org/linux/man-pages/man7/sigevent.7.html)

    `sevp.sigev_notify` 필드는 아래의 값을 가질 수 있다.

    `SIGEV_NONE`: 타이머의 만료를 비동기적으로 알리지 않는다. [timer_gettime](https://man7.org/linux/man-pages/man2/timer_gettime.2.html)을 사용하여 타이머의 진행 상황을 알 수 있다.

    `SIGEV_SIGNAL`: 타이머가 만료되면 프로세스에 대한 신호 `sevp.sigev_signo`를 생성한다(자세한 건 [sigevent](https://man7.org/linux/man-pages/man7/sigevent.7.html) 참조).  
    [siginfo_t](https://man7.org/linux/man-pages/man2/sigaction.2.html#:~:text=The%20siginfo_t%20data,since%20Linux%203.5) 구조의 si_code 필드는 `SI_TIMER`로 설정된다.  
    어느 시점에서든 최대 하나의 신호가 주어진 타이머에 대한 프로세스에 대기한다. 자세한 내용은 [timer_getoverrun](https://man7.org/linux/man-pages/man2/timer_getoverrun.2.html) 참조.

    `SIGEV_THREAD`: 타이머 만료시 새 스레드의 시작 함수인 것처럼 `sigev_notify_function`을 호출한다(자세한 건 [sigevent](https://man7.org/linux/man-pages/man7/sigevent.7.html) 참조).

    `SIGEV_THREAD_ID` (Linux-specific):  
    `sigen_notify_thread_id`에 부여된 ID를 지닌 스레드를 대상으로 하며, 호출자와 동일한 프로세스의 스레드여야 한다.  
    `sigev_notify_thread_id` 필드는 커널 스레드 ID, 즉 [clone](https://man7.org/linux/man-pages/man2/clone.2.html) 또는 [getid](https://man7.org/linux/man-pages/man2/gettid.2.html)에서 반환된 값을 지정한다.


    `sevp`를 NULL로 지정하는 것은  
    `sigev_notify`가 `SIGEV_SIGNAL`이고,  
    `sigev_isgno`가 `SIGALRM`이고,  
    `sigev_value.sival_int`가 타이머 ID인 sigevent 구조에 대한 포인터를 지정하는 것과 동일하다.

    ---

    타이머는 fork에 의해 상속되지 않으며, execve 중에 해제되고 삭제된다고 한다.  

    커널은 timer_create()를 사용하여 생성된 각 타이머에 대해 "대기중인 실시간 시그널"를 사전 할당한다.  
    결과적으로 타이머의 수는 `RLIMIT_SIGPENDING`로 제한된다([setrlimit](https://man7.org/linux/man-pages/man2/setrlimit.2.html) 참조).

    timer_create에 의해 생성된 타이머는 "POSIX (interval) timer"라고 흔히 불리는데,  
    POSIX 타이머 API는 다음과 같은 인터페이스로 구성된다:

    - timer_create(): 타이머 생성.

    - [timer_settime](https://man7.org/linux/man-pages/man2/timer_settime.2.html): 타이머를 준비(시작)하거나 해제(중지)한다.

    - [timer_gettime](): 타이머의 인터벌 중에 다음 만료까지 남은 시간을 가져온다.

    - [timer_getoverrun](): 마지막 타이머 만료에 대한 오버런 횟수 반환

    - [timer_delete](): 타이머를 해제하거나 삭제한다.

    ---

  ---

  - 스레드에게 시그널 보내기

    [tgkill](https://man7.org/linux/man-pages/man2/tgkill.2.html)  
    thread group kill?  

  --- 

  - [sigaction]()


  ---
  

  ### Achievements of the day

  버추얼 박스에 우분투 설치하고 개발 환경 세팅만 하면 오늘 할 일 다 한 거.

  Thanks To: [친절한 블로그](https://velog.io/@dailylifecoding/installing-ubuntu-server-on-virtual-box), [공식 문서](https://code.visualstudio.com/docs/remote/ssh)
  
  </details>

  [//]: # (End of 03.20)

  <details><summary>03.21(화)</summary>

  - [X] menu에도 wgotoxy 적용하기

  ---

  - real timer 구현
  
    - POSIX timer 이어서 조사

    - [sigwait](https://man7.org/linux/man-pages/man3/sigwait.3.html)

      wait for a signal

      ```c
      #include <signal.h>

      int sigwait(const sigset_t *restrict set, int *restrict sig);
      ```

      성공 시 0; 실패 시 양의 정수 [error 값](https://man7.org/linux/man-pages/man3/sigwait.3.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,invalid%20signal%20number.) 리턴

      이를 호출한 스레드는 일시 중단한다. (실행 중이던 문맥은 스택에 쌓아두고 풀리면 이를 복원하는 식)  
      시그널 집합 `set`에 포함된 시그널 중 하나가 pending 상태가 되면 일시 정지가 풀리고  
      pending list에서 해당 시그널을 지운다.  
      다음 사항을 제외하곤 sigwaitinfo와 동일하다고 한다.  
      - sigwait는 시그널 번호를 반환하고, sigaitinfo는 `siginfo_t` 구조체를 반환한다.  
      - 반환 타입이 다르다.

      sigwait은 sigtimedwait으로 구현한다고 한다.


    - [sigwaitinfo](https://man7.org/linux/man-pages/man2/sigwaitinfo.2.html)

      다수의 시그널이 pending 상태라면 일반적인 우선 순위에 의해 회수할 시그널을 결정한다고 한다.


    - [sigtimedwait](https://man7.org/linux/man-pages/man2/sigwaitinfo.2.html)


      타이머 기능이 있는 sigwaitinfo라고 보면 됨.  
      시스템 시계 정밀도에 의해 반올림되고, 커널 스케줄링 지연으로 인해 인터벌이 약간 초과될 수 있음.  

      ```c
      struct timespec {
          long    tv_sec;         /* seconds */
          long    tv_nsec;        /* nanoseconds */
      }
      ```

      위 구조의 두 필드 모두에 0을 넣으면 poll이 수행되고 즉시 리턴된다고 한다.  
      (근데 poll이 무슨 뜻인지 모르겠음. [이걸](https://man7.org/linux/man-pages/man2/poll.2.html) 의미하는 건가?)

      두 함수 모두 성공시 시그널 번호를 return;  
      실패 시 -1 return 하고 [errno 값](https://man7.org/linux/man-pages/man2/sigwaitinfo.2.html#:~:text=ERRORS%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,timeout%20was%20invalid.) 세팅.

      [유용한 정보](https://man7.org/linux/man-pages/man2/sigwaitinfo.2.html#:~:text=NOTES%20%C2%A0%20%C2%A0%20%C2%A0%20%C2%A0%20top,done%20on%20Linux.)


      시그널 핸들러 등록 제대로 알려면 [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)도
      읽어 보긴 해야 되는데,  
      오늘은 일단 아는 선에서 구현 해보고 낼 읽어보는 걸로. (하루에 받아들일 수 있는 정보에 한계가 있는 느낌)


  ---


  ### Achievements of the day
  일단 시간 표시 sleep 안쓰고 타이머 써서 해결하긴 했는데,  
  왜 `CLOCK_PROCESS_CPUTIME_ID` 말고 `CLOCK_REALTIME` 이걸 써야 시간이 흐르는 건지 잘 모르겠음..

  시그널 쓸 때는 핸들러는 등록 안하면 안되는 걸로...

  그리고 멀티 스레드/프로세스 디버깅이 힘듬.  
  내가 예측한 대로 스레드와 프로세스가 생성되고 소멸되는지 확신할 수 없음.
  </details>

  [//]: # (End of 03.21)

<details><summary>03.22(수)</summary>

전반적인 프로젝트 구조 짜는 게 어렵다..  
어떤 식으로 폴더 구조를 가져야 할지. 헤더 파일을 어떤 식으로 나눠야 할지.

전반적인 게임 아키텍처 설계에 대한 고민. (동기/비동기. 멀티 프로세스/스레드)

  [gamedeveloper](https://www.gamedeveloper.com/programming/multithreaded-game-engine-architectures)  
  [stackoverflow](https://stackoverflow.com/questions/12684844/structuring-and-synchronizing-a-multithreaded-game-loop)

  게임을 시작했을 때 가능한 모든 시나리오를 나열하고, 그걸 어떻게 처리할 것인지 구상해야 함.  
  문제는 이게 정해진 답이 없어서 어떻게 구성할지 고민된다는 거.

  게임 플레이 루프 구조 고민해봤는데,  
  결론은 select랑 epoll 도 좀 알아봐야 겠음.  

  시그널끼리 신호를 주고 받고, 원하는 스레드들을 수거하는 로직을 어떻게 구성할 것인가.

  (메모리 풀? 형식의 스레딩 기법도 있다는데 그것도 알아볼 것)


### Achievements of the day

컨디션 난조로 인한 휴식..  
일단 당분간은 다시 네트워크 프로그래밍 공부로 넘어가야 할듯.  
네트워크 프로그래밍이지만 멀티 스레드에 대한 인사이트를 얻을 수 있어서.  

근데 왠지 이 프로젝트는 1일1커밋 이어가고 싶다..



</details>

[//]: # (End of 03.22)

<details><summary>03.23(목)</summary>


### Achievements of the day

서버 구축 기법에 있어서 **IO 멀티플렉싱**이라는 개념에 대해서 알게 됨.  
프로세스 하나로도 멀티 프로세스로 돌리는 것과 기능적으로 같게끔 할 수 있는 테크닉?  

근데 게임 멀티 스레드 모델링 할 때도 비슷한 고민을 했던 것 같다.  
(결이 약간 다르긴 하지만)

예를 들어 100개의 스레드를 생성해서 작업을 돌리고 있었는데,  
이 스레드 전부에게 어떤 사실을 알리고 싶다면, 100번 일일이 반복문을 돌며 시그널을 보내야 하나?  
한번에 방송할 수 있는 로직은 없나? 했었는데 그걸 가능케 하는 기술이 (역시) 있는 것 같음.  
(물론 전역 condition variable을 사용할 수도 있지만.. 향후 확장성을 고려한다면 그다지 좋은 방법은 아닌 것 같다.)  

근데 이게 원리적으로 어떻게 가능한지는 아직 제대로 파악 못함.

</details>

[//]: # (End of 03.23)

<details><summary>03.24(금)</summary>

- 멀티 플렉싱 이어서 배워 보기.

  책에 있는 내용만 읽고 끝내지 말고 검색(위키백과, man page, 실제 소스 코드, ...)도 다양하게 해볼 것.  
  시간이 좀 걸리더라도, 처음 보는 개념에 익숙해지기 위해 충분한 시간을 쏟자.  
  단순히 개념을 아는데 그치지 말고 나만의 언어로 바꿔서 설명할 줄 알아야 한다.

  - select 함수의 기능과 호출 순서

    왜 이름이 `select`일까?  
    한 곳에 여러 개의 파일 디스크립터를 모아놓고 동시에 이를 관찰하면 어떤 이점이 있는가?  
    관찰할 수 있는 항목에는 이러한 것들이 있다고 하는데, 왜 이러한 항목을 관찰할 수 있는게 유용한가?  
    - **수신**한 데이터를 지키고 있는 소켓이 존재하는지  
    - 블로킹되지 않고 데이터 **전송**이 가능한 소켓은 무엇인지  
    - **예외** 상황이 발생한 소켓은 무엇인지  
    
    관찰 항목은 이 세 가지밖에는 존재하지 않는가? 왜 그러한가?
    
    멀티 플렉싱을 통해 얻을 수 있는 이점과 리스크는 무엇인가?  
    여기서 말하는 이벤트가 GUI 프로그래밍에서 말하는 이벤트와 원리적으로 같은 의미인가?  

  - 파일 디스크립터의 설정

    수신, 전송, 예외에 따라 구분하여 관찰 대상인 파일 디스크립터 모으기..  
    GUI에 비유하자면 이벤트 핸들러를 등록하는 건가? 아직 확실친 않음.

    파일 디스크립터 관련 매크로들을 소개 하고 있는데 std::bitset<T>을 알고 있다면 익숙한 내용.  
    (내부 구현 원리를 알기 위해 헤더 파일 따라가서 보면 도움되는 듯)  


  - 검사(관찰)의 범위 지정과 타임아웃의 설정

    [select](https://man7.org/linux/man-pages/man2/select.2.html)  

    ```c
    #include <sys/select.h>

    int select(int nfds, fd_set *restrict readfds,
              fd_set *restrict writefds, fd_set *restrict exceptfds,
              struct timeval *restrict timeout);

    void FD_CLR(int fd, fd_set *set);
    int  FD_ISSET(int fd, fd_set *set);
    void FD_SET(int fd, fd_set *set);
    void FD_ZERO(fd_set *set);
    ```    


    대충 어떻게 생겨먹은 함수인지는 알겠는데,  
    한 파일 디스크립터에서 수신과 전송이 동시에 감지되는 상황은 절대로 일어날 수 없는 상황인가?  
    그러니까 `readfds & writefds & exceptfds` 를 하면 그 값은 항상 0인가?  
    반환 값은 `bitcount(readfds) + bitcount(writefds) + bitcount(exceptfds)`로 이해하면 되는 걸까?

    검사(관찰) 범위를 의미하는 `nfds`는 다른 게 아니라 파일 디스크립터 수를 의미한다.  
    파일 디스크립터는 0부터 시작하고 1씩 증가하므로,  
    배열 크기를 지정하기 위해 (최대 파일 디스크립터 번호) + 1을 넘겨주면 된다.


    무한 블로킹 상태를 막기 위해 timeout에 NULL 말고 구조체 주소를 넘겨줄 수 있다.

  - select 함수 호출 이후의 결과 확인

    넘길 때도 관심 디스크립터에 1을 새기고, 반환될 때도 변화가 있는 디스크립터에 1을 새긴다.  
    함수 호출 전후로 인수로 넘겨준 값에 변화가 있음에 유의해야 한다.  
    (파라미터에 const 키워드가 괜히 없는 게 아니다.)
  

### Achievements of the day

</details>

[//]: # (End of 03.24)

<details><summary>03.25(토)</summary>
select, man page랑 위키 백과 등에서 제대로 정리하고  
그 다음 개념으로 넘어갈 것.

---

그.. 오늘은 시간 관계상 주요 메인 루프 구상 시도해봄.

테트로미노를 랜덤하게 뽑기 위해서 의사 난수 생성기를 검색해봤더니..   
C언어에서 rand, srand만 있는 줄 알았는데 더 정교한 함수들이 있었다.

[drand48](https://man7.org/linux/man-pages/man3/drand48.3p.html)  
[random](https://man7.org/linux/man-pages/man3/random.3.html)

이런 거 알려면 또 시간 좀 걸릴텐데..  
넘 완벽주의인가?  
아니 근데 더 근사한 솔루션이 있는데 안쓰는 것도 이상하지.  
사실 테트리스 게임에 뭘 그렇게 정교한 의사 난수가 필요하겠냐만..  
다 떠나서 어떻게 다른지 순수 호기심으로 궁금하긴 함.

Top-Down 식의 개발을 하다 보면 서브 모듈을 개발할 때 고민되는 것 같음.  
기능적으로 얼마나 정교하게 만들 것인가.  
너무 세세한 부분에 집중하기 보다는 일단 큰 덩어리를 만들어 놓고  
그 다음에 세세하게 다듬는게 낫겠지?

대신에 문서적으로 잘 기록해놓자.  
어느 정도 개발이 완성된 다음에 추가로 더 정교하게 만들 수 있는 부분 찾아서 실행에 옮길 수 있게끔.

---

- 테트로미노 움직임 그리기 구상..

  이거 생각해보니까  
  테트로미노 움직임뿐만 아니라, 라인 클리어나 회전 등도 묘사해야 하는 데 이걸 로직을 어떻게 구성하지?  
  아니 게다가 아래로 순간이동 커맨드도 있는데..  
  사용자가 입력을 안한다고 해서 테트로미노가 안움직이느냐? 그것도 아님.

  drawer 객체 전용 작업 큐를 만들어서 요청을 넣어야 하나..

- 게임 화면 그릴 때 매 프레임마다 Height x Width 행렬판을 일일이 출력하는 건  
  에바인 것 같은데.. 근데 이게 구현하는 입장에선 쉬움.

이거 사용자 입력에 따른 이벤트 기반(event-driven) 프로그래밍 해야함. 무조건임.  
그러니까

1) 사용자 입력과 상관없이 돌아가는 모듈
2) 사용자 입력에 따라 돌아가는 모듈

이렇게 나눠서 구현해야함.  

맞는데.. 사용자가 입력을 안할 때는 다시 방향을  
아래로 향하게 만들어야 하는데 이건 어떻게 구현해야 함?

아 원래 반복문 로직이 있고, 그 안에서 수행하다가 사용자 입력 감지되면
시그널 핸들러가 호출되는 로직?  
그리고 시그널 핸들러 탈출 전에 다시 방향을 아래로 바꿔 주는 식으로?

근데 사용자가 입력하는 속도보다 핸들러 수행 속도가 느리면  
어떻게 되지? 문제 없나? 그 안에서 재귀호출 되는 건가?

아니지 메인 스레드가 그 핸들러를 처리하지 말고, 입력 처리 스레드가 그 핸들러 처리하면 되는거 아님?  
근데 그러면.. 문제 될 건 없나?  
이거.. 아냐 핸들러가 방향 초기화 하는게 아니고 메인 스레드가 매 주기마다 초기화하는 게 맞는 것 같음.  
결론적으로 핸들러는 방향만 바꿔주면 됨. (정확히 말하면 방향을 바꾸라는 메시지를 전달해주면 됨)
~~근데 그러면 순간 이동 로직은 어떻게 구현해야함?  이건 나중에.~~  
아니 이거 감이 안잡혀;  
구현을 해보고 예상대로 되는지 디버깅을 해야될 것 같은데..  

---

`game_play_module_t`  
이것도 단순히 함수 포인터만 가리킬게 아니고 초기 인수도 가지고 있어야 코드가 깔끔하네.  
--> 구조체화 시킬 것. (객체 지향)


### Achievements of the day
하.. 게임 만드는 거 넘 어렵다.  
대충 구글링 해서 긁어 오면 되는 거 괜히 오버하고 있는 건가.  

병렬 프로그래밍은 상상 이상으로 어려운 것이었다..  
아니 이런 단순한 게임 만드는 것도 이렇게 쉽지가 않은데,  
게임 엔진은 어떻게 만드는 거야;

이거.. 맞아. select랑 poll까지 공부하고 와야 돼.  
아직 병렬 프로그래밍 방법론에 깊이가 없어서 그래.  
이런 류의 로직이 게임에만 있겠니. 분명 레퍼런스가 있을 거임.

</details>

[//]: # (End of 03.25)

<details><summary>03.26(일)</summary>

1. ~~[select](https://man7.org/linux/man-pages/man2/select.2.html)에 대해 더 알아보기.~~   
   --> 이거 요즘에는 잘 안쓴다는데? epoll 쓴다고함. 저자 말로는 그래도 장단점이 있다고는 하는데,  
       난 대규모 서버도 고려해야할 입장이기 때문에 select..에 너무 파고들진 않겠음.
2. `game_play_module_t` 더 객체적으로 정의하기.  
3. 소켓 프로그래밍 책 챕터 이어서 공부하기.  

- 리눅스의 send & recv.

  책 내용을 보면서 느낀 건, 단순히 man page를 읽는 것만으론 그 내용을 이해할 수 없다는 것.  
  man page는 그렇게 친절한 편이 아님. 그 기저에 있는 이론을 모른다면 그것만 읽고선 알아들을 수 없다.

### Achievements of the day

어떻게 해야 스파게티 코드를 짜지 않을 수 있을까.  
어떻게 해야 내가 짠 코드한테 말리지 않을 수 있을까.  
어떻게 해야 가독성을 높일 수 있는가. 유지보수성을 높일 수 있는가.  
어떻게 해야 코드 구조가 한눈에 훤히 보일 수 있을까?

이런 것들에 있어서 정답이 있나? 나만의 스킬, 노하우들을 연마하는 수밖에..

근데 선대 개발자들은 어떻게 작성했는지 궁금하긴 하다.  
C언어로 개발하기 넘 어렵다.  
아냐. 근데 생각없이 짜면 객체지향이라도 스파게티 코드가 생기는 건 마찬가지겠지.  

이게 유지 보수성, 확장성 생각해서 짜는게 쉬운게 아님 리얼.  
너무 완벽주의를 추구하고 있는 건가. 게임이 복잡해지면 코드 가독성도 상한선이 정해지는 건가.  

지금 코드가 맘에 드는가?  
--> 맘에 안듬. 내가 짠 코드인데도 구조가 한눈에 안들어옴.  


</details>

[//]: # (End of 03.26)

<details><summary>03.27(월)</summary>

소켓 프로그래밍 책 이어서 공부하기.  
프로그래밍 못하고 있다고 해서 조급할 필요 없다.  

- send & recv 공부 이어서.

  - MSG_PEEK 

    std::priority_queue<>에 비유하자면 pop()이 아니라, top()을 위한 플래그라고 볼 수 있음.  
    MSG_DONTWAIT(논블로킹)까지 걸면 데이터의 존재 유무만 빠르게 판단할 수 있다.


  - readv & writev 입출력 함수

    함수 호출 횟수를 줄일 수 있다. --> 비용 감소


- 멀티 캐스트 & 브로드 캐스트

  UDP 기반이라서.. 내 프로젝트와는 무관한 기술 아닌가?  
  개념적인 내용은 알아둬야 하는 걸까? 일단 넘어 가자.  

- C언어의 표준 입출력 함수

  표준 입출력 함수가 지니는 장점은 다음과 같다고 한다.  
  (ANSI C 표준 기반 함수들)

  1. 이식성(Portability)이 좋다.  
  2. 버퍼링을 통해 성능 향상에 도움이 된다.

  입출력 함수뿐만 아니라 모든 표준(standard) 함수들은 이식성이 좋다.  

  이렇게만 놓고 보면 마냥 좋기만 한 것 같지만, 그렇지도 않다.  
  나름 단점이 있다.

  1. 양방향 통신이 쉽지 않다.  
  2. 상황에 따라서 fflush 함수가 빈번히 호출될 수 있다.  
  3. 파일 디스크립터를 FILE 구조체의 포인터로 변환해야 한다.


  - [fdopen](https://man7.org/linux/man-pages/man3/fdopen.3p.html)

    파일 디스크립터를 FILE 구조체로 변환해준다. --> 표준 입출력 함수를 사용할 수 있다.

  - [fileno](https://man7.org/linux/man-pages/man3/fileno.3.html)

      fdopen의 반대격 함수.  

- [epoll](https://man7.org/linux/man-pages/man7/epoll.7.html) 공부

  [epoll_create](https://man7.org/linux/man-pages/man2/epoll_create.2.html)

    `size` 0보다 큰 값만 넘기면 된다.

  [epoll_ctl](https://man7.org/linux/man-pages/man2/epoll_ctl.2.html)

    ```c
    #include <sys/epoll.h>

    typedef union epoll_data {
        void        *ptr;
        int          fd;
        uint32_t     u32;
        uint64_t     u64;
    } epoll_data_t;

    struct epoll_event {
        uint32_t     events;      /* Epoll events */
        epoll_data_t data;        /* User data variable */
    };
    ```

  [epoll_wait](https://man7.org/linux/man-pages/man2/epoll_wait.2.html)





### Achievements of the day

작업에 대한 부담감 때문에 시작조차 하지 않으려는 경향이 있는 것 같다.  
이겨내야 돼. 힘들 때마다 내가 왜 이 게임을 만들고 싶은지 계속 상기하자.  
난 게임 만드는 게 정말로 재밌는 걸까?

그.. epoll 대강 읽어봤는데, 멀티 스레딩..에는 불필요한 것 같은데.  

</details>

[//]: # (End of 03.27)


<details><summary>03.28(화)</summary>

레벨 트리거, 엣지 트리거 이어서 공부하기(멀티 스레딩에 도움이 될 수도 있으니까)  
epoll 공부 끝내고, 스레드 부분 복습하기.  
내 메인 로직의 핵심 근거가 멀티 스레드이기 때문에 이 부분에 투자를 안할 수가 없다.

- 레벨 트리거(Level Trigger)와 엣지 트리거(Edge Trigger)

  그.. 중요한 내용인 건 알겠는데, 내 프로젝트에 당장 필요한 내용은 아님.

- 다시 스레드

  충분히 공부한 내용이라고 생각했는데, 막상 코드를 짜려고 하면 어떻게 해야 할지 감이 안잡힘.  
  소켓 프로그래밍 책에 나와 있는 예제 따라 치면서 사용에 익숙해질 것.  

  ```c
  // ...
  worker_t workers[THREAD_NUM];
  for (int i = 0; i < THREAD_NUM; ++i) {
      int start = (5 * i + 1);
      if (pthread_create(&(workers[i].thread_id), NULL, thread_main, (void*)&start) != 0) {
          puts("pthread_create() error");
          return 1;
      }
  }
  // ...
  ```

  위 코드가 잘못된 코드임을 알아야 한다.    
  (머리 속에 2개 이상의 함수 콜스택을 만들어서 시뮬레이션 할 줄 알아야 함.  
   `context switch`의 간격이 상상 이상으로 찰나임을 간과하면 안된다.  
   이는 곧 스레드의 실행 순서를 함부로 예측하면 안됨을 의미한다.  
   사실 위 코드는 포인터의 존재를 의식하지 않아서 발생한 문제이기도 함)




### Achievements of the day

새로운 API 공부할 때는 예제도 이것저것 작성해보면서 익숙해질 것.  
API와 친해져야 한다.

chat-gpt(copilot)가 생각보다 코드를 잘 짬.  
나랑 안맞는 부분 일일이 수정하는게 번거로워서 그렇지  
요구 사항만 자세하게 명시하면 꽤 그럴싸하게 작성해준다.  
물론 흔하디 흔한 코드를 작성하라고 해서 그런게 크겠지만.  

생소한 분야의 코딩이라면 배울점도 있음.
AI보다는 선대 개발자들한테 배우는 셈이라고 봄.  

단.. AI 코드가 만능은 아니다. 휘둘리면 안돼.  
AI가 작성한 코드를 내려다볼 수준은 되어야 쓸만한 것 같다.  
난 아직 그럴 수준은 못되기에 혼자서 더 프로그래밍 해보련다.


</details>

[//]: # (End of 03.28)

<details><summary>03.29(수)</summary>

스레드 공부 이어서 진행.  
너무 시간 끌린다 싶으면 아는 선에서 멀티 스레드 구조 설계해서 구현해볼 것.  
그래.. 완벽주의는 신중하게 적용하자.

책에 나와 있는 내용이 뭐랄까.  
워커 스레드 모델, 그러니까 대량의 작업 처리를 병렬로 돌릴 때에 대한 예시만 보여주고 있지  
스레드들 간의 복잡한 상호 작용에 대한 처리를 다루고 있지는 않음.  
그래서 다양한 API와 기법들을 조사해서 적용할 줄 알아야 함.  

- [pthread_detach](https://man7.org/linux/man-pages/man3/pthread_detach.3.html)

  자기 자신을 떼어놓고 싶으면 아래와 같이 콜하면 됨.

  ```c
  pthread_detach(pthread_self());
  ```

  
### Achievements of the day

실행해보면 오늘 어디까지 했는지 알 거임.  

</details>

[//]: # (End of 03.29)


<details><summary>03.30(목)</summary>
#define 상수들 대부분 다 extern으로 바꿀 것.

### Achievements of the day

오늘도 발전이 있긴 했는데 코드 아직 진행중이라 문서만 업데이트 해서 올림.

</details>

[//]: # (End of 03.30)


<details><summary>03.31(금)</summary>

game 폴더부터 리팩토링 하면 됨.  

### Achievements of the day

블록 이쁘게 꾸민다고 거기에 너무 시간 쏟음;  
담부턴 이러지 말자. 가끔은 과정보다는 결과에 신경써야 한다.  

실질적으로 서비스할 게임은 아니라고 생각하다 보니 그런 것 같은데  
그래도 가장 중요한 항목부터 수행해 나갈 것.  
불필요한 완벽주의는 독이다.

전반적으로 코드 리팩토링도 함.

</details>

[//]: # (End of 03.31)


</blockquote></details>

[//]: # (End of 2023.03)





<font size="3"> <details><summary>2023.04</summary><blockquote> </font>

<details><summary>04.01(토)</summary>

simulate.h부터 리팩토링 하면 됨.

리팩토링 다하면 의사 난수 생성 보완하거나, 
사용자 입력 받기 구현할 것.

코드 더 객체지향적으로 리팩토링.

### Achievements of the day

simulate.c까지 리팩토링 하긴 했는데,  
이쪽은 아직 추가하거나 수정할 게 꽤 있음.

</details>

[//]: # (End of 04.01)

<details><summary>04.02(일)</summary>


### Achievements of the day

간단하게 코드 리팩토링 함.  
내일부터 남은 부분 이어서 리팩토링 하면 될듯.  

초기에 로직 설계 성의 있게 안하면 나중에 가서 고생한다.  
좀 더 신중하게 코드 설계하는 걸로. 스노우볼이 상상 이상으로 커진다.  

다른 사람에게 코드 구조를 설명할 수 있어야 해.  
생산성도 중요한데, 어쨌든 포트폴리오이기도 하니까.

</details>

[//]: # (End of 04.02)


<details><summary>04.03(월)</summary>


### Achievements of the day

realtime_timer부터 시작해서 객체 지향적으로 짜봤는데, C언어 특성상 한계가 있음.  
~~왜 C언어 안쓰는지 알 것 같음. 하.. 이제 와서 C++로 전환하긴 좀 그런데.~~

일단.. 하는데까지 해보기. 어쨌든 객체 지향 도입하는 건 좋은 면이 많긴 함.

</details>

[//]: # (End of 04.03)


<details><summary>04.04(화)</summary>


### Achievements of the day

오늘 딱히 한 건 없지만 값진 경험 했음. 

내일부턴 사용자 입력 받는 로직 구현해보기.  
프로젝트 진행 질질 끌리면 흐름 끊겨서 위험함.

</details>

[//]: # (End of 04.04)


<details><summary>04.05(수)</summary>


사용자 입력 받기 구현 전에 게임 프레임 관련하여 좀 더 공부해보기.  
자료는 하나만 보지 말고 이것저것 다양하게 조사하기.  

맹목적으로 수용하지 말고 비판적으로 보기.  
기존의 이론을 바탕으로 내가 더 근사한 로직을 작성할 수도 있는 거니까.


- 게임 루프

  - 전통적인 게임 루프

    ```c
    while game is running
        process inputs
        update game world
        generate outputs
    ```

    입력은 키보드, 마우스, 컨트롤러, 네트워크 데이터 수신, ...  
    출력은 그래픽, 오디오, 네트워크 데이터 송신, ...  

  
  - 멀티 스레드 게임 루프

    렌더링과 업데이트를 동시에 수행하려면 메인 게임 루프 스레드를 수정해서 입력 처리, 게임 세계 업데  
    이트를 수행한 뒤에 출력을 생성할 때 그래픽을 제외한 출력만 생성하게 해야 한다. 그런 다음 그래픽에  
    관한 모든 데이터를 그래픽 작업만 전담하는 두 번째 스레드, 즉 렌더링 스레드로 넘겨줘야 한다.

    하지만 이때 중요한 문제가 있다. 렌더링 스레드가 화면을 그리는 동안 메인 스레드는 뭘 해야 할까?  
    그리기가 끝날 때까지 그냥 기다린다면 하나의 스레드로 전부 처리할 때와 처리 속도에 별 차이가 없다.  
    기껏 둘로 나눈 스레드의 효과를 제대로 살리려면 렌더링 스레드를 메인 스레드보다 한 프레임씩 늦게  
    수행해야 한다. 즉 메인 스레드가 업데이트를 수행하는 동안 렌더링 스레드는 메인 스레드가 전 프레임  
    에서 업데이트한 결과를 화면에 그려야 한다.

- 시간과 게임

  - 실제 시간과 게임 시간

    현실 세계에서 흘러간 시간을 의미하는 `실제 시간(real time)`과 게임 세계에서 흘러간 시간을 의미하는  
    `게임 시간(game time)`의 구별은 매우 중요한 문제다. 실제 시간과 게임 시간이 1:1로 대응할 때도 있지만,  
    항상 그렇진 않다. 일시 정지 상태인 게임을 예로 들어보자. 현실 세계에서 아무리 많은 시간이 흘러가도  
    게임 시간은 그대로 멈춰 있다. 일시 정지를 풀어서 게임 시간을 다시 업데이트하기 시작할 때까지 게임  
    시간은 흐르지 않는다.

  - 델타 시간

    게임 시간을 고려해서 게임 루프를 업데이트 하는 방법.

    ```c
    enemy.position.x += 5
    ```

    위와 같은 코드는 프로세서의 속도에 따라 게임의 진행 속도가 달라진다.  
    예를 들어 이 코드를 초당 30번 수행하면 즉 30FPS로 실행하면 적이 1초에  
    150픽셀을 이동하지만, 60FPS로 실행하면 1초에 300픽셀을 이동해버린다.  
    이런 문제를 해결하기 위해 델타 시간이라는 개념을 도입했다.
    
    **델타 시간**이란 이전 프레임을 수행하는 데 걸린 게임 시간을 말한다.  
    앞서 소개한 의사 코드에 델타 시간을 적용하려면 이동 거리를  
    `프레임당 몇 픽셀` 단위가 아닌 `초당 몇 픽셀` 단위로 생각해야 한다.  
    이상적인 이동 속도가 초당 150픽셀이라면 다음과 같이 수정할 수 있다.  

    ```c
    enemy.position.x += 150 * deltaTime
    ```

    위 코드는 프레임 속도와 관계없이 완벽하게 동작한다. 30FPS에서는 프레임당  
    `5(= 1 / 30 \* 150)`픽셀씩 움직여서 1초에 총 150픽셀을 움직일 것이고, 60FPS에서는  
    프레임당 `2.5(= 1 / 60 \* 150)`픽셀씩만 움직이겠지만 결국 초당 150픽셀을 움직일 것이다.  
    60FPS 쪽의 움직임이 더 부드럽겠지만 초당 이동 속도만 놓고 보면 차이가 없다.

    위치뿐만 아니라 오브젝트의 다양한 속성도 여러 프레임에 걸쳐서 변화가 일어날 수 있기  
    때문에 속성의 변화에도 델타 시간을 적용해야 한다. 델타 시간 값을 구하려면 먼저 이전  
    프레임을 수행하는 데 걸린 실제 시간을 알아내야 한다. 실제 경과 시간을 얻었다면 게임  
    시간으로 변환할 수 있다. 델타 시간을 적용해서 게임 루프를 수정하면 다음과 같다.

    ```c
    while game is running
        realDeltaTime = time since last frame
        gameDeltaTime = realDeltaTime * gameTimeFactor

        // smth inputs
        ...
        update game world with gameDeltaTime
        // smth outputs
    ```

    그런데 이와 같은 구현 방식은 문제가 있다. 일단 물리학을 적용한 게임이라면 프레임  
    속도에 따라 움직임 자체가 완전히 달라질 수 있다.  
    가장 간단한 방법은 목표로 설정한 델타 시간이 지날 때까지 게임 루프를 강제로 대기  
    시키는 프레임 제한을 구현하는 것이다. 예를 들어 목표로 설정한 프레임 속도가 30FPS  
    인데 30ms 만에 프레임의 모든 로직을 완료했다면, 바로 다음 프레임으로 넘어가지 않고  
    약 3.3ms 동안 루프를 대기시켜서 30FPS를 맞춘다. 이런 프레임 제한을 구현하면 아래와  
    같다.

    ```c
    // 30FPS에 해당하는 프레임 속도는 33.333ms이다.
    targetFrameTime = 33.3f
    while game is running
        realDeltaTime = time since last frame
        gameDeltaTime = realDeltaTime * gameTimeFactor

        // inputs
        update game world with gameDeltaTime
        // outputs

        while (time spent this frame) < targetFrameTime
            // smth works
    ```

    고려해야 할 점이 하나 더 있다. 고사양 게임의 경우 프레임의 수행 시간이 목표로 한 시간을  
    넘어가는 일이 생기면 어떻게 해야 할까? 몇 가지 해결책이 있지만 가장 일반적인 방법은 목표  
    로 하는 프레임 속도에 맟출 수 있게 바로 뒤 프레임의 렌더링을 건너뛰는 것이다. 이런 방법을  
    프레임 드랍이라고 한다.


- 게임 오브젝트

  넓은 의미에서 게임 오브젝트란 프레임마다 업데이트하거나 그려야 할 게임 세계 안의 모든 요소를  
  뜻한다. 구현 방식을 불문하고 게임이라면 무슨 수를 써서라도 게임 오브젝트의 자취를 쫓아서 게임  
  루프에 추가해야 한다.


  - 게임 오브젝트의 종류

    게임 오브젝트에는 크게 세 종류가 있다. 이 중 가장 눈에 띄는 오브젝트는 업데이트해야 할 뿐만  
    아니라 그리기도 해야 하는 오브젝트다. 캐릭터, 생명체 또는 기타 움직이는 모든 오브젝트는 게임  
    루프의 '게임 세계 업데이트' 단계에서 업데이트한 뒤에 '출력 생성' 단계에서 그려져야 한다.

    그려야 하지만 업데이트할 필요가 없는 오브젝트를 정적 오브젝트라고 한다.

    세 번째 게임 오브젝트는 눈에 잘 안 띄는 오브젝트로 업데이트해야 하지만 그릴 필요는 없는 오브  
    젝트다. 일례로 카메라가 있다. 엄밀히 말해 카메라를 통해 볼 수는 있어도 카메라를 볼 순 없다.  
    하지만 카메라는 많은 게임 내에서 자유자재로 움직이는 오브젝트다. 또 '트리거'라고 불리는 오브  
    젝트를 예로 들 수 있다. 트리거는 플레이어가 정해진 위치에 왔는지 감지하고 적절한 조치를 하는  
    오브젝트다. 그래서 트리거는 눈에 보이지 않는 상자 형태로 만들어진다. 그리고 플레이어를 감지할  
    수 있게 끊임없이 업데이트해야 한다.



### Achievements of the day

공부하면서 느낀 건데 내가 사서 고생을 하고 있네..  
OOP 갓..

코드 리팩토링 수행.

게임 루프 구현할 때 FPS 개념 도입하는 거 원리는 이해함.  
근데 아직 이러한 로직에 익숙치 않아서 논리적으로 코딩 못한 것 같음.  
뭐가 문제인지 파악은 했으니까 낼부터 다시 구현해보면 될 듯.

기존 함수를 새로운 함수로 교체할 때 요령이 부족한 것 같음.  
확실하게 새로운 변수, 함수 정의해서 구현하기.  

</details>

[//]: # (End of 04.05)

<details><summary>04.06(목)</summary>


### Achievements of the day

게임 루프 델타 타임 버전으로 시도했는데 이상하게 잘 안됨;  
어차피 콘솔 출력이라 미세한 움직임은 구현 못해서 일단 넘어가기로 함.

- 주요 로직 좀 더 모듈화 함.  
- 스폰 위치 랜덤화 구현. 덕분에 버그도 찾음.

</details>

[//]: # (End of 04.06)


<details><summary>04.07(금)</summary>

입력 받는 로직 설계 및 구현해보기.  
(신중하게 찬찬히 설계. 자료 조사도 충분히 하고.)

  <details><summary>CRT 이야기</summary>

  CRT(Cathode-Ray Tube)는 음극선을 이용하여 형광물질에 빛을 내는 [진공관](https://namu.wiki/w/%EC%A7%84%EA%B3%B5%EA%B4%80)으로 모니터나 텔레비전 등의 디스플레이로 사용된다.  
  
  전자 빔의 운동에너지가 앞면 유리에 도포된 [형광 물질](https://namu.wiki/w/%ED%98%95%EA%B4%91%20%EB%AC%BC%EC%A7%88)과 충돌하여 빛을 내는 방식이다. 전기 신호를 이용하여 음극선의 방향과 강도를 조절한다. 일본을 중심으로 아시아권에서는 흔히 초기 발명자인 카를 페르디난트 브라운의 이름에서 따온 '브라운관'으로 통한다.

  브라운관 텔레비전과 컴퓨터용 모니터의 동작 방식은 완전히 동일하지만 제어부와 픽셀피치, 픽셀의 모양, 특성이 조금씩 다르다. TV는 멀리서 보기 때문에 해상도가 낮은 대신 [개구율](https://terms.naver.com/entry.naver?docId=1021059&cid=50324&categoryId=50324)을 높이기 위해 원형이 아닌 위 아래로 길쭉한 픽셀을 가지고 있다. 반면 모니터는 가까이서 문서나 글자를 보아야 하기 때문에 해상도가 높고, 원형 픽셀을 가지고 있다.

  ![CRT 디스플레이](https://i.namu.wiki/i/2mCsPmldVbpL_wf6ZC-Xz4p2kXY5EVlSoNDOOy-_I0PjP25eprnNiDMoM77mDDXM8r_NH033PCl_R21So6awRRuJM3lAvEWBKfPkve7xmAXGnT0DsyfsBvs44agA1Gfdxc4tT_Y068eA_0to_aHzjQ.webp)

  | 명칭 | 설명 |
  |---|---|
  | 2. 전자총(Electronic Gun) | 화면을 향해 전자빔을 송출하는 장치. 3개의 빔이 각각 적색, 녹색, 청색 형광점으로 전자를 송출한다. |
  | 3. 전자빔(Electronic Beams) | 전자총에서 나오는 속도가 거의 균일한 전자의 흐름. 파장이 극히 짧다. |
  | 4. 편향 요크(Deflection Yoke) | 전자기력 발생 장치. 전자기력을 미세하고 정교하게 조정하여 전자빔을 휘게 한다. |
  | 5. 형광점(Phosphor Dot) | 작은 형광 입자. 적색점, 녹색점, 청색점으로 이루어져 있으며 전자빔이 닿으면 빛을 발생한다. 전자빔의 종류와 세기에 따라 발색 정도가 달라진다. |
  | 6. 섀도 마스크(Shadow Mask) | 형광면 앞에 위치한 얇은 금속판. 전자빔이 형광 도트에 정확하게 입사하도록 하는 역할을 한다. |
  | 7. 트라이어드(Triad) | 인접한 적, 녹, 청 형광점이 조화되어 색상을 만듦. 픽셀보다 작은 단위. |
  | 8. 픽셀(Pixel) | 몇 개의 트라이어드가 모여서 픽셀이 된다. LCD와는 상이한 구조를 띠는데, 이는 가변 해상도를 가지는 디스플레이의 특징이다. 다만 픽셀 개념은 아날로그 TV에는 존재하지 않는다. |


- CRT 모니터

  ![CRT DISPLAY](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1f/CRT_image_creation_animation.gif/330px-CRT_image_creation_animation.gif)


  CRT의 모든 그리기 작업은 한 지점에 전자의 흐름을 발사하는 전자총이 전담한다. 전자총은 화면의 왼쪽 위 모서리에서 시작해 수평 방향으로 가로지르면서 첫 번째 주사선을 그린다. 그런 다음 전자총이 조준하는 지점을 다음 주사선의 맨 왼쪽으로 옮겨서 다시 주사선을 그리기 시작한다. 모든 주사선이 그려질 때까지 이 과정을 반복한다.

  하나의 프레임을 다 그리고 나면 전자총이 화면의 오른쪽 아래 모서리를 가리키고 있을 것이다. 전자총이 조준하는 지점을 오른쪽 아래 모서리에서 왼쪽 위 모서리로 되돌리는 데 걸리는 시간을 수직 공백 시간(VBLANK)이라고 한다. 수직 공백 시간은 몇 분의 1초 단위며 CRT 가 TV용인지 컴퓨터용인지에 따라, 또 기기를 출시할 국가에 따라 달라질 수 있다.

  아타리 같은 초기 게임 시스템은 메모리의 크기가 작아서 화면 전체의 픽셀 데이터를 한 번에 저장하지 못했으므로 렌더링 방법이 훨씬 복잡할 수 밖에 없었다. [GCD 강연 영상](https://www.gdcvault.com/play/1014632/Classic-Game-Postmortem-PITFALL)([유튜브 영상](https://www.youtube.com/watch?v=MBT1OK6VAIU)도 있음)에 이러한 문제의 해결책이 나와있다고 한다.

- 색상 버퍼와 수직 동기화

  ![screen tearing](https://upload.wikimedia.org/wikipedia/commons/thumb/0/03/Tearing_%28simulated%29.jpg/330px-Tearing_%28simulated%29.jpg)

  요즘 하드웨어는 메모리가 넉넉해서 화면 전체의 픽셀 데이터를 한 번에 저장할 수 있는 색상 버퍼를 보유하는 데 아무 문제가 없다. 하지만 그렇다고 해서 게임 루프가 CRT의 전자총을 신경 쓰지 않아도 상관없다는 말은 아니다. 전자총이 화면을 반쯤 그렸을 때 게임 루프가 '출력 생성' 단계에 들어가는 상황이 발생했다고 하자. 즉 전 프레임의 데이터를 아직 CRT에 그리는 중인데 게임 루프가 다음 프레임의 픽셀 정보를 색상 버퍼에 쓰기 시작했다는 뜻이다. 결과적으로 위 그림처럼 각 프레임의 일부분이 한 화면에 나타나는 화면 밀림(screen tearing) 현상이 일어난다.

  더 큰 문제는 게임 루프가 다음 프레임에서 화면에 그려질 이미지 정보를 색상 버퍼에 채우는 과정을 끝내지 못한 상황이 발생할 수도 있다는 점이다. 결국, 화면의 반이 잘못 그려질 뿐 아니라 그래픽 정보의 손실까지도 일어날 수 있다.

  화면 밀림을 해결하는 방법의 하나는 게임 루프를 수정해서 수직 공백 시간 내에 렌더링을 수행하는 것이다. 일단 이미지가 잘리는 문제는 고쳐지겠지만, 게임 루프가 VBLANK 안에 색상 버퍼의 렌더링을 마쳐야 한다는 제약이 생긴다. 최신 게임을 렌더링하기에는 턱없이 부족한 시간이다.

  화면 밀림의 다른 해결책으로 이중 버퍼링(double buffering)이라는 렌더링 기법이 있다. 이중 버퍼링 기법은 두 개의 색상 버퍼를 사용한다. 게임은 두 개의 버퍼를 번갈아 사용하며 그리기를 수행해야 한다. 예를 들어 CRT가 버퍼 B의 내용을 표시하는 동안 게임 루프는 버퍼 A를 채운다. 그리고 다음 프레임에서 게임 루프가 버퍼 B를 채우는 동안 CRT는 버퍼 A의 내용을 표시한다. CRT와 게임 루프가 동시에 같은 버퍼를 사용하지 않는 한, CRT가 불완전한 프레임을 그릴 위험은 없다.

  화면 밀림을 완벽하게 방지하려면 버퍼 교환이 VBLANK 안에 이뤄져야 한다. 종종 게임의 그래픽 설정에서 수직 동기화(VSYNC)란 항목을 찾아 볼 수 있다. 엄밀히 말하면 부적절한 명칭이다. VSYNC란 BVLANK의 시작을 알리려고 모니터가 시스템에 보내는 신호를 뜻하기 때문이다. 어쨌든 버퍼 교환은 비교적 속도가 빠른 연산이기 때문에 게임이 프레임을 렌더링하는 데 쓸 수 있는 시간이 더 늘어난다. 물론 CRT가 프레임을 그리는 시간보다 렌더링 시간이 짧다면 더할 나위 없다. 아무튼, VBLANK 안에 버펴 교환이 일어난다면 화면 밀림을 완벽하게 방지할 수 있다.

  렌더링이 끝나는 즉시 버퍼 교환을 허용하는 게임도 있다. 즉 화면 밀림을 감수한다는 뜻이다. 사용자가 화면 갱신 속도보다 훨씬 빠른 프레임 속도로 게임을 실행하길 원할 때 이런 식으로 빠른 버퍼 교환을 허용하는 것이 일반적이다. 갱신 속도가 60Hz인 모니터에서 버퍼 교환을 VBLANK에 맞추면 프레임 속도의 상한이 60FPS로 제한된다. 하지만 이 상한을 없애면 입력 지연을 줄이기 위해 높은 사양의 컴퓨터를 갖춘 플레이어가 더 높은 프레임 속도로 게임을 플레이할 수 있다.

  이제 CRT는 거의 자취를 감췄지만, LCD도 여전히 이중 버퍼링으로 화면 밀림을 방지할 수 있다. 물론 버퍼 교환 시간을 LCD에 맞게 수정해야 한다. 두 개가 아닌 세 개의 색상 버퍼를 쓰는 삼중 버퍼링을 사용하는 게임도 있다. 삼중 버퍼링은 프레임 속도가 심하게 불규칙적일 때 프레임 속도를 일정하게 고르는 데 유용할 수 있지만, 입력 지연 시간의 증가를 감수해야 한다.

  </details>

  [//]: # (End of CRT 이야기)

  <details><summary>입력 시스템 설계</summary>

입력 장치

  입력 장치의 종류는 다양하다. PC나 콘솔 게이머라면 키보드, 마우스, 컨트롤러가 더 익숙하겠지만 모바일 게임에서 가장 중요한 입력 장치는 터치스크린과 가속도계다. 그 밖에 위모트, 키넥트, 기타 컨트롤러, VR 헤드셋용 헤드 트래킹 장치 등은 비교적 최근에 등장한 입력 장치다. 하지만 입력 장치의 종류에 상관없이 입력 장치가 정보를 요청받을 때 작용하는 핵심 기법이 있다. 


  </details>

  [//]: # (End of 입력 시스템 설계)  

  
### Achievements of the day

테트로미노 그림자(실루엣) 구현.

입력 구현하려고 관련 이론은 대강 읽어봤는데 쉽지 않네.  
입력 구현도 제대로 구현하려면 생각보다 알아야 할 게 많음..  
키보드뿐만 아니라 게임 패드도 지원할 생각이기 때문에 고려해서 설계하기.

CRT 이야기는 교양 삼아서 읽어 본 거지.

</details>

[//]: # (End of 04.07)

<details><summary>04.08(토)</summary>

### Achievements of the day

오늘 딱히 한 건 없고 termios.h 사용하는 예제 코드 좀 작성해봄.  
termios 관련 man page 좀 읽어 보려고 했는데 쉽지 않네.  
개발 공부는 정말 무궁무진 하구나.

주말엔 아무 생각없이 좋아하는 거 하면서 푹 쉬는 걸로..  
감당할 수 있는 만큼만 공부하자.  

</details>

[//]: # (End of 04.08)


<details><summary>04.09(일)</summary>

### Achievements of the day

입력 체계 어떻게 갖출지 대강 감 잡아서 구현 시도해보긴 했는데

입력 객체는 일단 정의만 해놓았고,  
회전 개념은 적용함. 

</details>

[//]: # (End of 04.09)

<details><summary>04.10(월)</summary>

- 방향키을 비롯한 키보드 입력 받기 (추후에 게임 패드도 지원할 예정 --> 확장성 감안하여 설계)  

  키보드의 방향키는 대응되는 아스키 코드가 없다. 아스키 코드는 문자 인코딩이지 키보드 인코딩이 아니기 때문이다. 방향키가 눌리면 운영체제가 프로그램이 캡처할 수 있는 이벤트를 트리거하는 방식이기에 방향키에 대한 아스키 코드나 유니 코드는 없다. 여기서 키보드 인코딩이란 키보드에서 입력된 키를 컴퓨터가 이해할 수 있는 코드로 변환하는 방법을 일컫는다.

  방향키 이벤트를 처리하기 위한 몇 가지 방법들이 있는데 그 중 가장 적합한 걸 골라 보는 걸로.

  1. ncurses 패키지  
    뭐랄까 효과는 강력한 것 같은데 대체로 추천하지는 않는 것 같다. 

  2. termios  
    고맙게도 키보드 관련 입력도 처리해주는 기능이 있는 듯.  

  3. <linux/joystick.h>  
    조이스틱은.. 이거 써야 하는 듯?

  4. evdev  
    터미널뿐만 아니라 좀 더 범용적으로 입력 이벤트를 처리할 수 있는 라이브러리.  
    리눅스 커널의 이벤트 드라이버 인터페이스라고 한다.  
    얘가.. 좀 복잡해 보여도 제일 ~~간지나긴 하는데~~ 범용성이 좋아보이는데.  
    의외로 코드 작성도 더 쉬울 수 있음.

  >evdev 라이브러리를 사용하는 것이 좋은 경우는 다음과 같습니다.
  >
  > - 다양한 입력 장치를 지원해야 하는 경우: evdev 라이브러리는 리눅스 커널의 이벤트 드라이버 인터페이스에 직접 접근하여 키보드, 마우스, 조이스틱 등 다양한 입력 장치의 이벤트를 처리할 수 있습니다. 따라서 다양한 입력 장치를 지원해야 하는 경우 evdev 라이브러리를 사용하는 것이 좋습니다.
  >
  > - 저수준의 입력 이벤트 처리가 필요한 경우: evdev 라이브러리는 리눅스 커널의 이벤트 드라이버 인터페이스에 직접 접근하여 입력 이벤트를 처리합니다. 따라서 저수준의 입력 이벤트 처리가 필요한 경우 evdev 라이브러리를 사용하는 것이 좋습니다.
  >
  > - 터미널 환경에서 작동하지 않는 경우: ncurses와 termios 라이브러리는 터미널 입출력을 제어하는 데 사용되며, 터미널에서 발생하는 입력 이벤트만 처리할 수 있습니다. 반면 evdev 라이브러리는 리눅스 커널의 이벤트 드라이버 인터페이스에 직접 접근하여 입력 이벤트를 처리할 수 있으므로 터미널 환경에서 작동하지 않는 경우에도 사용할 수 있습니다.
  >
  >위와 같은 경우에 evdev 라이브러리를 사용하는 것이 좋습니다. 하지만 evdev 라이브러리는 리눅스 전용 라이브러리로, 다른 운영 체제에서는 사용할 수 없습니다. 따라서 다른 운영 체제에서도 작동해야 하는 프로그램을 작성하는 경우에는 evdev 라이브러리를 사용하기 어렵습니다.    

  그.. 조이스틱까지 고려하면서 설계하려다 보니 머리가 아픈 것 같은데,  
  처음부터 너무 많은 걸 고려하면 시작도 못한다. 우선 키보드 버전부터 차근차근 구현해볼 것.  

  근데, 키보드 구현도 이게.. 어떤 식으로 설계를 해야할지 고민임.  
  스레드를 하나 따로 돌리는 건 맞는데, 스레드 종료는 어떻게 하지? 굳이 종료할 필요가 없는 건가?  
  그때 그때마다 이벤트 로직(콜백 함수)만 따로 교체해주면 되는 건가??  
  (물론 언젠가 종료는 해야함.)





### Achievements of the day

- 의사 난수 생성 알고리즘 업그레이드. (잘한 건지는 모르겠음...)  
- 게임 판 옆에 통계 제시.

입력 이벤트 처리 라이브러리 검색 좀 해봤는데 evdev가 가장 적절한 듯.  
어차피 윈도우즈 버전은 다른 라이브러리로 모조리 다 바꿀 것이기 때문에 갠춘.  
test 폴더에 이것저것 예제 코드 작성해놨으니 참고할 것.  
오늘 입력 이벤트 처리 구현은 못했지만, 그래도 나쁘지 않은 성과.

</details>

[//]: # (End of 04.10)


<details><summary>04.11(화)</summary>

- evdev

  ref  
  - https://www.kernel.org/doc/html/v5.0/input/input.html  
  - https://linux.die.net/man/4/evdev  
  - https://www.freedesktop.org/software/libevdev/doc/latest/  

### Achievements of the day

키보드 이벤트 처리 문제 때문에 우분투 데스크톱 버전 설치함.  
가상 머신 안에서 IDE 돌리는 건 오바라 개발은 윈도우즈에서 하고  
실행은 가상 머신 속 우분투에서 하는 걸로.

근데 리눅스에서 유니코드가 다르게 보여서.. 테트로미노 색이 내가 예상한 것과 다름.  

오늘 입력 처리까지 할 수 있었는데, pthread_cleanup_push이 컴파일이 안될 줄이야..  
아니 근데 이게 말이 돼? POSIX 코드에 오류가 있다고? 게다가 저건 흔하게 쓸 것 같은데..  
일단 오늘 분량은 올리자.


</details>

[//]: # (End of 04.11)

<details><summary>04.12(수)</summary>

### Achievements of the day

그.. 구현해서 돌려봤는데 내 예상대로 안 움직임;  
게임 루프.. 입력 이벤트까지 처리하려니까 진짜 어렵네.  
델타 시간 개념으로 구현해보는 걸로. 이거밖에 답이 없음.

그리고, 입력 로직 다시 짜야 함.  
게임 중이 아닐 때도 입력 들어오는 거 고려해야함.

스레드 동기화 더 세분화 해야 함.

하드 드롭 한 다음에 테트로미노 연산에 반응하는 거 어떻게 처리하지;  
좀 더 정교하게 설계해야 할 듯.

이미 쌓인 블록이랑 충돌 판정 이상함.

</details>

[//]: # (End of 04.12)

<details><summary>04.13(목)</summary>

### Achievements of the day

어제 문제점에서 개선한 건 없음.  
코드 리팩토링 좀 한 정도?  

디버깅 하기가 넘 어려움..  
문제를 더 잘게 쪼개서 부분적으로 접근하기로 함.  
동기화 문제 신경 쓰면서.

게임 루프 구현에 정답은 없기 때문에 나만의 방식으로 만들어 보자.

</details>

[//]: # (End of 04.13)

<details><summary>04.14(금)</summary>

### Achievements of the day

~~테트로미노 순회 구현 시도. --> 에바~~

게임 세계 상의 모든 객체는 위치를 가진다.  
그리고, 그 객체를 화면 상에 지우는/그리는 draw 함수도 필요.

객체화 시도.  
C로 C++ 흉내내려고 하지는 말자..  
객체지향적 코드가 나쁘다는 건 아닌데 C로는 한계가 있음.  
`this`가 지원안되는 것부터 무리임.  

`has-a` 관계랑 `void*`로 어떻게든 비빌 수 있기는 한데   
그러면 코드에 손이 너무 많이 감. 일단은 융통성 있기 짜는 걸로..ㅠ

코드 뒤집느라 힘들긴 한데 코드 가독성이나 유지 보수성은 올라가는 듯.

</details>

[//]: # (End of 04.14)

<details><summary>04.15(토)</summary>

아직 drawable, updatable 개념 적용하지 말 것.  
게임 보드 크기 넉넉하게 잡을 것. (스카이 라인이 무조건 맨 위가 아니다.)

tetromino_generator, manager 업데이트 해야 함. 특히 매니저.

### Achievements of the day

</details>

[//]: # (End of 04.15)

<details><summary>04.16(일)</summary>

생각해봤는데, 게임 오브젝트 반복문 돌리는 게 맞는 것 같음.

테트로미노 그리는 방식..  
전체 화면 출력에 대한 배열을 만들어서 화가 알고리즘을 적용하는 방법이 있긴 한데,  
별로 쓰고 싶지 않음.  

좀 번거롭지만 이전에 그려진 정보를 저장하여   
이전 픽셀을 지우고(엄밀히 말하면 배경색으로 채움) 새로운 픽셀을 출력하는 방식을 택해 보는 걸로.  

### Achievements of the day

</details>

[//]: # (End of 04.16)

<details><summary>04.17(월)</summary>

테트로미노 메모리 누수 조심!! 체계적으로 설계할 것. (이래서 C++이 편한데..)

테트로미노 위치 디버깅해볼 것.. 뭔가 이상함;

### Achievements of the day

</details>

[//]: # (End of 04.17)

<details><summary>04.18(화)</summary>


### Achievements of the day

- 사용자 입력 구현..

  - [X] Move L, R, D 구현.  
  - [X] Roate L, R 구현.  
  - [X] 하드 드롭 구현.  
  - [X] 출력하는 로직 변경. (바로바로 렌더러에게 출력 정보를 보내는 방향으로) 
  - [X] 라인 클리어만 구현.


</details>

[//]: # (End of 04.18)

<details><summary>04.19(수)</summary>


### Achievements of the day

  - [X] 라인 클리어 후 위에 있는 블록 낙하.
  - [X] 게임 시작 안했을 때도 입력 처리 해야함.
  - [ ] 테트로미노 keep 구현.
  - [ ] race condition.. 지금은 약간 어거지. 좀 더 융통성 있는 방식으로. 
  - [ ] 타이머 오차 있나 확인.  
  - [ ] 실루엣 구현.
  - [ ] 벽에 붙어 있어도 회전할 수 있게끔 만들기.
  - [ ] 원인 모를 렉 있음.
  - [ ] 회전할 때 뭔가 어색함..
  - [ ] 그밖에 버그 있나 확인.
  
사소한 시간 복잡도에 너무 연연하지 말자.  
자잘한 최적화는 버그 발견 후에 해도 괜찮음.

tetromino_status 판별 로직 좀 더 정교하게 설계할 필요.

종종 알 수 없는 렉이 있는데.. 아마 락 메커니즘 때문인듯? 확실치는 않음.

</details>

[//]: # (End of 04.19)

<details><summary>04.20(목)</summary>


### Achievements of the day

  - [X] 테트로미노 keep 구현. --> 지우기 과정에서 버그 있음. 지우기 알고리즘 다시 설계해야 함.
  - [ ] 테트로미노 모델링 통일화.
  - [ ] race condition.. 지금은 약간 어거지. 좀 더 융통성 있는 방식으로. 
  - [ ] 타이머 오차 있나 확인.  
  - [ ] 실루엣 구현.
  - [ ] 벽에 붙어 있어도 회전할 수 있게끔 만들기.
  - [ ] 원인 모를 렉 있음.
  - [ ] 회전할 때 뭔가 어색함..
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.20)

<details><summary>04.21(금)</summary>


### Achievements of the day

Didn't do anything.

</details>

[//]: # (End of 04.21)

<details><summary>04.22(토)</summary>


### Achievements of the day

  - [X] 테트로미노 keep 구현. --> 지우기 과정에서 버그 있음. --> 버그 수정!
  - [X] 테트로미노 모델링 통일화.
  - [X] 하드드롭 시 가끔씩 원인 모를 렉 있음.   
    --> 테스트 결과 스핀락 걸어서 생긴 문제 같음. 다시 뮤텍스로 바뀌니 그런 렉은 없음..  
        맨 페이지에 스레드 우선순위 어쩌구 했던 것 같은데 진짜 그게 관련이 있는 거였던 듯...
  - [ ] 벽에 붙어 있어도 회전할 수 있게끔 만들기.
  - [ ] race condition.. 지금은 약간 어거지. 좀 더 융통성 있는 방식으로. 
  - [ ] 타이머 오차 있나 확인.  
  - [ ] 실루엣 구현.
  - [ ] 회전할 때 뭔가 어색함..
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.22)

<details><summary>04.23(일)</summary>


### Achievements of the day

  - [X] 벽에 붙어 있어도 회전할 수 있게끔 만들기.
  - [X] 회전할 때 뭔가 어색함..
  - [ ] 점스 시스템 난이도 부여 (점수, 클리어한 라인 수)
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)
  - [ ] 게임 패드에도 동작하게끔 구현.
  - [ ] 실루엣 구현.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.23)

<details><summary>04.24(월)</summary>

닌텐도 스위치 프로 컨트롤러 인식은 되는데  
'계속 눌림'을 드라이버가 감지해주지 않음.  
--> 누르고 있음과 방금 뗌을 내가 직접 구별하여 구현하라는 건데 쉽진 않을 듯.
    아마 델타 시간 개념 적용해야 할 듯.

### Achievements of the day

  - [X] 게임 패드에도 동작하게끔 구현.  
        --> https://www.kernel.org/doc/html/v4.15/input/gamepad.html

</details>

[//]: # (End of 04.24)

<details><summary>04.25(화)</summary>

실루엣(예상 낙하 지점 제시) 어떻게 구현하지..?  
실루엣 전용 테트로미노 객체를 하나 생성해야 하나?  
얘도 매 시간마다 지우고 다시 그려야 하기 때문에 그게 깔끔하긴 할 듯.  
근데, 굳이 동적으로 할당할 필요는 없을 듯. 아닌가?

이제 보니 hold랑 스왑할 때도 실루엣 업데이트 해줘야 함.

### Achievements of the day

키보드를 제외한 입력 장치가 감지되지 않을 때  
에러 처리하지 않고, 그냥 종료하게끔 수정.

실루엣 구현 버그 있긴 한데, 해결할 수 있을 듯.

  - [ ] 실루엣 구현.


</details>

[//]: # (End of 04.25)

<details><summary>04.26(수)</summary>

사용자 입력 O_NONBLOCK으로 받을 수 있을 것 같음.  
안되는 줄 알고 따로 입력 스레드 돌렸었는데 이제 그럴 필요 없을 듯..  
(에러 메시지 꼼꼼하게 확인하자...)
게임 루프 안에 사용자 입력 로직도 넣어 보는 걸로.


게임을 플레이 할 때 키보드로 조작하다가 컨트롤러로 변경하면  
그에 맞게 게임 로직(버튼 이벤트, 조작키 안내와 같은 UI 등등)을 변경하는 기능을 제공하고 싶음.  
[GameInput fundamentals](https://learn.microsoft.com/en-us/gaming/gdk/_content/gc/input/overviews/input-fundamentals)
윈도우즈 내용이긴 한데 유용할 듯.  
잘 읽어 보자.

pthread_cleanup_push, pthread_cleanup_pop 내가 사용법을 이해 못한 거였음..   
하긴 표준 라이브러리에 오류가 있을리가 없지.  
pop을 깜빡하고 호출 안할까봐 일부러 #define으로 정의한 것.

### Achievements of the day

실루엣 구현 성공.
시간에 따른 낙하 속도 완화(난이도 하락)

  - [X] 실루엣 구현.
  - [X] 게임 루프 내 NONBLOCKING 입력 구현.  
    --> 구현은 했는데, 그닥 성능 차이를 모르겠어서.. 일단 좀더 측정해봐야 할듯.
  - [ ] 스카이 라인 제대로 출력하기.
  - [ ] 조작키 안내 
  - [ ] 점스 시스템 구현 (점수, 클리어한 라인 수)
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] 의사 난수 생성 별로인 것 같음.. 좀 더 고민해보기.  
        --> 관련하여 이런 [규칙](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-5.3)도 있으니 참고할 것.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.26)

<details><summary>04.27(목)</summary>

사용자 입력에 대한 반응 속도가 느린 것 같아서 자잘한 최적화 좀 시도해 봐야 할듯.

  - 배열 인덱싱할 때 범위 검사 안하게끔 배열 넉넉하게 잡기.

FPS가 너무 높아도 안좋고, 낮아도 안좋고.. 120 정도가 적당한 것 같음.  
물론 더 테스트해서 좋은 값을 얻을 순 있겠음.

### Achievements of the day

  - [X] 게임 루프 내 NONBLOCKING 입력 구현.  
    --> 구현은 했는데 그닥 성능 차이를 모르겠음. 일단 좀더 측정해봐야 할듯.
  - [X] 스카이 라인 제대로 출력하기.
  - [ ] 라인 클리어 후 블록 낙하 버그 있는듯. 좀 더 테스트 해볼 것.
  - [ ] 조작키 안내 
  - [ ] 점스 시스템 구현 (점수, 클리어한 라인 수)
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] 의사 난수 생성 별로인 것 같음.. 좀 더 고민해보기.  
        --> 관련하여 이런 [규칙](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-5.3)도 있으니 참고할 것.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.27)

<details><summary>04.28(금)</summary>

충돌 판정이 다소 아쉬움.. 조사하고 연구 좀 해봐야 할 듯.

터미널 출력 색상 좀 변경해보려고 했는데.. 예상대론 잘 안됨.. 좀 더 알아봐야 할듯.  
디테일에 너무 집착하진 말자.

게임 입력 반응 속도가 느린 게 아쉽다..  
우분투 듀얼 부팅이라도 해야 하나 하..

### Achievements of the day

  - [ ] 조작키 안내 
  - [ ] 점스 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기.
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] 의사 난수 생성 별로인 것 같음.. 좀 더 고민해보기.  
        --> 관련하여 이런 [규칙](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-5.3)도 있으니 참고할 것.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.28)

<details><summary>04.29(토)</summary>

7-bag 시스템 구현해보기.  

이를 구현하는 가장 간단한 방법은.. 길이 7 배열에 테트로미노 심볼들을 나열하고,  
7개를 주기로 이 배열의 요소들을 섞어주는 것 아닐까? 그리고 큐에 이 심볼들을 넣어주는 식?  


### Achievements of the day

  - [X] [7-bag](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#7-bag) 구현
  - [ ] 조작키 안내 
  - [ ] 점스 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기.
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.29)

<details><summary>04.30(일)</summary>

아스키 아트를 지원해주는 아주 신박한 [사이트](https://wepplication.github.io/tools/asciiArtGen/)가 있다.


### Achievements of the day

  - [X] 조작키 안내 
  - [ ] 점수 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기.
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] DAS, ARR ... --> 관련 [링크](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-3.4)
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 04.30)

</blockquote></details>

[//]: # (End of 2023.04)




<font size="3"> <details><summary>2023.05</summary><blockquote> </font>

<details><summary>05.01(월)</summary>

소리 출력 좀 알아 봤는데 만만치 않다. 이건 후순위로 미뤄야 함.  
사실상 커널 프로그래밍임.

### Achievements of the day

오늘 크게 한 건 없음..

  - [ ] 점수 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기. [(2009-가이드라인](https://tetris.fandom.com/wiki/Tetris_Guideline))
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] DAS, ARR 구현해보기 --> 관련 [링크](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-3.4)
  - [ ] 소리(효과음) 출력 알아보기. --> https://www.kernel.org/doc/html/v4.16/sound/kernel-api/index.html
  - [ ] 슬슬 문서화도 신경 써야 할 듯.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 05.01)



<details><summary>05.02(화)</summary>

내일 tetris_play_main_loop.c부터 이어서 리팩토링 하면 됨.

### Achievements of the day

구현한 건 없고 전반적인 코드 리팩토링 함.  
이제는 기능을 더 추가하기엔 애매함.

전반적인 로직, 주요 코드 설명 등 문서화에 신경 쓰고,  
여유되면 또 기능 구현해보는 식으로.

  - [ ] 점수 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기. [(2009-가이드라인](https://tetris.fandom.com/wiki/Tetris_Guideline))
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] DAS, ARR 구현해보기 --> 관련 [링크](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-3.4)
  - [ ] 소리(효과음) 출력 알아보기. --> https://www.kernel.org/doc/html/v4.16/sound/kernel-api/index.html
  - [ ] 슬슬 문서화도 신경 써야 할 듯.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 05.02)


<details><summary>05.03(수)</summary>


### Achievements of the day

코드 리팩토링..  
자소서..랑 병행하기 쉽지 않네.    
어느 정도 내려놔야 할 듯. 욕심 부리지 말기.

  - [ ] 점수 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기. [(2009-가이드라인](https://tetris.fandom.com/wiki/Tetris_Guideline))
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] DAS, ARR 구현해보기 --> 관련 [링크](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-3.4)
  - [ ] 소리(효과음) 출력 알아보기. --> https://www.kernel.org/doc/html/v4.16/sound/kernel-api/index.html
  - [ ] 슬슬 문서화도 신경 써야 할 듯.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 05.03)


<details><summary>05.04(목)</summary>

리팩토링 하면서 느낀 건데 이거 코드 설명을 어떻게 하지?  
쉽지 않아 보임..

### Achievements of the day

  - [ ] 점수 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기. [(2009-가이드라인](https://tetris.fandom.com/wiki/Tetris_Guideline))
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] DAS, ARR 구현해보기 --> 관련 [링크](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-3.4)
  - [ ] 소리(효과음) 출력 알아보기. --> https://www.kernel.org/doc/html/v4.16/sound/kernel-api/index.html
  - [ ] 슬슬 문서화도 신경 써야 할 듯.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 05.04)

<details><summary>05.05(금)</summary>

단순 코드 리팩토링..  

### Achievements of the day

  - [ ] 점수 시스템 구현 (각종 테크닉 점수, 클리어한 라인 수) --> 조사 충분히 해보기. [(2009-가이드라인](https://tetris.fandom.com/wiki/Tetris_Guideline))
  - [ ] 난이도 부여(시간이나 클리어한 라인 수에 따라 낙하 속도 증가)  
        --> 대충 구현해놓긴 했는데 좀 더 체계적으로 설계해보기.
  - [ ] DAS, ARR 구현해보기 --> 관련 [링크](https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4#s-3.4)
  - [ ] 소리(효과음) 출력 알아보기. --> https://www.kernel.org/doc/html/v4.16/sound/kernel-api/index.html
  - [ ] 슬슬 문서화도 신경 써야 할 듯.
  - [ ] 그밖에 버그 있나 확인.

</details>

[//]: # (End of 05.05)


</blockquote></details>

[//]: # (End of 2023.05)