/**
 * \file
 * \brief AlternateFunctionPinInitializer struct header
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef BOARD_ALTERNATEFUNCTIONPININITIALIZER_HPP_
#define BOARD_ALTERNATEFUNCTIONPININITIALIZER_HPP_

#include "distortos/chip/STM32-GPIOv2.hpp"

namespace distortos
{

namespace board
{

/// initializer for single pin with alternate function
struct AlternateFunctionPinInitializer
{
	/// identifier of pin
	chip::Pin pin;

	/// desired alternate function of pin
	chip::PinAlternateFunction alternateFunction;

	/// desired output type of pin: push-pull (false) or open-drain (true)
	bool openDrain;

	/// desired output speed of pin
	chip::PinOutputSpeed outputSpeed;

	/// desired pull-up/pull-down configuration of pin
	chip::PinPull pull;
};

}	// namespace board

}	// namespace distortos

#endif	// BOARD_ALTERNATEFUNCTIONPININITIALIZER_HPP_
