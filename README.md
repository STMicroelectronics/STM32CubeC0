# STM32CubeC0 MCU Firmware Package

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/STM32CubeC0.svg?color=brightgreen)

> [!IMPORTANT]
> This repository contains **submodule**. Please refer to the ["How to"](README.md#how-to-clone-and-get-updates) section for more details.

## Overview

**STM32Cube** is an STMicroelectronics original initiative to ease developers' life by reducing efforts, time and cost.

**STM32Cube** covers the overall STM32 products portfolio. It includes a comprehensive embedded software platform delivered for each STM32 series.
   * The CMSIS modules (core and device) corresponding to the ARM(tm) core implemented in this STM32 product.
   * The STM32 HAL-LL drivers, an abstraction layer offering a set of APIs ensuring maximized portability across the STM32 portfolio.
   * The BSP drivers of each evaluation, demonstration or nucleo board provided for this STM32 series.
   * A consistent set of middleware libraries such as RTOS, USB, Bootloader...
   * A full set of software projects (basic examples, applications, and demonstrations) for each board provided for this STM32 series.

The **STM32CubeC0 MCU Package** projects are directly running on the STM32C0 series boards. You can find in each Projects/*Board name* directories a set of software projects (Applications/Demonstration/Examples).

## Release note

Details about the content of this release are available in the release note [here](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/STM32CubeC0/blob/master/Release_Notes.html).

## How to clone and get updates

This repository contains **submodules**.
* To **clone** it, run the command below
```
git clone --recursive https://github.com/STMicroelectronics/STM32CubeC0.git
```
* To **pull** the latest updates, run the commands below from the root of the repository
```
git pull; git submodule update --init --recursive
```

> [!CAUTION]
> If the "Download ZIP" option is used instead of the `git clone` command, then the different **submodules** have to be collected and added **manually**.

> [!NOTE]
> The latest version of this firmware available on GitHub may be **ahead** of the one available on [st.com](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) or via [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html). This is due to the **rolling release**. Please refer to [this](https://github.com/STMicroelectronics/STM32Cube_MCU_Overall_Offer/discussions/21) post for more details.

## Boards available

  * STM32C0
    * [NUCLEO-C031C6](https://www.st.com/en/evaluation-tools/nucleo-c031c6.html)
    * [STM32C0116-DK](https://www.st.com/en/evaluation-tools/stm32c0116-dk.html)
    * [STM32C0316-DK](https://www.st.com/en/evaluation-tools/stm32c0316-dk.html)

## Troubleshooting

Please refer to the [CONTRIBUTING.md](CONTRIBUTING.md) guide.
