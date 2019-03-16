#pragma once

#include "IClientUnknown.h"
#include "IClientRenderable.h"
#include "IClientNetworkable.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable {
public:
	void Release( ) override = 0;
};
