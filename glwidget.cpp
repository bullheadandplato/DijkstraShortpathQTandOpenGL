#include "StdAfx.h"
#include "glwidget.h"
#include<QMessageBox>
#include<iostream>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent), mWallsNumber(0)
{


	ui.setupUi(this);
	mCalcDistance.FillWallsMatrix(mWallsNumber);


}

GLWidget::~GLWidget()
{
}

void GLWidget::SetWallsNumber(int number) 
{
	mWallsNumber = (number < 0)? 0 : number;
}

void GLWidget::GenerateWalls() 
{
	mCalcDistance.FillWallsMatrix(mWallsNumber);
    paintGL();
	repaint();
}


void GLWidget::FindPath()
{
    QMessageBox msgBox;
    if(!mCalcDistance.OsamaDistanceFindPath())
	{

        msgBox.setText("Unable to find path!");
        msgBox.setWindowTitle("ERROR");


	}
    else if(xp!=0 || yp!=0){
        msgBox.setText("Path found.");
        msgBox.setWindowTitle("Success");
      repaint();
    }
    else{
         msgBox.setWindowTitle("ERROR");
        msgBox.setText("Please enter last position point.");
    }
    msgBox.exec();
}



void GLWidget::ShowWalls() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);

	for(size_t x = 0; x < MATRIX_SIZE; ++x) 
	{
		for(size_t y = 1; y <= MATRIX_SIZE; ++y) 
		{
			if(mCalcDistance.mWallsMatrix[x][MATRIX_SIZE - y]) 
			{
				PaintCube(x, MATRIX_SIZE - y);
			}
		}
	}
}

void GLWidget::ShowPath( size_t x,size_t y)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    qglColor(Qt::green);

	PaintQuad(x, y);
	while(x != 0 || y != 0) 
	{
		auto curElement = mCalcDistance.mParentsMatrix[x][y];
		x = curElement.first, y = curElement.second;
		PaintQuad(x, y);
	}
}


void GLWidget::PaintQuad(size_t x, size_t y) const
{
	glBegin(GL_QUADS);
        glVertex2f(x*2.0f / MATRIX_SIZE, (y+1)*2.0f / MATRIX_SIZE);			// left-top
        glVertex2f((x+1)*2.0f / MATRIX_SIZE, (y+1)*2.0f / MATRIX_SIZE);	// right-top
        glVertex2f((x+1)*2.0f / MATRIX_SIZE, y*2.0f / MATRIX_SIZE);			// right-bottom
        glVertex2f(x*2.0f / MATRIX_SIZE, y*2.0f / MATRIX_SIZE);					// left-bottom
	glEnd();
}


void GLWidget::PaintCube(size_t x, size_t y) const
{
	float x_low = x*2.0f / MATRIX_SIZE;
	float x_high = (x+1)*2.0f / MATRIX_SIZE;

	float y_low = y*2.0f / MATRIX_SIZE;
	float y_high = (y+1)*2.0f / MATRIX_SIZE;

	float z_low = 0.0f;
	float z_high = -1.0f/ MATRIX_SIZE;

	glBegin(GL_QUADS);

    glColor3f(0.0f,1.0f,1.0f);		// white
        glVertex3f(x_high, y_low, z_low);
        glVertex3f(x_low, y_low, z_low);
        glVertex3f(x_low, y_high, z_low);
        glVertex3f(x_high, y_high, z_low);

    glColor3f(0.0f,0.0f,0.0f);      // Blue
		glVertex3f(x_low, y_high, z_high);       
		glVertex3f(x_low, y_high, z_low);        
		glVertex3f(x_low, y_low, z_low);         
		glVertex3f(x_low, y_low, z_high);        

	glColor3f(1.0f,0.5f,0.0f);    // Orange
		glVertex3f(x_high, y_low, z_high);       
		glVertex3f(x_low, y_low, z_high);        
		glVertex3f(x_low, y_low, z_low);         
		glVertex3f(x_high, y_low, z_low);        
		

	glColor3f(1.0f,0.0f,0.0f);  // Red
		glVertex3f(x_high, y_high, z_high);      
		glVertex3f(x_low, y_high, z_high);       
		glVertex3f(x_low, y_low, z_high);        
		glVertex3f(x_high, y_low, z_high);       


	glColor3f(1.0f,0.0f,1.0f);  // Purple
		glVertex3f(x_high, y_high, z_low);       
		glVertex3f(x_high, y_high, z_high);      
		glVertex3f(x_high, y_low, z_high);       
		glVertex3f(x_high, y_low, z_low);        

	glEnd();                         

}


void GLWidget::initializeGL() 
{
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_NORMALIZE);
    //glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	glOrtho(-1.2f, 1.2f, -1.2f, 1.2f, -1.2f, 1.2f);

    glTranslatef(-1.0f, -1.0f, 0.0f);
    qglClearColor(Qt::gray);

    glRotated(45, 1, 1, 0);
}


void GLWidget::paintGL() {

	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1, 0, 0);	//Red

	// Show grid
	glBegin(GL_QUAD_STRIP);
        for(size_t i = 0; i <= MATRIX_SIZE; i++)
		{
            glVertex2f(i*2.0f / MATRIX_SIZE, 0.0f);
            glVertex2f(i*2.0f / MATRIX_SIZE, 2.0f);
		}
	glEnd();

	glBegin(GL_QUAD_STRIP);
        for(size_t i = 0; i <= MATRIX_SIZE; i++)
		{
			glVertex2f(0.0f, i*2.0f / MATRIX_SIZE);
			glVertex2f(2.0f, i*2.0f / MATRIX_SIZE);
		}
	glEnd();
    ShowPath(xp,yp);
    ShowWalls();
}

void GLWidget::setPos(){
    if(xp>MATRIX_SIZE-1 || yp>MATRIX_SIZE-1){
        xp=0;
        yp=0;
        QMessageBox messagebox;
        messagebox.setText("Point size exceeded");
        messagebox.exec();
        return;

    }
   paintGL();
   repaint();
}
void GLWidget::resizeGL(int w, int h) 
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, static_cast<GLint>(w), static_cast<GLint>(h));

}
void GLWidget::setPoints(size_t x, size_t y){

    xp=x;
    yp=y;
}
