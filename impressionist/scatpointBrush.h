//
// ScatpointBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATPOINTBRUSH_H
#define SCATPOINTBRUSH_H

#include "impBrush.h"

class ScatpointBrush : public ImpBrush
{
public:
	ScatpointBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif
