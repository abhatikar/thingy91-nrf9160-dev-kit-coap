# Thingy:91 / nRF9160 Dev-Kit CoAP Example Code

## How-to: Compiling

### 1. Get the GNU Arm Embedded Toolchain & West

http://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html#installing-the-toolchain

http://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html#installing-west

#### 1.1 Additional Instructions for Windows

| Software | Description                                                                  |
| -------- | ---------------------------------------------------------------------------- |
| `CMake`  | **1.** Download latest stable release: https://cmake.org/download/           |
|          | **2.** Installation instructions... TODO                                     |
|          | **3.** E.g. make sure to check "add to PATH" if asked during installation.   |
| `Ninja`  | **1.** Download latest binary: https://github.com/ninja-build/ninja/releases |
|          | **2.** Place it under C:\ninja\ninja.exe                                     |
|          | **3.** Add to PATH (how?)                                                    |
| `Git`    | **1.** Download and install for Windows: https://git-scm.com/download/win    |

### 2. Get the code

Create a new folder on your computer and run the following command inside of it:

```
west init -m https://github.com/TelenorStartIoT/thingy91-nrf9160-dev-kit-coap
```

This will fetch the correct NCS version based on the `west.yml` file in this repository. Once the command has finished run the following command:

```
west update
```

You may also need to install required Python dependencies:

```
pip3 install -r zephyr/scripts/requirements.txt
pip3 install -r nrf/scripts/requirements.txt
pip3 install -r bootloader/mcuboot/scripts/requirements.txt
```

### 3. Compile

Run the following command from the root of your newly created folder:

```
west build telenor-coap/ -b thingy91_nrf9160ns --pristine
```

Change `thingy91_nrf9160ns` to `nrf9160dk_nrf9160ns` if you want to build for the nRF9160 DK instead of the Thingy:91.

### 4. Find the correct .hex-file

You will find the final product under `build/zephyr/`. Depending on which device you want to flash you must choose the correct .hex-file:

- Thingy:91 with MCUboot: `app_signed.hex`
- nRF9160 DK: `merged.hex`
