# Requirements Analysis

게임을 설계하여 만들어 본 경험이 없기 때문에  
전문가처럼 체계적이고 디테일한 요구 분석서를 작성하는 건 불가능하다.

요구 사항을 완벽하게 명시한 뒤에 코딩에 돌입하는 것이 아니라,  
설계/구현 루틴을 수없이 돌리는 방식을 택한다.

프로젝트 진행 과정에서 수없이 로직이 뒤바뀔 것이기에  
어느 정도 프로젝트가 진행된 후에 문서화 해볼 예정.

---

## Index

[Best Practice](#best-practice)  

[Tetris Guideline](#tetris-guideline)

[프로그래밍 요구 사항](#프로그래밍-요구-사항)  

[Coding Standard](#coding-standard)  

[Stuff you should look for](#stuff-you-should-look-for)

---

## Best Practice

이 정도 수준까지 구현하는 건 무리겠지만,
참고할 만한 구현물들.

- [TETRIS 99](https://namu.wiki/w/TETRIS%2099)
- [Tetris Effect](https://namu.wiki/w/Tetris%20Effect)
- [TETRIS](https://tetris.com/play-tetris) (아마 오리지널인듯?)

---

## Tetris Guideline

분량이 많은 관계로 [본문](../tetris_guideline.md) 따로 작성.

공식 [테트리스 가이드라인](https://tetris.fandom.com/wiki/Tetris_Guideline)이 있기 때문에 내가 추가적으로 작성할 건 없는 듯.  
다만 가이드라인과 다르게 구현하는 부분도 있을 것이기에 이를 반영하여 작성한다.

---


## 프로그래밍 요구 사항

출처: [우테코 프리코스](https://github.com/woowacourse-precourse/java-lotto#-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D-%EC%9A%94%EA%B5%AC-%EC%82%AC%ED%95%AD)

반드시 지키자는 건 아니다.  
게임 프로그래밍과는 다른 부분도 있을 거다.  
그냥 이런 뉘앙스를 인지하고 프로그래밍 한다 정도?


- indent(인덴트, 들여쓰기) depth를 3이 넘지 않도록 구현한다. 2까지만 허용한다.
  - 예를 들어 while문 안에 if문이 있으면 들여쓰기는 2이다.
  - 힌트: indent(인덴트, 들여쓰기) depth를 줄이는 좋은 방법은 함수(또는 메서드)를 분리하면 된다.

- 3항 연산자를 쓰지 않는다.

- 함수(또는 메서드)의 길이가 15라인을 넘어가지 않도록 구현한다.
  - 함수(또는 메서드)가 한 가지 일만 하도록 최대한 작게 만들어라.

- else 예약어를 쓰지 않는다.
  - 힌트: if 조건절에서 값을 return하는 방식으로 구현하면 else를 사용하지 않아도 된다.
  - else를 쓰지 말라고 하니 switch/case로 구현하는 경우가 있는데 switch/case도 허용하지 않는다.

---

## Coding Standard

* [POCU 아카데미 C++ 코딩 표준](https://docs.popekim.com/ko/coding-standards/pocu-cpp)

### 추가적으로 컨벤션 정의하기  

나 혼자 수행하는 프로젝트이므로 나에게 가장 편한 방식을 정하면 됨.  
결국엔 실수 덜하고 가독성 높이기 위한 방편이니까.

* 배열 인덱싱 변수명에는 가급적 i, j, k, ...을 포함한다. (객체의 좌표 변수(주로 x, y, z을 포함)와 배열 인덱싱 변수를 혼용하지 않도록 하기 위함.)

* `for`문 내부에서 쓰이지 않는 카운트 변수는 `_`(Underscore. under-bar라고도 한다.)로 선언한다.

  대개 `for`문을 아래와 같이 작성하곤 하는데  
  ```c
  for (int i = 0; i < 10; ++i) {
      ...
  }
  ```
  변수 `i`가 중괄호 안에서 쓰이지 않는다면 
  ```c
  for (int _ = 0; _ < 10; ++_) {
      ...
  }
  ```
  이런 식으로 변수를 선언하자는 뜻. (파이썬의 `for _ in range(10)`과 유사)  

  매크로를 사용한다면 아래와 같이 작성할 수도 있겠다.

  ```c
  #define forn(i, n) for (int i = 0; i < n; ++i)

  forn(_, 10) {
      ...
  }
  ```

  `while`문을 이용하는 방법도 있긴 한데, 변수의 범위(scope)가 커지므로 `while`문보다는 `for`문을 선호한다.
  ```c
  int _ = 10;
  while (_-- > 0) {
      ...
  }
  ```

---

## Stuff you should look for

* 어떤 코딩 컨벤션을 사용하든지 정답은 없다.  
  단, 어떤 규칙을 따르기로 했으면 그 일관성을 유지할 것.  
* 사용하지 않는 변수, 함수, 매크로, 클래스(구조체), 열거형은 과감하게 다 지우기. (실수할 여지가 많다.)  
* `assert` 쓰는 걸 주저하지 말자.  
  버그는 일찍 알아챌수록 좋다.
* `char[]`나 `wchar_t[]` 출력할 때 끝에 널 문자(`'\0'`, `L'\0'`) 넣기.  
* `null pointer exception` 유의  
* `exit` 류의 시스템 콜을 사용할 때는 안 닫힌 파일를 비롯하여 정리되지 않은 항목은 없는지 잘 확인해주기.
* 주요 시스템 콜이 실패했는지 확인하는 로직 빼먹지 말고 작성.  
  ```c
  if (smth_syscall(...) == -1) {
      handle_error("smth_syscall() error");
  }
  ```
* 문자열을 출력한다면 `%c` 여러번 보다 버퍼에 모아 두었다가 한번에 `%s` 출력하기.  
* 코드 리뷰가 IDE보다 깃허브에서 더 잘됨;  
  리팩토링 하려면 깃허브에서 보기.
* 객체 지향(OOP)에 지나치게 집착하지 않기.  
  융통성 있게 구현하기.  
* `static` 올바르게 사용하기.  
  1. **race condition**이 없는 각 스레드 고유 변수는 `static`으로 선언하면 안 된다.
  2. 함수에 [자동 변수](https://ko.wikipedia.org/wiki/자동_변수) 주소를 넘겨주는 행위는 멀티 스레딩에서 오작동 할 여지가 있다.  
  `전역`이나 `지역` `static`으로 선언해서 넘겨주는 방식 선호.  
  (메모리 최적화가 필요하다면 `동적 할당`을 사용할 수도 있음)  
* `상수` 일일이 `#define` 하지 말고 `enum` 애용하기. (단 `int`형만 저장할 수 있음에 유의)
* 인수 넘겨줄 때 타입 안맞으면 형변환 하기.
