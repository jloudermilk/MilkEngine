#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_
#include <Utilities.h>
#include <tinyxml2.h>
#include <Sprite.h>

struct Char
{
	union{
		struct{
			std::string sName;
			Vector2 v2Size;
			Vector4 v4Location;
			float yOffset;
		};
		struct
		{
			std::string Name;
			float width, height;
			float x0,x1,y0,y1;
			float offset;
		};
	};
};

struct Font
{
	Vector2 v2Size;
	std::string sSheet;
	float fKerning;
};
class FontManager
{
public:
	static FontManager& Instance();

	void LoadFont(const char * a_pFontSheet);
	void DrawString(std::string str,Vector2 pos,float scale);
private:
	static void CleanUp();

	FontManager(void);
	~FontManager(void);
	void LoadString(std::string str);

	Sprite iSprite;
	Font FontAtlas;
	std::map<char,Char> charMap;
	std::vector<Char> DrawList;
	int CharCount;

	static FontManager* MInstance;

	///future use
	GLuint PositionBuffer;
	GLuint ColorBuffer;
	GLuint UVBuffer;
	GLuint MatrixBuffer;


};

#endif // _FONT_MANAGER_H_