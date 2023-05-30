#ifndef BOSS_SPRITE_H_
#define BOSS_SPRITE_H_

#include <memory>

#include "sprite.h"
#include "sprite_skin.h"

#include "question_ui.h"

class BossSprite : public Sprite {
private:
	int x, y;
	QuestionUI qui;

public:
	void animate(void) override;
	void on_click(void) override;

	void set_pos_x(int x) {this->x = x;};
	void set_pos_y(int y) {this->y = y;};

	BossSprite(std::shared_ptr<SpriteSkin> skin,
		   int x, int y, QuestionUI qui,
		   int z_order = 0);
	~BossSprite(void) override {};
};

#endif /* BOSS_SPRITE_H_ */
