#ifndef TILE_SPRITE_H_
#define TILE_SPRITE_H_

#include "sprite.h"

class TileSprite : public Sprite {
public:
	int x, y;
	int index;
	int block_id;

	void translate(int, int);
	void animate(void) override;
	void on_click(void) override;

	TileSprite(std::shared_ptr<TextureSkin> &skin, Rect bounds,
		   enum bounds_action bounds_action,
		   int z_order = 0);
	~TileSprite(void) override;
};

#endif /* TILE_SPRITE_H_ */
