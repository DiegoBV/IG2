#include "AppObj.h"

#pragma once
class Toy: public AppObj
{
private:
	const Ogre::Real vel = 100;                      //velocidad de toy

	Ogre::SceneNode* head;                          //nodo de la cabeza

	Ogre::SceneNode* body;                          //nodo del cuerpo

	Entity* bodyEnt = nullptr;                     //entidad del cuerpo, la guardamos para comprobar colisiones
	
	Sphere bmb;                                   //coordenadas de la bomba (igual lo cambiamos y lo sacamos fuera)

	bool on = false;                             //booleano que indica si se esta moviendo costantemente

//------------------------------------------------------------MOVIMIENTO Y COLISION-----------------------------------------------

	void movement(Ogre::Real time);              //Traslacion de toy

	void rotateDirection();                     //cambio de direccion

	void rotateBody_Head();                    //rotacion del cuerpo y la cabeza

	bool check_collision();                   //comprueba las colisiones entre body y la bomba

public:
	Toy() {};

	virtual ~Toy() {};

	Toy(Ogre::SceneNode* node);

	virtual void frameRendered(const Ogre::FrameEvent & evt);        //"update" de toy

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);   //metodo heredado de la clase "InputListener"

	InputListener* getTrueSelf() { return this; };                  //get this
	 
	virtual void receiveEvent(Eventos evnt, AppObj* sender);       //respuesta a los eventos

	void setBomb(const Sphere nBomb) { bmb = nBomb; };            //set de la bomba
};

// roll -> rota eje z
// pitch -> rota eje x
// yaw -> rota eje y

