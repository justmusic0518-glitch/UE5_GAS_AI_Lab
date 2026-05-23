# 프로젝트 구조와 시작 순서

## 문서 위치

앞으로 프로젝트 관련 문서는 전부 아래 폴더에 둔다.

```text
Docs/GAS_AI_Docs
```

현재 기준 문서:

```text
Docs/GAS_AI_Docs/ProjectGoal.md
Docs/GAS_AI_Docs/ProjectStructure.md
```

## 큰 방향

이 프로젝트는 `캐릭터 조작 + GAS 전투 + 보스 AI + SmartObject NPC`를 따로따로 만들고, 마지막에 하나의 흐름으로 연결한다.

처음부터 마을, 보스, GAS, AI를 동시에 만들지 않는다. 먼저 플레이어가 움직이고 공격할 수 있어야 나머지 시스템이 의미를 가진다.

우선순위는 다음과 같다.

```text
1. 플레이어 캐릭터 조작, 카메라, 기본 전투감
2. GAS 전투 구조
3. 보스 캐릭터와 보스 AI 패턴
4. SmartObject 기반 NPC 상호작용
5. 맵 꾸미기, 사운드, VFX, UI
```

## C++ 폴더 구조

권장 C++ 구조는 다음과 같다.

```text
Source/GAS_AI_Prototype
├─ AbilitySystem
│  ├─ Abilities
│  ├─ Attributes
│  ├─ Components
│  └─ Effects
├─ AI
│  ├─ Boss
│  ├─ NPC
│  └─ Tasks
├─ Characters
│  ├─ Base
│  ├─ Player
│  ├─ Boss
│  └─ NPC
├─ Components
├─ Data
├─ Game
├─ Interaction
└─ UI
```

처음부터 모든 폴더와 클래스를 만들 필요는 없다. 실제 구현이 생기는 순서대로 만든다.

## 주요 C++ 클래스 후보

### 캐릭터

```text
ACombatCharacterBase
```

플레이어와 보스가 공유할 전투 베이스.

담당:

- AbilitySystemComponent 보유 또는 접근
- AttributeSet 보유
- 피격 처리
- 사망 처리
- 공통 GameplayTag 확인

```text
AGASAIPlayerCharacter
```

플레이어 캐릭터.

담당:

- Enhanced Input
- 이동
- 카메라
- 락온
- 공격 입력
- 회피 입력

```text
ABossCharacter
```

보스 캐릭터.

담당:

- 보스 HP
- 보스 공격 Montage
- 페이즈 전환
- AI에서 Ability 실행 가능하도록 연결

```text
ANPCCharacter
```

마을 NPC.

담당:

- AI 이동
- 상호작용 애니메이션
- SmartObject 사용 흐름

### GAS

```text
UGASAIAbilitySystemComponent
```

필요할 때만 만든다. 처음에는 기본 `UAbilitySystemComponent`로 시작해도 된다.

```text
UCombatAttributeSet
```

담당:

- Health
- MaxHealth
- Stamina
- MaxStamina

```text
UGASGameplayAbilityBase
```

모든 Ability의 공통 베이스.

담당:

- 공통 태그 체크
- CommitAbility 처리
- 종료 처리 규칙

초기 Ability 후보:

```text
UGA_PlayerAttack
UGA_PlayerDodge
UGA_BossPatternBase
```

### AI

```text
ABossAIController
```

보스 BehaviorTree와 Blackboard 실행.

```text
UBossPatternDataAsset
```

보스 패턴 조건과 정보를 담는 데이터.

담당:

- 패턴 Ability
- 최소 거리
- 최대 거리
- 쿨타임
- 페이즈 조건
- 우선순위

```text
UBossPatternSelector
```

가능한 패턴 중 현재 상황에 맞는 패턴을 고르는 로직.

```text
UNPCSmartObjectInteractorComponent
```

NPC가 SmartObject를 찾고 사용하는 흐름을 담당.

담당:

- SmartObject 검색
- 슬롯 예약
- 슬롯 위치로 이동 요청
- 상호작용 시작
- 슬롯 해제

## Content 폴더 구조

언리얼 에셋은 `Content/_Project` 아래에 모은다.

```text
Content/_Project
├─ AI
│  ├─ BehaviorTrees
│  ├─ Blackboards
│  └─ StateTrees
├─ Animations
│  ├─ Player
│  ├─ Boss
│  └─ NPC
├─ Characters
│  ├─ Player
│  ├─ Boss
│  └─ NPC
├─ GAS
│  ├─ Abilities
│  ├─ Effects
│  └─ Cues
├─ Maps
│  ├─ Village
│  └─ BossArena
├─ SmartObjects
├─ UI
├─ Audio
└─ VFX
```

외부 무료 에셋은 가능하면 아래처럼 분리한다.

```text
Content/External
```

직접 만든 프로젝트 에셋과 외부 에셋을 섞지 않는다.

## 플러그인과 모듈

초기부터 필요한 것:

```text
EnhancedInput
GameplayAbilities
GameplayTags
GameplayTasks
AIModule
```

마을 NPC 단계에서 필요한 것:

```text
StateTree
GameplayStateTree
SmartObjects
GameplayInteractions
```

처음부터 SmartObject 관련 플러그인을 다 켜도 되지만, 구현 순서는 뒤로 둔다.

## 시작 순서

### 0단계 - 프로젝트 기준 정리

- 문서는 `Docs/GAS_AI_Docs`에 둔다.
- 에셋은 `Content/_Project`에 둔다.
- 외부 에셋은 `Content/External`에 둔다.
- C++ 클래스는 기능별 폴더에 둔다.

### 1단계 - 모듈과 플러그인 세팅

- `Build.cs`에 GAS와 AI 관련 모듈을 추가한다.
- `.uproject`에 필요한 플러그인을 켠다.
- 프로젝트가 빌드되는지 확인한다.

이 단계의 성공 기준:

```text
에디터 실행 가능
C++ 빌드 성공
GameplayAbilities 관련 include 가능
```

### 2단계 - 플레이어 캐릭터 기초

- `ACombatCharacterBase` 생성
- `AGASAIPlayerCharacter` 생성
- Enhanced Input 연결
- 이동 구현
- 카메라 구현
- 테스트 맵에서 캐릭터 조작 확인

이 단계에서는 GAS를 깊게 넣지 않는다. 먼저 캐릭터가 안정적으로 움직여야 한다.

### 3단계 - GAS 최소 구조

- `UCombatAttributeSet` 생성
- Health, MaxHealth, Stamina, MaxStamina 추가
- 캐릭터에 AbilitySystemComponent 연결
- BeginPlay 또는 Possessed 시점에 ASC 초기화
- 기본 Attribute 초기화

이 단계의 성공 기준:

```text
플레이어가 ASC를 가진다.
플레이어가 HP와 Stamina를 가진다.
로그 또는 디버그 UI로 Attribute 값을 확인할 수 있다.
```

### 4단계 - 공격과 회피

- 공격 GameplayAbility 생성
- 회피 GameplayAbility 생성
- AnimMontage 연결
- AnimNotify 시점에 Trace 판정 실행
- GameplayTag로 공격 중/회피 중 상태 제어

이 단계의 성공 기준:

```text
공격 입력으로 Montage가 재생된다.
Notify 타이밍에 Trace가 나간다.
회피 중에는 공격이 막히거나, 공격 중에는 회피가 막히는 식의 상태 제어가 된다.
```

### 5단계 - 보스

- `ABossCharacter` 생성
- 보스도 GAS 구조 연결
- 보스 HP 구현
- BehaviorTree와 Blackboard 생성
- PatternSelector로 3개 패턴 실행

### 6단계 - 마을 NPC

- SmartObject 5개 제작
- NPC 3명 제작
- NPC가 SmartObject를 찾아 이동
- 예약, 사용, 해제 흐름 구현
- 상호작용 애니메이션 연결

## 지금 당장 시작할 일

가장 먼저 할 일은 다음 두 가지다.

```text
1. Build.cs와 uproject에 GAS/AI 플러그인 세팅
2. ACombatCharacterBase와 AGASAIPlayerCharacter 생성
```

이 두 개가 끝나면 프로젝트의 뼈대가 생긴다. 그 다음부터 이동, 카메라, GAS를 순서대로 붙인다.
