#ifndef LABEL_SPRITE_H_
#define LABEL_SPRITE_H_

#include "sprite.h"

class LabelSprite : public Sprite {
public:
	LabelSprite(double x, double y,
		    std::wstring *text_str);
	~LabelSprite(void) override;
};

#endif /* TILE_SPRITE_H_ */
