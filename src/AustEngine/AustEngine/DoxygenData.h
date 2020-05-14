#pragma once
/// \defgroup ENGINEEVENTS Engine Functions
/// \brief These are top-level functions directly called by the engine itself, but that
/// are overloaded by the user.

/// \defgroup SCENEEVENTS Scene Functions
/// \brief These are functions related to the Scene class, from which all in-game scenes
/// should be derived.

/// \defgroup GAMEOBJECTEVENTS Game Object Functions
/// \brief These are functions related to the Game Object class, from which all game
/// entities which need to be updated, drawn, etc. should be derived.

/// \defgroup UPDATEEVENTS Updatable Functions
/// \ingroup GAMEOBJECTEVENTS
/// \brief These are functions related to the Updatable class, a parent class of the
/// Game Object class that specifically relates to the game object's frame-by-frame
/// function calls.

/// \defgroup DRAWEVENTS Drawable Functions
/// \ingroup GAMEOBJECTEVENTS
/// \brief These are functions related to the Drawable class, a parent class of the
/// Game Object class that specifically relates to rendering the game object on-screen.

/// \defgroup ALARMEVENTS Alarmable Functions
/// \ingroup GAMEOBJECTEVENTS
/// \brief These are functions related to the Alarmable class, a parent class of the
/// Game Object class that gives access to functions to set alarms and to execute specific
/// commands once said alarms are triggered.

/// \defgroup INPUTEVENTS Inputable Functions
/// \ingroup GAMEOBJECTEVENTS
/// \brief These are functions related to the Inputable class, a parent class of the
/// Game Object class that gives access to functions to track key press/release and to
/// execute specific commands once a tracked key press/release occurs.

/// \defgroup STOREEVENTS Storable Functions
/// \ingroup GAMEOBJECTEVENTS
/// \brief These are functions related to the game object store & recreate system. This
/// is a system available to users that allows a certain amount of data from up to 32 objects
/// flagged as "storable" to be kept and used later to recreate the objects. This way, important
/// objects in a scene can be stored, then used to recreate the scene later. Note that the
/// Storable class is a separate superclass from the GameObject class, and must also be
/// inherited from to be used.

/// \defgroup COLLISIONEVENTS Collision Functions
/// \brief These are functions related to in-game collision. Many of these are within
/// the Collidable class, a parent class of the Game Object class that specifically relates
/// to game object collision, but some of these functions are called from within the Scene
/// class to allow collision to begin with.

/// \defgroup SYSTEMEVENTS In-Engine Systems
/// \brief These are functions related to in-engine systems that can be used from within
/// scene or game object code. This includes a simple UI system, sprites, a sprite string
/// mechanism for displaying strings from a TGA file, and a Particle system.

/// \defgroup UIEVENTS UI Functions
/// \ingroup SYSTEMEVENTS
/// \brief These are functions related to the (very simple) UI system provided by the
/// engine. Certain interface elements like health bars are able to be drawn directly
/// by the engine given the proper input.

/// \defgroup PARTICLESYSTEM Particle System
/// \ingroup SYSTEMEVENTS
/// \brief These are functions related to the (very simple) UI system provided by the
/// engine. Certain interface elements like health bars are able to be drawn directly
/// by the engine given the proper input.

/// \defgroup SPRITEEVENTS Sprite Functions
/// \ingroup SYSTEMEVENTS
/// \brief These are functions related to the (very simple) UI system provided by the
/// engine. Certain interface elements like health bars are able to be drawn directly
/// by the engine given the proper input.

/// \defgroup SPRITESTRING Sprite String System
/// \ingroup SYSTEMEVENTS
/// \brief These are functions related to the (very simple) UI system provided by the
/// engine. Certain interface elements like health bars are able to be drawn directly
/// by the engine given the proper input.

/*! \mainpage About AustEngine
AustEngine is a simple C++ engine designed for the production of basic 3D Games.
AustEngine is built using AZUL as a framework.
\section features Features
AustEngine provides these game-making tools:
	- A resource manager to load shaders, models, and textures and to use them in-game
	- Base classes Scene & GameObject, used to create specific derived level & entity classes
	- Various modules for an Update/Draw function, alarms, keyboard input, and collision;
	these are parents of the GameObject class but can also be implemented separately
	- God Camera & Collision Visualizer tools for debugging
*/

/*! \page components AustEngine Components
Here is a list of AustEngine functions & classes available to the user.

	- \ref SCENEEVENTS "Scene Class Functions": Functions within the Scene & SceneManager classes
	- \ref GAMEOBJECTEVENTS "GameObject Class Functions": Functions within the GameObject class & its parents
	- \ref COLLISIONEVENTS "Collision Functions": Functions within both the Scene & GameObject classes
	  related to the collision system
*/