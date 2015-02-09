//
// scatpointBrush.cpp
//
// The implementation of Scatpoint Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatpointBrush.h"

extern float frand();

ScatpointBrush::ScatpointBrush( ImpressionistDoc* pDoc, const char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatpointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void ScatpointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}
    
    int size = pDoc->getSize();
    
    int half_size = size / 2;
    
    glPointSize(1);
    
    
    for (int i = -half_size; i < half_size; i++) {
        for (int j = -half_size; j < half_size; j++) {
            
            if (frand() < 0.8f) continue;
            Point p = Point(target.x + i, target.y + j);
            
            if (pDoc->getMultiColor()) ImpBrush::c_pBrushes[BRUSH_POINTS]->BrushMove(p, p);
            else ImpBrush::c_pBrushes[BRUSH_POINTS]->BrushMove(source, p);
        }
    }
}

void ScatpointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

