/*
 * MapUtilities.h
 *
 *  Created on: Jul 14, 2015
 *      Author: colman
 */

#ifndef MAPUTILITIES_H_
#define MAPUTILITIES_H_
#include <cstdlib>
#include <cmath>
#include <vector>

#include "../Constants.h"
#include "../Png/lodepng.h"

using std::vector;

class MapUtilities {
public:
	MapUtilities();
	virtual ~MapUtilities();

	static bool* ConvertPngToRawPixels(vector<unsigned char>& png_image,
									  const unsigned int image_height,
									  const unsigned int image_width);
	static bool IsRgbaPixelWhite(vector<unsigned char>& png_image,
								 const unsigned int pixel_index);
	static GridCell** CreateCompressedGridMap(bool* raw_pixels_image,
			  	  	  	  	  	  	  	  	  const unsigned int image_real_height,
			  	  	  	  	  	  	  	  	  const unsigned int image_real_width,
											  unsigned int& grid_height,
											  unsigned int& grid_width);
	static GridCell** InitializeGrid(const unsigned int grid_height,
									 const unsigned int grid_width);
	static void DeleteGrid(GridCell** grid_map,
			 	 	 	   const unsigned int grid_height);
	static void CopyGrid(GridCell** destination_grid,
						 GridCell** source_grid,
						 const unsigned int grid_height,
						 const unsigned int grid_width,
						 const unsigned int blow_grid_size);
	static bool AreaHasBlackPixel(bool* raw_pixels_image,
								  const unsigned int row,
								  const unsigned int col,
								  const unsigned int grid_width,
								  const unsigned int adjancent_height_ceiling,
								  const unsigned int adjancent_width_ceiling);
	static void CreateBlowedWeightedGridMap(GridCell** grid_map,
											const unsigned int grid_height,
											const unsigned int grid_width);
	static void BlowCurrentCellNeighbours(GridCell** grid_map,
										  const unsigned int current_cell_row,
										  const unsigned int current_cell_col,
										  const int blow_grid_size);
	static void WeightCurrentCellBasedOnNeighbours(GridCell** grid_map,
										  	  	   const int current_cell_row,
										  	  	   const int current_cell_col,
										  	  	   const int blow_grid_size);
};

#endif /* MAPUTILITIES_H_ */
