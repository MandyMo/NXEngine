/*
 *  File:    NXSky.h
 *
 *  author:  张雄(zhang xiong, 1025679612@qq.com)
 *  date:    2017_04_13
 *  purpose: define sky box & sky sphere
 */


#pragma once

#include "NXIEntity.h"

namespace NX {
	class Sky : public IEntity{
	public:
		Sky();
		virtual ~Sky();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
	};

	class SkyBox : public Sky {
	public:
		SkyBox();
		virtual ~SkyBox();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
	};

	class SkySphere : public Sky {
	public:
		SkySphere();
		virtual ~SkySphere();

	public:
		virtual void Render(struct RenderParameter &renderer) override;
	};
}