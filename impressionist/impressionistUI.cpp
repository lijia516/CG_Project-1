//
// impressionistUI.cpp
//
// The user interface part for the program.
//

#include <iostream>
#include <FL/fl_ask.H>

#include <algorithm>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    myWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------


//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//-------------------------------------------------------------
// Brings up the apply filter dialog
// This is called by the UI when the apply filter menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_applyFilter(Fl_Menu_* o, void* v)
{
    whoami(o)->m_applyFilterDialog->show();
    whoami(o)->scale = 3;
    whoami(o)->offset = 3;
    whoami(o)->m_nKernelWidth = 3;
  //  whoami(o)->m_nHeightWidth = 3;
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}





//------------------------------------------------------------
// Show the edge image in the origin view
// Called by the UI when the original image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_view_edge_image(Fl_Menu_* o, void* v)
{
    
    ImpressionistDoc* pDoc=whoami(o)->getDocument();
    pDoc->m_pUI->m_origView->setOriginalView(2);
    
    // grayscale
    const unsigned char* sourceBuffer = pDoc->m_ucBitmap;
    int srcBufferWidth = pDoc->m_nWidth;
    int srcBufferHeight = pDoc->m_nHeight;
    unsigned char* destBuffer = pDoc->m_ucPreviewBackup;

    pDoc->grayscaleImage(sourceBuffer, destBuffer, srcBufferWidth, srcBufferHeight);
    
    
    
    // blurring
    double fltKernel[9] = {1,2,1,2,3,2,1,2,1};
    const double *filterKernel = fltKernel;
    
    int m_scale = pDoc->m_pUI->scale;
    int m_offset = pDoc->m_pUI->offset;
    int m_KernelWidth = 3; //pDoc->m_pUI->m_nKernelWidth;
    int m_KernelHeight = 3; //pDoc->m_pUI->m_nKernelHeight;
    
    sourceBuffer = pDoc->m_ucPreviewBackup;
    destBuffer = pDoc->m_ucPreviewBackup2;
    
    pDoc->applyFilter(sourceBuffer, srcBufferWidth, srcBufferHeight, destBuffer, filterKernel, m_KernelWidth, m_KernelHeight, m_scale, m_offset);
    
    double sobelEdgeDetectKnl1[9] = {1,2,1,0,0,0,-1,-2,-1};
    double sobelEdgeDetectKnl2[9] = {1,0,-1,2,0,-2,1,0,-1};
    
    
    // edge detection
    sourceBuffer = pDoc->m_ucPreviewBackup2;
   // destBuffer = pDoc->m_ucPainting;

    destBuffer = pDoc->m_ucEdgeImage;
    pDoc->edgeDetector(sourceBuffer, srcBufferWidth, srcBufferHeight, destBuffer, sobelEdgeDetectKnl1, sobelEdgeDetectKnl2, m_KernelWidth, m_KernelHeight);
    
   // pDoc->m_pUI->m_paintView->refresh();
    
    
    
    pDoc->m_pUI->m_origView->refresh();
    
}


//------------------------------------------------------------
// Show the grayscale image in the origin view
// Called by the UI when the grayscale image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_view_grayscale_image(Fl_Menu_* o, void* v)
{
    
    ImpressionistDoc* pDoc=whoami(o)->getDocument();
    pDoc->m_pUI->m_origView->setOriginalView(1);
    
    const unsigned char* sourceBuffer = pDoc->m_ucBitmap;
    unsigned char* destBuffer = pDoc->m_ucGrayscaleImage;
    int srcBufferWidth = pDoc->m_nWidth;
    int srcBufferHeight = pDoc->m_nHeight;
    pDoc->grayscaleImage(sourceBuffer, destBuffer, srcBufferWidth, srcBufferHeight);
    
    pDoc->m_pUI->m_origView->refresh();
    
}


//------------------------------------------------------------
// Show the original image in the origin view
// Called by the UI when the original image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_view_original_image(Fl_Menu_* o, void* v)
{
    
    ImpressionistDoc* pDoc=whoami(o)->getDocument();
    pDoc->m_pUI->m_origView->setOriginalView(0);
    
    pDoc->m_pUI->m_origView->refresh();
    
}


//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version 1.1.9 for CS 384G, Fall 2008");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	//	int type=(int)v;
	long long tmp = reinterpret_cast<long long>(v);
	int type = static_cast<int>(tmp);
    
    if (type == 1) {
        
        pUI->m_LineAngleTypeChoice->activate();
        pUI->m_BrushLineWidthSlider->activate();
        pUI->m_BrushLineAngleSlider->activate();
        
    }else{
        
        pUI->m_LineAngleTypeChoice->deactivate();
        pUI->m_BrushLineWidthSlider->deactivate();
        pUI->m_BrushLineAngleSlider->deactivate();
        
    }
    
    if (type == 4 || type == 5 || type == 6) {
        
        
        ///////////////////////////
        ///////multiColor stuff////
        //////////////////////////
        
    }
    
	pDoc->setBrushType(type);
}



//-------------------------------------------------------------
// Sets the type of line angle to use to the one chosen in the line angle type
// choice.
// Called by the UI when a line anlge type is chosen in the line anlge choice
//-------------------------------------------------------------
void ImpressionistUI::cb_lineAngleChoice(Fl_Widget* o, void* v)
{
    ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    //	int type=(int)v;
    long long tmp = reinterpret_cast<long long>(v);
    int lineAngleType = static_cast<int>(tmp);
    
    if (lineAngleType == 0) {
        
        pUI->m_BrushLineAngleSlider->activate();
    }else{
        
        pUI->m_BrushLineAngleSlider->deactivate();
    }
    
    pUI->m_nLineAngleType = lineAngleType;
}



//-------------------------------------------------------------
// Sets the type of kernel to use to the one chosen in the kernel type
// choice.
// Called by the UI when a kernel type is chosen in the kernel type choice
//-------------------------------------------------------------

void ImpressionistUI::cb_filterChoice(Fl_Widget* o, void* v)
{
    ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    long long tmp = reinterpret_cast<long long>(v);
    
    int type = static_cast<int>(tmp);
    
    switch (type) {
            
        case BOX_FILTER:
            
            for (int i = 0; i < 9; i++) {
                
                    pUI->m_KernelValues[i] -> value("1");
            
            }
            
            break;
            
            
        case BARTLETT_FILTER:
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    
                    int temp = 3 - abs(i-1)-abs(j-1);
                    char* c = new char[1];
                    c[0] = temp+'0';
                    
                    pUI->m_KernelValues[i*3+j]->value(c);
                }
            }
            
            break;
            
            
        case GAUSSIAN_FILTER:
            
            ///////////////////////
            
            break;
            
        default:
            break;
    }
    
    
    
}



// set kernel width
void ImpressionistUI::cb_KernelWidthInput(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->m_nKernelWidth = atoi(((Fl_Int_Input *)o)->value() );
}


// set kernel height
void ImpressionistUI::cb_KernelHeightInput(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->m_nKernelHeight = atoi( ((Fl_Int_Input *)o)->value() );
}


// set kernel scale
void ImpressionistUI::cb_KernelScaleInput(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->scale = atoi( ((Fl_Int_Input *)o)->value() );
}

// set kernel offset
void ImpressionistUI::cb_KernelOffsetInput(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->offset = atoi( ((Fl_Float_Input *)o)->value() );
}



// get kernel width
int ImpressionistUI::getKernelWidth()
{
    return m_nKernelWidth;
}

// get kernel height
int ImpressionistUI::getKernelHeight()
{
    return m_nKernelHeight;
}

// get kernel scale
int ImpressionistUI::getKernelScale()
{
    return scale;
}

// get kernel offset
int ImpressionistUI::getKernelOffset()
{
    return offset;
}

// get kernel value
double* ImpressionistUI::getKernelValues()
{
    
    double* values = new double[3 * 3];
    
    for (int i = 0; i < 9; i++) {
            
            values[i] = (double) atoi( m_KernelValues[i] -> value());
    }
    
    return values;
}


//------------------------------------------------------------
// Preview filter button in Apply filter diagonal.
// Called by the UI when the apply filter button is pushed
//------------------------------------------------------------
//void ImpressionistUI::static_cb_preview_filter_button(Fl_Widget* o, void* v)
//{
//    ((ImpressionistUI*)(o->user_data()))->cb_preview_filter_button(o, v);
//}

void ImpressionistUI::cb_preview_filter_button(Fl_Widget* o, void* v)
{
    ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
    
    const unsigned char* sourceBuffer = pDoc->m_ucBitmap;
    int srcBufferWidth = pDoc->m_nWidth;
    int srcBufferHeight = pDoc->m_nHeight;
    unsigned char* destBuffer = pDoc->m_ucPainting;
   // unsigned char* destBuffer = pDoc->m_ucPreviewBackup;
  //  double fltKernel[9] = {1,2,1,2,3,2,1,2,1};
  //  const double *filterKernel = fltKernel;
    
    const double *filterKernel = pDoc->m_pUI->getKernelValues();
    
    int m_scale = pDoc->m_pUI->scale;
    int m_offset = pDoc->m_pUI->offset;
    int m_KernelWidth = pDoc->m_pUI->m_nKernelWidth;
    int m_KernelHeight = pDoc->m_pUI->m_nKernelHeight;
    
    
    std::cout << "m_scale" << m_scale << "\n";
    std::cout << "m_offset" <<  m_offset << "\n";
    std::cout << "m_KernelWidth" << m_KernelWidth << "\n";
    std::cout << "m_KernelHeight" << m_KernelHeight << "\n";
    
    
    pDoc->applyFilter(sourceBuffer, srcBufferWidth, srcBufferHeight, destBuffer, filterKernel, m_KernelWidth, m_scale, m_KernelHeight, m_offset);
    
    pDoc->m_pUI->m_paintView->refresh();
}


//------------------------------------------------------------
// Apply filter button in Apply filter diagonal.
// Called by the UI when the apply filter button is pushed
//------------------------------------------------------------
void ImpressionistUI::static_cb_apply_filter_button(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->cb_apply_filter_button(o, v);
}

void ImpressionistUI::cb_apply_filter_button(Fl_Widget* o, void* v)
{
    ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
    
    const unsigned char* sourceBuffer = pDoc->m_ucBitmap;
    int srcBufferWidth = pDoc->m_nWidth;
    int srcBufferHeight = pDoc->m_nHeight;
    unsigned char* destBuffer = pDoc->m_ucPainting;
    
    double fltKernel[9] = {1,2,1,2,3,2,1,2,1};
    const double *filterKernel = fltKernel;
    
    pDoc->applyFilter(sourceBuffer, srcBufferWidth, srcBufferHeight, destBuffer, filterKernel, m_nKernelWidth, m_nKernelHeight, scale, offset);
    
    m_paintView->refresh();
}


//------------------------------------------------------------
// Cancle filter button in Apply filter diagonal.
// Called by the UI when the cancle filter button is pushed
//------------------------------------------------------------
void ImpressionistUI::static_cb_cancle_filter_button(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->cb_cancle_filter_button(o, v);
}

void ImpressionistUI::cb_cancle_filter_button(Fl_Widget* o, void* v)
{
    m_paintView->RestoreContent();
    m_paintView->refresh();
    m_applyFilterDialog->hide();
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->m_nAlpha=float( ((Fl_Slider *)o)->value() ) ;
}


//-----------------------------------------------------------
// Updates the line brush width to use from the value of the line width
// slider
// Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->m_nLineWidth=int( ((Fl_Slider *)o)->value() ) ;
}

//-----------------------------------------------------------
// Updates the line brush width to use from the value of the line width
// slider
// Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->m_nLineAngle=int( ((Fl_Slider *)o)->value() ) ;
}



//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}


//------------------------------------------------
// Return the brush alpha
//------------------------------------------------
float ImpressionistUI::getAlpha()
{
    return m_nAlpha;
}

//-------------------------------------------------
// Set the brush alpha
//-------------------------------------------------
void ImpressionistUI::setAlpha( float alpha )
{
    m_nAlpha=alpha;
    
    if (alpha<=1 && alpha>=0)
        m_BrushAlphaSlider->value(m_nAlpha);
}


//------------------------------------------------
// Return the line brush width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
    return m_nLineWidth;
}

//-------------------------------------------------
// Set the line brush width
//-------------------------------------------------
void ImpressionistUI::setLineWidth( int lineWidth )
{
    m_nLineWidth=lineWidth;
    
    if (lineWidth<=10)
        m_BrushLineWidthSlider->value(m_nLineWidth);
}


//------------------------------------------------
// Return the line brush angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
    
    switch (m_nLineAngleType) {
        case SLIDER_RIGHT:
            
            break;
            
        case BRUSH_DIRECTION:
            //???????????
            break;
            
        case GRADIENT:
            m_nLineAngle = m_paintView->getPointGradient();
            break;
            
        default:
            break;
    }
    
    return m_nLineAngle;
    
}

//-------------------------------------------------
// Set the line brush angle
//-------------------------------------------------
void ImpressionistUI::setLineAngle( int lineAngle )
{
    m_nLineAngle=lineAngle;
    
    if (lineAngle <= 2 * PI)
        m_BrushLineAngleSlider->value(m_nLineAngle);
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes },
        { "&Apply Filter...",	FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_applyFilter },
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

    { "&View",		0, 0, 0, FL_SUBMENU },
        { "&Original Image",	FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_view_original_image },
        { "&Grayscale Image",	FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_view_grayscale_image },
        { "&Edge Image",	FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_view_edge_image },
        { 0 },
    
    
	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {0}
};

// Line brush angle choice menu definition
Fl_Menu_Item ImpressionistUI::lineAngleTypeMenu[NUM_LINE_ANGLE_TYPE+1] = {
    {"Slider/Right mouse",	FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_lineAngleChoice, (void *)SLIDER_RIGHT},
    {"Brush Direction",		FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_lineAngleChoice, (void *)BRUSH_DIRECTION},
    {"Gradient",		FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_lineAngleChoice, (void *)GRADIENT},
    {0}
};


// Line brush angle choice menu definition
Fl_Menu_Item ImpressionistUI::filterTypeMenu[NUM_FILTER_TYPE+1] = {
    {"Box Filter",	FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_filterChoice, (void *)BOX_FILTER},
    {"Bartlett Filter",		FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_filterChoice, (void *)BARTLETT_FILTER},
    {"Gaussian Filter",		FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_filterChoice, (void *)GAUSSIAN_FILTER},
    {0}
};


//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

    
    //--------------
    // filter
    m_applyFilterDialog = new Fl_Window(400, 325, "Apply Filter Dialog");
    
        // Add kernel width/height input
        m_KernelWidthInput = new Fl_Int_Input(100, 10, 50, 25, "kernel width:");
        m_KernelWidthInput->user_data((void*)(this));   // record self to be used by static callback functions
        m_KernelWidthInput->value("3");
        m_KernelWidthInput->callback(cb_KernelWidthInput);
    
    
        m_KernelScaleInput = new Fl_Int_Input(100, 50, 50, 25, "kernel scale:");
        m_KernelScaleInput->user_data((void*)(this));   // record self to be used by static callback functions
        m_KernelScaleInput->value("1.0");
        m_KernelScaleInput->callback(cb_KernelScaleInput);
    
    
        // Add kernel scale/offset
    
    //    m_KernelScaleInput = new Fl_Float_Input(100, 50, 50, 25, "kernel scale:");
    //    m_KernelScaleInput->user_data((void*)(this));   // record self to be used by static callback functions
    //    m_KernelScaleInput->value("1.0");
    //    m_KernelScaleInput->callback(cb_KernelScaleInput);
    
        m_KernelOffsetInput = new Fl_Float_Input(300, 50, 50, 25, "kernel offset:");
        m_KernelOffsetInput->user_data((void*)(this));   // record self to be used by static callback functions
        m_KernelOffsetInput->value("1.0");
        m_KernelOffsetInput->callback(cb_KernelOffsetInput);
    
    
    
        // add kernel value input
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                
                m_KernelValues[i*3+j] = new Fl_Float_Input(110 + 50 * i, 110 + 40 * j, 50, 30);
                m_KernelValues[i*3+j]->value("1.0");
            }
        }
    
    
        // Add a brush type choice to the dialog
        m_FilterTypeChoice = new Fl_Choice(55,235,150,25,"&Filter");
        m_FilterTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
        m_FilterTypeChoice->menu(filterTypeMenu);
        m_FilterTypeChoice->callback(cb_filterChoice);
    
    
    
        // Add a set filter buttton to the dialog
    
    //    m_setFilterButton = new Fl_Button(300,10,100,25,"&Set Filter");
    //    m_setFilterButton->user_data((void*)(this));
    //    m_setFilterButton->callback(cb_set_filter_button);
    
    
    
        // Add a Preview filter button to the dialog
    
        m_PreviewFilterButton = new Fl_Button(20,280,100,25,"&Preview Filter");
        m_PreviewFilterButton->user_data((void*)(this));
        m_PreviewFilterButton->callback(cb_preview_filter_button);

    
    
        // Add a apply filter button to the dialog
    
        m_ApplyFilterButton = new Fl_Button(150,280,100,25,"&Apply Filter");
        m_ApplyFilterButton->user_data((void*)(this));
        m_ApplyFilterButton->callback(static_cb_apply_filter_button, this);
   
    
        // Add a cancle filter button to the dialog
    
        m_CancleFilterButton = new Fl_Button(280,280,100,25,"&Cancle Filter");
        m_CancleFilterButton->user_data((void*)(this));
        m_CancleFilterButton->callback(static_cb_cancle_filter_button, this);
    
    
    m_applyFilterDialog->end();
    
    
    
    
	// init values

	m_nSize = 10;
    m_nAlpha = 1.0;
    m_nLineWidth = 5;
    m_nLineAngle = 45;
    
	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);
    
    
        // Add a line angle choice to the dialog
        m_LineAngleTypeChoice = new Fl_Choice(120,45,150,25,"&Line Angle");
        m_LineAngleTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
        m_LineAngleTypeChoice->menu(lineAngleTypeMenu);
        m_LineAngleTypeChoice->callback(cb_lineAngleChoice);
        m_LineAngleTypeChoice->deactivate();
		
        m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);
    
        // Add alpha slider to the dialog
        m_BrushAlphaSlider = new Fl_Value_Slider(10, 105, 300, 20, "Alpha");
        m_BrushAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
        m_BrushAlphaSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushAlphaSlider->labelfont(FL_COURIER);
        m_BrushAlphaSlider->labelsize(12);
        m_BrushAlphaSlider->minimum(0);
        m_BrushAlphaSlider->maximum(1.0);
        m_BrushAlphaSlider->step(0.1);
        m_BrushAlphaSlider->value(m_nAlpha);
        m_BrushAlphaSlider->align(FL_ALIGN_RIGHT);
        m_BrushAlphaSlider->callback(cb_alphaSlides);
    
    
        // Add line brush width slider to the dialog
        m_BrushLineWidthSlider = new Fl_Value_Slider(10, 130, 300, 20, "Line Width");
        m_BrushLineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
        m_BrushLineWidthSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushLineWidthSlider->labelfont(FL_COURIER);
        m_BrushLineWidthSlider->labelsize(12);
        m_BrushLineWidthSlider->minimum(1);
        m_BrushLineWidthSlider->maximum(10);
        m_BrushLineWidthSlider->step(1);
        m_BrushLineWidthSlider->value(m_nLineWidth);
        m_BrushLineWidthSlider->align(FL_ALIGN_RIGHT);
        m_BrushLineWidthSlider->callback(cb_lineWidthSlides);
        m_BrushLineWidthSlider->deactivate();
    
    
        // Add line brush angle slider to the dialog
        m_BrushLineAngleSlider = new Fl_Value_Slider(10, 155, 300, 20, "Line Angle");
        m_BrushLineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
        m_BrushLineAngleSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushLineAngleSlider->labelfont(FL_COURIER);
        m_BrushLineAngleSlider->labelsize(12);
        m_BrushLineAngleSlider->minimum(0);
        m_BrushLineAngleSlider->maximum(359);
        m_BrushLineAngleSlider->step(1);
        m_BrushLineAngleSlider->value(m_nLineAngle);
        m_BrushLineAngleSlider->align(FL_ALIGN_RIGHT);
        m_BrushLineAngleSlider->callback(cb_lineAngleSlides);
        m_BrushLineAngleSlider->deactivate();
    
    
    

    m_brushDialog->end();	

}

ImpressionistUI::~ImpressionistUI()
{
}
