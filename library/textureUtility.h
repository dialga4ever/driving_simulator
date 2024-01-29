#include <SFML/Graphics.hpp>
#include <iostream>
/**
 * The function loads a texture from a file and sets it as the texture for a sprite, then sets the
 * position of the sprite.
 * 
 * @param self The "self" parameter is a reference to the sf::Sprite object that the function is being
 * called on.
 * @param filename The filename parameter is a string that represents the path to the image file that
 * you want to load as a texture for the sprite.
 * @param x The x-coordinate of the position where the sprite will be placed on the screen.
 * @param y The parameter "y" represents the y-coordinate of the position where the sprite will be
 * placed on the screen.
 */
void spriteLoadFromFilePos(sf::Sprite *self,sf::Texture *quitTexture, const std::string &filename, int x, int y);
/**
 * The function "centerOrigin" centers the origin of a given sprite.
 * 
 * @param self The parameter "self" is of type sf::Sprite. It represents the sprite object that we want
 * to center the origin of.
 */
void centerOrigin(sf::Sprite *self);


void centerTextOrigin(sf::Text *self);