#include "LoadTexture.h"

LoadTexture::LoadTexture(const char* path) :image_path(path)
{
	width = new int();
	height = new int();

}
unsigned char* LoadTexture::Load_Image()
{
	imagedata = SOIL_load_image(image_path, width, height, 0, SOIL_LOAD_RGB);
	if (imagedata == nullptr)
	{
		std::cout << "Ê§°Ü" << std::endl;
	}
	return SOIL_load_image(image_path, width, height, 0, SOIL_LOAD_RGB);

}
LoadTexture::~LoadTexture()
{
	delete width;
	delete height;
	width = nullptr;
	height = nullptr;

}