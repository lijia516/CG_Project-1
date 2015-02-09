//
// randScatlineBrush.h
//
// The header file for Scatline Brush.
//

#ifndef RANDSCATLINEBRUSH_H
#define RANDSCATLINEBRUSH_H

#include "impBrush.h"

class RandScatlineBrush : public ImpBrush
{
public:
	RandScatlineBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif
