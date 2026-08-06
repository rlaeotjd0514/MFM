# MFM — 개인 트레이딩 시스템 (진행 중)

C++로 트레이딩 시스템의 구조를 직접 설계해보기 위한 개인 학습 프로젝트.

## 현재 구현 범위
- OKX 무기한 선물 실시간 시세 WebSocket 스트림 수신

## 구조

| 모듈 | 역할 |
|---|---|
| NetworkEngineLib | 네트워크 I/O 계층 |
| TradeCenterConnector | 거래소별 커넥터 추상화 |
| DataManager | 시세/체결 데이터 관리 |
| TradeLogic | 전략 실행 로직 |
| BackTester | 백테스팅 |

## 개발 환경
C++17 / CMake / vcpkg / Qt6

## 진행 예정
- (여기에 로드맵)
