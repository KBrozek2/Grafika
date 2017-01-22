#include "Image.h"


void Image::createWindow()
{

	window = SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "SDL_CreateWindow() Failed: " << SDL_GetError() << std::endl;
		exit(1);
	}
	else {

		screenSurface = SDL_GetWindowSurface(window);
	}
}


SDL_Surface *Image::displayBitMap(char *path) {


	image = SDL_LoadBMP(path);
	if (!image) {
		std::cerr << "SDL_LoadBMP() Failed: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SCREEN_WIDTH = image->w;
	SCREEN_HEIGHT = image->h;
	SDL_BlitSurface(image, nullptr, screenSurface, nullptr);
	SDL_UpdateWindowSurface(window);
	return image;
}

SDL_Surface *Image::loadBitMap(char *path)
{
	image = SDL_LoadBMP(path);
	if (!image) {
		std::cerr << "SDL_LoadBMP() Failed: " << SDL_GetError() << std::endl;
		exit(1);
	}
	SCREEN_WIDTH = image->w;
	SCREEN_HEIGHT = image->h;
	return image;
}

bool Image::isMessageFittedIn(int size, char * img_path)
{
	SDL_Surface *bmp = loadBitMap(img_path);
	long long totalPix = (bmp->w) * (bmp->h);

	if (size < totalPix)
		return true;
	else
		return false;
}

bool Image::isBmpRightSize(char * img_path)
{
	SDL_Surface *bmp = loadBitMap(img_path);

	if (bmp->h <= 1080 && bmp->w <= 1920)
		return true;
	else
		return false;
}


SDL_Color Image::getPixel(int x, int y)
{

	SDL_Color color;
	Uint32 col = 0;
	if ((x >= 0) && (x<SCREEN_WIDTH) && (y >= 0) && (y<SCREEN_HEIGHT)) {
		//determine position
		char* pPosition = (char*)image->pixels;
		//offset by y
		pPosition += (image->pitch*y);
		//offset by x
		pPosition += (image->format->BytesPerPixel*x);
		//copy pixel data
		memcpy(&col, pPosition, image->format->BytesPerPixel);
		//convert color
		SDL_GetRGB(col, image->format, &color.r, &color.g, &color.b);
	}
	return (color);
}

void Image::setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
	if ((x >= 0) && (x<SCREEN_WIDTH) && (y >= 0) && (y<SCREEN_HEIGHT))
	{
		/* Zamieniamy poszczególne sk?adowe koloru na format koloru pixela */
		Uint32 pixel = SDL_MapRGB(image->format, R, G, B);

		/* Pobieramy informacji ile bajtów zajmuje jeden pixel */
		int bpp = image->format->BytesPerPixel;

		/* Obliczamy adres pixela */
		Uint8 *p = (Uint8 *)image->pixels + y * image->pitch + x * bpp;

		/* Ustawiamy warto?? pixela, w zale?no?ci od formatu powierzchni*/
		switch (bpp)
		{
		case 1: //8-bit
			*p = pixel;
			break;

		case 2: //16-bit
			*(Uint16 *)p = pixel;
			break;

		case 3: //24-bit
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4: //32-bit
			*(Uint32 *)p = pixel;
			break;

		}
		/* update the screen (aka double buffering) */
	}
}


Image::Image() :
	SCREEN_WIDTH(0), SCREEN_HEIGHT(0), image(nullptr), window(nullptr), screenSurface(nullptr) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init() Failed: " << SDL_GetError() << std::endl;
		exit(1);
	}

}
Image::~Image() {

	//Deallocate surface
	SDL_FreeSurface(image);
	image = nullptr;

	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}