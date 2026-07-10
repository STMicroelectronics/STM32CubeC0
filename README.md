# STM32CubeC0 MCU Firmware

![tag](https://img.shields.io/badge/tag-v1.4.1-brightgreen.svg)
[![release note](https://img.shields.io/badge/release_note-view_html-gold.svg)](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/STM32CubeC0/blob/main/Release_Notes.html)
[![offer](https://img.shields.io/badge/stm32cube_mcu_offer-browse-orange.svg)](https://github.com/STMicroelectronics/STM32Cube_MCU_Overall_Offer)

> [!IMPORTANT]
> This repository contains **submodules**. Please refer to the ["How to"](README.md#how-to-use) section for more details.

## Overview

This repository provides the **STM32CubeC0** MCU firmware, including **all** software components (Drivers, Middleware, Projects, Utilities).

## How to use

* To **clone** the repository, run the command below
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

## Feedback and contributions

Please refer to the [CONTRIBUTING.md](CONTRIBUTING.md) guide.