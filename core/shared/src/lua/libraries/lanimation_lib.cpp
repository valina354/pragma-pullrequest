/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan
 */

#include "stdafx_shared.h"
#include "pragma/model/animation/animated_pose.hpp"
#include "pragma/model/animation/animation_channel.hpp"
#include "pragma/model/animation/animation_player.hpp"
#include "pragma/model/animation/skeletal_animation.hpp"
#include "pragma/model/animation/play_animation_flags.hpp"
#include "pragma/model/model.h"
#include <luainterface.hpp>

namespace Lua::animation
{
	void register_library(Lua::Interface &lua);
};
void Lua::animation::register_library(Lua::Interface &lua)
{
	auto animMod = luabind::module(lua.GetState(),"animation");

	auto cdPose = luabind::class_<pragma::animation::AnimatedPose>("Pose");
	cdPose.def(luabind::constructor<>());
	cdPose.def("SetTransformCount",static_cast<void(*)(lua_State*,pragma::animation::AnimatedPose&,uint32_t)>([](lua_State *l,pragma::animation::AnimatedPose &pose,uint32_t count) {
		pose.SetTransformCount(count);
	}));
	cdPose.def("SetBoneIndex",static_cast<void(*)(lua_State*,pragma::animation::AnimatedPose&,uint32_t,uint32_t)>([](lua_State *l,pragma::animation::AnimatedPose &pose,uint32_t idx,uint32_t boneIdx) {
		pose.SetBoneIndex(idx,boneIdx);
	}));
	cdPose.def("GetTransform",static_cast<umath::ScaledTransform*(*)(lua_State*,pragma::animation::AnimatedPose&,uint32_t)>([](lua_State *l,pragma::animation::AnimatedPose &pose,uint32_t boneIdx) -> umath::ScaledTransform* {
		return pose.GetTransform(boneIdx);
	}));
	cdPose.def("SetTransform",static_cast<void(*)(lua_State*,pragma::animation::AnimatedPose&,uint32_t,const umath::ScaledTransform&)>(
		[](lua_State *l,pragma::animation::AnimatedPose &pose,uint32_t boneIdx,const umath::ScaledTransform &transform) {
		pose.SetTransform(boneIdx,transform);
	}));
	cdPose.def("Clear",static_cast<void(*)(lua_State*,pragma::animation::AnimatedPose&)>(
		[](lua_State *l,pragma::animation::AnimatedPose &pose) {
		pose.Clear();
	}));
	cdPose.def("Lerp",static_cast<void(*)(lua_State*,pragma::animation::AnimatedPose&,const pragma::animation::AnimatedPose&,float)>(
		[](lua_State *l,pragma::animation::AnimatedPose &pose,const pragma::animation::AnimatedPose &other,float f) {
		pose.Lerp(other,f);
	}));
	cdPose.def("Localize",static_cast<void(*)(lua_State*,pragma::animation::AnimatedPose&,const Skeleton&)>(
		[](lua_State *l,pragma::animation::AnimatedPose &pose,const Skeleton &skeleton) {
		pose.Localize(skeleton);
	}));
	cdPose.def("Globalize",static_cast<void(*)(lua_State*,pragma::animation::AnimatedPose&,const Skeleton&)>(
		[](lua_State *l,pragma::animation::AnimatedPose &pose,const Skeleton &skeleton) {
		pose.Globalize(skeleton);
	}));
	cdPose.def("GetBoneTranslationTable",static_cast<luabind::object(*)(lua_State*,pragma::animation::AnimatedPose&)>(
		[](lua_State *l,pragma::animation::AnimatedPose &pose) {
		return Lua::vector_to_table(l,pose.GetBoneTranslationTable());
	}));
	animMod[cdPose];

	auto cdChannel = luabind::class_<pragma::animation::AnimationChannel>("Channel");
	cdChannel.def("GetValueType",static_cast<udm::Type(*)(lua_State*,pragma::animation::AnimationChannel&)>([](lua_State *l,pragma::animation::AnimationChannel &channel) -> udm::Type {
		return channel.valueType;
	}));
	cdChannel.def("GetInterpolation",static_cast<pragma::animation::AnimationChannelInterpolation(*)(lua_State*,pragma::animation::AnimationChannel&)>(
		[](lua_State *l,pragma::animation::AnimationChannel &channel) -> pragma::animation::AnimationChannelInterpolation {
		return channel.interpolation;
	}));
	cdChannel.def("GetTargetPath",static_cast<util::Path(*)(lua_State*,pragma::animation::AnimationChannel&)>(
		[](lua_State *l,pragma::animation::AnimationChannel &channel) -> util::Path {
		return channel.targetPath;
	}));
	cdChannel.def("GetTimes",static_cast<luabind::object(*)(lua_State*,pragma::animation::AnimationChannel&)>(
		[](lua_State *l,pragma::animation::AnimationChannel &channel) -> luabind::object {
		return Lua::vector_to_table(l,channel.times);
	}));
	cdChannel.def("Save",static_cast<bool(*)(lua_State*,pragma::animation::AnimationChannel&,udm::LinkedPropertyWrapper&)>(
		[](lua_State *l,pragma::animation::AnimationChannel &channel,udm::LinkedPropertyWrapper &prop) -> bool {
		return channel.Save(prop);
	}));
	cdChannel.def("Load",static_cast<bool(*)(lua_State*,pragma::animation::AnimationChannel&,udm::LinkedPropertyWrapper&)>(
		[](lua_State *l,pragma::animation::AnimationChannel &channel,udm::LinkedPropertyWrapper &prop) -> bool {
		return channel.Load(prop);
	}));
	animMod[cdChannel];

	auto cdPlayer = luabind::class_<pragma::animation::AnimationPlayer>("Player");
	cdPlayer.scope[luabind::def("create",static_cast<std::shared_ptr<pragma::animation::AnimationPlayer>(*)(lua_State*,Model&)>([](lua_State *l,Model &mdl) {
		return pragma::animation::AnimationPlayer::Create(mdl);
	}))];
	cdPlayer.def("Advance",static_cast<void(*)(lua_State*,pragma::animation::AnimationPlayer&,float,bool)>([](lua_State *l,pragma::animation::AnimationPlayer &player,float dt,bool force) {
		player.Advance(dt,force);
	}));
	cdPlayer.def("Advance",static_cast<void(*)(lua_State*,pragma::animation::AnimationPlayer&,float)>([](lua_State *l,pragma::animation::AnimationPlayer &player,float dt) {
		player.Advance(dt);
	}));
	cdPlayer.def("GetCurrentAnimationId",static_cast<pragma::animation::AnimationId(*)(lua_State*,pragma::animation::AnimationPlayer&)>([](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return player.GetCurrentAnimationId();
	}));
	cdPlayer.def("GetDuration",static_cast<float(*)(lua_State*,pragma::animation::AnimationPlayer&)>([](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return player.GetDuration();
	}));
	cdPlayer.def("GetRemainingDuration",static_cast<float(*)(lua_State*,pragma::animation::AnimationPlayer&)>([](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return player.GetDuration();
	}));
	cdPlayer.def("GetCurrentTimeFraction",static_cast<float(*)(lua_State*,pragma::animation::AnimationPlayer&)>([](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return player.GetCurrentTimeFraction();
	}));
	cdPlayer.def("GetCurrentTime",static_cast<float(*)(lua_State*,pragma::animation::AnimationPlayer&)>([](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return player.GetCurrentTime();
	}));
	cdPlayer.def("GetPlaybackRate",static_cast<float(*)(lua_State*,pragma::animation::AnimationPlayer&)>([](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return player.GetPlaybackRate();
	}));
	cdPlayer.def("SetPlaybackRate",static_cast<void(*)(lua_State*,pragma::animation::AnimationPlayer&,float)>([](lua_State *l,pragma::animation::AnimationPlayer &player,float playbackRate) {
		player.SetPlaybackRate(playbackRate);
	}));
	cdPlayer.def("SetCurrentTime",static_cast<void(*)(lua_State*,pragma::animation::AnimationPlayer&,float)>([](lua_State *l,pragma::animation::AnimationPlayer &player,float time) {
		player.SetCurrentTime(time);
	}));
	cdPlayer.def("SetCurrentTime",static_cast<void(*)(lua_State*,pragma::animation::AnimationPlayer&,float,bool)>([](lua_State *l,pragma::animation::AnimationPlayer &player,float time,bool force) {
		player.SetCurrentTime(time,force);
	}));
	cdPlayer.def("StopAnimation",static_cast<void(*)(lua_State*,pragma::animation::AnimationPlayer&)>(
		[](lua_State *l,pragma::animation::AnimationPlayer &player) {
		player.StopAnimation();
	}));
	cdPlayer.def("GetCurrentSlice",static_cast<pragma::animation::AnimationSlice*(*)(lua_State*,pragma::animation::AnimationPlayer&)>(
		[](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return &player.GetCurrentSlice();
	}));
	cdPlayer.def("GetPreviousSlice",static_cast<pragma::animation::AnimationSlice*(*)(lua_State*,pragma::animation::AnimationPlayer&)>(
		[](lua_State *l,pragma::animation::AnimationPlayer &player) {
		return &player.GetPreviousSlice();
	}));
	animMod[cdPlayer];

	auto cdSlice = luabind::class_<pragma::animation::AnimationSlice>("Slice");
	animMod[cdSlice];
}
