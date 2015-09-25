//
// CircleBrush.h
//
// The header file for Circle Brush.
//

#ifndef CIRCLEBRUSH_H
#define CIRCLEBRUSH_H

#include "ImpBrush.h"
#include <math.h>

class CircleBrush : public ImpBrush
{
public:
	CircleBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );

	void DrawCircle(Point source, Point target, float r, bool flag = 0, double R = 0, double G = 0, double B = 0,
		int H = 0, int S = 0, int V = 0);
};

#endif
