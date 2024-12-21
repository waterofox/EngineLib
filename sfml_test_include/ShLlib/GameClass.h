#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameScene.h"

#include <iostream>
#include <fstream>

#include<vector>
#include<map>
#include<queue>


//������� ��� ��������� ������ � �������:
#define DELTA_TIME Game->getDeltaTime()
#define OBJECT Game->getVessel()

class GameClass
{
	//��� ��� ��������:
	using script = void(*)(GameClass*);

	//��� ��� ���������� ���������:
	using instruction = void(*)(GameClass*, Game::GameObject*);
private:
	//���� ��� �������� ������� �����:
	sf::Clock clock;
	sf::Time timeSinceLastUodate = sf::Time::Zero;
	sf::Time fixedDeltaTime = sf::Time::Zero;
	int framePerSeconds = 60;

	//���� ��� ����������� ����.�������
	sf::Event actualEvent;
	sf::Keyboard::Key key;

	//game events instructions
	std::map<int, instruction> instructions;
	std::queue<std::pair<int,Game::GameObject*>> gameEventQueue;		//todo ����� ���� ������ ����� ����, ����� ������������� ��������� ���� ���� ������� �� �����.

	sf::RenderWindow window; //�������� ����
	unsigned int width;
	unsigned int height;

	//game scene
	std::vector<Game::GameScene>* scene = nullptr;
	std::string sceneName = "";
	bool isSceneReady = false;

	sf::View camera; //������
	bool dynamicCamera = false;
	bool fullscreen = false;

	Game::GameObject* buferObject = nullptr; // ��� ������������ �������� (����� ������)

	//game scripts
	std::map<std::string, std::vector<script>> scripts;

public:
	//sfml classic methods
	void run();
	void eventHandling();
	void update();
	void render();

	void playerInput(sf::Keyboard::Key,bool isPressed); //todo ����� �������� ��� ���, ��� ������� ��� ����� ������������� (����� ������ ������� � ���� ��������� �� �����)


	bool loadScene(std::string path);

	bool getObject(std::string name, Game::GameObject*& buffer);
	Game::GameObject*& getVessel();

	void addScript(std::string sceneName, script scriptPtr);

	void addInstruction(int id, instruction instructionPtr);
	void emitGameEvent(int eventId,Game::GameObject * sender);

	sf::Vector2u getWindowSize();
	
	sf::Time getDeltaTime();

	sf::View& getCamera();


//important staff
	//constructors
	GameClass(unsigned int width, unsigned int height,unsigned int fps)
	{
		this->width = width;
		this->height = height;
		this->framePerSeconds = fps;
		this->fixedDeltaTime = sf::seconds(1.6 / fps);
	}
	//destructors
	~GameClass() 
	{ 
		delete scene;
		buferObject = nullptr;
	}
};
