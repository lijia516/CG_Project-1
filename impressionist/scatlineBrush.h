//
// scatlineBrush.h
//
// The header file for Scatline Brush.
//

#ifndef SCATLINEBRUSH_H
#define SCATLINEBRUSH_H

#include "impBrush.h"

class ScatlineBrush : public ImpBrush
{
public:
	ScatlineBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif
