#include "FontManager.h"

FontManager* FontManager::MInstance = 0;

FontManager& FontManager::Instance()
{
	if (MInstance == 0)
		MInstance = new FontManager();
	return *MInstance;
}

FontManager::FontManager(void)
{
	atexit(&CleanUp);


	/*	iSprite.LoadVertShader("../resources/fontVert.glsl");
		iSprite.LoadFragShader("../resources/fontFrag.glsl");
		iSprite.LinkShaders();
		*/
	glGenBuffers(1, &PositionBuffer);
	glGenBuffers(1, &ColorBuffer);
	glGenBuffers(1, &UVBuffer);
	glGenBuffers(1, &MatrixBuffer);


}


FontManager::~FontManager(void)
{
}

void FontManager::CleanUp()
{
	delete MInstance;
	MInstance = 0;
}

void FontManager::LoadFont(const char * a_pFontSheet)
{

	/*
	XML structure
	- Element "TextureAtlas"	the root element
	- - Attribute "imagePath"	attribute of TextureAtlas Element
	- - Attribute "width"		attribute of TextureAtlas Element
	- - Attribute "height"		attribute of TextureAtlas Element


	- -	Element "char"			child of TextureAtlas Element
	- - - Attribute "name"		attribute of char Element
	- - - Attribute "x"			attribute of char Element
	- - - Attribute "y"			attribute of char Element
	- - - Attribute "width"		attribute of char Element
	- - - Attribute "height"	attribute of char Element
	*/
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	char ch;
	doc.LoadFile(a_pFontSheet); // load the document
	rootNode = doc.FirstChildElement("TextureAtlas");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
	childElement = currentNode->ToElement();
	FontAtlas.sSheet = childElement->Attribute("imagePath");
	FontAtlas.v2Size.U = (float)childElement->IntAttribute("width");
	FontAtlas.v2Size.V = (float)childElement->IntAttribute("height");
	FontAtlas.fKerning = (float)childElement->IntAttribute("kerning");

	iSprite.LoadTexture(FontAtlas.sSheet.c_str());
	iSprite.m_Scale.x = FontAtlas.v2Size.U;
	iSprite.m_Scale.y = FontAtlas.v2Size.V;
	//GLint uvAttrib = glGetAttribLocation(iSprite.m_ShaderProgram,"texcoord");
	//glEnableVertexAttribArray(uvAttrib);
	//iSprite.matrix_location = glGetUniformLocation (iSprite.m_ShaderProgram, "matrix");

	for (childElement = currentNode->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		if (str.length() > 1)
		{

			if (str == "&amp")
				ch = '&';

			else if (str == "&apos")
				ch = '\'';

			else if (str == "&astr")
				ch = '*';

			else if (str == "&bar")
				ch = '|';

			else if (str == "&bslsh")
				ch = '\\';

			else if (str == "&col")
				ch = ':';

			else if (str == "&fslsh")
				ch = '/';

			else if (str == "&gt")
				ch = '>';

			else if (str == "&lt")
				ch = '<';

			else if (str == "&quest")
				ch = '?';

			else if (str == "&quot")
				ch = '\"';

			else if (str == "&under")
				ch = '_';


		}
		else{
			ch = str.at(0);
		}
		charMap[ch].Name = str;
		charMap[ch].x0 = childElement->IntAttribute("x");
		charMap[ch].y0 = childElement->IntAttribute("y");
		charMap[ch].width = childElement->IntAttribute("width");
		charMap[ch].height = childElement->IntAttribute("height");
		charMap[ch].x1 = charMap[ch].x0 + charMap[ch].width;
		charMap[ch].y1 = charMap[ch].y0 + charMap[ch].height;
		charMap[ch].offset = childElement->IntAttribute("offset");
	}
	//need to add a space
	//these could get moved to the xml file
	ch = ' ';
	charMap[ch].Name = " ";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 8;
	charMap[ch].height = 8;
	charMap[ch].x1 = 0;
	charMap[ch].y1 = 0;
	charMap[ch].offset = 0;
	ch = '\n';
	charMap[ch].Name = "&ret";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 0;
	charMap[ch].height = 0;
	charMap[ch].x1 = 0;
	charMap[ch].y1 = 0;
	charMap[ch].offset = 20;


}
void FontManager::LoadString(std::string str)
{
	DrawList.clear();
	char c;
	for (CharCount = 0; CharCount < str.length(); CharCount++)
	{
		c = str.at(CharCount);
		DrawList.push_back(charMap[c]);

	}
}



void FontManager::DrawString(std::string str, float2 pos, float scale)
{
	LoadString(str);


	Char c;

	float newPos = 0;
	for (int i = 0; i < DrawList.size(); i++)
	{
		c = DrawList[i];
		if (i != 0){

			if (c.Name == "&ret"){
				newPos = (pos.U - 4) * scale;
				pos.V -= c.offset * scale;
				
			}
			else{
				newPos = iSprite.m_Position.x +( (c.width / 2)*scale) + ((DrawList[i - 1].width / 2)*scale) + FontAtlas.fKerning;
				//newPos *= scale;
			}
			iSprite.m_Position = glm::vec3(newPos, pos.V - (c.offset*scale), 0.f);
		}
		else
			iSprite.m_Position = glm::vec3(pos.U + ((c.width / 2) * scale), pos.V - (c.offset*scale), 0.f);

		iSprite.m_UVData[0] = float2(c.x0 / FontAtlas.v2Size.U, c.y0 / FontAtlas.v2Size.V);
		iSprite.m_UVData[1] = float2(c.x1 / FontAtlas.v2Size.U, c.y0 / FontAtlas.v2Size.V);
		iSprite.m_UVData[2] = float2(c.x0 / FontAtlas.v2Size.U, c.y1 / FontAtlas.v2Size.V);
		iSprite.m_UVData[3] = float2(c.x1 / FontAtlas.v2Size.U, c.y1 / FontAtlas.v2Size.V);

		iSprite.m_Scale = glm::vec2(c.width*scale, c.height*scale);

		//Set scale of each char

		iSprite.SetUVData();
		iSprite.Update(.1f);
	}

}
