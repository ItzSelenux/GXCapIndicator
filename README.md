# gxcapindicator
Simple Cap/Num lock key indicator for x11 tray

## Features:

- [x] Monitor Cap/Num Keys
- [x] Toggle Cap/Num Keys with a on-screen button
- [x] Hiddeable indicators
- [x] Choose update rate
- [ ] Wayland support

## Configuration

| Item | Description | Possible values| Default Value| example
| --- | --- | --- | --- | --- |
| showcap | Enables "Caps Lock" key indicator | 0, 1 | 1 | showcap=1|
| shownum | Enables "Num Lock" key indicator | 0, 1  | 1 | shownum=1 |
| updrate | Set update rate | (Number) | 0 | updrate=0 |

## Build

```
make gxcapindicator
```
