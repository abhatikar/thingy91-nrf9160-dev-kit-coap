# Thingy:91 / nRF9160 Dev-Kit CoAP Example Code

## How-to: Compiling

### 1. Get the GNU Arm Embedded Toolchain & West

Follow each step for your operating system in the Nordic semiconductor guide:

- [Toolchain](http://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html#installing-the-toolchain)

- [West](http://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html#installing-west)

- Additional instructions for Windows [here](./README_WIN.md)

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

### 4. Flash

You will find the final product under `build/zephyr/`. Depending on which device you want to flash you must choose the correct .hex-file:

- Thingy:91 with MCUboot: `app_signed.hex`
- nRF9160 DK: `merged.hex`

#### Flash Thingy:91

Use the nRF Connect Programmer desktop application to flash Thingy:91 in MCUboot mode with the `app_signed.hex` file.

#### Flash nRF9160 DK

Run the following command while the nRF9160 DK is connected via a USB cable:

```
west flash
```
