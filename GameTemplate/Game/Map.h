#pragma once
//class MovingFloor;
class Player;
class Map:public IGameObject
{
public:
	Map() {}
	~Map() {}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc);
private:
	const bool WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition);
	SpriteRender m_spriteRender;
	SpriteRender m_playerSprite;
	SpriteRender m_enemySprite;

	//MovingFloor* m_movingFloor = nullptr;
	Player* m_player = nullptr;
	bool m_isImage = false;
};

