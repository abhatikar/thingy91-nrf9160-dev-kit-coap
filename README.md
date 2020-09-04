# Thingy:91 / nRF9160 Dev-Kit CoAP Example Code

## How-to: Compiling

### 1. Get the GNU Arm Embedded Toolchain & West

http://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html#installing-the-toolchain

http://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html#installing-west

### 2. Get the code

Create a new folder on your computer and run the following command inside of it:

```
west init -m https://github.com/TelenorStartIoT/thingy91-nrf9160-dev-kit-coap
```

This will fetch the correct NCS version based on the `west.yml` file in this repository. Once the command has finished run the following command:

```
west update
```

### 3. Compile

Run the following command from the root of your newly created folder:

```
west build telenor-coap/ -b thingy91_nrf9160ns --pristine
```

Change `thingy91_nrf9160ns` to `nrf9160dk_nrf9160ns` if you want to build for the nRF9160 DK instead of the Thingy:91.

### 4. Find the correct .hex file

You will find the final product under `build/zephyr/`. Depending on which device you want to flash you must choose the correct .hex-file:

- Thingy:91 with MCUboot: `app_signed.hex`
- nRF9160 DK: `merged.hex`
