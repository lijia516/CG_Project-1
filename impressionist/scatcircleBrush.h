//
// scatcircleBrush.h
//
// The header file for Scatcircle Brush.
//

#ifndef SCATCIRCLEBRUSH_H
#define SCATCIRCLEBRUSH_H

#include "impBrush.h"

class ScatcircleBrush : public ImpBrush
{
public:
	ScatcircleBrush( ImpressionistDoc* pDoc = NULL, const char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif
