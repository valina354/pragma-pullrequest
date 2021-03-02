/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2021 Silverlan
 */

#ifndef __C_SHADER_LOADING_H__
#define __C_SHADER_LOADING_H__

#include "pragma/rendering/shaders/world/c_shader_textured.hpp"

namespace pragma
{
	class DLLCLIENT ShaderLoading
		: public ShaderGameWorldLightingPass
	{
	public:
		ShaderLoading(prosper::IPrContext &context,const std::string &identifier);
		virtual bool BindMaterial(CMaterial &mat) override;
	};
};

#endif