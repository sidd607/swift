/*
 * Copyright (c) 2010-2013 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Base/boost_bsignals.h>
#include <Swiften/Base/Error.h>
#include <Swiften/Component/ComponentConnector.h>
#include <Swiften/Component/ComponentSession.h>
#include <Swiften/Component/ComponentError.h>
#include <Swiften/Elements/Presence.h>
#include <Swiften/Elements/Message.h>
#include <Swiften/JID/JID.h>
#include <string>
#include <Swiften/Parser/PayloadParsers/FullPayloadParserFactoryCollection.h>
#include <Swiften/Serializer/PayloadSerializers/FullPayloadSerializerCollection.h>
#include <Swiften/Component/ComponentSessionStanzaChannel.h>
#include <Swiften/Entity/Entity.h>
#include <Swiften/Base/SafeByteArray.h>

namespace Swift {
	class EventLoop;
	class IQRouter;
	class NetworkFactories;
	class ComponentSession;
	class BasicSessionStream;

	/**
	 * The central class for communicating with an XMPP server as a component.
	 *
	 * This class is responsible for setting up the connection with the XMPP 
	 * server and authenticating the component.
	 *
	 * This class can be used directly in your application, although the Component 
	 * subclass provides more functionality and interfaces, and is better suited 
	 * for most needs.
	 */
	class SWIFTEN_API CoreComponent : public Entity {
		public:
			CoreComponent(const JID& jid, const std::string& secret, NetworkFactories* networkFactories);
			~CoreComponent();

			void connect(const std::string& host, int port);
			void disconnect();
			
			void sendMessage(boost::shared_ptr<Message>);
			void sendPresence(boost::shared_ptr<Presence>);
			void sendData(const std::string& data);

			IQRouter* getIQRouter() const {
				return iqRouter_;
			}

			StanzaChannel* getStanzaChannel() const {
				return stanzaChannel_;
			}

			bool isAvailable() const {
				return stanzaChannel_->isAvailable();
			}

			/**
			 * Returns the JID of the component
			 */
			const JID& getJID() const {
				return jid_;
			}

		public:
			boost::signal<void (const ComponentError&)> onError;
			boost::signal<void ()> onConnected;
			boost::signal<void (const SafeByteArray&)> onDataRead;
			boost::signal<void (const SafeByteArray&)> onDataWritten;

			boost::signal<void (boost::shared_ptr<Message>)> onMessageReceived;
			boost::signal<void (boost::shared_ptr<Presence>) > onPresenceReceived;

		private:
			void handleConnectorFinished(boost::shared_ptr<Connection>);
			void handleStanzaChannelAvailableChanged(bool available);
			void handleSessionFinished(boost::shared_ptr<Error>);
			void handleDataRead(const SafeByteArray&);
			void handleDataWritten(const SafeByteArray&);

		private:
			NetworkFactories* networkFactories;
			JID jid_;
			std::string secret_;
			ComponentSessionStanzaChannel* stanzaChannel_;
			IQRouter* iqRouter_;
			ComponentConnector::ref connector_;
			boost::shared_ptr<Connection> connection_;
			boost::shared_ptr<BasicSessionStream> sessionStream_;
			boost::shared_ptr<ComponentSession> session_;
			bool disconnectRequested_;
	};
}
