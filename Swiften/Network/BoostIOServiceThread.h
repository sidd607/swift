/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>

namespace Swift {
	class SWIFTEN_API BoostIOServiceThread {
		public:
			BoostIOServiceThread();
			~BoostIOServiceThread();

			boost::shared_ptr<boost::asio::io_service> getIOService() const {
				return ioService_;
			}

		private:
			void doRun();

		private:
			boost::shared_ptr<boost::asio::io_service> ioService_;
			boost::thread* thread_;
	};
}
