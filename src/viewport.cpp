#include <viewport.h>

float* viewport;
float* currentViewport;

Viewport::Viewport(int count)
{
	this->count = count;
	viewport = new float[count * 4];
	currentViewport = new float[4];

	for (int i = 0; i < count * 4; i++)
	{
		std::cout << viewport[i] << std::endl;
	}
}

void Viewport::setViewportf(int index, float x, float y, float w, float h)
{
	viewport[(index * 4) + 0] = x;
	viewport[(index * 4) + 1] = y;
	viewport[(index * 4) + 2] = w;
	viewport[(index * 4) + 3] = h;
	glViewportIndexedf(index, x, y, w, h);
}

void Viewport::setViewportfv(int index)
{
	viewport[(index * 4) + 0] = currentViewport[0];
	viewport[(index * 4) + 1] = currentViewport[1];
	viewport[(index * 4) + 2] = currentViewport[2];
	viewport[(index * 4) + 3] = currentViewport[3];
	glViewportIndexedfv(index, viewport);
}

void Viewport::makeArray()
{
	glViewportArrayv(0, count, viewport);
}

void Viewport::setCurrentViewport(int index)
{
	glViewport(viewport[(index*4)],viewport[(index*4)+1],viewport[(index*4)+2],viewport[(index*4)+3]);
}

void Viewport::getViewportDimensions(Viewport* viewport, int index, float* dimensions)
{
	dimensions[0] = viewport->viewport[(index * 4) + 0];
	dimensions[1] = viewport->viewport[(index * 4) + 1];
	dimensions[2] = viewport->viewport[(index * 4) + 2];
	dimensions[3] = viewport->viewport[(index * 4) + 3];
}

void Viewport::setViewportDimensions(Viewport* viewport, int index, float* dimensions)
{
	
	viewport->viewport[(index * 4) + 2] = dimensions[2];
	viewport->viewport[(index * 4) + 3] = dimensions[3];
}