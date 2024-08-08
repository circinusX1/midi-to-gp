
#include "tgmeasureimpl.h"


const vvector TGMeasureImpl::KEY_SIGNATURES = vvector {
	std::vector<int> {NATURAL, NATURAL, NATURAL, NATURAL, NATURAL, NATURAL, NATURAL},
	std::vector<int> {NATURAL, NATURAL, NATURAL, SHARP, NATURAL, NATURAL, NATURAL},
	std::vector<int> {SHARP, NATURAL, NATURAL, SHARP, NATURAL, NATURAL, NATURAL},
	std::vector<int> {SHARP, NATURAL, NATURAL, SHARP, SHARP, NATURAL, NATURAL},
	std::vector<int> {SHARP, SHARP, NATURAL, SHARP, SHARP, NATURAL, NATURAL},
	std::vector<int> {SHARP, SHARP, NATURAL, SHARP, SHARP, SHARP, NATURAL},
	std::vector<int> {SHARP, SHARP, SHARP, SHARP, SHARP, SHARP, NATURAL},
	std::vector<int> {SHARP, SHARP, SHARP, SHARP, SHARP, SHARP, SHARP},
	std::vector<int> {NATURAL, NATURAL, NATURAL, NATURAL, NATURAL, NATURAL, FLAT},
	std::vector<int> {NATURAL, NATURAL, FLAT, NATURAL, NATURAL, NATURAL, FLAT},
	std::vector<int> {NATURAL, NATURAL, FLAT, NATURAL, NATURAL, FLAT, FLAT},
	std::vector<int> {NATURAL, FLAT, FLAT, NATURAL, NATURAL, FLAT, FLAT},
	std::vector<int> {NATURAL, FLAT, FLAT, NATURAL, FLAT, FLAT, FLAT},
	std::vector<int> {FLAT, FLAT, FLAT, NATURAL, FLAT, FLAT, FLAT},
	std::vector<int> {FLAT, FLAT, FLAT, FLAT, FLAT, FLAT, FLAT}
};


const vvector TGMeasureImpl::SCORE_KEY_SHARP_POSITIONS = vvector
{
	std::vector<int> {1, 4, 0, 3, 6, 2, 5},
	std::vector<int> {3, 6, 2, 5, 8, 4, 7},
	std::vector<int> {7, 3, 6, 2, 5, 1, 4},
	std::vector<int> {2, 5, 1, 4, 7, 3, 6}
};
const vvector TGMeasureImpl::SCORE_KEY_FLAT_POSITIONS = vvector
{
	std::vector<int> {5, 2, 6, 3, 7, 4, 8},
	std::vector<int> {7, 4, 8, 5, 9, 6, 10},
	std::vector<int> {4, 1, 5, 2, 6, 3, 7},
	std::vector<int> {6, 3, 7, 4, 8, 5, 9}
};
