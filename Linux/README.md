# Linux based Tetris

리눅스(대표적으로 우분투)에서 돌아가는 테트리스 게임을 만들어 보려고 한다.

본 문서는 개발 과정에서 끊임 없이 수정/보완할 예정.

결과물인 안나온 미완성 프로젝트이지만 일단 깃허브에 올려 놓는다.

(원래는 [소켓 프로그래밍 공부](https://github.com/keunbum/connection-to-the-other-world)를 끝내고 프로젝트를 진행하려고 했는데,
당장의 포트폴리오가 시급하기 때문에 동시에 진행.)

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
  - OS: 우분투(WSL)
  - IDE: Visual Studio Code
  - LANG: GNU C11

- 타겟 플랫폼:  
  좁게는 우분투(LTS 20에서 개발하지만 그 이하도 큰 문제 없을듯)에서 넓게는 데비안 기반 리눅스?

---

## 프로젝트 구상

### Q1. 왜 리눅스인가?

실용성, 효용성 측면을 고려한다면 리눅스에서,    
그것도 콘솔 게임을 만드는 건 다분히 포트폴리오 때문.  

굳이 이유를 든다면 (리눅스 상에서 개발하여 얻을 수 있는 이점)

- 내가 요즘 주로 공부하고 있는 내용이 리눅스 기반 소켓 프로그래밍이라서.
- 윈도우즈의 여러 API도 그 원형은 리눅스에서 가져온 것이 많아서.
- 리눅스 관련 프로젝트 경험을 어필할 때 필요할 수 있으니까.

### Q2. 플랫폼은? (다르게 말하면 사용자 인터페이스?) (ex. 웹, 콘솔, GUI, ...)

1. ~~웹(크롬 등의 인터넷 브라우저를 이용)~~
2. ~~Qt (나름의 GUI? 사실 Qt에 대해 잘 모른다. 어설프게 들어보기만 한 정도)~~
3. 터미널(GNOME 터미널 에뮬레이터로 대변되는 bash shell 위에서?)

내 기준에선 크게 세 가지의 선택지가 있는데 이 중 터미널의 방식을 택하려고 한다.

이유는..    
- 웹은 제대로 된 게임을 서비스하기엔 한계가 있으니까.
  - 테트리스 정도면 무리없을 듯.
  - 아님 콘솔에서 만든 게임을 그대로 웹 상으로 포팅하기?
  - 사실 가장 큰 이유는 내가 웹을 잘 몰라서.
- 내가 개발을 WSL로 하고 있으니까.  
  - CLI에서는 GUI 창을 못 띄우니까.
- 상황에 따라 다르겠지만 GUI보다는 구현 난이도나 낮거나 개발 기간이 덜 걸릴 것 같아서.

### Q3. 구체적으로 어떤 라이브러리나 기술을 가져다 만들 것인가?

- 주 개발 언어: GCC 컴파일러
  - 내가 요즘 C언어로 소켓 프로그래밍을 공부하고 있어서.
  - 사실 C++만 되어도 구현 난이도가 한폭 낮아질 거다. OOP, template, STL 등이 워낙 강력하니까.  
  - 그러나, 상대적으로 손이 많이 가는 C언어로 무언가를 만들 수 있다면 그것으로 개발 역량을 보여줄 수 있다고 생각해서.


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

<details><summary>template(문서 작성용)</summary>

### Achievements of the day

</details>

[//]: # (template)

<font size="3"> <details><summary>miscellaneous search</summary><blockquote> </font>

  <details><summary>signal</summary>
  
  signal, sigsuspend 등 이어서 조사하기
  
  </details>  

  <details><summary>abort()와 _Exit()</summary>

  </details>  

  <details><summary>getopt</summary>

  [getopt](https://man7.org/linux/man-pages/man3/pthread_create.3.html)  
  그동안 리눅스 명령행에서 프로그램 실행할 때  
  `-a`나 `--version` 같은 옵션 처리 어떻게 하나 했더니 시스템 콜이 다 있었네...  

  </details>

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

</details>

[//]: # (miscellaneous search)

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
    2. termios.h의 [tcgetattr](https://xn--linux-8yu.die.net/man/3/tcgetattr).  
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

    새로 생성된 스레드의 결과나 종료 상태가 필요하다면 joinable한 스레드를 만들어야 할 것이다.  
    --> `pthread_join` 사용 --> 종료 상태 확인 --> 자원이 환원됨

    detached --> 종료 시 커널(운영체제)이 알아서 자원 회수해 감.  
    억지로 pthread_join을 호출하여 종료 상태를 얻을 수 없다.  

    스레드를 생성하면 디폴트는 joinable로 세팅된다.  
    종료 결과가 필요하지 않은 데몬 스레드들은 detached로 설정하면 되겠다. ([pthread_attr_setdetachstate](https://man7.org/linux/man-pages/man3/pthread_attr_setdetachstate.3.html) 참조)  

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
    - start_routine 함수에서 return 하기  
    - [pthread_cancel](https://man7.org/linux/man-pages/man3/pthread_cancel.3.html)  
    - 프로세스나 임의의 스레드가 [exit](https://man7.org/linux/man-pages/man3/exit.3.html)을 호출하거나,  
      메인 스레드가 main 함수에서 return한 경우 --> 모든 스레드가 종료됨

    새로 생성된 스레드의 signal mask: 그대로 상속, pending signal: 초기화, alternate signal stack: 초기화, CPU-time clock: 0으로 초기화.

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

    main 스레드뿐만 아니라 아무 스레드나 다른 joinable한 스레드와 결합 가능하다.
    
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
    > A.  
    > 
    > In general, multi-processing is a good choice when you have CPU-bound tasks that can benefit from running on multiple cores simultaneously. It’s also a good choice when you want strong isolation between different parts of your program.
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

  ---

  - menu에도 wgotoxy 적용하기
  

  ### Achievements of the day

  </details>

  [//]: # (End of 03.20)

</blockquote></details>

[//]: # (End of 2023.03)


---
