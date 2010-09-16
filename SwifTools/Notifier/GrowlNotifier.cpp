/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

// FIXME: Should we release the strings created in the constructor?

#include <cassert>

#include "Swiften/Base/ByteArray.h"
#include "SwifTools/Notifier/GrowlNotifier.h"

#pragma GCC diagnostic ignored "-Wold-style-cast"

namespace {
	struct Context {
		Context() {}
		Context(const boost::function<void()>& callback) : callback(new boost::function<void()>(callback)) {}

		boost::function<void()>* callback;
	};

	void processNotification(CFPropertyListRef growlContext, bool activateCallback) {
		Context context;

		CFDataRef growlContextData = (CFDataRef) CFArrayGetValueAtIndex((CFArrayRef) growlContext, 0);
		assert(CFDataGetLength(growlContextData) == sizeof(Context));
		CFDataGetBytes(growlContextData, CFRangeMake(0, CFDataGetLength(growlContextData)), (UInt8*) &context);
		
		if (activateCallback) {
			(*context.callback)();
		}
		delete context.callback;
	}

	void notificationClicked(CFPropertyListRef growlContext) {
		processNotification(growlContext, true);
	}

	void notificationTimedout(CFPropertyListRef growlContext) {
		processNotification(growlContext, false);
	}
}

namespace Swift {

GrowlNotifier::GrowlNotifier(const String& name) {
	// All notifications
	CFMutableArrayRef allNotifications = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
	CFArrayAppendValue(allNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(ContactAvailable)));
	CFArrayAppendValue(allNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(ContactUnavailable)));
	CFArrayAppendValue(allNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(ContactStatusChange)));
	CFArrayAppendValue(allNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(IncomingMessage)));
	CFArrayAppendValue(allNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(SystemMessage)));

	// Default Notifications
	CFMutableArrayRef defaultNotifications = CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
	CFArrayAppendValue(defaultNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(ContactAvailable)));
	CFArrayAppendValue(defaultNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(IncomingMessage)));
	CFArrayAppendValue(defaultNotifications, SWIFTEN_STRING_TO_CFSTRING(typeToString(SystemMessage)));

	// Initialize delegate
	InitGrowlDelegate(&delegate_);
	delegate_.applicationName = SWIFTEN_STRING_TO_CFSTRING(name);
	CFTypeRef keys[] = { GROWL_NOTIFICATIONS_ALL, GROWL_NOTIFICATIONS_DEFAULT };
	CFTypeRef values[] = { allNotifications, defaultNotifications };
	delegate_.registrationDictionary = CFDictionaryCreate(kCFAllocatorDefault, keys, values, 2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	delegate_.growlNotificationWasClicked = &notificationClicked;
	delegate_.growlNotificationTimedOut = &notificationTimedout;
	Growl_SetDelegate(&delegate_);
}

void GrowlNotifier::showMessage(Type type, const String& subject, const String& description, const boost::filesystem::path& picturePath, boost::function<void()> callback) {
	ByteArray picture;
	picture.readFromFile(picturePath.string());

	CFStringRef cfSubject = SWIFTEN_STRING_TO_CFSTRING(subject);
	CFStringRef cfDescription = SWIFTEN_STRING_TO_CFSTRING(description);
	CFStringRef cfName = SWIFTEN_STRING_TO_CFSTRING(typeToString(type));
	CFDataRef cfIcon = CFDataCreate( NULL, (UInt8*) picture.getData(), picture.getSize());
	
	Context context(callback);
	CFDataRef cfContextData[1];
	cfContextData[0] = CFDataCreate(kCFAllocatorDefault, (const UInt8*) &context, sizeof(Context));
	CFArrayRef cfContext = CFArrayCreate( kCFAllocatorDefault, (const void **) cfContextData, 1, &kCFTypeArrayCallBacks );
	CFRelease(cfContextData[0]);

	Growl_NotifyWithTitleDescriptionNameIconPriorityStickyClickContext(cfSubject, cfDescription, cfName, cfIcon, 0, false, cfContext);

	CFRelease(cfContext);
	CFRelease(cfIcon);
	CFRelease(cfName);
	CFRelease(cfDescription);
	CFRelease(cfSubject);
}

}