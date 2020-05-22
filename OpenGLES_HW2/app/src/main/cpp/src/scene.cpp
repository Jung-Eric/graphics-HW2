#include "scene.h"
#include "binary/teapot.h"
#include "binary/floral.h"
#include "binary/cloud.h"
#include "binary/checker.h"

Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
Object* Scene::teapot = nullptr;
Texture* Scene::diffuse = nullptr;
Texture* Scene::dissolve = nullptr;
Material* Scene::material = nullptr;
LeftLight* Scene::lightL = nullptr;
RightLight* Scene::lightR = nullptr;

float dis_count = 0.0;

float imp = 0;

void Scene::setup(AAssetManager* aAssetManager) {
    Asset::setManager(aAssetManager);

    Scene::vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    Scene::fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    Scene::program = new Program(Scene::vertexShader, Scene::fragmentShader);

    Scene::camera = new Camera(Scene::program);
    Scene::camera->eye = vec3(20.0f, 20.0f, 20.0f);

    Scene::lightL = new LeftLight(program);
    Scene::lightR = new RightLight(program);
    lightL->position = vec3(-3.0f, 9.0f, 9.0f);
    lightR->position = vec3(9.0f, 9.0f, -3.0f);

    //change here.
    //Scene::diffuse = new Texture(Scene::program, 0, "textureDiff", floralTexels, floralSize);

    Scene::diffuse = new Texture(Scene::program, 0, "textureDiff", checkerTexels, checkerSize);

    //cloud texture
    Scene::dissolve = new Texture(Scene::program, 0, "textureDissolve", cloudTexels, cloudSize);

    Scene::material = new Material(Scene::program, diffuse, nullptr);
    Scene::teapot = new Object(program, material, teapotVertices, teapotIndices);
}

void Scene::screen(int width, int height) {
    Scene::camera->aspect = (float) width/height;
}

void Scene::update(float deltaTime) {

    Scene::program->use();

    //Scene::teapot->material->threshold = abs(sin(10*radians(dis_count)));
    /*
    if(dis_count<180) {
        dis_count ++;
        imp = sin(10 * radians(dis_count));
        Scene::teapot->material->threshold = abs(imp);
        Scene::teapot->material->displacement = Scene::teapot->material->threshold;
    }
    else{

    }
     */
    dis_count ++;
    imp = sin(10 * radians(dis_count));
    Scene::teapot->material->threshold = abs(imp);
    Scene::teapot->material->displacement = Scene::teapot->material->threshold;


    Scene::camera->update();
    Scene::lightL->update();
    Scene::lightR->update();

    Scene::teapot->draw();
}
