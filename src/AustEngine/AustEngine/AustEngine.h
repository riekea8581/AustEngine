#ifndef AUSTENGINE_H
#define AUSTENGINE_H

#include "AzulCore.h"

class AustEngine: public Engine
{
	friend class EngineAttorney;
private:
	static AustEngine* ptrInstance;

	AustEngine() {};
	AustEngine(const AustEngine&) = delete;
	AustEngine& operator=(const AustEngine&) = delete;
	~AustEngine() {};

	static AustEngine& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new AustEngine;
		return *ptrInstance;
	}

	// Methods Users need to overload
    virtual void Initialize();
    virtual void LoadContent();
	virtual void Update();
    virtual void Draw();
    virtual void UnLoadContent();

	//User-Defined; Specific to Each Game
	/// \brief User-defined method that determines what assets are to be loaded into the game.
	/// 
	/// \ingroup ENGINEEVENTS
	/// 
	/// The LoadResources() function is called when the engine is started and should be defined by the user to
	/// load all relevant resources. This involves calling the Load() functions of the Model, Shader, Texture,
	/// Image, SpriteFont, TerrainObject, and ParticleEffect managers. At the end, SubmitChangeScene() should be
	/// called with the starting scene.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts a LoadResources() function loading a model, shader, and texture, then setting
	/// "BaseScene" as the start scene.
	/// 
	/// \code
	/// 
	/// void AustEngine::LoadResources()
	/// {
	/// 	ModelManager::Load("Model", "Model.azul");
	/// 	ShaderManager::Load("textureFlatRender", "textureFlatRender");
	/// 	TextureManager::Load("BrickTex", "BrickTexture.tga");
	/// 	SceneManager::SubmitChangeScene(new StartScene());
	/// }
	///
	/// \endcode
	virtual void LoadResources();
	/// \brief User-defined method that determines what special tasks to do on game start.
	/// 
	/// \ingroup ENGINEEVENTS
	/// 
	/// Sometimes the user will want to execute specific commands as soon as the game starts that the engine itself
	/// does not cover. For this reason the user-defined AustInitialize function is included. This function can
	/// include any calls the user desires, or it also can be left empty.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an AustInitialize() function that sets the window name & size, common usages
	/// of the AustInitialize function.
	/// 
	/// \code
	/// 
	/// void AustEngine::AustInitialize()
	/// {
	///		this->setWindowName("Hello World");
	///		this->setWidthHeight(800, 600);
	/// }
	///
	/// \endcode
	virtual void AustInitialize();
	/// \brief User-defined method that determines what special tasks to do on game end.
	/// 
	/// \ingroup ENGINEEVENTS
	/// 
	/// Sometimes the user will want to execute specific commands once the game ends that the engine itself
	/// does not cover. For this reason the user-defined AustEnd function is included. This function can
	/// include any calls the user desires, or it also can be left empty.
	/// 
	/// \par Example:
	/// 
	/// The following example depicts an AustEnd() function that terminates a factory that the scenes do not.
	/// 
	/// \code
	/// 
	/// void AustEngine::AustEnd()
	/// {
	///		ObjectFactory::Terminate();
	/// }
	///
	/// \endcode
	virtual void AustEnd();

public:
	static void RunAustEngine()
	{
		Instance().run();
		delete ptrInstance;
		ptrInstance = nullptr;
	};
	static int GetWindowWidth() { return Instance().getWidth(); };
	static int GetWindowHeight() { return Instance().getHeight(); };
	static void EngineSetClearColor(float r, float g, float b, float a)
		{ Instance().SetClearColor(r, g, b, a); };
	static void SetWindowWH(int w, int h) { Instance().setWidthHeight(w, h); };
	static void SetWindowName(const char *name) { Instance().setWindowName(name); };
};

#endif