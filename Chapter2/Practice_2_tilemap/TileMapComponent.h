#pragma
#include "SpriteComponent.h"
#include <string>
#include <vector>
#include "Math.h"

class TileMapComponent : public SpriteComponent {
public:
	// Set draw order to default to lower (so it's in the background)
	TileMapComponent(Actor* owner, int drawOrder=10);
	void Draw(SDL_Renderer* renderer) override;
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetTileMap(SDL_Texture* texture, std::vector<std::string>& csvNames, int rows, int cols);
private:
	struct TileMap
	{
		std::string csvName;
		int layer;
	};
	std::vector<TileMap> mTileMap;
	SDL_Texture* mTexture;
	Vector2 mScreenSize;
	int mTileRows;
	int mTileCols;
};