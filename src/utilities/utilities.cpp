#include "utilities/utilities.h"

std::string format_time(GLdouble t){
    GLint h = floor(t/3600);
    GLint m = floor(t/60-h*60);
    GLint s = round(t-m*60-h*3600);
    return std::to_string(h)+"."+std::to_string(m)+"."+std::to_string(s);
}

vec3 add(vec3 a,vec3 b){
    return vec3{{a[0]+b[0],a[1]+b[1],a[2]+b[2]}};
}
vec3 sub(vec3 a,vec3 b){
    return vec3{{a[0]-b[0],a[1]-b[1],a[2]-b[2]}};
}
vec3 mul(var a,vec3 b){
    return vec3{{a*b[0],a*b[1],a*b[2]}};
}
vec3 mul(vec3 a, var b){
    return vec3{{b*a[0],b*a[1],b*a[2]}};
}
var dot(vec3 a,vec3 b){
    return (a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);
}
vec3 cross(vec3 a, vec3 b){
    return vec3{{a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]}};
}

var abs(std::array<var, 3> a){
    return static_cast<var >(sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]));
}

var dist(vec3 a,vec3 b){
    return abs(sub(a,b));
}

vec3 unit(vec3 a,vec3 b){
    std::array<var ,3> vec = sub(a,b);
    return mul(1.0/abs(vec),vec);
}

std::string to_string(vec3 a){
        return "{" + std::to_string(a[0]) + "," + std::to_string(a[1]) +
                "," + std::to_string(a[2])+"}";
}

std::string to_string(vec4 a){
    return "{" + std::to_string(a[0]) + "," + std::to_string(a[1]) +
            "," + std::to_string(a[2]) +  "," + std::to_string(a[3]) + "}";
}

var SCALE = 15.0;

var FPS = 10.0;

GLboolean INTERACTIVE = false;
GLboolean TESTING = false;

//converts from pixel values to opengl context location.
var openGLpos(GLint x, GLboolean isy, camera* c){
    if(isy) return (((1.0 - 2.0*x/c->height))/c->zoom)*SCALE+c->position[1];
    else return (((2.0*x/c->width-1.0))/c->zoom)*SCALE+c->position[0];
}

vec4 color_red = {1.0,0.0,0.0,1.0};
vec4 color_yellow = {1.0,1.0,0.0,1.0};
vec4 color_green = {0.0,1.0,0.0,1.0};
vec4 color_cyan = {0.0,1.0,1.0,1.0};
vec4 color_blue = {0.0,0.0,1.0,1.0};
vec4 color_magenta= {1.0,0.0,1.0,1.0};
vec4 color_black = {0.0,0.0,0.0,1.0};
vec4 color_white = {1.0,1.0,1.0,1.0};

std::array<vec4*,6> color_list = {&color_red,&color_green,&color_blue,
                                  &color_yellow,&color_cyan,&color_magenta};


void render_sphere(camera* c, vec3 x, var R){
    GLint subdivisions = 20;
    GLUquadricObj *quadric = gluNewQuadric();
    glColor4d(0.0,0.0,1.0,1.0);
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glPushMatrix();
    glTranslatef(c->zoom*(x[0]-c->position[0])/SCALE,
                 c->zoom*(x[1]-c->position[1])/SCALE,
                 c->zoom*(x[2]-c->position[2])/SCALE);
    gluSphere(quadric, R/(c->zoom*SCALE), subdivisions,subdivisions);
    //glRotatef(0.01,0.0,0.0,1.0);
    glPopMatrix();
    gluDeleteQuadric(quadric);
}

void render_grid(camera* c){
    glLineWidth(1.0);
    glColor4f(0.0, 0.0, 0.0,1.0);
    glBegin(GL_LINES);
    glVertex3f(-1.0,-(c->position[1]/SCALE)*c->zoom, 0.0);
    glVertex3f(1.0, -(c->position[1]/SCALE)*c->zoom, 0);
    glEnd();

    glLineWidth(1.0);
    glColor4f(0.0, 0.0, 0.0,1.0);
    glBegin(GL_LINES);
    glVertex3f(-(c->position[0]/SCALE)*c->zoom,-1.0, 0.0);
    glVertex3f(-(c->position[0]/SCALE)*c->zoom, 1.0, 0);
    glEnd();
}
//

