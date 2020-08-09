#include "Plane.h"
#include "TextureManager.h"

Plane::Plane()
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	m_buildAnimations();

	m_angle = 0.0f;

	m_playerDetected = false;
	m_haveLOS = false;

	m_buildDecisionTree();
}

Plane::~Plane()
= default;

void Plane::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation(
		"spritesheet", getAnimation("plane"), x, y, 0.5f, m_angle, 255, true);
}

void Plane::update()
{
	m_checkCurrentConditions();
	m_brain.Update(this);
}

void Plane::clean()
{
}

void Plane::setAngle(float angle)
{
	m_angle = angle;
}

void Plane::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}

void Plane::m_buildDecisionTree()
{
	// root
	m_root = new TreeNode();
	m_root->Name = "LOS?";
	m_root->isRoot = true;
	m_root->condition = [&]()->bool { return m_haveLOS;  };

	// root->left
	m_root->leftChild = new TreeNode();
	m_root->leftChild->Name = "Radius Detection?";
	m_root->leftChild->condition  = [&]()->bool { return m_playerDetected;  };

	// root->left->right
	m_root->leftChild->rightChild = new TreeNode();
	m_root->leftChild->rightChild->Name = "Move to LOS";
	m_root->leftChild->rightChild->action = [&]()->void { /* move to LOS action */ };
	m_root->leftChild->rightChild->isLeaf = true;

	// root->left-left
	m_root->leftChild->leftChild = new TreeNode();
	m_root->leftChild->leftChild->Name = "Patrol";
	m_root->leftChild->leftChild->action = [&]()->void { /* Patrol action */ };
	m_root->leftChild->leftChild->isLeaf = true;

	//root->right
	m_root->rightChild = new TreeNode();
	m_root->rightChild->Name = "Close Combat Range?";
	m_root->rightChild->condition = [&]()->bool { return m_withinMeleeRange;  };

	// root->right->right
	m_root->rightChild->rightChild = new TreeNode();
	m_root->rightChild->rightChild->Name = "Close Combat Attack";
	m_root->rightChild->rightChild->action = [&]()->void { /*perform close combat attack */ };
	m_root->rightChild->rightChild->isLeaf = true;

	// root->right->left
	m_root->rightChild->leftChild = new TreeNode();
	m_root->rightChild->leftChild->Name = "Move to Close Combat Range";
	m_root->rightChild->rightChild->action = [&]()->void { /*perform move to close combat range */ };
	m_root->rightChild->leftChild->isLeaf = true;
}

void Plane::m_checkCurrentConditions()
{
	if (m_health >= 25)
	{
		if (m_playerDetected)
		{
			if (m_haveLOS)
			{
				// check the distance
				
				if (m_withinMeleeRange)
				{
					m_brain.SetInnerState(MELEE_ATTACK);
				}
				else
				{
					m_brain.SetInnerState(MOVE_TO_MELEE);
				}
			}
			else
			{
				m_brain.SetInnerState(MOVE_TO_LOS);
			}
		}
	}
	else
	{
		m_brain.SetOuterState(FLIGHT);
	}
}
