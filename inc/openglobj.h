#ifndef OPENGLOBJ_H
#define OPENGLOBJ_H
#define GL_GLEXT_PROTOTYPES

#include<QGLWidget>
#include<QtOpenGL>
#include<QOpenGLBuffer>
#include<QOpenGLFunctions>
#include<QOpenGLShaderProgram>
#include<fstream>
#include<sstream>
#include<inc/bluetoothconnectionwindow.h>
#include<QTimer>
#include<QString>

class OpenGLobj : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLobj(QWidget* parent = nullptr);
    ~OpenGLobj();
    void setColor(QColor& col);
    void scale(int s);
    void change_sensitivity(int s);
signals:
    void xRotationChanged(double angle);
    void yRotationChanged(double angle);
    void zRotationChanged(double angle);

    
public slots:
    void setXRotation(double angle);
    void setYRotation(double angle);
    void setZRotation(double angle);
    void timeToDraw();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    
  //  virtual void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    void draw();
    void import();
    double xRot;
    double yRot;
    double zRot;
    std::vector<float*> vertices;
    std::vector<std::vector<float>> uvs;
    std::vector<float*> normals;
    GLfloat** vert;
    QPoint lastPos;
    QTimer* timer;
    float color[3];
    float len;
    float sen;
    
    
};

#endif // OPENGLOBJ_H
