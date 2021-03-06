/*
 * Copyright (c) 2010-2012 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swift/Controllers/XMPPEvents/StanzaEvent.h>
#include <Swift/Controllers/Settings/SettingsProvider.h>
#include <Swift/Controllers/HighlightAction.h>

namespace Swift {
	class EventController;
	class SoundPlayer;
	class HighlightManager;
	class SoundEventController {
		public:
			SoundEventController(EventController* eventController, SoundPlayer* soundPlayer, SettingsProvider* settings, HighlightManager* highlightManager);
			void setPlaySounds(bool playSounds);
			bool getSoundEnabled() {return playSounds_;}
		private:
			void handleSettingChanged(const std::string& settingPath);
			void handleEventQueueEventAdded(boost::shared_ptr<StanzaEvent> event);
			void handleHighlight(const HighlightAction& action);
			EventController* eventController_;
			SoundPlayer* soundPlayer_;
			bool playSounds_;
			SettingsProvider* settings_;
			HighlightManager* highlightManager_;
	};
}
