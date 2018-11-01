#include "Sinbad.h"



Sinbad::Sinbad()
{
}

Sinbad::~Sinbad()
{
}

Sinbad::Sinbad(Ogre::SceneNode * node): AppObj(node)
{
	sinbadNode = addChild("nSinbad", "Sinbad.mesh");           //anyade hijo al pNode, en este caso es el plano

	entity = pNode->getCreator()->getEntity("nSinbad");       //guardamos la entidad

	swordR = pNode->getCreator()->createEntity("swordR","Sword.mesh");  //creamos la entidad de las espadas

	entity->attachObjectToBone("Sheath.R", swordR);                     //hacemos attach a la entidad de sinbad

	swordL = pNode->getCreator()->createEntity("swordL", "Sword.mesh");

	entity->attachObjectToBone("Sheath.L", swordL);

	createWalk();                                                      //creamos la animacion de andar

	if (entity != nullptr) {
		follAnim_ = Run;                                   //empieza bailando asi que la siguiente animacion es correr (o suicidio si se pulsa la b)
		animState = entity->getAnimationState("Dance");    //accedemos a la anim de bailar
		animStateAux = entity->getAnimationState("RunTop"); //guardamos tambien el movimiento de los brazos
		animState->setEnabled(true);
		animState->setLoop(true);
	}
}

void Sinbad::frameRendered(const Ogre::FrameEvent & evt)
{
	if (follAnim_ == Run) {
		animState->addTime(evt.timeSinceLastFrame);      //si esta bailando, solo le damos el tiempo al estado de bailar
	}
	else if(follAnim_ == Suicide){
		
		suicideState->addTime(evt.timeSinceLastFrame);   //tiempo al estado de suicidio

		if (!suicideState->hasEnded()) {                //si la animacion de suicidio no ha terminado, la animacion de correr sigue activa
			animState->addTime(evt.timeSinceLastFrame);
			animStateAux->addTime(evt.timeSinceLastFrame);
		}
		else {                                        //si ha terminado, se crea la animacion de muerte y cambia las animaciones
			death();
			follAnim_ = Muerto;
			switchAnim();
		}

	}
	else if (follAnim_ == Muerto) {
		deathState->addTime(evt.timeSinceLastFrame);   //si esta muerto, le damos tiempo a dicho estado
	}
	else {
		animState->addTime(evt.timeSinceLastFrame);    //si esta corriendo, le damos el tiempo a la animacion de correr y la de moverse por el plano
		animStateAux->addTime(evt.timeSinceLastFrame);
		walkinState->addTime(evt.timeSinceLastFrame);

		//if(suicideState != nullptr)
			//suicideState->addTime(evt.timeSinceLastFrame);
	}
	
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_r:
		switchAnim();  //cambia la animacion entre correr y bailar
		break;
	case SDLK_b:
		if (follAnim_ != Suicide || follAnim_ != Muerto) {     //para evitar errores
			suicide();                                        //crea la animacion de suicidio
			follAnim_ = Suicide;
			switchAnim();
		}
		break;
	default:
		break;
	}
	return false;
}

void Sinbad::receiveEvent(Eventos evnt, AppObj * sender)
{
	switch (evnt)
	{
	case AppObj::colision:                 //si colisiona, empieza a suicidarse
		suicide();
		follAnim_ = Suicide;
		switchAnim();
		break;
	default:
		break;
	}
}

void Sinbad::switchAnim()
{
	switch (follAnim_)
	{
	case Sinbad::Dance:
		animState->setEnabled(false);                    //inhabilita todos
		animStateAux->setEnabled(false);
		walkinState->setEnabled(false);

		animState = entity->getAnimationState("Dance");         //cambia a la animacion "Dance"
		animState->setEnabled(true);
		animState->setLoop(true);

		entity->detachObjectFromBone(swordR);                //cambia las espadas de posicion
		entity->attachObjectToBone("Sheath.R", swordR);

		follAnim_ = Run;
		break;
	case Sinbad::Run:
		animStateAux->setEnabled(false);                    //inhabilita todos
		animState->setEnabled(false);

		animState = entity->getAnimationState("RunBase");   //cambia animstate a la animacion de correr (piernas)

		animState->setEnabled(true);                       //activa los estados necesarios
		animState->setLoop(true);
		animStateAux->setEnabled(true);
		animStateAux->setLoop(true);
		walkinState->setLoop(true);
		walkinState->setEnabled(true);

		entity->detachObjectFromBone(swordR);
		entity->attachObjectToBone("Handle.R", swordR);

		follAnim_ = Dance;
		break;
	case Sinbad::Suicide:
		animState->setEnabled(false);                            //inhabilita todos
		animStateAux->setEnabled(false);
		walkinState->setEnabled(false);

		animState = entity->getAnimationState("RunBase");      //cambia animstate a la animacion de correr (piernas)

		animState->setEnabled(true);                           //activa los estados necesarios
		animState->setLoop(true);
		animStateAux->setEnabled(true);
		animStateAux->setLoop(true);

		entity->detachObjectFromBone(swordR);                 //cambia las espadas de posicion
		entity->attachObjectToBone("Handle.R", swordR);

		entity->detachObjectFromBone(swordL);
		entity->attachObjectToBone("Handle.L", swordL);

		suicideState->setEnabled(true);                      //la animacion de suicidio esta ya creada, asi que la activa tambien
		suicideState->setLoop(false);
		break;
	case Sinbad::Muerto:
		animState->setEnabled(false);                       //inhabilita todos
		animStateAux->setEnabled(false);
		walkinState->setEnabled(false);
		suicideState->setEnabled(false);

		entity->detachObjectFromBone(swordR);              //cambia las espadas de posicion
		entity->attachObjectToBone("Sheath.R", swordR);

		entity->detachObjectFromBone(swordL);
		entity->attachObjectToBone("Sheath.L", swordL);

		deathState->setEnabled(true);                      //la animacion de muerto esta ya creada, asi que la activamos
		break;
	default:
		break;
	}
}

void Sinbad::createWalk()
{
	
	sinbadNode->setPosition(400, 100, -300);             //Colocamos a simbad
	sinbadNode->setScale(20, 20, 20);                   //Cambiamos la escala
	sinbadNode->setInitialState();                     //Guardamos la posicion actual
	                                                  //Al guardar la nueva posicion creamos un nuevo sistema de coordenadas relativo a simbad.
	                                                 //Su posicion actual es 0,0,0

	anim = pNode->getCreator()->createAnimation("walk", animDuration);          //creamos la animacion
	track = anim->createNodeTrack(0);                                          //creamos los tracks
	track->setAssociatedNode(sinbadNode);                                     //le asociamos el nodo de sinbad

	Vector3 src(0, 0, 1);                                                   //para las rotaciones
	Vector3 dest(0, 0, 1);
	Quaternion quat = src.getRotationTo(dest);

	longitudPaso = animDuration / 8;
	int i = 0;

//-----------------------------------Primer Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++); 
	keyFramePos = Vector3(0, 0, 50); //Posicion inicial
	kf->setTranslate(keyFramePos);
	quat = src.getRotationTo(dest);  //"cuarta" rotacion
	kf->setRotation(quat);     //se hace siempre
	
//-----------------------------------Segundo Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++); 
	keyFramePos = Vector3(0, 0, 550);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);

//-----------------------------------Tercer Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++); 
	keyFramePos = Vector3(-50, 0, 600);
	kf->setTranslate(keyFramePos);
	dest = { -1,0,0 };             //primera rotacion
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);

//-----------------------------------Cuarto Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++);
	keyFramePos = Vector3(-750, 0, 600);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);

//-----------------------------------Quinto Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++);
	keyFramePos = Vector3(-800, 0, 550);
	dest = { 0, 0, -1};           //segunda rotacion
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);
	kf->setTranslate(keyFramePos);

//-----------------------------------Sexto Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++);
	keyFramePos = Vector3(-800, 0, 50);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);

//-----------------------------------Septimo Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++);
	keyFramePos = Vector3(-750, 0, 0);
	dest = { 1, 0, 0 };            //tercera rotacion
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);

//-----------------------------------Octavo Frame---------------------
	kf = track->createNodeKeyFrame(longitudPaso * i++);
	keyFramePos = Vector3(-50, 0, 0);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);


	//El Loop se encarga de volver a la posicion inicial
	walkinState = pNode->getCreator()->createAnimationState("walk");
}

void Sinbad::suicide()
{
	if (suic == nullptr) {
		Vector3 src(0, 0, 1);

		suic = pNode->getCreator()->createAnimation("suicide", animDuration);      //creamos la animacion
		suiTrack = suic->createNodeTrack(0);
		suiTrack->setAssociatedNode(sinbadNode);


		bombPos = { -400, 0, 300 };                                               //posicion de la bomba ---> centro del plano

		Vector3 currentPos = sinbadNode->getPosition() - Vector3(400, 100, -300); //sacamos la posicion de origen --> la posicion global del nodo - posicion inicial local

		stepLeng = animDuration;

		sKf = suiTrack->createNodeKeyFrame(stepLeng * 0);
		sKf->setTranslate(currentPos);                      //primer frame esta en la posicion original
		Vector3 ori = bombPos - currentPos;                //sacamos el vector diferencia entre la bomba y la posicion actual para rotar a sinbad
		Quaternion quat = src.getRotationTo(ori);
		sKf->setRotation(quat);

		sKf = suiTrack->createNodeKeyFrame(stepLeng * 1);
		sKf->setTranslate(bombPos);          //en el segundo frame, trasladamos a sinbad
		sKf->setRotation(quat);

		suicideState = pNode->getCreator()->createAnimationState("suicide");
	}
}

void Sinbad::death()
{
	if (deathAnim == nullptr) {


		deathAnim = pNode->getCreator()->createAnimation("death", deathDuration);
		deathTrack = deathAnim->createNodeTrack(0);
		deathTrack->setAssociatedNode(sinbadNode);

		deathPos = sinbadNode->getPosition() - Vector3(400, 200, -300); // 200 para que este a lvl suelo


		Vector3 src(0, 0, 1);
		Vector3 dst(0, 1, 0);
		Quaternion quat;

		deathLenght = deathDuration / 2;

		//Primer frame
		deathKf = deathTrack->createNodeKeyFrame(deathLenght * 0);
		deathKf->setTranslate(deathPos);
		quat = src.getRotationTo(dst);
		deathKf->setRotation(quat);

		//Segundo frame
		deathKf = deathTrack->createNodeKeyFrame(deathLenght * 1);
		deathPos -= Vector3(-36000, 0, 0); //Movemos hacia la derecha
		deathKf->setTranslate(deathPos);//Movimiento
		deathKf->setRotation(quat); // rotacion

		deathState = pNode->getCreator()->createAnimationState("death");
	}
}
