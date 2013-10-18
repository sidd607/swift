/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>

#include <Sluift/GenericLuaElementConvertor.h>
#include <Swiften/Elements/PubSubEventConfiguration.h>

namespace Swift {
	class LuaElementConvertors;

	class PubSubEventConfigurationConvertor : public GenericLuaElementConvertor<PubSubEventConfiguration> {
		public:
			PubSubEventConfigurationConvertor(LuaElementConvertors* convertors);
			virtual ~PubSubEventConfigurationConvertor();

			virtual boost::shared_ptr<PubSubEventConfiguration> doConvertFromLua(lua_State*) SWIFTEN_OVERRIDE;
			virtual void doConvertToLua(lua_State*, boost::shared_ptr<PubSubEventConfiguration>) SWIFTEN_OVERRIDE;

		private:
			LuaElementConvertors* convertors;
	};
}