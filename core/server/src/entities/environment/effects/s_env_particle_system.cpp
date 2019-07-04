#include "stdafx_server.h"
#include "pragma/entities/environment/effects/s_env_particle_system.h"
#include "pragma/entities/s_entityfactories.h"
#include <pragma/networking/nwm_util.h>
#include <pragma/networking/enums.hpp>
#include "pragma/entities/baseentity_luaobject.h"
#include "pragma/lua/s_lentity_handles.hpp"
#include <pragma/entities/entity_component_system_t.hpp>

using namespace pragma;

LINK_ENTITY_TO_CLASS(env_particle_system,EnvParticleSystem);

void SParticleSystemComponent::SendData(NetPacket &packet,networking::ClientRecipientFilter &rp)
{
	packet->WriteString(m_particleFile);
	packet->WriteString(m_particleName);
}

void SParticleSystemComponent::SetContinuous(bool b)
{
	BaseEnvParticleSystemComponent::SetContinuous(b);

	NetPacket p;
	nwm::write_entity(p,&GetEntity());
	p->Write<bool>(b);
	server->SendPacket("env_prtsys_setcontinuous",p,pragma::networking::Protocol::SlowReliable);
}

luabind::object SParticleSystemComponent::InitializeLuaObject(lua_State *l) {return BaseEntityComponent::InitializeLuaObject<SParticleSystemComponentHandleWrapper>(l);}

///////////////

void EnvParticleSystem::Initialize()
{
	SBaseEntity::Initialize();
	AddComponent<SParticleSystemComponent>();
}
