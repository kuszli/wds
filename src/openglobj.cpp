#include<QtWidgets>
#include<QtOpenGL>
#include "inc/openglobj.h"


OpenGLobj::OpenGLobj(QWidget* parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    xRot=0;
    yRot=0;
    zRot=0;
    color[0]=1.0;
    color[1]=0.0;
    color[2]=0.0;
    len = 6.0;
    sen = 5;
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    import();
}

OpenGLobj::~OpenGLobj(){}



QSize OpenGLobj::minimumSizeHint() const
{
    return QSize(200,200);
}

QSize OpenGLobj::sizeHint() const
{
    return QSize(400,400);
}

static void qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 2*M_PI*16;
    while (angle > 2*M_PI*16)
        angle -= 2*M_PI*16;
}

void OpenGLobj::setXRotation(double angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void OpenGLobj::setYRotation(double angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void OpenGLobj::setZRotation(double angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void OpenGLobj::initializeGL()
{

    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable ( GL_COLOR_MATERIAL );
    static GLfloat lightPosition[4] = { 0, 0, 0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    timer = new QTimer;
    timer->setInterval(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeToDraw()));
    timer->start(0);
}

void OpenGLobj::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, -1.0, -10.0);
    glScalef(0.3, 0.3, 1.0);

    glRotatef(qRadiansToDegrees(xRot), 1.0, 0.0, 0.0);
    glRotatef(qRadiansToDegrees(yRot), 0.0, 1.0, 0.0);
    glRotatef(qRadiansToDegrees(zRot), 0.0, 0.0, 1.0);

    /*
    glRotatef(xRot/16, 1.0, 0.0, 0.0);
    glRotatef(yRot/16, 0.0, 1.0, 0.0);
    glRotatef(zRot/16, 0.0, 0.0, 1.0);
*/
    draw();
}

void OpenGLobj::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLobj::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void OpenGLobj::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}



void OpenGLobj::draw()
{

glColor3f(0.7,0.7,0.5);
   glBegin(GL_QUADS);
       // top
       glNormal3f(0.0f, 1.0f, 0.0f);
       glVertex3f(-0.5f, 1.0f, 0.5f);
       glVertex3f(0.5f, 1.0f, 0.5f);
       glVertex3f(0.5f, 1.0f, -0.5f);
       glVertex3f(-0.5f, 1.0f, -0.5f);

       glEnd();

       glBegin(GL_QUADS);
       // front
       glNormal3f(0.0f, 0.0f, 1.0f);
       glVertex3f(0.5f, -1.0f, 0.5f);
       glVertex3f(0.5f, 1.0f, 0.5f);
       glVertex3f(-0.5f, 1.0f, 0.5f);
       glVertex3f(-0.5f, -1.0f, 0.5f);

       glEnd();

       glBegin(GL_QUADS);
       // right
       glNormal3f(1.0f, 0.0f, 0.0f);
       glVertex3f(0.5f, 1.0f, -0.5f);
       glVertex3f(0.5f, 1.0f, 0.5f);
       glVertex3f(0.5f, -1.0f, 0.5f);
       glVertex3f(0.5f, -1.0f, -0.5f);

       glEnd();

       glBegin(GL_QUADS);
       // left
       glNormal3f(-1.0f, 0.0f, 0.0f);
       glVertex3f(-0.5f, -1.0f, 0.5f);
       glVertex3f(-0.5f, 1.0f, 0.5f);
       glVertex3f(-0.5f, 1.0f, -0.5f);
       glVertex3f(-0.5f, -1.0f, -0.5f);

       glEnd();

       glBegin(GL_QUADS);
       // bottom
       glNormal3f(0.0f, -1.0f, 0.0f);
       glVertex3f(0.5f, -1.0f, 0.5f);
       glVertex3f(-0.5f, -1.0f, 0.5f);
       glVertex3f(-0.5f, -1.0f, -0.5f);
       glVertex3f(0.5f, -1.0f, -0.5f);

       glEnd();

       glBegin(GL_QUADS);
       // back
       glNormal3f(0.0f, 0.0f, -1.0f);
       glVertex3f(0.5f, 1.0f, -0.5f);
       glVertex3f(0.5f, -1.0f, -0.5f);
       glVertex3f(-0.5f, -1.0f, -0.5f);
       glVertex3f(-0.5f, 1.0f, -0.5f);

       glEnd();

      glColor3f(color[0], color[1], color[2]);

       glBegin(GL_QUADS);
           // top
           glNormal3f(0.0f, 1.0f, 0.0f);
           glVertex3f(-0.5f, len, 0.5f);
           glVertex3f(0.5f, len, 0.5f);
           glVertex3f(0.5f, len, -0.5f);
           glVertex3f(-0.5f, len, -0.5f);

           glEnd();

           glBegin(GL_QUADS);
           // front
           glNormal3f(0.0f, 0.0f, 1.0f);
           glVertex3f(0.5f, 1.0f, 0.5f);
           glVertex3f(0.5f, len, 0.5f);
           glVertex3f(-0.5f, len, 0.5f);
           glVertex3f(-0.5f, 1.0f, 0.5f);

           glEnd();


           glBegin(GL_QUADS);
           // right
           glNormal3f(1.0f, 0.0f, 0.0f);
           glVertex3f(0.5f, len, -0.5f);
           glVertex3f(0.5f, len, 0.5f);
           glVertex3f(0.5f, 1.0f, 0.5f);
           glVertex3f(0.5f, 1.0f, -0.5f);

           glEnd();

           glBegin(GL_QUADS);
           // left
           glNormal3f(-1.0f, 0.0f, 0.0f);
           glVertex3f(-0.5f, 1.0f, 0.5f);
           glVertex3f(-0.5f, len, 0.5f);
           glVertex3f(-0.5f, len, -0.5f);
           glVertex3f(-0.5f, 1.0f, -0.5f);

           glEnd();

           glBegin(GL_QUADS);
           // back
           glNormal3f(0.0f, 0.0f, -1.0f);
           glVertex3f(0.5f, len, -0.5f);
           glVertex3f(0.5f, 1.0f, -0.5f);
           glVertex3f(-0.5f, 1.0f, -0.5f);
           glVertex3f(-0.5f, len, -0.5f);

           glEnd();



}

void OpenGLobj::setColor(QColor& col){
    color[0] = col.redF();
    color[1] = col.greenF();
    color[2] = col.blueF();
    updateGL();

}


void OpenGLobj::scale(int s){
    len = (float) s/20.0;
    updateGL();
}

void OpenGLobj::change_sensitivity(int s){
   // sen = (float) 1.5-s/100.0;
   // updateGL();
}

void OpenGLobj::timeToDraw(){

    double x = BluetoothConnectionWindow::accX;
    double y = BluetoothConnectionWindow::accY;
    double z = BluetoothConnectionWindow::accZ;
   /* if(qFabs(y)>9.81){
        setXRotation(qAsin(y/qFabs(y)));
    }
    else{
        setXRotation(qAsin(y/9.81));
    }
    */
    if(qFabs(z)>9.81){
        setXRotation(qAsin(-z/qFabs(z)));
    }
    else{
        setXRotation(qAsin(-z/9.81));
    }

    if(qFabs(x)>9.81){
        setZRotation(qAsin(x/qFabs(x)));
    }
    else{
        setZRotation(qAsin(x/9.81));
    }

}


void OpenGLobj::import(){

    std::fstream file;
    std::string letter;
    std::vector<float> uv;
    float tmp;
    std::string line;
    file.open("/home/kuszli/kush/model/model.obj", std::ios::in);
    if(file.good()){
        qDebug() << "successfully opened file";
        while(std::getline(file, line)){
            if(line.at(0) == '#')
                continue;

            else if(line.at(0) == 'v' && line.at(1)!= 'n'){
                std::istringstream lineStream(line);
                lineStream >> letter;
                float* edge = new float[3];
                for(int i=0; i<3; ++i){
                    lineStream >> edge[i];
                    //edge.push_back(tmp);
                }
                vertices.push_back(edge);
            }
            else if(line.at(0) == 'v' && line.at(1) == 'n'){
                std::istringstream lineStream(line);
                lineStream >> letter;
                float* normal = new float[3];
                for(int i=0; i<3; ++i){
                   lineStream >> normal[i];
                }
                normals.push_back(normal);
            }
            else if(line.at(0) =='f'){
                std::istringstream lineStream(line);
                lineStream >> letter;
            }
            else{

            }

        }

    }
    else{
        qDebug() << "Error while opening file";
    }

    vert = new GLfloat*[vertices.size()];
    for(int i=0; i<vertices.size(); ++i){
        vert[i]= new GLfloat[3];
        for(int j=0; j<3; ++j){
            vert[i][j] = vertices.at(i)[j];
        }
    }
}
