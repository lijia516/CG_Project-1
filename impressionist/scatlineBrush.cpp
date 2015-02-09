//
// scatlineBrush.cpp
//
// The implementation of Scatline Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatlineBrush.h"
#include <iostream>

extern float frand();

ScatlineBrush::ScatlineBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatlineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void ScatlineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

    int size = pDoc->getSize();
    int half_size = size / 2;
    int lineWidth = pDoc->getLineWidth();
    int lineAngle = pDoc->getLineAngle();
    
    for (int i = -half_size; i < half_size; i++) {
            
            if (frand() < 0.8f) continue;
            
            Point p = Point(target.x + i, target.y);
            if (pDoc->getMultiColor()) ImpBrush::c_pBrushes[BRUSH_LINES]->BrushMove(p, p);
            else ImpBrush::c_pBrushes[BRUSH_LINES]->BrushMove(source, p);
    }
}

void ScatlineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

