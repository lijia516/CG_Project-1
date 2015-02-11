//
// impBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "impBrush.h"
#include <iostream>

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   const char*			name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
const char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[4];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
    
   
    if (pDoc->getColorBlending()) {
        
        std::cout<<pDoc->m_pUI->m_ColorChooser->r()<<","<<pDoc->m_pUI->m_ColorChooser->g()<<","<<pDoc->m_pUI->m_ColorChooser->b()<<"\n";
        
        color[0] = (color[0] + static_cast<GLubyte> (pDoc->m_pUI->m_ColorChooser->r() * 255.0f)) / 2;
        color[1] = (color[1] + static_cast<GLubyte> (pDoc->m_pUI->m_ColorChooser->g() * 255.0f)) / 2;
        color[2] = (color[2] + static_cast<GLubyte> (pDoc->m_pUI->m_ColorChooser->b() * 255.0f)) / 2;
    }
    
    
    color[3] = static_cast<GLubyte>(255.0f * pDoc->getAlpha());
	glColor4ubv( color );

}
