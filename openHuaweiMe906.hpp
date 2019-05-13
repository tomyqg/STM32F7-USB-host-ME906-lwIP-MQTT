/**
 * \file
 * \brief Declaration of openHuaweiMe906()
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef OPENHUAWEIME906_HPP_
#define OPENHUAWEIME906_HPP_

#include "HuaweiMe906.hpp"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Wraps selected HuaweiMe906 serial port into a FILE and sets line buffering.
 *
 * \param [in] huaweiMe906 is a reference to HuaweiMe906 object
 * \param [in] port selects the serial port of \a huaweiMe906 that will be accessed
 * \param [in] mode is the mode with which the stream is opened
 *
 * \return pointer to opened FILE object
 */

FILE* openHuaweiMe906(HuaweiMe906& huaweiMe906, HuaweiMe906::Port port, const char* mode);

#endif	// OPENHUAWEIME906_HPP_
