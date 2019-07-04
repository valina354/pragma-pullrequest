#include "stdafx_server.h"
#include "pragma/entities/components/s_time_scale_component.hpp"
#include "pragma/lua/s_lentity_handles.hpp"
#include <pragma/networking/enums.hpp>
#include <networkmanager/nwm_packet.h>

using namespace pragma;

void STimeScaleComponent::Initialize()
{
	BaseTimeScaleComponent::Initialize();
}
luabind::object STimeScaleComponent::InitializeLuaObject(lua_State *l) {return BaseEntityComponent::InitializeLuaObject<STimeScaleComponentHandleWrapper>(l);}

void STimeScaleComponent::SetTimeScale(float timeScale)
{
	BaseTimeScaleComponent::SetTimeScale(timeScale);
	auto &ent = static_cast<SBaseEntity&>(GetEntity());
	if(ent.IsShared() == false)
		return;
	NetPacket p;
	p->Write<float>(timeScale);
	ent.SendNetEvent(m_netEvSetTimeScale,p,pragma::networking::Protocol::SlowReliable);
}
