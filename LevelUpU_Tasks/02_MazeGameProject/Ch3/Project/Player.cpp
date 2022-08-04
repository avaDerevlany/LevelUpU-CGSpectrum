#include <iostream>

#include "Player.h"
#include "Key.h"
#include "Sword.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player()
	: PlacableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberOfLives)
{

}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

bool Player::HasSword()
{
	return m_pSword != nullptr;
}

void Player::PickupSword(Sword* sword)
{
	m_pSword = sword;
}

void Player::RemoveSword()
{
	m_pSword = nullptr;
}

void Player::UseSword()
{
	if (m_pSword)
	{
		// swish
	}
}

void Player::Draw()
{
	cout << "@";
}
