# GXCapIndicator

<img src="https://raw.githubusercontent.com/ItzSelenux/ItzSelenux.github.io/main/res/projects/gxcapindicator.svg" alt="GXCapIndicator Logo" width="111px" />

**GXCapIndicator** is a simple tool for indicating the status of Caps Lock and Num Lock keys in the system tray.

## Features

- [x] Monitor Caps Lock and Num Lock keys
- [x] Toggle Caps Lock and Num Lock with an on-screen button
- [x] Hideable indicators
- [x] Adjustable update rate
- [x] Wayland support (with `Evdev`)

## Installation

To build GXCapIndicator, choose the backend you want to use:

### With Evdev Backend

```sh
make
```

### With X11 Backend

```sh
make WITHX11=1
```

## Backend Differences

GXCapIndicator supports two backends for fetching key status: X11 and Evdev. Each backend has its own capabilities and limitations.

### X11 Backend
- Uses `XkbGetState` to fetch the key status.
- Some options are not available:
  - **Initial Visual State**: Cannot set the initial visual state of Caps Lock/Num Lock (unnecessary with XkbGetState).
  
### Evdev Backend
- Uses `libinput_event_get_keyboard_event` to fetch the key status.
- Some options are not available:
  - **Update Rate**: Polling rate is fixed and cannot be adjusted.
  - **Toggle Functionality**: Can't be implemented without root access.

## Configuration

You can configure GXCapIndicator with the integrated GUI (`settings` in indicator menu) or by editing` $HOME/.config/gxcapindicator` using the following options:

| Item        | Description                          | Possible Values | Default Value | Example     | Scope   |
|-------------|--------------------------------------|-----------------|---------------|-------------|---------|
| `showcap`   | Enables the Caps Lock key indicator  | `0`, `1`        | `1`           | `showcap=1` | All     |
| `shownum`   | Enables the Num Lock key indicator   | `0`, `1`        | `1`           | `shownum=1` | All     |
| `updrate`   | Sets the update rate                 | (Number)        | `0`           | `updrate=0` | X11     |
| `vcapstate` | Sets the initial visual state of Caps Lock | `0`, `1`   | `0`           | `vcapstate=0` | Evdev   |
| `vnumstate` | Sets the initial visual state of Num Lock  | `0`, `1`   | `0`           | `vnumstate=0` | Evdev   |