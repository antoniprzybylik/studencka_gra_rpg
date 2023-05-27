#ifndef BOSS_SPRITE_H_
#define BOSS_SPRITE_H_

#include <memory>

#include "sprite.h"
#include "sprite_skin.h"

class BossSprite : public Sprite {
private:
	int x, y;

public:
	void animate(void) override;

	BossSprite(std::shared_ptr<SpriteSkin> skin,
		   int x, int y, int z_order = 0);
	~BossSprite(void) override {};
};

#endif /* BOSS_SPRITE_H_ */
