/****************************************************************************
 * arch/risc-v/src/common/espressif/esp_spi.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#ifndef __ARCH_RISCV_SRC_COMMON_ESPRESSIF_ESP_SPI_H
#define __ARCH_RISCV_SRC_COMMON_ESPRESSIF_ESP_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

#ifdef CONFIG_ESPRESSIF_SPI

#include <nuttx/spi/spi.h>

#ifdef CONFIG_ESPRESSIF_SPI2
#  define ESPRESSIF_SPI2 2
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: esp_spibus_initialize
 *
 * Description:
 *   Initialize the selected SPI bus.
 *
 * Input Parameters:
 *   port - Port number (for hardware that has multiple SPI interfaces)
 *
 * Returned Value:
 *   Valid SPI device structure reference on success; NULL on failure
 *
 ****************************************************************************/

struct spi_dev_s *esp_spibus_initialize(int port);

/****************************************************************************
 * Name:  esp_spi[2]_select and esp_spi[2]_status
 *
 * Description:
 *   The external functions, esp_spi[2]_select,
 *   esp_spi[2]_status, and esp_spi[2]_cmddata must be provided
 *   by board-specific logic.
 *   These are implementations of the select, status, and cmddata methods of
 *   the SPI interface defined by struct spi_ops_s (include/nuttx/spi/spi.h).
 *   All other methods (including esp_spibus_initialize()) are provided
 *   by common ESP32-S3 logic. To use this common SPI logic on your board:
 *
 *   1. Provide logic in esp_board_initialize() to configure SPI chip
 *      select pins.
 *   2. Provide esp_spi[2]_select() and esp_spi[2]_status()
 *      functions in your board-specific logic. These functions will perform
 *      chip selection and status operations using GPIOs in the way your
 *      board is configured.
 *   3. If CONFIG_SPI_CMDDATA is defined in your NuttX configuration file,
 *      then provide esp_spi[2]_cmddata() functions in your
 *      board-specific logic. These functions will perform cmd/data selection
 *      operations using GPIOs in the way your board is configured.
 *   4. Add a call to esp_spibus_initialize() in your low level
 *      application initialization logic.
 *   5. The handle returned by esp_spibus_initialize() may then be used
 *      to bind the SPI driver to higher level logic (e.g., calling
 *      mmcsd_spislotinitialize(), for example, will bind the SPI driver to
 *      the SPI MMC/SD driver).
 *
 ****************************************************************************/

#ifdef CONFIG_ESPRESSIF_SPI2
void esp_spi2_select(struct spi_dev_s *dev, uint32_t devid,
                         bool selected);
uint8_t esp_spi2_status(struct spi_dev_s *dev, uint32_t devid);
int esp_spi2_cmddata(struct spi_dev_s *dev,
                         uint32_t devid,
                         bool cmd);
#endif

/****************************************************************************
 * Name: esp_spibus_uninitialize
 *
 * Description:
 *   Uninitialize an SPI bus.
 *
 * Input Parameters:
 *   dev - Device-specific state data
 *
 * Returned Value:
 *   Zero (OK) is returned on success.  Otherwise -1 (ERROR).
 *
 ****************************************************************************/

int esp_spibus_uninitialize(struct spi_dev_s *dev);

#endif /* CONFIG_ESPRESSIF_SPI */

#ifdef __cplusplus
}
#endif
#undef EXTERN

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_RISCV_SRC_COMMON_ESPRESSIF_ESP_SPI_H */
