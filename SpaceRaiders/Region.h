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

	bool isIn(Vector2D in) const
	{
		//int x = static_cast<int>(in.x);
		//int y = static_cast<int>(in.y);
		//return (x >= left && x <= right && y >= top && y <= bottom);
		return (in.x >= left && in.x < right + 1 && in.y >= top && in.y < bottom + 1);
	}

	bool isInHorizontally(Vector2D in) const
	{
		/*int x = static_cast<int>(in.x);
		return (x >= left && x <= right);*/
		return (in.x >= left && in.x < right + 1);
	}

	bool isInVertically(Vector2D in) const
	{
		/*int y = static_cast<int>(in.y);
		return (y >= top && y <= bottom);*/
		return (in.y >= top && in.y < bottom + 1);
	}

};