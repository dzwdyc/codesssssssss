
#ifndef __TEXTURE_CONTROL__
#define __TEXTURE_CONTROL__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

typedef enum
{
	TexturePathNONE,
	TexturePathFigure,
	TexturePathMonster,
	TexturePathHair,
	TexturePathWeapon, 
	TexturePathSkillCaster, 
	TexturePathSkillLocus, 
	TexturePathSkillExplosion 
} TexturePathType;

class TextureController {
    
public:
    
    static string getTextureRoute(TexturePathType type, unsigned int number);
    
    static string getTexturePath(TexturePathType type, unsigned int number);
    
    static void addSpriteFrames(TexturePathType type, unsigned int number, Ref *target = NULL, SEL_CallFunc selector = NULL);
    
    static void subSpriteFrames(TexturePathType type, unsigned int number);
    
    static void removeAllSpriteFrames();
    
};


#endif /* defined(__TEXTURE_CONTROL__) */
