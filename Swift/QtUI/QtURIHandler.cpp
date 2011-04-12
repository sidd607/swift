/*
 * Copyright (c) 2011 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include "QtURIHandler.h"

#include <QCoreApplication>
#include <QFileOpenEvent>
#include <QUrl>

#include "QtSwiftUtil.h"
#ifdef Q_WS_MAC
#include <SwifTools/URIHandler/MacOSXURIHandlerHelpers.h>
#endif

using namespace Swift;

QtURIHandler::QtURIHandler() {
	qApp->installEventFilter(this);
#ifdef Q_WS_MAC
	registerAppAsDefaultXMPPURIHandler();
#endif
}

bool QtURIHandler::eventFilter(QObject*, QEvent* event) {
	if (event->type() == QEvent::FileOpen) {
		QFileOpenEvent* fileOpenEvent = static_cast<QFileOpenEvent*>(event);
		if (fileOpenEvent->url().scheme() == "xmpp") {
			onURI(Q2PSTRING(fileOpenEvent->url().toString()));
			return true;
		}
	}
	return false;
}