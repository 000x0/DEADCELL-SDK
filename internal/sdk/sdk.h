#pragma once

// Pad macro
#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif

#include "classes/cutlvector.h"
#include "classes/color.h"

// Interfaces
#include "interfaces/DT_Recv.h"
#include "interfaces/ClientClass.h"
#include "interfaces/Def.h"
#include "interfaces/ClientDLL.h"
#include "interfaces/IClientModeShared.h"
#include "interfaces/IClientEntity.h"
#include "interfaces/IClientEntityList.h"
#include "interfaces/IVModelInfo.h"
#include "interfaces/IClientRenderable.h"
#include "interfaces/CInput.h"
#include "interfaces/ICvar.h"
#include "interfaces/CGlobalVars.h"
#include "interfaces/CHandle.h"
#include "interfaces/IMaterialVar.h"
#include "interfaces/IMaterial.h"
#include "interfaces/ITexture.h"
#include "interfaces/IMaterialSystem.h"
#include "interfaces/IVRenderView.h"
#include "interfaces/IVModelRender.h"
#include "interfaces/ISurface.h"
#include "interfaces/IVDebugOverlay.h"
#include "interfaces/IPanel.h"
#include "interfaces/INetChannel.h"
#include "interfaces/IStudioRender.h"
#include "interfaces/IEngineTrace.h"
#include "interfaces/IGameMovement.h"
#include "interfaces/IPrediction.h"
#include "interfaces/IGameEvent.h"
#include "interfaces/IMatRenderContext.h"
#include "interfaces/IViewRenderBeams.h"
#include "interfaces/IWeaponInfo.h"
#include "interfaces/IWeaponSystem.h"
#include "interfaces/IEffects.h"
#include "interfaces/CGlowObjectManager.h"
#include "interfaces/CPhysicsSurface.h"
#include "interfaces/ILocalize.h"

#include "utils/interface_manager.h"

#include "game/game.h"

#include "utils/netvars.h"

#include "classes/animstate.h"
#include "classes/keyvalues.h"
#include "classes/entity.h"

#include "client.h"
