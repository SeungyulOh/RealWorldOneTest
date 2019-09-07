#pragma once

struct Region
{
	Region() {}
	Region(int _left, int _top, int _right, int _bottom) 
	:left(_left) , top(_top), right(_right) , bottom(_bottom) {}
	~Region() {}
	
	int left;
	int top;
	int right;
	int bottom;

	bool isIn(Vector2D in) 
	{
		return (in.x >= left && in.x <= right && in.y >= top && in.y <= bottom);
	}

	bool isInHorizontally(Vector2D in) 
	{
		return (in.x >= left && in.x <= right);
	}

	bool isInVertically(Vector2D in)
	{
		return (in.y >= top && in.y <= bottom);
	}

};