#pragma once

//custom structure which is almost the same as RECT 
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

	bool isIn(Vector2D in) const
	{
		return (in.x >= left && in.x < right + 1 && in.y >= top && in.y < bottom + 1);
	}

	bool isInHorizontally(Vector2D in) const
	{
		return (in.x >= left && in.x < right + 1);
	}

	bool isInVertically(Vector2D in) const
	{
		return (in.y >= top && in.y < bottom + 1);
	}

};