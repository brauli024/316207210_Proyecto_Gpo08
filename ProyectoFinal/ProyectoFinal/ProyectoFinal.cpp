// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Properties
const GLuint WIDTH = 1000, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 SpotLightDir(0.0f, -1.0f, 0.0f);
glm::vec3 SpotLightPos(-13.8f, 5.0f, 3.0f);     //Spotlight posicionada en la sala


// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(-15.85f, 1.655f, 3.0f),   //Pointlight TV
    glm::vec3(17.25f, 10.2f, -3.8f)     //Pointlight l�mpara
};


//--------------------------------Variables para animaciones--------------------------------

glm::vec3 Light1 = glm::vec3(0);    //Apagar PointLight de TV
glm::vec3 enciende_TV = glm::vec3(0);   //Inicializa el escalamiento de la TV encendida en 0
glm::vec3 apaga_TV = glm::vec3(1);      //Inicializa el escalamiento de la TV apagada en 1
glm::vec3 alfa1 = glm::vec3(1);     //Canal alfa para los chicles de la cabeza de Benson
glm::vec3 alfa2 = glm::vec3(1);     //Canal alfa para la cabeza de Benson

//Variables para activar y desactivar animaciones
bool active1;   //Para activar y desactivar animaci�n simple 1 (encender y apagar TV)
bool active2;   //Para activar y desactivar animaci�n simple 2 (Benson enojado)
bool active3;   //Para activar y desactivar animaci�n simple 3 (Mordecai feliz)
bool active4;   //Para activar y desactivar animaci�n compleja 1 (brinco Rigby)
bool active5;   //Para activar y desactivar animaci�n compleja 2 (poner cartucho)

//Variables para automatizar animaciones
//Mover brazo izquierdo de Mordecai
bool anim1 = false;     //Mover hasta l�mite superior
bool anim2 = false;     //Mover hasta l�mite inferior
float rot1 = 0.0f;      //Rotaci�n del brazo izquierdo
//Mover brazo derecho de Mordecai
bool anim3 = false;     //Mover hasta l�mite superior
bool anim4 = false;     //Mover hasta l�mite inferior
float rot2 = 0.0f;      //Rotaci�n del brazo derecho
//Mover pierna izquierda de Mordecai
bool anim5 = false;     //Mover hasta l�mite superior
bool anim6 = false;     //Mover hasta l�mite inferior
float rot3 = 0.0f;      //Rotaci�n de la pierna izquierda
//Mover pico de Mordecai
float rot4 = 0.0f;      //Rotaci�n del pico
//Salto Rigby
bool anim7 = false;
//Poner cartucho
bool anim8 = false;
float rot5 = 0.0f;      //Rotaci�n del cartucho

//Iicializaci�n de variables con las posiciones veritcal y horizontal iniciales para animaciones de tiro parab�lico
//Rigby
float trasX_1 = -11.5f;     //Inicializar posici�n horizontal
float trasY_1 = 0.83f;      //Inicializar posici�n vertical
//Cartucho
float trasZ_1 = 2.5f;       //Inicializar posici�n horizontal
float trasY_2 = 0.660f;     //Inicializar posici�n vertical

//Velocidades horizontales y verticales para animaciones de tiro parab�lico
//Rigby
float V0_X1 = -1.0f;    //Velocidad horizontal
float V0_Y1 = 4.13f;    //Velocidad vertical
//Cartucho
float V0_Z1 = 1.217f;   //Velocidad horizontal
float V0_Y2 = 5.173f;   //Velocidad vertical

//Variables de tiempo para animaciones de tiro parab�lico
float tiempo = 0.0f;    //Rigby
float tiempo2 = 0.0f;   //Cartucho


int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    /*glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );*/
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
    Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
    

    // Load models

    //-------------------------Fachada-------------------------
    Model Fachada((char*)"Models/Fachada/Fachada.obj");
    //-------------------------Ventanas-------------------------
    Model Ventanas((char*)"Models/Fachada/Ventanas.obj");
    //-------------------------Cuarto de Mordecai y Rigby-------------------------
    Model Cama((char*)"Models/Cama/Cama.obj");
    Model Buro((char*)"Models/Buro/Buro.obj");
    Model Cajonera((char*)"Models/Cajonera/Cajonera.obj");
    Model Lampara((char*)"Models/Lampara/Lampara.obj");
    Model Trampolin((char*)"Models/Trampolin/Trampolin.obj");
    //-------------------------Sala-------------------------
    Model Control((char*)"Models/Control/Control.obj");
    Model Sofa((char*)"Models/Sofa/Sofa.obj");
    Model MesaConsola((char*)"Models/Mesa_Consola/Mesa.obj");
    Model Consola((char*)"Models/Consola/Consola.obj");
    Model Cartucho((char*)"Models/Cartucho/Cartucho.obj");
    Model MesaTV((char*)"Models/Mesa_TV/Mesa.obj");
    Model TV_encendida((char*)"Models/TV/TV_Encendida.obj");
    Model TV_apagada((char*)"Models/TV/TV_apagada.obj");
    //Mordecai
    Model MordecaiCuerpo((char*)"Models/Mordecai/Cuerpo.obj");
    Model MordecaiBrazoIzq((char*)"Models/Mordecai/Brazo_Izq.obj");
    Model MordecaiBrazoDer((char*)"Models/Mordecai/Brazo_Der.obj");
    Model MordecaiPiernaIzq((char*)"Models/Mordecai/Pierna_Izq.obj");
    Model MordecaiPicoAbajo((char*)"Models/Mordecai/Pico_Abajo.obj");
    //Rigby
    Model Rigby((char*)"Models/Rigby/Rigby.obj");
    //Benson
    Model BensonCuerpo((char*)"Models/Benson/Benson_Cuerpo.obj");
    Model BensonCabeza((char*)"Models/Benson/Benson_Cabeza.obj");
    Model BensonChicles((char*)"Models/Benson/Benson_Chicles.obj");

    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] =
    {
        // Positions            // Normals              // Texture Coords
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
    };


    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };


    GLuint indices[] =
    {  // Note that we start from 0!
        0,1,2,3,
        4,5,6,7,
        8,9,10,11,
        12,13,14,15,
        16,17,18,19,
        20,21,22,23,
        24,25,26,27,
        28,29,30,31,
        32,33,34,35
    };

    // Positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Texture Coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    //SkyBox
    GLuint skyboxVBO, skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);


    // Set texture units
    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);


    // Load textures 

    vector<const GLchar*> faces;
    faces.push_back("SkyBox/Fondo.tga");
    faces.push_back("SkyBox/Fondo.tga");
    faces.push_back("SkyBox/Fondo.tga");
    faces.push_back("SkyBox/Fondo.tga");
    faces.push_back("SkyBox/Fondo.tga");
    faces.push_back("SkyBox/Fondo.tga");

    GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // OpenGL options
        glEnable(GL_DEPTH_TEST);


        //------------------------------------------------LIGHTING SHADER------------------------------------------------


        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use();
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), 0.0f, -1.0f, -1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


        // Point light TV
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), Light1.x, Light1.y, Light1.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), Light1.x, Light1.y, Light1.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.1f, 0.1f, 0.1f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 1.8f);

        // Point light L�mpara
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.3f, 0.3f, 0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.3f, 0.3f, 0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.1f, 0.1f, 0.1f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0075f);

        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), SpotLightPos.x, SpotLightPos.y, SpotLightPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), SpotLightDir.x, SpotLightDir.y, SpotLightDir.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.35f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.44f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(25.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(34.0f)));

        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        // Create camera transformations
        glm::mat4 view = camera.GetViewMatrix();

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        glm::mat4 model(1);


        //--------------------------Fachada--------------------------
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(1.2f, 1.0f, 1.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Fachada.Draw(lightingShader);

        //--------------------------Cuarto de Mordecai y Rigby--------------------------
        //Cama
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.0f, 8.255f, -6.8f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Cama.Draw(lightingShader);
        
        //Bur�
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(17.15f, 8.255f, -4.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Buro.Draw(lightingShader);
 
        //L�mpara
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(17.25f, 9.505f, -3.8f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Lampara.Draw(lightingShader);
        
        //Cajonera azul
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(12.5f, 8.255f, 1.9f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Cajonera.Draw(lightingShader);
        
        //Trampol�n
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(14.0f, 8.255f, -1.1f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Trampolin.Draw(lightingShader);


        //--------------------------Sala--------------------------
        //Sofa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-11.5f, 0.055f, 3.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Sofa.Draw(lightingShader);

        //Mesa Consola
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-13.8f, 0.055f, 3.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MesaConsola.Draw(lightingShader);

        //Consola
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-14.0f, 0.707f, 3.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Consola.Draw(lightingShader);

        //Cartucho
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-14.047, trasY_2, trasZ_1));  //Traslaci�n con animaci�n de tiro parab�lico.
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rot5), glm::vec3(1.0f, 0.0f, 0.0f));    //Rotaci�n para animaci�n de cartucho.
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Cartucho.Draw(lightingShader);

        //Controles
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-13.3f, 0.715f, 3.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Control.Draw(lightingShader);
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-13.3f, 0.715f, 4.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Control.Draw(lightingShader);

        //Mesa TV
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-16.5f, 0.055f, 3.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MesaTV.Draw(lightingShader);

        //TV Apagada
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-16.3f, 0.885f, 3.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(apaga_TV.x, apaga_TV.y, apaga_TV.z));   //Esacalamiento para animaci�n de TV.
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        TV_apagada.Draw(lightingShader);

        //TV Encendida
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-16.3f, 0.885f, 3.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(enciende_TV.x, enciende_TV.y, enciende_TV.z));  //Esacalamiento para animaci�n de TV.
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        TV_encendida.Draw(lightingShader);

        //Benson
        //Cuerpo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, 0.055f, -3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        BensonCuerpo.Draw(lightingShader);

        //Mordecai
        //Cuerpo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, 0.055f, 3.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiCuerpo.Draw(lightingShader);
        //BrazoIzq
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.018f, 2.151f, 3.104f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot1), glm::vec3(1.0f, 0.0f, 0.0f));   //Rotaci�n para animaci�n de brazo de Mordecai
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiBrazoIzq.Draw(lightingShader);
        //BrazoDer
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.016f, 2.154f, 2.898f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot2), glm::vec3(1.0f, 0.0f, 0.0f));   //Rotaci�n para animaci�n de brazo de Mordecai
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiBrazoDer.Draw(lightingShader);
        //PiernaIzq
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, 1.204f, 3.086f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot3), glm::vec3(1.0f, 0.0f, 0.0f));   //Rotaci�n para animaci�n de pierna de Mordecai
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiPiernaIzq.Draw(lightingShader);
        //Pico
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.254f, 2.477f, 2.995f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot4), glm::vec3(1.0f, 0.0f, 0.0f));   //Rotaci�n para animaci�n de pico de Mordecai
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiPicoAbajo.Draw(lightingShader);

        //Rigby
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(trasX_1, trasY_1, 4.25f));      //Traslaci�n para animaci�n de tiro parab�lico
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Rigby.Draw(lightingShader);



        //Trabajando canal alfa
        glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //Chicles Benson
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, 0.055f, -3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        //Par�metros de color alfa de chicles para animaci�n de Benson:
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), alfa1.x, alfa1.y, alfa1.z, 1.0);    
        BensonChicles.Draw(lightingShader);

        //Cabeza Benson
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, 0.055f, -3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        //Par�metros de color alfa de la cabeza para animaci�n de Benson:
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), alfa2.x, alfa2.y, alfa2.z, 0.5);
        BensonCabeza.Draw(lightingShader);

        //Ventanas
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(1.2f, 1.0f, 1.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1, 1, 1, 0.8);
        Ventanas.Draw(lightingShader);

        glDisable(GL_BLEND);   //Desactiva el canal alfa 
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
        
        glBindVertexArray(0);


        //------------------------------------------------LAMP SHADER------------------------------------------------


        /*// Also draw the lamp object, again binding the appropriate shader
        lampShader.Use();
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");

        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        model = glm::mat4(1);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Draw the light object (using light's vertex attributes)
        for (GLuint i = 0; i < 2; i++)
        {
            model = glm::mat4(1);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        model = glm::mat4(1);
        model = glm::translate(model, SpotLightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);*/


        //------------------------------------------------MODEL SHADER------------------------------------------------


        //shader.Use();

        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model


        //glBindVertexArray(0);


        //------------------------------------------------SKYBOX SHADER------------------------------------------------

        // Draw skybox as last
        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
        SkyBoxshader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // Set depth function back to default

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

    //------------------Mover Mordecai------------------

    //BrazoIzq
    if (anim1)
    {
        if (rot1 < 150)     //Mover brazo hasta llegar al l�mite superior
        {
            rot1 += 0.5f;
        }
        else                //Al llegar al l�mite se debe mover el brazo en sentido contrario
        {
            anim2 = true;
            anim1 = false;
        }
    }

    if (anim2)
    {
        if (rot1 > 135)     //Mover brazo hasta llegar al l�mite inferior
        {
            rot1 -= 0.5f;
        }
        else                //Al llegar al l�mite se debe mover el brazo en sentido contrario
        {
            anim2 = false;
            anim1 = true;
        }
    }

    //BrazoDer
    if (anim3)
    {
        if (rot2 < 120)     //Mover brazo hasta llegar al l�mite superior
        {
            rot2 += 0.5f;
        }
        else                //Al llegar al l�mite se debe mover el brazo en sentido contrario
        {
            anim4 = true;
            anim3 = false;
        }
    }

    if (anim4)
    {
        if (rot2 > 105)     //Mover brazo hasta llegar al l�mite inferior
        {
            rot2 -= 0.5f;
        }
        else                //Al llegar al l�mite se debe mover el brazo en sentido contrario
        {
            anim4 = false;
            anim3 = true;
        }
    }

    //PiernaIzq
    if (anim5)
    {
        if (rot3 < 30)      //Mover pierna hasta llegar al l�mite superior
        {
            rot3 += 0.5f;
        }
        else                //Al llegar al l�mite se debe mover la pierna en sentido contrario
        {
            anim6 = true;
            anim5 = false;
        }
    }

    if (anim6)
    {
        if (rot3 > 15)      //Mover pierna hasta llegar al l�mite inferior
        {
            rot3 -= 0.5f;
        }
        else                //Al llegar al l�mite se debe mover la pierna en sentido contrario
        {
            anim6 = false;
            anim5 = true;
        }
    }

    //------------------Brinco Rigby------------------

    if (anim7)
    {
        if (tiempo < 1.0f)      //Se realiza la animaci�n hasta un tiempo de 1 segundo (aprox)
        {
            tiempo += 0.05f;
            //Ecuaci�n de movimiento horizontal:
            trasX_1 = -11.5f + (V0_X1 * tiempo);
            //Ecuaci�n de movimiento vertical:  
            trasY_1 = 0.83f + (V0_Y1 * tiempo) - ((1.0f / 2.0f) * 9.81f * pow(tiempo, 2));      
        }
        else                    //Se detiene la animaci�n
        {
            anim7 = false;
        }
    }

    //------------------Poner cartucho------------------

    if (anim8)
    {
        if (tiempo2 < 1.0f)     //Se realiza la animaci�n hasta un tiempo de 1 segundo (aprox)
        {

            if (rot5 < 90)      //Se realiza el giro de 90� del cartucho
            {
                rot5 += 1.0f;
            }
            tiempo2 += 0.01f;
            //Ecuaci�n de movimiento horizontal:
            trasZ_1 = 2.5f + (V0_Z1 * tiempo2);
            //Ecuaci�n de movimiento vertical:
            trasY_2 = 0.660f + (V0_Y2 * tiempo2) - ((1.0f / 2.0f) * 9.81f * pow(tiempo2, 2));
        }
        else                    //Se detiene la animaci�n
        {
            anim8 = false;
        }
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    //------------------Encender y apagar TV------------------

    if (keys[GLFW_KEY_P])
    {
        active1 = !active1;
        if (active1)    //Se enciende la TV
        {
            enciende_TV = glm::vec3(1);     //Escala el modelo de la TV encendida en 1
            apaga_TV = glm::vec3(0);        //Escala el modelo de la TV apagada en 0
            Light1 = glm::vec3(1);          //Activa la pointlight de la TV cuando se enciende
        }
        else            //Se apaga la TV
        {
            enciende_TV = glm::vec3(0);     //Escala el modelo de la TV encendida en 0
            apaga_TV = glm::vec3(1);        //Escala el modelo de la TV apagada en 1
            Light1 = glm::vec3(0);          //Desactiva la pointlight de la TV cuando se apaga
        }
    }

    //------------------Benson enojado------------------

    if (keys[GLFW_KEY_M])
    {
        active2 = !active2;
        if (active2)    //Se cambia el color de los modelos
        {
            alfa1 = glm::vec3(1.0f, 0.0f, 0.0f);        //Se cambia el color de los chicles de Benson a rojo
            alfa2 = glm::vec3(1.0f, 0.0f, 0.0f);        //Se cambia el color de la cabeza de Benson a rojo
        }
        else            //Se regresa el color original de los modelos
        {
            alfa1 = glm::vec3(1);                   //Se regresa el color de los chicles de Benson al original
            alfa2 = glm::vec3(1);                   //Se regresa el color de la cabeza de Benson al original
        }
    }

    //------------------Mover Mordecai------------------

    if (keys[GLFW_KEY_O])
    {
        rot1 = 135;     //Inicializa la posici�n del brazo izquierdo
        rot2 = 120;     //Inicializa la posici�n del brazo derecho
        rot3 = 15;      //Inicializa la posici�n de la pierna izquierda
        rot4 = -20;     //Cambia la posici�n del pico para que se vea abierto
        active3 = !active3;
        if (active3)    //Se inicia el movimiento de las partes del cuerpo
        {
            anim1 = true;   //Se activa el movimiento con el l�mite superior del brazo izquierdo
            anim2 = false;  //Se desactiva el movimiento con el l�mite inferior del brazo izquierdo
            anim3 = true;   //Se activa el movimiento con el l�mite superior del brazo derecho
            anim4 = false;  //Se desactiva el movimiento con el l�mite inferior del brazo derecho
            anim5 = true;   //Se activa el movimiento con el l�mite superior de la pierna izquierda
            anim6 = false;  //Se desactiva el movimiento con el l�mite inferior de la pierna izquierda
        }
        else            //Se detiene el movimiento de las partes del cuerpo
        {
            //Se desactivan todos los movimientos
            anim1 = false;
            anim2 = false;
            anim3 = false;
            anim4 = false;
            anim5 = false;
            anim6 = false;
            //Se regresa a la posici�n inicial todas las partes del cuerpo
            rot1 = 0;
            rot2 = 0;
            rot3 = 0;
            rot4 = 0;
        }
    }

    //------------------Brinco Rigby------------------

    if (keys[GLFW_KEY_SPACE])
    {
        active4 = !active4;
        if (active4)
        {
            anim7 = true;       //Se activa el movimiento
        }
        else
        {
            anim7 = false;      //Se desaciva el movimiento
            //Se reinicializan las variables pertinentes al tiro parab�lico para poner a Rigby en su posci�n inicial
            trasX_1 = -11.5f;
            trasY_1 = 0.83f;
            tiempo = 0.0f;
        }
    }

    //------------------Poner cartucho------------------

    if (keys[GLFW_KEY_N])
    {
        active5 = !active5;
        if (active5)
        {
            anim8 = true;       //Se activa el movimiento
        }
        else
        {
            anim8 = false;      //Se desaciva el movimiento
            //Se reinicializan las variables necesarias para poner al cartucho en su posci�n inicial nuevamente
            trasZ_1 = 2.5f;
            trasY_2 = 0.660f;
            tiempo2 = 0.0f;
            rot5 = 0.0f;
        }
    }

}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}