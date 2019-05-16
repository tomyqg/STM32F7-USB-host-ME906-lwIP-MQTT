/**
 * \file
 * \brief lwipErrorToErrorCode() declaration
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LWIP_INTEGRATION_INCLUDE_LWIPERRORTOERRORCODE_HPP_
#define LWIP_INTEGRATION_INCLUDE_LWIPERRORTOERRORCODE_HPP_

#include "lwip/err.h"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Converts lwIP's error to error code.
 *
 * \param [in] error is a lwIP's error
 *
 * \return \a error converted to error code
 */

int lwipErrorToErrorCode(err_t error);

#endif	// LWIP_INTEGRATION_INCLUDE_LWIPERRORTOERRORCODE_HPP_
