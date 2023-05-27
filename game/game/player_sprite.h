#ifndef PLAYER_SPRITE_H_
#define PLAYER_SPRITE_H_

#include <memory>

#include "sprite.h"
#include "sprite_skin.h"

class PlayerSprite : public Sprite {
public:
	void animate(void) override;

	PlayerSprite(std::shared_ptr<SpriteSkin> skin,
		     int z_order = 0);
	~PlayerSprite(void) override {};
};

#endif /* PLAYER_SPRITE_H_ */
