//
// alphaMapBrush.h
//
// The header file for AlphaMap Brush.
//

#ifndef ALPHAMAPBRUSH_H
#define ALPHAMAPBRUSH_H

#include "impBrush.h"
#define EDGES 200

class AlphaMapBrush : public ImpBrush
{
public:
	AlphaMapBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
    void setAlphaMapBrushColor(Point source, int alphaMap_x, int alphaMap_y);
	char* BrushName( void );
};

#endif
