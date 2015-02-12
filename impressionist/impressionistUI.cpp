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

static int    m_npreviewNum;

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
	void ImpressionistUI::c(Fl_Menu_* o, void* v)
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
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v)
{
    ImpressionistDoc *pDoc=whoami(o)->getDocument();
    
    char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getAnotherImageName() );
    if (newfile != NULL) {
        pDoc->loadAnotherImage(newfile);
        pDoc->hasAnotherImage = true;
    }
}


//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_black_and_white_image(Fl_Menu_* o, void* v)
{
    ImpressionistDoc *pDoc=whoami(o)->getDocument();
    
    char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getBlackAndWhiteImageName() );
    if (newfile != NULL) {
        pDoc->loadBlackAndWhiteImage(newfile);
        pDoc->hasBlackAndWhiteImage = true;
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
    m_npreviewNum = 0;
    whoami(o)->scale = 1;
    whoami(o)->offset = 0;
    whoami(o)->m_nKernelWidth = 5;
    whoami(o)->m_nKernelHeight = 5;
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
// Auto paint.
// Called by the UI when the auto paint button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_auto_paint_button(Fl_Widget* o, void* v)
{
    ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
    
    pDoc->autoPaint();
    
}


//------------------------------------------------------------
// Auto paint.
// Called by the UI when the auto paint button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_coarse_to_fine_paint_button(Fl_Widget* o, void* v)
{
    ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
    
    pDoc->coarseToFinePainting();
    
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
    
    
    if (pDoc->m_ucEdgeImage) {
            
        if (pDoc->hasEdgeImage == false) {
            pDoc->getEdgeImage();
            pDoc->hasEdgeImage = true;
        }
        pDoc->m_pUI->m_origView->setOriginalView(2);
        pDoc->m_pUI->m_origView->refresh();
    }
    
}


//------------------------------------------------------------
// Show the grayscale image in the origin view
// Called by the UI when the grayscale image menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_view_grayscale_image(Fl_Menu_* o, void* v)
{
    
    ImpressionistDoc* pDoc=whoami(o)->getDocument();
    
    if (pDoc->m_ucGrayscaleImage) {
        
        if (pDoc->hasGrayscaleImage == false) {
             pDoc->getGrayscaleImage();
             pDoc->hasGrayscaleImage = true;
            
        }
        
        pDoc->m_pUI->m_origView->setOriginalView(1);
        pDoc->m_pUI->m_origView->refresh();
    }
   
    
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
    
    if (type == 1 || type == 4) {
        
        pUI->m_LineAngleTypeChoice->activate();
        pUI->m_BrushLineWidthSlider->activate();
        pUI->m_BrushLineAngleSlider->activate();
        
    }else{
        
        pUI->m_LineAngleTypeChoice->deactivate();
        pUI->m_BrushLineWidthSlider->deactivate();
        pUI->m_BrushLineAngleSlider->deactivate();
        pUI->m_AnotherGradientLightButton->deactivate();
    }
    
    if (type == 3 || type == 4 || type == 5 || type == 7) {
        
        pUI->m_MultiColorLightButton->activate();
        
    }else {
        
        pUI->m_MultiColorLightButton->deactivate();
    }
    
    
    if (type == 0 || type == 3) {
        
        pUI->m_EdgeClippingLightButton->deactivate();
        pUI->m_AnotherEdgeClippingLightButton->deactivate();
        
    } else {
        
        pUI->m_EdgeClippingLightButton->activate();
        pUI->m_AnotherEdgeClippingLightButton->activate();
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
    
    pUI->m_nLineAngleType = lineAngleType;
    
    switch (lineAngleType) {
        case SLIDER_RIGHT:
            pUI->m_BrushLineAngleSlider->activate();
            pUI->m_AnotherGradientLightButton->deactivate();
            break;
            
        case BRUSH_DIRECTION:
            pUI->m_BrushLineAngleSlider->deactivate();
            pUI->m_AnotherGradientLightButton->deactivate();
            break;
            
        case GRADIENT:
            pUI->m_BrushLineAngleSlider->deactivate();
            pUI->m_AnotherGradientLightButton->activate();
            break;
            
        default:
            break;
    }
    
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
            
            for (int i = 0; i < FLT_WIDTH * FLT_HEIGHT; i++) {
                
                    pUI->m_KernelValues[i] -> value("1");
            
            }
            
            break;
            
            
        case BARTLETT_FILTER:
            
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    
                    int temp = 5 - abs(i-2)-abs(j-2);
                    
                    if (temp < 0) temp = 0;
                    
                    char* c = new char[1];
                    c[0] = temp+'0';
                    
                    pUI->m_KernelValues[i*5+j]->value(c);
                }
            }
            
            break;
            
            
        case GAUSSIAN_FILTER:
            
            pUI->m_KernelValues[0]->value("1");
            pUI->m_KernelValues[1]->value("4");
            pUI->m_KernelValues[2]->value("7");
            pUI->m_KernelValues[3]->value("4");
            pUI->m_KernelValues[4]->value("1");
            
            pUI->m_KernelValues[5]->value("4");
            pUI->m_KernelValues[6]->value("16");
            pUI->m_KernelValues[7]->value("26");
            pUI->m_KernelValues[8]->value("16");
            pUI->m_KernelValues[9]->value("4");
            
            pUI->m_KernelValues[10]->value("7");
            pUI->m_KernelValues[11]->value("26");
            pUI->m_KernelValues[12]->value("41");
            pUI->m_KernelValues[13]->value("26");
            pUI->m_KernelValues[14]->value("7");
            
            pUI->m_KernelValues[15]->value("4");
            pUI->m_KernelValues[16]->value("16");
            pUI->m_KernelValues[17]->value("26");
            pUI->m_KernelValues[18]->value("16");
            pUI->m_KernelValues[19]->value("4");
            
            pUI->m_KernelValues[20]->value("1");
            pUI->m_KernelValues[21]->value("4");
            pUI->m_KernelValues[22]->value("7");
            pUI->m_KernelValues[23]->value("4");
            pUI->m_KernelValues[24]->value("1");
            
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
    ((ImpressionistUI*)(o->user_data()))->scale = atoi( ((Fl_Float_Input *)o)->value() );
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
    
    double* values = new double[5 * 5];
    
    for (int i = 0; i < 25; i++) {
            
        values[i] = (double) atoi( m_KernelValues[i] -> value());
        
    }

    
    return values;
}


//------------------------------------------------------------
// Preview filter button in Apply filter diagonal.
// Called by the UI when the apply filter button is pushed
//------------------------------------------------------------


void ImpressionistUI::cb_preview_filter_button(Fl_Widget* o, void* v)
{
    ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
    
    if (m_npreviewNum == 0) {
        m_npreviewNum = 1;
    
        pDoc->m_ucTempPointer = pDoc->m_ucPainting;
    }
    
    
    const unsigned char* sourceBuffer = pDoc->m_ucPainting;
    

    
    unsigned char* temp = new unsigned char [pDoc->m_nPaintWidth*pDoc->m_nPaintHeight*3];
    
    unsigned char* destBuffer = temp;
    
    
    int srcBufferWidth = pDoc->m_nWidth;
    int srcBufferHeight = pDoc->m_nHeight;
    
    const double *filterKernel = pDoc->m_pUI->getKernelValues();
    
    
    int m_scale = pDoc->m_pUI->scale;
    int m_offset = pDoc->m_pUI->offset;
    int m_KernelWidth = pDoc->m_pUI->m_nKernelWidth;
    int m_KernelHeight = pDoc->m_pUI->m_nKernelHeight;
    
    pDoc->applyFilter(sourceBuffer, srcBufferWidth, srcBufferHeight, destBuffer, filterKernel, m_KernelWidth, m_KernelHeight, m_scale, m_offset);
    
    pDoc->m_ucPainting = temp;
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
    pDoc->m_ucTempPointer = pDoc->m_ucPainting;
    m_npreviewNum = 0;
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
    
    ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
    pDoc->m_ucPainting = pDoc->m_ucTempPointer;
    m_paintView->refresh();
    
    m_npreviewNum = 0;
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
void ImpressionistUI::cb_drawSpaceSlides(Fl_Widget* o, void* v)
{
    ((ImpressionistUI*)(o->user_data()))->m_nDrawSpace=int( ((Fl_Slider *)o)->value() ) ;
}


//-----------------------------------------------------------
// Updates the brush alpha value to use from the value of the alpha
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



//-----------------------------------------------------------
// Updates the edge clipping status from the edge clipping
// light button
// Called by the UI when the line width edge clipping light button is pressed
//-----------------------------------------------------------
void ImpressionistUI::cb_edgeClippingLightButton(Fl_Widget* o, void* v)
{
    ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    
    if (pUI->m_nEdgeClipping==TRUE) pUI->m_nEdgeClipping=FALSE;
    
    else {
        
        pUI->m_nEdgeClipping=TRUE;
        
        if (pDoc->hasEdgeImage == false) {
            
            if (pDoc->m_ucEdgeImage) {
                
                pDoc->getEdgeImage();
                pDoc->hasEdgeImage = true;
            }
        }
        
    }
}


//-----------------------------------------------------------
// Updates the gradience status from the perpendicular to gradient from anther image
// light button
// Called by the UI when the line width edge clipping light button is pressed
//-----------------------------------------------------------
void ImpressionistUI::cb_anotherEdgeClippingLightButton(Fl_Widget* o, void* v)
{
    ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    
    if (pUI->m_nAnotherEdgeClipping==TRUE) pUI->m_nAnotherEdgeClipping=FALSE;
    
    else {
        
        pUI->m_nAnotherEdgeClipping=TRUE;
        
        if (pDoc->hasBlackAndWhiteImage == false) {
            
            char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getBlackAndWhiteImageName() );
            if (newfile != NULL) {
                pDoc->loadBlackAndWhiteImage(newfile);
                pDoc->hasBlackAndWhiteImage = true;
            }
            
        }
    }
}


//-----------------------------------------------------------
// Updates the gradience status from the perpendicular to gradient from anther image
// light button
// Called by the UI when the line width edge clipping light button is pressed
//-----------------------------------------------------------
void ImpressionistUI::cb_anotherGradientLightButton(Fl_Widget* o, void* v)
{
    ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    
    if (pUI->m_nAnotherGradient==TRUE) pUI->m_nAnotherGradient=FALSE;
    
    else {
        
        pUI->m_nAnotherGradient=TRUE;
        
        if (pDoc->hasAnotherImage == false) {
            
            char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getAnotherImageName() );
            if (newfile != NULL) {
                pDoc->loadAnotherImage(newfile);
                pDoc->hasAnotherImage = true;
            }
            
        }
    }
}




//-----------------------------------------------------------
// Updates the multicolor status from the edge clipping
// light button
// Called by the UI when the line width edge clipping light button is pressed
//-----------------------------------------------------------
void ImpressionistUI::cb_multiColorLightButton(Fl_Widget* o, void* v)
{
    ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    
    if (pUI->m_nMultiColor==TRUE) pUI->m_nMultiColor=FALSE;
    
    else {
        
        pUI->m_nMultiColor=TRUE;
        
    }
}


//-----------------------------------------------------------
// Updates the multicolor status from the edge clipping
// light button
// Called by the UI when the line width edge clipping light button is pressed
//-----------------------------------------------------------
void ImpressionistUI::cb_colorBlendingLightButton(Fl_Widget* o, void* v)
{
    ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    
    if (pUI->m_nColorBlending==TRUE) pUI->m_nColorBlending=FALSE;
    
    else {
        
        pUI->m_nColorBlending=TRUE;
        
    }
    
        std::cout << "color blending: " << pUI->m_nColorBlending << "\n";
}


//-----------------------------------------------------------
// Updates the rand space status from the edge clipping
// light button
// Called by the UI when the line width edge clipping light button is pressed
//-----------------------------------------------------------
void ImpressionistUI::cb_randSpaceLightButton(Fl_Widget* o, void* v)
{
    ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));
    ImpressionistDoc* pDoc=pUI->getDocument();
    
    
    if (pUI->m_nRandSpace==TRUE) pUI->m_nRandSpace=FALSE;
    
    else {
        
        pUI->m_nRandSpace=TRUE;
        
    }
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
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getDrawSpace()
{
    return m_nDrawSpace;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setDrawSpace( int drawSpace )
{
    m_nDrawSpace=drawSpace;
    
    if (drawSpace<=20 && drawSpace > 0)
        m_DrawSpaceSlider->value(m_nDrawSpace);
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
// Return the color blending
//------------------------------------------------
bool ImpressionistUI::getColorBlending()
{
    return m_nColorBlending;
}


//------------------------------------------------
// Return the multi color
//------------------------------------------------
bool ImpressionistUI::getMultiColor()
{
    return m_nMultiColor;
}


//------------------------------------------------
// Return the random space
//------------------------------------------------
bool ImpressionistUI::getRandSpace()
{
    return m_nRandSpace;
}

//------------------------------------------------
// Return the multi color
//------------------------------------------------
bool ImpressionistUI::getEdgeClipping()
{
    return m_nEdgeClipping;
}

//------------------------------------------------
// Return the multi color
//------------------------------------------------
bool ImpressionistUI::getAnotherEdgeClipping()
{
    return m_nAnotherEdgeClipping;
}


//------------------------------------------------
// Return if use another gradient or not
//------------------------------------------------
bool ImpressionistUI::getAnotherGradient()
{
    return m_nAnotherGradient;
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
            m_nLineAngle = m_paintView->getBrushDirection();
            break;
            
        case GRADIENT:
            m_nLineAngle = m_paintView->getPerpendicularDirectionToGradient();
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
		//{ "&Color", FL_ALT + 'r', (Fl_Callback *)ImpressionistUI::cb_color_chooser },
        { "&Load Another Image...",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_another_image },
        { "&Load B&W Image...",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_black_and_white_image },
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
  {"Points",                FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",                 FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",               FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",      FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",       FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",     FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Triangle",              FL_ALT+'t', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_TRIANGLE},
  {"RandScattered Lines",	FL_ALT+'r', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_RANDSCATTERED_LINES},
  {0}
};

// Line brush angle choice menu definition
Fl_Menu_Item ImpressionistUI::lineAngleTypeMenu[NUM_LINE_ANGLE_TYPE+1] = {
    {"Slider/Right mouse",	FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_lineAngleChoice, (void *)SLIDER_RIGHT},
    {"Brush Direction",		FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_lineAngleChoice, (void *)BRUSH_DIRECTION},
    {"Perpendicular To Gradient",		FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_lineAngleChoice, (void *)GRADIENT},
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
    
    
    m_npreviewNum = 0;
    
    
    //--------------
    // filter
    m_applyFilterDialog = new Fl_Window(400, 325, "Apply Filter Dialog");
    
        // Add kernel scale
        m_KernelScaleInput = new Fl_Float_Input(100, 10, 50, 25, "Filter scale:");
        m_KernelScaleInput->user_data((void*)(this));   // record self to be used by static callback functions
        m_KernelScaleInput->value("1.0");
        m_KernelScaleInput->callback(cb_KernelScaleInput);
    
        // Add kernel offset
        m_KernelOffsetInput = new Fl_Float_Input(300, 10, 50, 25, "Filter offset:");
        m_KernelOffsetInput->user_data((void*)(this));   // record self to be used by static callback functions
        m_KernelOffsetInput->value("0.0");
        m_KernelOffsetInput->callback(cb_KernelOffsetInput);
    
    
    
        // add kernel value input
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                
                m_KernelValues[i*5+j] = new Fl_Float_Input(80 + 50 * i, 50 + 35 * j, 50, 30);
                m_KernelValues[i*5+j]->value("1.0");
            }
        }
    
    
        // Add a brush type choice to the dialog
        m_FilterTypeChoice = new Fl_Choice(55,235,150,25,"&Filter");
        m_FilterTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
        m_FilterTypeChoice->menu(filterTypeMenu);
        m_FilterTypeChoice->callback(cb_filterChoice);
    
    
    
    
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
    m_nDrawSpace = 5;
    
	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 500, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,230,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);
    
    
        // Add a line angle choice to the dialog
        m_LineAngleTypeChoice = new Fl_Choice(80,45,200,25,"&Line Angle");
        m_LineAngleTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
        m_LineAngleTypeChoice->menu(lineAngleTypeMenu);
        m_LineAngleTypeChoice->callback(cb_lineAngleChoice);
        m_LineAngleTypeChoice->deactivate();
		
        // Add clear canvas button
        m_ClearCanvasButton = new Fl_Button(295,10,95,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);
    
        // Add multi color button to control the color source of scatted brush
        m_MultiColorLightButton = new Fl_Light_Button(295,45,95,25,"&Multi Color");
        m_MultiColorLightButton->user_data((void*)(this));   // record self to be used by static callback functions
        m_MultiColorLightButton->callback(cb_multiColorLightButton);
        m_MultiColorLightButton->deactivate();
    
        // Add ddge clipping button
        m_EdgeClippingLightButton = new Fl_Light_Button(10,185,120,25,"&Edge Clipping");
        m_EdgeClippingLightButton->user_data((void*)(this));   // record self to be used by static callback functions
        m_EdgeClippingLightButton->callback(cb_edgeClippingLightButton);
        m_EdgeClippingLightButton->deactivate();
    
    
        // Add another gradient button
        m_AnotherEdgeClippingLightButton = new Fl_Light_Button(150,185,235,25,"& Edge Clipping Base on B&W file");
        m_AnotherEdgeClippingLightButton->user_data((void*)(this));   // record self to be used by static callback functions
        m_AnotherEdgeClippingLightButton->callback(cb_anotherEdgeClippingLightButton);
        m_AnotherEdgeClippingLightButton->deactivate();
    
    
        // Add another gradient button
        m_AnotherGradientLightButton = new Fl_Light_Button(10,230,235,25,"&Perpendicular to Another Gradient");
        m_AnotherGradientLightButton->user_data((void*)(this));   // record self to be used by static callback functions
        m_AnotherGradientLightButton->callback(cb_anotherGradientLightButton);
        m_AnotherGradientLightButton->deactivate();
    
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
    
        // Add auto paint
        m_AutoPaintButton = new Fl_Button(305,280,80,25,"&Auto Paint");
        m_AutoPaintButton->user_data((void*)(this));
        m_AutoPaintButton->callback(cb_auto_paint_button);
    
    
    
        // Add random space button to control the color source of scatted brush
        m_RandSpaceLightButton = new Fl_Light_Button(205,280,95,25,"&RandSpace");
        m_RandSpaceLightButton->user_data((void*)(this));   // record self to be used by static callback functions
        m_RandSpaceLightButton->callback(cb_randSpaceLightButton);
    
    
    
        // Add spacing slider to the dialog
        m_DrawSpaceSlider = new Fl_Value_Slider(10, 280, 150, 20, "draw\nspace");
        m_DrawSpaceSlider->user_data((void*)(this));	// record self to be used by static callback functions
        m_DrawSpaceSlider->type(FL_HOR_NICE_SLIDER);
        m_DrawSpaceSlider->labelfont(FL_COURIER);
        m_DrawSpaceSlider->labelsize(12);
        m_DrawSpaceSlider->minimum(1);
        m_DrawSpaceSlider->maximum(20);
        m_DrawSpaceSlider->step(1);
        m_DrawSpaceSlider->value(m_nDrawSpace);
        m_DrawSpaceSlider->align(FL_ALIGN_RIGHT);
        m_DrawSpaceSlider->callback(cb_drawSpaceSlides);
        m_DrawSpaceSlider->activate();
    
    
        // Add auto paint
        m_CoarseToFinePaintButton = new Fl_Button(250,230,135,25,"&CoarseToFine Paint");
        m_CoarseToFinePaintButton->user_data((void*)(this));
        m_CoarseToFinePaintButton->callback(cb_coarse_to_fine_paint_button);
    
    
    
        // Add random space button to control the color source of scatted brush
        m_colorBlendingLightButton = new Fl_Light_Button(10,320,130,25,"&Color Blending");
        m_colorBlendingLightButton->user_data((void*)(this));   // record self to be used by static callback functions
        m_colorBlendingLightButton->callback(cb_colorBlendingLightButton);
    
        // color chooser
        m_ColorChooser = new Fl_Color_Chooser(10, 350, 300, 125);
        m_ColorChooser->user_data((void*)(this));
        m_ColorChooser->rgb(1,1,1);
    
    m_brushDialog->end();

}

ImpressionistUI::~ImpressionistUI()
{
}
