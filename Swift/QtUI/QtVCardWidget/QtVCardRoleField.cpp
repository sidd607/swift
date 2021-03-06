/*
 * Copyright (c) 2012-2014 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

#include "QtVCardRoleField.h"

#include <QGridLayout>
#include <boost/algorithm/string.hpp>

#include <Swift/QtUI/QtSwiftUtil.h>

namespace Swift {

QtVCardRoleField::QtVCardRoleField(QWidget* parent, QGridLayout *layout, bool editable) :
	QtVCardGeneralField(parent, layout, editable, layout->rowCount(), tr("Role"), false, false), roleLineEdit(NULL) {
	connect(this, SIGNAL(editableChanged(bool)), SLOT(handleEditibleChanged(bool)));
}

QtVCardRoleField::~QtVCardRoleField() {
}

void QtVCardRoleField::setupContentWidgets() {
	roleLineEdit = new QtResizableLineEdit(this);
	getGridLayout()->addWidget(roleLineEdit, getGridLayout()->rowCount()-1, 2, 1, 2, Qt::AlignVCenter);
	getTagComboBox()->hide();
	childWidgets << roleLineEdit;
}

bool QtVCardRoleField::isEmpty() const {
	return roleLineEdit->text().isEmpty();
}

void QtVCardRoleField::setRole(const std::string& role) {
	roleLineEdit->setText(P2QSTRING(role));
}

std::string QtVCardRoleField::getRole() const {
	return Q2PSTRING(roleLineEdit->text());
}

void QtVCardRoleField::handleEditibleChanged(bool isEditable) {
	assert(roleLineEdit);

	roleLineEdit->setEditable(isEditable);
	roleLineEdit->setStyleSheet(isEditable ? "" : "QLineEdit { border: none; background: transparent; }");
}

}
