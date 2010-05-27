/*
 * Copyright (c) 2010 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/signals.hpp>

#include "Swiften/Base/String.h"
#include "Swiften/JID/JID.h"

#include "Swift/Controllers/Chat/MUCSearchController.h"

namespace Swift {

	class MUCSearchWindow {
		public:
			virtual ~MUCSearchWindow() {};

			virtual void setNick(const String& nick) = 0;
			virtual void setMUC(const String& nick) = 0;
			virtual void clearList() = 0;
			virtual void addService(const MUCService& service) = 0;

			virtual void show() = 0;

			boost::signal<void (const JID&)> onAddService;
	};
}