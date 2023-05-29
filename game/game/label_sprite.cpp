#include <SFML/Graphics.hpp>
#include <memory>

#include "algebra.h"
#include "sprite.h"
#include "label_sprite.h"

LabelSprite::LabelSprite(double x, double y,
		         std::wstring *text_str) :
Sprite(std::make_shared<LabelSkin>(text_str), 10)
{
	this->set_position(Rect(x, y, 260.0, 20.0));
}

LabelSprite::~LabelSprite(void)
{
}
