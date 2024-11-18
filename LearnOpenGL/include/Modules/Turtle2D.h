#include <SDL2/SDL.h>
#include <cmath>
class Turtle2D {
public:
	Turtle2D() {
		mRenderer = nullptr;
		x = 0; y = 0;
		angle = 0;
		length = 1;
		isPenDown = false;
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}
	void SetRenderer(SDL_Renderer* renderer) {
		mRenderer = renderer;
	}
	// pen
	void PenUp() {
		isPenDown = false;
	}
	void PenDown() {
		isPenDown = true;
	}
	void SetPenColor(int r, int g, int b, int a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	// movement
	void SetAngle(float angle) {
		this->angle = angle;
	}
	void SetLength(float length) {
		this->length = length;
	}
	void RotateRight(float angle) {
		this.angle -= angle * (M_PI / 180.0);
	}
	void RotateLeft(float angle) {
		this.angle += angle * (M_PI / 180.0);
	}

	// set starting position
	void MoveTo(float x, float y) {

	}

	void Step() {
		// compute where the turtle will end up
		float startX = x;
		float startY = y;
		float endX = startX + length * cos(angle);
		float endY = startY + length * sin(angle);
		// move the turtle to the new position
		x = endX;
		y = endY;
		if (mRenderer && isPenDown) {

			SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
			SDL_RenderDrawLine(mRenderer, 
				static_cast<int>(round(startX)), static_cast<int>(round(startY)),
				static_cast<int>(round(endX)), static_cast<int>(round(endY)));
		}
	}

private:
	SDL_Renderer* mRenderer;
	float x, y;
	float angle;
	float length;
	char r, g, b, a;
	bool isPenDown;
};