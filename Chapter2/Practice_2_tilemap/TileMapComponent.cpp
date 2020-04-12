#include "TileMapComponent.h"
#include "Actor.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder)
{
}

void TileMapComponent::Draw(SDL_Renderer* renderer) {
	for (auto& tilemap : mTileMap) {
		std::ifstream fin(tilemap.csvName);
		std::string line;
		std::vector<std::vector<int>> fields;
		SDL_Rect tile;
		SDL_Rect r;
		int mTextureWidth;
		int mTextureHeight;
		int rows;
		int cols;
		SDL_QueryTexture(mTexture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
		while (getline(fin, line))
		{
			std::istringstream sin(line);
			std::vector<int> rowContent;
			std::string field;
			while (getline(sin, field, ','))
			{
				rowContent.push_back(std::stoi(field));

			}
			fields.push_back(rowContent);
		}
		rows = fields.size();
		cols = fields[0].size();
		int test_count = 0;
		for (int i = 0; i < fields.size(); i++) {
			for (int j = 0; j < fields[i].size(); j++) {
				if (fields[i][j] == -1) continue;
				tile.w = static_cast<int>(mTextureWidth / mTileCols);
				tile.h = static_cast<int>(mTextureHeight / mTileRows);
				tile.x = (fields[i][j] % mTileCols) * tile.w;
				tile.y = (fields[i][j] / mTileCols) * tile.h;
				r.w = static_cast<int>(mScreenSize.x / cols);
				r.h = static_cast<int>(mScreenSize.y / rows);
				// Center the rectangle around the position of the owner
				r.x = r.w * j;
				r.y = r.h * i;
				// Draw this tile
				SDL_RenderCopyEx(
					renderer, 
					mTexture, 
					&tile, 
					&r, 
					-Math::ToDegrees(mOwner->GetRotation()),
					nullptr,
					SDL_FLIP_NONE
				);
			}
		}
	}


}

void TileMapComponent::SetTileMap(SDL_Texture* texture, std::vector<std::string>& csvNames, int rows, int cols) {
	int count = 0;
	for (std::string csvName : csvNames) {
		TileMap temp;
		temp.csvName = csvName;
		temp.layer = 0;
		mTileMap.emplace_back(temp);
		count++;
	}
	mTexture = texture;
	mTileRows = rows;
	mTileCols = cols;
}