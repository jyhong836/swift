/*
 * Copyright (c) 2012 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <Swift/Controllers/Settings/SettingsProviderHierachy.h>

#include <Swiften/Base/foreach.h>
#include <Swiften/Base/Log.h>
namespace Swift {

SettingsProviderHierachy::~SettingsProviderHierachy() {
}

std::string SettingsProviderHierachy::getSetting(const Setting<std::string>& setting) {
	foreach (SettingsProvider* provider, providers_) {
		std::string providerSetting = provider->getSetting(setting);
		if (providerSetting != setting.getDefaultValue()) {
			return providerSetting;
		}
	}
	return setting.getDefaultValue();
}

void SettingsProviderHierachy::storeSetting(const Setting<std::string>& setting, const std::string& settingValue) {
	if (!getIsSettingFinal(setting.getKey())) {
		getWritableProvider()->storeSetting(setting, settingValue);
	}
}

bool SettingsProviderHierachy::getSetting(const Setting<bool>& setting) {
	foreach (SettingsProvider* provider, providers_) {
		bool providerSetting = provider->getSetting(setting);
		if (providerSetting != setting.getDefaultValue()) {
			return providerSetting;
		}
	}
	return setting.getDefaultValue();
}

void SettingsProviderHierachy::storeSetting(const Setting<bool>& setting, const bool& settingValue) {
	if (!getIsSettingFinal(setting.getKey())) {
		getWritableProvider()->storeSetting(setting, settingValue);
	}
}

int SettingsProviderHierachy::getSetting(const Setting<int>& setting) {
	foreach (SettingsProvider* provider, providers_) {
		int providerSetting = provider->getSetting(setting);
		if (providerSetting != setting.getDefaultValue()) {
			return providerSetting;
		}
	}
	return setting.getDefaultValue();
}

void SettingsProviderHierachy::storeSetting(const Setting<int>& setting, const int& settingValue) {
	if (!getIsSettingFinal(setting.getKey())) {
		getWritableProvider()->storeSetting(setting, settingValue);
	}
}

std::vector<std::string> SettingsProviderHierachy::getAvailableProfiles() {
	/* Always pull profiles from the topmost */
	return getWritableProvider()->getAvailableProfiles();
}

void SettingsProviderHierachy::createProfile(const std::string& profile) {
	return getWritableProvider()->createProfile(profile);
}

void SettingsProviderHierachy::removeProfile(const std::string& profile) {
	return getWritableProvider()->removeProfile(profile);
}

bool SettingsProviderHierachy::getIsSettingFinal(const std::string& settingPath) {
	bool isFinal = false;
	foreach (SettingsProvider* provider, providers_) {
		isFinal |= provider->getIsSettingFinal(settingPath);
	}
	return isFinal;
}

SettingsProvider* SettingsProviderHierachy::getWritableProvider() {
	return providers_.back();
}

void SettingsProviderHierachy::addProviderToTopOfStack(SettingsProvider* provider) {
	providers_.push_back(provider);
	provider->onSettingChanged.connect(onSettingChanged);
}

}

