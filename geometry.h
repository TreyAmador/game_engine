#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <SDL.h>


// could implement cross product / dot product....
struct Vector2D {
	float x, y;
	Vector2D() :
		x(0.0f), y(0.0f)
	{}
	Vector2D(int x, int y) :
		x(static_cast<float>(x)),
		y(static_cast<float>(y))
	{}
	Vector2D(float x, float y) :
		x(x), y(y)
	{}
	Vector2D(const Vector2D& vec) :
		x(vec.x), y(vec.y)
	{}
};


struct Point2D {
	int x, y;
	Point2D() : 
		x(0), y(0)
	{}
	Point2D(int x, int y) : 
		x(x), y(y)
	{}
	Point2D(const Point2D& point) : 
		x(point.x), y(point.y) 
	{}
	void operator=(const Point2D& rh) {
		x = rh.x;
		y = rh.y;
	}
	void operator+=(const Point2D& rh) {
		x += rh.x;
		y += rh.y;
	}
};


struct Rectangle {

	int x, y;
	int w, h;

	Rectangle() :
		x(0), y(0), w(0), h(0)
	{}
	Rectangle(int x, int y) :
		x(x), y(y), w(0), h(0)
	{}
	Rectangle(int x, int y, int w, int h) :
		x(x), y(y), w(w), h(h)
	{}
	Rectangle(const Point2D& point) :
		x(point.x), y(point.y), w(0), h(0)
	{}
	Rectangle(const SDL_Rect& rect) :
		x(rect.x), y(rect.y), w(rect.w), h(rect.h)
	{}

	void operator+=(const Point2D& point) {
		x += point.x;
		y += point.y;
	}

	int top() const { return y; }
	int bottom() const { return y + h; }
	int left() const { return x; }
	int right() const { return x + w; }

	int width() const { return w; }
	int height() const { return h; }

	SDL_Rect SDL_Rectangle() {
		return { x, y, w, h };
	}

	bool collidesWith( const Rectangle& rect ) const {
		return
			top() <= rect.bottom() &&
			bottom() >= rect.top() &&
			left() <= rect.right() &&
			right() >= rect.left();
	}
};

#endif
