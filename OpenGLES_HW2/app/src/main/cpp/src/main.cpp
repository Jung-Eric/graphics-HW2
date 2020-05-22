#include "main.h"

void surfaceCreated(AAssetManager* aAssetManager) {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);


    // Add some functions to enable alpha blending`
    // alpha_dest = 1 - alpha_src. Please find opengl blending functions.

    GLenum Src = GL_SRC_ALPHA;
    GLenum Dest = GL_ONE_MINUS_SRC_ALPHA;
    //GLenum Dest = 1 - GL_SRC_ALPHA;
    glBlendFunc(Src,Dest);
    //glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_BLEND);
    Scene::setup(aAssetManager);
}

void surfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    Scene::screen(width, height);
}

void drawFrame(float deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::update(deltaTime);
}