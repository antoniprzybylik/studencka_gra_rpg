#ifndef TILE_DATA_H_
#define TILE_DATA_H_

#include <memory>

typedef struct {
	bool hard;
	int shift_x;
	int shift_y;
} tile_data_t;

std::unique_ptr<tile_data_t[]> load_tile_data(void);

#endif /* TILE_DATA_H_ */
