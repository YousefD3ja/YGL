#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/gl.h>
#include <iostream>

class Viewport
{
public:

	int count;
	float* viewport;
	float* currentViewport;
	

	Viewport(int count);
	void makeArray();

	void setViewportf(int index, float x, float y, float w, float h);

	void setViewportfv(int index);

	void setCurrentViewport(int index);

	static void getViewportDimensions(Viewport* viewport, int index, float* dimensions);

	static void setViewportDimensions(Viewport* viewport, int index, float* dimensions);

};
#endif
