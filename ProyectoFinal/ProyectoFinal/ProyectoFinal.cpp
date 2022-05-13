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
glm::vec3 SpotLightPos(-13.8f, 5.0f, 3.0f);


// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(-15.85f, 1.655f, 3.0f)
};


//Others
//glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light1 = glm::vec3(0);
glm::vec3 alfa1 = glm::vec3(1);
glm::vec3 alfa2 = glm::vec3(1);
glm::vec3 enciende_TV = glm::vec3(0);
glm::vec3 apaga_TV = glm::vec3(1);
float rot1 = 0.0f, rot2 = 0.0f, rot3 = 0.0f, rot4 = 0.0f, rot5 = 0.0f;
float trasX_1 = -11.5f, trasY_1 = 0.83f, trasZ_1 = 2.5f, trasY_2 = 0.660f;
bool active;
bool active2;
bool active3;
bool active4;
bool anim1 = false;
bool anim2 = false;
bool anim3 = false;
bool anim4 = false;
bool anim5 = false;
bool anim6 = false;
bool anim7 = false;
bool anim8 = false;
float V0_X1 = -1.0f;
float V0_Z1 = 1.217f;
float V0_Y1 = 4.13f;
float V0_Y2 = 5.173f;
float tiempo = 0.0f, tiempo2 = 0.0f;


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

    Model Fachada((char*)"Models/Fachada/Fachada.obj");
    Model Ventanas((char*)"Models/Fachada/Ventanas.obj");
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


        //Fachada
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(1.2f, 1.0f, 1.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        Fachada.Draw(lightingShader);

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
        model = glm::translate(model, glm::vec3(-14.047, trasY_2, trasZ_1));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rot5), glm::vec3(1.0f, 0.0f, 0.0f));
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
        model = glm::scale(model, glm::vec3(apaga_TV.x, apaga_TV.y, apaga_TV.z));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        TV_apagada.Draw(lightingShader);

        //TV Encendida
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-16.3f, 0.885f, 3.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(enciende_TV.x, enciende_TV.y, enciende_TV.z));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        TV_encendida.Draw(lightingShader);

        //Benson
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
        model = glm::rotate(model, glm::radians(-rot1), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiBrazoIzq.Draw(lightingShader);
        //BrazoDer
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.016f, 2.154f, 2.898f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot2), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiBrazoDer.Draw(lightingShader);
        //PiernaIzq
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, 1.204f, 3.086f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot3), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiPiernaIzq.Draw(lightingShader);
        //PicoAbajo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.254f, 2.477f, 2.995f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-rot4), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
        MordecaiPicoAbajo.Draw(lightingShader);

        //Rigby
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(trasX_1, trasY_1, 4.25f));
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
        glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), alfa1.x, alfa1.y, alfa1.z, 1.0);
        BensonChicles.Draw(lightingShader);

        //Cabeza Benson
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, 0.055f, -3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
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


        //// Also draw the lamp object, again binding the appropriate shader
        //lampShader.Use();
        //// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        //modelLoc = glGetUniformLocation(lampShader.Program, "model");
        //viewLoc = glGetUniformLocation(lampShader.Program, "view");
        //projLoc = glGetUniformLocation(lampShader.Program, "projection");

        //// Set matrices
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        //glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        //model = glm::mat4(1);
        //model = glm::translate(model, lightPos);
        //model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //// Draw the light object (using light's vertex attributes)
        //for (GLuint i = 0; i < 2; i++)
        //{
        //    model = glm::mat4(1);
        //    model = glm::translate(model, pointLightPositions[i]);
        //    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        //    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //    glBindVertexArray(VAO);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //}

        //model = glm::mat4(1);
        //model = glm::translate(model, SpotLightPos);
        //model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //glBindVertexArray(0);


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
        if (rot1 < 150)
        {
            rot1 += 0.5f;
        }
        else
        {
            anim2 = true;
            anim1 = false;
        }
    }

    if (anim2)
    {
        if (rot1 > 135)
        {
            rot1 -= 0.5f;
        }
        else
        {
            anim2 = false;
            anim1 = true;
        }
    }

    //BrazoDer
    if (anim3)
    {
        if (rot2 < 120)
        {
            rot2 += 0.5f;
        }
        else
        {
            anim4 = true;
            anim3 = false;
        }
    }

    if (anim4)
    {
        if (rot2 > 105)
        {
            rot2 -= 0.5f;
        }
        else
        {
            anim4 = false;
            anim3 = true;
        }
    }

    //PiernaIzq
    if (anim5)
    {
        if (rot3 < 30)
        {
            rot3 += 0.5f;
        }
        else
        {
            anim6 = true;
            anim5 = false;
        }
    }

    if (anim6)
    {
        if (rot3 > 15)
        {
            rot3 -= 0.5f;
        }
        else
        {
            anim6 = false;
            anim5 = true;
        }
    }

    //------------------Brinco Rigby------------------

    if (anim7)
    {
        if (tiempo < 1.0f)
        {
            tiempo += 0.05f;
            trasX_1 = -11.5f + (V0_X1 * tiempo);
            trasY_1 = 0.83f + (V0_Y1 * tiempo) - ((1.0f / 2.0f) * 9.81f * pow(tiempo, 2));
        }
        else
        {
            anim7 = false;
        }
    }

    //------------------Poner cartucho------------------

    if (anim8)
    {
        //model = glm::translate(model, glm::vec3(-14.047f, 0.928f, 3.717f));
        if (tiempo2 < 1.0f)
        {

            if (rot5 < 90)
            {
                rot5 += 1.0f;
            }
            tiempo2 += 0.01f;
            trasZ_1 = 2.5f + (V0_Z1 * tiempo2);
            trasY_2 = 0.660f + (V0_Y2 * tiempo2) - ((1.0f / 2.0f) * 9.81f * pow(tiempo2, 2));
        }
        else
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

    //------------------Mover Mordecai------------------

    if (keys[GLFW_KEY_O])
    {
        rot1 = 135;
        rot2 = 120;
        rot3 = 15;
        rot4 = -20;     //PicoAbajo
        active3 = !active3;
        if (active3)
        {
            anim1 = true;
            anim2 = false;
            anim3 = true;
            anim4 = false;
            anim5 = true;
            anim6 = false;
        }
        else
        {
            anim1 = false;
            anim2 = false;
            anim3 = false;
            anim4 = false;
            anim5 = false;
            anim6 = false;
            rot1 = 0;
            rot2 = 0;
            rot3 = 0;
            rot4 = 0;
        }
    }

    //------------------Encender y apagar TV------------------

    if (keys[GLFW_KEY_P])
    {
        active2 = !active2;
        if (active2)
        {
            enciende_TV = glm::vec3(1);
            apaga_TV = glm::vec3(0);
            Light1 = glm::vec3(1);
        }
        else
        {
            enciende_TV = glm::vec3(0);
            apaga_TV = glm::vec3(1);
            Light1 = glm::vec3(0);
        }
    }

    //------------------Benson enojado------------------

    if (keys[GLFW_KEY_M])
    {
        active = !active;
        if (active)
        {
            alfa1 = glm::vec3(1.0f, 0.0f, 0.0f);
            alfa2 = glm::vec3(1.0f, 0.0f, 0.0f);
        }
        else
        {
            alfa1 = glm::vec3(1);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
            alfa2 = glm::vec3(1);
        }
    }

    //------------------Brinco Rigby------------------

    if (keys[GLFW_KEY_SPACE])
    {
        active3 = !active3;
        if (active3)
        {
            anim7 = true;
        }
        else
        {
            anim7 = false;
            trasX_1 = -11.5f;
            trasY_1 = 0.83f;
            tiempo = 0.0f;
        }
    }

    //------------------Poner cartucho------------------

    if (keys[GLFW_KEY_N])
    {
        active4 = !active4;
        if (active4)
        {
            anim8 = true;
        }
        else
        {
            anim8 = false;
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