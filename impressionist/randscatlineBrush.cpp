//
// randscatlineBrush.cpp
//
// The implementation of Random Scatline Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "randscatlineBrush.h"
#include <iostream>

extern float frand();

RandScatlineBrush::RandScatlineBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void RandScatlineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void RandScatlineBrush::BrushMove( const Point source, const Point target )
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
    
    for (int i = -half_size; i < half_size; i = i + 2) {
        for (int j = -half_size; j < half_size; j = j + 2) {
            
            if (frand() < 0.8f) continue;
            
            
            
            pDoc->setSize(size / 5 + 1);
            pDoc->setLineWidth(1);
            pDoc->setLineAngle(int(frand()*360));
            
          //  std::cout << "angle: " << frand()*360 << "\n";
            
            Point p = Point(target.x + i, target.y + j);
            ImpBrush::c_pBrushes[BRUSH_LINES]->BrushMove(p, p);
            // ImpBrush::c_pBrushes[BRUSH_CIRCLES]->BrushMove(source, p);
        }
    }
    
    pDoc->setSize(size);
    pDoc->setLineWidth(lineWidth);
    pDoc->setLineAngle(lineAngle);
}

void RandScatlineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

