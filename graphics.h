#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include <map>
#include <string>
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;
struct Color;


class Graphics {

public:
	Graphics();
	~Graphics();

	SDL_Surface* load_image(const std::string& filepath);
	SDL_Surface* load_image(const std::string& filepath, const Color& color);
	void blit_surface( SDL_Texture* sourceTexture, SDL_Rect* srcRect, SDL_Rect* destRect );
	void flip();
	void clear();
	SDL_Renderer* get_renderer() const;

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	std::map<std::string, SDL_Surface*> sprite_sheets_;

};

#endif
