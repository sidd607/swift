/*
 * Copyright (c) 2012 Mateusz Piękos
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

#include <Swiften/Whiteboard/IncomingWhiteboardSession.h>
#include <Swiften/Elements/WhiteboardPayload.h>

#include <boost/smart_ptr/make_shared.hpp>
#include <Swiften/Elements/Whiteboard/WhiteboardInsertOperation.h>
#include <Swiften/Elements/Whiteboard/WhiteboardDeleteOperation.h>
#include <Swiften/Elements/Whiteboard/WhiteboardUpdateOperation.h>

namespace Swift {
	IncomingWhiteboardSession::IncomingWhiteboardSession(const JID& jid, IQRouter* router) : WhiteboardSession(jid, router) {
	}

	IncomingWhiteboardSession::~IncomingWhiteboardSession() {
	}

	void IncomingWhiteboardSession::accept() {
		boost::shared_ptr<WhiteboardPayload> payload = boost::make_shared<WhiteboardPayload>(WhiteboardPayload::SessionAccept);
		boost::shared_ptr<GenericRequest<WhiteboardPayload> > request = boost::make_shared<GenericRequest<WhiteboardPayload> >(IQ::Set, toJID_, payload, router_);
		request->send();
		onRequestAccepted(toJID_);
	}

	void IncomingWhiteboardSession::handleIncomingOperation(WhiteboardOperation::ref operation) {
		WhiteboardClient::Result pairResult = client.handleServerOperationReceived(operation);
		if (pairResult.client) {
			if (pairResult.client->getPos() != -1) {
				onOperationReceived(pairResult.client);
			}
			lastOpID = pairResult.client->getID();
		}

		if (pairResult.server) {
			WhiteboardPayload::ref payload = boost::make_shared<WhiteboardPayload>();
			payload->setOperation(pairResult.server);
			sendPayload(payload);
		}
	}

	void IncomingWhiteboardSession::sendOperation(WhiteboardOperation::ref operation) {
		operation->setID(idGenerator.generateID());
		operation->setParentID(lastOpID);
		lastOpID = operation->getID();

		WhiteboardOperation::ref result = client.handleLocalOperationReceived(operation);

		if (result) {
			WhiteboardPayload::ref payload = boost::make_shared<WhiteboardPayload>();
			payload->setOperation(result);
			sendPayload(payload);
		}
	}
}
