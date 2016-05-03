#pragma once
#include <array>
#include <vector>
#include <bitset>
#include <utility>
class OsamaDistance
{
    //used by FindPath() to decide nearest point.
		std::vector<std::pair<size_t, size_t> > GetElementsTo( const std::pair<size_t, size_t> &position ) const;

public:
    OsamaDistance( void );
    ~OsamaDistance( void );

    //fill points i.e genrate obstacles more accurate tells their positions
	void FillWallsMatrix( const size_t wallsNumber );

    //method is used to find the path between elements, it uses dijkstra's alog
    bool OsamaDistanceFindPath( const std::pair<size_t, size_t> startPosition = std::make_pair(0, 0) );

    //size of the grid
    static const size_t MATRIX_SIZE = 20;

    //intialize 2D array if size[MATRIX_SIZE][MATRIX_SIZE]
	std::array<std::array<std::pair<size_t, size_t>, MATRIX_SIZE>, MATRIX_SIZE> mParentsMatrix;

    //intialize 2D array if size[MATRIX_SIZE][MATRIX_SIZE] & all its first columns values are 0 by using bitset
    std::array<std::bitset<MATRIX_SIZE>, MATRIX_SIZE> mWallsMatrix;

private:
    //intialize 2D array if size[MATRIX_SIZE][MATRIX_SIZE]
	std::array<std::array<size_t, MATRIX_SIZE>, MATRIX_SIZE> mDistancesMatrix;

    //intialize 2D array if size[MATRIX_SIZE] & all its first columns values are 0 by using bitset
    std::array<std::bitset<MATRIX_SIZE>, MATRIX_SIZE> mMarkedMatrix;

    //intialize 2D array if size[MATRIX_SIZE] & all its first column values are 0 by using bitset
	std::array<std::bitset<MATRIX_SIZE>, MATRIX_SIZE> mAddedMatrix;
};

