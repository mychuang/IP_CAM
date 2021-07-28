#pragma once
#include <QPushButton>

namespace Utils {
	static void enableButtonWithUI(bool setEnabled, QPushButton *button) {
		button->setEnabled(setEnabled);

	}
};