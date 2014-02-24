#include"InputManager.h"
vector<pair<unsigned char, keyState> > InputManager::Keys = vector<pair<unsigned char, keyState> >();
vector<pair<unsigned char, keyState> > InputManager::Mouse = vector<pair<unsigned char, keyState> >();
vec2 InputManager::mousePosition = vec2();

vec2 InputManager::getMousePosition(){
	return mousePosition;
}

keyState InputManager::getKey(unsigned int key){
	if(Keys.size()<=0)
		return keyState::NONE;
	for(auto k : Keys){
		if(k.first == key)
			return k.second;
	}
	return keyState::NONE;
}

keyState InputManager::getMouseButton(unsigned int key){
	if(Mouse.size()<=0)
		return keyState::NONE;

	for(auto button : Mouse){
		if(button.first == key)
			return button.second;
	}
	return keyState::NONE;
}

void InputManager::update(){
}