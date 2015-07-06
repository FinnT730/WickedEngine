#pragma once
#include "CommonInclude.h"
#include "RenderTarget.h"
#include "DepthTarget.h"

class RenderableComponent
{
public:
	static int screenW, screenH;

	RenderableComponent(){}
	~RenderableComponent(){}

	//initialize component
	virtual void Initialize(){};
	//load (graphics) resources
	virtual void Load(){};
	//delete resources
	virtual void Unload(){};
	//start component, load temporary resources
	virtual void Start(){};
	//unload temporary resources
	virtual void Stop(){};
	//update logic
	virtual void Update(){};
	//Render to layers, rendertargets, etc
	virtual void Render(){};
	//Compose the rendered layers (for example blend the layers together as Images)
	virtual void Compose(){};
};

