#include "StdAfx.h"
#include "OsamaDistance.h"
#include <cassert>
#include <ctime>
#include <random>
#include <limits>

OsamaDistance::OsamaDistance( void )
{
}
// ----------------------------------------------------------------------------


OsamaDistance::~OsamaDistance( void )
{
}
// ----------------------------------------------------------------------------

void OsamaDistance::FillWallsMatrix( const size_t wallsNumber )
{
	assert(wallsNumber <= MATRIX_SIZE*MATRIX_SIZE);

    //fill existing mWallsMatrix and mParentsMatrix with zeroes
    for(size_t x = 0; x < MATRIX_SIZE; ++x)
        for(size_t y = 0; y < MATRIX_SIZE; ++y)
        {
            mWallsMatrix[x][y] = 0;
            mParentsMatrix[x][y] = std::pair<size_t, size_t>(0, 0);
        }

    //generate random number
	std::default_random_engine gen(static_cast<size_t>(time(NULL)));
	std::uniform_int_distribution<size_t> index_rand(0, MATRIX_SIZE-1);

    //fill wmwallMatrix with 1 at postion on random genrated number
    //1 will indicate build obstacle there
	for(size_t i = 0; i < wallsNumber; ++i) 
	{
		size_t x = index_rand(gen), y = index_rand(gen);
		while(mWallsMatrix[x][y]) 
		{
			++x;
			if(x == MATRIX_SIZE)
				x = 0, ++y;
			if(y == MATRIX_SIZE)
				y = 0;
		}
		mWallsMatrix[x][y] = 1;
	}	
}

// ------------------Decide element location w.r.t nearest point used by findpath()----------------------------------------------------------
std::vector<std::pair<size_t, size_t> > OsamaDistance::GetElementsTo( const std::pair<size_t, size_t> &position ) const
{
	std::vector<std::pair<size_t, size_t> > elementsTo;
	size_t x = position.first, y = position.second;
//if x of point is greater than
	if(x > 0 && !mMarkedMatrix[x-1][y]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x-1, y));

	if(x < MATRIX_SIZE-1 && !mMarkedMatrix[x+1][y]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x+1, y));

	if(y > 0 && !mMarkedMatrix[x][y-1]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x, y-1));

	if(y < MATRIX_SIZE-1 && !mMarkedMatrix[x][y+1]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x, y+1));
	
	return elementsTo;
}
// ----------------------------------------------------------------------------


bool OsamaDistance::OsamaDistanceFindPath( const std::pair<size_t, size_t> startPosition )
{
	// If there is wall on start position
    //false means path not find and true means theres exist path
	if(mWallsMatrix[startPosition.first][startPosition.second])
	{
		return false;
	}

    // Initialize the matrix in which distance will be stored
    const size_t INF = size_t()-1;                         //set INF value to max value of type size_t
	for(size_t x = 0; x < mDistancesMatrix.size(); ++x)
		for(size_t y = 0; y < mDistancesMatrix[0].size(); ++y) 
		{
            mDistancesMatrix[x][y] = INF;               //initial distance is max i.e infinite
            mParentsMatrix[x][y] = startPosition;       //intialize paren with (0,0)
            mMarkedMatrix[x][y] = mWallsMatrix[x][y];   //set those matrix as marked which on which wall exist
		}
    mDistancesMatrix[0][0] = 0;

   //reset added matrix to not include previous values in next calculation
	for(size_t i = 0; i < mAddedMatrix.size(); ++i) 
	{
		mAddedMatrix[i].reset();
	}

    //set current position to (0,0)
	std::pair<size_t, size_t> curPosition = startPosition;
	mMarkedMatrix[startPosition.first][startPosition.second] = true;

    //use canidateformarks to print
    std::vector<std::pair<size_t, size_t>> candidatesForMark;
	candidatesForMark.push_back(startPosition);	

	while(!candidatesForMark.empty()) 
    {
		size_t iForMarked = 0;

		curPosition = candidatesForMark[iForMarked];
		size_t currentDistance = mDistancesMatrix[curPosition.first][curPosition.second];
		
		for(size_t i = 0; i < candidatesForMark.size(); ++i) 
		{
			size_t x = candidatesForMark[i].first, y = candidatesForMark[i].second;


			if (!mMarkedMatrix[x][y] && (mDistancesMatrix[x][y] < currentDistance)) 
			{
				curPosition = candidatesForMark[i];
				currentDistance = mDistancesMatrix[x][y];	
				iForMarked = i;
			}
		}

		// If there are no more reachable position then exit
		if(currentDistance == INF) 
		{
			break;
		}

		candidatesForMark.erase(candidatesForMark.cbegin() + iForMarked);
		mMarkedMatrix[curPosition.first][curPosition.second] = true;

		// Get the nearest elements to try to change(reduce) its distance
		std::vector<std::pair<size_t, size_t> > elementsTo = GetElementsTo(curPosition);

		for(size_t i = 0; i < elementsTo.size(); ++i) 
		{
			size_t x = elementsTo[i].first, y = elementsTo[i].second;
			const size_t len = 1, toDistance = mDistancesMatrix[x][y];

			if(currentDistance + len < toDistance) 
			{
				mDistancesMatrix[x][y] = currentDistance + len;
				mParentsMatrix[x][y] = curPosition;
			}

			if(!mAddedMatrix[x][y]) 
			{
				candidatesForMark.push_back(elementsTo[i]);
				mAddedMatrix[x][y] = true;
			}
		}
	}

	if(mDistancesMatrix[MATRIX_SIZE-1][MATRIX_SIZE-1] == INF) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

// ----------------------------------------------------------------------------
