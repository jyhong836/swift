/*
 * Copyright (c) 2011 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include <Swiften/Base/boost_bsignals.h>
#include <Swiften/Elements/Form.h>

class QBoxLayout;
class QCloseEvent;

namespace Swift {
	class QtFormWidget;
	class QtMUCConfigurationWindow : public QWidget {
		Q_OBJECT
		public:
			QtMUCConfigurationWindow(Form::ref form);
			virtual ~QtMUCConfigurationWindow();
			boost::signal<void (Form::ref)> onFormComplete;
			boost::signal<void ()> onFormCancelled;
		private slots:
			void handleCancelClicked();
			void handleOKClicked();
		protected:
			virtual void closeEvent(QCloseEvent* event);
		private:
			QtFormWidget* formWidget_;
			QPushButton* okButton_;
			QPushButton* cancelButton_;
			bool closed_;
	};
}
