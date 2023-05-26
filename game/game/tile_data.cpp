#include <memory>

#include "tile_data.h"

std::unique_ptr<tile_data_t[]> load_tile_data(void)
{
	std::unique_ptr<tile_data_t[]> tile_data = 
				std::make_unique<tile_data_t[]>(20);

	tile_data[0].hard = 0;
	tile_data[0].shift_x = 0;
	tile_data[0].shift_y = 0;

	tile_data[1].hard = 0;
	tile_data[1].shift_x = 0;
	tile_data[1].shift_y = 0;
	
	tile_data[2].hard = 1;
	tile_data[2].shift_x = 0;
	tile_data[2].shift_y = 0;
	
	tile_data[3].hard = 0;
	tile_data[3].shift_x = 0;
	tile_data[3].shift_y = 0;
	
	tile_data[4].hard = 0;
	tile_data[4].shift_x = 0;
	tile_data[4].shift_y = 0;
	
	tile_data[5].hard = 0;
	tile_data[5].shift_x = 0;
	tile_data[5].shift_y = 0;
	
	tile_data[6].hard = 0;
	tile_data[6].shift_x = 0;
	tile_data[6].shift_y = 0;
	
	tile_data[7].hard = 0;
	tile_data[7].shift_x = 0;
	tile_data[7].shift_y = 0;
	
	tile_data[8].hard = 1;
	tile_data[8].shift_x = 0;
	tile_data[8].shift_y = 0;
	
	tile_data[9].hard = 0;
	tile_data[9].shift_x = 0;
	tile_data[9].shift_y = 0;
	
	tile_data[10].hard = 1;
	tile_data[10].shift_x = 0;
	tile_data[10].shift_y = 0;

	return tile_data;
}
