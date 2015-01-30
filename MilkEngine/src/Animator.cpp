#include "Animator.h"


Animator::Animator(void)
{
	
}


Animator::~Animator(void)
{
}
void Animator::ImportSheet( const char* a_pSpriteSheet)
{
	LoadSprites(a_pSpriteSheet);
	LoadAnimations(atlas.sAnimations.c_str());


	/*This doesnt work for some reason
	//I figured it out its in the math lib
	m_minUVCoords = Vector2(mSprites["idle"].x0,mSprites["idle"].y0);
	m_maxUVCoords = Vector2(mSprites["idle"].x1,mSprites["idle"].y1);
	m_uvScale = Vector2(atlas.v2Size.m_fX,atlas.v2Size.m_fY);
	*/


	m_dFrames = (1.0/15.0);
	currentAnimation = "";
	currentSprite = "idle";
	currentFrame = 0;
	currentPlayType = SINGLE;
	SetSprite();
	



}

void Animator::SetSprite()
{
	if(currentAnimation == "")
	{
	m_UVData[0].U = mSprites["idle"].x0;
	m_UVData[0].V = mSprites["idle"].y0;
	m_UVData[1].U = mSprites["idle"].x1;
	m_UVData[1].V = mSprites["idle"].y1;
	m_SpriteScale.U = mSprites[currentSprite].width;
	m_SpriteScale.V = mSprites[currentSprite].height;
	}else
	{
		
		m_UVData[0].U = mSprites[currentSprite].x0;
		m_UVData[0].V = mSprites[currentSprite].y0;
		m_UVData[1].U = mSprites[currentSprite].x1;
		m_UVData[1].V = mSprites[currentSprite].y1;
m_SpriteScale.U =  mSprites[currentSprite].width;
m_SpriteScale.V = mSprites[currentSprite].height;

	}
}


void Animator::LoadSprites(const char* a_pSpriteSheet)
{
	/*
	XML structure
	- Element "atlas"			the root element
	- - Attribute "width"		attribute of atlas Element
	- - Attribute "height"		attribute of atlas Element
	- - Attribute "sheet"		attribute of atlas Element
	- - Attribute "animations"	attribute of atlas Element

	- -	Element "sprite"		child of atlas Element
	- - - Attribute "name"		attribute of sprite Element
	- - - Attribute "x"			attribute of sprite Element
	- - - Attribute "y"			attribute of sprite Element
	- - - Attribute "width"		attribute of sprite Element
	- - - Attribute "height"	attribute of sprite Element
	*/
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	doc.LoadFile(a_pSpriteSheet); // load the document
	rootNode = doc.FirstChildElement("atlas");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
	childElement = currentNode->ToElement();
	atlas.width = (float)childElement->IntAttribute("width"); 
	atlas.height = (float)childElement->IntAttribute("height");
	atlas.sSheet = childElement->Attribute("sheet");
	atlas.sAnimations = childElement->Attribute("animations");


	for (childElement = currentNode->FirstChildElement(); 
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		mSprites[str].Name = str;
		mSprites[str].x0 = childElement->IntAttribute("x0");
		mSprites[str].x1 = childElement->IntAttribute("x1");
		mSprites[str].y0 = childElement->IntAttribute("y0");
		mSprites[str].y1 = childElement->IntAttribute("y1");
		mSprites[str].height = mSprites[str].y1 - mSprites[str].y0;
		mSprites[str].width = mSprites[str].x1 - mSprites[str].x0;
	}
std:printf("Sprite load done!\n");


}
void Animator::LoadAnimations(const char* a_pAnimationSheet)
{
	/*
	XML structure
	<animation name = "teleport" fps = "30">
	<frame>tpod 0</frame>
	- Element "animation"		a root element
	- - Attribute "name"		attribute of animation Element
	- - Attribute "fps"			attribute of animation Element

	- -	Element "frame"		child of animation Element
	- - - Attribute "name"		attribute of frame Element
	*/
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement, *child;
	std::string str,aniName;
	doc.LoadFile(a_pAnimationSheet); // load the document
	rootNode = doc.FirstChildElement("animation");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child

	for (childElement = currentNode->ToElement(); 
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		aniName = childElement->Attribute("name");
		int i = 0;
		for (child = childElement->FirstChildElement(); 
			child != NULL; child = child->NextSiblingElement())
		{

			str = child->Attribute("name");
			mAnimations[aniName].push_back(str);
			i++;
		}
	}
std:printf("Animation load done!\n");

}


void Animator::SetAnimation(std::string animation,PlayType type)
{
	currentAnimation = animation;
	currentFrame = 0;
	loopFrame = 0;
	currentPlayType = type;
	switch (type){
	case ONCE:
		
		break;
	case LOOP:
		loopFrame =0;
		break;
	case PINGPONG:
		break;
	case REVERSE:
		currentFrame = mAnimations[currentAnimation].size();
		loopFrame = currentFrame;
		break;
	case RANDOMLOOP:
	case RANDOM:
		/*srand(time(NULL));
		currentFrame =  (unsigned int)(rand() % mAnimations[currentAnimation].size());
		loopFrame = currentFrame;
		*/break;
	case LOOPSECTION:
		SetAnimation(animation,type, 0);
	case SINGLE:
		break;
	default:
		break;
	}
	currentSprite = mAnimations.at(currentAnimation)[currentFrame];
	SetSprite();
	

}
void Animator::SetAnimation(std::string animation,PlayType type, int frame)
{
	switch(type)
	{
	case LOOPSECTION:
	currentAnimation = animation;
	currentFrame = 0;
	currentPlayType = type;
	loopFrame = frame;
	break;
	default:
		SetAnimation(animation,type);
		break;
	}

}
void Animator::PlayAnimation()
{
	elapsedTime += getDeltaTime();
	
	if(elapsedTime > m_dFrames){
		elapsedTime = 0;
	switch (currentPlayType){
	case ONCE:
		if(mAnimations.at(currentAnimation)[currentFrame] != mAnimations.at(currentAnimation).back())
		{
			currentFrame++;
			currentSprite = mAnimations.at(currentAnimation)[currentFrame];
		}
		break;
	case LOOPSECTION:
	case LOOP:
		if(mAnimations.at(currentAnimation)[currentFrame] == mAnimations.at(currentAnimation).back())
		{
			currentFrame = loopFrame;
			currentSprite = mAnimations.at(currentAnimation)[currentFrame];
		}
		else
		{
			currentFrame++;
			currentSprite = mAnimations.at(currentAnimation)[currentFrame];
		}
		break;
	case PINGPONG:
		break;
	case REVERSE:
		currentFrame = mAnimations[currentAnimation].size();
		loopFrame = currentFrame;
		break;
	case RANDOMLOOP:
	case RANDOM:
	/*	srand(time(NULL));
		currentFrame =  rand() % mAnimations[currentAnimation].size();
		loopFrame = currentFrame;
		*/break;
	case SINGLE:
		break;
	default:
		break;
	}
	SetSprite();
	}



}

void Animator::SetUVData(float2 * data)
{
	data[0].U = m_UVData[0].U / atlas.width;
	data[0].V = m_UVData[0].V/ atlas.height;
	data[1].U = m_UVData[1].U / atlas.width;
	data[1].V = m_UVData[0].V / atlas.height;
	data[2].U = m_UVData[0].U / atlas.width;
	data[2].V = m_UVData[1].V / atlas.height;
	data[3].U = m_UVData[1].U / atlas.width;
	data[3].V = m_UVData[1].V / atlas.height;

}
void Animator::Update()
{
	

	PlayAnimation();


}