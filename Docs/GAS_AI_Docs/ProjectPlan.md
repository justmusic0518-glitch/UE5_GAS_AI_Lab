# GAS_AI_Prototype 4일 초압축 MVP 실행 계획

## 기준

- 시작일: 2026-05-27 수요일
- 1차 종료일: 2026-05-30 토요일
- 기준 시간대: Asia/Seoul
- 목표 형태: 4일 안에 `플레이어 GAS 전투 -> 보스 3패턴 -> NPC/게이트 -> 전체 루프`를 한 번 이어붙인다.
- 운영 원칙: 일단 과하게 잡는다. 못 하면 나중에 늘리고, 지금은 느슨하게 잡지 않는다.

이 계획은 현실적인 일정표가 아니라, 현재 속도를 기준으로 일부러 세게 잡은 압축 훈련표다.  
하루 안에 끝낼 수 있는 작업만 적는 것이 아니라, 하루를 끝까지 밀었을 때 닿아야 하는 상한선을 같이 적는다.

핵심 목표는 아래다.

```text
플레이어가 이동, 카메라, 락온, 공격, 회피를 모두 사용한다.
공격과 회피는 GameplayAbility로 실행된다.
공격은 Montage 또는 임시 애니메이션 타이밍에서 Trace를 발생시킨다.
Trace가 맞으면 GameplayEffect 또는 명확한 Damage 경로로 HP를 줄인다.
보스는 HP를 가지고 3개 패턴을 선택해 실행한다.
보스 패턴은 예고, 판정, 피해 적용을 가진다.
NPC는 SmartObject 또는 대체 상호작용 루프를 가진다.
플레이어는 게이트/트리거를 통해 보스전으로 들어간다.
시작부터 승리/패배까지 한 번 이어진다.
```

## 4일 MVP 성공 기준

1. PIE에서 플레이어가 정상 스폰되고 Move/Look/LockOn/Attack/Dodge를 사용할 수 있다.
2. 플레이어와 보스가 ASC와 AttributeSet을 가진다.
3. `InitAbilityActorInfo`가 호출되고, Owner/Avatar 구조를 설명할 수 있다.
4. 플레이어에게 Attack/Dodge Ability가 부여된다.
5. 입력으로 Attack/Dodge Ability가 실행된다.
6. Attack Ability가 Montage 또는 임시 공격 타이밍을 사용한다.
7. 공격 판정이 실제 대상 HP를 감소시킨다.
8. Dodge Ability 중 짧은 무적 또는 피격 무시 상태가 있다.
9. 보스가 3개 패턴 중 하나를 조건에 따라 선택한다.
10. 보스 패턴이 플레이어에게 피해를 줄 수 있다.
11. NPC 1명 이상이 상호작용 루프를 돈다.
12. 보스 게이트 또는 트리거로 보스전 흐름에 들어간다.
13. 플레이어 HP, Stamina, 보스 HP, 현재 상태가 로그 또는 최소 UI로 확인된다.
14. 전체 루프가 시작부터 승리/패배까지 한 번 이어진다.
15. 구현 구조와 남은 문제를 문서로 설명할 수 있다.

## 이번 4일 동안 버릴 것

- 예쁜 UI
- 고급 카메라 보간
- 완성형 락온 UI
- 입력 버퍼
- 콤보
- 정교한 Stamina 회복
- 좋은 애니메이션 퀄리티
- 자연스러운 보스 이동
- 멋진 VFX/SFX
- 대화 시스템
- 복잡한 SmartObject/StateTree 구조
- 대규모 마을 NPC
- 정교한 BehaviorTree
- 완성형 맵

단, 아래는 버리지 않는다.

```text
1. Ability로 공격/회피가 실행되는 구조
2. Trace 또는 판정으로 HP가 감소하는 구조
3. 보스 패턴 3개
4. 전체 플레이 루프
```

## 일정 상태 판단 기준

자동 점검은 아래 기준으로 판단한다.

```text
정상:
오늘 최소 완료 기준이 PIE 또는 빌드 기준으로 확인되었다.

미달 0.5일:
코드는 있지만 BP 할당, 에디터 연결, PIE 검증 중 하나가 비어 있다.

미달 1일:
오늘 핵심 기능이 코드상으로도 이어지지 않았다.

미달 2일 이상:
전날 핵심 기능이 없어서 오늘 목표를 시작할 수 없다.

빠름 0.5일:
오늘 목표가 검증되고 내일 목표의 코드 뼈대가 들어갔다.

빠름 1일 이상:
내일 목표도 PIE에서 최소 검증되었다.
```

파일 존재 여부만으로 완료 처리하지 않는다.  
특히 BP 변수 할당, MappingContext 등록, ASC 초기화, Ability 부여, GameplayEffect 적용, Montage/Notify/Trace 연결, 보스 패턴 판정, NPC 루프 실제 실행을 본다.

## 2026-05-27 수 - 플레이어 전투 세로 조각 완성

오늘 목표는 단순 Move/Look이 아니다.  
Move/Look은 이미 진행된 상태로 보고, 오늘 안에 플레이어 전투의 최소 세로 조각을 만든다.

목표:

- 플레이어 스폰, 카메라, Move/Look을 PIE에서 확정한다.
- 락온을 만든다.
- ASC와 AttributeSet을 초기화한다.
- GameplayTag와 Ability 베이스를 만든다.
- Attack/Dodge Ability를 만들고 입력에서 실행한다.
- 임시 애니메이션 또는 Montage를 연결한다.
- 공격 Trace로 더미 또는 보스 후보의 HP를 줄인다.
- Dodge 중 피해 무시 상태를 만든다.

작업:

- `BossMap`의 GameMode가 실제로 `BP_CombatGameMode` 또는 `ACombatGameMode`를 쓰는지 확인한다.
- `BP_CombatPlayerCharacter`가 실제 Pawn으로 스폰되는지 확인한다.
- `playerCharacterInputConfig`와 `characterIMC`가 BP에 할당되어 있는지 확인한다.
- Move/Look 축을 PIE에서 확인하고, 뒤집혔으면 즉시 수정한다.
- `InputMove`에서 Forward/Right 축 사용이 IA_Move 설정과 맞는지 확인한다.
- 캐릭터 회전 정책을 정리한다.
  - 평상시: 이동 방향 회전
  - 락온 중: 타겟 방향 회전
- `IA_LockOn`, `IA_Attack`, `IA_Dodge`를 만든다.
- 임시 LockOnTarget, DummyTarget, 또는 Boss 후보 Actor를 만든다.
- 가장 가까운 대상 찾기, 락온 설정, 락온 해제를 구현한다.
- 락온 중 현재 타겟 이름과 거리를 로그로 출력한다.
- `InitAbilityActorInfo`를 호출한다.
- Health, MaxHealth, Stamina, MaxStamina를 로그로 출력한다.
- GameplayTag 목록을 만든다.
  - `State.LockOn`
  - `State.Attacking`
  - `State.Dodging`
  - `State.Invincible`
  - `State.Hit`
  - `State.Dead`
  - `Ability.Attack`
  - `Ability.Dodge`
- `UGASGameplayAbilityBase` 또는 프로젝트 이름에 맞는 Ability 베이스를 만든다.
- 플레이어에게 시작 Ability를 부여한다.
- Attack Ability를 만든다.
- Dodge Ability를 만든다.
- 입력에서 ASC를 통해 Attack/Dodge Ability를 실행한다.
- 임시 공격 애니메이션을 찾는다.
  - 있으면 Montage로 만든다.
  - 없으면 임시 Montage 또는 타이머 기반 공격 타이밍으로 대체한다.
  - 애니메이션 찾기에 30분 이상 쓰지 않는다.
- Attack Ability 실행 중 공격 타이밍에 Trace를 발생시킨다.
- Trace 범위를 DrawDebug로 확인한다.
- Trace가 맞은 대상 이름을 로그로 출력한다.
- Damage GameplayEffect를 만들거나, 오늘 안에 막히면 명확한 임시 Damage 함수로 HP 감소를 먼저 확인한다.
- 대상 HP 감소를 로그로 확인한다.
- Dodge Ability 중 `State.Invincible` 또는 피격 무시 상태를 적용한다.

최소 완료 기준:

- PIE에서 플레이어가 보인다.
- Move/Look이 동작한다.
- LockOn 키로 대상이 잡히고 해제된다.
- 플레이어 ASC가 초기화되고 HP/Stamina가 로그로 보인다.
- Attack 키로 Attack Ability가 실행된다.
- Dodge 키로 Dodge Ability가 실행된다.
- 공격 타이밍에 Trace가 발생한다.
- Trace가 대상 HP를 줄인다.
- Dodge 중 피해 무시 상태가 확인된다.
- 빌드가 통과한다.

빡센 목표:

- 공격은 Montage 기반으로 실행한다.
- 공격 중 `State.Attacking`, 회피 중 `State.Dodging`/`State.Invincible` 태그가 정확히 붙고 빠진다.
- Ability 실패 이유를 로그로 남긴다.
- 같은 공격에서 같은 대상을 여러 번 때리지 않도록 막는다.
- 플레이어 HP/Stamina를 화면 로그 또는 임시 UI로 볼 수 있게 한다.

추가 도전:

- Damage를 GameplayEffectSpecHandle로 적용한다.
- Dodge Stamina Cost를 GameplayEffect로 처리한다.
- 락온 중 공격 방향이 타겟을 향하게 만든다.
- 오늘 TIL에 `Enhanced Input`, `ASC Owner/Avatar`, `GameplayAbility 실행 흐름`, `AnimNotify/Trace`를 정리한다.

오늘 끝나면 설명할 수 있어야 하는 것:

- InputAction과 MappingContext 차이
- `BindAction`과 Ability 실행 연결 방식
- ASC Owner Actor와 Avatar Actor 차이
- Ability를 부여하는 것과 실행하는 것의 차이
- GameplayTag가 bool보다 나은 이유
- Montage/Notify/Trace가 공격 판정으로 이어지는 흐름

오늘 버릴 것:

- 좋은 공격 애니메이션 찾기
- 완성형 이펙트
- 콤보
- 카메라 고급 보정
- 완성형 UI

## 2026-05-28 목 - 보스 캐릭터, 보스 GAS, 보스 3패턴 1차 완성

목표:

- 보스를 만든다.
- 보스가 HP와 ASC를 가진다.
- 플레이어 공격으로 보스 HP가 감소한다.
- 보스가 3개 패턴을 선택하고 실행한다.
- 보스 패턴이 플레이어에게 피해를 준다.

작업:

- `ABossCharacter`를 만든다.
- `ACombatCharacterBase`를 상속한다.
- 보스 ASC와 AttributeSet을 초기화한다.
- 보스 HP를 플레이어보다 크게 설정한다.
- 보스를 맵에 배치한다.
- 보스를 락온 대상으로 인식하게 만든다.
- 플레이어 공격으로 보스 HP가 감소하는지 확인한다.
- `ABossAIController`를 만들거나, 4일 압축용 C++ StateMachine/Timer를 먼저 만든다.
- Pattern 정보를 담는 struct 또는 DataAsset을 만든다.
  - 이름
  - 최소 거리
  - 최대 거리
  - 쿨다운
  - 우선순위
  - 실행 함수 또는 Ability
- PatternSelector를 만든다.
- 거리와 쿨다운 기준으로 실행 가능한 패턴을 고른다.
- 패턴 1: 근접 베기 또는 내려찍기
- 패턴 2: 돌진 또는 전방 찌르기
- 패턴 3: 원형 범위 또는 장판 공격
- 각 패턴에 예고 시간을 둔다.
- 예고 중 DrawDebug 또는 임시 표시로 공격 범위를 보여준다.
- 각 패턴이 플레이어에게 Damage를 적용하게 만든다.
- 플레이어 Dodge 중이면 피해를 무시하게 만든다.
- 보스 패턴 실행 중에는 다음 패턴을 고르지 않게 한다.
- 보스 HP 0 이하 사망 처리를 만든다.
- 플레이어 HP 0 이하 사망 처리를 만든다.

최소 완료 기준:

- 보스가 맵에 있다.
- 보스 HP가 확인된다.
- 플레이어 공격으로 보스 HP가 감소한다.
- 보스가 3개 패턴 후보 중 하나를 선택한다.
- 3개 패턴이 각각 실행 가능하다.
- 각 패턴에는 예고, 판정, 피해 적용이 있다.
- Dodge 중 최소 1개 보스 패턴 피해를 무시할 수 있다.
- 플레이어 사망과 보스 사망 로그가 있다.
- 빌드가 통과한다.

빡센 목표:

- 보스 패턴을 GameplayAbility로 실행한다.
- PatternSelector가 거리와 쿨다운을 모두 본다.
- 보스 HP 50% 이하에서 패턴 우선순위가 바뀐다.
- 보스가 락온 타겟으로 안정적으로 잡힌다.
- 보스전 시작부터 사망까지 한 번 플레이된다.

추가 도전:

- BehaviorTree/Blackboard로 최소 실행까지 연결한다.
- PatternData를 DataAsset으로 분리한다.
- 보스 공격도 GameplayEffect로 통일한다.
- 보스 패턴별 Debug 색상을 다르게 표시한다.

오늘 끝나면 설명할 수 있어야 하는 것:

- BossCharacter와 BossAIController 역할 차이
- PatternSelector가 BehaviorTree와 어떻게 연결될 수 있는지
- 거리/쿨다운/우선순위가 패턴 선택에 왜 필요한지
- 플레이어 공격 Damage와 보스 공격 Damage를 같은 구조로 처리하는 이유

오늘 버릴 것:

- 자연스러운 보스 추적 이동
- 좋은 보스 애니메이션
- 2페이즈 연출
- 복잡한 BT 설계
- 보스 밸런스

## 2026-05-29 금 - NPC 상호작용, 보스 게이트, 전체 흐름 연결

목표:

- 전투 테스트를 맵 흐름으로 확장한다.
- NPC 상호작용 루프를 만든다.
- 게이트 또는 Trigger로 보스전에 진입한다.
- 시작부터 보스전 진입까지 흐름을 만든다.

작업:

- SmartObject 관련 플러그인 상태를 확인한다.
  - `SmartObjects`
  - `StateTree`
  - `GameplayStateTree`
  - `GameplayInteractions`
- SmartObject가 1시간 이상 막히면 즉시 대체 루프로 전환한다.
- 대체 루프는 아래 구조로 만든다.
  - NPC Idle
  - 상호작용 지점 후보 찾기
  - 예약
  - 이동 또는 즉시 상태 전환
  - 사용 중 상태
  - 해제
  - 다시 Idle
- NPC 1명을 만든다.
- 상호작용 지점 3개를 만든다.
  - 앉기
  - 게시판 보기
  - 캠프파이어 대기
- 예약/사용/해제 로그를 만든다.
- NPC 1명 루프가 돌면 NPC 3명으로 늘린다.
- 같은 지점을 동시에 쓰지 못하게 한다.
- 보스 게이트 Actor 또는 Trigger를 만든다.
- 플레이어가 게이트에 닿거나 상호작용하면 보스전이 시작되게 한다.
- 보스전 시작 위치를 정한다.
- 보스전 시작 시 플레이어 HP, Stamina, 보스 HP를 초기화하거나 확인한다.
- 보스전 중 플레이어/보스 HP를 로그 또는 화면에 표시한다.
- 승리/패배 조건을 화면 로그로 표시한다.

최소 완료 기준:

- NPC 1명이 상호작용 루프를 돈다.
- 상호작용 지점 3개가 있다.
- 예약/사용/해제 개념이 로그로 확인된다.
- 플레이어가 게이트 또는 Trigger로 보스전에 들어간다.
- 보스전 시작 시 보스와 플레이어 상태가 정상이다.
- 보스전 승리/패배 조건이 확인된다.
- 빌드가 통과한다.

빡센 목표:

- NPC 3명이 동시에 루프를 돈다.
- 실제 SmartObject를 사용한다.
- 보스 게이트도 SmartObject로 처리한다.
- 마을 구역과 보스 구역을 명확히 나눈다.
- 플레이어가 마을에서 시작해 보스전 종료까지 한 번에 이어진다.

추가 도전:

- NPC 상태를 StateTree로 관리한다.
- NPC별 선호 행동을 다르게 준다.
- 게이트 진입 전후로 GameMode 또는 Subsystem에서 전투 상태를 관리한다.
- 최소 UMG로 HP/Stamina/LockOn/보스 HP를 표시한다.

오늘 끝나면 설명할 수 있어야 하는 것:

- SmartObject의 예약/사용/해제 개념
- SmartObject가 막혔을 때 대체 루프를 만드는 이유
- Trigger와 SmartObject 게이트의 차이
- NPC AI와 보스 AI의 목표 차이

오늘 버릴 것:

- 대화 UI
- NPC 감정 표현
- 예쁜 마을
- 복잡한 길찾기
- 완성형 StateTree

## 2026-05-30 토 - 통합, 디버그 UI, 문서화, 다음 단계 재계획

목표:

- 4일 동안 만든 기능을 하나의 플레이 루프로 묶는다.
- 막히는 지점을 제거하고, 어디가 임시 구현인지 문서화한다.
- 다음 단계에서 깊게 팔 방향을 정한다.

작업:

- 전체 루프를 처음부터 끝까지 플레이한다.
  - 플레이어 시작
  - Move/Look
  - LockOn
  - Attack Ability
  - Dodge Ability
  - NPC 상호작용 확인
  - 보스 게이트 진입
  - 보스 패턴 3개
  - 피해 적용
  - 승리 또는 패배
- Debug 로그를 정리한다.
- BP 변수 미할당 시 경고를 추가한다.
- `playerCharacterInputConfig`, `characterIMC`, 시작 Ability, Attribute 초기화가 비어 있으면 바로 알 수 있게 한다.
- 최소 UI 또는 화면 Debug Text를 만든다.
  - 플레이어 HP
  - 플레이어 Stamina
  - 보스 HP
  - LockOn 대상
  - 현재 Ability/상태 태그
- 빌드 또는 에디터 컴파일을 통과시킨다.
- `ProjectStructure.md`와 실제 폴더 구조 차이를 정리한다.
- README 초안을 작성한다.
- 4일 결과를 `ProjectTIL`에 정리한다.
- 남은 문제를 우선순위로 나눈다.
  - 즉시 막는 문제
  - 조작감 문제
  - GAS 구조 문제
  - 보스 AI 구조 문제
  - NPC/SmartObject 문제
  - 애니메이션/콘텐츠 문제
- 다음 계획을 다시 잡는다.
  - GAS 심화
  - 보스 AI 심화
  - SmartObject/StateTree 정리
  - 조작감/애니메이션 정리

최소 완료 기준:

- 시작부터 승리/패배까지 한 번 이어진다.
- 플레이어와 보스 HP 변화가 확인된다.
- Attack/Dodge/BossPattern/NPC/Gate가 한 루프 안에서 확인된다.
- 빌드가 통과한다.
- README 또는 문서에 현재 구조와 남은 문제가 기록된다.
- 다음 계획의 방향이 정해진다.

빡센 목표:

- 전체 루프를 영상으로 녹화할 수 있을 정도로 안정화한다.
- 보스전이 3회 연속으로 중간에 터지지 않는다.
- Debug UI만 보고도 현재 상태를 이해할 수 있다.
- 임시 구현과 나중에 고칠 구현을 코드/문서에서 구분한다.

추가 도전:

- GameplayDebugger 카테고리를 만든다.
- GameplayCue 또는 최소 VFX/SFX를 붙인다.
- 보스 패턴 데이터를 DataAsset으로 정리한다.
- NPC SmartObject를 실제 플러그인 구조로 재시도한다.

오늘 끝나면 설명할 수 있어야 하는 것:

- 전체 전투 루프가 어떤 클래스들을 거쳐 흐르는지
- 입력에서 Ability, Montage, Trace, Damage까지 이어지는 경로
- 보스 패턴 선택과 피해 적용 경로
- NPC 상호작용과 게이트 흐름
- 다음에 리팩터링해야 할 부분

오늘 버릴 것:

- 새 기능 욕심
- 대규모 리팩터링
- 완성형 UI
- 연출 퀄리티

## 날짜별 산출물 요약

```text
05-27:
플레이어 Move/Look/LockOn/ASC/Tag/AttackAbility/DodgeAbility/Montage 또는 임시 공격 타이밍/Trace/Damage까지 확인

05-28:
BossCharacter/Boss ASC/Boss HP/Boss PatternSelector/보스 3패턴/플레이어 피격/보스 사망/플레이어 사망 확인

05-29:
NPC 상호작용 루프/상호작용 지점 3개/예약 사용 해제/보스 게이트/마을에서 보스전 진입/승패 흐름 확인

05-30:
전체 루프 통합/최소 UI 또는 화면 로그/디버그 정리/README/TIL/다음 계획 확정
```

## 매일 끝날 때 기록할 것

매일 아래 내용을 `ProjectTIL` 또는 별도 Daily Log에 적는다.

```text
오늘 실제로 동작한 것:
PIE에서 확인한 것:
코드만 있고 아직 검증 못 한 것:
내일 첫 작업:
오늘 헷갈린 개념:
내일 Codex에게 리뷰받을 부분:
억지로 붙인 임시 구현:
나중에 반드시 고칠 구현:
```

## 터졌을 때 줄이는 순서

이 계획은 일부러 과하다. 터지면 아래 순서로 줄인다.

1. UI를 로그와 DrawDebug로 대체한다.
2. 애니메이션을 임시 Montage 또는 타이머 기반 공격 타이밍으로 대체한다.
3. SmartObject가 막히면 커스텀 상호작용 루프로 대체한다.
4. BehaviorTree가 막히면 C++ Timer/StateMachine으로 대체한다.
5. 보스 이동이 막히면 제자리 보스로 유지한다.
6. NPC 3명이 막히면 NPC 1명으로 줄인다.
7. 그래도 막히면 게이트는 Trigger로 처리한다.

하지만 아래는 줄이지 않는다.

```text
1. 플레이어 Attack/Dodge Ability
2. 공격 판정으로 HP 감소
3. 보스 3패턴
4. 시작부터 승리/패배까지 이어지는 루프
```

## 빠르게 끝났을 때 추가 목표

하루 목표를 빨리 끝내면 아래 순서로 더 한다.

1. BP 변수 미할당 경고를 추가한다.
2. Ability 실패 이유 로그를 추가한다.
3. Debug UI를 만든다.
4. TIL에 개념을 정리한다.
5. README에 구조를 적는다.
6. 다음 날짜의 최소 완료 기준을 먼저 끝낸다.
7. 조작감과 카메라를 다듬는다.
8. GameplayEffect/GameplayTag 사용을 더 정석화한다.
9. 보스 패턴 데이터를 DataAsset으로 옮긴다.
10. SmartObject를 실제 플러그인 방식으로 재시도한다.

## 기술 판단 우선순위

헷갈리면 아래 순서로 판단한다.

```text
1. 지금 PIE에서 확인 가능한가?
2. 전체 루프를 앞으로 밀어주는가?
3. GAS/AI/SmartObject 학습에 직접 도움이 되는가?
4. 나중에 설명 가능한 구조인가?
5. 보기 좋은가?
```

보기 좋은 것보다 연결이 먼저다.  
하지만 연결된 뒤에는 반드시 왜 그렇게 만들었는지 설명할 수 있어야 한다.

## 자동 점검에서 특히 봐야 할 위험

- Move/Look 코드는 있는데 BP InputConfig가 비어 있는 상태
- MappingContext가 LocalPlayer에 등록되지 않은 상태
- GameMode가 실제 맵에 적용되지 않은 상태
- ASC는 있는데 `InitAbilityActorInfo`가 없는 상태
- AttributeSet은 있는데 Ability/Effect에서 쓰지 않는 상태
- Ability 클래스는 있는데 플레이어에게 부여되지 않은 상태
- 입력은 있는데 ASC를 통해 Ability가 실행되지 않는 상태
- Attack Ability는 있는데 Montage/Trace/Damage로 이어지지 않는 상태
- 애니메이션을 찾느라 기능 구현이 멈춘 상태
- Trace는 있는데 같은 대상을 여러 번 때리는 상태
- Damage Effect는 있는데 Health 감소가 확인되지 않는 상태
- Dodge는 있는데 무적/피격 무시가 없는 상태
- 보스는 있는데 플레이어 공격으로 HP가 줄지 않는 상태
- 보스 패턴 이름만 있고 예고/판정/피해가 없는 상태
- 보스 패턴 3개가 실제로 서로 다른 조건을 가지지 않는 상태
- NPC 파일만 있고 맵에서 루프가 돌지 않는 상태
- SmartObject 학습에 막혀 전체 루프가 멈춘 상태
- 게이트가 없어서 마을과 보스전이 연결되지 않는 상태
- 문서 계획과 실제 구조가 계속 어긋나는 상태

## 4일 종료 후 재계획 기준

2026-05-30 종료 시점에 아래 셋 중 하나로 다음 계획을 다시 잡는다.

```text
성공:
전체 루프가 시작부터 승리/패배까지 이어진다.
다음 계획은 GAS 정석화, 보스 AI 심화, SmartObject 정리, 조작감 개선으로 간다.

부분 성공:
플레이어 GAS 전투와 보스전은 되지만 NPC/게이트/문서가 약하다.
다음 계획은 통합 안정화와 문서화를 먼저 한다.

위험:
입력, ASC, Ability, Damage 중 하나가 아직 막혀 있다.
다음 계획은 범위를 줄이고 플레이어 GAS 전투 세로 조각을 완성하는 데 집중한다.
```
