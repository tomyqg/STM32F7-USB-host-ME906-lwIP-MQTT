/**
 * \file
 * \brief STM32F7xx_HAL_Driver configuration
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef STM32F7XX_HAL_DRIVER_CONFIGURATION_H_
#define STM32F7XX_HAL_DRIVER_CONFIGURATION_H_

#ifdef __cplusplus
extern "C"
{
#endif	/* def __cplusplus */

/*---------------------------------------------------------------------------------------------------------------------+
| clock-related global defines
+---------------------------------------------------------------------------------------------------------------------*/

/** value of the external clock source for I2S peripheral, Hz */
#define EXTERNAL_CLOCK_VALUE				12288000

/** time out for HSE start up, milliseconds */
#define HSE_STARTUP_TIMEOUT					100

/** value of the internal oscillator, Hz */
#define HSI_VALUE							16000000

/** time out for LSE start up, milliseconds */
#define LSE_STARTUP_TIMEOUT					5000

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* def __cplusplus */

#endif	/* STM32F7XX_HAL_DRIVER_CONFIGURATION_H_ */
